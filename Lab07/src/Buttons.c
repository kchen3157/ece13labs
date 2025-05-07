/**
 * @file        Buttons.c
 *
 * @author      Kyle Chen
 *
 * @date        2025-05-06
 */

// **** Include libraries here ****
// Standard libraries.

// Course libraries.
#include "Buttons.h"




// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
static volatile uint8_t debounceCounter[4] = {0, 0, 0, 0};
static volatile uint8_t savedButtonState = 0x00;

// **** Declare function prototypes ****

void Buttons_Init(void)
{
    return;
}


uint8_t Buttons_End(void)
{
    return 0;
}

/**
 * ButtonsCheckEvents function checks the current button states and returns
 * any events that have occured since its last call.  This function should be
 * called repeatedly in a Timer ISR, though it can be called in main() during
 * testing.
 *
 * In normal use, this function should only be used after ButtonsInit().
 *
 * This function should assume that the buttons start in an off state with value
 * 0. Therefore if no buttons are pressed when ButtonsCheckEvents() is first
 * called, BUTTONS_EVENT_NONE should be returned.
 *
 * @return  Each bit of the return value corresponds to one ButtonEvent flag,
 *          as described in Buttons.h.  If no events are detected,
 *          BUTTONS_EVENT_NONE is returned.
 *
 * Note that more than one event can occur simultaneously, though this
 * situation is rare. To handle this, the output should be a bitwise OR of
 * all applicable event flags.  For example, if button 1 was released at the
 * same time that button 2 was pressed, this function should return
 * (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN).
 */
uint8_t Buttons_CheckEvents(void)
{
    uint8_t buttonEvents = BUTTON_EVENT_NONE;

#ifdef STM32F4
    enum ButtonStateFlags currentButtonState = ~BUTTON_STATES();

    if ((currentButtonState & BUTTON_STATE_1) != (savedButtonState & BUTTON_STATE_1) )
    {
        if ((debounceCounter[0] < BUTTONS_DEBOUNCE_PERIOD))
        {
            debounceCounter[0]++;
        }
        else
        {
            buttonEvents |= (currentButtonState & BUTTON_STATE_1) ? BUTTON_EVENT_1DOWN : BUTTON_EVENT_1UP;
            savedButtonState ^= BUTTON_STATE_1;
            debounceCounter[0] = 0;
        }
    }
    else
    {
        debounceCounter[0] = 0;
    }

    if ((currentButtonState & BUTTON_STATE_2) != (savedButtonState & BUTTON_STATE_2) )
    {
        if ((debounceCounter[1] < BUTTONS_DEBOUNCE_PERIOD))
        {
            debounceCounter[1]++;
        }
        else
        {
            buttonEvents |= (currentButtonState & BUTTON_STATE_2) ? BUTTON_EVENT_2DOWN : BUTTON_EVENT_2UP;
            savedButtonState ^= BUTTON_STATE_2;
            debounceCounter[1] = 0;
        }
    }
    else
    {
        debounceCounter[1] = 0;
    }

    if ((currentButtonState & BUTTON_STATE_3) != (savedButtonState & BUTTON_STATE_3) )
    {
        if ((debounceCounter[2] < BUTTONS_DEBOUNCE_PERIOD))
        {
            debounceCounter[2]++;
        }
        else
        {
            buttonEvents |= (currentButtonState & BUTTON_STATE_3) ? BUTTON_EVENT_3DOWN : BUTTON_EVENT_3UP;
            savedButtonState ^= BUTTON_STATE_3;
            debounceCounter[2] = 0;
        }
    }
    else
    {
        debounceCounter[2] = 0;
    }

    if ((currentButtonState & BUTTON_STATE_4) != (savedButtonState & BUTTON_STATE_4) )
    {
        if ((debounceCounter[3] < BUTTONS_DEBOUNCE_PERIOD))
        {
            debounceCounter[3]++;
        }
        else
        {
            buttonEvents |= (currentButtonState & BUTTON_STATE_4) ? BUTTON_EVENT_4DOWN : BUTTON_EVENT_4UP;
            savedButtonState ^= BUTTON_STATE_4;
            debounceCounter[3] = 0;
        }
    }
    else
    {
        debounceCounter[3] = 0;
    }

    // savedButtonState = currentButtonState;
#endif /*  STM32F4 */

    return buttonEvents;
    
}
