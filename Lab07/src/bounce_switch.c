/**
 * @file    bounce_switch.c
 *
 * @author  Kyle Chen
 *
 * @date    2025-05-06
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
#define LED_1 (0b1 << 7)
#define LED_2 (0b1 << 6)
#define LED_3 (0b1 << 5)
#define LED_4 (0b1 << 4)
#define LED_5 (0b1 << 3)
#define LED_6 (0b1 << 2)
#define LED_7 (0b1 << 1)
#define LED_8 (0b1 << 0)

#define TIMER_A_PERIOD 0.2
#define BASE_PERIOD_CHANGE 0.06
#define SW1_CHANGE (BASE_PERIOD_CHANGE * 1)
#define SW2_CHANGE (BASE_PERIOD_CHANGE * 2)

// **** Declare any datatypes here ****
struct Timer
{
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static volatile struct Timer TimerA = {.event = FALSE, .timeRemaining = 0};

static volatile uint8_t direction = 0; // 0 = LD 1->8 (bit 7 -> 0), 1 = LD 8->1 (bit 0 -> 7)

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
        "Welcome to CRUZID's Lab07, Part 2 (bounce_switch)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);

    LEDs_Set(LED_1);

    HAL_Delay(1000);

    while (TRUE)
    {
        if (TimerA.event)
        {
            uint8_t led_state = LEDs_Get();

            if (led_state & LED_8)
            {
                direction = 1;
            }
            else if (led_state & LED_1)
            {
                direction = 0;
            }

            LEDs_Set(direction ? (led_state << 1) : (led_state >> 1));
            TimerA.event = FALSE;
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

        if (TimerA.timeRemaining <= 0)
        {
            TimerA.event = TRUE;

            // Base period
            TimerA.timeRemaining = (TIMER_A_PERIOD * TIM4_DEFAULT_FREQ_HZ);

            // Binary period adjustment
            TimerA.timeRemaining -= (SW1_STATE()) ? (SW1_CHANGE * TIM4_DEFAULT_FREQ_HZ) : 0;
            TimerA.timeRemaining -= (SW2_STATE()) ? (SW2_CHANGE * TIM4_DEFAULT_FREQ_HZ) : 0;
        }

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}
