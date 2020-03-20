#include "flash.h"

extern SPI_HandleTypeDef hspi1;

void read(uint32_t address,uint8_t* data,uint16_t size){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
	uint8_t _data[4];
	_data[0]=0x03;
	_data[1]=(address>>16)&0xFF;
	_data[2]=(address>>8)&0xFF;
	_data[3]=(address)&0xFF;
	HAL_SPI_Transmit(&hspi1,_data,4,0xFFFF);
	HAL_SPI_Receive(&hspi1,data,size,0xFFFF);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
}

uint8_t read_status_register(){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
	uint8_t _data=0x05;
	uint8_t status;
	HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
	HAL_SPI_Receive(&hspi1,&status,1,0xFFFF);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
	return status;
}

void write_status_register(uint8_t data){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
	uint8_t _data=0x50;
	HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
	_data = 0x01;
	HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
	HAL_SPI_Transmit(&hspi1,&data,1,0xFFFF);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
}

void write_byte( uint32_t address, uint8_t byte){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
	uint8_t data[5]={0x06,(address>>16)&0xFF,(address>>8)&0xFF,(address)&0xFF,byte};
	HAL_SPI_Transmit(&hspi1,data,1,0xFFFF);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
	data[0]=0x02;
	HAL_SPI_Transmit(&hspi1,data,5,0xFFFF);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
	HAL_Delay(1);
}

void write_array(uint32_t address,uint8_t* data,uint16_t size){
	for(uint16_t i=0;i<size;i++){
		write_byte(address+i,data[i]);
	}
}	

void full_clear(){
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_RESET);
	uint8_t _data=0x06;
	HAL_SPI_Transmit(&hspi1,&_data,1,0xFFFF);
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_7,GPIO_PIN_SET);
}
