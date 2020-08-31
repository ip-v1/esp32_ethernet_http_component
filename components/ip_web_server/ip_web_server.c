/**
 * @file ip_web_server.c
 * @author Inderpreet Singh
 * @brief web server implementation
 * @version 0.1
 * @date 2020-08-25
 *
 * @copyright Copyright (c) 2020
 *
 * This file contains all the code relevant to the web server on the embedded
 * module. It contains the URL and URL handlers as well as server code for the
 * project
 */
#include "ip_web_server.h"

const char *TAG = "Jelly Fish";

// const char report[] = "{primary_cpu: ESP32, secondary_cpu: absent}";

/**
 * @brief HTTP GET Handler
 *
 * @param req
 * @return esp_err_t
 */
esp_err_t api_get_handler(httpd_req_t *req) {
  char *buf;
  size_t buf_len;

  /* Get header value string length and allocate memory for length + 1,
   * extra byte for null termination */
  buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
  if (buf_len > 1) {
    buf = malloc(buf_len);
    /* Copy null terminated value string into buffer */
    if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK) {
      ESP_LOGI(TAG, "Found header => Host: %s", buf);
    }
    free(buf);
  }

  // buf_len = httpd_req_get_hdr_value_len(req, "Test-Header-2") + 1;
  // if (buf_len > 1) {
  //   buf = malloc(buf_len);
  //   if (httpd_req_get_hdr_value_str(req, "Test-Header-2", buf, buf_len) ==
  //       ESP_OK) {
  //     ESP_LOGI(TAG, "Found header => Test-Header-2: %s", buf);
  //   }
  //   free(buf);
  // }

  // I dont really care about headers right now.
  // buf_len = httpd_req_get_hdr_value_len(req, "Test-Header-1") + 1;
  // if (buf_len > 1) {
  //   buf = malloc(buf_len);
  //   if (httpd_req_get_hdr_value_str(req, "Test-Header-1", buf, buf_len) ==
  //       ESP_OK) {
  //     ESP_LOGI(TAG, "Found header => Test-Header-1: %s", buf);
  //   }
  //   free(buf);
  // }

  /* Read URL query string length and allocate memory for length + 1,
   * extra byte for null termination */
  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    buf = malloc(buf_len);
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
      ESP_LOGI(TAG, "Found URL query => %s", buf);
      char param[32];
      /* Get value of expected key from query string */
      if (httpd_query_key_value(buf, "query1", param, sizeof(param)) ==
          ESP_OK) {
        ESP_LOGI(TAG, "Found URL query parameter => query1=%s", param);
        if (strcmp(param, "1")) {
          trigger_io(); // trigger io if url has ?query1=1
        }
      }
      if (httpd_query_key_value(buf, "query3", param, sizeof(param)) ==
          ESP_OK) {
        ESP_LOGI(TAG, "Found URL query parameter => query3=%s", param);
      }
      if (httpd_query_key_value(buf, "query2", param, sizeof(param)) ==
          ESP_OK) {
        ESP_LOGI(TAG, "Found URL query parameter => query2=%s", param);
      }
    }
    free(buf);
  }

  /* Set some custom headers */
  // httpd_resp_set_hdr(req, "Custom-Header-1", "Custom-Value-1");
  // httpd_resp_set_hdr(req, "Custom-Header-2", "Custom-Value-2");

  /* Send response with custom headers and body set as the
   * string passed in user context*/
  // const char *resp_str = (const char *)req->user_ctx;
  const char *resp_str = (const char *)get_status();
  httpd_resp_send(req, resp_str, sizeof(Status));
  trigger_io();

  /* After sending the HTTP response the old HTTP request
   * headers are lost. Check if HTTP request headers can be read now. */
  // if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
  //   ESP_LOGI(TAG, "Request headers lost");
  // }
  return ESP_OK;
}

const httpd_uri_t api = {.uri = "/api",
                         .method = HTTP_GET,
                         .handler = api_get_handler,
                         /* Let's pass response string in user
                          * context to demonstrate it's usage */
                         .user_ctx = NULL};

/**
 * @brief HTTP GET Handler
 *
 * @param req
 * @return esp_err_t
 */
