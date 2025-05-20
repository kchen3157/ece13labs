/**
 * @file        Lab08_main.c
 *
 * @author      Kyle Chen
 *
 * @date        05-19-2025
 */
// **** Include libraries here ****
// Standard libraries.
#include <stdio.h>

// Course library.
#include <Adc.h>
#include <BOARD.h>
#include <Buttons.h>
#include <Leds.h>
#include <Oled.h>
#include <Timers.h>

// **** Set any macros or preprocessor directives here ****
#define BAKE_UI     "BAKE"
#define TOAST_UI    "TOAST"
#define BROIL_UI    "BROIL"
#define ERROR_UI    "ERROR"
#define SEL_UI      '>'
#define NOT_SEL_UI  ' '

#define DEFAULT_COOK_MODE   BAKE

// **** Set any local typedefs here ****
typedef enum
{
    SETUP,
    SELECTOR_CHANGE_PENDING,
    COOKING,
    RESET_PENDING
} OvenState;

typedef enum
{
    BAKE,
    TOAST,
    BROIL
} OvenCookMode;

typedef enum
{
    TIME,
    TEMP
} OvenSettingSelect;

typedef struct
{
    OvenState           state;                  // Main toaster state
    OvenCookMode        cook_mode;              // Which cook mode is selected
    OvenSettingSelect   setting_select;         // Which setting is selected for configuration
    uint16_t            setting_cook_time;      // The set cook time in seconds
    uint16_t            setting_temperature;    // The set cook temperature in Fahrenheit (Range: 300-555)
    uint16_t            cook_time_left;         // Cook time left in seconds (Range: 1-256)
    uint16_t            button_hold_time;       // Time button was held in milliseconds
} OvenData;

// **** Declare any datatypes here ****

// **** Define any module-level, global, or external variables here ****
static volatile OvenData oven;

// **** Put any helper functions here ****

/* This function will update your OLED to reflect the state. */
void updateOvenOLED(void)
{
    // Update OLED here.
    char oled_buffer[100];
    char* cook_mode_ui;
    char time_sel_ui;
    char temp_sel_ui;
    uint8_t time_min;
    uint8_t time_sec;

    if (oven.setting_select == TIME)
    {
        time_sel_ui = SEL_UI;
        temp_sel_ui = NOT_SEL_UI;
    }
    else
    {
        time_sel_ui = NOT_SEL_UI;
        temp_sel_ui = SEL_UI;
    }

    // Oven cook mode display
    if (oven.cook_mode == BAKE)
    {
        cook_mode_ui = BAKE_UI;
    }
    else if (oven.cook_mode == BROIL)
    {
        cook_mode_ui = BROIL_UI;
    }
    else if (oven.cook_mode == TOAST)
    {
        cook_mode_ui = TOAST_UI;
    }
    else
    {
        cook_mode_ui = ERROR_UI;
    }

    // Oven time
    if (oven.state == COOKING)
    {
        time_min = (uint8_t) (oven.cook_time_left / 60);
        time_sec = (uint8_t) (oven.cook_time_left % 60);
    }
    else
    {
        time_min = (uint8_t) (oven.setting_cook_time / 60);
        time_sec = (uint8_t) (oven.setting_cook_time % 60);
    }

    // Load ui data into buffer
    if (oven.state == COOKING && oven.cook_mode == BAKE)
    {
        sprintf(oled_buffer, "|\x01\x01\x01\x01\x01| MODE: %s\n|     | %cTIME: %d:%02d\n|     | %cTEMP: %d\xF8\n|\x03\x03\x03\x03\x03|", 
            cook_mode_ui, time_sel_ui, time_min, time_sec, temp_sel_ui, oven.setting_temperature);
    }
    else if (oven.state == COOKING && oven.cook_mode == BROIL)
    {
        sprintf(oled_buffer, "|\x01\x01\x01\x01\x01| MODE: %s\n|     | %cTIME: %d:%02d\n|     | %cTEMP: %d\xF8\n|\x04\x04\x04\x04\x04|", 
            cook_mode_ui, time_sel_ui, time_min, time_sec, temp_sel_ui, oven.setting_temperature);
    }
    else if (oven.state == COOKING && oven.cook_mode == TOAST)
    {
        sprintf(oled_buffer, "|\x02\x02\x02\x02\x02| MODE: %s\n|     | TIME: %d:%02d\n|     |\n|\x03\x03\x03\x03\x03|", 
            cook_mode_ui, time_min, time_sec);
    }
    else if (oven.cook_mode == TOAST)
    {
        sprintf(oled_buffer, "|\x02\x02\x02\x02\x02| MODE: %s\n|     | TIME: %d:%02d\n|     |\n|\x04\x04\x04\x04\x04|", 
            cook_mode_ui, time_min, time_sec);
    }
    else
    {
        sprintf(oled_buffer, "|\x02\x02\x02\x02\x02| MODE: %s\n|     | %cTIME: %d:%02d\n|     | %cTEMP: %d\xF8\n|\x04\x04\x04\x04\x04|", 
            cook_mode_ui, time_sel_ui, time_min, time_sec, temp_sel_ui, oven.setting_temperature);
    }

    OLED_DrawString(oled_buffer);
    OLED_Update();
}

/* This function will execute your state machine.
 * It should ONLY run if an event flag has been set.
 */
void runOvenSM(void)
{
    // Write your SM logic here.

    if (oven.state == SETUP)
        {
            if (Buttons_CheckEvents() == BUTTON_EVENT_3DOWN)
            {
                oven.state = SELECTOR_CHANGE_PENDING;
            }
        }


        if (oven.state == SELECTOR_CHANGE_PENDING)
        {
            
        }
}

int main()
{
    BOARD_Init();
    Buttons_Init();
    LEDs_Init();
    Timers_Init();
    ADC_Init(ADC_CONTINUOUS_WATCHDOG); // See the typedef of Adc_Modes_t in Adc.h for the ADC configuration options.
    OLED_Init();

    printf(
        "Welcome to CRUZID's Lab08 (Toaster Oven)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);

    // Initialize state machine (and anything else you need to init) here.
    oven.state = SETUP;
    oven.cook_mode = BAKE;
    oven.button_hold_time = 0;
    oven.setting_cook_time = 1;
    oven.cook_time_left = 1;
    oven.setting_temperature = 350;
    

    while (1)
    {
        // Add main loop code here:
        // check for events
        // on event, run runOvenSM()
        // clear event flags
        updateOvenOLED();
    }

    BOARD_End();
    while(1);
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

        /***************************************************************************
         * Your code goes in between this comment and the preceding one with
         * asterisks.
         **************************************************************************/
    }
}
