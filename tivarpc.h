/*
 * tivarpc.h
 *
 *  Fichero de cabecera. Implementa la funcionalidad RPC entre la TIVA y el interfaz de usuario
 *
 */

#ifndef TIVARPC_H__
#define TIVARPC_H__


#include <stdbool.h>
#include <stdint.h>
#include "serialprotocol.h"
#include "rpc_commands.h"
#include "queue.h"

// Parametros de funcionamiento de la tarea
#define TIVARPC_TASK_STACK (512)
#define TIVARPC_TASK_PRIORITY (tskIDLE_PRIORITY+2)

// Parametros cola
#define MAX_BUTTONS_QUEUE_ELEMENTS 10
xQueueHandle buttonsQueue;      //QueueHandle_t buttonsQueue;

void TivaRPC_Init(void);
int32_t TivaRPC_SendFrame(uint8_t comando,void *parameter,int32_t paramsize);

#endif /*TIVARPC_H__ */
