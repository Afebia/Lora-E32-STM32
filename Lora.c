/*
 * Lora.c
 *
 *  Created on: Apr 3, 2024
 *      Author: berat
 */

#include "Lora_STM32.h"
#include "BNO055_STM32.h"
#include "BME280_STM32.h"


extern float Heading,Pitch,Roll,Temperature,Humidity,Pressure;


void LORA_MODE(mode_t mode){
	switch (mode) {
		case NORMALL:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0); //M1 LOW
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0); //M0 LOW
			break;
		case WAKEUPL:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 0); //M1 LOW
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1); //M0 HIGH
			break;
		case PWRSAVEL:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1); //M1 HIGH
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 0); //M0 LOW
			break;
		case SLEEPL:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, 1); //M1 HIGH
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, 1); //M0 HIGH
			break;

	}
}

//Changing parameters(ADDH,ADDL,PORTMODE,BAUDRATE,AIRRATE,CHANNEL,OPTIONS) in SLEEP MODE
void LORA_SET_PARAMETER(uint8_t addh, uint8_t addl, speed_t speed,uint8_t chan,option_t option){

	uint8_t Parameters[6] = {0xC0,addh,addl,speed,chan,option};

	LORA_MODE(SLEEPL); // firstly we put lora into sleep mode
	HAL_Delay(100);
	HAL_UART_Transmit(&huart3, Parameters, sizeof(Parameters), HAL_MAX_DELAY); // than we send 6bytes to lora.
																			   // First byte is 0xC0, then ADDH,ADDL,SLEEP,CHANNEL,OPTIONS
	HAL_Delay(1000);


}

void LORA_RECEIVE(void)
{
	uint8_t Data[21];

	float temperature;
	float humidity;
	float pressure;
	float heading, roll, pitch;


	HAL_UART_Receive(&huart3, Data, sizeof(Data), HAL_MAX_DELAY);
    memcpy(&heading, &Data[0], sizeof(float));
    memcpy(&roll, &Data[4], sizeof(float));
    memcpy(&pitch, &Data[8], sizeof(float));
    memcpy(&temperature, &Data[12], sizeof(float));
    memcpy(&pressure, &Data[16], sizeof(float));
    memcpy(&humidity, &Data[20], sizeof(float));


    printf("Received Data:\n");
    printf("Temperature = %f\t", temperature);
    printf("Pressure = %f\t", pressure);
    printf("Humidity = %f\t\n", humidity);
    printf("Heading = %f\t", heading);
    printf("Roll = %f\t", roll);
    printf("Pitch = %f\t\n", pitch);


}

//Transmit datas
void Transmit_Data(uint8_t addh,uint8_t addl,uint8_t chan){


	uint8_t SEND_DATA1[24];

	//We write receiver's address and channel in the first three byte of array
	SEND_DATA1[0] = addh;
	SEND_DATA1[1] = addl;
	SEND_DATA1[2] = chan;

	memcpy(&SEND_DATA1[3], &Heading, sizeof(float));
	memcpy(&SEND_DATA1[7], &Roll, sizeof(float));
	memcpy(&SEND_DATA1[11], &Pitch, sizeof(float));
	memcpy(&SEND_DATA1[15], &Temperature, sizeof(float));
	memcpy(&SEND_DATA1[19], &Pressure, sizeof(float));
	memcpy(&SEND_DATA1[23], &Humidity, sizeof(float));

	HAL_UART_Transmit(&huart3, (uint8_t*)SEND_DATA1, sizeof(SEND_DATA1), HAL_MAX_DELAY); // Then we send array to the lora

}
