
#include "htmlMenu.h"



char *generatedHtml;
char *generatedHtml1;

static const char *TAG = "htmlMenu.c";
TaskHandle_t taskhandle=NULL;

char ** htmlArray[50];
char * htmlhead="\
		<html>\r\n\
			<head>\r\n\
				<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\r\n";
char * css="\
  <style> .switch {\r\n\
     position: relative;\r\n\
     display: inline-block;\r\n\
     width: 15%;\r\n\
     height: 7%;\r\n\
     max-height: 30px;\r\n\
}\r\n\
 .switchDiv {\r\n\
     margin-left:5%;\r\n\
}\r\n\
 .switch input {\r\n\
     opacity: 0;\r\n\
     width: 0;\r\n\
     height: 0;\r\n\
}\r\n\
 .sliderswitch {\r\n\
     position: absolute;\r\n\
     cursor: pointer;\r\n\
     top: 0;\r\n\
     left: 0;\r\n\
     right: 0;\r\n\
     bottom: 0;\r\n\
     background-color: #7e7e7e;\r\n\
     -webkit-transition: .4s;\r\n\
     transition: .4s;\r\n\
}\r\n\
 .sliderswitch:before {\r\n\
     position: absolute;\r\n\
     content: \"\";\r\n\
     height: 80%;\r\n\
     width: 40%;\r\n\
     left: 10%;\r\n\
     bottom: 10%;\r\n\
     background-color: white;\r\n\
     -webkit-transition: .4s;\r\n\
     transition: .4s;\r\n\
}\r\n\
 input:checked + .sliderswitch {\r\n\
     background-color: #04AA6D;\r\n\
}\r\n\
 input:focus + .sliderswitch {\r\n\
     box-shadow: 0 0 1px #2196F3;\r\n\
}\r\n\
 input:checked + .sliderswitch:before {\r\n\
     -webkit-transform: translateX(100%);\r\n\
     -ms-transform: translateX(100%);\r\n\
     transform: translateX(100%);\r\n\
}\r\n\
 body {\r\n\
     font-family: Arial, Helvetica, sans-serif;\r\n\
}\r\n\
 .mobile-container {\r\n\
     width: 100%;\r\n\
     max-width: 480px;\r\n\
     margin: auto;\r\n\
     background-color: #555;\r\n\
     height: 100%;\r\n\
     min-height: 500px;\r\n\
     color: white;\r\n\
     border-radius: 10px;\r\n\
}\r\n\
 .topnav {\r\n\
     overflow: hidden;\r\n\
     background-color: #333;\r\n\
     position: relative;\r\n\
}\r\n\
 .topnav #menuElements {\r\n\
     display: none;\r\n\
}\r\n\
 .topnav a {\r\n\
     color: white;\r\n\
     padding: 15px 16px;\r\n\
     text-decoration: none;\r\n\
     font-size: 17px;\r\n\
     display: block;\r\n\
}\r\n\
 .topnav a.icon {\r\n\
     background: black;\r\n\
     display: block;\r\n\
     position: absolute;\r\n\
     right: 0;\r\n\
     top: 0;\r\n\
}\r\n\
 .topnav a:hover {\r\n\
     background-color: #ddd;\r\n\
     color: black;\r\n\
}\r\n\
 .active {\r\n\
     background-color: #990000;\r\n\
     color: white;\r\n\
}\r\n\
 .div {\r\n\
     width: 35px;\r\n\
     height: 3px;\r\n\
     background-color: white;\r\n\
     margin: 3px 0;\r\n\
}\r\n\
 .button {\r\n\
     border: none;\r\n\
     color: white;\r\n\
     padding: 15px 32px;\r\n\
     text-align: center;\r\n\
     text-decoration: none;\r\n\
     display: inline-block;\r\n\
     font-size: 16px;\r\n\
     margin: 4px 2px;\r\n\
     cursor: pointer;\r\n\
}\r\n\
 \r\n .button1 {\r\n\
     background-color: #4CAF50;\r\n\
     margin-left: 35%;\r\n\
     width: 30%;\r\n\
     margin-top: 3%;\r\n\
}\r\n\
/* Green */\r\n\
 .slidecontainer {\r\n\
     width: 100%;\r\n\
}\r\n\
 .slider {\r\n\
     -webkit-appearance: none;\r\n\
     width: 100%;\r\n\
     height: 25%;\r\n\
     background: #d3d3d3;\r\n\
     outline: none;\r\n\
     opacity: 0.7;\r\n\
     -webkit-transition: .2s;\r\n\
     transition: opacity .2s;\r\n\
}\r\n\
 .slider:hover {\r\n\
     opacity: 1;\r\n\
}\r\n\
 .slider::-webkit-slider-thumb {\r\n\
     -webkit-appearance: none;\r\n\
     appearance: none;\r\n\
     width: 25px;\r\n\
     height: 25px;\r\n\
     background: #04AA6D;\r\n\
     cursor: pointer;\r\n\
}\r\n\
 .slider::-moz-range-thumb {\r\n\
     width: 25px;\r\n\
     height: 25px;\r\n\
     background: #04AA6D;\r\n\
     cursor: pointer;\r\n\
}\r\n\
 .vertical-center {\r\n\
     margin: 0;\r\n\
     margin-top: 1.5%;\r\n\
     vertical-align: top;\r\n\
}\r\n\
 .csuszka {\r\n\
     width: 90%;\r\n\
     height: 50px;\r\n\
     vertical-align: top;\r\n\
     display: inline-block;\r\n\
}\r\n\
 .szazalek {\r\n\
     width: 10%;\r\n\
     height: 4%;\r\n\
     display: inline-block;\r\n\
     veritical-align: top;\r\n\
}\r\n\
 .szazalek>p {\r\n\
     margin: 0;\r\n\
     padding-left: 34%;\r\n\
     padding-top: 4%;\r\n\
}\r\n\
 </style>\r\n";

