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
// Configs
#define LONG_PRESS_MS               500         // Length of long press (ms)
#define OVEN_TEMP_MIN               300         // Minimum oven temp
#define OVEN_TIME_MIN               1           // Minimum cook time (sec)
#define OVEN_TEMP_MAX               555         // Maximum oven temp
#define OVEN_TIME_MAX               256         // Maximum cook time (sec)
#define OVEN_TOAST_TEMP             500         // Constant temperature of toast cooking
#define COOK_TIME_FREQ              1           // Frequency of cook timer countdown (Hz)
#define ALERT_FREQ                  2           // Frequency of cooking done ALERT (Hz)

#define INIT_STATE                  SETUP       // Initial state upon startup
#define INIT_COOK_MODE              BAKE        // Initial cook mode set upon startup
#define INIT_SETTING_COOK_TIME      1           // Initial cook time set upon startup
#define INIT_SETTING_TEMP           350         // Initial temp set upon startup
#define INIT_SETTING_SEL            TIME        // Initial setting selection set upon startup
#define INIT_COOK_TIME_LEFT         1           // Initial cook time left value
#define INIT_BUTTON_HOLD_TIME       0           // Initial button hold counter value

// System Configs
#define OLED_BUFFER_SIZE            100         // Size of the OLED buffer for updates
#define NUM_LEDS                    8           // Number of LEDs for use in progress bar
#define ADC_WINDOW_SIZE             60          // Size of window (lo->hi) of ADC sensitivity
#define ADC_MAX_READING             4095        // Maximum reading of ADC
#define ADC_MIN_READING             0           // Minimum reading of ADC

// UI Character Elements
#define BAKE_UI                     "BAKE"
#define TOAST_UI                    "TOAST"
#define BROIL_UI                    "BROIL"
#define ERROR_UI                    "ERROR"
#define SEL_UI                      '>'
#define NOT_SEL_UI                  ' '

// Miscellaneous Constants
#define COOK_TIME_TICK_PERIOD       (TIM4_DEFAULT_FREQ_HZ / COOK_TIME_FREQ)
#define ALERT_TICK_PERIOD           (TIM4_DEFAULT_FREQ_HZ / ALERT_FREQ)   
#define ADC_TEMP_RES                (OVEN_TEMP_MAX - OVEN_TEMP_MIN)
#define ADC_TIME_RES                (OVEN_TIME_MAX - OVEN_TIME_MIN)
#define SEC_PER_MIN                 60

// **** Set any local typedefs here ****
typedef enum
{
    SETUP,
    SELECTOR_CHANGE_PENDING,
    COOKING,
    RESET_PENDING,
    ALERT
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
    OvenState state;                  // Main toaster state
    OvenCookMode cook_mode;           // Which cook mode is selected
    OvenSettingSelect setting_select; // Which setting is selected for configuration
    uint16_t setting_cook_time;       // The set cook time in seconds
    uint16_t setting_temperature;     // The set cook temperature in Fahrenheit (Range: 300-555)
    uint16_t cook_time_left;          // Cook time left in seconds (Range: 1-256)
    uint16_t button_hold_time;        // Time button was held in milliseconds
} OvenData;

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

// **** Define any module-level, global, or external variables here ****
static volatile OvenData oven;
static volatile struct Timer systick = {.event = FALSE, .timeRemaining = 0};
static volatile struct AdcResult AdcResult = {.event = FALSE, .value = 1};
static volatile uint16_t cooking_ticks = 0;
static volatile uint16_t alert_ticks = 0;

// **** Put any helper functions here ****
void updateOvenOLED(void); 
void runOvenSM(void);

