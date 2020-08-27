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

char report[50];

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

void setup_trigger_pin(void) {
  gpio_reset_pin(TRIG_PIN);
  gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
}

void trigger_io(void) {
  vTaskDelay(500 / portTICK_PERIOD_MS);
  gpio_set_level(TRIG_PIN, 1);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  gpio_set_level(TRIG_PIN, 0);
}