char *cssChart = "<style>\r\n\
.graph .labels.x-labels {\r\n\
  text-anchor: middle;\r\n\
}\r\n\
\r\n\
.graph .labels.y-labels {\r\n\
  text-anchor: end;\r\n\
}\r\n\
\r\n\
\r\n\
.graph {\r\n\
  height: 500px;\r\n\
  width: 800px;\r\n\
}\r\n\
\r\n\
.graph .grid {\r\n\
  stroke: #ccc;\r\n\
  stroke-dasharray: 0;\r\n\
  stroke-width: 1;\r\n\
}\r\n\
\r\n\
.labels {\r\n\
  font-size: 13px;\r\n\
}\r\n\
\r\n\
.label-title {\r\n\
  font-weight: bold;\r\n\
  text-transform: uppercase;\r\n\
  font-size: 12px;\r\n\
  fill: black;\r\n\
}\r\n\
\r\n\
.data {\r\n\
  fill: blue;\r\n\
  stroke-width: 1; \r\n\
}\r\n\
\r\n\
.mhover:hover,.mhover:active\r\n\
{\r\n\
  fill: red;\r\n\
}\r\n \
		.valami {\r\n\
		    width: 100px;\r\n\
		    display: block;\r\n\
		    overflow: hidden;\r\n\
		    white-space: nowrap;\r\n\
		    text-overflow: ellipsis;\r\n\
		}\r\n\
		\r\n\
		.valami:hover {    \r\n\
		    overflow: visible;\r\n\
		}		</style>";

char * htmlChart = "<svg version=\"1.2\" xmlns=\"http://www.w3.org/200\" xmlns:xlink=\"http://www.w3.org/19/xlink\" class=\"graph\" aria-labelledby=\"title\" role=\"img\">\r\n\
 \r\n\
<g class=\"grid x-grid\" id=\"xGrid\">\r\n\
  <line x1=\"90\" x2=\"90\" y1=\"5\" y2=\"371\"></line>\r\n\
</g>\r\n\
<g class=\"grid y-grid\" id=\"yGrid\">\r\n\
  <line x1=\"90\" x2=\"705\" y1=\"370\" y2=\"370\"></line>\r\n\
</g>\r\n\
  <g class=\"labels x-labels\">\r\n\
  <text x=\"100\" y=\"400\">2008</text>\r\n\
  <text x=\"246\" y=\"400\">2009</text>\r\n\
  <text x=\"392\" y=\"400\">2010</text>\r\n\
  <text x=\"538\" y=\"400\">2011</text>\r\n\
  <text x=\"684\" y=\"400\">2012</text>\r\n\
  <text x=\"400\" y=\"440\" class=\"label-title\">Year</text>\r\n\
</g>\r\n\
<g class=\"labels y-labels\">\r\n\
  <text x=\"80\" y=\"15\">15</text>\r\n\
  <text x=\"80\" y=\"131\">10</text>\r\n\
  <text x=\"80\" y=\"248\">5</text>\r\n\
  <text x=\"80\" y=\"373\">0</text>\r\n\
  <text x=\"50\" y=\"200\" class=\"label-title\">Price</text>\r\n\
</g>\r\n\
<g class=\"data\" data-setname=\"Our first data set\">\r\n\
  <circle cx=\"90\" cy=\"192\" data-value=\"7.2\" r=\"4\" alt=\"sdad\" class=\"mhover\"> <title clss=\"valami\" id=\"title\"> 7.2</title></circle>\r\n\
  <circle cx=\"240\" cy=\"141\" data-value=\"8.1\" r=\"4\" class=\"mhover\"><title id=\"title\"> 7.3</title></circle>\r\n\
  <circle cx=\"388\" cy=\"179\" data-value=\"7.7\" r=\"4\"></circle>\r\n\
  <circle cx=\"531\" cy=\"200\" data-value=\"6.8\" r=\"4\"></circle>\r\n\
  <circle cx=\"677\" cy=\"104\" data-value=\"6.7\" r=\"4\"></circle>\r\n\
</g>\r\n\
</svg>";

