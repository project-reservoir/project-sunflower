#include "console.h"
#include "debug.h"
#include "FreeRTOS.h"

#include "lwip/opt.h"
#include "lwip/sys.h"
#include "lwip/api.h"

void tcp_task(void)
{
    struct netconn *conn, *newconn;
    err_t err;

    conn = netconn_new(NETCONN_TCP);

    if(conn != NULL) 
    {  
        err = netconn_bind(conn, NULL, 7);

        if (err == ERR_OK) 
        {
            /* Tell connection to go into listening mode. */
            netconn_listen(conn);

            while (1) 
            {
                /* Grab new connection. */
                newconn = netconn_accept(conn);

                /* Process the new connection. */
                if (newconn) {
                    struct netbuf *buf;
                    void *data;
                    u16_t len;

                    while ((buf = netconn_recv(newconn)) != NULL) 
                    {
                        do 
                        {
                            netbuf_data(buf, &data, &len);              
                            netconn_write(newconn, data, len, NETCONN_COPY);

                        } while(netbuf_next(buf) >= 0);
                      
                        netbuf_delete(buf);
                    }

                    /* Close connection and discard connection identifier. */
                    netconn_close(newconn);
                    netconn_delete(newconn);
                }
            }
        }
        else
        {
            printf(" can not bind TCP netconn");
        }
    } 
    else 
    {
        printf("can not create TCP netconn");
    }
}