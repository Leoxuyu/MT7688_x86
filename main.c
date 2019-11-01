/*
 * main.c
 *
 *  Created on: 2019年10月21日
 *      Author: work
 */

//#include <stdio.h>
//
//int main(void)
//{
//	printf("hello!\n");
//	return 0;
//}

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <modbus.h>

/* Constants defined by configure.ac */
#define HAVE_INTTYPES_H 1
#define HAVE_STDINT_H 1

#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#ifdef HAVE_STDINT_H
# include <stdint.h>
#endif

#define SERVER_ID         17
#define INVALID_SERVER_ID 18

const uint16_t UT_BITS_ADDRESS = 0x130;
const uint16_t UT_BITS_NB = 0x25;
const uint8_t UT_BITS_TAB[] = { 0xCD, 0x6B, 0xB2, 0x0E, 0x1B };

const uint16_t UT_INPUT_BITS_ADDRESS = 0x1C4;
const uint16_t UT_INPUT_BITS_NB = 0x16;
const uint8_t UT_INPUT_BITS_TAB[] = { 0xAC, 0xDB, 0x35 };

const uint16_t UT_REGISTERS_ADDRESS = 0x160;
const uint16_t UT_REGISTERS_NB = 0x3;
const uint16_t UT_REGISTERS_NB_MAX = 0x20;
const uint16_t UT_REGISTERS_TAB[] = { 0x022B, 0x0001, 0x0064 };

/* Raise a manual exception when this address is used for the first byte */
const uint16_t UT_REGISTERS_ADDRESS_SPECIAL = 0x170;
/* The response of the server will contains an invalid TID or slave */
const uint16_t UT_REGISTERS_ADDRESS_INVALID_TID_OR_SLAVE = 0x171;
/* The server will wait for 1 second before replying to test timeout */
const uint16_t UT_REGISTERS_ADDRESS_SLEEP_500_MS = 0x172;
/* The server will wait for 5 ms before sending each byte */
const uint16_t UT_REGISTERS_ADDRESS_BYTE_SLEEP_5_MS = 0x173;

/* If the following value is used, a bad response is sent.
   It's better to test with a lower value than
   UT_REGISTERS_NB_POINTS to try to raise a segfault. */
const uint16_t UT_REGISTERS_NB_SPECIAL = 0x2;

const uint16_t UT_INPUT_REGISTERS_ADDRESS = 0x108;
const uint16_t UT_INPUT_REGISTERS_NB = 0x1;
const uint16_t UT_INPUT_REGISTERS_TAB[] = { 0x000A };

const float UT_REAL = 123456.00;

const uint32_t UT_IREAL_ABCD = 0x0020F147;
const uint32_t UT_IREAL_DCBA = 0x47F12000;
const uint32_t UT_IREAL_BADC = 0x200047F1;
const uint32_t UT_IREAL_CDAB = 0xF1470020;

/* const uint32_t UT_IREAL_ABCD = 0x47F12000);
const uint32_t UT_IREAL_DCBA = 0x0020F147;
const uint32_t UT_IREAL_BADC = 0xF1470020;
const uint32_t UT_IREAL_CDAB = 0x200047F1;*/



# include <sys/socket.h>

enum {
    TCP,
    TCP_PI,
    RTU
};

