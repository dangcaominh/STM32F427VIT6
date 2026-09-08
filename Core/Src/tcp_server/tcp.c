#include <stdio.h>
#include <stdbool.h>
#include "lwip.h"
#include "lwip/tcp.h"
#include "tcp_server/tcp.h"

struct tcp_pcb* tcp;

bool isConnected = 0;

static err_t tcp_connect_callback(void* arg, struct tcp_pcb* tpcb, err_t err)
{
    if (err == ERR_OK)
    {
        printf("3-way handshake thanh cong! Da ket noi toi Server.\r\n");
        isConnected = 1;
        tcp_nagle_disable(tpcb);
        tcp_sent(tpcb, client_sent_cb);
    }
    else
    {
        printf("Ket noi loi, ma loi: %d\r\n", err);
        tcp_close(tpcb);
    }
    return ERR_OK;
}

err_t init_tcp_client()
{
    ip_addr_t serverip;
    uint16_t server_port = 8080;

    IP4_ADDR(&serverip, 192, 168, 1, 12);

    tcp = tcp_new();

    if(tcp == NULL)
    {
        printf("Khong the khoi tao TCP PCB\r\n");
        return ERR_MEM;
    }

    err_t err = tcp_connect(tcp, &serverip, server_port, tcp_connect_callback);

    if (err != ERR_OK)
    {
        printf("Loi trong qua trinh 3-way hanshake: %d\r\n", err);
        tcp_abort(tcp);
    }

    return err;
}

// Callback chạy khi Server đã gửi gói ACK xác nhận đã nhận dữ liệu
static err_t client_sent_cb(void* arg, struct tcp_pcb* tpcb, u16_t len)
{
    //printf("Server da nhan va ACK %d bytes\r\n", len);
    return ERR_OK;
}


err_t send_tcp_data(void* data, uint16_t len)
{
    if (tcp_sndbuf(tcp) < len)
    {
        return ERR_MEM;
    }

    err_t err = tcp_write(tcp, data, len, 1); 

    if (err == ERR_OK)
    {
        err = tcp_output(tcp);
    }
    return err;
}


int tcp_send_chunk(uint8_t* frame_buf, int32_t len)
{
    if (len <= 0) return 0;

    uint16_t available_buf = tcp_sndbuf(tcp);
    if (available_buf == 0) return 0;

    // Giới hạn gửi theo bộ đệm khả dụng và tối đa 2 * TCP_MSS mỗi lần gửi
    uint16_t send_len = (len > available_buf) ? available_buf : len;
    if (send_len > (4 * TCP_MSS)) send_len = 4 * TCP_MSS;

    err_t err = send_tcp_data(frame_buf, send_len);
    if (err == ERR_OK)
    {
        return send_len; // Trả về đúng số byte đã đẩy vào bộ đệm TCP
    }
    
    return 0;
}