char * body ="\
		</head>\r\n\
		<body onload=\"onloadFunction()\">\r\n\
		\r\n\
		<div class=\"mobile-container\">\r\n\
		\r\n\
		<!-- Top Navigation Menu -->\r\n\
		<div class=\"topnav\">\r\n\
		  <a href=\"#home\" class=\"active\">Templogger</a>\r\n\
		  <div id=\"menuElements\"></div>\r\n\
		  <a href=\"javascript:void(0);\" class=\"icon\" onclick=\"myFunction()\">\r\n\
		    <i ><div class=\"div\"></div><div class=\"div\"></div><div class=\"div\" ></div></i>\r\n\
		  </a>\r\n\
		</div>\r\n\
		<div class=\"switchDiv\">\r\n\
		<p>Toggle Switch</p>\r\n\
		<label class=\"switch\">\r\n\
		  <input type=\"checkbox\">\r\n\
		  <span class=\"sliderswitch\"></span>\r\n\
		</label>\r\n\
		</div>\r\n\
		\r\n\
		<div id=\"page1\"><svg version=\"1.2\" xmlns=\"http://www.w3.org/200\" xmlns:xlink=\"http://www.w3.org/19/xlink\" class=\"graph\" aria-labelledby=\"title\" role=\"img\">\r\n\
 \r\n\
<g class=\"grid x-grid\" id=\"xGrid\">\r\n\
  <line x1=\"90\" x2=\"90\" y1=\"5\" y2=\"371\"></line>\r\n\
</g>\r\n\
<g class=\"grid y-grid\" id=\"yGrid\">\r\n\
  <line x1=\"90\" x2=\"705\" y1=\"370\" y2=\"370\"></line>\r\n\
</g>\r\n\
  <g class=\"labels x-labels\">\r\n\
  <text x=\"100\" y=\"400\">2008</text>\r\n\
  <text x=\"246\" y=\"400\">2009</text>\r\n\
  <text x=\"392\" y=\"400\">2010</text>\r\n\
  <text x=\"538\" y=\"400\">2011</text>\r\n\
  <text x=\"684\" y=\"400\">2012</text>\r\n\
  <text x=\"400\" y=\"440\" class=\"label-title\">Year</text>\r\n\
</g>\r\n\
<g class=\"labels y-labels\">\r\n\
  <text x=\"80\" y=\"15\">15</text>\r\n\
  <text x=\"80\" y=\"131\">10</text>\r\n\
  <text x=\"80\" y=\"248\">5</text>\r\n\
  <text x=\"80\" y=\"373\">0</text>\r\n\
  <text x=\"50\" y=\"200\" class=\"label-title\">Price</text>\r\n\
</g>\r\n\
<g class=\"data\" data-setname=\"Our first data set\">\r\n\
  <circle cx=\"90\" cy=\"192\" data-value=\"7.2\" r=\"4\" alt=\"sdad\" class=\"mhover\"> <title id=\"title\"> 7.2</title></circle>\r\n\
  <circle cx=\"240\" cy=\"141\" data-value=\"8.1\" r=\"4\" class=\"mhover\"><title id=\"title\"> 7.3</title></circle>\r\n\
  <circle cx=\"388\" cy=\"179\" data-value=\"7.7\" r=\"4\"></circle>\r\n\
  <circle cx=\"531\" cy=\"200\" data-value=\"6.8\" r=\"4\"></circle>\r\n\
  <circle cx=\"677\" cy=\"104\" data-value=\"6.7\" r=\"4\"></circle>\r\n\
</g>\r\n\
</svg></div>\r\n\
		<div id=\"page\"></div>\r\n\
</div>\r\n\
</body>\r\n\
</html>";

