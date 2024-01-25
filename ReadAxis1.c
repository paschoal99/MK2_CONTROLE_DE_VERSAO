/*
 * ReadAxis1.c
 *
 *  Created on: Sep 29, 2021
 *      Author: diego.marinho
 */


#include <ReadAxis1.h>
#include <scheduler.h>
#include <math.h>
#include <stdlib.h>

//********************************************************************************************************************************************
//***********************************************************== VARIABLES ==******************************************************************
//********************************************************************************************************************************************
ReadAxis1_t		ReadAxis1;
/////////////////////////////////37   38   39   40   41    42   43   44  45   46   47   48   49   50   51   52   53    54   55  56   57   58   59   60   61   62   63  64   65   66  67   68   69  70  71   72   73   74   75   76   77
const float ResolutionAcel[41] = {0.2, 0.1, 0.3, 0.3, 0.3, 0.4, 0.4, 0.4, 0.6, 0.5, 0.6, 0.6, 0.6, 0.6, 0.6, 0.6, 0.7, 0.9, 1.1, 1.1, 1.2, 1.3, 1.4, 1.4, 1.6, 1.6, 2, 2.1, 2.1, 2.3, 2.4, 2.9, 3, 3.4, 3.6, 4.2, 4.5, 5.3, 6.8, 8.2, 10};


//********************************************************************************************************************************************
//***********************************************************== PROTOTYPES ==*****************************************************************
//********************************************************************************************************************************************
uint8_t ReadAxis1GetCRC(unsigned char *startAddr, unsigned char *endAddr);


//********************************************************************************************************************************************
//***********************************************************== CONTROL MOTOR INIT ==*************************************************************
//********************************************************************************************************************************************
void ReadAxis1Init(void){
	taskSetState(TASK_CONTROL_ANGLE1, TASK_STOP); //inicia a leitura do angulo 1
	taskSetState(TASK_TRANSMIT_ANGLE, TASK_STOP); //não envia ângulo a central

	UART_Receive(&UART_0, &ReadAxis1.rxData, 1);

	ReadAxis1.ChangeAngle = true;
	//DIGITAL_IO_ToggleOutput(&LED1);
	//DIGITAL_IO_ToggleOutput(&LED2);

	//setup do sensor
	SetupSensor();
	taskSetState(TASK_CONTROL_ANGLE1, TASK_GO); //inicia a leitura do angulo 1


}