esp_err_t hello_get_handler(httpd_req_t *req) {
  char *buf;
  size_t buf_len;

  /* Get header value string length and allocate memory for length + 1,
   * extra byte for null termination */
  buf_len = httpd_req_get_hdr_value_len(req, "Host") + 1;
  if (buf_len > 1) {
    buf = malloc(buf_len);
    /* Copy null terminated value string into buffer */
    if (httpd_req_get_hdr_value_str(req, "Host", buf, buf_len) == ESP_OK) {
      ESP_LOGI(TAG, "Found header => Host: %s", buf);
    }
    free(buf);
  }

  buf_len = httpd_req_get_hdr_value_len(req, "Test-Header-2") + 1;
  if (buf_len > 1) {
    buf = malloc(buf_len);
    if (httpd_req_get_hdr_value_str(req, "Test-Header-2", buf, buf_len) ==
        ESP_OK) {
      ESP_LOGI(TAG, "Found header => Test-Header-2: %s", buf);
    }
    free(buf);
  }

  buf_len = httpd_req_get_hdr_value_len(req, "Test-Header-1") + 1;
  if (buf_len > 1) {
    buf = malloc(buf_len);
    if (httpd_req_get_hdr_value_str(req, "Test-Header-1", buf, buf_len) ==
        ESP_OK) {
      ESP_LOGI(TAG, "Found header => Test-Header-1: %s", buf);
    }
    free(buf);
  }

  /* Read URL query string length and allocate memory for length + 1,
   * extra byte for null termination */
  buf_len = httpd_req_get_url_query_len(req) + 1;
  if (buf_len > 1) {
    buf = malloc(buf_len);
    if (httpd_req_get_url_query_str(req, buf, buf_len) == ESP_OK) {
      ESP_LOGI(TAG, "Found URL query => %s", buf);
      char param[32];
      /* Get value of expected key from query string */
      if (httpd_query_key_value(buf, "query1", param, sizeof(param)) ==
          ESP_OK) {
        ESP_LOGI(TAG, "Found URL query parameter => query1=%s", param);
      }
      if (httpd_query_key_value(buf, "query3", param, sizeof(param)) ==
          ESP_OK) {
        ESP_LOGI(TAG, "Found URL query parameter => query3=%s", param);
      }
      if (httpd_query_key_value(buf, "query2", param, sizeof(param)) ==
          ESP_OK) {
        ESP_LOGI(TAG, "Found URL query parameter => query2=%s", param);
      }
    }
    free(buf);
  }

  /* Set some custom headers */
  httpd_resp_set_hdr(req, "Custom-Header-1", "Custom-Value-1");
  httpd_resp_set_hdr(req, "Custom-Header-2", "Custom-Value-2");

  /* Send response with custom headers and body set as the
   * string passed in user context*/
  // const char *resp_str = (const char *)req->user_ctx;
  const char *resp_str = (const char *)get_data_share();
  httpd_resp_send(req, resp_str, strlen(resp_str));
  trigger_io();

  /* After sending the HTTP response the old HTTP request
   * headers are lost. Check if HTTP request headers can be read now. */
  if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
    ESP_LOGI(TAG, "Request headers lost");
  }
  return ESP_OK;
}

const httpd_uri_t info = {.uri = "/info",
                          .method = HTTP_GET,
                          .handler = hello_get_handler,
                          /* Let's pass response string in user
                           * context to demonstrate it's usage */
                          .user_ctx = NULL};

/* An HTTP POST handler */
esp_err_t echo_post_handler(httpd_req_t *req) {
  char buf[100];
  int ret, remaining = req->content_len;

  while (remaining > 0) {
    /* Read the data for the request */
    if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) <= 0) {
      if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
        /* Retry receiving if timeout occurred */
        continue;
      }
      return ESP_FAIL;
    }

    /* Send back the same data */
    httpd_resp_send_chunk(req, buf, ret);
    remaining -= ret;

    /* Log data received */
    ESP_LOGI(TAG, "=========== RECEIVED DATA ==========");
    ESP_LOGI(TAG, "%.*s", ret, buf);
    ESP_LOGI(TAG, "====================================");
  }

  // End response
  httpd_resp_send_chunk(req, NULL, 0);
  return ESP_OK;
}

