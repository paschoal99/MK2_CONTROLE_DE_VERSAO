/*
 * Debauce.c
 *
 *  Created on: Jun 13, 2023
 *      Author: victor.paschoal
 */
/** @mainpage CONTROLE DE ÂNGULO MOVIMENTO DE FLEXO DISTRAÇÃO
 *
 * @date 05/07/2023
 *
 * @version 1.0
 *
 *
 */
#include <ReadAxis1.h>
#include <Action.h>
#include <Conf.h>
#include <scheduler.h>
#include <math.h>
#include <stdlib.h>
#include <Debauce.h>

DEBAUCE_t		DEBAUCE;

//********************************************************************************************************************************************
//***********************************************************== CONF INIT ==*************************************************************
//********************************************************************************************************************************************

void DebauceInit(void){

	taskSetState(TASK_DEBAUCE, TASK_1S);

}

//********************************************************************************************************************************************
//***********************************************************== CONF TASK ==**************************************************************
//********************************************************************************************************************************************

void DebauceTask(void){

	DEBAUCE.CONT_DEBAUCE ++;
	if((DEBAUCE.CONT_DEBAUCE >= 2) && (DIGITAL_IO_GetInput(&BOT_AUTO))){

		DEBAUCE.CONT_DEBAUCE = 0;
		DEBAUCE.STATUS_DEBAUCE = true;
		taskSetState(TASK_DEBAUCE, TASK_STOP);
	}else{
		taskSetState(TASK_DEBAUCE, TASK_200MS);
	}

}
