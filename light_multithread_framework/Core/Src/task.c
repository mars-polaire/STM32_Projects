/*
 * task.c
 *
 *  Created on: Apr 15, 2025
 *      Author: mars-polaire
 */
#include "task.h"
#include <stdio.h>
#include "led.h"
#include "stm32l4xx_hal.h"
#include "button.h"
#include "ssd1315.h"
#include "fonts.h"
#include "main.h"

void taskLED() {
    int numero_motif = (HAL_GetTick() / globalDelayInMs) % (tableau_motif[index_tableau_motif]->size);
    int motif_value = tableau_motif[index_tableau_motif]->motif[numero_motif];
    LED_Set_Value_With_Int(motif_value);
    LED_Update();
}

void taskButton() {
    BUTTON_Update();

    if (BUTTON_Get_Pressed(CENTER)) {
        globalDelayInMs = (globalDelayInMs > 50) ? globalDelayInMs / 2 : 50;
        printf("Speed increased: %d ms\r\n", globalDelayInMs);
    }

    if (BUTTON_Get_Pressed(DOWN)) {
        globalDelayInMs = (globalDelayInMs < 3200) ? globalDelayInMs * 2 : 3200;
        printf("Speed decreased: %d ms\r\n", globalDelayInMs);
    }

    if (BUTTON_Get_Pressed(LEFT)) {
        index_tableau_motif = (index_tableau_motif + 1) % 3;
        printf("Pattern changed: %d\r\n", index_tableau_motif);
    }

    needDisplayRefresh = 1; // Trigger display refresh
}

void taskScreen(void) {
    // Initialize the screen and clear it with a black background
    ssd1315_Init();
    ssd1315_Clear(SSD1315_COLOR_BLACK);

    char buffer[16] = {0};

    // Display the speed information
    sprintf(buffer, "Speed: %d ms", globalDelayInMs);
    ssd1315_Draw_string(0, 0, buffer, &Font_7x10);

    // Display the current pattern
    sprintf(buffer, "Pattern: %s", tableau_motif[index_tableau_motif]->name);
    ssd1315_Draw_string(1, 0, buffer, &Font_7x10);

    // Refresh the screen to update the display
    ssd1315_Refresh();
}

