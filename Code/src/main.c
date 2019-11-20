
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
#include "SPI.h"

#include <stdio.h>

static int GET_DATA = 0;

void TIM10_Init(){
	RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
	
	TIM10->PSC = 180000-1;
	TIM10->ARR = 200;
	TIM10->DIER |= TIM_DIER_UIE;
	TIM10->CR1 |= TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
}




int main(){

	RCC_Init();
	MCO_Init();
	LTDC_Init();
	TIM10_Init();
	SPI1_Init();
	
	
	
	volatile uint16_t x =0;
	
	uint16_t ID = SPI1_Read(0x7E);
	char str[25];
	//sprintf(str, "%X\n", ID);
	
	


	while(1){
		if(GET_DATA){
			k_fill(DISPLAY, COLOR_WHITE);
			ID = SPI1_Read(0x7E);
			sprintf(str, "ID=%X\n", ID);
			k_print_string(DISPLAY, str, 0, 0, 2, COLOR_BLUE);
			int16_t TEMP_out = SPI1_Read(0x0E);
			double tempature = 25 + TEMP_out / 70.0;
			sprintf(str, "t0=%5.2f\n", tempature);
			k_print_string(DISPLAY, str, 0, 20, 2, COLOR_BLUE);
		
			//Считываем показания гироскопа
			int16_t X_GYRO = SPI1_Read(X_GYRO_OUT);
			int16_t Y_GYRO = SPI1_Read(Y_GYRO_OUT);
			int16_t Z_GYRO = SPI1_Read(Z_GYRO_OUT);
		
			//Считываем показания акселирометра
			int16_t X_ACCL = SPI1_Read(X_ACCL_OUT);
			int16_t Y_ACCL = SPI1_Read(Y_ACCL_OUT);
			int16_t Z_ACCL = SPI1_Read(Z_ACCL_OUT);
		
			//Считываем показания углов
			int16_t X_DELTANG = SPI1_Read(X_DELTANG_OUT);
			int16_t Y_DELTANG = SPI1_Read(Y_DELTANG_OUT);
			int16_t Z_DELTANG = SPI1_Read(Z_DELTANG_OUT);
			
			//Считываем показания скорости
			int16_t X_DELTVEL = SPI1_Read(X_DELTVEL_OUT);
			int16_t Y_DELTVEL = SPI1_Read(Y_DELTVEL_OUT);
			int16_t Z_DELTVEL = SPI1_Read(Z_DELTVEL_OUT);
			
			double x_gir = X_GYRO * 0.005;
			double y_gir = Y_GYRO * 0.005;
			double z_gir = Z_GYRO * 0.005;
			sprintf(str, "vx=%7.3f\n", x_gir);
			k_print_string(DISPLAY, str, 0, 40, 2, COLOR_BLUE);
			sprintf(str, "vy=%7.3f\n", y_gir);
			k_print_string(DISPLAY, str, 0, 60, 2, COLOR_BLUE);
			sprintf(str, "vz=%7.3f\n", z_gir);
			k_print_string(DISPLAY, str, 0, 80, 2, COLOR_BLUE);
			
			
			double x_acc = X_ACCL  * 0.0005;
			double y_acc = Y_ACCL  * 0.0005;
			double z_acc = Z_ACCL  * 0.0005;
			sprintf(str, "ax=%7.3f\n", x_acc);
			k_print_string(DISPLAY, str, 120, 40, 2, COLOR_BLUE);
			sprintf(str, "ay=%7.3f\n", y_acc);
			k_print_string(DISPLAY, str, 120, 60, 2, COLOR_BLUE);
			sprintf(str, "az=%7.3f\n", z_acc);
			k_print_string(DISPLAY, str, 120, 80, 2, COLOR_BLUE);
			
		
			double x_del = X_DELTANG * 0.0022;
			double y_del = Y_DELTANG * 0.0022;
			double z_del = Z_DELTANG * 0.0022;
			
			sprintf(str, "dax=%7.3f\n", x_del);
			k_print_string(DISPLAY, str, 0, 120, 2, COLOR_BLUE);
			sprintf(str, "day=%7.3f\n", y_del);
			k_print_string(DISPLAY, str, 0, 140, 2, COLOR_BLUE);
			sprintf(str, "daz=%7.3f\n", z_del);
			k_print_string(DISPLAY, str, 0, 160, 2, COLOR_BLUE);
			
			
			double x_dvel = X_DELTVEL * 0.006104;
			double y_dvel = Y_DELTVEL * 0.006104;
			double z_dvel = Z_DELTVEL * 0.006104;
			sprintf(str, "dvx=%7.3f\n", x_dvel);
			k_print_string(DISPLAY, str, 0, 200, 2, COLOR_BLUE);
			sprintf(str, "dvy=%7.3f\n", y_dvel);
			k_print_string(DISPLAY, str, 0, 220, 2, COLOR_BLUE);
			sprintf(str, "dvz=%7.3f\n", z_dvel);
			k_print_string(DISPLAY, str, 0, 240, 2, COLOR_BLUE);
			GET_DATA = 0;
		}
	}
}

void TIM1_UP_TIM10_IRQHandler(void){
	TIM10->SR &= ~TIM_SR_UIF;
	GET_DATA = 1;
}
