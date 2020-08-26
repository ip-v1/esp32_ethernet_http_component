#ifndef _UART_COMMS_H
#define _UART_COMMS_H

#include "driver/gpio.h"
#include "driver/uart.h"

#define U1_TXD (GPIO_NUM_4)
#define U1_RXD (GPIO_NUM_2)
#define NC (UART_PIN_NO_CHANGE)

void start_task_test(void);

#endif
