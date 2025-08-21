#ifndef INC_TCPSERVER_H_
#define INC_TCPSERVER_H_

#include "lwip/api.h"	// para keep alive original
#include "lwip/tcp.h" // Necesario para acceso al PCB

#define RETRY_DELAY_MS 5000 // Tiempo de espera para reintentar en caso de error

void tcpserver_init (void);

void enable_keepalive(struct netconn *conn);


extern void SendString(const char *str);
extern void SendNumber(int16_t);

extern void TurnOnRedLED(void);
extern void TurnOffRedLED(void);


#endif /* INC_TCPSERVER_H_ */
