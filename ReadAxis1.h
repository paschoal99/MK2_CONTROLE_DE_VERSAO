/*
 * ReadAxis1.h
 *
 *  Created on: Sep 29, 2021
 *      Author: diego.marinho
 */

#ifndef READAXIS1_H_
#define READAXIS1_H_

#include <DAVE.h>

//********************************************************************************************************************************************
//***********************************************************== DEFINES ==********************************************************************
//********************************************************************************************************************************************


#define READ_AXIS1_BUFFER_LEN		          32
#define READ_AXIS1_FIXED_PKT_LEN	          5

#define READ_AXIS1_HEADER				      0x7E
#define READ_AXIS1_TAIL					      0x81
#define READ_AXIS1_ID					      0x06

#define READ_AXIS1_STATE_WAIT_HEADER		  0
#define READ_AXIS1_STATE_GET_LEN			  10
#define READ_AXIS1_STATE_GET_ID			      20
#define READ_AXIS1_STATE_GET_FUNC			  30
#define READ_AXIS1_STATE_GET_DATA			  40
#define READ_AXIS1_STATE_CHECK_CRC	          50
#define READ_AXIS1_STATE_WAIT_TAIL	          60

#define FUNC_ANGLE1				              0x00


#define ADD_ACCELR  0x31
#define ADD_ACCELW  0x30

#define LIS2DW12_OUT_X_L                     0x28U
#define LIS2DW12_OUT_X_H                     0x29U
#define LIS2DW12_OUT_Y_L                     0x2AU
#define LIS2DW12_OUT_Y_H                     0x2BU
#define LIS2DW12_OUT_Z_L                     0x2CU
#define LIS2DW12_OUT_Z_H                     0x2DU
#define LIS2DW12_FIFO_CTRL                   0x2EU

#define LIS2DW12_WHO_AM_I                    0x0FU
#define LIS2DW12_CTRL1                       0x20U
#define LIS2DW12_CTRL2                       0x21U
#define LIS2DW12_CTRL6                       0x25U




//********************************************************************************************************************************************
//***********************************************************== STRUCTS ==********************************************************************
//********************************************************************************************************************************************
typedef struct STReadAxis1{
	uint8_t		          rxData;
	uint8_t		          rxState;
	uint8_t		          rxCrc;
	uint8_t		          rxByteCount;
	uint8_t		          rxIndex;
	uint8_t		          rxFunc;
	uint8_t		          rxBuffer[READ_AXIS1_BUFFER_LEN];
	uint8_t		          txBuffer[READ_AXIS1_BUFFER_LEN];
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
	float                 Angle;
	bool                  ChangeAngle;
	uint16_t              counter;
	bool                  ChangeTrue;
	bool                  StatusCalibration1;
	bool                  StatusCalibration2;
	float                 OffsetAngle1;
	float                 OffsetAngle2;
	uint8_t               AngleCalibration;
	int8_t                OffsetMemoryRead1;
	int8_t                OffsetMemoryRead2;
	uint8_t               OffsetMemory1;
	uint8_t               OffsetMemory2;
	uint8_t               CountWork;
	float                 AngleResolution;

	uint8_t               CountInit;


}
ReadAxis1_t;



//********************************************************************************************************************************************
//***********************************************************== VARIABLES ==******************************************************************
//********************************************************************************************************************************************
extern ReadAxis1_t		ReadAxis1;

//********************************************************************************************************************************************
//***********************************************************== PROTOTYPES ==*****************************************************************
//********************************************************************************************************************************************
void ReadAxis1Init(void);
void ReadAxis1Task(void);
void TransmitAngleTask(void);
void ReadAxis1SendSetup(void);
void SetupSensor(void);

float lis2dw12_from_fs2_to_mg(int16_t lsb);

#endif /* READAXIS1_H_ */
