#include "ADIS.h"
#include "SPI.h"

#include <stdio.h>

int ADIS_Init(){
		SPI1_Init();
		uint16_t ID = SPI1_Read(PROD_ID);
		if(ID != ADIS_ID) return 16;
		return 0;
}

void ADIS_Burst(int16_t* d){
	d[0] = SPI1_Read(0x0E);
	d[1] = SPI1_Read(X_GYRO_OUT);
	d[2] = SPI1_Read(Y_GYRO_OUT);
	d[3] = SPI1_Read(Z_GYRO_OUT);
	d[4] = SPI1_Read(X_ACCL_OUT);
	d[5] = SPI1_Read(Y_ACCL_OUT);
	d[6] = SPI1_Read(Z_ACCL_OUT);
}
