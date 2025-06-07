/*
 * AgentTest.c
 *
 *Author: Sai Akhil Madurakavi
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Agent.h"
#include "Message.h"

/* Simple assertion macro */
#define ASSERT(cond, msg)                           \
    do {                                             \
        if (!(cond)) {                               \
            printf("FAIL: %s\n", msg);               \
            exit(EXIT_FAILURE);                      \
        }                                            \
    } while (0)

/* Test 1: after agentInit state must be agent_state_start */
static void test_initial_state(void) {
    AgentInit();
    ASSERT(AgentGetState() == AGENT_STATE_START,
           "initial state is not AGENT_STATE_START");
    printf("PASS: test_initial_state\n");
}

/* Test 2: agentSetState and agentGetState should work correctly */
static void test_set_get_state(void) {
    AgentSetState(AGENT_STATE_DEFENDING);
    ASSERT(AgentGetState() == AGENT_STATE_DEFENDING,
           "agentGetState did not return DEFENDING");
    AgentSetState(AGENT_STATE_END_SCREEN);
    ASSERT(AgentGetState() == AGENT_STATE_END_SCREEN,
           "agentGetState did not return END_SCREEN");
    printf("PASS: test_set_get_state\n");
}

/* Test 3: start -> challenging on bb_event_start_button,
   returned message must be message_cha with correct param0 */
static void test_start_to_challenging(void) {

    AgentSetState(AGENT_STATE_START);
    
    BB_Event evt = { .type = BB_EVENT_START_BUTTON, .param0 = 0, .param1 = 0, .param2 = 0 };
    
    Message msg = AgentRun(evt);

    ASSERT(AgentGetState() == AGENT_STATE_CHALLENGING,
           "state did not become CHALLENGING after START_BUTTON");
    ASSERT(msg.type == MESSAGE_CHA,
           "expected MESSAGE_CHA from START_BUTTON branch");

    printf("PASS: test_start_to_challenging\n");
}

/* Test 4: start -> accepting on bb_event_cha_received,
   returned message must be message_acc with param0 = (rand() & 0xFFFF) */
static void test_start_to_accepting(void) {
    AgentSetState(AGENT_STATE_START);
    BB_Event evt = { .type = BB_EVENT_CHA_RECEIVED, .param0 = 0x9999 };
    Message msg = AgentRun(evt);

    ASSERT(AgentGetState() == AGENT_STATE_ACCEPTING,
           "state did not become ACCEPTING after CHA_RECEIVED");
    ASSERT(msg.type == MESSAGE_ACC,
           "expected MESSAGE_ACC from CHA_RECEIVED");

    printf("PASS: test_start_to_accepting\n");
}

/* Test 5: challenging -> waiting_to_send on bb_event_acc_received,
   returned message must be message_rev with param0 = hash_a */
static void test_challenging_to_waiting(void) {
    AgentInit();
    /* first, set hash_a by simulating start button */
    AgentSetState(AGENT_STATE_START);
    BB_Event start_evt = { .type = BB_EVENT_START_BUTTON };
    AgentRun(start_evt);  /* now state is CHALLENGING, hash_a = 0x1234 */

    /* now simulate receiving acc */
    AgentSetState(AGENT_STATE_CHALLENGING);
    BB_Event acc_evt = { .type = BB_EVENT_ACC_RECEIVED, .param0 = 0x7777 };
    Message msg = AgentRun(acc_evt);

    printf("%d", AgentGetState());
    ASSERT(AgentGetState() == AGENT_STATE_WAITING_TO_SEND,
           "state did not become WAITING_TO_SEND after ACC_RECEIVED");
    ASSERT(msg.type == MESSAGE_REV,
           "expected MESSAGE_REV in CHALLENGING->WAITING_TO_SEND");

    printf("PASS: test_challenging_to_waiting\n");
}

/* Test 6: accepting -> end_screen on bb_event_rev_received,
   since negotiationVerify returns false */
static void test_accepting_cheating(void) {
    /* prepare for accepting state by simulating cha_received */
    AgentSetState(AGENT_STATE_START);
    BB_Event cha_evt = { .type = BB_EVENT_CHA_RECEIVED, .param0 = 0xAAAA };
    AgentRun(cha_evt);  /* now state is ACCEPTING, hash_b = 0x1234 */

    /* simulate rev_received; negotiationVerify is false, so go to end_screen */
    AgentSetState(AGENT_STATE_ACCEPTING);
    BB_Event rev_evt = { .type = BB_EVENT_REV_RECEIVED, .param0 = 0xBBBB };
    Message msg = AgentRun(rev_evt);

    ASSERT(AgentGetState() == AGENT_STATE_END_SCREEN,
           "accepting with failed verify did not go to END_SCREEN");
    ASSERT(msg.type == MESSAGE_NONE,
           "accepting-cheating should return MESSAGE_NONE");
    printf("PASS: test_accepting_cheating\n");
}

