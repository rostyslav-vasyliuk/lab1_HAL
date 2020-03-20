#ifndef FLASH_H
#define FLASH_H


#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common


void read(uint32_t address,uint8_t* data,uint16_t size);
uint8_t read_status_register(void);
void write_status_register(uint8_t data);
void write_byte( uint32_t address, uint8_t byte);
void write_array(uint32_t address,uint8_t* data,uint16_t size);	
void full_clear(void);

#endif
