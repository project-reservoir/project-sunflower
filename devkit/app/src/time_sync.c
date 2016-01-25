#include "time_sync.h"
#include "debug.h"
#include <stdio.h>
#include <string.h>
#include "xprintf.h"
#include "dns.h"
#include "stm32f4xx_rtc.h"

#define TIME_SERVER "time.nist.gov"
#define TIME_PORT   37
static struct netconn *g_conn          = NULL;

void TimeSyncHwInit(void)
{
    // Initialize the RTC here
    RTC_InitTypeDef rtc;
    rtc.RTC_HourFormat = RTC_HourFormat_24;
    rtc.RTC_SynchPrediv = 128; // LSI clock is ~32.768 kHz, which is close to the default values
    rtc.RTC_SynchPrediv = 256;
    RTC_Init(&rtc);
}

void TimeSyncInit(void)
{
    g_conn = netconn_new(NETCONN_TCP);
    
    if (g_conn == NULL) 
    {
        WARN("Netconn initialization failed\n");
    }
}

void TimeSyncTask(void)
{
    while(g_conn == NULL)
    {
        // Delay for 5 seconds
        vTaskDelay(5000);
        TimeSyncInit();
    }
    
    // Sync the time from the time-server once every hour
    while(1)
    {
        TimeSync();
        vTaskDelay(60 * 60 * 1000);
    }
}

// Connect to a time server and download the current TIME
bool TimeSync(void)
{
    err_t err;
    void* data;
    uint16_t len;
    struct netbuf *buf;
    ip_addr_t addr;
    uint32_t received_time;
    
    if(g_conn == NULL)
    {
        ERR("Cannot connect to time server: netconn not initialized\n");
        return false;
    }
    
    err = netconn_gethostbyname(TIME_SERVER, &addr);
    
    if(err != ERR_OK)
    {
        ERR("DNS could not resolve hostname: %s\n", lwip_strerr(err));
        return false;
    }
    
    err = netconn_connect(g_conn, &addr, TIME_PORT);
    
    if(err != ERR_OK) 
    {
        ERR("Netconn could not connect to host %s\n", lwip_strerr(err));
        netconn_close(g_conn);
        return false;
    }
    
    if(netconn_recv(g_conn, &buf) == ERR_OK)
    {
        do 
        {
            netbuf_data(buf, &data, &len);
            DEBUG("Data length: %d\n", len);
            
            if(len == 4)
            {
                received_time = ((((uint8_t*)data)[0]) << 24) | ((((uint8_t*)data)[1]) << 16) | ((((uint8_t*)data)[2]) << 8) | (((uint8_t*)data)[3]);
                INFO("Time sync received! Current time is %u\n", received_time);
                
                // Update the RTC
            }
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
    }
    
    //netconn_close(g_conn);
    
    return true;
}

// Return the current UNIX time
uint32_t TimeSyncGet(void)
{
    return 0;
}