char * script= "<script>\r\n\
		function myFunction() {\r\n\
		  var x = document.getElementById(\"menuElements\");\r\n\
		  if (x.style.display === \"block\") {\r\n\
		    x.style.display = \"none\";\r\n\
		  } else {\r\n\
		    x.style.display = \"block\";\r\n\
		  }\r\n\
		}\r\n\
		function onloadFunction()\r\n\
				{let menuItems=[\"settings;Beallitasok\",\"akarmi;Akarmi\"];\r\n\
				let pageItems=[\"val;Fohangero;-32;0;-32;0\",\"val1;Hangero;-16;0;-16;0\"];\r\n\
				let switchItems=[\"val;Fohangero;-32;0;-32;0\",\"val1;Hangero;-16;0;-16;0\"];\r\n\
				creatToElement(\"menuElements\",menuItems);\r\n\
				creatToInputElement(\"page\",pageItems);\r\n\
				creatToSwitchElement(\"page\",switchItems);\r\n\
			}\r\n\
		\r\n\
		function creatToElement(dest,command)\r\n\
		{\r\n\
			for(x=0;x<command.length;x++)\r\n\
					{\r\n\
					let array = command[x].split(\";\");\r\n\
									\r\n\
					document.getElementById(dest).innerHTML+=\" <a href=\\\"\"+array[0]+\"\\\">\"+array[1]+\"</a>\";\r\n\
				}\r\n\
		}\r\n\
		function creatToSwitchElement(dest,command)\r\n\
				{\r\n\
					for(x=0;x<command.length;x++)\r\n\
							{\r\n\
							let array = command[x].split(\";\");\r\n\
											\r\n\
							document.getElementById(dest).innerHTML+=\"<div id=\\\"div_\"+array[0]+\"\\\" class=\\\"switchDiv\\\"><p>\"+array[1]+\"</p> <label class=\\\"switch\\\"> <input oninput=\\\"ertekAdo('\"+array[0]+\"')\\\" id=\\\"\"+array[0]+\"\\\" type=\\\"checkbox\\\" ><span class=\\\"sliderswitch\\\"></span></label></div>\";\r\n\
							if(array[5]==1)\r\n\
		{\r\n\
			document.getElementById(dest).innerHTML+=\"<button class=\\\"button button1\\\" onclick=\\\"window.location.href='/motoron?val='+document.getElementById(&quot;val&quot;).value\\\">Beallit</button>\";\r\n\
		}	\r\n\
		\r\n\
			document.getElementById(dest).innerHTML+=\"</div>\";\r\n\
		\r\n\
				}\r\n\
				}\r\n\
						function creatToInputElement(dest,command)\r\n\
				{\r\n\
					for(x=0;x<command.length;x++)\r\n\
							{\r\n\
							let array = command[x].split(\";\");\r\n\
											\r\n\
							document.getElementById(dest).innerHTML+=\"<div id=\\\"div_\"+array[0]+\"\\\"style=\\\"padding-left: 5%;padding-right: 5%;width: 90%;\\\"><p>\"+array[1]+\"</p><div class=\\\"csuszka\\\"> <input oninput=\\\"ertekAdo('\"+array[0]+\"')\\\" id=\\\"\"+array[0]+\"\\\" class=\\\"slider\\\" type=\\\"range\\\" min=\\\"\"+array[2]+\"\\\" max=\\\"\"+array[3]+\"\\\" value=\\\"\"+array[4]+\"\\\"\\></div><div class=\\\"szazalek\\\"> <p id=\\\"p_\"+array[0]+\"\\\">\"+array[4]+\" </p></div>\";\r\n\
							if(array[5]==1)\r\n\
		{\r\n\
			document.getElementById(dest).innerHTML+=\"<button class=\\\"button button1\\\" onclick=\\\"window.location.href='/motoron?val='+document.getElementById(&quot;val&quot;).value\\\">Beallit</button>\";\r\n\
		}	\r\n\
		\r\n\
			document.getElementById(dest).innerHTML+=\"</div>\";\r\n\
		\r\n\
				}\r\n\
				}\r\n\
						  function ertekAdo(id) {\r\n\
					var val = document.getElementById(id).value;\r\n\
					document.getElementById('p_'+id).innerHTML = val;\r\n\
					}\r\n\
		</script>\r\n";
char htmlegesz[10000];
char* htmlMem;


static const httpd_uri_t defHTMLCode = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = defaulHTTP_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  = " ASDSA"


};

