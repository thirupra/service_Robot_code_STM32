/*
 * MPU6050.c
 *
 *  Created on: Dec 8, 2022
 *      Author: Naveen
 */


#include "MPU6050.h"
#include "usart.h"
#include "stdio.h"

int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;
float GX_1,GY_2,GZ_2;

void MPU6050_Init (void)
{
	uint8_t check;
	uint8_t Data;
HAL_I2C_IsDeviceReady(&hi2c2, MPU6050_ADDR, 2, 100);
	// check device ID WHO_AM_I

	HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);

	if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
		Data = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
		Data = 0x00;
		HAL_I2C_Mem_Write(&hi2c2, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
	}

}
char buff[50];

void MPU6050_Read_Accel (Mpu6050_Data * Data)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/

	Data->AX = Accel_X_RAW/16384.0;
	Data->AY = Accel_Y_RAW/16384.0;
	Data->AZ = Accel_Z_RAW/16384.0;
	HAL_UART_Transmit(&huart1, (uint8_t *)buff, sprintf(buff, "AX = %f\n",Data->AX), 100);
	HAL_UART_Transmit(&huart1, (uint8_t *)buff, sprintf(buff, "AY = %f\n",Data->AY), 100);
	HAL_UART_Transmit(&huart1, (uint8_t *)buff, sprintf(buff, "AZ = %f\n",Data->AZ), 100);


}


void MPU6050_Read_Gyro (Mpu6050_Data * Data)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from GYRO_XOUT_H register

	HAL_I2C_Mem_Read (&hi2c2, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into dps (�/s)
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 131.0
	     for more details check GYRO_CONFIG Register              ****/

	Data->GX = Gyro_X_RAW/131.0;
	Data->GY = Gyro_Y_RAW/131.0;
	Data->GZ = Gyro_Z_RAW/131.0;
	float GX_1,GY_2,GZ_2;
	GX_1 = Data->GX;
	GY_2 = Data->GY;
	GZ_2 = Data->GZ;
	    HAL_UART_Transmit(&huart1, (uint8_t *)buff, sprintf(buff, "GX = %f\n",GX_1), 100);
		HAL_UART_Transmit(&huart1, (uint8_t *)buff, sprintf(buff, "GY = %f\n",GY_2), 100);
		HAL_UART_Transmit(&huart1, (uint8_t *)buff, sprintf(buff, "GZ = %f\n",GZ_2), 100);
}

