/**
 * @file    bounce_adc_template.c
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
#include <Oled.h>

// User libraries

// **** Set macros and preprocessor directives ****
#define ADC_WINDOW_SIZE 50
#define ADC_MAX_READING 4095
#define ADC_MIN_READING 0

// **** Declare any datatypes here ****
struct AdcResult
{
    uint8_t event;
    uint16_t value;
};

// **** Define global, module-level, or external variables here ****
static volatile struct AdcResult AdcResult;

// **** Declare function prototypes ****

int main(void)
{
    BOARD_Init();
    OLED_Init();
    ADC_Init(ADC_CONTINUOUS_WATCHDOG); // See the typedef of Adc_Modes_t in Adc.h for the ADC configuration options.
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 3 (bounce_adc)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);
    ADC_Start();

    while (TRUE)
    {
        if (AdcResult.event)
        {
            AdcResult.event = FALSE;

            char buffer[20];

            sprintf(buffer, "%d", AdcResult.value);

            OLED_Clear(OLED_COLOR_BLACK);
            OLED_DrawString(buffer);
            OLED_Update();
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

        int16_t lim_upper = (int16_t)AdcResult.value + (ADC_WINDOW_SIZE / 2);
        lim_upper = (lim_upper > ADC_MAX_READING) ? (ADC_MAX_READING - 1) : lim_upper;
        lim_upper = (lim_upper < ADC_MIN_READING) ? (ADC_MIN_READING + 1) : lim_upper;

        int16_t lim_lower = (int16_t)AdcResult.value - (ADC_WINDOW_SIZE / 2);
        lim_lower = (lim_lower > ADC_MAX_READING) ? (ADC_MAX_READING - 1) : lim_lower;
        lim_lower = (lim_lower < ADC_MIN_READING) ? (ADC_MIN_READING + 1) : lim_lower;

        ADC_Watchdog_Config((uint16_t)lim_upper, (uint16_t)lim_lower);

        AdcResult.event = TRUE;

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}
