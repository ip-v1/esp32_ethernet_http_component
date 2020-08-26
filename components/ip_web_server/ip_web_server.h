#ifndef _IP_WEB_SERVER_H
#define _IP_WEB_SERVER_H

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tcpip_adapter.h"
#include "esp_eth.h"
#include "esp_event.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "tcpip_adapter.h"

#include <esp_http_server.h>

esp_err_t hello_get_handler(httpd_req_t *req);
esp_err_t echo_post_handler(httpd_req_t *req);
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err);
esp_err_t ctrl_put_handler(httpd_req_t *req);

httpd_handle_t start_webserver(void);
void stop_webserver(httpd_handle_t server);
void disconnect_handler(void* arg, esp_event_base_t event_base, 
                               int32_t event_id, void* event_data);
void connect_handler(void* arg, esp_event_base_t event_base, 
                            int32_t event_id, void* event_data);

#endif
