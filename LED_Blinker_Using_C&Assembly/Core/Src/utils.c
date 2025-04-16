/*
 * utils.c
 *
 *  Created on: Apr 16, 2025
 *      Author: mars-polaire
 */

#include "utils.h"
#include "LED.h"
#include "button.h"

void loop() {
    int GreenLED_state = 0;
    int speed = 100;
    int prev_button_state = 0, button_state ;

    while (1) {

        button_state = BUTTON_GetBlueLevel();


        if (button_state == 1 && prev_button_state == 0) {
            UTILS_WaitN10ms(5);


            if (BUTTON_GetBlueLevel() == 1) {

                speed = (speed == 1000) ? 100 : 1000;
            }
        }


        prev_button_state = button_state;


        LED_DriveGreen(GreenLED_state);
        GreenLED_state = 1 - GreenLED_state;


        UTILS_WaitN10ms(speed);
    }
}

void setup(){
//  it will be run once.
    LED_Enable();
    LED_Configure();

}

void UTILS_WaitN10ms(int N){
	int n,i,s=0;
    for(n=1;n<=N;n++){
    	for(i=0;i<2500;i++){
    		s=s+i;
    	}
    }
}
