/**
 * @file    bounce_ec_template.c
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
#include <Adc.h>
#include <Buttons.h>
#include <Timers.h>
#include <Leds.h>
#include <Oled.h>

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

#define ADC_WINDOW_SIZE 50
#define ADC_MAX_READING 4095
#define ADC_MIN_READING 0
#define MIN_INTERVAL 50
#define MAX_INTERVAL 1000

// **** Declare any datatypes here ****
struct AdcResult
{
    uint8_t event;
    uint16_t value;
};

struct Timer
{
    uint8_t event;
    int16_t timeRemaining;
};

// **** Define global, module-level, or external variables here ****
static volatile struct AdcResult AdcResult;
static volatile struct Timer TimerA = {.event = FALSE, .timeRemaining = 0};
static volatile struct Timer TimerB = {.event = FALSE, .timeRemaining = 0};
static volatile ButtonEventFlags buttonEvents;

static volatile uint8_t direction = 0; // 0 = LD 1->8 (bit 7 -> 0), 1 = LD 8->1 (bit 0 -> 7)
static volatile uint8_t bounce_led_enable = TRUE;

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
    LEDs_Init();
    Buttons_Init();
    OLED_Init();
    Timers_Init();
    ADC_Init(ADC_CONTINUOUS_WATCHDOG); // See the typedef of Adc_Modes_t in Adc.h for the ADC configuration options.
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 6 (extra credit!!)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);
    ADC_Start();

    LEDs_Set(LED_1);

    while (TRUE)
    {
        //******** Bouncing LED logic ********
        if (TimerA.event)
        {
            uint8_t led_state = LEDs_Get();

            // Change direction when reach end
            if (led_state & LED_8)
            {
                direction = 1;
            }
            else if (led_state & LED_1)
            {
                direction = 0;
            }

            // Stop if switch says so
            if (bounce_led_enable)
            {
                LEDs_Set(direction ? (led_state << 1) : (led_state >> 1));
            }

            TimerA.event = FALSE;
        }

        //******** Bouncing LED Pause Switch logic ********
        if (TimerB.event)
        {
            TimerB.event = FALSE;
            if (!SW1_STATE())
            {
                // Stop LED bounce on button down
                if (buttonEvents & (BUTTON_EVENT_1DOWN | BUTTON_EVENT_2DOWN | BUTTON_EVENT_3DOWN | BUTTON_EVENT_4DOWN))
                {
                    bounce_led_enable = !bounce_led_enable;
                }
            }
            else
            {
                // Stop LED bounce on button up
                if (buttonEvents & (BUTTON_EVENT_1UP | BUTTON_EVENT_2UP | BUTTON_EVENT_3UP | BUTTON_EVENT_4UP))
                {
                    bounce_led_enable = !bounce_led_enable;
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

        TimerA.timeRemaining--;

        if (TimerA.timeRemaining <= 0)
        {
            TimerA.event = TRUE;

            // Set timer period using ADC reading, scaled to go between MAX_INTERVAL and MIN_INTERVAL
            TimerA.timeRemaining = (MIN_INTERVAL + ((MAX_INTERVAL - MIN_INTERVAL) * (ADC_MAX_READING - AdcResult.value)) / ADC_MAX_READING) / 10;
        }

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

        TimerB.timeRemaining--;

        if (TimerB.timeRemaining <= 0)
        {
            TimerB.event = TRUE;

            buttonEvents = Buttons_CheckEvents();

            // Poll button at frequency of 1000Hz
            TimerB.timeRemaining = (1);
        }

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}

/**
 * This is the interrupt for the ADC1 peripheral. It will trigger whenever a new
 * ADC reading is available in the ADC when you are configured as
 * ADC_CONTINUOUS_INTERRUPT or ADC_SINGLE_SHOT_INTERRUPT.
 *
 * It should not be called, and should communicate with main code only by using
 * module-level variables.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1)
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
}

/**
 * This is the interrupt for the ADC1 peripheral's analog watchdog. It will trigger
 * whenever a new ADC reading is available that is outside of the high/low thresholds
 * that you set in ADC_Watchdog_Config(). This interrupt is only active when the ADC
 * is configured as ADC_CONTINUOUS_WATCHDOG or ADC_SINGLE_SHOT_WATCHDOG.
 *
 * It should not be called, and should communicate with main code only by using
 * module-level variables.
 */
void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc1)
    {
        /***************************************************************************
         * Your code goes in between this comment and the following one with
         * asterisks.
         **************************************************************************/

         AdcResult.value = HAL_ADC_GetValue(&hadc1);

         //******Config ADC watchdog with new window values based upon new result******
 
         int16_t lim_upper = (int16_t)AdcResult.value + (ADC_WINDOW_SIZE / 2);
         int16_t lim_lower = (int16_t)AdcResult.value - (ADC_WINDOW_SIZE / 2);
 
         // Create deadzone; do not let upper/lower limit surpass the max/min
         lim_upper = (lim_upper > ADC_MAX_READING) ? (ADC_MAX_READING - 1) : lim_upper;
         lim_upper = (lim_upper < ADC_MIN_READING) ? (ADC_MIN_READING + 1) : lim_upper;
         lim_lower = (lim_lower > ADC_MAX_READING) ? (ADC_MAX_READING - 1) : lim_lower;
         lim_lower = (lim_lower < ADC_MIN_READING) ? (ADC_MIN_READING + 1) : lim_lower;
 
         ADC_Watchdog_Config((uint16_t)lim_upper, (uint16_t)lim_lower);
 
         // Broadcast ADC has new result
         AdcResult.event = TRUE;

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}
