#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_at.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "web3.h"

#define MAX_HTTP_RECV_BUFFER 512
#define MAX_NODE_URL_LEN 128
char *g_node_url;

void web3_init(){
    g_node_url = (char*)malloc(MAX_NODE_URL_LEN);
    strcpy(g_node_url,"https://mainnet.infura.io");
    printf("url %s\n", g_node_url);
    /*
        "https://geth:Ushu764Yshdl73jsd@eth-node-wookong.nbltrust.com",
        "https://geth:Ushu764Yshdl73jsd@node.wooko.ng/eth",
        "https://mainnet.infura.io",
    */

}

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

uint32_t http_post(const char* post_data, char* result){  
    esp_http_client_config_t config = {
        .url = g_node_url,
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
        printf("HTTP POST request failed: %d", err);
    }
    esp_http_client_cleanup(client);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_setupCmd_RpcSetNodeUrl(uint8_t para_num){
     if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *url;
    if (esp_at_get_para_as_str (0,&url) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    strcpy(g_node_url,(char*)url);
    esp_at_response_result(ESP_AT_RESULT_CODE_OK);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_setupCmd_RpcBalance(uint8_t para_num){
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *addr;
    if (esp_at_get_para_as_str (0,&addr) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    printf("addr = %s\n",addr);
    char result[MAX_HTTP_RECV_BUFFER] = { 0 };
    const char *post_data = "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getBalance\",\"params\":[\"0xc94770007dda54cF92009BFF0dE90c06F603a09f\", \"latest\"],\"id\":1}";
    uint32_t rv = http_post(post_data,result);
    esp_at_port_write_data((uint8_t*)result,strlen((char*)result));
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}