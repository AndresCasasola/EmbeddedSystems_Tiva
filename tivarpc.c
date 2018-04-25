/*
 * tivarpc.c
 *
 * Implementa la funcionalidad RPC entre la TIVA y el interfaz de usuario
 *
 */

#include <tivarpc.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "utils/uartstdio.h"
#include "drivers/buttons.h"
#include "drivers/rgb.h"
#include "usb_dev_serial.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "rpc_commands.h"

//Defino a un tipo que es un puntero a funcion con el prototipo que tienen que tener las funciones que definamos
typedef int32_t (*rpc_function_prototype)(uint32_t param_size, void *param);

// Globales
static uint8_t Rxframe[MAX_FRAME_SIZE];	//Usar una global permite ahorrar pila en la tarea de RX.
static uint8_t Txframe[MAX_FRAME_SIZE]; //Usar una global permite ahorrar pila en las tareas, pero hay que tener cuidado al transmitir desde varias tareas!!!!
static uint32_t gRemoteProtocolErrors=0;
TaskHandle_t xHandle=NULL;  // Manejador de la tarea para poder eliminarla
static int32_t TivaRPC_ReceiveFrame(uint8_t *frame, int32_t maxFrameSize);


    /**************  INICIO: TAREA BOTONES :INICIO  **************/

static portTASK_FUNCTION( TivaRPC_ButtonsTask, pvParameters ){

    UARTprintf("Buttons task working...\n");
    if ((buttonsQueue = xQueueCreate(MAX_BUTTONS_QUEUE_ELEMENTS, 2*sizeof(bool))) == NULL )
    {
        while(1);
    }

    bool buttons[2];

    while(1){
        xQueueReceive(buttonsQueue, (void *) buttons, portMAX_DELAY);

        PARAMETERS_SWITCHES_INTERRUPT parametro;
        parametro.state1=buttons[0];
        parametro.state2=buttons[1];

        TivaRPC_SendFrame(COMMAND_SWITCHES_INTERRUPT, &parametro, sizeof(parametro));
    }
}
    /**************  FIN: TAREA BOTONES :FIN  **************/

/*  =====================================================================================  */
/*  ==============  INICIO: Funciones RPC (Remote Procedure Call) :INICIO  ==============  */
/*  =====================================================================================  */

//Funcion que se ejecuta cuando llega un paquete indicando comando rechazado
static int32_t RPC_RejectedCommand(uint32_t param_size, void *param)
{
    //He recibido "Comando rechazado" desde el PC
    //TODO, por hacer: Tratar dicho error??
    gRemoteProtocolErrors++;
    return 0;
}


//Funcion que se ejecuta cuando llega un PING
static int32_t RPC_Ping(uint32_t param_size, void *param)
{
    int32_t numdatos;

    numdatos=TivaRPC_SendFrame(COMMAND_PING,NULL,0);
    return numdatos;
}

//Funcion que se ejecuta cuando llega el comando que configura los LEDS
static int32_t RPC_LEDGpio(uint32_t param_size, void *param)
{
    PARAMETERS_LED_GPIO parametro;

    if (check_and_extract_command_param(param, param_size, sizeof(parametro),&parametro)>0)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,parametro.value);
        return 0;	//Devuelve Ok (valor mayor no negativo)
    }
    else
    {
        return PROT_ERROR_INCORRECT_PARAM_SIZE; //Devuelve un error
    }
}

//Funcion que se ejecuta cuando recibimos un comando que no tenemos aun implementado
static int32_t RPC_GpioPwmMode(uint32_t param_size, void *param)
{
    PARAMETERS_GPIO_PWM_MODE parametro;
    int32_t i32Status=0;

    if (check_and_extract_command_param(param, param_size, sizeof(parametro),&parametro)>0)
    {
        if(parametro.mode == 0){
            RGBDisable();
            ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
        }else if(parametro.mode == 1)
            RGBEnable();

        if(i32Status == -1) // CMDLINE_BAD_CMD = -1
        {
            UARTprintf("Error en RPC_GpioPwmMode !\n");   //No pongo acentos adrede
        }
        return 0;   //Devuelve Ok (valor mayor no negativo)
    }
    else
    {
        return PROT_ERROR_INCORRECT_PARAM_SIZE; //Devuelve un error
    }
}

