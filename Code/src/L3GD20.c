#include "stm32f429xx.h"
#include "L3GD20.h"
#include "SPI.h"

#include <stdint.h>

uint8_t L3GD20_Read(uint8_t reg){
	GPIOC->BSRR = GPIO_BSRR_BR1;
	uint8_t data = SPI5_Read(reg);
	GPIOC->BSRR = GPIO_BSRR_BS1;
	return data;
}

void L3GD20_Write(uint8_t reg, uint8_t data){
	GPIOC->BSRR = GPIO_BSRR_BR1;
	SPI5_Write(reg, data);
	GPIOC->BSRR = GPIO_BSRR_BS1;
}


int L3GD20_Init(){
	SPI5_Init();
	
	//CS
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	GPIOC->MODER |= GPIO_MODER_MODE1_0;
	GPIOC->MODER &= ~GPIO_MODER_MODE1_1;
	GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR1_0 | GPIO_OSPEEDER_OSPEEDR1_1;
	GPIOC->BSRR = GPIO_BSRR_BS1;
	
	L3GD20_Read(0x00);
	uint8_t ID = L3GD20_Read(WHO_AM_I);
	if(ID != L3GD20_ID) return 1;
	
	L3GD20_Write(0x20, 0x0F);
	L3GD20_Write(0x23, 0x30);
	
	return 0;
}

void L3GD20_Burst(int8_t* d){
	d[0] = L3GD20_Read(OUT_TEMP);
	d[1] = L3GD20_Read(OUT_X_L);
	d[2] = L3GD20_Read(OUT_X_H);
	d[3] = L3GD20_Read(OUT_Y_L);
	d[4] = L3GD20_Read(OUT_Y_H);
	d[5] = L3GD20_Read(OUT_Z_L);
	d[6] = L3GD20_Read(OUT_Z_H);
}

