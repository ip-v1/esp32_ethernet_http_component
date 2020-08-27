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
#include <data_share.h>
#include <stdio.h>
#include <string.h>

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
