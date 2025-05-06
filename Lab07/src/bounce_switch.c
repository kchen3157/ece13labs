/**
 * @file    bounce_switch_template.c
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

// User libraries

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****
struct Timer {
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
    LEDs_Init();
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/
    printf(
        "Welcome to CRUZID's Lab07, Part 2 (bounce_switch)."
        "Compiled on %s %s.\n\r",
        __TIME__,
        __DATE__
    );
    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
    BOARD_End();
    while (1);
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