const httpd_uri_t echo = {.uri = "/echo",
                          .method = HTTP_POST,
                          .handler = echo_post_handler,
                          .user_ctx = NULL};

/**
 * @brief 404 handler
 *
 *  This handler allows the custom error handling functionality to be
 * tested from client side. For that, when a PUT request 0 is sent to
 * URI /ctrl, the /info and /echo URIs are unregistered and following
 * custom error handler http_404_error_handler() is registered.
 * Afterwards, when /info or /echo is requested, this custom error
 * handler is invoked which, after sending an error message to client,
 * either closes the underlying socket (when requested URI is /echo)
 * or keeps it open (when requested URI is /info). This allows the
 * client to infer if the custom error handler is functioning as expected
 * by observing the socket state.
 */
esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err) {
  if (strcmp("/info", req->uri) == 0) {
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/info URI is not available");
    /* Return ESP_OK to keep underlying socket open */
    return ESP_OK;
  } else if (strcmp("/echo", req->uri) == 0) {
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "/echo URI is not available");
    /* Return ESP_FAIL to close underlying socket */
    return ESP_FAIL;
  }
  /* For any other URI send 404 and close socket */
  httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
  return ESP_FAIL;
}

/* An HTTP PUT handler. This demonstrates realtime
 * registration and deregistration of URI handlers
 */
esp_err_t ctrl_put_handler(httpd_req_t *req) {
  char buf;
  int ret;

  if ((ret = httpd_req_recv(req, &buf, 1)) <= 0) {
    if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
      httpd_resp_send_408(req);
    }
    return ESP_FAIL;
  }

  if (buf == '0') {
    /* URI handlers can be unregistered using the uri string */
    ESP_LOGI(TAG, "Unregistering /info and /echo URIs");
    httpd_unregister_uri(req->handle, "/info");
    httpd_unregister_uri(req->handle, "/echo");
    /* Register the custom error handler */
    httpd_register_err_handler(req->handle, HTTPD_404_NOT_FOUND,
                               http_404_error_handler);
  } else {
    ESP_LOGI(TAG, "Registering /info and /echo URIs");
    httpd_register_uri_handler(req->handle, &info);
    httpd_register_uri_handler(req->handle, &echo);
    /* Unregister custom error handler */
    httpd_register_err_handler(req->handle, HTTPD_404_NOT_FOUND, NULL);
  }

  /* Respond with empty body */
  httpd_resp_send(req, NULL, 0);
  return ESP_OK;
}

const httpd_uri_t ctrl = {.uri = "/ctrl",
                          .method = HTTP_PUT,
                          .handler = ctrl_put_handler,
                          .user_ctx = NULL};

httpd_handle_t start_webserver(void) {
  httpd_handle_t server = NULL;
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();

  // Start the httpd server
  ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
  if (httpd_start(&server, &config) == ESP_OK) {
    // Set URI handlers
    ESP_LOGI(TAG, "Registering URI handlers");
    httpd_register_uri_handler(server, &info);
    httpd_register_uri_handler(server, &echo);
    httpd_register_uri_handler(server, &ctrl);
    httpd_register_uri_handler(server, &api);
    return server;
  }

  ESP_LOGI(TAG, "Error starting server!");
  return NULL;
}

void stop_webserver(httpd_handle_t server) {
  // Stop the httpd server
  httpd_stop(server);
}

/**
 * @brief Web server disconnect hander
 *
 * @param arg
 * @param event_base
 * @param event_id
 * @param event_data
 */
void disconnect_handler(void *arg, esp_event_base_t event_base,
                        int32_t event_id, void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server) {
    ESP_LOGI(TAG, "Stopping webserver");
    stop_webserver(*server);
    *server = NULL;
  }
}

/**
 * @brief Web server connection handler
 *
 * @param arg
 * @param event_base
 * @param event_id
 * @param event_data
 */
void connect_handler(void *arg, esp_event_base_t event_base, int32_t event_id,
                     void *event_data) {
  httpd_handle_t *server = (httpd_handle_t *)arg;
  if (*server == NULL) {
    ESP_LOGI(TAG, "Starting webserver");
    *server = start_webserver();
  }
}
