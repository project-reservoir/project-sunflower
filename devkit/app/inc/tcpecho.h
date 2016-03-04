#ifndef __TCPECHO_H
#define __TCPECHO_H

#include "radio_packets.h"

enum BINARY_COMMANDS {
    PAYLOAD     = 0x1,
    START       = 0x2,
    VALIDATE    = 0x3,
    EXIT_MODE   = 0x4,
    TCP_ACK     = 0x5,
    TCP_NACK    = 0x6,
    END         = 0x7
};

enum DEVICE_TYPE {
    DANDELION_DEVICE = 0x1,
    SUNFLOWER_DEVICE = 0x2
};

void tcpecho_os_init(void);
void tcpecho_thread(void *arg);
void unix_time_thread(void);
void EnqueueSensorTCP(generic_message_t* data);
uint32_t GetUnixTime(void);

#endif //__TCPECHO_H