int main(int argc, char*argv[])
{
    int s = -1;
    modbus_t *ctx;
    modbus_mapping_t *mb_mapping;
    int rc;
    int i;
    int use_backend;
    uint8_t *query;
    int header_length;

    if (argc > 1)
    {
        if (strcmp(argv[1], "tcp") == 0)
        {
            use_backend = TCP;
        }
        else if (strcmp(argv[1], "tcppi") == 0)
        {
            use_backend = TCP_PI;
        }
        else if (strcmp(argv[1], "rtu") == 0)
        {
            use_backend = RTU;
        }
        else
        {
            printf("Usage:\n  %s [tcp|tcppi|rtu] - Modbus server for unit testing\n\n", argv[0]);
            return -1;
        }
    }
    else
    {
        /* By default */
        use_backend = TCP;
    }

    if (use_backend == TCP)
    {
        ctx = modbus_new_tcp("10.89.14.228", 1502);
        query = malloc(MODBUS_TCP_MAX_ADU_LENGTH);
    }
    else if (use_backend == TCP_PI)
    {
        ctx = modbus_new_tcp_pi("::0", "1502");
        query = malloc(MODBUS_TCP_MAX_ADU_LENGTH);
    }
    else
    {
        ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);
        modbus_set_slave(ctx, SERVER_ID);
        query = malloc(MODBUS_RTU_MAX_ADU_LENGTH);
    }
    header_length = modbus_get_header_length(ctx);

    modbus_set_debug(ctx, TRUE);

    mb_mapping = modbus_mapping_new_start_address(
        UT_BITS_ADDRESS, UT_BITS_NB,
        UT_INPUT_BITS_ADDRESS, UT_INPUT_BITS_NB,
        UT_REGISTERS_ADDRESS, UT_REGISTERS_NB_MAX,
        UT_INPUT_REGISTERS_ADDRESS, UT_INPUT_REGISTERS_NB);
    if (mb_mapping == NULL)
    {
        fprintf(stderr, "Failed to allocate the mapping: %s\n",
                modbus_strerror(errno));
        modbus_free(ctx);
        return -1;
    }

    /* Examples from PI_MODBUS_300.pdf.
       Only the read-only input values are assigned. */

    /* Initialize input values that's can be only done server side. */
    modbus_set_bits_from_bytes(mb_mapping->tab_input_bits, 0, UT_INPUT_BITS_NB,
                               UT_INPUT_BITS_TAB);

    /* Initialize values of INPUT REGISTERS */
    for (i=0; i < UT_INPUT_REGISTERS_NB; i++) {
        mb_mapping->tab_input_registers[i] = UT_INPUT_REGISTERS_TAB[i];;
    }

    if (use_backend == TCP) {
        s = modbus_tcp_listen(ctx, 1);
        modbus_tcp_accept(ctx, &s);
    } else if (use_backend == TCP_PI) {
        s = modbus_tcp_pi_listen(ctx, 1);
        modbus_tcp_pi_accept(ctx, &s);
    } else {
        rc = modbus_connect(ctx);
        if (rc == -1) {
            fprintf(stderr, "Unable to connect %s\n", modbus_strerror(errno));
            modbus_free(ctx);
            return -1;
        }
    }

    for (;;) {
        do {
            rc = modbus_receive(ctx, query);
            /* Filtered queries return 0 */
        } while (rc == 0);

        /* The connection is not closed on errors which require on reply such as
           bad CRC in RTU. */
        if (rc == -1 && errno != EMBBADCRC) {
            /* Quit */
            break;
        }

        /* Special server behavior to test client */
        if (query[header_length] == 0x03) {
            /* Read holding registers */

            if (MODBUS_GET_INT16_FROM_INT8(query, header_length + 3)
                == UT_REGISTERS_NB_SPECIAL) {
                printf("Set an incorrect number of values\n");
                MODBUS_SET_INT16_TO_INT8(query, header_length + 3,
                                         UT_REGISTERS_NB_SPECIAL - 1);
            } else if (MODBUS_GET_INT16_FROM_INT8(query, header_length + 1)
                       == UT_REGISTERS_ADDRESS_SPECIAL) {
                printf("Reply to this special register address by an exception\n");
                modbus_reply_exception(ctx, query,
                                       MODBUS_EXCEPTION_SLAVE_OR_SERVER_BUSY);
                continue;
            } else if (MODBUS_GET_INT16_FROM_INT8(query, header_length + 1)
                       == UT_REGISTERS_ADDRESS_INVALID_TID_OR_SLAVE) {
                const int RAW_REQ_LENGTH = 5;
                uint8_t raw_req[] = {
                    (use_backend == RTU) ? INVALID_SERVER_ID : 0xFF,
                    0x03,
                    0x02, 0x00, 0x00
                };

                printf("Reply with an invalid TID or slave\n");
                modbus_send_raw_request(ctx, raw_req, RAW_REQ_LENGTH * sizeof(uint8_t));
                continue;
            } else if (MODBUS_GET_INT16_FROM_INT8(query, header_length + 1)
                       == UT_REGISTERS_ADDRESS_SLEEP_500_MS) {
                printf("Sleep 0.5 s before replying\n");
                usleep(500000);
            } else if (MODBUS_GET_INT16_FROM_INT8(query, header_length + 1)
                       == UT_REGISTERS_ADDRESS_BYTE_SLEEP_5_MS) {
                /* Test low level only available in TCP mode */
                /* Catch the reply and send reply byte a byte */
                uint8_t req[] = "\x00\x1C\x00\x00\x00\x05\xFF\x03\x02\x00\x00";
                int req_length = 11;
                int w_s = modbus_get_socket(ctx);
                if (w_s == -1) {
                    fprintf(stderr, "Unable to get a valid socket in special test\n");
                    continue;
                }

                /* Copy TID */
                req[1] = query[1];
                for (i=0; i < req_length; i++) {
                    printf("(%.2X)", req[i]);
                    usleep(5000);
                    rc = send(w_s, (const char*)(req + i), 1, MSG_NOSIGNAL);
                    if (rc == -1) {
                        break;
                    }
                }
                continue;
            }
        }

        rc = modbus_reply(ctx, query, rc, mb_mapping);
        if (rc == -1) {
            break;
        }
    }

    printf("Quit the loop: %s\n", modbus_strerror(errno));

    if (use_backend == TCP) {
        if (s != -1) {
            close(s);
        }
    }
    modbus_mapping_free(mb_mapping);
    free(query);
    /* For RTU */
    modbus_close(ctx);
    modbus_free(ctx);

    return 0;
}























