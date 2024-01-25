/*
 * main.c
 *
 *  Created on: 2021 Sep 13 11:49:33
 *  Author: diego.marinho
 */

#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)
#include <scheduler.h>
#include <Action.h>
#include <Conf.h>
#include <ReadAxis1.h>
#include <Debauce.h>

/**
 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */


int main(void)
{
	DAVE_STATUS_t status;

	status = DAVE_Init();           /* Initialization of DAVE APPs  */

	if(status != DAVE_STATUS_SUCCESS)
	{
		/* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
		XMC_DEBUG("DAVE APPs initialization failed\n");

		while(1U)
		{

		}
	}

	WATCHDOG_Start(); 		// Start the watchdog timer



	//  ACTION.Cont_Ciclos_R[0] = 150;
	//  E_EEPROM_XMC1_Write(CONT_CYCLES, &ACTION.Cont_Ciclos_R[0]);


	//  	ACTION.Cont_Ciclos = 0;
	//
	//	ACTION.Cont_Ciclos_Memory[0] = ACTION.Cont_Ciclos >> 24	;
	//	ACTION.Cont_Ciclos_Memory[1] = ACTION.Cont_Ciclos >> 16	;
	//	ACTION.Cont_Ciclos_Memory[2] = ACTION.Cont_Ciclos >> 8	;
	//	ACTION.Cont_Ciclos_Memory[3] = ACTION.Cont_Ciclos		;
	//
	//	E_EEPROM_XMC1_Write(CONT_CYCLES, ACTION.Cont_Ciclos_Memory);



	//  E_EEPROM_XMC1_Read(CONT_CYCLES, 0, &ACTION.Cont_Ciclos_Memory[0], 4);
	//  ACTION.Cont_Ciclos_Report = ACTION.Memory_00;
	//
	//  E_EEPROM_XMC1_Read(CONT_CYCLES, 0,&ACTION.Memory_01, 2);
	//  ACTION.Cont_Ciclos_Report = (ACTION.Memory_00 << 8)  | ACTION.Memory_01;
	//
	//  E_EEPROM_XMC1_Read(CONT_CYCLES, 0,&ACTION.Memory_02, 3);
	//  ACTION.Cont_Ciclos_Report = (ACTION.Memory_01 << 16) | ACTION.Memory_02;
	//
	//  E_EEPROM_XMC1_Read(CONT_CYCLES, 0,&ACTION.Memory_03, 4);
	//  ACTION.Cont_Ciclos_Report = (ACTION.Memory_02 << 24) | ACTION.Memory_03;
	//


	E_EEPROM_XMC1_Read(CONT_CYCLES, 0, &ACTION.Cont_Ciclos_Memory_Report[0], 4);

	ACTION.Cont_Ciclos_Report = ACTION.Cont_Ciclos_Memory_Report [0];
	ACTION.Cont_Ciclos_Report = (ACTION.Cont_Ciclos_Report << 8) | ACTION.Cont_Ciclos_Memory_Report[1];
	ACTION.Cont_Ciclos_Report = (ACTION.Cont_Ciclos_Report << 8) | ACTION.Cont_Ciclos_Memory_Report[2];
	ACTION.Cont_Ciclos_Report = (ACTION.Cont_Ciclos_Report << 8) | ACTION.Cont_Ciclos_Memory_Report[3];

	ACTION.Cycles_Display = ACTION.Cont_Ciclos_Report;


	//  E_EEPROM_XMC1_Read(CONT_CYCLES, 0, &ACTION.Cont_Ciclos_Memory_Report[0], 4);
	//
	//  ACTION.Cont_Ciclos_Report = ACTION.Cont_Ciclos_Memory_Report[0];
	//  ACTION.Cont_Ciclos_Report = (ACTION.Cont_Ciclos_Report << 24) | ACTION.Cont_Ciclos_Memory_Report[1];
	//  ACTION.Cont_Ciclos_Report = (ACTION.Cont_Ciclos_Report << 16) | ACTION.Cont_Ciclos_Memory_Report[2];
	//  ACTION.Cont_Ciclos_Report = (ACTION.Cont_Ciclos_Report << 8)  | ACTION.Cont_Ciclos_Memory_Report[3];
	//
	//
	//  ACTION.Cont_Ciclos_Report_teste = ACTION.Cont_Ciclos_Report;


	E_EEPROM_XMC1_Read(OFFSET1,		 	0,	 &ReadAxis1.OffsetMemory1,		 1);
	E_EEPROM_XMC1_Read(OFFSET2,		 	0,	 &ReadAxis1.OffsetMemory2,		 1);
	//E_EEPROM_XMC1_Read(CONF_ANG_HIGH,     0,	 &CONF.STATUS_CONF_ANG_HIGH,	 2);


	if(ReadAxis1.OffsetMemory1 == 0xFF){
		ReadAxis1.OffsetMemory1 = 0;
	}

	if(ReadAxis1.OffsetMemory2 == 0xFF){
		ReadAxis1.OffsetMemory2 = 0;
	}

	ReadAxis1.OffsetMemoryRead1 = ReadAxis1.OffsetMemory1;
	ReadAxis1.OffsetAngle1 = (float)ReadAxis1.OffsetMemoryRead1/10;
	ReadAxis1.OffsetAngle1 = 0;

	ReadAxis1.OffsetMemoryRead2 = ReadAxis1.OffsetMemory2;
	ReadAxis1.OffsetAngle2 = (float)ReadAxis1.OffsetMemoryRead2/10;
	ReadAxis1.OffsetAngle2 = 0;

	ReadAxis1Init();
	ActionInit();
	ConfInit();
	DebauceInit();

	/* Placeholder for user application code. The while loop below can be replaced with user application code. */
	while(1U)
	{
		scheduler();
		WATCHDOG_Service(); //service the watchdog timer.
	}
}


void Watchdog_Handler(void){
	WATCHDOG_ClearAlarm(); 	//clears the alarm flag
	WATCHDOG_Service(); 	//service the watchdog timer.
	WATCHDOG_Stop(); 		//Stop the watchdog timer
}
