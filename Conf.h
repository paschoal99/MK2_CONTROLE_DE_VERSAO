/*
 * Conf.h
 *
 *  Created on: Jun 13, 2023
 *      Author: victor.paschoal
 */

#ifndef CONF_H_
#define CONF_H_

#include <DAVE.h>

//********************************************************************************************************************************************
//***********************************************************== DEFINES ==********************************************************************
//********************************************************************************************************************************************


#define CONF_AXIS1_BUFFER_LEN		          32
#define CONF_AXIS1_FIXED_PKT_LEN	          5

#define CONF_AXIS1_HEADER				      0x7E
#define CONF_AXIS1_TAIL					  0x81
#define CONF_AXIS1_ID					      0x06

#define CONF_AXIS1_STATE_WAIT_HEADER		  0
#define CONF_AXIS1_STATE_GET_LEN			  10
#define CONF_AXIS1_STATE_GET_ID			      20
#define CONF_AXIS1_STATE_GET_FUNC			  30
#define CONF_AXIS1_STATE_GET_DATA			  40
#define CONF_AXIS1_STATE_CHECK_CRC	          50
#define CONF_AXIS1_STATE_WAIT_TAIL	          60

#define CONF_ANG_1						0
#define CONF_ANG_2						1
#define CONF_ANG_3						2
#define CONF_ANG_4						3

#define BOT_AUTO_PRESS					0
#define BOT_AUTO_DPRESS					1

#define BOT_MIN_PRESS					0
#define BOT_MIN_DPRESS					1



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
typedef struct STCONF{
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
	uint8_t				 Ang_min;


	uint8_t				 Bot_Ang;
	uint8_t				 Maq_Auto;
	uint8_t				 Maq_Ang_Min;


	uint8_t				 Cont_Ang;
	uint8_t				 Bot_Status;

	bool				 ANGLE;
	uint8_t				 BOT_ANGLE;

	bool				 ANG_ZERO;
	uint8_t				 BOT_ZERO;

	bool				 AUTOMATICO;
	uint8_t				 BOT_AUTO;

	bool				 MANUAL;
	uint8_t				 BOT_MANUAL;

	bool				 AUX_AUTO;
	bool 				 AUX_MANUAL;
	bool				 AUX_CONF_MAX;
	bool				 AUX_CONF_MIN;

	uint16_t				 Cont_AUT;
	uint16_t				 Cont_MANUAL;
	uint16_t				 Cont_ANG_MAX;
	uint16_t				 Cont_ANG_MIN;
	uint8_t				STATUS_CONF_ANG_HIGH[2];
	uint8_t				STATUS_CONF_ANG_LOW[2];
	bool				 STATUS_AUTOMATICO;
	bool				 STATUS_MANUAL;
	bool				 STATUS_BOT_AUTO;
	bool				 STATUS_BOT_MANUAL;
	bool				 BOT_START;
	bool				 STATUS_ANG_ZERO;

	bool 				ANG_MAX_INF;
	bool 				ANG_MAX_SUP;






}
CONF_t;



//********************************************************************************************************************************************
//***********************************************************== VARIABLES ==******************************************************************
//********************************************************************************************************************************************

extern CONF_t		CONF;

//********************************************************************************************************************************************
//***********************************************************== PROTOTYPES ==*****************************************************************
//********************************************************************************************************************************************

void ConfInit(void);
void ConfTask(void);

#endif /* CONF_H_ */
