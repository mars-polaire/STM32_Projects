/*
 * button.c
 *
 *  Created on: Apr 16, 2025
 *      Author: mars-polaire
 */
#include "stm32l4xx.h"
#include "stm32l476xx.h"
#include "button.h"
#include "stm32l4xx_hal.h"

int BUTTON_GetBlueLevel(void) {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_SET ? 1 : 0;
}

void BUTTON_Enable(void) {
    // (bit 2 of RCC_AHB2ENR)
    *((volatile uint32_t *)0x4002104C) |= (1 << 2);
}


void BUTTON_Config(void) {


    // (00 in MODER)
    GPIOC->MODER &= ~0x0C000000;

    // (01 in PUPDR)
    GPIOC->PUPDR &= ~0x08000000;
    GPIOC->PUPDR |=  0x04000000;

}
