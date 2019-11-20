#include "stm32f429xx.h"
#include "L3GD20.h"
#include "SPI.h"

#include <stdint.h>

int L3GD20_Init(){
	SPI5_Init();
	SPI5_Read(0x00);
	uint8_t ID = SPI5_Read(WHO_AM_I);
	if(ID != L3GD20_ID) return 1;
	
	SPI5_Write(0x20, 0x0F);
	SPI5_Write(0x23, 0x30);
	volatile uint8_t t = SPI5_Read(0x20);
	
	return 0;
}

void L3GD20_Burst(int8_t* d){
	d[0] = SPI5_Read(OUT_TEMP);
	d[1] = SPI5_Read(OUT_X_L);
	d[2] = SPI5_Read(OUT_X_H);
	d[3] = SPI5_Read(OUT_Y_L);
	d[4] = SPI5_Read(OUT_Y_H);
	d[5] = SPI5_Read(OUT_Z_L);
	d[6] = SPI5_Read(OUT_Z_H);
}

