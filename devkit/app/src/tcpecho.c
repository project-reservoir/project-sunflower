/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */


#include "lwip/opt.h"
#include "xprintf.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "fw_update.h"
#include "tcpecho.h"
#include "stm32f4xx.h"
#include "radio_packets.h"
#include "FreeRTOS.h"
#include "sensor_conversions.h"
#include "valve.h"

#if LWIP_NETCONN

#include "lwip/sys.h"
#include "lwip/api.h"

#define TCPECHO_THREAD_PRIO  osPriorityAboveNormal

#define TCP_FW_PAYLOAD_BYTES 256

#define MAX_WAITING_LOGS 20

const char* banner = "SUNFLOWER OS TCP/IP TERMINAL INTERFACE";

osMessageQId sensorMsgQ;

void net_printf(struct netconn *conn, const char *fmt, ...);
void net_bin_nack(struct netconn *conn);
void net_bin_ack(struct netconn *conn);

uint32_t unix_time;

void tcpecho_os_init(void)
{
    osMessageQDef(SensorLogQueue, MAX_WAITING_LOGS, generic_message_t*);
    sensorMsgQ = osMessageCreate(osMessageQ(SensorLogQueue), NULL);
}

void tcpecho_thread(void *arg)
{
    struct netconn *conn, *newconn;
    err_t err;

    LWIP_UNUSED_ARG(arg);

    /* Create a new connection identifier. */
    conn = netconn_new(NETCONN_TCP);

    if (conn != NULL) {
        /* Bind connection to well known port number 1337. */
        err = netconn_bind(conn, NULL, 1337);

        if (err == ERR_OK) {
            /* Tell connection to go into listening mode. */
            netconn_listen(conn);

            while (1) {
                /* Grab new connection. */
                err = netconn_accept(conn, &newconn);

                /* Process the new connection. */
                if (err == ERR_OK) {
                    struct netbuf *buf;
                    void   *data;
                    u16_t  len;
                    bool   fw_update_mode = false;
                    
                    net_printf(newconn, "%s\r\n", banner);

                    while ((err = netconn_recv(newconn, &buf)) == ERR_OK) {
                        do {
                            netbuf_data(buf, &data, &len);              
                            
                            // Ignore all 1 char or less sequences
                            if(len > 0)
                            {
                                if(!fw_update_mode)
                                {
                                    switch(((char*)data)[0]) 
                                    {
                                        case 'm':
                                            switch(((char*)data)[1])
                                            {
                                                case 'f':
                                                    fw_update_mode = true;
                                                    continue;
                                            }
                                            
                                            net_printf(newconn, "mf : enter firmware update mode. All ASCII output will cease.");
                                            net_printf(newconn, "Can be disabled by restarting TCP connection or sending the ");
                                            net_printf(newconn, "EXIT_FW_UPDATE_MODE command.\r\n");
                                            
                                            break;
                                            
                                        case 't':
                                            switch(((char*)data)[1]) 
                                            {
                                                case 's':
                                                    unix_time = atoi((const char*)&(((char*)data)[2]));
                                                    continue;
                                            }
                                            net_printf(newconn, "ts <UNIX time> : set the system time to <UNIX time>\r\n");
                                            
                                            break;
                                            
                                        case 'r':
                                            {
                                                generic_message_t* msg;
                                                osEvent            msgQueueEvent;
                                                
                                                // Get a sensor log
                                                do
                                                {
                                                    msgQueueEvent = osMessageGet(sensorMsgQ, 0);
                                                    
                                                    if(msgQueueEvent.status == osEventMessage)
                                                    {
                                                        msg = (generic_message_t*)(msgQueueEvent.value.p);
                                                        // Print the message to the TCP console
                                                        
                                                        net_printf(newconn, "DREP:  ", msg->src);
                                                        
                                                        net_printf(newconn, "%08x,", msg->src); // Dandelion ID
                                                        
                                                        net_printf(newconn, "%d,", unix_time);  // Timestamp
                                                        
                                                        // TODO: improve moisture math
                                                        float moisture0 = msg->payload.sensor_message.moisture0;
                                                        float moisture1 = msg->payload.sensor_message.moisture1;
                                                        float moisture2 = msg->payload.sensor_message.moisture2;
                                                        
                                                        /*if(moisture2 < 0)
                                                        {
                                                            moisture2 = 0.0f;
                                                        }*/
                                                        
                                                        //moisture2 = moisture2 / 500.0f;
                                                        
                                                        net_printf(newconn, "%f,", moisture0);  // Moist 0
                                                        net_printf(newconn, "%f,", moisture1);  // Moist 1
                                                        net_printf(newconn, "%f,", moisture2);  // Moist 2
                                                                                                                
                                                        net_printf(newconn, "%f,", TMP102_To_Float(msg->payload.sensor_message.temp0));               // Soil Temp 1
                                                        net_printf(newconn, "%f,", TMP102_To_Float(msg->payload.sensor_message.temp1));               // Soil Temp 2
                                                        net_printf(newconn, "%f,", TMP102_To_Float(msg->payload.sensor_message.temp2));               // Soil Temp 3
                                                        
                                                        net_printf(newconn, "%f,", HTU21D_Temp_To_Float(msg->payload.sensor_message.air_temp));       // Air Humidity
                                                        net_printf(newconn, "%d", msg->payload.sensor_message.chip_temp);                             // Air Temp
                                                        
                                                        net_printf(newconn, "\r\n");
                                                        
                                                        // Free the memory used by the message
                                                        vPortFree(msg);
                                                    }
                                                } while(msgQueueEvent.status == osEventMessage);
                                            }
                                            break;
                                        case 'v':
                                            {
                                                uint8_t valve = 0;
                                                switch(((char*)data)[1]) 
                                                {
                                                    case 'o':
                                                        valve = atoi((const char*)&(((char*)data)[2]));
                                                        OpenValve(valve);
                                                        break;
                                                    
                                                    case 'c':
                                                        valve = atoi((const char*)&(((char*)data)[2]));
                                                        CloseValve(valve);
                                                        break;
                                                }
                                                net_printf(newconn, "vo <valve> : open valve\r\n");
                                                net_printf(newconn, "vc <valve> : close valve\r\n");
                                            }
                                            break;
                                        case 'p':
                                            {
                                                long  polling_rate = atoi((const char*)&(((char*)data)[2]));
                                                
                                                if(polling_rate < 500 || polling_rate > (24 * 60 * 60 * 1000))
                                                {
                                                    ERR("Minimum polling rate is 500ms, maximum rate is %d\n", (24 * 60 * 60 * 1000));
                                                    break;
                                                }
                                               
                                                generic_message_t* generic_msg = pvPortMalloc(sizeof(generic_message_t));
                                        
                                                // TODO: check we didn't run out of RAM (we should catch this in the 
                                                //       application Malloc failed handler, but just in case)
                                            
                                                generic_msg = pvPortMalloc(sizeof(generic_message_t));
                                                generic_msg->cmd = SENSOR_CMD;
                                                
                                                generic_msg->payload.sensor_cmd.sensor_polling_period = polling_rate;
                                                generic_msg->payload.sensor_cmd.valid_fields = 0x1;
                                                SendToBroadcast((uint8_t*)generic_msg, sizeof(generic_message_t));
                                            }
                                            break;
                                        default:
                                            net_printf(newconn, "m : mode control\r\n");
                                            net_printf(newconn, "t : time control\r\n");
                                            net_printf(newconn, "r : report request\r\n");
                                            net_printf(newconn, "v : valve control\r\n");
                                            net_printf(newconn, "p : polling rate\r\n");
                                            break;
                                    }
                                    net_printf(newconn, "\r\n\n");
                                }
                                else if(fw_update_mode)
                                {                                    
                                    switch(((char*)data)[0])
                                    {
                                        // PAYLOAD, type, addr[4], payload[64]
                                        case PAYLOAD:
                                            if(len == (TCP_FW_PAYLOAD_BYTES + 6))
                                            {
                                                uint32_t addr = (((uint8_t*)data)[5] << 24) | (((uint8_t*)data)[4] << 16) | (((uint8_t*)data)[3] << 8) | (((uint8_t*)data)[2]);
                                                
                                                switch(((uint8_t*)data)[1])
                                                {
                                                    // DANDELION TYPE
                                                    case DANDELION_DEVICE:
                                                        for(uint16_t i = 0; i < TCP_FW_PAYLOAD_BYTES; i += 4)
                                                        {
                                                            uint32_t word = (((uint8_t*)data)[9 + i] << 24) | (((uint8_t*)data)[8 + i] << 16) | (((uint8_t*)data)[7 + i] << 8) | (((uint8_t*)data)[6 + i]);
                                                            Write_Dandelion_Word(addr + i, word);
                                                        }
                                                        net_bin_ack(newconn);
                                                        break;
                                                    
                                                    // SUNFLOWER TYPE
                                                    case SUNFLOWER_DEVICE:
                                                        for(uint16_t i = 0; i < TCP_FW_PAYLOAD_BYTES; i += 4)
                                                        {
                                                            uint32_t word = (((uint8_t*)data)[9 + i] << 24) | (((uint8_t*)data)[8 + i] << 16) | (((uint8_t*)data)[7 + i] << 8) | (((uint8_t*)data)[6 + i]);
                                                            Write_Sunflower_Word(addr + i, word);
                                                        }
                                                        net_bin_ack(newconn);
                                                        break;
                                                    
                                                    default:
                                                        net_bin_nack(newconn);
                                                        break;
                                                }
                                            }
                                            break;
                                        
                                        // START, type
                                        case START:
                                            if(len == 2)
                                            {                                                
                                                switch(((uint8_t*)data)[1])
                                                {
                                                    // DANDELION TYPE
                                                    case DANDELION_DEVICE:
                                                        FLASH_Unlock();
                                                        Erase_Dandelion_Image();
                                                        net_bin_ack(newconn);
                                                        break;
                                                    
                                                    // SUNFLOWER TYPE
                                                    case SUNFLOWER_DEVICE:
                                                        FLASH_Unlock();
                                                        Erase_Sunflower_Image();
                                                        net_bin_ack(newconn);
                                                        break;
                                                    
                                                    default:
                                                        net_bin_nack(newconn);
                                                        break;
                                                }
                                            }
                                            break;
                                                                                
                                        // VALIDATE, type
                                        case VALIDATE:
                                            if(len == 2)
                                            {                                                
                                                switch(((uint8_t*)data)[1])
                                                {
                                                    // DANDELION TYPE
                                                    case DANDELION_DEVICE:
                                                        Erase_Dandelion_Image();
                                                        net_bin_ack(newconn);
                                                        break;
                                                    
                                                    // SUNFLOWER TYPE
                                                    case SUNFLOWER_DEVICE:
                                                        Erase_Sunflower_Image();
                                                        net_bin_ack(newconn);
                                                        break;
                                                    
                                                    default:
                                                        net_bin_nack(newconn);
                                                        break;
                                                }
                                            }
                                            break;
                                        
                                        // EXIT BINARY MODE
                                        case EXIT_MODE:
                                            fw_update_mode = false;
                                            net_bin_ack(newconn);
                                            break;
                                        
                                        // EXIT BINARY MODE
                                        case END:
                                            FLASH_Lock();
                                            net_bin_ack(newconn);
                                            break;
                                        
                                        default:
                                            ERR("Unexpected TCP command");
                                            net_bin_nack(newconn);
                                            break;
                                    }
                                }
                            }
                            
                        } while (netbuf_next(buf) >= 0);
                        
                        netbuf_delete(buf);
                    }

                    /* Close connection and discard connection identifier. */
                    netconn_close(newconn);
                    netconn_delete(newconn);
                }
            }
        } else {
            xprintf(" can not bind TCP netconn");
        }
    } else {
        xprintf("can not create TCP netconn");
    }
}

