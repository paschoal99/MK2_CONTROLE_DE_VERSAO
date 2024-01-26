/*
 * Conf.c
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
 */

#include <ReadAxis1.h>
#include <Action.h>
#include <Conf.h>
#include <scheduler.h>
#include <math.h>
#include <stdlib.h>
#include <Debauce.h>

CONF_t		CONF;

//********************************************************************************************************************************************
//***********************************************************== CONF INIT ==*************************************************************
//********************************************************************************************************************************************

void ConfInit(void){

//	E_EEPROM_XMC1_Read(SENSE_MOTOR, 0, &ACTION.Status_Sense_motor[0], 1);
//
//
//	if(ACTION.Status_Sense_motor[0] == 1){
//		ACTION.Status_Sense_motor[0] = 0;
//	}
//
//	else if(ACTION.Status_Sense_motor[0] == 0){
//		ACTION.Status_Sense_motor[0] = 1;
//	}

	E_EEPROM_XMC1_Read(CONF_ANG_HIGH, 0, &CONF.STATUS_CONF_ANG_HIGH[0], 2);
	E_EEPROM_XMC1_Read(CONF_ANG_LOW, 0, &CONF.STATUS_CONF_ANG_LOW[0], 2);

	if(CONF.STATUS_CONF_ANG_HIGH[0] == 1){
		ACTION.Ang_max = 3;						//valor teste prototipo
		CONF.Bot_Ang = CONF_ANG_2;
		DIGITAL_IO_SetOutputHigh(&LED_CONF_5);
		DIGITAL_IO_SetOutputLow(&LED_CONF_10);
		DIGITAL_IO_SetOutputLow(&LED_CONF_15);
	}

	else if(CONF.STATUS_CONF_ANG_HIGH[0] == 2){
		ACTION.Ang_max = 5;						//valor teste prototipo
		CONF.Bot_Ang = CONF_ANG_3;
		DIGITAL_IO_SetOutputLow(&LED_CONF_5);
		DIGITAL_IO_SetOutputHigh(&LED_CONF_10);
		DIGITAL_IO_SetOutputLow(&LED_CONF_15);
	}

	else if(CONF.STATUS_CONF_ANG_HIGH[0] == 3){
		ACTION.Ang_max = 9;						//valor teste prototipo
		CONF.Bot_Ang = CONF_ANG_1;
		DIGITAL_IO_SetOutputLow(&LED_CONF_5);
		DIGITAL_IO_SetOutputLow(&LED_CONF_10);
		DIGITAL_IO_SetOutputHigh(&LED_CONF_15);
	}

	if(CONF.STATUS_CONF_ANG_LOW[0] == 1){
		ACTION.Ang_min = 0;
		//	CONF.Maq_Ang_Min = BOT_MIN_DPRESS;
		DIGITAL_IO_SetOutputHigh(&LED_CONF_MIN_0);
		DIGITAL_IO_SetOutputLow (&LED_CONF_MIN_5);
	}

	else if(CONF.STATUS_CONF_ANG_LOW[0] == 2){
		ACTION.Ang_min = -5;
		//	CONF.Maq_Ang_Min = BOT_MIN_DPRESS;
		DIGITAL_IO_SetOutputLow(&LED_CONF_MIN_0);
		DIGITAL_IO_SetOutputHigh (&LED_CONF_MIN_5);
	}

	CONF.STATUS_BOT_AUTO = false;
	CONF.STATUS_ANG_ZERO = false;

	taskSetState(TASK_CONF, TASK_GO);

}

//********************************************************************************************************************************************
//***********************************************************== CONF TASK ==**************************************************************
//********************************************************************************************************************************************

