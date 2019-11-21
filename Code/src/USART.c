#include "stm32f429xx.h"
#include "USART.h"

void USART6_Init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
	
	//RX
	GPIOG->MODER |= GPIO_MODER_MODE9_1;
	GPIOG->MODER &= ~GPIO_MODER_MODE9_0;
	GPIOG->AFR[1] &=  ~GPIO_AFRH_AFSEL9_Msk;
	GPIOG->AFR[1] |=  8 << GPIO_AFRH_AFSEL9_Pos;
	GPIOG->OTYPER &= ~GPIO_OTYPER_OT9;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1 | GPIO_OSPEEDER_OSPEEDR9_0;
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPD9_Msk;
	
	//TX
	GPIOG->MODER |= GPIO_MODER_MODE14_1;
	GPIOG->MODER &= ~GPIO_MODER_MODE14_0;
	GPIOG->AFR[1] &=  ~GPIO_AFRH_AFSEL14_Msk;
	GPIOG->AFR[1] |=  8 << GPIO_AFRH_AFSEL14_Pos;
	GPIOG->OTYPER &= ~GPIO_OTYPER_OT14;
	GPIOG->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR14_1 | GPIO_OSPEEDER_OSPEEDR14_0;
	GPIOG->PUPDR &= ~GPIO_PUPDR_PUPD14_Msk;
	
	//USART6->BRR = 0x249F;
	USART6->BRR = 0x30D; 	
	USART6->CR1 |= USART_CR1_TE; 
	USART6->CR1 |= USART_CR1_RE;
	USART6->CR1 |= USART_CR1_UE;
	
	USART6->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART6_IRQn);
}

void USART6_sent(char c){
	while(!(USART6->SR & USART_SR_TC));
	USART6->DR = c;
}

void USART6_sentstr(char* str){
	uint8_t i = 0;
	do{
		USART6_sent(str[i]);
	}	while(str[i++] != '\n');
}
