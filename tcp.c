#include <stdio.h>


typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;

/**
 * ----------------------------------------
 * |    16位源端口号    |   16位目的端口号  |
 * ----------------------------------------
 * |            32位序号                   |
 * ----------------------------------------
 * |            32确认号                   |
 * ----------------------------------------
 * |4头部长度|6位保留 6 |      16位窗口大小  |
 * ----------------------------------------
 * |  16位校验和      |   16紧急指针       |
 * ----------------------------------------
 * |          选项, 最多40字节             |
 * ----------------------------------------
 * 
 * 16位端口号(port number) 告知主机该报文段是来自哪里(源端口)以及传给哪个
 *  上层协议或应用程序(目的端口)的。
 * 32位序号(sequence number) 一次TCP通信(从TCP连接建立到断开)过程中某一个
 *  传输方向上的字节流的每个字节的编号.假设主机A和主机B进行TCP通信, A发送给B 
 *  的第一个TCP报文段中,序号值被系统初始化为某个随机值ISN(Initial Sequence Number)
 *  初始序号值),那么在该传输方向上(从A到B),后续的TCP报文段中序号值将被系统设置成
 *  ISN加上该报文所携带数据的第一个字节在整个字节流中的偏移。例如： 某个TCP报文
 *  段传送的数据是字节流中的每1025~2048字节,那么该报文的序号值就是ISN + 1025
 *  另外一个传输方向(B到A)的TCP报文段的序号值也具有相同的含义.
 * 32位确认号(acknowledgement number) 用作对另一方发送来的TCP报文段的响应。
 *  其值是收到的TCP报文段的序号值加1.假设主机A和主机B进行TCP通信,那么A发送出的
 *  TCP报文段不仅携带自己的序号,还包含对B发送来的TCP报文段的确认号。反之，B发送出的TC
 *  P报文段也同时携带自己的序号和对A发送来的报文段的确认号。
 * 4位头部长度(header length) 标识该TCP头部有多少个32bit字(4字节).因4位最大为15
 *  所以TCP头部最长是60字节。
 * 6位标志位：
 *      URG标志：表示紧急指针(urgent pointer)是否有效。
 *      ACK标志：表示确认号是否有效。我们称携带ACK标志的TCP报文段为确认报文段。
 *      PSH标志：提示接收端应用程序应该立即从TCP接收缓冲区中读走数据,为接收后续
 *              数据腾出空间.
 *      RST标志：表示要求对方重新建立连接，我们称携带RST标志的TCP报文段为复位报文段。
 *      SYN标志：表示请求建立一个连接,我们称携带SYN标志的TCP报文段为同步报文段
 *      FIN标志：表示通知对方本端要关闭连接了,我们称携带FIN标志的TCP报文段为结束报文段。
 * 
 * 16位窗口大小(window size) 是TCP流量控制的一个手段。这里说的窗口，指的是接收
 *   通告窗口(receiver window) 它告诉对方本端的TCP接收缓冲区还能容纳多少个字节数据
 *   这样对方就可以控制发送数据的速度。
 * 16位校验和(TCP checksum) 由发送端填充，接收端对TCP报文段执行RCR算法,以检验
 *  TCP报文段在传输过程中是否损坏.注意：这个校验不仅包括TCP头部,也包括数据部分
 *  这也是TCP可靠传输的一个重要保障。
 * 16位紧急指针(urgent pointer) 是一个正的偏移量.它和序号字段的值相加表示最后一个
 *  紧急数据的下一个字节的序号。因此，确切的说, 这个字段是紧急指针相对当前序号的偏移
 *  TCP紧急指针是发送端向接收端发送紧急数据的方法 
 * 
*/


typedef struct
{
    uint16_t srcport;
    uint16_t dstport;
    uint32_t seqnum;
    uint32_t acknum;
    uint16_t headerlength:4;
    uint16_t reserved:6;
    uint16_t urg:1;
    uint16_t ack:1;
    uint16_t psh:1;
    uint16_t rst:1;
    uint16_t syn:1;
    uint16_t fin:1;
    uint16_t windowsize;
    uint16_t checksum;
    uint16_t urgentPonter;
    uint8_t  option[0];
}tcp_t;


int main(int argc, char *argv[])
{
    tcp_t tcp;
    printf("tcp size: %ld\n",sizeof(tcp));

    return 0;
}