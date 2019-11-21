#include <stdint.h>

#ifndef ADXL345_Header
#define ADXL345_Header

#define DEVID				0x00
#define ADXL345_ID	0xE5

#define DATAX0			0x32
#define DATAX1			0x33
#define DATAY0			0x34
#define DATAY1			0x35
#define DATAZ0			0x36
#define DATAZ1			0x37

int ADXL345_Init(void);

void ADXL345_Burst(int8_t* d);

uint8_t ADXL345_Read(uint8_t reg);

void ADXL345_Write(uint8_t reg, uint8_t data);

#endif

