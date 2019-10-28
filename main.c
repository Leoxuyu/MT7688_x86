/*
 * main.c
 *
 *  Created on: 2019年10月21日
 *      Author: work
 */

#include <stdio.h>
#include "dlt645.h"
#include "dlt645_port_linux.h"

uint8_t add[6]={0,0,0,0,0,1};
dlt645_t DLT645;

int main(void)
{
	uint8_t read_buf[4];
	DLT645_Port_Init_Debug(&DLT645,add);
    //if(dlt645_read_data(&dlt645,DLT645_1997_READ_TEST_CODE,read_buf,DLT645_1997) > 0) //1997采集测试
    if(dlt645_read_data(&DLT645,0x02010100,read_buf,DLT645_2007) > 0)  //2007采集测试
    {
        printf("读取成功,A相电压值为: %.2f \r\n",*(float *)read_buf);
    }
    else
    {
        printf("读取失败\r\n");
    }
	printf("hello!\n");
	return 0;
}
