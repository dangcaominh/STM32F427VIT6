#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdio.h>
#include "lwip.h"
#include "lwip/tcp.h"

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

extern struct tcp_pcb* tcp;

static err_t tcp_connect_callback(void* arg, struct tcp_pcb* tpcb, err_t err);

err_t init_tcp_client();

static err_t client_sent_cb(void* arg, struct tcp_pcb* tpcb, u16_t len);

err_t send_tcp_data(void* data, uint16_t len);

int tcp_send_chunk(uint8_t* frame_buf, int32_t len);

#endif