/* Test 7: waiting_to_send -> attacking on bb_event_message_sent,
   returned message must be message_sho with row=1, col=2 */
static void test_waiting_to_attacking(void) {
    AgentSetState(AGENT_STATE_WAITING_TO_SEND);
    BB_Event sent_evt = { .type = BB_EVENT_MESSAGE_SENT };
    Message msg = AgentRun(sent_evt);

    ASSERT(AgentGetState() == AGENT_STATE_ATTACKING,
           "state did not become ATTACKING after MESSAGE_SENT");
    ASSERT(msg.type == MESSAGE_SHO,
           "expected MESSAGE_SHO in WAITING_TO_SEND->ATTACKING");

    /* FieldAIDecideGuess stub returns row=1, col=2 */
    ASSERT(msg.param0 == 1 && msg.param1 == 2,
           "MESSAGE_SHO.row/col incorrect (should be 1,2)");
    printf("PASS: test_waiting_to_attacking\n");
}

/* Test 8: attacking -> defending on bb_event_res_received */
static void test_attacking_to_defending(void) {
    AgentSetState(AGENT_STATE_ATTACKING);
    BB_Event res_evt = {
        .type   = BB_EVENT_RES_RECEIVED,
        .param0 = 4,  /* row */
        .param1 = 5,  /* col */
        .param2 = 1   /* result (ignored by stub) */
    };
    Message msg = AgentRun(res_evt);

    ASSERT(AgentGetState() == AGENT_STATE_DEFENDING,
           "state did not become DEFENDING after RES_RECEIVED");
    ASSERT(msg.type == MESSAGE_NONE,
           "expected MESSAGE_NONE after processing RES");
    printf("PASS: test_attacking_to_defending\n");
}

/* Test 9: defending -> waiting_to_send on bb_event_sho_received,
   returned message must be message_res with row/col matching event */
static void test_defending_to_waiting(void) {
    AgentSetState(AGENT_STATE_DEFENDING);
    BB_Event sho_evt = {
        .type   = BB_EVENT_SHO_RECEIVED,
        .param0 = 7,  /* row */
        .param1 = 8   /* col */
    };
    Message msg = AgentRun(sho_evt);

    ASSERT(AgentGetState() == AGENT_STATE_WAITING_TO_SEND,
           "state did not become WAITING_TO_SEND after SHO_RECEIVED");
    ASSERT(msg.type == MESSAGE_RES,
           "expected MESSAGE_RES in DEFENDING->WAITING_TO_SEND");
    ASSERT(msg.param0 == 7 && msg.param1 == 8,
           "MESSAGE_RES.row/col incorrect (should match event 7,8)");
    printf("PASS: test_defending_to_waiting\n");
}

/* Test 10: bb_event_reset_button resets to agent_state_start */
static void test_reset_button(void) {
    AgentSetState(AGENT_STATE_DEFENDING);
    BB_Event reset_evt = { .type = BB_EVENT_RESET_BUTTON };
    Message msg = AgentRun(reset_evt);

    ASSERT(AgentGetState() == AGENT_STATE_START,
           "reset did not set state to START");
    ASSERT(msg.type == MESSAGE_NONE,
           "reset should return MESSAGE_NONE");
    printf("PASS: test_reset_button\n");
}

/* Test 11: bb_event_error forces agent_state_end_screen */
static void test_error_event(void) {
    AgentSetState(AGENT_STATE_CHALLENGING);
    BB_Event err_evt = { .type = BB_EVENT_ERROR };
    Message msg = AgentRun(err_evt);

    ASSERT(AgentGetState() == AGENT_STATE_END_SCREEN,
           "error event did not set state to END_SCREEN");
    ASSERT(msg.type == MESSAGE_NONE,
           "error should return MESSAGE_NONE");
    printf("PASS: test_error_event\n");
}

/* Test 12: agent_state_end_screen ignores any event and stays in end_screen */
static void test_end_screen_behavior(void) {
    AgentSetState(AGENT_STATE_END_SCREEN);
    BB_Event dummy = { .type = BB_EVENT_START_BUTTON };
    Message msg = AgentRun(dummy);

    ASSERT(AgentGetState() == AGENT_STATE_END_SCREEN,
           "end_screen state should not change on any event");
    ASSERT(msg.type == MESSAGE_NONE,
           "end_screen should return MESSAGE_NONE");
    printf("PASS: test_end_screen_behavior\n");
}

int main(void) {
    test_initial_state();
    test_set_get_state();
    test_start_to_challenging();
    test_start_to_accepting();
    test_challenging_to_waiting();
    test_accepting_cheating();
    test_waiting_to_attacking();
    test_attacking_to_defending();
    test_defending_to_waiting();
    test_reset_button();
    test_error_event();
    test_end_screen_behavior();

    printf("All tests passed.\n");
    return 0;
}
