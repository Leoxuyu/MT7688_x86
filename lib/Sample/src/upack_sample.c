/*
 * upack_sample.c
 *
 *  Created on: 2019年10月24日
 *      Author: work
 */

#include <stdio.h>

#include "upack_sample.h"
#include "upacker.h"

upacker_inst msg_packer;

uint8_t test_count=0;
uint8_t test_package[6];



void data_send(uint8_t *d, uint16_t size)       //发送数据
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("0x%02X ",*(uint8_t *)(d+i));
		test_package[test_count]=*(uint8_t *)(d+i);
		test_count++;
	}
}


void handle_callback(uint8_t *d, uint16_t size) //解包成功后的处理回调
{
	printf("\nunpack OK!\n");
}


void upack_test(void)
{
	uint8_t buff[2];
	upacker_init(&msg_packer, handle_callback, data_send);
    buff[0] = 0x40;
    buff[1] = 0x45;
    upacker_pack(&msg_packer, (uint8_t *)buff, 2);
    upacker_unpack(&msg_packer, (uint8_t *)test_package,6);
}
