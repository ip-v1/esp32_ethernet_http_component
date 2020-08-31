/**
 * @file data_share.c
 * @author Inderpreet Singh
 * @brief Code for shared data and getter and setter functions.
 * @version 0.1
 * @date 2020-08-26
 *
 * @copyright Copyright (c) 2020
 *
 */
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <data_share.h>
#include <stdio.h>
#include <string.h>

#define TRIG_PIN GPIO_NUM_32
#define SENSOR_PIN GPIO_NUM_36

unsigned int trigger_count = 0;
unsigned int get_trigger_count() { return trigger_count; }
void reset_trigger_count(void) { trigger_count = 0; }

Status status;
Status *get_status(void) { return &status; }

char report[50];
char tmp[5];

/**
 * @brief Get the data share object
 *
 * @return char*
 */
char *get_data_share(void) {
  memcpy(report, "{primary_cpu: ESP32, secondary_cpu: absent}", 43);
  return report;
}

/**
 * @brief Set the data share object
 *
 * @param data
 * @param size
 */
void set_data_share(char *data, unsigned char size) {
  memcpy(report, data, size);
}

void setup_ios(void) {
  gpio_reset_pin(TRIG_PIN);
  gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
  gpio_set_level(TRIG_PIN, 1);

  gpio_reset_pin(SENSOR_PIN);
  gpio_set_direction(SENSOR_PIN, GPIO_MODE_INPUT);
}

void trigger_io(void) {
  vTaskDelay(500 / portTICK_PERIOD_MS);
  gpio_set_level(TRIG_PIN, 0);
  vTaskDelay(550 / portTICK_PERIOD_MS);
  gpio_set_level(TRIG_PIN, 1);
}

char read_sensor_gpio() {
  static char last_gpio_state = '1'; // assume GPIO was high

  switch (last_gpio_state) {
  case '0':
    if (gpio_get_level(SENSOR_PIN) == 1) {
      last_gpio_state = '1';
      trigger_count++;
    }
    break;
  case '1':
    if (gpio_get_level(SENSOR_PIN) == 0) {
      last_gpio_state = '0';
      // do nothing
    }
    break;
  default:
    break;
  }
  return last_gpio_state;
}

void control_task(void *pvParameters) {
  for (;;) {
    status.sensorState = read_sensor_gpio();
    sprintf(tmp, "%04d", trigger_count);
    memcpy(status.triggerCount, tmp, 4);
    vTaskDelay(25 / portTICK_PERIOD_MS);
  }
}

void start_task_control() {
  setup_ios();
  status.sof = '{';
  strcpy(status.sensorStateString, "Sensor State: ");
  status.sensorState = '1';
  status.c1 = ',';
  strcpy(status.triggerCountString, "Trigger Count: ");
  strcpy(status.triggerCount, "0000");
  status.eof = '}';
  xTaskCreate(&control_task, "Control Task", 2048, NULL, 5, NULL);
}
