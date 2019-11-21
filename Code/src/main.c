
/*
ADIS-SPI1
SKC - B3
MISO - B4
MOSI - B5
CS - C4



AHB - 180
APB2 - 90
APB1 - 45

*/


#include "stm32f429xx.h"

#include "RCC.h"
#include "LTDC.h"
#include "display.h"
#include "ADIS.h"
#include "L3GD20.h"
#include "ADXL345.h"
#include "SPI.h"
#include "USART.h"

#include <stdio.h>

void ADIS_View(void);
void L3GD20_View(void);
void ADXL345_View(void);

static int GET_DATA = 0;
char ADIS_Res[125];
char L3GD20_Res[125];
char ADXL345_Res[125];

void TIM10_Init(){
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
	
	TIM10->PSC = 18000-1;
	TIM10->ARR = 200-1;
	TIM10->DIER |= TIM_DIER_UIE;
	TIM10->CR1 |= TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}

void ERROR(){
	while(1);
}


int main(){

	RCC_Init();
	MCO_Init();
	LTDC_Init();
	USART6_Init();
	
	USART6_sentstr("Hello\r\n");
	
	if(ADIS_Init()) ERROR();
	if(L3GD20_Init()) ERROR();
	if(ADXL345_Init()) ERROR();
	
	TIM10_Init();

	while(1){
		if(GET_DATA){
			k_fill(DISPLAY, COLOR_WHITE);
			ADIS_View();
			L3GD20_View();
			ADXL345_View();
			USART6_sentstr("ADIS:\r\n");
			USART6_sentstr(ADIS_Res);
			USART6_sentstr("L3GD20:\r\n");
			USART6_sentstr(L3GD20_Res);
			USART6_sentstr("ADXL345:\r\n");
			USART6_sentstr(ADXL345_Res);
			GET_DATA = 0;
		}
	}
}

void ADIS_View(){
	int16_t BURST[7];
	char str[15];
	ADIS_Burst(BURST);
	k_print_string(DISPLAY, "ADIS:\n", 0, 0, 2, COLOR_BLUE);
	
	double tempature = 25 + BURST[0] / 70.0;
	sprintf(str, "t0=%5.2f\n", tempature);
	k_print_string(DISPLAY, str, 0, 20, 2, COLOR_BLUE);
			
	double x_gir = BURST[1] * 0.005;
	double y_gir = BURST[2] * 0.005;
	double z_gir = BURST[3] * 0.005;
	sprintf(str, "vx=%7.3f\n", x_gir);
	k_print_string(DISPLAY, str, 0, 40, 2, COLOR_BLUE);
	sprintf(str, "vy=%7.3f\n", y_gir);
	k_print_string(DISPLAY, str, 0, 60, 2, COLOR_BLUE);
	sprintf(str, "vz=%7.3f\n", z_gir);
	k_print_string(DISPLAY, str, 0, 80, 2, COLOR_BLUE);
		
	double x_acc = BURST[4]  * 0.0005;
	double y_acc = BURST[5] * 0.0005;
	double z_acc = BURST[6] * 0.0005;
	sprintf(str, "ax=%7.3f\n", x_acc);
	k_print_string(DISPLAY, str, 120, 40, 2, COLOR_BLUE);
	sprintf(str, "ay=%7.3f\n", y_acc);
	k_print_string(DISPLAY, str, 120, 60, 2, COLOR_BLUE);
	sprintf(str, "az=%7.3f\n", z_acc);
	k_print_string(DISPLAY, str, 120, 80, 2, COLOR_BLUE);
	
	sprintf(ADIS_Res, "vx = %7.3f vy = %7.3f vz = %7.3f ax = %7.3f ay = %7.3f az = %7.3f\r\n", x_gir, y_gir, z_gir, x_acc, y_acc, z_acc);
}

void L3GD20_View(){
	int8_t BURST[7];
	char str[25];
	L3GD20_Burst(BURST);
	double x_gir = ((BURST[2] << 8)|BURST[1])*0.07;
	double y_gir = ((BURST[4] << 8)|BURST[3])*0.07;
	double z_gir = ((BURST[6] << 8)|BURST[5])*0.07;
	sprintf(str, "vx=%7.3f\n", x_gir);
	k_print_string(DISPLAY, str, 0, 120, 2, COLOR_BLUE);
	sprintf(str, "vy=%7.3f\n", y_gir);
	k_print_string(DISPLAY, str, 0, 140, 2, COLOR_BLUE);
	sprintf(str, "vz=%7.3f\n", z_gir);
	k_print_string(DISPLAY, str, 0, 160, 2, COLOR_BLUE);
	sprintf(L3GD20_Res, "vx = %7.3f vy = %7.3f vz = %7.3f\r\n", x_gir, y_gir, z_gir);
}

void ADXL345_View(){
	int8_t BURST[7];
	char str[25];
	ADXL345_Burst(BURST);
	double x_acc = ((BURST[2] << 8)|BURST[1])*0.0078;
	double y_acc = ((BURST[4] << 8)|BURST[3])*0.0078;
	double z_acc = ((BURST[6] << 8)|BURST[5])*0.0078;
	sprintf(str, "vx=%7.3f\n", x_acc);
	k_print_string(DISPLAY, str, 120, 120, 2, COLOR_BLUE);
	sprintf(str, "vy=%7.3f\n", y_acc);
	k_print_string(DISPLAY, str, 120, 140, 2, COLOR_BLUE);
	sprintf(str, "vz=%7.3f\n", z_acc);
	k_print_string(DISPLAY, str, 120, 160, 2, COLOR_BLUE);
	sprintf(ADXL345_Res, "ax = %7.3f ay = %7.3f az = %7.3f\r\n", x_acc, y_acc, z_acc);
}

void TIM1_UP_TIM10_IRQHandler(void){
	TIM10->SR &= ~TIM_SR_UIF;
	GET_DATA = 1;
}
