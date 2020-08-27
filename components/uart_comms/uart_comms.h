#ifndef _UART_COMMS_H
#define _UART_COMMS_H

#include "driver/gpio.h"
#include "driver/uart.h"

#define U1_TXD (GPIO_NUM_4)
#define U1_RXD (GPIO_NUM_5)
#define NC (UART_PIN_NO_CHANGE)

#define SCL1_PIN GPIO_NUM_12
#define SDA1_PIN GPIO_NUM_14

void start_task_test(void);

#endif
