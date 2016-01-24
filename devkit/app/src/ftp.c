#include "ftp.h"
#include "debug.h"
#include <stdio.h>
#include <string.h>
#include "xprintf.h"
#include "lwip/sockets.h"

#define FTP_SERVER  "waterloo.autom8ed.com"
#define FTP_USER    "themachine"
#define FTP_PASS    "s4mar1tan"
#define FTP_PORT    1337

#define TMP_STR_LEN 64

struct netconn *g_conn          = NULL;
struct netconn *g_data          = NULL;
bool            g_connected     = false;

static bool FTP_SendCommand(char* command, size_t msg_size);
static bool FTP_PASV(void);

void FTP_Init(void)
{
    
    lwip_socket_init();
    if(!g_conn) 
    {
        g_conn = netconn_new(NETCONN_TCP);
    }
    
    if (g_conn == NULL) 
    {
        WARN("Netconn initialization failed\n");
    }
}

bool FTP_DownloadFirmware(void)
{
    struct ip_addr addr;
    err_t err;
    
    err = netconn_gethostbyname(FTP_SERVER, &addr);
    
    if(err != ERR_OK)
    {
        ERR("DNS could not resolve hostname: %s\n", lwip_strerr(err));
        return false;
    }
    
    FTP_Init();
    FTP_Connect(&addr, FTP_PORT);
    FTP_GetFwVersions(NULL, NULL, 0);
}

