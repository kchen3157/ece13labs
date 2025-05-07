/**
 * @file        Leds.c
 *
 * This library provides an interface for controlling the LEDs on the UCSC
 * Nucleo I/O Shield development board.
 *
 * @author      Kyle Chen
 *
 * @date        2025-05-06
 */
// Standard libraries.
#include <stdio.h>
#include <stdlib.h>

// Course libraries.
#include <Leds.h>

/**
 * LEDs_Init() Initializes the LED bar by doing three things:
 *      1) Enables usage of the GPIO clocks for needed ports.
 *      2) Use the appropriate SFRs to set each LED pin to "output" mode.
 *      3) Use the appropriate SFRs to set each LED pin's output value to 0 (low
 *         voltage).
 * After calling LEDs_Init(), the other functions in this file can be used to
 * manipulate the LED bar.
 */
int8_t LEDs_Init(void)
{
    // Enable GPIO clocks for ports C and B.
#ifdef STM32F4
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    // Init GOIO output pins for LEDs.
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
#endif             /*  STM32F4 */
    LEDs_Set(0x0); // Reset LEDs.

    return SUCCESS;
}

/**
 * LEDs_Set() controls the output on the LED bar.  Input values are 8-bit
 * patterns, where each bit describes the desired state of the corresponding
 * LED. So, for example, LEDs_Set(0x80) should  leave the first LED on, and the
 * last 7 LEDs off. LEDs_Set(0x1F) should turn off the first three LEDs and turn
 * on the remaining five LEDs.
 *
 * @param newPattern:  An 8-bit value describing the desired output on the LED
 * bar.
 *
 * LEDs_Set should not change any LED pins to inputs.
 */
void LEDs_Set(uint8_t newPattern){
#ifdef STM32F4
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/

    GPIOC->BSRR |= ((0b1 << 7) & newPattern) ? (0b1 << 8) : (0b1 << (8 + 16)); // LD1 -> PC8
    GPIOC->BSRR |= ((0b1 << 6) & newPattern) ? (0b1 << 9) : (0b1 << (9 + 16)); // LD2 -> PC9
    GPIOC->BSRR |= ((0b1 << 5) & newPattern) ? (0b1 << 10) : (0b1 << (10 + 16)); // LD3 -> PC10
    GPIOC->BSRR |= ((0b1 << 4) & newPattern) ? (0b1 << 11) : (0b1 << (11 + 16)); // LD4 -> PC11

    GPIOB->BSRR |= ((0b1 << 3) & newPattern) ? (0b1 << 0) : (0b1 << (0 + 16)); // LD5 -> PB0
    GPIOB->BSRR |= ((0b1 << 2) & newPattern) ? (0b1 << 1) : (0b1 << (1 + 16)); // LD6 -> PB1
    GPIOB->BSRR |= ((0b1 << 1) & newPattern) ? (0b1 << 2) : (0b1 << (2 + 16)); // LD7 -> PB2
    GPIOB->BSRR |= ((0b1 << 0) & newPattern) ? (0b1 << 3) : (0b1 << (3 + 16)); // LD8 -> PB3


/***************************************************************************
 * Your code goes in between this comment and the preceding one with
 * asterisks.
 **************************************************************************/
#endif /*  STM32F4 */
}

/**
 * LEDs_Get() returns the current state of the LED bar.  Return values are 8-bit
 * patterns, where each bit describes the current state of the corresponding
 * LED. So, for example, if the LED bar's LED's are
 *
 * [ON OFF ON OFF   OFF ON OFF ON],
 *
 * LEDs_Get() should return 0xA5.
 *
 * @return  (uint8_t)   An 8-bit value describing the current output on the LED
 *                      bar.
 *
 * LEDs_Get() should not change the state of the LEDs, or any SFRs.
 */
uint8_t LEDs_Get(void)
{
    uint8_t ledState = 0x00;
#ifdef STM32F4
    /***************************************************************************
     * Your code goes in between this comment and the following one with
     * asterisks.
     **************************************************************************/

    ledState |= ((0b1 << 8) & GPIOC->ODR) ? (0b1 << 7) : 0; // LD1 -> PC8
    ledState |= ((0b1 << 9) & GPIOC->ODR) ? (0b1 << 6) : 0; // LD2 -> PC9
    ledState |= ((0b1 << 10) & GPIOC->ODR) ? (0b1 << 5) : 0; // LD3 -> PC10
    ledState |= ((0b1 << 11) & GPIOC->ODR) ? (0b1 << 4) : 0; // LD4 -> PC11

    ledState |= ((0b1 << 0) & GPIOB->ODR) ? (0b1 << 3) : 0; // LD5 -> PB0
    ledState |= ((0b1 << 1) & GPIOB->ODR) ? (0b1 << 2) : 0; // LD6 -> PB1
    ledState |= ((0b1 << 2) & GPIOB->ODR) ? (0b1 << 1) : 0; // LD7 -> PB2
    ledState |= ((0b1 << 3) & GPIOB->ODR) ? (0b1 << 0) : 0; // LD8 -> PB3

    /***************************************************************************
     * Your code goes in between this comment and the preceding one with
     * asterisks.
     **************************************************************************/
#endif /*  STM32F4 */
    return ledState;
}
