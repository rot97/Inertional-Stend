#ifndef SPI_HEADER
#define SPI_HEADER

#include <stdint.h>

uint16_t SPI1_Read(uint8_t adr);

void SPI1_Init(void);

void SPI1_Write(uint8_t adr, uint8_t data);

void SPI5_Init(void);

uint8_t SPI5_Read(uint8_t reg);

void SPI5_Write(uint8_t reg, uint8_t data);

#endif
