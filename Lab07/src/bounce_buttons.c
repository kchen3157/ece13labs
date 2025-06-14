/**
 * @file    bounce_buttons_template.c
 *
 * @author
 *
 * @date
 */
// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course libraries.
#include <BOARD.h>
#include <Buttons.h>
#include <Timers.h>
#include <Leds.h>

// User libraries.

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Timer
{
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static volatile struct Timer TimerA = {.event = FALSE, .timeRemaining = 0};

static volatile ButtonEventFlags buttonEvents; // Filled in by the Timer's ISR. May contain multiple ButtonEventFlags events.

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
    Timers_Init();
    Buttons_Init();
    LEDs_Init();
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 5 (bounce_buttons)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);

    while (TRUE)
    {
        if (TimerA.event)
        {
            TimerA.event = FALSE;

            //! LEDs wired from MSB
            // BTN1 -> LED1/2 (0b11000000)
            // BTN2 -> LED3/4 (0b00110000)
            // BTN3 -> LED5/6 (0b00001100)
            // BTN4 -> LED7/8 (0b00000011)

            if (!SW1_STATE()) //* Set LEDs on Button Down
            {
                if (buttonEvents & BUTTON_EVENT_1DOWN)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 6));
                }
                if (buttonEvents & BUTTON_EVENT_2DOWN)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 4));
                }
                if (buttonEvents & BUTTON_EVENT_3DOWN)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 2));
                }
                if (buttonEvents & BUTTON_EVENT_4DOWN)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 0));
                }
            }
            else //* Set LEDs on Button Up
            {
                if (buttonEvents & BUTTON_EVENT_1UP)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 6));
                }
                if (buttonEvents & BUTTON_EVENT_2UP)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 4));
                }
                if (buttonEvents & BUTTON_EVENT_3UP)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 2));
                }
                if (buttonEvents & BUTTON_EVENT_4UP)
                {
                    LEDs_Set(LEDs_Get() ^ (0b11 << 0));
                }
            }

            buttonEvents = BUTTON_EVENT_NONE;
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

            buttonEvents = Buttons_CheckEvents();

            // 1 cycle equates to frequency of 1000 Hz
            TimerA.timeRemaining = (1);
        }
        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}
