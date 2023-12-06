#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"
#include "tcpip_adapter.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "esp_tls.h"

#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_sleep.h"

#include "ssd1306.h"
#include "font8x8_basic.h"
#include "htmlMenu.h"

#define tag "SSD1306"

#define WEB_SERVER "www.hipochondri.hu"
#define WEB_PORT "80"
#define WEB_URL "http://hipochondri.hu/temperature.php?value="

static const char *TAG = "example";


static char REQUEST[300];



void io_init();


#define DEFAULT_VREF    1100        //Use adc2_vref_to_gpio() to obtain a better estimate
#define NO_OF_SAMPLES   64          //Multisampling

static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_3;     //GPIO34 if ADC1, GPIO14 if ADC2
static const adc_atten_t atten = ADC_ATTEN_DB_0;
static const adc_unit_t unit = ADC_UNIT_1;

static void check_efuse()
{
    //Check TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

static void print_char_val_type(esp_adc_cal_value_t val_type)
{
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        printf("Characterized using Two Point Value\n");
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        printf("Characterized using eFuse Vref\n");
    } else {
        printf("Characterized using Default Vref\n");
    }
}

		uint16_t adc_max=0;
        uint16_t adc_min=0;
        uint16_t adc_temp=20000;
        double temp_max=-100;
		double temp_min=100;
		double temp_temp=0;

		esp_err_t event_handler(void *ctx, system_event_t *event)
		{
		    return ESP_OK;
		}

void app_main()
{
		SSD1306_t dev;
		int center, top, bottom;
		char lineChar[20];

		static httpd_handle_t server = NULL;
		//ESP_ERROR_CHECK( esp_event_loop_init(event_handler, NULL) );
		ESP_ERROR_CHECK(esp_event_loop_create_default());
		nvs_flash_init();
		//tcpip_adapter_init();
		//wifi_init_softap();

		ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT,IP_EVENT_AP_STAIPASSIGNED, &connect_handler, &server));
		/*while(1)
			{
			vTaskDelay(40000 / portTICK_PERIOD_MS);
			}*/

	#if CONFIG_I2C_INTERFACE
		ESP_LOGI(tag, "INTERFACE is i2c");
		ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
		ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
		ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
		i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
	#endif // CONFIG_I2C_INTERFACE
		#if CONFIG_SSD1306_128x64
			ESP_LOGI(tag, "Panel is 128x64");
			ssd1306_init(&dev, 128, 64);
		#endif // CONFIG_SSD1306_128x64





	 const struct addrinfo hints = {
	        .ai_family = AF_INET,
	        .ai_socktype = SOCK_STREAM,
	    };
	    struct addrinfo *res;
	    struct in_addr *addr;
	    int s, r;
	    char recv_buf[64];
        check_efuse();
        /*ide illeszem be az uj dolgokat */
        io_init();


        /*Idaig*/


        printf("Exit deep sleep mode\r\n");
