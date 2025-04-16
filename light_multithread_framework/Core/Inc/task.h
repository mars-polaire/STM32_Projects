/*
 * task.h
 *
 *  Created on: Apr 15, 2025
 *      Author: mars-polaire
 */

#ifndef INC_TASK_H_
#define INC_TASK_H_
static int globalDelayInMs=200;
typedef struct motif_type{
	int size;
    int * motif;
    char * name;
}MOTIF_TYPE;
int upDownMotif[]={0,128,192,224,240,248,252,254,255,254,252,248,240,224,192,128};
int chenillardUpMotif[]={1,2,4,8,16,32,64,128};
int chenillardDownMotif[]={128,64,32,16,8,4,2,1};
const MOTIF_TYPE upDown={16,upDownMotif,"Up Down"};
const MOTIF_TYPE chenillardUp={8,chenillardUpMotif,"K 2000"};
const MOTIF_TYPE chenillardDown={8,chenillardDownMotif,"K-2000"};
const MOTIF_TYPE* tableau_motif[3]={&upDown, &chenillardUp, &chenillardDown};
static int index_tableau_motif=0;
void taskLED();
void taskButton();
void taskScreen();


#endif /* INC_TASK_H_ */
