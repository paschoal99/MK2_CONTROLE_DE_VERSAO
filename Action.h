/*
 * Action.h
 *
 *  Created on: Apr 27, 2023
 *      Author: victor.paschoal
 */

#ifndef ACTION_H_
#define ACTION_H_

#include <DAVE.h>

//********************************************************************************************************************************************
//***********************************************************== DEFINES ==********************************************************************
//********************************************************************************************************************************************


#define ACTION_AXIS1_BUFFER_LEN		          32
#define ACTION_AXIS1_FIXED_PKT_LEN	          5

#define ACTION_AXIS1_HEADER				      0x7E
#define ACTION_AXIS1_TAIL					  0x81
#define ACTION_AXIS1_ID					      0x06

#define ACTION_AXIS1_STATE_WAIT_HEADER		  0
#define ACTION_AXIS1_STATE_GET_LEN			  10
#define ACTION_AXIS1_STATE_GET_ID			      20
#define ACTION_AXIS1_STATE_GET_FUNC			  30
#define ACTION_AXIS1_STATE_GET_DATA			  40
#define ACTION_AXIS1_STATE_CHECK_CRC	          50
#define ACTION_AXIS1_STATE_WAIT_TAIL	          60

#define ACTION_CONF_1						1
#define ACTION_CONF_2						2
#define ACTION_CONF_3						3
#define ACTION_CONF_4						4

//
//#define FUNC_ANGLE1				              0x00
//
//
//#define ADD_ACCELR  0x31
//#define ADD_ACCELW  0x30
//
//#define LIS2DW12_OUT_X_L                     0x28U
//#define LIS2DW12_OUT_X_H                     0x29U
//#define LIS2DW12_OUT_Y_L                     0x2AU
//#define LIS2DW12_OUT_Y_H                     0x2BU
//#define LIS2DW12_OUT_Z_L                     0x2CU
//#define LIS2DW12_OUT_Z_H                     0x2DU
//#define LIS2DW12_FIFO_CTRL                   0x2EU
//
//#define LIS2DW12_WHO_AM_I                    0x0FU
//#define LIS2DW12_CTRL1                       0x20U
//#define LIS2DW12_CTRL2                       0x21U
//#define LIS2DW12_CTRL6                       0x25U




//********************************************************************************************************************************************
//***********************************************************== STRUCTS ==********************************************************************
//********************************************************************************************************************************************
typedef struct STACTION{
	uint8_t		          rxData;
	uint8_t		          rxState;
	uint8_t		          rxCrc;
	uint8_t		          rxByteCount;
	uint8_t		          rxIndex;
	uint8_t		          rxFunc;
	uint8_t		          rxBuffer[ACTION_AXIS1_BUFFER_LEN];
	uint8_t		          txBuffer[ACTION_AXIS1_BUFFER_LEN];
	uint8_t		          rxTimer;
	uint8_t		          TaskState;
	uint8_t               register_map[2];
	I2C_MASTER_STATUS_t   status_I2C;
	uint8_t               whoamI;
	uint8_t               rst;
	int16_t               data_raw_acceleration[3];
	uint8_t               data_raw_buff[6];
	int16_t               data_raw_acceleration_buffer[10];
	int32_t               data_raw_acceleration_Sum;
	int32_t               data_raw_acceleration_Sum1;
	int32_t               data_raw_acceleration_Sum2;
	int16_t               data_raw_acceleration_Media1;
	int16_t               data_raw_acceleration_Media2;
	float                 acceleration_mg1;
	float                 acceleration_mg2;
	float                 acceleration_mg;
	float                 Angle1;
	float                 Angle2;
	uint16_t              AngleInt;
	int16_t              AngleIndice;
	float                Angle;
	bool                 ChangeAngle;
	uint16_t             counter;
	bool                 ChangeTrue;
	bool                 StatusCalibration1;
	bool                 StatusCalibration2;
	float                OffsetAngle1;
	float                OffsetAngle2;
	uint8_t              AngleCalibration;
	int8_t               OffsetMemoryACTION1;
	int8_t               OffsetMemoryACTION2;
	uint8_t              OffsetMemory1;
	uint8_t              OffsetMemory2;
	uint8_t              CountWork;
	float                AngleResolution;
	uint8_t				 Conf;
	bool				 START;
	bool				 Aux_angle_horario;
	bool				 Aux_angle_ant_horario;
	bool				 Horario;
	bool				 Ant_Horario;
	uint8_t               CountInit;
	uint8_t				 Ang_max;
	float				 Ang_min;
	bool				 Control_reverse;

	uint8_t				 VAL_Porcent;
	uint8_t				 RES_Porcent;
	uint8_t				 Porcent_treated;

	uint8_t				 VAL_Porcent_Min;
	uint8_t				 RES_Porcent_Min;
	float				 Porcent_treated_Min;

	uint8_t				 Erro_Ang_Min_5;
	uint8_t				 Erro_Ang_Min_0;

	uint8_t				 Ang_Min_Treated; // guarda valor de correção do angulo minimo

	uint8_t				 Status_Sense_motor[2];
	bool				 Status_motor;
	uint32_t			 Cont_Ciclos;
	uint8_t				 Cont_Ciclos_Memory[4];
	uint32_t			 Cont_Ciclos_Report;
	uint32_t			 Cont_Ciclos_Report_teste;
	uint32_t			 Cycles_Display;
	uint8_t				 Cont_Ciclos_Memory_Report[4];
	bool				 Ang_High;
	bool				 Ang_Low;

	uint8_t		Memory_00;
	uint8_t		Memory_01;
	uint8_t		Memory_02;
	uint8_t		Memory_03;

	uint8_t			ANG_TESTE_MANUAL;



}
ACTION_t;



//********************************************************************************************************************************************
//***********************************************************== VARIABLES ==******************************************************************
//********************************************************************************************************************************************

extern ACTION_t		ACTION;

//********************************************************************************************************************************************
//***********************************************************== PROTOTYPES ==*****************************************************************
//********************************************************************************************************************************************

void ActionInit(void);
void ActionTask(void);


#endif /* ACTION_H_ */
