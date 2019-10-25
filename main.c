/*
 * main.c
 *
 *  Created on: 2019年10月21日
 *      Author: work
 */

#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include "amessage.pb-c.h"
#include "protobuf-c.h"

void protobuf_encode_decode(void)
{
	int i=0;
    void *buf;                     // Buffer to store serialized data
    unsigned msg_len;              // Length of serialized data

    // Encode message to buffer

    printf("---- Encoding ---\n");
        AMessage encode_msg = AMESSAGE__INIT;

        encode_msg.has_a  = 1;
        encode_msg.a      = atoi("12345");
        encode_msg.has_b  = 1;
        encode_msg.b      = atoi("67890");

        msg_len = amessage__get_packed_size(&encode_msg);
        buf = malloc(msg_len);

        printf("Encoding %d serialized bytes\n", msg_len);
        amessage__pack(&encode_msg, buf);
        printf("\n[");
        for(i=0;i<msg_len;i++)
        {
        	printf("0x%02X ",*(uint8_t*)(buf+i));
        }
        printf("]\n");
    // Unpack the message from buffer.
    {
        printf("---- Decoding ---\n");

        AMessage* decode_msg;
        decode_msg = amessage__unpack(NULL, msg_len, buf);
        if (decode_msg == NULL)
        {
          printf("Error unpacking incoming message\n");
          return;
        }
        printf("Received: a=%d b=%d \n",decode_msg->a, decode_msg->b);  // required field

        amessage__free_unpacked(decode_msg, NULL);
    }

    free(buf);

    return;
}

int main(void)
{
	protobuf_encode_decode();
	printf("hello!\n");
	return 0;
}
