#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

/**
 * @brief IPV4 协议头部结构
 * -------------------------------------------------------------------
 * |4位版本号|4位头部长度|8位服务类型|      16位总长度(字节数)           |
 * -------------------------------------------------------------------
 * |        16位标识               |3位标志|    13位片偏移             |
 * -------------------------------------------------------------------
 * | 8位生存时间(TTL)| 8位协议      |      16位头部检验和               |
 * -------------------------------------------------------------------|
 * |                        32位源端IP地址                            |
 * -------------------------------------------------------------------
 * |                        32位目的端IP地址                          |
 * -------------------------------------------------------------------
 * |                        选项,最多40字节                           |
 * -------------------------------------------------------------------
 * 
 * 4位版本号(version) 指定IP协议的版本。对IPv4来说其值为4.
 * 4位头部长度(header length) 标识该IP头部有多少个32bit字(4字节),因为4位最大
 *      只能表示15,所以IP头部最长是60个字节。
 * 8位服务类型(type of service,TOS) 包括一个3位的做优先权字段(现在已被忽略),
 *      4位的TOS字段和1位保留字段(必须置0), 4位的TOS字段分别表示: 最小延时,
 *      最大吞吐量,最高可靠性和最小开销. 其中最多有一个能置为1,应用程序应根据实际
 *      需要来设置,比如像ssh,telnet这样的登录服务应设置最小延时,文件传输程序ftp则
 *      需要设置最大吞吐量。
 * 16位总长度(total length) 是指整个IP数据报的长度,以字节为单位,因此IP数据报的最大
 *      长度为65535(2^16次方-1)字节。但是由于MTU限制,长度超过MTU的数据报都将被分片
 *      传输,所以实际传输的IP数据报(或分片)的长度都远远没有达到最大值.接下来的3个段
 *      描述了如何进行分片。
 * 16位标识(identification).唯一地标识主机发送的每一个数据报.其初值由系统随机生成;
 *      每发送一个数据报,其值就加1,该值在数据报分片时被复制到每个分片中,因此同一个数
 *      据报的所有分片都具有相同的标识值.
 * 3位标志字段的第一位保留.第二位(Don't Fragment,DF)表示禁止分片. 如果设置了这个位,
 *      IP模块将不对数据报进行分片,在这种情况下，如果IP数据报长度超过MTU的话，IP模块
 *      将丢弃该数据报并返回一个ICMP差错报文. 第三位(More Fragment, MF)表示更多分片,
 *      除了最后一个数据分片外,其它分片都要把它置1.
 * 13位分片偏移(Fragmentation, offset)是分片相对原始IP数据报开始处(仅指数据部分)
 *      的偏移.实际的偏移值是该值左移3位(乘以8)后得到的. 由于这个原因,除了最后一个IP分
 *      片外,每个IP分片的数据部分的长度必需是8的整数倍(这样才能保证后面的IP分片拥有一个合
 *       适的偏移值).
 * 8位生存时间(Time to live, TTL)是指数据报到达目的地之前允许经过的路由跳数,TTL值被 发
 *      送端设置(常见值为64). 数据报在转发过程中每经过一个路由,该值就被路由器减1，
 *      当TTL值被减为0时,路由器将丢弃数据报。并向源端发达一个ICMP差错报文,TTL
 *      的值可以防止数据报陷入路由循环.
 * 16位头部检验和(header checksum)由发送端填充,接收端对其使用CRC算法以检验IP数据报头
 *      部在传输过程中是否损坏.
 * 32位的源端IP址和目的端IP地址用来标识数据报的发送端和接收端,一般情况下这两个地址在整个
 *      数据报的传递过程中保持不变。
 * IPV4最后一个先项字段(option) 是可变长的可选信息。
 *      可用IP选项包括:
 *          记录路由(record route): 告诉数据报途径所有路由器都将自己的IP地址填入头部
 *              的选项部分,这样我们可以跟踪数据报的传递路径。
 *          时间戳(timestamp): 告诉每个路由器都将数据报被转发的时间(或时间与IP地址对)
 *              填入IP头部的选项部分,这样就可以测量途径路由之间数据报传输的时间。
 *          松散源路由选择(loose source routing): 指定一个路由器IP地址列表，数据报发送
 *              过程中必须经过其中所有的路由器。
 *          严格源路由选择(strict source routing): 和松散源路由选择类似,不过数据报只能
 *              经过被指定的路由器.
 */
typedef struct
{
    uint8_t version:4;              /* 4位版本号   */
    uint8_t header_length:4;        /* 4位头部长度 */
    uint8_t service_type;           /* 8位服务类型 */
    uint16_t total_length;          /* 16位总长度(字节数) */
    uint16_t identification;        /* 16位标识 */
    uint16_t flags:3;                /* 3位标志位 */
    uint16_t fragment_offset:13;    /* 13位片偏移 */
    uint8_t time_to_live;           /* 8位生存时间TTL */
    uint8_t protocol;               /* 8位协议 */
    uint16_t header_checksum;       /* 16位头部检验和 */
    uint32_t source_address;        /* 32位源IP地址 */
    uint32_t destination_address;   /* 32位目的IP地址 */
    uint8_t options[0];             /* 选项, 最多40字节 */
} ipv4_t;


int main(int argc, char **argv)
{
    ipv4_t ipv4_header;
    printf("ipv4_header size: %ld\n", sizeof(ipv4_header));
    ipv4_header.version = 4;
    ipv4_header.header_length = 20;
    ipv4_header.service_type = 0x1;
    ipv4_header.total_length = htons(60);
    ipv4_header.identification = htons(1234);
    ipv4_header.flags = 0;
    ipv4_header.fragment_offset = htons(0);
    ipv4_header.time_to_live = 64;
    ipv4_header.protocol =6;
    ipv4_header.source_address = htonl(127);
    ipv4_header.destination_address = htonl(128);
    ipv4_header.options[0] = 0;
    return 0;
}