bool FTP_Connect(struct ip_addr *addr, uint16_t port)
{
    err_t err;   
    char tmp[TMP_STR_LEN];
    void* data;
    uint16_t len;
    struct netbuf *buf;
    int8_t size;
    
    if(g_conn == NULL)
    {
        WARN("Cannot connect to FTP: netconn not initialized\n");
        return false;
    }
    
    err = netconn_connect(g_conn, addr, port);
    
    if(err != ERR_OK) 
    {
        ERR("(FTP) Netconn could not connect to host %s\n", lwip_strerr(err));
        return false;
    }
    
    g_connected = true;

    size = snprintf(tmp, TMP_STR_LEN, "USER %s\n", FTP_USER);
    assert_param(size > 0 && size < TMP_STR_LEN);
    netconn_write(g_conn, tmp, size, NETCONN_COPY);
    
    size = snprintf(tmp, TMP_STR_LEN, "PASS %s\n", FTP_PASS);
    assert_param(size > 0 && size < TMP_STR_LEN);
    netconn_write(g_conn, tmp, size, NETCONN_COPY);
    
    while((buf = netconn_recv(g_conn)) != NULL)
    {
        bool logged_in = false;
        
        do 
        {
            netbuf_data(buf, &data, &len);
            DEBUG("%s\n", (char*)data);
            if(len >= 3)
            {
                if(strncmp((char*)data, "230", 3) == 0)
                {
                    logged_in = true;
                }
                else if(((char*)data)[0] == '4' || ((char*)data)[0] == '5')
                {
                    ERR("Could not connect to FTP, aborting");
                    return false;
                }
            }
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
        
        if(logged_in)
        {
            break;
        }
    }
    
    return true;
}

bool FTP_SendCommand(char* command, size_t msg_size)
{
    void* data;
    uint16_t len;
    struct netbuf *buf;
    
    // Cannot send command if not connected
    if(g_connected == false)
    {
        return false;
    }
    
    if(netconn_write(g_conn, command, msg_size, NETCONN_COPY) != ERR_OK)
    {
        ERR("Could not write command over g_conn socket\n");
        return false;
    }
    
    while((buf = netconn_recv(g_conn)) != NULL)
    {
        bool done = false;
        do 
        {
            netbuf_data(buf, &data, &len);
            
            DEBUG("%s\n", (char*)data);
            
            if(((char*)data)[0] == '2' || ((char*)data)[0] == '3')
            {
                done = true;
            }
            else if(((char*)data)[0] == '4' || ((char*)data)[0] == '5')
            {
                DEBUG("Error connecting to FTP, aborting\n");
                return false;
            }
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
        
        if(done)
        {
            break;
        }
    }
    
    return true;
}

// Send a PASV command and open the g_data netconn.
// Returns true if the g_data netconn was opened, else returns false for any error
bool FTP_PASV(void)
{  
    char tmp[TMP_STR_LEN];
    int8_t size; 
    void* data;
    uint16_t len;
    struct netbuf *buf;
    
    // Cannot send command if not connected
    if(g_connected == false)
    {
        return false;
    }
    
    size = snprintf(tmp, TMP_STR_LEN, "PASV\n");
    assert_param(size > 0 && size < TMP_STR_LEN);
    if(netconn_write(g_conn, tmp, size, NETCONN_COPY) != ERR_OK)
    {
        ERR("Could not write PASV command over g_conn socket\n");
        return false;
    }
    
    while((buf = netconn_recv(g_conn)) != NULL)
    {
        bool done = false;
        do 
        {
            netbuf_data(buf, &data, &len);
            
            DEBUG("%s\n", (char*)data);
            
            if(strncmp((char*)data, "227", 3) == 0)
            {
                uint8_t         start_pos = 0;
                long            ip_temp_a;
                long            ip_temp_b;
                long            ip_temp_c;
                long            ip_temp_d;
                long            port_a;
                long            port_b;
                char*           first_num;
                struct ip_addr  addr;
                for(uint8_t i = 0; i < len; i++)
                {
                    if(((char*)data)[i] == '(')
                    {
                        start_pos = i;
                        ((char*)data)[i] = ' ';
                    }
                    else if(((char*)data)[i] == ')' || ((char*)data)[i] == ',')
                    {
                        ((char*)data)[i] = ' ';
                    }
                }
                
                first_num = &((char*)data)[start_pos];
                                
                xatoi(&first_num, &ip_temp_a);
                xatoi(&first_num, &ip_temp_b);
                xatoi(&first_num, &ip_temp_c);
                xatoi(&first_num, &ip_temp_d);
                xatoi(&first_num, &port_a);
                xatoi(&first_num, &port_b);
                
                IP4_ADDR(&addr, ip_temp_a, ip_temp_b, ip_temp_c, ip_temp_d);
                
                g_data = netconn_new(NETCONN_TCP);
                
                if(g_data == NULL)
                {
                    ERR("Could not allocate g_data TCP socket for PASV command\n");
                    return false;
                }
                
                if(netconn_connect(g_data, &addr, (port_a*256) + port_b) != ERR_OK)
                {
                    netconn_delete(g_data);
                    ERR("Could not connect to data port from PASV command\n");
                    return false;
                }
                
                done = true;
            }
            else if(((char*)data)[0] == '4' || ((char*)data)[0] == '5')
            {
                DEBUG("Error sending passv command\n");
                return false;
            }
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
        
        if(done)
        {
            break;
        }
    }
    
    return true;
}

bool FTP_GetFwVersions(char* sunflower, char* dandelion, uint8_t max_len)
{
    char tmp[TMP_STR_LEN];
    int8_t size;     
    void* data;
    uint16_t len;
    struct netbuf *buf;
    char* data_ptr;
    char* end_of_data;
    
    // Cannot send command if not connected
    if(g_connected == false)
    {
        return false;
    }
    
    // Open a PASV data socket
    if(!FTP_PASV())
    {
        ERR("Could not LIST files: cannot open PASV data socket");
        return false;
    }
    
    size = snprintf(tmp, TMP_STR_LEN, "NLST\n");
    assert_param(size > 0 && size < TMP_STR_LEN);
    if(!FTP_SendCommand(tmp, size))
    {
        ERR("Could not write LIST command over g_conn socket\n");
        return false;
    }
    
    while((buf = netconn_recv(g_data)) != NULL)
    {
        do
        {
            netbuf_data(buf, &data, &len);
            
            data_ptr = (char*)data;
            end_of_data = data_ptr;
            
            while(data_ptr)
            {
                // If this file is the dandelion firmware image
                if(strncmp(data_ptr, "DANDELION", 9) == 0)
                {
                    // Advance to the \n character
                    while(*end_of_data != '\n')
                    {
                        end_of_data++;
                    }
                }
                
                // If this file is the sunflower firmware image
                if(strncmp(data_ptr, "SUNFLOWER", 9) == 0)
                {
                    
                }
            }
            
            INFO("%s\n", (char*)data);
        } while (netbuf_next(buf) >= 0);
        netbuf_delete(buf);
    }
    
    netconn_delete(g_data);
    g_data = NULL;
    
    return true;
}

void FTP_Get(void)
{
    
}
