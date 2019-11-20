#include "stm32f429xx.h"

#define ADIS_ID					0x406A
#define PROD_ID					0x7E

#define BURST_LENGTH  	14

#define SYS_E_FLAG 			0x08
#define TEMP_OUT				0x0E
#define X_GYRO_LOW			0x10
#define X_GYRO_OUT			0x12
#define Y_GYRO_LOW			0x14
#define Y_GYRO_OUT			0x16
#define Z_GYRO_LOW			0x18
#define Z_GYRO_OUT			0x1A
#define X_ACCL_LOW			0x1C
#define X_ACCL_OUT			0x1E
#define Y_ACCL_LOW			0x20
#define Y_ACCL_OUT			0x22
#define Z_ACCL_LOW			0x24
#define Z_ACCL_OUT			0x26

#define X_DELTANG_LOW		0x40
#define X_DELTANG_OUT		0x42
#define Y_DELTANG_LOW		0x44
#define Y_DELTANG_OUT		0x46
#define Z_DELTANG_LOW		0x48
#define Z_DELTANG_OUT		0x4A

#define X_DELTVEL_LOW		0x4C
#define X_DELTVEL_OUT		0x4E
#define Y_DELTVEL_LOW		0x50
#define Y_DELTVEL_OUT		0x52
#define Z_DELTVEL_LOW		0x54
#define Z_DELTVEL_OUT		0x56

#define GLOB_CMD				0x02
#define RESET_REG				0x80

#define DATA_CNT				0x04

void ADIS_Burst(int16_t*);

int ADIS_Init(void);
