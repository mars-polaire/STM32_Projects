/*
 * encoder.h
 *
 *  Created on: Apr 16, 2025
 *      Author: mars-polaire
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_
#include <stdint.h>
#include "stm32l4xx_hal.h"
#include "tim.h"

typedef struct encoder {
    TIM_HandleTypeDef *htim;
    int32_t max_value;
    int32_t min_value;
} ENCODER;

void encoder_init(TIM_HandleTypeDef *htim_param, int32_t min, int32_t max);
int32_t encoder_read();

static ENCODER encoder;



#endif /* INC_ENCODER_H_ */
