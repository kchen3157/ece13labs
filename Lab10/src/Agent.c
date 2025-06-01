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

#include "Agent.h"
#include "Oled.h"
#include "Field.h"
#include "FieldOled.h"


// * Global Vars
static volatile AgentState agent_state;
static volatile uint16_t turn;
static volatile Field my_field;
static volatile Field op_field;


/** AgentInit()
 *
 * The Init() function for an Agent sets up everything necessary for an agent
 * before the game starts.  At a minimum, this requires:
 *   -setting the start state of the Agent SM.
 *   -setting turn counter to 0
 *
 * If you are using any other persistent data in Agent SM, that should be reset
 * as well.
 * 
 * It is not advised to call srand() inside of AgentInit().
 */
void AgentInit(void)
{
    agent_state = AGENT_STATE_START;
    turn = 0;

    OLED_Clear(OLED_COLOR_BLACK);
    OLED_DrawString("BATTLEBOATS:\n\nPress BTN4 to begin,\nor wait for PLAYER2.");
    OLED_Update();
}

/** AgentRun(event)
 *
 * AgentRun() evolves the Agent state machine in response to an event.
 * 
 * If the returned Message struct is a valid message (that is, not of type
 * MESSAGE_NONE), then it will be passed to the transmission module and sent via
 * UART. This is handled at the top level! AgentRun is ONLY responsible for
 * generating the Message struct, not for encoding or sending it.
 * 
 * @param   event   The most recently detected event
 * @return  Message, a Message struct to send to the opponent. 
 */
Message AgentRun(BB_Event event)
{
    Message message_out;
    
    switch (agent_state)
    {
        case AGENT_STATE_START:
        {
            if (event.type == BB_EVENT_START_BUTTON)
            {
                message_out.type = MESSAGE_CHA;

                // Generate A hash
                int16_t hash_A = (int16_t) (rand() & 0xFFFF);
                
                // Generate #a secret key
                message_out.param0 = (hash_A * hash_A) % 0xBEEF;

                // Init fields
                FieldInit(&my_field, &op_field);

                // Place own boats
                FieldAIPlaceAllBoats(&my_field);

                agent_state = AGENT_STATE_CHALLENGING;
            }
            else if (event.type == BB_EVENT_CHA_RECEIVED)
            {
                message_out.type = MESSAGE_ACC;
                // Generate B
                message_out.param0 = (int16_t) (rand() & 0xFFFF);
                // Send ACC
                // Init fields
                FieldInit(&my_field, &op_field);
                // Place own boats
                FieldAIPlaceAllBoats(&my_field);

                agent_state = AGENT_STATE_ACCEPTING;
            }
            break;
        }
        case AGENT_STATE_CHALLENGING:
        {
            break;
        }
        case AGENT_STATE_ACCEPTING:
        {
            break;
        }
        default:
        {
            break;
        }
    }
}

/** AgentGetState() 
 *
 * This function is very useful for testing AgentRun().
 *
 * @return  Returns the current state that AgentGetState() is in.
 */
AgentState AgentGetState(void)
{
    return agent_state;
}

/** AgentSetState(newState)
 * 
 * This function is very useful for testing AgentRun().
 *
 * @param   newState    Force the agent into the state given by AgentState.
 */
void AgentSetState(AgentState newState)
{
    agent_state = newState;
}
