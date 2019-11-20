#include "stm32f429xx.h"
#include "ADXL345.h"
#include "SPI.h"

#include <stdint.h>

uint8_t ADXL345_Read(uint8_t reg){
	GPIOC->BSRR = GPIO_BSRR_BR5;
	uint8_t data = SPI5_Read(reg);
	GPIOC->BSRR = GPIO_BSRR_BS5;
	return data;
}

void ADXL345_Write(uint8_t reg, uint8_t data){
	GPIOC->BSRR = GPIO_BSRR_BR5;
	SPI5_Write(reg, data);
	GPIOC->BSRR = GPIO_BSRR_BS5;
}


int ADXL345_Init(){
	SPI5_Init();
	
	//CS
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODE5_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE5_1;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR5_1;
	GPIOC->BSRR = GPIO_BSRR_BS5;
	
	ADXL345_Read(0x00);
	uint8_t ID = ADXL345_Read(DEVID);
	if(ID != ADXL345_ID) return 1;
	
	ADXL345_Write(0x2D, 0x08);
	ADXL345_Write(0x31, 0x01);
	
	return 0;
}

void ADXL345_Burst(int8_t* d){
	d[1] = ADXL345_Read(DATAX0);
	d[2] = ADXL345_Read(DATAX1);
	d[3] = ADXL345_Read(DATAY0);
	d[4] = ADXL345_Read(DATAY1);
	d[5] = ADXL345_Read(DATAZ0);
	d[6] = ADXL345_Read(DATAZ1);
}