//Funcion que se ejecuta cuando recibimos un comando que no tenemos aun implementado
static int32_t RPC_UnimplementedCommand(uint32_t param_size, void *param)
{
    return PROT_ERROR_UNIMPLEMENTED_COMMAND;
}

//Funcion que se ejecuta cuando llega el comando que configura el BRILLO
static int32_t RPC_LEDPwmBrightness(uint32_t param_size, void *param)
{
    PARAMETERS_LED_PWM_BRIGHTNESS parametro;


    if (check_and_extract_command_param(param, param_size, sizeof(parametro),&parametro)>0)
    {


        RGBIntensitySet(parametro.rIntensity);

        return 0;	//Devuelve Ok (valor mayor no negativo)
    }
    else
    {
        return PROT_ERROR_INCORRECT_PARAM_SIZE; //Devuelve un error
    }
}

static int32_t RPC_LEDPwmColor(uint32_t param_size, void *param)
{
    PARAMETERS_LED_PWM_COLOR parametro;
    int i;

    if (check_and_extract_command_param(param, param_size, sizeof(parametro),&parametro)>0)
    {

        for(i=0; i<3; i++){
            parametro.rgb[i] *= 255;
        }

        RGBColorSet(parametro.rgb);

        return 0;   //Devuelve Ok (valor mayor no negativo)
    }
    else
    {
        return PROT_ERROR_INCORRECT_PARAM_SIZE; //Devuelve un error
    }
}

static int32_t RPC_SwitchesSound(uint32_t param_size, void *param)
{
    PARAMETERS_SWITCHES_SOUND parametro;

    // Sondeo Switches
    parametro.state1=( 0 == GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) );
    parametro.state2=( 0 == GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) );

    return TivaRPC_SendFrame(COMMAND_SWITCHES_SOUND,&parametro,sizeof(parametro));

}