void ConfTask(void){

	CONF.BOT_ZERO = DIGITAL_IO_GetInput(&BOT_MIN);
	if(CONF.BOT_ZERO == false){
		//		CONF.BOT_ZERO = false;


		switch(CONF.Maq_Ang_Min)
		{
		case BOT_MIN_PRESS:
		{

			if(/*(CONF.AUTOMATICO == true && CONF.STATUS_BOT_AUTO == false) ||*/ (CONF.BOT_ZERO == false && CONF.STATUS_ANG_ZERO == false && DEBAUCE.STATUS_DEBAUCE_ANG_MIN == true)){
				CONF.ANG_MAX_SUP = false;
				DIGITAL_IO_SetOutputHigh(&LED_CONF_MIN_0);
				DIGITAL_IO_SetOutputLow (&LED_CONF_MIN_5);
				ACTION.Erro_Ang_Min_0 = 4;
				ACTION.Ang_min = 0;
				CONF.BOT_ZERO = 1;
				CONF.STATUS_ANG_ZERO = true;
				DEBAUCE.STATUS_DEBAUCE_ANG_MIN = false;
				CONF.Maq_Ang_Min = BOT_MIN_DPRESS;
				CONF.STATUS_CONF_ANG_LOW[0] = 1;
				E_EEPROM_XMC1_Write(CONF_ANG_LOW, &CONF.STATUS_CONF_ANG_LOW[0]);
				taskSetState(TASK_DEBAUCE, TASK_GO);
			}
		}
		break;

		case BOT_MIN_DPRESS:
		{
			if(/*(CONF.AUTOMATICO == true && CONF.STATUS_BOT_AUTO == true) ||*/ (CONF.BOT_ZERO == false && CONF.STATUS_ANG_ZERO == true && DEBAUCE.STATUS_DEBAUCE_ANG_MIN == true)){
				CONF.ANG_MAX_SUP = true;
				DIGITAL_IO_SetOutputLow (&LED_CONF_MIN_0);
				DIGITAL_IO_SetOutputHigh(&LED_CONF_MIN_5);
				ACTION.Erro_Ang_Min_5 = 4;
				ACTION.Ang_min = -5;
				CONF.Maq_Ang_Min = BOT_MIN_PRESS;
				CONF.Cont_AUT = 0;
				CONF.STATUS_ANG_ZERO = false;
				DEBAUCE.STATUS_DEBAUCE_ANG_MIN = false;
				CONF.STATUS_CONF_ANG_LOW[0] = 2;
				E_EEPROM_XMC1_Write(CONF_ANG_LOW, &CONF.STATUS_CONF_ANG_LOW[0]);
				taskSetState(TASK_DEBAUCE, TASK_GO);

			}
		}
		break;
		}
	}


	CONF.BOT_AUTO = DIGITAL_IO_GetInput(&BOT_AUTO);
	if(CONF.BOT_AUTO == false){
		//		CONF.BOT_AUTO = true;

		switch(CONF.Maq_Auto)
		{
		case BOT_AUTO_PRESS:
		{
			if((CONF.AUTOMATICO == true && CONF.STATUS_BOT_AUTO == false) || (CONF.BOT_AUTO == false && CONF.STATUS_BOT_AUTO == false && DEBAUCE.STATUS_DEBAUCE == true)){ //Liga automatico
				CONF.Maq_Auto = BOT_AUTO_DPRESS;
				CONF.STATUS_BOT_AUTO = true;
				CONF.STATUS_AUTOMATICO = true;
				DEBAUCE.STATUS_DEBAUCE = false;
				CONF.BOT_AUTO = 1;
				taskSetState(TASK_DEBAUCE, TASK_GO);
				taskSetState(TASK_ACTION, TASK_GO);
			}
		}
		break;

		case BOT_AUTO_DPRESS:
		{
			if((CONF.AUTOMATICO == true && CONF.STATUS_BOT_AUTO == true) || (CONF.BOT_AUTO == false && CONF.STATUS_BOT_AUTO == true && DEBAUCE.STATUS_DEBAUCE == true)){ //Desliga automatico
				CONF.Maq_Auto = BOT_AUTO_PRESS;
				CONF.Cont_AUT = 0;
				CONF.STATUS_BOT_AUTO = false;
				CONF.STATUS_AUTOMATICO = false;
				DEBAUCE.STATUS_DEBAUCE = false;
				CONF.BOT_AUTO = 1;
				taskSetState(TASK_DEBAUCE, TASK_GO);
				DIGITAL_IO_SetOutputLow(&LED1);
				DIGITAL_IO_SetOutputLow(&LED2);
				taskSetState(TASK_ACTION, TASK_STOP);
			}
		}
		break;
		}
	}






	CONF.BOT_MANUAL = DIGITAL_IO_GetInput(&BOT_MANUAL);
	if(CONF.MANUAL == true || CONF.BOT_MANUAL == 1){
		CONF.Maq_Auto = BOT_AUTO_PRESS;
		CONF.STATUS_BOT_AUTO = false;
		CONF.STATUS_AUTOMATICO = false;
		CONF.STATUS_MANUAL = true;
		CONF.STATUS_BOT_MANUAL = true;
		taskSetState(TASK_ACTION, TASK_GO);
		taskSetState(TASK_CONF, TASK_STOP);
	}

	if(CONF.ANGLE == true ){
		CONF.ANGLE = false;
		switch(CONF.Bot_Ang)
		{
		case CONF_ANG_1:
		{
			if(DEBAUCE.STATUS_DEBAUCE == true){
				CONF.ANG_MAX_INF = false;
				DEBAUCE.STATUS_DEBAUCE = false;
				CONF.STATUS_CONF_ANG_HIGH[0] = 1;
				ACTION.Ang_max = 3;						//valor teste prototipo
				ACTION.VAL_Porcent = 95;
				CONF.Bot_Ang = CONF_ANG_2;
				taskSetState(TASK_DEBAUCE, TASK_GO);
				DIGITAL_IO_SetOutputHigh(&LED_CONF_5);
				DIGITAL_IO_SetOutputLow(&LED_CONF_10);
				DIGITAL_IO_SetOutputLow(&LED_CONF_15);
				E_EEPROM_XMC1_Write(CONF_ANG_HIGH, &CONF.STATUS_CONF_ANG_HIGH[0]);
			}

		}
		break;

		case CONF_ANG_2:
		{
			if(DEBAUCE.STATUS_DEBAUCE == true){
				CONF.ANG_MAX_INF = false;
				DEBAUCE.STATUS_DEBAUCE = false;
				CONF.STATUS_CONF_ANG_HIGH[0] = 2;
				ACTION.Ang_max = 5;						//valor teste prototipo
				ACTION.VAL_Porcent = 50;
				CONF.Bot_Ang = CONF_ANG_3;
				taskSetState(TASK_DEBAUCE, TASK_GO);
				DIGITAL_IO_SetOutputLow (&LED_CONF_5);
				DIGITAL_IO_SetOutputHigh(&LED_CONF_10);
				DIGITAL_IO_SetOutputLow (&LED_CONF_15);
				E_EEPROM_XMC1_Write(CONF_ANG_HIGH, &CONF.STATUS_CONF_ANG_HIGH[0]);
			}

		}
		break;

		case CONF_ANG_3:
		{
			if(DEBAUCE.STATUS_DEBAUCE == true){
				CONF.ANG_MAX_INF = true;
				DEBAUCE.STATUS_DEBAUCE = false;
				CONF.STATUS_CONF_ANG_HIGH[0] = 3;
				ACTION.Ang_max = 9;						//valor teste prototipo
				ACTION.VAL_Porcent = 10;
				CONF.Bot_Ang = CONF_ANG_1;
				taskSetState(TASK_DEBAUCE, TASK_GO);
				DIGITAL_IO_SetOutputLow (&LED_CONF_5);
				DIGITAL_IO_SetOutputLow (&LED_CONF_10);
				DIGITAL_IO_SetOutputHigh(&LED_CONF_15);
				E_EEPROM_XMC1_Write(CONF_ANG_HIGH, &CONF.STATUS_CONF_ANG_HIGH[0]);
			}

		}
		break;
		}
	}
}

void Handler_BOT_MAX (void){
	CONF.ANGLE = true;
}


