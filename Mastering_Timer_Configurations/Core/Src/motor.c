/*
 * Motor.c
 *
 *  Created on: Apr 16, 2025
 *      Author: mars-polaire
 */

#include "motor.h"
#include "main.h"
#include "tim.h"
#include <stdlib.h>
#include "stm32l4xx_hal.h"

static STEPPERMOTOR stepper_motor;

void init_stepper(
 TIM_HandleTypeDef * htim_pwm_p, uint32_t pwm_channel_number_p,
 GPIO_TypeDef * gpio_direction_p, uint16_t gpio_direction_pin_p,
 GPIO_TypeDef * gpio_ms1_p, uint16_t gpio_ms1_pin_p,
 GPIO_TypeDef * gpio_ms2_p, uint16_t gpio_ms2_pin_p,
 GPIO_TypeDef * gpio_enable_p, uint16_t gpio_enable_pin_p)
 {

 stepper_motor.htim_pwm=htim_pwm_p;
 stepper_motor.pwm_channel_number = pwm_channel_number_p;
 stepper_motor.gpio_direction = gpio_direction_p;
 stepper_motor.gpio_direction_pin = gpio_direction_pin_p;
 stepper_motor.gpio_ms1 = gpio_ms1_p;
 stepper_motor.gpio_ms1_pin = gpio_ms1_pin_p;
 stepper_motor.gpio_ms2 = gpio_ms2_p;
 stepper_motor.gpio_ms2_pin = gpio_ms2_pin_p;
 stepper_motor.gpio_enable = gpio_enable_p;
 stepper_motor.gpio_enable_pin = gpio_enable_pin_p;
 HAL_GPIO_WritePin(stepper_motor.gpio_direction, stepper_motor.gpio_direction_pin,0);
 HAL_GPIO_WritePin(stepper_motor.gpio_enable, stepper_motor.gpio_enable_pin,1);
 HAL_GPIO_WritePin(stepper_motor.gpio_ms1, stepper_motor.gpio_ms1_pin,0);
 HAL_GPIO_WritePin(stepper_motor.gpio_ms2, stepper_motor.gpio_ms2_pin,0);
 stepper_motor.htim_pwm->Instance->CCR1=stepper_motor.htim_pwm->Instance->ARR/2;
 HAL_TIM_PWM_Start(stepper_motor.htim_pwm,stepper_motor.pwm_channel_number);
 }
 void launch_stepper(int speed){
 int abs_speed_value = abs(speed);
 abs_speed_value = (abs_speed_value>8)?8:abs_speed_value;
 stepper_motor.speed=speed;
 const uint16_t period_counter_value[8]={1599,1399,1199,999,799,599,399,299};
 if (abs_speed_value==0){
 stepper_motor.htim_pwm->Instance->CCR1=0;
 }
 else{
	 HAL_GPIO_WritePin(stepper_motor.gpio_enable, stepper_motor.gpio_enable_pin,0);
	 HAL_GPIO_WritePin(stepper_motor.gpio_direction, stepper_motor.gpio_direction_pin,(speed>0)?1:0);
	 stepper_motor.htim_pwm->Instance->ARR=period_counter_value[abs_speed_value-1];
	 stepper_motor.htim_pwm->Instance->CCR1=stepper_motor.htim_pwm->Instance->ARR/2;
 }
}

float get_speed(){

 if (stepper_motor.speed==0) return 0;
 int32_t period_value = ((stepper_motor.htim_pwm->Instance->ARR+1)*80)/(stepper_motor.htim_pwm->Instance) ;
 int32_t one_turn = period_value * 1600;
 float speed = (((stepper_motor.speed>0)?1:-1)*(60 * 1000000))/one_turn;
 return speed;

}