//********************************************************************************************************************************************
//***********************************************************== CONTROL MOTOR TASK ==**************************************************************
//********************************************************************************************************************************************
void ReadAxis1Task(void){
	//leitura de dados do sensor
	//Leitura dos dados crus do acelerômetro 1

	memset(ReadAxis1.data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
	ReadAxis1.register_map[0] = LIS2DW12_OUT_X_L;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, ReadAxis1.data_raw_buff, 6, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));



	ReadAxis1.data_raw_acceleration[0] = (int16_t)ReadAxis1.data_raw_buff[1];
	ReadAxis1.data_raw_acceleration[0] = (ReadAxis1.data_raw_acceleration[0] * 256) +  (int16_t)ReadAxis1.data_raw_buff[0];
	ReadAxis1.data_raw_acceleration[1] = (int16_t)ReadAxis1.data_raw_buff[3];
	ReadAxis1.data_raw_acceleration[1] = (ReadAxis1.data_raw_acceleration[1] * 256) +  (int16_t)ReadAxis1.data_raw_buff[2];
	ReadAxis1.data_raw_acceleration[2] = (int16_t)ReadAxis1.data_raw_buff[5];
	ReadAxis1.data_raw_acceleration[2] = (ReadAxis1.data_raw_acceleration[2] * 256) +  (int16_t)ReadAxis1.data_raw_buff[4];

	if(ReadAxis1.counter != 10){
		ReadAxis1.counter++;

		ReadAxis1.data_raw_acceleration_Sum1 = ReadAxis1.data_raw_acceleration_Sum1 + ReadAxis1.data_raw_acceleration[0];
		ReadAxis1.data_raw_acceleration_Sum2 = ReadAxis1.data_raw_acceleration_Sum2 + ReadAxis1.data_raw_acceleration[1];

	}

	if(ReadAxis1.counter == 10){
		ReadAxis1.counter = 0;


        ///////////////////////////////////////calculo da aceleração da gravidade em 2 eixos//////////////////////
		ReadAxis1.data_raw_acceleration_Media1 = ReadAxis1.data_raw_acceleration_Sum1/10;
		ReadAxis1.data_raw_acceleration_Sum1 = 0;

		ReadAxis1.acceleration_mg1 = lis2dw12_from_fs2_to_mg(ReadAxis1.data_raw_acceleration_Media1)/1000;

		ReadAxis1.data_raw_acceleration_Media2 = ReadAxis1.data_raw_acceleration_Sum2/10;
		ReadAxis1.data_raw_acceleration_Sum2 = 0;

		ReadAxis1.acceleration_mg2 = lis2dw12_from_fs2_to_mg(ReadAxis1.data_raw_acceleration_Media2)/1000;

		ReadAxis1.Angle = asin(ReadAxis1.acceleration_mg2);
		ReadAxis1.Angle = -ReadAxis1.Angle;
		ReadAxis1.Angle = 180*ReadAxis1.Angle/3.141592;

		taskSetState(TASK_ACTION, TASK_GO);

		if(ReadAxis1.acceleration_mg2 < -1){
			ReadAxis1.ChangeTrue = true; //indica eixo 2
		}



		ReadAxis1.AngleIndice = (int16_t)ReadAxis1.Angle;

		if(ReadAxis1.AngleIndice >= 37){
			//ReadAxis1.AngleResolution = ReadAxis1.Angle + ResolutionAcel[ReadAxis1.AngleIndice - 37] + 1.6;
			ReadAxis1.AngleResolution = ReadAxis1.Angle;
		}
		else{
			ReadAxis1.AngleResolution = ReadAxis1.Angle;
		}

		if(ReadAxis1.AngleResolution >= 75){
			ReadAxis1.ChangeTrue = true; //indica eixo 2
//			DIGITAL_IO_ToggleOutput(&LED1);
//			DIGITAL_IO_ToggleOutput(&LED2);

		}

		if(ReadAxis1.ChangeTrue == true){
			ReadAxis1.Angle2 = acos(ReadAxis1.acceleration_mg1);
			ReadAxis1.Angle2 = 180*ReadAxis1.Angle2/3.141592;
			ReadAxis1.AngleResolution = ReadAxis1.Angle2;

			if(ReadAxis1.AngleResolution <= 65){
				ReadAxis1.ChangeTrue = false; //indica eixo 1
//				DIGITAL_IO_ToggleOutput(&LED1);
//				DIGITAL_IO_ToggleOutput(&LED2);
			}
		}



		ReadAxis1.AngleInt = ReadAxis1.AngleResolution*100;


	}


	taskSetState(TASK_CONTROL_ANGLE1, TASK_20MS);
//	DIGITAL_IO_ToggleOutput(&LED1);

}

void TransmitAngleTask(void){
	//envia o angulo a central
	  uint8_t txIndex = 0;
	  ReadAxis1.txBuffer[txIndex++] = 0x7E;
	  ReadAxis1.txBuffer[txIndex++] = 8;
	  ReadAxis1.txBuffer[txIndex++] = 0;
	  ReadAxis1.txBuffer[txIndex++] = ReadAxis1.AngleInt >> 8;
	  ReadAxis1.txBuffer[txIndex++] = (uint8_t)ReadAxis1.AngleInt;
	  ReadAxis1.txBuffer[txIndex++] = ReadAxis1.ChangeTrue;
	  ReadAxis1.txBuffer[txIndex] = ReadAxis1GetCRC(&ReadAxis1.txBuffer[0], &ReadAxis1.txBuffer[txIndex - 1]);
	  txIndex++;
	  ReadAxis1.txBuffer[txIndex++] = 0x81;
	  UART_Transmit(&UART_0, ReadAxis1.txBuffer, 8);
//	  DIGITAL_IO_ToggleOutput(&LED2);
//	  taskSetState(TASK_TRANSMIT_ANGLE, TASK_STOP);

}

