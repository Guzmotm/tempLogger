#ifndef MAIN_HTMLMENU_H_
#define MAIN_HTMLMENU_H_
/*wifi*/

#include "esp_log.h"
#include <sys/param.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include <esp_http_server.h>
#include "esp_wifi.h"
#include "stdlib.h"


#define EXAMPLE_ESP_WIFI_SSID      "TempLogger"
#define EXAMPLE_ESP_WIFI_PASS      "12345678"
#define EXAMPLE_ESP_WIFI_CHANNEL   1
#define EXAMPLE_MAX_STA_CONN       4

extern TaskHandle_t taskhandle;


void connect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
void wifi_init_softap(void);
esp_err_t defaulHTTP_handler(httpd_req_t *req);

#endif /* MAIN_HTMLMENU_H_ */
