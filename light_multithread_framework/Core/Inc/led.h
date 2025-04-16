/*
 * led.h
 *
 *  Created on: Apr 15, 2025
 *      Author: huawei
 */

#ifndef INC_LED_H_
#define INC_LED_H_

typedef struct led {
	int isOn;
    GPIO_TypeDef* port;
    uint16_t pinNumber;
}LED;
void LED_Set_Value_With_Int(int value);
void LED_Set_Value_With_Array(int value[8]);
int LED_Get_Value();
void LED_Update();
void LED_Test_All();

#endif /* INC_LED_H_ */