void unix_time_thread(void)
{
    while(1)
    {
        unix_time++;
        vTaskDelay(1000);
    }
}

uint32_t GetUnixTime(void)
{
    return unix_time;
}

// Add a sensor log to the TCP transmit queue
// The pointer passed into this function will NEVER be freed automatically: a copy of the data is made
// Caller must free the input pointer after this function returns.
void EnqueueSensorTCP(generic_message_t* data)
{
    generic_message_t* message = pvPortMalloc(sizeof(generic_message_t));
    memcpy(message, data, sizeof(generic_message_t));
    
    if(osMessagePut(sensorMsgQ, (uint32_t)message, 0) != osOK)
    {
        vPortFree(message);
    }
}

void net_printf(struct netconn *conn, const char *fmt, ...)
{
    char buffer[64];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, 64, fmt, args);
    
    netconn_write(conn, buffer, strlen(buffer), NETCONN_COPY);
}

void net_bin_ack(struct netconn *conn)
{
    uint8_t buffer[1];
    buffer[0] = TCP_ACK;
    
    netconn_write(conn, buffer, 1, NETCONN_COPY);
}
    
void net_bin_nack(struct netconn *conn)
{
    uint8_t buffer[1];
    buffer[0] = TCP_NACK;
    
    netconn_write(conn, buffer, 1, NETCONN_COPY);
}

void tcpecho_init(void)
{
    sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, TCPECHO_THREAD_PRIO);
}
/*-----------------------------------------------------------------------------------*/

#endif /* LWIP_NETCONN */
