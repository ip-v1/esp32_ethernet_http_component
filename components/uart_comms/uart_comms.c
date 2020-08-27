#include "uart_comms.h"
#include <data_share.h>
#include <stdio.h>

typedef struct _InfoT {
  char sof;
  char ver[3];
  char str[64];
} InfoT;

InfoT infoT;

void vTaskCode(void *pvParameters) {
  // uint8_t data* = malloc(1024);
  for (;;) {
    static uint8_t state = 0;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    const char msg[] = "Hello World\n\r";
    // int len;
    switch (state) {
    case 0: // init state
      uart_driver_install(UART_NUM_1, 2048, 0, 0, NULL, 0);
      uart_param_config(UART_NUM_1, &uart_config);
      ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, U1_TXD, U1_RXD, NC, NC));
      state = 1;
      break;
    case 1: // work state
      // len = uart_read_bytes(UART_NUM_2, data, 1024, 20/portTICK_RATE_MS);
      uart_write_bytes(UART_NUM_1, (const char *)msg, 13);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      break;
    default:
      break;
    }
  }
  // for (;;)
  // {
  //     // Task Code here
  //     printf("%s\n", infoT.str);
  //     vTaskDelay(1000 / portTICK_PERIOD_MS);
  // }
}

void start_task_test() {
  xTaskCreate(&vTaskCode, "my task 1", 2048, NULL, 5, NULL);
  sprintf(infoT.str, "Test String from Main");
}
