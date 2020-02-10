#include "web3_def.h"
#include "esp_http_client.h"
#include "web3_http.h"

esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
        case HTTP_EVENT_ON_CONNECTED:
        case HTTP_EVENT_HEADER_SENT:
        case HTTP_EVENT_ON_HEADER:    
        case HTTP_EVENT_ON_FINISH:
        case HTTP_EVENT_DISCONNECTED:
        case HTTP_EVENT_ON_DATA:
            // if (!esp_http_client_is_chunked_response(evt->client)) {
                
            //     printf("data %s\n", (char*)evt->data);
            // }
            break;
    }
    return ESP_OK;
}

uint32_t http_post(const char* url, const char* post_data, char* result){  
    esp_http_client_config_t config = {
        .url = url,
        .event_handler = http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);
    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_post_field(client, post_data, strlen(post_data));
    esp_http_client_clear_response_buffer(client);
    err = esp_http_client_perform(client);
    if (err == ESP_OK) {
            int content_length = esp_http_client_get_content_length(client);
            uint32_t total_len = strlen(esp_http_client_get_response_buffer(client));
            char* total =  esp_http_client_get_response_buffer(client);
            memcpy(result,total+total_len - content_length,content_length);
    }
    else {
        w3printf("HTTP POST request failed: %d", err);
        return WEB3_HTTP_FAIL;
    }
    esp_http_client_cleanup(client);
    return WEB3_OK;
}
