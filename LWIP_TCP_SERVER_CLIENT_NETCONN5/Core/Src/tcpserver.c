#include "lwip/opt.h"
#include "lwip/api.h"
#include "lwip/sys.h"
#include "string.h"



#include "tcpserver.h"
#include "modbus.h"

static struct netconn *conn, *newconn;

static struct netbuf *netbuf;

uint8_t mb_req_buf[MB_ADU_MAXSIZE];
uint8_t mb_repl_buf[MB_ADU_MAXSIZE];

static void copyString(uint8_t* dest, uint8_t* src, unsigned num);

static void process_client_connection(struct netconn *client_conn);
static err_t initialize_server();


// Función principal del hilo TCP
static void tcp_thread(void *arg) {
    err_t server_err, accept_err;

    SendString("*************** Initial thread started and running ******************* \r");

    while (1) {
        // Inicializar el servidor
        server_err = initialize_server();
        if (server_err != ERR_OK) {
            //printf("Error: Reintentando iniciar el servidor en %d ms...\n", RETRY_DELAY_MS);
        	SendString("Error: Reintentando iniciar el servidor");
        	TurnOffRedLED();
            sys_msleep(RETRY_DELAY_MS); // Esperar antes de reintentar (un sleep de la propia librería lwip)
            continue;
        }

        // Aceptar conexiones entrantes
        while (1) {
            accept_err = netconn_accept(conn, &newconn);
            if (accept_err == ERR_OK) {
                //printf("Cliente conectado.\n");
            	SendString("Cliente conectado...\r");
            	holding_registers[MB_SERVER_STATUS] = 1;
                process_client_connection(newconn); // Procesar conexión del cliente
            } else {
                //printf("Error al aceptar conexión (Error: %d). Reintentando...\n", accept_err);
            	SendString("Error al aceptar conexión Reintentando...\n");
                break; // Salir al detectar un error en el servidor
            }
        }

        // Liberar recursos del servidor en caso de error
        //printf("Cerrando servidor...\n");
        SendString("Cerrando servidor...\n");
        netconn_close(conn);
        netconn_delete(conn);
        conn = NULL;

        // Reintentar después de un tiempo
        //printf("Reiniciando servidor en %d ms...\n", RETRY_DELAY_MS);
        SendString("Reiniciando servidor en ms...\n");
        sys_msleep(RETRY_DELAY_MS);  //un sleep de la propia librería lwip
    }
}





void tcpserver_init(void) {
	sys_thread_new("tcp_thread", tcp_thread, NULL, DEFAULT_THREAD_STACKSIZE,
			osPriorityNormal);
}

static void copyString(uint8_t* dest, uint8_t* src, unsigned num){
	for(unsigned i = 0; i != num; ++i){
		dest[i] = src[i];
	}
}


/************************************************************************/
// Función para procesar una conexión de cliente
static void process_client_connection(struct netconn *client_conn) {
    //struct netbuf *netbuf;
    err_t recv_err;

    // Configurar timeout para evitar bloqueos indefinidos
    //netconn_set_recvtimeout(client_conn, 5000); // Timeout de 5 segundos

    while ((recv_err = netconn_recv(client_conn, &netbuf)) == ERR_OK) {
        do {
            copyString(mb_req_buf, netbuf->p->payload, netbuf->p->len); // Obtener mensaje del cliente
            uint16_t buf_len = netbuf->p->len;
            buf_len = mb_process(mb_repl_buf, mb_req_buf, buf_len);    // Procesar datos
            netconn_write(client_conn, mb_repl_buf, buf_len, NETCONN_COPY); // Responder al cliente
        } while (netbuf_next(netbuf) > 0);

        netbuf_delete(netbuf); // Liberar el buffer después de procesarlo
    }

    // Cerrar y liberar la conexión del cliente
    netconn_close(client_conn);
    netconn_delete(client_conn);
    SendString("Desconecto...\r");
    holding_registers[MB_SERVER_STATUS] = 0;
}

// Función para inicializar la conexión TCP
static err_t initialize_server() {
    conn = netconn_new(NETCONN_TCP);
    if (conn == NULL) {
        //printf("Error: No se pudo crear la conexión.\n");
    	SendString("Error: No se pudo crear la conexión.\n");
    	TurnOffRedLED();
        return ERR_MEM;
    }


    err_t err = netconn_bind(conn, IP_ADDR_ANY, MB_TCP_PORT);
    if (err != ERR_OK) {
        //printf("Error: No se pudo enlazar al puerto %d (Error: %d).\n", MB_TCP_PORT, err);
    	SendString("Error: No se pudo enlazar al puerto\n");
    	TurnOffRedLED();
        netconn_delete(conn);
        conn = NULL;
        return err;
    }

    osDelay(1000);
    SendString("Activando Keep-Alive...\r");


    //netconn_set_keepalive(newconn, 1);
    enable_keepalive(conn);

    netconn_listen(conn); // Escuchar conexiones entrantes
    //printf("Servidor TCP escuchando en el puerto %d.\n", MB_TCP_PORT);
    SendString("Servidor TCP escuchando en el puerto: ");
    SendNumber(MB_TCP_PORT);
    SendString("\r");
    TurnOnRedLED();
    return ERR_OK;
}

void enable_keepalive(struct netconn *conn) {
    if (conn != NULL && conn->pcb.tcp != NULL) {
        struct tcp_pcb *pcb = conn->pcb.tcp;

        // Activar opción KEEPALIVE
        pcb->so_options |= SOF_KEEPALIVE;

        // Configurar parámetros de Keep-Alive
        pcb->keep_idle = TCP_KEEPIDLE_DEFAULT;     // Tiempo en ms antes del primer paquete
        pcb->keep_intvl = TCP_KEEPINTVL_DEFAULT;   // Intervalo entre intentos en ms
        pcb->keep_cnt = TCP_KEEPCNT_DEFAULT;       // Número máximo de intentos
    }
}