static int32_t RPC_SwitchesInterruptEnable(uint32_t param_size, void *param)
{
    PARAMETERS_SWITCHES_INTERRUPT_ENABLE parametro;

    if (check_and_extract_command_param(param, param_size, sizeof(parametro),&parametro)>0)
    {
        if(parametro.check){

            if((xTaskCreate(TivaRPC_ButtonsTask, (portCHAR *)"TivaRPC_ButtonsTask", 512,NULL,tskIDLE_PRIORITY + 1, &xHandle) != pdTRUE))
            {
                    while(1);
            }

            GPIOIntClear(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
            GPIOIntEnable(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
            IntEnable(INT_GPIOF);

        }else{

            vQueueDelete(buttonsQueue);
            GPIOIntDisable(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
            GPIOIntClear(GPIO_PORTF_BASE,GPIO_PIN_4|GPIO_PIN_0);
            vTaskDelete(xHandle);
        }

    }
    return 0;
}
/*  ===============================================================================  */
/*  ==============  FIN: Funciones RPC (Remote Procedure Call) :FIN  ==============  */
/*  ===============================================================================  */


/*  =================================================================  */
/*  ===================  TABLA DE FUNCIONES RPC  ====================  */
/*  =================================================================  */

/* Array que contiene las funciones que se van a ejecutar en respuesta a cada comando */
static const rpc_function_prototype rpc_function_table[]={
                                            RPC_RejectedCommand,            /* Responde al paquete comando rechazado */
                                            RPC_Ping,                       /* Responde al comando ping */
                                            RPC_LEDGpio,                    /* Responde al comando LEDS */
                                            RPC_LEDPwmBrightness,           /* Responde al comando Brillo */
                                            RPC_GpioPwmMode,                /* Responde al comando Modo (PWM/GPIO) */
                                            RPC_LEDPwmColor,                /* Responde al comando Color */
                                            RPC_SwitchesSound,              /* Responde al comando para sondear los switches */
                                            RPC_SwitchesInterruptEnable,    /* Responde al comando para (des)habilitar las interrupciones de los botones */
                                            RPC_UnimplementedCommand        /* Responde a cualquier comando no declarado */
};

    /**************  INICIO: TAREA SERVER :INICIO  **************/

// Codigo para procesar los comandos recibidos a traves del canal USB del micro ("conector lateral")
//Esta tarea decodifica los comandos y ejecuta la función que corresponda a cada uno de ellos (por posicion)
//También gestiona posibles errores en la comunicacion
static portTASK_FUNCTION( TivaRPC_ServerTask, pvParameters ){

    //Frame es global en este fichero, se reutiliza en las funciones que envian respuestas ---> CUIDADO!!!

    int32_t numdatos;
    uint8_t command;
    void *ptrtoreceivedparam;

    /* The parameters are not used. (elimina el warning)*/
    ( void ) pvParameters;

    for(;;)
    {
        //Espera hasta que se reciba una trama con datos serializados por el interfaz USB
        numdatos=TivaRPC_ReceiveFrame(Rxframe,MAX_FRAME_SIZE); //Esta funcion es bloqueante

        if (numdatos>0)
        {
            //Si no ha habido errores recibiendo la trama, la intenta decodificar y procesar
            //primero se "desestufa" y se comprueba el checksum
            numdatos=destuff_and_check_checksum(Rxframe,numdatos);
            if (numdatos<0)
            {
                //Error de checksum (PROT_ERROR_BAD_CHECKSUM), ignorar el paquete
                gRemoteProtocolErrors++;
                // Procesamiento del error (TODO, POR HACER!!)
            }
            else
            {
                //El paquete esta bien, luego procedo a tratarlo.
                //Obtiene el valor del campo comando
                command=decode_command_type(Rxframe);
                //Obtiene un puntero al campo de parametros y su tamanio.
                numdatos=get_command_param_pointer(Rxframe,numdatos,&ptrtoreceivedparam);

                //Accedemos a la tabla de funciones y ejecutarmos la correspondiente al comando que ha llegado
                //Primero hay que comprobar que el tamanio de dicha tabla es suficiente.

                if (command<(sizeof(rpc_function_table)/sizeof(rpc_function_prototype)))
                {
                    int32_t error_status;
                    //Aqui es donde se ejecuta a funcion de la tabla que corresponde con el valor de comando que ha llegado
                    error_status=rpc_function_table[command](numdatos,ptrtoreceivedparam); //La funcion puede devolver códigos de error.

                    //Una vez ejecutado, se comprueba si ha habido errores.
                    switch(error_status)
                    {

                        //Se procesarían a continuación
                        case PROT_ERROR_NOMEM:
                        {
                            // Procesamiento del error NO MEMORY
                            UARTprintf("RPC Error: not enough memory\n");
                        }
                        break;
                        case PROT_ERROR_STUFFED_FRAME_TOO_LONG:
                        {
                            // Procesamiento del error STUFFED_FRAME_TOO_LONG
                            UARTprintf("RPC Error: Frame too long. Cannot be created\n");
                        }
                        break;
                        case PROT_ERROR_COMMAND_TOO_LONG:
                        {
                            // Procesamiento del error COMMAND TOO LONG
                            UARTprintf("RPC Error: Packet too long. Cannot be allocated\n");
                        }
                        break;
                        case PROT_ERROR_INCORRECT_PARAM_SIZE:
                        {
                            // Procesamiento del error INCORRECT PARAM SIZE
                            UARTprintf("RPC Error: Incorrect parameter size\n");
                        }
                        break;
                        case PROT_ERROR_UNIMPLEMENTED_COMMAND:
                        {
                            PARAMETERS_COMMAND_REJECTED parametro;
                            parametro.command=command;
                            numdatos=TivaRPC_SendFrame(COMMAND_REJECTED,&parametro,sizeof(parametro));
                            UARTprintf("RPC Error: Unexpected command: %x\n",(uint32_t)command);
                            gRemoteProtocolErrors++;
                            //Aqui se podria, ademas, comprobar numdatos....
                        }
                        break;
                        //AÑadir casos de error adicionales aqui...
                        default:
                            /* No hacer nada */
                            break;
                    }
                }
                else
                {
                    /* El valor del comando que ha llegado es superior al numero de comandos que hay implementados en la tabla  */
                    // Se envia el "Comando Rechazado" hacia el GUI
                    PARAMETERS_COMMAND_REJECTED parametro;
                    parametro.command=command;
                    numdatos=TivaRPC_SendFrame(COMMAND_REJECTED,&parametro,sizeof(parametro));
                    UARTprintf("RPC Error: Unexpected command: %x\n",(uint32_t)command);
                    //Aqui se podria, ademas,  comprobar numdatos....
                    gRemoteProtocolErrors++;
                }
            }
        }
        else
        { // if (numdatos >0)
            //Error de recepcion de trama(PROT_ERROR_RX_FRAME_TOO_LONG), ignorar el paquete
            gRemoteProtocolErrors++;
            // Procesamiento del error (TODO)
        }
    }
}
    /**************  FIN: TAREA SERVER :FIN  **************/


//Inicializa la tarea que recibe comandos (se debe llamar desde main())
void TivaRPC_Init(void)
{
    USBSerialInit(32,32);   //Inicializo el  sistema USB-serie

    //
    // Crea la tarea que gestiona los comandos USB (definidos en CommandProcessingTask)
    //
    if(xTaskCreate(TivaRPC_ServerTask, (portCHAR *)"usbser",TIVARPC_TASK_STACK, NULL, TIVARPC_TASK_PRIORITY, NULL) != pdTRUE)
    {
        while(1);
    }

}


// TODO
//Ojo!! TxFrame es global (para ahorrar memoria de pila en las tareas) --> Se deben tomar precauciones al usar esta funcion varias tareas
//IDEM en lo que respecta al envio por la conexion USB serie desde varias tareas....
//Estas precauciones no se han tomado en este codigo de parti1da, pero al realizar la practica se deberian tener en cuenta....
// "TODO" (por hacer)
int32_t TivaRPC_SendFrame(uint8_t comando,void *parameter,int32_t paramsize)
{
    int32_t numdatos;

    numdatos=create_frame(Txframe,comando,parameter,paramsize,MAX_FRAME_SIZE);
    if (numdatos>=0)
    {
        USBSerialWrite(Txframe,numdatos,portMAX_DELAY);
    }

    return numdatos;
}

/* Recibe una trama (sin los caracteres de inicio y fin */
/* Utiliza la funcion bloqueante xSerialGetChar ---> Esta funcion es bloqueante y no se puede llamar desde una ISR !!!*/
// Esta funcion es INTERNA de la biblioteca y solo se utiliza en la rarea TivaRPC_ServerTask
static int32_t TivaRPC_ReceiveFrame(uint8_t *frame, int32_t maxFrameSize)
{
    int32_t i;
    uint8_t rxByte;

    do
    {
        //Elimino bytes de la cola de recepcion hasta llegar a comienzo de nueva trama
        USBSerialGetChar( ( char *)&rxByte, portMAX_DELAY);
    } while (rxByte!=START_FRAME_CHAR);

    i=0;
    do
    {
        USBSerialGetChar( ( char *)frame, portMAX_DELAY);
        i++;
    } while ((*(frame++)!=STOP_FRAME_CHAR)&&(i<=maxFrameSize));

    if (i>maxFrameSize)
    {
        return PROT_ERROR_RX_FRAME_TOO_LONG;    //Numero Negativo indicando error
    }
    else
    {
        return (i-END_SIZE);    //Devuelve el numero de bytes recibidos (quitando el de BYTE DE STOP)
    }
}