void ReceiveCentral(void){
	UART_Receive(&UART_0, &ReadAxis1.rxData, 1);
	UART_ClearRXFIFOStatus(&UART_0, XMC_USIC_CH_RXFIFO_EVENT_STANDARD);


	switch(ReadAxis1.rxState)
	{
	    case READ_AXIS1_STATE_WAIT_HEADER:
	    {
	    	if(ReadAxis1.rxData == READ_AXIS1_HEADER){
	    		ReadAxis1.rxState = READ_AXIS1_STATE_GET_LEN;
	    		ReadAxis1.rxCrc = ReadAxis1.rxData;
	    	}
	    }
	    break;

		case READ_AXIS1_STATE_GET_LEN:
		{
			if(ReadAxis1.rxData < READ_AXIS1_BUFFER_LEN + READ_AXIS1_FIXED_PKT_LEN)
			{
				ReadAxis1.rxByteCount = ReadAxis1.rxData;
				ReadAxis1.rxCrc ^= ReadAxis1.rxData;
				ReadAxis1.rxState = READ_AXIS1_STATE_GET_FUNC;
			}
			else
			{
				ReadAxis1.rxState = READ_AXIS1_STATE_WAIT_HEADER;
			}
		}
		break;



		case READ_AXIS1_STATE_GET_FUNC:
		{
			ReadAxis1.rxFunc = ReadAxis1.rxData;
			ReadAxis1.rxCrc ^= ReadAxis1.rxData;
			ReadAxis1.rxIndex = 0;
			ReadAxis1.rxState = READ_AXIS1_STATE_GET_DATA;
		}
		break;

		case READ_AXIS1_STATE_GET_DATA:
		{
			ReadAxis1.rxBuffer[ReadAxis1.rxIndex++] = ReadAxis1.rxData;
			ReadAxis1.rxCrc ^= ReadAxis1.rxData;
			if(ReadAxis1.rxIndex == ReadAxis1.rxByteCount - READ_AXIS1_FIXED_PKT_LEN) // data len = total - (start, len, id, func, crc, stop)
			{
				ReadAxis1.rxState = READ_AXIS1_STATE_CHECK_CRC;
			}
		}
		break;

		case READ_AXIS1_STATE_CHECK_CRC:
		{
			ReadAxis1.rxCrc = ~ReadAxis1.rxCrc;
			if(ReadAxis1.rxData == ReadAxis1.rxCrc)
			{
				ReadAxis1.rxState = READ_AXIS1_STATE_WAIT_TAIL;
			}
			else
			{
				ReadAxis1.rxState = READ_AXIS1_STATE_WAIT_HEADER;
			}
		}
		break;

		case READ_AXIS1_STATE_WAIT_TAIL:
		{
			if(ReadAxis1.rxData == READ_AXIS1_TAIL)
			{

				if(ReadAxis1.rxBuffer[1] == 1){
					ReadAxis1.StatusCalibration1 = true;
					ReadAxis1.AngleCalibration = ReadAxis1.rxBuffer[1];
				}
				else if(ReadAxis1.rxBuffer[1] == 2){
					ReadAxis1.StatusCalibration2 = true;
					ReadAxis1.AngleCalibration = ReadAxis1.rxBuffer[1];
				}
				taskSetState(TASK_TRANSMIT_ANGLE, TASK_GO);

				if(ReadAxis1.rxBuffer[2] == 1){
					//entrou no modo encoder
					//parar a leitura
					taskSetState(TASK_CONTROL_ANGLE1, TASK_STOP);
					taskSetState(TASK_TRANSMIT_ANGLE, TASK_STOP);
				}
				else if(ReadAxis1.rxBuffer[2] == 2){
					//voltou para o modo angulo
					//reiniciar a leitura
					taskSetState(TASK_CONTROL_ANGLE1, TASK_GO);
					ReadAxis1.counter = 0;
					ReadAxis1.data_raw_acceleration_Sum = 0;
				}
			}
			ReadAxis1.rxState = READ_AXIS1_STATE_WAIT_HEADER;
		}
		break;
	}
}

uint8_t ReadAxis1GetCRC(unsigned char *startAddr, unsigned char *endAddr)
{
     uint8_t crc = 0;
     while(startAddr <= endAddr)
     {
         //ServiceDog();            // Feed the watchdog.
         crc = crc ^ (*startAddr);
         startAddr++;
     }
     crc = ~crc;
     crc &= 0x00FF;
     return(crc);
}

//********************************************************************************************************************************************
//***********************************************************== SEND IDLE ==******************************************************************
//********************************************************************************************************************************************
void ReadAxis1SendSetup(void){

}

