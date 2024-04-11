/*
 * Lora_STM32.h
 *
 *  Created on: Apr 3, 2024
 *      Author: berat
 */

#ifndef INC_LORA_STM32_H_
#define INC_LORA_STM32_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "string.h"

extern UART_HandleTypeDef huart3;

//-------------------------------------MODE

typedef enum{
 NORMALL  = 0,
 WAKEUPL  = 1,
 PWRSAVEL = 2,
 SLEEPL   = 3

}mode_t;
//-------------------------------------MODE

//-------------------------------------ADDRESS PARAMETER
#define ADDH 0x00
#define ADDL 0x17
//-------------------------------------ADDRESS PARAMETER

//-------------------------------------CHANNEL PARAMETER
#define CHAN 0x00
//-------------------------------------CHANNEL PARAMETER

//-------------------------------------SPEED PARAMETER
typedef enum{  //BNO055 AXIS REMAP
	SER_PORT_MODE_8N1 = (0x00<<0x06),
	SER_PORT_MODE_8O1 = (0x01 << 0x06),
	SER_PORT_MODE_8E1 = (0x02 << 0x06),

	BAUD_RATE_1200   = (0x00 <<0x03),
	BAUD_RATE_2400   = (0x01 <<0x03),
	BAUD_RATE_4800   = (0x02 <<0x03),
	BAUD_RATE_9600   = (0x03 <<0x03),
	BAUD_RATE_19200  = (0x04 <<0x03),
	BAUD_RATE_38400  = (0x05 <<0x03),
	BAUD_RATE_57600  = (0x06 <<0x03),
	BAUD_RATE_115200 = (0x07 <<0x03),

	AIR_RATE_03K  = (0x00 << 0x00),
	AIR_RATE_12K  = (0x01 << 0x00),
	AIR_RATE_24K  = (0x02 << 0x00),
	AIR_RATE_48K  = (0x03 << 0x00),
	AIR_RATE_96K  = (0x04 << 0x00),
	AIR_RATE_192K = (0x05 << 0x00)

}speed_t;
//-------------------------------------SPEED PARAMETER

//-------------------------------------OPTION PARAMETER
typedef enum{  //BNO055 AXIS REMAP
	  TRANS_MODE = (0x00 << 0x07),
	  FIXED_MODE = (0x01 << 0x07),

	  PUSH_PULL    = (0x01 << 0x06),
	  OPEN_CIRCUIT = (0x00 << 0x06),

	  WAKEUP_250  = (0x00 << 0x03),
	  WAKEUP_500  = (0x01 << 0x03),
	  WAKEUP_750  = (0x02 << 0x03),
	  WAKEUP_1000 = (0x03 << 0x03),
	  WAKEUP_1250 = (0x04 << 0x03),
	  WAKEUP_1500 = (0x05 << 0x03),
	  WAKEUP_1750 = (0x06 << 0x03),
	  WAKEUP_2000 = (0x07 << 0x03),

	  FEC_OFF = (0x00 << 0x02),
	  FEC_ON  = (0x01 << 0x02),

	  TRANSPWR_30dBm = (0x00 << 0x00),
	  TRANSPWR_27dBm = (0x01 << 0x00),
	  TRANSPWR_24dBm = (0x02 << 0x00),
	  TRANSPWR_21dBm = (0x03 << 0x00)

}option_t;
//-------------------------------------OPTION PARAMETER

//Function define
void LORA_MODE(mode_t mode);
void LORA_SET_PARAMETER(uint8_t addh, uint8_t addl, uint8_t speed,uint8_t chan,uint8_t option);


void LORA_RECEIVE(void);
void Transmit_Data(uint8_t addl,uint8_t addh,uint8_t chan);

#endif /* INC_LORA_STM32_H_ */
