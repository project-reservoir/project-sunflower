#ifndef __TCPECHO_H
#define __TCPECHO_H

enum BINARY_COMMANDS {
    PAYLOAD     = 0x1,
    START       = 0x2,
    VALIDATE    = 0x3,
    EXIT_MODE   = 0x4,
    ACK         = 0x5,
    NACK        = 0x6,
    END         = 0x7
};

enum DEVICE_TYPE {
    DANDELION_DEVICE = 0x1,
    SUNFLOWER_DEVICE = 0x2
};

#endif //__TCPECHO_H