void SetupSensor(void){
	// WHO AM I
	ReadAxis1.register_map[0] = LIS2DW12_WHO_AM_I;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, &ReadAxis1.whoamI, 1, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));

	ReadAxis1.register_map[0] = LIS2DW12_CTRL2;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, &ReadAxis1.rst, 1, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));

	ReadAxis1.register_map[0] = LIS2DW12_CTRL2;
	ReadAxis1.register_map[1] = ReadAxis1.rst | 0b01000000;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, ReadAxis1.register_map, 2, true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));

	do {
		ReadAxis1.register_map[0] = LIS2DW12_CTRL2;
		ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
		while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
		ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, &ReadAxis1.rst, 1, true, true);
		while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));
		ReadAxis1.register_map[1] = ReadAxis1.rst & 0b01000000;
	} while (ReadAxis1.register_map[1]);

	//Block data update
	ReadAxis1.register_map[0] = LIS2DW12_CTRL2;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, &ReadAxis1.rst, 1, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));

	ReadAxis1.register_map[0] = LIS2DW12_CTRL2;
	ReadAxis1.register_map[1] = ReadAxis1.rst | 0b00001000;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, ReadAxis1.register_map, 2, true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));

	//Accelerometer cutoff filter frequency
	ReadAxis1.register_map[0] = LIS2DW12_CTRL6;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, &ReadAxis1.rst, 1, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));

	ReadAxis1.register_map[0] = LIS2DW12_CTRL6;
	ReadAxis1.register_map[1] = ReadAxis1.rst & 0b00111111;
	ReadAxis1.register_map[1] = ReadAxis1.register_map[1] | 0b01000000;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, ReadAxis1.register_map, 2, true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));

	//Select accelerometer operating modes
	ReadAxis1.register_map[0] = LIS2DW12_CTRL1;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, &ReadAxis1.rst, 1, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));

	ReadAxis1.register_map[0] = LIS2DW12_CTRL1;
	ReadAxis1.register_map[1] = ReadAxis1.rst & 0b11110011;
	ReadAxis1.register_map[1] = ReadAxis1.register_map[1] | 0b00000100;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, ReadAxis1.register_map, 2, true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));

	//Accelerometer data rate selection
	ReadAxis1.register_map[0] = LIS2DW12_CTRL1;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, &ReadAxis1.rst, 1, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));

	ReadAxis1.register_map[0] = LIS2DW12_CTRL1;
	ReadAxis1.register_map[1] = ReadAxis1.rst & 0b00001100;
	ReadAxis1.register_map[1] = ReadAxis1.register_map[1] | 0b00110001;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, ReadAxis1.register_map, 2, true);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));

	//Leitura dos dados crus do acelerômetro 1
	memset(ReadAxis1.data_raw_acceleration, 0x00, 3 * sizeof(int16_t));
	ReadAxis1.register_map[0] = LIS2DW12_OUT_X_L;
	ReadAxis1.status_I2C = I2C_MASTER_Transmit(&I2C_MASTER_0, true, ADD_ACCELW, &ReadAxis1.register_map[0], 1, false);
	while(I2C_MASTER_IsTxBusy(&I2C_MASTER_0));
	ReadAxis1.status_I2C = I2C_MASTER_Receive(&I2C_MASTER_0, true, ADD_ACCELR, ReadAxis1.data_raw_buff, 6, true, true);
	while(I2C_MASTER_IsRxBusy(&I2C_MASTER_0));

	ReadAxis1.data_raw_acceleration[0] = (int16_t)ReadAxis1.data_raw_buff[1];
	ReadAxis1.data_raw_acceleration[0] = (ReadAxis1.data_raw_acceleration[0] * 256) +  (int16_t)ReadAxis1.data_raw_buff[0];
	ReadAxis1.data_raw_acceleration[1] = (int16_t)ReadAxis1.data_raw_buff[3];
	ReadAxis1.data_raw_acceleration[1] = (ReadAxis1.data_raw_acceleration[1] * 256) +  (int16_t)ReadAxis1.data_raw_buff[2];
	ReadAxis1.data_raw_acceleration[2] = (int16_t)ReadAxis1.data_raw_buff[5];
	ReadAxis1.data_raw_acceleration[2] = (ReadAxis1.data_raw_acceleration[2] * 256) +  (int16_t)ReadAxis1.data_raw_buff[4];
}

float lis2dw12_from_fs2_to_mg(int16_t lsb)
{
  return ((float)lsb) * 0.061f;
}
