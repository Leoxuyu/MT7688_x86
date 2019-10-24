/*
 * TF_Sample.c
 *
 *  Created on: 2019年10月24日
 *      Author: work
 */

#include <stdio.h>

#include <stdio.h>
#include <string.h>
#include "TinyFrame.h"

TinyFrame *sample_tf;
bool do_corrupt = false;

uint8_t recv_buff[0xFF];
uint8_t recv_count=0;

void recv_buff_clean(void)
{
    recv_count=0;
    memset(recv_buff,0x00,sizeof(recv_buff));
}

//	数据打印
void DumpFrame(const uint8_t *buff, size_t len)
{
	int i;
	printf("[ ");
	recv_buff_clean();
	for(i=0;i<len;i++)
	{
		recv_count++;
		recv_buff[i]=*(uint8_t*)(buff+i);
		printf("0x%02X ",*(uint8_t*)(buff+i));
	}
	printf("]\n");
}

//	数据发送底层，可自定义数据发送底层
void TF_WriteImpl(TinyFrame *tf, const uint8_t *buff, uint32_t len)
{
	uint8_t *xbuff = (uint8_t *)buff;
	DumpFrame(xbuff, len);
}

/** 一个普通监听器函数的示例 **/
TF_Result myListener(TinyFrame *tf, TF_Msg *msg)
{
	printf("Generic Listener triggered !\n");
    return TF_STAY;
}

/** 一个ID监听器函数的示例 **/
TF_Result testIdListener(TinyFrame *tf, TF_Msg *msg)
{
    printf("ID Listener triggered !\n");
    return TF_CLOSE;
}

void TF_Sample_Test(void)
{
    TF_Msg msg;

	//设置TinyFrame库
    sample_tf = TF_Init(TF_MASTER); // 1 = master, 0 = slave
    TF_AddGenericListener(sample_tf, myListener);

    TF_ClearMsg(&msg);
    msg.type = 0x22;
    msg.data = (char *) "Hello TinyFrame";
    msg.len = 16;
    TF_Send(sample_tf, &msg);
    TF_Accept(sample_tf, recv_buff, recv_count);

    // test checksums are tested
    do_corrupt = true;
    msg.type = 0x44;
    msg.data = (char *) "Hello2";
    msg.len = 7;
    TF_Send(sample_tf, &msg);
    TF_Accept(sample_tf, recv_buff, recv_count);

}

























