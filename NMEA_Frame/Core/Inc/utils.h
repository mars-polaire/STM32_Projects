/*
 * utils.h
 *
 *  Created on: Apr 14, 2025
 *      Author: huawei
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_
#include "stm32l4xx_hal.h"
extern UART_HandleTypeDef huart1;
int fillbuffer(char* buffer, int size);
int isGPGGA(char *frame);
int extractChecksum(char *buffer);
int calculateChecksum(char *buffer);
int checkFrame(char *buffer);
int recherchevirg(char *frame, int i);
float getLatitude(char *frame);
float getLongitude(char *frame);
void setup(void);
void loop(void);



#endif /* INC_UTILS_H_ */