esp_err_t defaulHTTP_handler(httpd_req_t *req)
{

    esp_err_t error=0;
    htmlMem=(char*)malloc((strlen(htmlhead)+strlen(css)+strlen(cssChart)+strlen(body)+strlen(script))*sizeof(char)+1);
       if(htmlMem!=NULL)
       {
       	printf("sikeres hely foglalas\r\n");
       }
       else
       {
       	printf("sikertelen hely foglalas\r\n");
       }
       *htmlMem=0;
		strcat(htmlMem,htmlhead);
		strcat(htmlMem,css);
		strcat(htmlMem,cssChart);
		strcat(htmlMem,body);
		strcat(htmlMem,script);
    const char *respone = htmlMem;
       //const char *respone = req->user_ctx;
    error = httpd_resp_send(req, respone, strlen(respone));
    free(htmlMem);
    if(error!=ESP_OK)
    {
    	ESP_LOGI(TAG, "Error %d while sending Repsone", error);

    }
    else
    {
    	ESP_LOGI(TAG,"Respone sent succesfully");

    }
    return error;
}

static esp_err_t settings_handler(httpd_req_t *req)
{
	char buf[100];
	printf("settings**************************\r\n");
	printf("req:%s\r\n",req->uri);


	   const char s[2] = "=";
	   char *token;


	   token = strtok(req->uri, s);


	   while( token != NULL ) {
	      sprintf( buf,"%s", token );

	      token = strtok(NULL, s);
	   }
	int tmp_percent=atoi(buf);



	printf("motorOnHandler******************\r\n");
    esp_err_t error=0;
    printf("req:%s",req->uri);

    ESP_LOGI(TAG,"MOTOR Power NF");
    /*strcat(htmlegesz,htmlhead);
    strcat(htmlegesz,css);
    strcat(htmlegesz,body);
    strcat(htmlegesz,script);*/
    htmlMem=(char*)malloc((strlen(htmlhead)+strlen(css)+strlen(cssChart)+strlen(body)+strlen(script))*sizeof(char)+1);
    if(htmlMem!=NULL)
    {
    	printf("sikeres hely foglalas\r\n");
    }
    else
    {
    	printf("sikertelen hely foglalas\r\n");
    }
    *htmlMem=0;
    strcat(htmlMem,htmlhead);
	strcat(htmlMem,css);
	strcat(htmlMem,cssChart);
	strcat(htmlMem,body);
	strcat(htmlMem,script);
    const char *respone = (const char*)htmlMem;
    error=0;
    if(strlen(req->uri)==strlen("/settings"))
    {
    	printf("page ujrakuldes\r\n");
		error = httpd_resp_send(req, respone, strlen(respone));
		printf("page ujrakuldes1\r\n");
		//free(htmlMem);
    }
    else
    {
    	printf("command feldolgozas\r\n");
    	  const char s[2] = "=";
    		   char *token;

    		   /* get the first token */
    		   token = strtok(req->uri, s);

    		   /* walk through other tokens */
    		   while( token != NULL ) {
    		      sprintf( buf,"%s", token );
    		      printf("buff:%s\r\n",buf);
    		      token = strtok(NULL, s);
    		   }

    		       		      printf("buff:%s\r\n",buf);
    		int tmp_vol=atoi(buf);
    		printf("tmp_vol:%d\r\n",tmp_vol);

    }
    free(htmlMem);
    if(error!=ESP_OK)
    {
    	ESP_LOGI(TAG, "Error %d while sending Repsone", error);

    }
    else
    {
    	ESP_LOGI(TAG,"Respone sent succesfully");

    }
    return error;
}





static const httpd_uri_t settings = {
    .uri       = "/settings",
    .method    = HTTP_GET,
    .handler   = settings_handler,
    /* Let's pass response string in user
     * context to demonstrate it's usage */
    .user_ctx  ="Hello"


};

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        httpd_register_uri_handler(server, &defHTMLCode);

        httpd_register_uri_handler(server, &settings);


        #if CONFIG_EXAMPLE_BASIC_AUTH
        httpd_register_basic_auth(server);
        #endif
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}



esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
{

    /* For any other URI send 404 and close socket */
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
    return ESP_FAIL;
}



static void stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    httpd_stop(server);
}

static void disconnect_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGI(TAG, "Stopping webserver");
        stop_webserver(*server);
        *server = NULL;
    }
}

void connect_handler(void* arg, esp_event_base_t event_base,
                            int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver();
    }
}

static void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                 MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 MAC2STR(event->mac), event->aid);
    }
}


void wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
   // ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .channel = EXAMPLE_ESP_WIFI_CHANNEL,
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };
    if (strlen(EXAMPLE_ESP_WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS, EXAMPLE_ESP_WIFI_CHANNEL);
}
