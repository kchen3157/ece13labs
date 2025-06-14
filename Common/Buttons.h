#ifndef BUTTONS_H
#define BUTTONS_H
/**
 * @file  Buttons.h
 *
 * This library provides an interface to the 4 pushbuttons on the UCSC Nucleo IO
 * shield for the Nucleo development kit.
 *
 * This library relies on continuously polling the pins connected to the 
 * pushbuttons. It then provides an event-based interface for use. The 
 * resultant output are either UpEvents or DownEvents corresponding to 
 * whether the button has been pushed-down or released.
 *
 * Be aware that the ButtonsInit() function exists for configuring the 
 * appropriate pins on the STM32 processor and must be done before 
 * ButtonsCheckEvents() will work.
 *
 * @date  11 Nov 2024
 */
#include <stdint.h>

// We rely on this file to define various macros for working with the hardware
// buttons.
#include "BOARD.h"

// BTN4 D2 ; BTN3 C12 ; BTN2 C5 ; BTN1 C4
#define BUTTON_STATES() ( ((GPIOC->IDR & 0x30) >> 4) | ((GPIOC->IDR & 0x1000) >> 10) | ((GPIOD->IDR & 0x4) << 1) )

enum ButtonStateFlags {
    BUTTON_STATE_1 = 0x1,
    BUTTON_STATE_2 = 0x2,
    BUTTON_STATE_3 = 0x4,
    BUTTON_STATE_4 = 0x8
};

/**
 * Specify the minimum length of time between button events. This means that 
 * once ButtonsCheckEvents() returns an event for a particular button, no 
 * events for that button will be called until ButtonsCheckEvents() has been 
 * called 4 more times.
 */
#define BUTTONS_DEBOUNCE_PERIOD 4

/**
 * This enum{} lists all of the possible button events that could occur. Each 
 * event constants were chosen so that multiple button events can be recorded 
 * in a single call to ButtonsCheckEvents(). 
 *
 * All possible event flags will also fit into a char datatype.  This is to 
 * handle the rare situation where two buttons change state simultaneously (or
 * at least, within the frequency of the timer interrupt).  So, a single char 
 * could indicate that button 1 was released at the same time that while 
 * button 2 was pressed with (BUTTON_EVENT_1UP | BUTTON_EVENT_2DOWN).
 */
typedef enum {
    BUTTON_EVENT_NONE = 0x00,
    BUTTON_EVENT_1UP = 0x01,
    BUTTON_EVENT_1DOWN = 0x02,
    BUTTON_EVENT_2UP = 0x04,
    BUTTON_EVENT_2DOWN = 0x08,
    BUTTON_EVENT_3UP = 0x10,
    BUTTON_EVENT_3DOWN = 0x20,
    BUTTON_EVENT_4UP = 0x40,
    BUTTON_EVENT_4DOWN = 0x80
} ButtonEventFlags;

/**
 * This function initializes the proper pins such that the buttons 1-4 may be 
 * used.
 */
void Buttons_Init(void);

/** Buttons_End()
 */
uint8_t Buttons_End(void);

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
uint8_t Buttons_CheckEvents(void);

#endif // BUTTONS_H
