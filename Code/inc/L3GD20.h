#include <stdint.h>

#ifndef L3GD20_Header
#define L3GD20_Header

#define WHO_AM_I		0x0F
#define L3GD20_ID		0xD4

#define OUT_TEMP		0x26
#define OUT_X_L			0x28
#define OUT_X_H			0x29
#define OUT_Y_L			0x2A
#define OUT_Y_H			0x2B
#define OUT_Z_L			0x2C
#define OUT_Z_H			0x2D

int L3GD20_Init(void);

void L3GD20_Burst(int8_t* d);

uint8_t L3GD20_Read(uint8_t reg);

void L3GD20_Write(uint8_t reg, uint8_t data);

#endif

