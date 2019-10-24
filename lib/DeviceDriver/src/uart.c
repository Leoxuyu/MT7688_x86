/*
 * uart.c
 *
 *  Created on: 2019年10月21日
 *      Author: work
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <asm/termios.h>
#include "uart.h"

//设置波特率
void UART_SetBaudRate(SerialConfigure_t *cfg,uint32_t BaudRate)
{
	cfg->baud_rate=BaudRate;
}

//设置数据位
void UART_SetDataBits(SerialConfigure_t *cfg,uint32_t DataBits)
{
	cfg->data_bits=DataBits;
}




//
void UART_RX_FIFO_Init(uint32_t size)
{

}

void UART_TX_FIFO_Init(uint32_t size)
{

}




int UART_Init(char * ttyName)
{
	int fd;
	fd = open(ttyName, O_RDWR | O_NOCTTY );
	return fd;
}




