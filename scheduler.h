/*
 * scheduler.h
 *
 *  Created on: Sep 29, 2021
 *      Author: diego.marinho
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_


#include <DAVE.h>

//********************************************************************************************************************************************
//***********************************************************== DEFINES ==********************************************************************
//********************************************************************************************************************************************

#define N_OF_TASKS				5

// Tasks Defines
#define TASK_CONTROL_ANGLE1 		0
#define TASK_TRANSMIT_ANGLE 		1
#define TASK_ACTION			 		2
#define TASK_CONF			 		3
#define TASK_DEBAUCE				4


// Tasks States
#define TASK_GO           		1               // Set to pooling the task
#define TASK_STOP           	-1              // Set to stop the task
#define TASK_2MS				2
#define TASK_7MS           		7
#define TASK_10MS           	10
#define TASK_15MS				15
#define TASK_20MS				20
#define TASK_30MS				30
#define TASK_40MS				40
#define TASK_100MS          	100
#define TASK_200MS          	200
#define TASK_1S             	1000
#define TASK_2S					2000
#define TASK_5S					5000
#define TASK_6S					6000
#define TASK_10S             	10000


//********************************************************************************************************************************************
//***********************************************************== PROTOTYPES ==*****************************************************************
//********************************************************************************************************************************************

void scheduler(void);
void taskSetState(uint8_t task, int32_t state);
int32_t taskGetState(uint8_t task);

#endif /* SCHEDULER_H_ */
