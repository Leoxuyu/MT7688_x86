/*
 * dlt645_port_linux.c
 *
 *  Created on: 2019年10月28日
 *      Author: work
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "dlt645.h"
#include "dlt645_port_linux.h"

static DLT645_PORT_t DLT645_PORT;

//DLT645 默认配置
void DLT645_Config_Default(DLT645_PORT_t *dlt645)
{
	dlt645->Flag=FLAG_IDLE;
	dlt645->Timeout=500;
}

int DLT645_Write(dlt645_t *ctx)
{
	return 0;
}

int DLT645_Read(dlt645_t *ctx,uint16_t len)
{
	return 0;
}

int DLT645_Write_Debug(dlt645_t *ctx)
{
	int i;
	printf("DLT645 Message Len:%d;\n",ctx->DataLenToSend);
	printf("DLT645 Debug:[");
	for (i=0;i<ctx->DataLenToSend;i++)
	{
		printf("0x%02X ",*((ctx->MessageToSend)+i));
	}
	printf("]\n");
	return 0;
}

int DLT645_Read_Debug(dlt645_t *ctx,uint16_t len)
{
	uint8_t sample[16]={0x68,0x00,0x90,0x78,0x56,0x34,0x12,0x68,0x11,0x04,0x33,0x33,0x33,0x33,0x55,0x16};
//	memcpy(msg,sample,sizeof(sample));
	return sizeof(sample);
}


//初始化DLT645协议,调试模式
void DLT645_Port_Init_Debug(dlt645_t *ctx,uint8_t *ADD)
{
	memcpy(ctx->addr,ADD,6);
	ctx->debug=1;
	ctx->read=DLT645_Write_Debug;
	ctx->write=DLT645_Read_Debug;
	ctx->port_data=(void *) &DLT645_PORT;
}

//初始化DLT645协议,普通模式
void DLT645_Port_Init(dlt645_t *ctx,uint8_t *ADD)
{
	memcpy(ctx->addr,ADD,6);
	ctx->debug=0;
	ctx->read=DLT645_Write;
	ctx->write=DLT645_Read;
	ctx->port_data=(void *) &DLT645_PORT;
}
