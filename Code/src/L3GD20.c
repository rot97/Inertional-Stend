#include "stm32f429xx.h"
#include "L3GD20.h"
#include "SPI.h"

#include <stdint.h>

int L3GD20_Init(){
	SPI5_Init();
	SPI5_Read(0x00);
	uint8_t ID = SPI5_Read(WHO_AM_I);
	if(ID != L3GD20_ID) return 1;
	return 0;
}

