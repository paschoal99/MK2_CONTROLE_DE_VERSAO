/*
 * scheduler.c
 *
 *  Created on: Sep 29, 2021
 *      Author: diego.marinho
 */

#include <scheduler.h>
#include <Action.h>
#include <Conf.h>
#include <ReadAxis1.h>
#include <Debauce.h>


//********************************************************************************************************************************************
//***********************************************************== VARIABLES ==******************************************************************
//********************************************************************************************************************************************

volatile int32_t tasksTimer[N_OF_TASKS];

void(*func[N_OF_TASKS])(void) =
{
	&ReadAxis1Task,
	&TransmitAngleTask,
	&ActionTask,
	&ConfTask,
	&DebauceTask
};




//********************************************************************************************************************************************
//***********************************************************== SCHEDULER ==******************************************************************
//********************************************************************************************************************************************
void scheduler(void)
{
    unsigned char i = 0;

    for(i = 0; i < N_OF_TASKS; i++)     // Run all the tasks
    {
        if(!tasksTimer[i])             	// If GO STATE
        {
            func[i]();                  // Execute
        }
    }
    return;
}



//********************************************************************************************************************************************
//***********************************************************== TIMER 1MS IRQ ==**************************************************************
//********************************************************************************************************************************************

void Timer1msIRQHandler(void){

	for(uint8_t i = 0; i < N_OF_TASKS; i++)     	// Timer for managing all the tasks
    {
        if(tasksTimer[i] > 0)
        {
        	tasksTimer[i]--;
        }
    }

	ReadAxis1.CountWork++;
	if(ReadAxis1.CountWork == 200){
		ReadAxis1.CountWork = 0;
		//DIGITAL_IO_ToggleOutput(&LED2);
	}


}

//********************************************************************************************************************************************
//***********************************************************== TASK SET STATE ==*************************************************************
//********************************************************************************************************************************************
void taskSetState(uint8_t task, int32_t state)
{
    if(task < N_OF_TASKS)
    {
        tasksTimer[task] = state;
    }
    return;
}


//********************************************************************************************************************************************
//***********************************************************== TASK GET STATE ==*************************************************************
//********************************************************************************************************************************************
int32_t taskGetState(uint8_t task)
{
    return(tasksTimer[task]);
}
