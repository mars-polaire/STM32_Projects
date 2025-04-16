/*
 * motor.h
 *
 *  Created on: Apr 16, 2025
 *      Author: mars-polaire
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_
#include "main.h"
#include "tim.h"

typedef struct stepperMotor{
	TIM_HandleTypeDef * htim_pwm;
	uint32_t pwm_channel_number;
	GPIO_TypeDef * gpio_direction;
	uint16_t gpio_direction_pin;
	GPIO_TypeDef * gpio_ms1;
	uint16_t gpio_ms1_pin;
	GPIO_TypeDef * gpio_ms2;
	uint16_t gpio_ms2_pin;
	GPIO_TypeDef * gpio_enable;
	uint16_t gpio_enable_pin;
	uint8_t speed;
	uint32_t step_target;
	uint32_t step_actual;
}STEPPERMOTOR;

void launch_stepper(int speed);

void init_stepper(TIM_HandleTypeDef * htim_pwm_p, uint32_t pwm_channel_number_p,
		GPIO_TypeDef * gpio_direction_p, uint16_t gpio_direction_pin_p,
		GPIO_TypeDef * gpio_ms1_p, uint16_t gpio_ms1_pin_p,
		GPIO_TypeDef * gpio_ms2_p, uint16_t gpio_ms2_pin_p,
		GPIO_TypeDef * gpio_enable_p, uint16_t gpio_enable_pin_p);


#endif /* INC_MOTOR_H_ */
