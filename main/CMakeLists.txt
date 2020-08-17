idf_component_register(SRCS "ethernet_example_main.c" 
                       INCLUDE_DIRS "." ""
                       REQUIRES esp_http_server nvs_flash
                       )
