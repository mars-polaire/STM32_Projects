/*
 * led.c
 *
 *  Created on: Apr 15, 2025
 *      Author: mars-polaire
 */
#include "led.h"
#include "main.h"
#include "stm32l4xx_hal.h"

#define LED_BAR_SIZE 8   // Number of LEDs in the bar


static LED led_bar[LED_BAR_SIZE] = {
    {0, LED_0_GPIO_Port, LED_0_Pin},  // LED 0
    {0, LED_1_GPIO_Port, LED_1_Pin},  // LED 1
    {0, LED_2_GPIO_Port, LED_2_Pin},  // LED 2
    {0, LED_3_GPIO_Port, LED_3_Pin},  // LED 3
    {0, LED_4_GPIO_Port, LED_4_Pin},  // LED 4
    {0, LED_5_GPIO_Port, LED_5_Pin},  // LED 5
    {0, LED_6_GPIO_Port, LED_6_Pin},  // LED 6
    {0, LED_7_GPIO_Port, LED_7_Pin}   // LED 7
};


void LED_Set_Value_With_Int(int value) {
    for (int i = 0; i < LED_BAR_SIZE; i++) {
        // Extract bit i and assign to LED state
        led_bar[i].isOn = (value >> i) & 1;
    }
}

/* Sets LED states using an array (direct per-LED control)
   Array format: [LED0_state, LED1_state, ...] */
void LED_Set_Value_With_Array(int value[LED_BAR_SIZE]) {
    for (int i = 0; i < LED_BAR_SIZE; i++) {

        led_bar[i].isOn = value[i] & 1;
    }
}


int LED_Get_Value() {
    int toReturn = 0;
    for (int i = 0; i < LED_BAR_SIZE; i++) {

        toReturn |= (led_bar[i].isOn) << i;
    }
    return toReturn;
}

/* Updates physical LED states based on internal values
    called after changing LED states to see hardware changes */
void LED_Update() {
    for (int i = 0; i < LED_BAR_SIZE; i++) {
        // Write to GPIO using HAL library
        HAL_GPIO_WritePin(
            led_bar[i].port,          // GPIO port
            led_bar[i].pin,           // GPIO pin
            led_bar[i].isOn ?         // set/reset based on state
                GPIO_PIN_SET :
                GPIO_PIN_RESET
        );
    }
}

/* Test function: Lights all LEDs temporarily */
void LED_Test_All() {
    LED_Set_Value_With_Int(0xFF);  // 0xFF = 0b11111111 (all LEDs on)
    LED_Update();                   // Apply to hardware

}

