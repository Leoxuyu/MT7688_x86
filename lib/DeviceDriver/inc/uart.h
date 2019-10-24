/*
 * uart.h
 *
 *  Created on: 2019年10月21日
 *      Author: work
 */

#ifndef LIB_DEVICEDRIVER_INC_UART_H_
#define LIB_DEVICEDRIVER_INC_UART_H_

#include <stdint.h>

#define BAUD_RATE_2400                  2400
#define BAUD_RATE_4800                  4800
#define BAUD_RATE_9600                  9600
#define BAUD_RATE_19200                 19200
#define BAUD_RATE_38400                 38400
#define BAUD_RATE_57600                 57600
#define BAUD_RATE_115200                115200
#define BAUD_RATE_230400                230400
#define BAUD_RATE_460800                460800
#define BAUD_RATE_921600                921600
#define BAUD_RATE_2000000               2000000
#define BAUD_RATE_3000000               3000000

#define DATA_BITS_5                     5
#define DATA_BITS_6                     6
#define DATA_BITS_7                     7
#define DATA_BITS_8                     8
#define DATA_BITS_9                     9

#define STOP_BITS_1                     0
#define STOP_BITS_2                     1
#define STOP_BITS_3                     2
#define STOP_BITS_4                     3

#define PARITY_NONE                     0
#define PARITY_ODD                      1
#define PARITY_EVEN                     2

#define BIT_ORDER_LSB                   0
#define BIT_ORDER_MSB                   1

#define NRZ_NORMAL                      0       /* Non Return to Zero : normal mode */
#define NRZ_INVERTED                    1       /* Non Return to Zero : inverted mode */

typedef struct DataFIFO
{
	uint32_t len;
    uint8_t *buffer;
    uint16_t put_index, get_index;
    uint8_t is_full;
}DataFIFO_t;

typedef struct SerialConfigure
{
    uint32_t baud_rate		:32;
    uint32_t data_bits		:4;
    uint32_t stop_bits		:2;
    uint32_t parity			:2;
    uint32_t bufsize		:24;
    DataFIFO_t RX_FIFO;
    DataFIFO_t TX_FIFO;
}SerialConfigure_t;








#endif /* LIB_DEVICEDRIVER_INC_UART_H_ */
