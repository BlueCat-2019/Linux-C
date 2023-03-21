#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t ;
/* arp 数据帧格式 */
/**
 * @brief arp 数据帧封装
 * 
 * ----------------------------------------------------------------
 * |2bytes|2bytes|1bytes|1bytes|2bytes|6bytes|4bytes|6bytes|4bytes|
 * ----------------------------------------------------------------
 * 2字节的硬件类型，定义物理地址的类型，值为1表示MAC地址
 * 2字节的协议类型，表示要映射的协议类型地址，值为0x800表示IP地址
 * 1字节的硬件地址长度，MAC地址为6
 * 1字节的协议地址长度，IP地址为4
 * 2字节的操作字段指出4种操作类型：ARP请求(值为1)、ARP应答(值为2)、RARP请求(值为3)、RARP应答(值为4)
 * 最后的4个字段，分别为通信双方的以太网地址和IP地址。发送端填充除目的端以太网地址外的其它三个字段，以构
 * 建ARP请求并发送，接收端发现请求的ARP报文目的端IP地址是自己，就把自己的以太网地址填充进去，然后交换两个
 * 目的端地址和两个发送端地址，构建应答报文并发送。(操作字段需要改为2)
*/
typedef struct
{
    uint16_t htype;      /* 硬件类型 */
    uint16_t ptype;      /* 协议类型 */
    uint8_t  hlen;       /* 硬件地址长度 */
    uint8_t  plen;       /* 协议地址长度 */
    uint16_t oper;       /* 操作字段 1:arp请求,2:arp应答,3:rarp请求,4:rarp应答 */
    uint8_t  smac[6];    /* 发送端MAC地址 */
    uint8_t  sip[4];     /* 发送端IP地址 */
    uint8_t  dmac[6];    /* 接收端MAC地址 */
    uint8_t  dip[4];     /* 接收端IP地址 */
    uint8_t  data[0];    /* 数据 一般填充0, 至少18字节 */
} arp_frame_t;

/* arp 请求/应答报文的长度为28字节，如果再加上以太网帧头部和尾部的18字节,则一个携带ARP
 * 请求/应答报文的以太网帧长度为46个字节。不过,有些实现要求以太网帧的数据部份长度至少为
 * 46个字节，此时ARP请求应答报文的长度就需要增加到至少46个字节，也就是在帧尾补0 */


/* Test */
int main(int argc, char *argv[])
{
    uint8_t *buffer = malloc(sizeof(uint8_t) * 32);
    strcpy(buffer, "Hello BlueMoon and Ilrian");
    printf("buffer: %s\n", buffer);
    arp_frame_t *arp = malloc(sizeof(arp_frame_t) + strlen(buffer) + 1);
    strcpy(arp->data, buffer);
    printf("arp: %s\n", arp->data);
    buffer = arp->data;
    free(arp);
        // buffer[1] = 'Z';
        // arp->data[2] = 'Y';
        // printf("buffer: %s\n", buffer);
        // printf("arp: %s\n", arp->data);
    return 0;
}