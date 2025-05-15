/**
 * @file        bounce_timers.c
 *
 * @author      Kyle Chen
 *
 * @date        2025-05-06
 */

// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course libraries.
#include <BOARD.h>
#include <Buttons.h>
#include <Timers.h>
#include <Leds.h>

// User libraries

// **** Set macros and preprocessor directives ****
// Period in seconds
#define TIMER_A_PERIOD 2
#define TIMER_B_PERIOD 3
#define TIMER_C_PERIOD 5

#define TIMER_A_LED (0b1 << 7)
#define TIMER_B_LED (0b1 << 6)
#define TIMER_C_LED (0b1 << 5)

// **** Declare any datatypes here ****
struct Timer
{
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static volatile struct Timer TimerA = {.event = FALSE, .timeRemaining = (TIMER_A_PERIOD * TIM4_DEFAULT_FREQ_HZ)},
                             TimerB = {.event = FALSE, .timeRemaining = (TIMER_B_PERIOD * TIM4_DEFAULT_FREQ_HZ)},
                             TimerC = {.event = FALSE, .timeRemaining = (TIMER_C_PERIOD * TIM4_DEFAULT_FREQ_HZ)}; // Set the initial event and timeRemaining for each timer here.

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
    Timers_Init();
    LEDs_Init();
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 1 (bouce_timers)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);
    while (1)
    {
        // TIMA -> LD1 (2 sec.)
        // TIMB -> LD2 (3 sec.)
        // TIMC -> LD3 (5 sec.)

        if (TimerA.event)
        {
            printf("A ");
            LEDs_Set(LEDs_Get() ^ TIMER_A_LED);
            TimerA.event = FALSE;
        }

        if (TimerB.event)
        {
            printf("B ");
            LEDs_Set(LEDs_Get() ^ TIMER_B_LED);
            TimerB.event = FALSE;
        }

        if (TimerC.event)
        {
            printf("C ");
            LEDs_Set(LEDs_Get() ^ TIMER_C_LED);
            TimerC.event = FALSE;
        }
    }
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
    BOARD_End();
    while (1)
        ;
}

/**
 * This is the interrupt for the TIM peripheral. It will trigger whenever a timer
 * ticks over from its period to 0.
 *
 * It should not be called, and should communicate with main code only by using
 * module-level variables.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim2) // This will be triggered every TIM2_DEFAULT_FREQ_HZ
    {
        /***************************************************************************
         * Your code goes in between this comment and the following one with
         * asterisks.
         **************************************************************************/

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
    else if (htim == &htim3) // This will be triggered every TIM3_DEFAULT_FREQ_HZ
    {
        /***************************************************************************
         * Your code goes in between this comment and the following one with
         * asterisks.
         **************************************************************************/

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
    else if (htim == &htim4) // This will be triggered every TIM4_DEFAULT_FREQ_HZ
    {
        /***************************************************************************
         * Your code goes in between this comment and the following one with
         * asterisks.
         **************************************************************************/

        TimerA.timeRemaining--;
        TimerB.timeRemaining--;
        TimerC.timeRemaining--;

        if (TimerA.timeRemaining <= 0)
        {
            TimerA.event = TRUE;
            TimerA.timeRemaining = (TIMER_A_PERIOD * TIM4_DEFAULT_FREQ_HZ);
        }

        if (TimerB.timeRemaining <= 0)
        {
            TimerB.event = TRUE;
            TimerB.timeRemaining = (TIMER_B_PERIOD * TIM4_DEFAULT_FREQ_HZ);
        }

        if (TimerC.timeRemaining <= 0)
        {
            TimerC.event = TRUE;
            TimerC.timeRemaining = (TIMER_C_PERIOD * TIM4_DEFAULT_FREQ_HZ);
        }

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}
