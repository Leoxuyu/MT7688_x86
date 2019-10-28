/*
 * dlt645_port_linux.h
 *
 *  Created on: 2019年10月28日
 *      Author: work
 */

#ifndef LIB_DLT645_INC_DLT645_PORT_LINUX_H_
#define LIB_DLT645_INC_DLT645_PORT_LINUX_H_

typedef enum DLT645_FLAG
{
	FLAG_IDLE=0,
	TX,
	RX
}DLT645_FLAG_t;

//DLT 645硬件拓展结构体
typedef struct
{
	DLT645_FLAG_t Flag;		//用于串口接收的信号量
    uint32_t Timeout;		//字节间的超时时间
} DLT645_PORT_t;

int DLT645_Write(dlt645_t *ctx);
int DLT645_Read(dlt645_t *ctx,uint16_t len);

int DLT645_Write_Debug(dlt645_t *ctx);
int DLT645_Read_Debug(dlt645_t *ctx,uint16_t len);

void DLT645_Port_Init_Debug(dlt645_t *ctx,uint8_t *ADD);
void DLT645_Port_Init(dlt645_t *ctx,uint8_t *ADD);


#endif /* LIB_DLT645_INC_DLT645_PORT_LINUX_H_ */
