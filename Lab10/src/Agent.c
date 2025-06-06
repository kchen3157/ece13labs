/**
 * Agent.c
 *
 * Implementation of Agent Module
 *
 * @author  Kyle Chen
 *
 * @date    28 May 2025
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "Agent.h"
#include "Oled.h"
#include "Field.h"
#include "FieldOled.h"
#include "Negotiation.h"

// TODO: Ensure Everything is random

// * Global Vars
static volatile AgentState agent_state;
static volatile FieldOledTurn playerTurn;
static volatile uint8_t turn_count;
static Field my_field;
static Field op_field;

static volatile GuessData guess;

static volatile NegotiationData hash_A;    // A
static volatile NegotiationData hash_B;    // B
static volatile NegotiationData hash_sA;   // #A

static volatile NegotiationOutcome outcome;

static char dialog_buffer[100];

void DrawDialog(void)
{
    OLED_Clear(OLED_COLOR_BLACK);
    OLED_DrawString(dialog_buffer);
    OLED_Update();
}

void AgentInit(void)
{
    // Set initial state and turn counter
    agent_state = AGENT_STATE_START;
    turn_count = 0;
    playerTurn = FIELD_OLED_TURN_NONE;

    sprintf(dialog_buffer, "BATTLEBOATS:\n\nPress BTN4 to begin,\nor wait for PLAYER2.");
    DrawDialog();
}

Message AgentRun(BB_Event event)
{
    Message message_out = {.type = MESSAGE_NONE, .param0 = 0, .param1 = 0, .param2 = 0};

    if (event.type == BB_EVENT_RESET_BUTTON)
    {
        agent_state = AGENT_STATE_START;
        AgentInit();
        return message_out;
    }

    if (event.type == BB_EVENT_ERROR)
    {
        sprintf(dialog_buffer, "Error detected.\nPlease reset.");
        DrawDialog();
        agent_state = AGENT_STATE_END_SCREEN;
        return message_out;
    }
    
    switch (agent_state)
    {
        case AGENT_STATE_START:
        {
            if (event.type == BB_EVENT_START_BUTTON) // You are Challenger
            {
                // Generate A and #A hash
                hash_A = (uint16_t) (rand() & 0xFFFF);
                hash_sA = NegotiationHash(hash_A);
                
                // Send out #A hash
                message_out.type = MESSAGE_CHA;
                message_out.param0 = hash_sA;

                // Init fields
                FieldInit(&my_field, &op_field);
                FieldAIPlaceAllBoats(&my_field);

                sprintf(dialog_buffer, "Waiting for\nopponent...");
                DrawDialog();

                agent_state = AGENT_STATE_CHALLENGING;

                printf("%u", hash_A);
            }
            else if (event.type == BB_EVENT_CHA_RECEIVED) // Upon getting A
            {
                // Generate B hash
                hash_B = (uint16_t) (rand() & 0xFFFF);

                // Send out B hash
                message_out.type = MESSAGE_ACC;
                message_out.param0 = hash_B;

                // Init fields
                FieldInit(&my_field, &op_field);
                FieldAIPlaceAllBoats(&my_field);

                agent_state = AGENT_STATE_ACCEPTING;
            }
            break;
        }
        case AGENT_STATE_CHALLENGING: 
        {
            if (event.type == BB_EVENT_ACC_RECEIVED) // Upon getting B
            {
                // Receive B hash
                hash_B = event.param0;

                // Send out A hash
                message_out.type = MESSAGE_REV;
                message_out.param0 = hash_A;

                // Determine heads/tails
                outcome = NegotiateCoinFlip(hash_A, hash_B);
                if (outcome == HEADS)
                {
                    playerTurn = FIELD_OLED_TURN_MINE;
                    agent_state = AGENT_STATE_WAITING_TO_SEND;
                }
                else
                {
                    playerTurn = FIELD_OLED_TURN_THEIRS;
                    agent_state = AGENT_STATE_DEFENDING;
                }

                if (playerTurn == FIELD_OLED_TURN_MINE)
                {
                    printf("My turn\n");
                }
                else if (playerTurn == FIELD_OLED_TURN_THEIRS)
                {
                    printf("Their turn\n");
                }

                FieldOledDrawScreen(&my_field, &op_field, playerTurn, turn_count);
            }
            break;
        }
        case AGENT_STATE_ACCEPTING: // You are B
        {
            if (event.type == BB_EVENT_REV_RECEIVED)
            {
                // Receive A hash
                hash_A = event.param0;

                // Determine heads/tails
                outcome = NegotiateCoinFlip(hash_A, hash_B);
                if (NegotiationVerify(hash_A, hash_sA))  // Verify A hash with commitment
                {
                    sprintf(dialog_buffer, "END: Cheating Detected.");
                    DrawDialog();
                    agent_state = AGENT_STATE_END_SCREEN;
                }
                else if (outcome == HEADS) 
                {
                    playerTurn = FIELD_OLED_TURN_THEIRS;
                    agent_state = AGENT_STATE_DEFENDING;
                }
                else
                {
                    playerTurn = FIELD_OLED_TURN_MINE;

                    // Decide guess shot
                    GuessData guess = FieldAIDecideGuess(&op_field);

                    // Send shot
                    message_out.type = MESSAGE_SHO;
                    message_out.param0 = guess.row;
                    message_out.param1 = guess.col;

                    agent_state = AGENT_STATE_ATTACKING;
                }

                FieldOledDrawScreen(&my_field, &op_field, playerTurn, turn_count);
            }
            break;
        }
        case AGENT_STATE_WAITING_TO_SEND:
        {
            if (event.type == BB_EVENT_MESSAGE_SENT)
            {
                turn_count++;

                // Decide guess shot
                guess = FieldAIDecideGuess(&op_field);

                // Send shot
                message_out.type = MESSAGE_SHO;
                message_out.param0 = guess.row;
                message_out.param1 = guess.col;

                agent_state = AGENT_STATE_ATTACKING;
            }
            break;
        }
        case AGENT_STATE_ATTACKING:
        {
            if (event.type == BB_EVENT_RES_RECEIVED)
            {
                // Receive attack results and update opponent's field
                GuessData attack_result;
                attack_result.row = event.param0;
                attack_result.col = event.param1;
                attack_result.result = event.param2;
                FieldUpdateKnowledge(&op_field, &attack_result);

                // Draw screen
                FieldOledDrawScreen(&my_field, &op_field, playerTurn, turn_count);
                
                // Determine if endgame
                if (FieldGetBoatStates(&op_field) == 0) // States = 0, all op boats sunk
                {
                    sprintf(dialog_buffer, "END: Victory.");
                    DrawDialog();
                    agent_state = AGENT_STATE_END_SCREEN; // VICTORY
                }
                else
                {
                    agent_state = AGENT_STATE_DEFENDING;
                }  
            }
            break;
        }
        case AGENT_STATE_DEFENDING:
        {
            if (event.type == BB_EVENT_SHO_RECEIVED)
            {
                // Receive attack details and apply to your board
                GuessData attack;
                attack.row = event.param0;
                attack.col = event.param1;
                FieldRegisterEnemyAttack(&my_field, &attack);

                // Send out attack results
                message_out.type = MESSAGE_RES;
                message_out.param0 = attack.row;
                message_out.param1 = attack.col;
                message_out.param2 = attack.result;

                // Draw screen
                FieldOledDrawScreen(&my_field, &op_field, playerTurn, turn_count);

                // Determine if endgame
                if (FieldGetBoatStates(&my_field) == 0) // States = 0, all of my boats sunk
                {
                    sprintf(dialog_buffer, "END: Defeat.");
                    DrawDialog();
                    agent_state = AGENT_STATE_END_SCREEN; // DEFEAT
                }
                else
                {
                    agent_state = AGENT_STATE_WAITING_TO_SEND;
                }
            }
            break;
        }
        case AGENT_STATE_END_SCREEN:
        {
            // If entered, stay here.
            DrawDialog();
            break;
        }
        default:
        {
            sprintf(dialog_buffer, "FATAL ERROR:\nInvalid State");
            DrawDialog();
            break;
        }
    }

    return message_out;
}

AgentState AgentGetState(void)
{
    return agent_state;
}

void AgentSetState(AgentState newState)
{
    agent_state = newState;
}