int main(void)
{
    BOARD_Init();
    Buttons_Init();
    LEDs_Init();
    Timers_Init();
    ADC_Init(ADC_CONTINUOUS_WATCHDOG);
    OLED_Init();
    ADC_Start();

    printf(
        "Welcome to CRUZID's Lab08 (Toaster Oven)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__);

    // Initialize state machine, display
    oven = (OvenData) {
        .state = INIT_STATE,
        .cook_mode = INIT_COOK_MODE,
        .button_hold_time = INIT_BUTTON_HOLD_TIME,
        .setting_cook_time = INIT_SETTING_COOK_TIME,
        .cook_time_left = INIT_COOK_TIME_LEFT,
        .setting_temperature = INIT_SETTING_TEMP,
        .setting_select = INIT_SETTING_SEL
    };
    updateOvenOLED();

    while (TRUE)
    {
        // Main system ticking
        if (systick.event == TRUE)
        {
            systick.event = FALSE;
            runOvenSM();
        }
    }

    BOARD_End();
    while (TRUE)
        ;
}

void runOvenSM(void)
{
    uint8_t buttonEvents;
    switch (oven.state)
    {
        case SETUP:
        {
            //********** Handle Button Events **********
            buttonEvents = Buttons_CheckEvents();
            if (buttonEvents & BUTTON_EVENT_3DOWN)
            {
                oven.button_hold_time = 0;
                oven.state = SELECTOR_CHANGE_PENDING;
            }
            else if (buttonEvents & BUTTON_EVENT_4DOWN)
            {
                oven.cook_time_left = oven.setting_cook_time;
                oven.state = COOKING;
            }

            //********** Handle ADC Events **********
            if (AdcResult.event)
            {
                AdcResult.event = FALSE;
                if (oven.setting_select == TIME || oven.cook_mode == BROIL || oven.cook_mode == TOAST)
                {
                    oven.setting_cook_time = ((AdcResult.value * ADC_TIME_RES) / ADC_MAX_READING) + 1;
                    updateOvenOLED();
                }
                else if (oven.setting_select == TEMP)
                {
                    oven.setting_temperature = ((AdcResult.value * ADC_TEMP_RES) / ADC_MAX_READING) + OVEN_TEMP_MIN;
                    updateOvenOLED();
                }
            }

            break;
        }
        case SELECTOR_CHANGE_PENDING:
        {
            if (oven.button_hold_time > LONG_PRESS_MS) // Rotate to next mode if long press
            {
                switch (oven.cook_mode)
                {
                    case BROIL:
                        oven.cook_mode = BAKE;
                        break;
                    case BAKE:
                        oven.cook_mode = TOAST;
                        break;
                    case TOAST:
                    default:
                        oven.setting_temperature = OVEN_TOAST_TEMP;
                        oven.cook_mode = BROIL;
                }
                
                updateOvenOLED();
                oven.state = SETUP;
            }
            else if (Buttons_CheckEvents() & BUTTON_EVENT_3UP) // Otherwise, next setting selection
            {
                if (oven.cook_mode == BAKE)
                {
                    oven.setting_select = (oven.setting_select == TIME ? TEMP : TIME);
                }

                updateOvenOLED();
                oven.state = SETUP;
            }
            
            oven.button_hold_time++;
            break;
        }
        case COOKING:
        {
            //********** Handle Button Events **********
            if (Buttons_CheckEvents() & BUTTON_EVENT_4DOWN)
            {
                oven.button_hold_time = 0;
                oven.state = RESET_PENDING;
            }

            //********** Handle Default Countbar **********
            cooking_ticks++;
            if (cooking_ticks >= COOK_TIME_TICK_PERIOD)
            {
                cooking_ticks = 0;

                // Light bar (rounds up according to percentage of time left)
                uint8_t num_leds_on = (oven.setting_cook_time > 0) ? 
                    (((oven.cook_time_left * NUM_LEDS) / oven.setting_cook_time) + 1) : 0;
                uint8_t prog_bar = (oven.cook_time_left > 0) ? ((0b1 << num_leds_on) - 1) : 0;

                LEDs_Set(prog_bar);

                if (oven.cook_time_left <= 0)
                {
                    oven.state = ALERT;
                    updateOvenOLED();
                }
                else
                {
                    updateOvenOLED();
                    oven.cook_time_left--;
                }
                
            }
            break;
        }
        case RESET_PENDING:
        {
            if (oven.button_hold_time > LONG_PRESS_MS) // Reset if long press
            {
                oven.state = SETUP;
                updateOvenOLED();
                LEDs_Set(0);
            }
            else if (Buttons_CheckEvents() & BUTTON_EVENT_4UP) // Otherwise, return and do nothing
            { 
                oven.state = COOKING;
            }
            oven.button_hold_time++;
            break;
        }
        case ALERT:
        {
            //********** Handle Button Events **********
            if (Buttons_CheckEvents() == BUTTON_EVENT_4DOWN)
            {
                oven.state = SETUP;
                updateOvenOLED();
            }

            //********** Handle Alert Display Update **********
            alert_ticks++;
            if (alert_ticks >= ALERT_TICK_PERIOD)
            {
                alert_ticks = 0;
                updateOvenOLED();
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void updateOvenOLED(void)
{
    char oled_buffer[OLED_BUFFER_SIZE];
    char *cook_mode_ui;

    if (oven.state == ALERT)
    {
        OLED_Clear((OLED_GetPixel(0, 0) == OLED_COLOR_BLACK) ? OLED_COLOR_WHITE : OLED_COLOR_BLACK);
        OLED_Update();
        return;
    }

    OLED_Clear(OLED_COLOR_BLACK);

    char time_sel_ui = (oven.setting_select == TIME) ? SEL_UI : NOT_SEL_UI;
    char temp_sel_ui = (oven.setting_select == TIME) ? NOT_SEL_UI : SEL_UI;

    uint8_t time_min = (oven.state == COOKING) ? 
        (oven.cook_time_left / SEC_PER_MIN) : (oven.setting_cook_time / SEC_PER_MIN);
    uint8_t time_sec = (oven.state == COOKING) ? 
        (oven.cook_time_left % SEC_PER_MIN) : (oven.setting_cook_time % SEC_PER_MIN);

    // Oven cook mode display
    switch (oven.cook_mode)
    {
        case BAKE:
            cook_mode_ui = BAKE_UI;
            break;
        case BROIL:
            cook_mode_ui = BROIL_UI;
            break;
        case TOAST:
            cook_mode_ui = TOAST_UI;
            break;
        default:
            cook_mode_ui = ERROR_UI;
            break;
    }

    // Load ui data into buffer
    if (oven.state == COOKING)
    {
        if (oven.cook_mode == BAKE)
        {
            sprintf(oled_buffer, "|\x01\x01\x01\x01\x01| MODE: %s\n|     | %cTIME: %d:%02d\n|     | %cTEMP: %d\xF8\n|\x03\x03\x03\x03\x03|",
                    cook_mode_ui, time_sel_ui, time_min, time_sec, temp_sel_ui, oven.setting_temperature);
        }
        else if (oven.cook_mode == BROIL)
        {
            sprintf(oled_buffer, "|\x01\x01\x01\x01\x01| MODE: %s\n|     | TIME: %d:%02d\n|     | TEMP: %d\xF8\n|\x04\x04\x04\x04\x04|",
                    cook_mode_ui, time_min, time_sec, oven.setting_temperature);
        }
        else if (oven.cook_mode == TOAST)
        {
            sprintf(oled_buffer, "|\x02\x02\x02\x02\x02| MODE: %s\n|     | TIME: %d:%02d\n|     |\n|\x03\x03\x03\x03\x03|",
                    cook_mode_ui, time_min, time_sec);
        }
    }
    else
    {
        if (oven.cook_mode == TOAST)
        {
            sprintf(oled_buffer, "|\x02\x02\x02\x02\x02| MODE: %s\n|     | TIME: %d:%02d\n|     |\n|\x04\x04\x04\x04\x04|",
                    cook_mode_ui, time_min, time_sec);
        }
        else if (oven.cook_mode == BROIL)
        {
            sprintf(oled_buffer, "|\x02\x02\x02\x02\x02| MODE: %s\n|     | TIME: %d:%02d\n|     | TEMP: %d\xF8\n|\x04\x04\x04\x04\x04|",
                    cook_mode_ui, time_min, time_sec, oven.setting_temperature);
        }
        else if (oven.cook_mode == BAKE)
        {
            sprintf(oled_buffer, "|\x02\x02\x02\x02\x02| MODE: %s\n|     | %cTIME: %d:%02d\n|     | %cTEMP: %d\xF8\n|\x04\x04\x04\x04\x04|",
                    cook_mode_ui, time_sel_ui, time_min, time_sec, temp_sel_ui, oven.setting_temperature);
        }
    }

    OLED_DrawString(oled_buffer);
    OLED_Update();
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
    if (htim == &htim4) // This will be triggered every TIM4_DEFAULT_FREQ_HZ
    {
        systick.timeRemaining--;

        if (systick.timeRemaining <= 0)
        {
            systick.event = TRUE;

            // Poll buttons at 1000 Hz
            systick.timeRemaining = (1);
        }
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
        AdcResult.value = HAL_ADC_GetValue(&hadc1);

        if (AdcResult.value <= ADC_MIN_READING || AdcResult.value >= ADC_MAX_READING)
        {
            return;
        }

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
    }
}
