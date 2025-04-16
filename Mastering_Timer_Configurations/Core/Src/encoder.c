/*
 * encoder.c
 *
 *  Created on: Apr 16, 2025
 *      Author: mars-polaire
 */
#include "encoder.h"
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include"tim.h"


void encoder_init(TIM_HandleTypeDef *htim_param, int32_t min, int32_t max) {
    encoder.htim = htim_param;
    encoder.min_value = min;
    encoder.max_value = max;
    encoder.htim->Instance->CNT = 0;
    HAL_TIM_Encoder_Start(htim_param, TIM_CHANNEL_ALL);

}

int32_t encoder_read() {
    int32_t count = encoder.htim->Instance->CNT;


    if (count > encoder.max_value) {
        count = encoder.max_value;
        encoder.htim->Instance->CNT = encoder.max_value;
    } else if (count < encoder.min_value) {
        count = encoder.min_value;
        encoder.htim->Instance->CNT = encoder.min_value;
    }

    return count;
}

