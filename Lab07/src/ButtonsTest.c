/**
 * @file        ButtonsTest.c
 *
 * @author      Kyle Chen
 *
 * @date        2025-05-06
 */

// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>
#include <string.h>

// Course libraries.
#include <BOARD.h>
#include <Buttons.h>
#include <Timers.h>

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Timer
{
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static volatile struct Timer TimerA = {.event = FALSE, .timeRemaining = 0};

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
    Timers_Init();
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 4 (ButtonsTest). Compiled on %s %s.\n",
        __TIME__,
        __DATE__);

    printf("Please press some buttons!\n");

    while (1)
    {

        if (TimerA.event)
        {
            TimerA.event = FALSE;

            uint8_t buttonEvents = Buttons_CheckEvents();

            if (buttonEvents == BUTTON_EVENT_NONE)
            {
                continue;
            }

            char button1Events[5], button2Events[5], button3Events[5], button4Events[5];

            if (buttonEvents & BUTTON_EVENT_1UP)
            {
                strcpy(button1Events, " UP ");
            }
            else if (buttonEvents & BUTTON_EVENT_1DOWN)
            {
                strcpy(button1Events, "DOWN");
            }
            else
            {
                strcpy(button1Events, "----");
            }

            if (buttonEvents & BUTTON_EVENT_2UP)
            {
                strcpy(button2Events, " UP ");
            }
            else if (buttonEvents & BUTTON_EVENT_2DOWN)
            {
                strcpy(button2Events, "DOWN");
            }
            else
            {
                strcpy(button2Events, "----");
            }

            if (buttonEvents & BUTTON_EVENT_3UP)
            {
                strcpy(button3Events, " UP ");
            }
            else if (buttonEvents & BUTTON_EVENT_3DOWN)
            {
                strcpy(button3Events, "DOWN");
            }
            else
            {
                strcpy(button3Events, "----");
            }

            if (buttonEvents & BUTTON_EVENT_4UP)
            {
                strcpy(button4Events, " UP ");
            }
            else if (buttonEvents & BUTTON_EVENT_4DOWN)
            {
                strcpy(button4Events, "DOWN");
            }
            else
            {
                strcpy(button4Events, "----");
            }

            printf("EVENT: 4: %s, 3: %s, 2: %s, 1: %s\n", button4Events, button3Events, button2Events, button1Events);
        }
    }
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
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

        if (TimerA.timeRemaining <= 0)
        {
            TimerA.event = TRUE;

            // Base period
            TimerA.timeRemaining = (1);
        }
        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}