//vTaskDelay(4000 / portTICK_PERIOD_MS);
        //Configure ADC
        if (unit == ADC_UNIT_1) {
            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(channel, atten);
        } else {
            adc2_config_channel_atten((adc2_channel_t)channel, atten);
        }

        //Characterize ADC
        adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
        esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars);
        print_char_val_type(val_type);

        //Continuously sample ADC1
        uint darab=0;
        double temp=0;

        while (1) {
        	//ssd1306_clear_screen(&dev, false);
            uint32_t adc_reading = 0;
            //Multisampling
            for (int i = 0; i < NO_OF_SAMPLES; i++) {
                if (unit == ADC_UNIT_1) {
                	adc_temp=adc1_get_raw((adc1_channel_t)channel);
                    adc_reading += adc_temp;
                    if(adc_max<adc_temp)
                    {
                    	adc_max=adc_temp;
                    }
                    if(adc_min>adc_temp)
					{
						adc_min=adc_temp;
					}
                } else {
                    int raw;
                    adc2_get_raw((adc2_channel_t)channel, ADC_WIDTH_BIT_12, &raw);
                    adc_reading += raw;
                }
            }
            adc_reading-=(adc_max+adc_min);
            adc_reading /= NO_OF_SAMPLES;
            adc_reading=(adc_reading+((adc_max+adc_min)/2))/2;
            adc_min=20000;
            adc_max=0;
            //Convert adc_reading to voltage in mV
            int32_t voltage =(int32_t) esp_adc_cal_raw_to_voltage(adc_reading, adc_chars);
            temp_temp=(double)(voltage-500)/10;
            temp+=temp_temp;
            if(temp_max<temp_temp)
			  {
				temp_max=temp_temp;
			  }
			  if(temp_min>temp_temp)
			{
				temp_min=temp_temp;
			}
				darab++;
            if(darab==60)
            {
            	darab=0;
            	char hofokString[10];
            	memset(hofokString,0,10);
            	double hofok=0;
            	hofok=(temp-(temp_max+temp_min))/58;
            	sprintf(hofokString," %.1fC",hofok);
				ssd1306_clear_screen(&dev, false);
				ssd1306_contrast(&dev, 0x1);
				ssd1306_display_text_x3(&dev, 0, "Temp:", 4, false);
				ssd1306_display_text_x3(&dev, 4, hofokString, strlen(hofokString), false);
			 // ESP_ERROR_CHECK( nvs_flash_init() );
				tcpip_adapter_init();
			    //ESP_ERROR_CHECK(esp_event_loop_create_default());
			    ESP_ERROR_CHECK(example_connect());
            	sprintf(REQUEST, "GET " WEB_URL "%f HTTP/1.0\r\n" "Host: "WEB_SERVER"\r\n" "User-Agent: esp-idf/1.0 esp32\r\n""\r\n",(hofok));
            	printf(REQUEST);
            	//vTaskDelay(1000 /  portTICK_PERIOD_MS);
            	printf("Raw: %d\tVoltage: %f C\n", adc_reading, temp/60);
            	temp=0;

            	int err = getaddrinfo(WEB_SERVER, "80", &hints, &res);

            	        if(err != 0 || res == NULL) {
            	            ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
            	            vTaskDelay(1000 / portTICK_PERIOD_MS);
            	            continue;
            	        }

            	        /* Code to print the resolved IP.

            	           Note: inet_ntoa is non-reentrant, look at ipaddr_ntoa_r for "real" code */
            	        addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
            	        ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

            	        s = socket(res->ai_family, res->ai_socktype, 0);
            	        if(s < 0) {
            	            ESP_LOGE(TAG, "... Failed to allocate socket.");
            	            freeaddrinfo(res);
            	            vTaskDelay(1000 / portTICK_PERIOD_MS);
            	            continue;
            	        }
            	        ESP_LOGI(TAG, "... allocated socket");

            	        if(connect(s, res->ai_addr, res->ai_addrlen) != 0) {
            	            ESP_LOGE(TAG, "... socket connect failed errno=%d", errno);
            	            close(s);
            	            freeaddrinfo(res);
            	            vTaskDelay(4000 / portTICK_PERIOD_MS);
            	            continue;
            	        }

            	        ESP_LOGI(TAG, "... connected");
            	        freeaddrinfo(res);

            	        if (write(s, REQUEST, strlen(REQUEST)) < 0) {
            	            ESP_LOGE(TAG, "... socket send failed");
            	            close(s);
            	            vTaskDelay(4000 / portTICK_PERIOD_MS);
            	            continue;
            	        }
            	        ESP_LOGI(TAG, "... socket send success");

            	        struct timeval receiving_timeout;
            	        receiving_timeout.tv_sec = 5;
            	        receiving_timeout.tv_usec = 0;
            	        if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout,
            	                sizeof(receiving_timeout)) < 0) {
            	            ESP_LOGE(TAG, "... failed to set socket receiving timeout");
            	            close(s);
            	            vTaskDelay(4000 / portTICK_PERIOD_MS);
            	            continue;
            	        }
            	        ESP_LOGI(TAG, "... set socket receiving timeout success");

            	        /* Read HTTP response */
            	        do {
            	            bzero(recv_buf, sizeof(recv_buf));
            	            r = read(s, recv_buf, sizeof(recv_buf)-1);
            	            for(int i = 0; i < r; i++) {
            	               // putchar(recv_buf[i]);
            	            }
            	        } while(r > 0);

            	        ESP_LOGI(TAG, "... done reading from socket. Last read return=%d errno=%d.", r, errno);
            	        close(s);


            	        temp_min=100;
						temp_max=-100;
						printf("Enter deep sleep mode\r\n");
						//ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_16, 0));
						esp_deep_sleep(600*1000*1000);

            }


            vTaskDelay(10/portTICK_PERIOD_MS);
        }


}
 void io_init()
 {
	 /* Left (boot) button to input */
	 PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_NUM_0], PIN_FUNC_GPIO);
	 gpio_set_direction(GPIO_NUM_0,GPIO_MODE_INPUT);
	 /*Right button to input*/
	 PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_NUM_34], PIN_FUNC_GPIO);
	 gpio_set_direction(GPIO_NUM_34,GPIO_MODE_INPUT);
	 /*Temperature sensor ENABLE*/
	PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[GPIO_NUM_16], PIN_FUNC_GPIO);
	ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_16, GPIO_MODE_OUTPUT));
	ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_16, 1));

 }
