/*
 * button.c
 *
 *  Created on: Apr 15, 2025
 *      Author: mars-polaire
 */

#include "button.h"
#include "stm32l4xx_hal.h"
#include "main.h"
/* Joystick button configuration  */
static BUTTON joystick[5] = {
    {0, 0, BTN_CENTER_GPIO_Port, BTN_CENTER_Pin},   // Center button
    {0, 0, BTN_BOTTOM_GPIO_Port, BTN_BOTTOM_Pin},   // Down direction
    {0, 0, BTN_RIGHT_GPIO_Port,  BTN_RIGHT_Pin},    // Right direction
    {0, 0, BTN_TOP_GPIO_Port,    BTN_TOP_Pin},      // Up direction
    {0, 0, BTN_LEFT_GPIO_Port,   BTN_LEFT_Pin}      // Left direction
};

/* Returns current physical state of a button (1 = pressed, 0 = released) */
int BUTTON_Get_Value(DIRECTION direction) {
    return joystick[direction].isOn;
}

/* Returns 1 if button was newly pressed since last update  */
int BUTTON_Get_Pressed(DIRECTION direction) {
    return joystick[direction].hasBeenPressed;
}

/* Updates button states */
void BUTTON_Update() {
    // 1. Snapshot current GPIO states for all buttons
    int currentStates[5];
    for (int i = 0; i < 5; i++) {
        currentStates[i] = HAL_GPIO_ReadPin(joystick[i].port, joystick[i].pinNumber);
    }

    // 2. Detect rising edges (0->1 transitions) and update states
    for (int i = 0; i < 5; i++) {
        // hasBeenPressed = (was OFF) AND (is now ON)
        joystick[i].hasBeenPressed = (!joystick[i].isOn) && (currentStates[i]);

        // Update current state for next detection cycle
        joystick[i].isOn = currentStates[i];
    }
}
