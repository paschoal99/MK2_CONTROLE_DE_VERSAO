/*
 * Action.c
 *
 *  Created on: Apr 27, 2023
 *      Author: victor.paschoal
 */

/*
 * ReadAxis1.c
 *
 *  Created on: Jul 03, 2023
 *      Author: VICTOR.PASCHOAL
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

ACTION_t		ACTION;

//********************************************************************************************************************************************
//***********************************************************== CONTROL MOTOR INIT ==*************************************************************
//********************************************************************************************************************************************

void ActionInit(void){

	taskSetState(TASK_ACTION, TASK_STOP);

}

//********************************************************************************************************************************************
//***********************************************************== CONTROL MOTOR TASK ==*********************************************************
//********************************************************************************************************************************************


void ActionTask(void){


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////******************************************//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////CONTROLE DE ACIONAMENTO DO MODO AUTOMATICO//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////******************************************//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	if(CONF.STATUS_BOT_AUTO  == true || CONF.STATUS_BOT_MANUAL == true){
		CONF.STATUS_BOT_MANUAL = false;

		if(CONF.STATUS_AUTOMATICO == true){


			if(CONF.ANG_MAX_SUP == true && CONF.ANG_MAX_INF == true){
				DIGITAL_IO_SetOutputHigh(&LED1);
				DIGITAL_IO_SetOutputHigh(&PARTIDA);

			}else{


				DIGITAL_IO_SetOutputHigh(&LED1);
				DIGITAL_IO_SetOutputHigh(&PARTIDA);

				///////////////////////////////////////////////////////////////////////////////////////////
				ACTION.RES_Porcent = (ACTION.Ang_max * ACTION.VAL_Porcent) / 100;		//calculo da correção
				ACTION.Porcent_treated = (ACTION.Ang_max - ACTION.RES_Porcent);

				if(ReadAxis1.Angle >= ACTION.Porcent_treated){
					ACTION.Control_reverse = true;
				}

				///////////////////////////////////////////////////////////////////////////////////////////
				if(ACTION.Ang_min == -5){
					ACTION.Porcent_treated_Min = (ACTION.Ang_min + ACTION.Erro_Ang_Min_5); //ACTION.Erro_Ang_Min_5 adiciona o angulo de correção quando configurado -5

					if(ReadAxis1.Angle <= ACTION.Porcent_treated_Min){	//MINIMO
						ACTION.Control_reverse = false;
					}
				}
				if(ACTION.Ang_min == 0){
					ACTION.Ang_Min_Treated = ACTION.Ang_min + ACTION.Erro_Ang_Min_0; //ACTION.Erro_Ang_Min_0 adiciona o angulo de correção quando configurado 0

					if(ReadAxis1.Angle <= ACTION.Ang_Min_Treated){		//MINIMO
						ACTION.Control_reverse = false;
					}
				}
				///////////////////////////////////////////////////////////////////////////////////////////

				if(ACTION.Control_reverse == true){
					DIGITAL_IO_SetOutputHigh(&LED2);
					DIGITAL_IO_SetOutputHigh(&REVERSAO);
				}

				if(ACTION.Control_reverse == false){
					DIGITAL_IO_SetOutputLow(&LED2);
					DIGITAL_IO_SetOutputLow(&REVERSAO);
				}
			}

		}



		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////------------------------------------------//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////--CONTROLE DE ACIONAMENTO DO MODO MANUAL--//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////------------------------------------------//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		else if(CONF.STATUS_MANUAL == true){

			if(CONF.ANG_MAX_SUP == true && CONF.ANG_MAX_INF == true){
				CONF.STATUS_MANUAL = false;
				DIGITAL_IO_SetOutputHigh(&LED1);
				DIGITAL_IO_SetOutputHigh(&PARTIDA);

			}else{

				CONF.STATUS_MANUAL = false;
				DIGITAL_IO_SetOutputHigh(&LED1);
				DIGITAL_IO_SetOutputHigh(&PARTIDA);

				ACTION.RES_Porcent = (ACTION.Ang_max * ACTION.VAL_Porcent) / 100;
				ACTION.Porcent_treated = (ACTION.Ang_max - ACTION.RES_Porcent);



				if(ReadAxis1.Angle >= ACTION.Porcent_treated){			//MAXIMO
					ACTION.Control_reverse = true;

				}

				if(ACTION.Ang_min == -5){
					ACTION.Porcent_treated_Min = (ACTION.Ang_min + ACTION.Erro_Ang_Min_5); //ACTION.Erro_Ang_Min_5 adiciona o angulo de correção quando configurado -5

					if(ReadAxis1.Angle <= ACTION.Porcent_treated_Min){	//MINIMO
						ACTION.Control_reverse = false;
					}
				}
				if(ACTION.Ang_min == 0){
					ACTION.Ang_Min_Treated = ACTION.Ang_min + ACTION.Erro_Ang_Min_0; //ACTION.Erro_Ang_Min_0 adiciona o angulo de correção quando configurado 0

					if(ReadAxis1.Angle <= ACTION.Ang_Min_Treated){		//MINIMO
						ACTION.Control_reverse = false;
					}
				}

				if(ACTION.Control_reverse == true){				//aciona a inversão
					DIGITAL_IO_SetOutputHigh(&LED2);
					DIGITAL_IO_SetOutputHigh(&REVERSAO);
				}
				if(ACTION.Control_reverse == false){			//desaciona a inversão
					DIGITAL_IO_SetOutputLow(&LED2);
					DIGITAL_IO_SetOutputLow(&REVERSAO);
				}

			}
//
taskSetState(TASK_ACTION, TASK_STOP);
		}

	}else{
		DIGITAL_IO_SetOutputLow(&LED1);
		DIGITAL_IO_SetOutputLow(&LED2);
		DIGITAL_IO_SetOutputLow(&PARTIDA);
		taskSetState(TASK_ACTION, TASK_STOP);
		taskSetState(TASK_CONF, TASK_GO);

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////--------------------------------------------------///////////////////////////////////////////----------------------/////////////////////////////////////////
	//////////////////////////--CONTROLE DE CICLOS REALIZADOS PELO EQUIPAMENTO--///////////////////////////////////////////----------------------/////////////////////////////////////////
	//////////////////////////--------------------------------------------------///////////////////////////////////////////----------------------/////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	if(ReadAxis1.Angle <= 0 && ACTION.Ang_High == true){

		ACTION.Ang_High = false;
		ACTION.Cont_Ciclos = ACTION.Cont_Ciclos_Report ++;

		ACTION.Cont_Ciclos_Memory[0] = ACTION.Cont_Ciclos >> 24;
		ACTION.Cont_Ciclos_Memory[1] = ACTION.Cont_Ciclos >> 16;
		ACTION.Cont_Ciclos_Memory[2] = ACTION.Cont_Ciclos >> 8;
		ACTION.Cont_Ciclos_Memory[3] = ACTION.Cont_Ciclos;


		E_EEPROM_XMC1_Write(CONT_CYCLES, ACTION.Cont_Ciclos_Memory);
	}

	if(ReadAxis1.Angle >= 5){
		ACTION.Ang_High = true;
	}
}




