#include <stdio.h>


typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;


/**
 * -------------------------------------------------------------
 * |4位版本号|8位通信类型|          20位流标签                    |
 * -------------------------------------------------------------
 * | 16位净荷长度   | 8位下一个包头 | 8位跳数限制                  |
 * -------------------------------------------------------------
 * |                128 源端IP地址                               |
 * -------------------------------------------------------------
 * |                128 目的端IP地址                             |
 * -------------------------------------------------------------
 * 
 * 4位版本号(version) 指定IP协议的版本.对IPV6来说,其值为 6
 * 8位通信类型(traffic class) 指示数据流通类型或优先级,和IPV4中的TOS类似
 * 20位流标签(flow label) 是IPv6新增加的字段,用于某些对连接的服务质量有特
 *      殊要求的通信,比如音频或视频实时数据传输.
 * 16位净荷长度(payload length) 指的是IPv6扩展头部和应用程序数据长度之和
 *      不包括固定头部长度.
 * 8位下一个包头(next header) 指出紧跟IPv6固定头部后的包头类型, 如扩展头
 *      (如果有的话)或某个上层协议头(比如TCP,UDP 或 ICMP). 它类似于IPv4
 *      头部中的协议字段,且相同的取值有相同的含义.
 * 8位路数限制(hop limit) 和IPv4中的TTL含义相同.
*/


typedef struct
{
    uint32_t version:4;
    uint32_t type:8;
    uint32_t flag:20;
    uint16_t length;
    uint8_t  nextHeader;
    uint8_t  live;
    uint8_t  srcIP[16];
    uint8_t  dstIP[16];
}ipv6_t;

int main(int argc, char *argv[])
{
    ipv6_t ipv6;
    printf("ipv6 size: %ld\n", sizeof(ipv6));
    return 0;
}