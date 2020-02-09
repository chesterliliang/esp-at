#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_at.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "cJSON.h"
#include "web3.h"

#define W3_DBG_PRINT    0
#define MAX_HTTP_RECV_BUFFER 512
#define MAX_NODE_URL_LEN 128
char *g_node_url;
bool g_dbg_print = true;
const char* g_eth_template = "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getTransactionReceipt\",\"params\":[\"0xb903239f8543d04b5dc1ba6579132b143087c68db1b2168786408fcbce568238\"],\"id\":1}";
char send_string[MAX_HTTP_RECV_BUFFER] = { 0 };
char result_string[MAX_HTTP_RECV_BUFFER] = { 0 };
char at_response[MAX_HTTP_RECV_BUFFER] = { 0 };

void w3printf(const char *cmd, ...)  
{  
    if(g_dbg_print){
        printf("%s %s ", __DATE__, __TIME__);  
        va_list args;       
        va_start(args,cmd);  
        vprintf(cmd,args);  
        va_end(args);      
    }

}  

void web3_init(){
    g_node_url = (char*)malloc(MAX_NODE_URL_LEN);
    g_dbg_print = false;
    strcpy(g_node_url,"https://mainnet.infura.io");
    w3printf("url %s\n", g_node_url);
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
        w3printf("HTTP POST request failed: %d", err);
        return ESP_AT_RESULT_CODE_ERROR;
    }
    esp_http_client_cleanup(client);
    return ESP_AT_RESULT_CODE_OK;
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

uint8_t at_setupCmd_RpcSetDbg(uint8_t para_num){
     if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    int32_t dbg = 0;
    if (esp_at_get_para_as_digit (0,&dbg) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    if(dbg==0)
        g_dbg_print=false;
    else
        g_dbg_print=true;
        
    esp_at_response_result(ESP_AT_RESULT_CODE_OK);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

void post_json_helper(const char* method, cJSON* params, const int32_t id, char* post_string ){
    //Init Object
    cJSON* send=cJSON_Parse(g_eth_template); 
    //Set method name
    cJSON* new_method_item = cJSON_CreateString(method);
    cJSON_ReplaceItemInObject(send,"method",new_method_item);
    //Set params
    cJSON_ReplaceItemInObject(send,"params",params);
    //set id
    cJSON* new_id_item = cJSON_CreateNumber(id);
    cJSON_ReplaceItemInObject(send, "id", new_id_item);
    //dump string
    memcpy(post_string,cJSON_Print(send), strlen(cJSON_Print(send)));
    w3printf("send_string = %s\n",send_string); 
    //delete
    cJSON_Delete(send);
}

void result_json_helper(const char* result, char* result_string){
    //init object
    cJSON* receive=cJSON_Parse(result); 
    //get result
    cJSON *r=cJSON_GetObjectItem(receive,"result"); 
    //cp result
    memcpy(result_string,cJSON_Print(r), strlen(cJSON_Print(r)));
    //del object 
    cJSON_Delete(receive);
}

uint8_t at_setupCmd_RpcBalance(uint8_t para_num){
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *addr;
    if (esp_at_get_para_as_str (0,&addr) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    w3printf("addr = %s\n",addr);
    char **string = (char**)malloc(sizeof(char*)*2);
    string[0] = (char*)malloc(strlen((char*)addr)+1);
    string[1] = (char*)malloc(strlen((const char*)"latest"));
    strcpy(string[0],(char*)addr);
    strcpy(string[1],(const char*)"latest");

    cJSON* params = cJSON_CreateStringArray((const char**)string,2); 

    post_json_helper("eth_getBalance",params, 1, send_string);
    
    free(string);

    uint32_t rv = http_post(send_string,result_string);
    if(rv!=ESP_AT_RESULT_CODE_OK){
        return rv;
    }
    
    result_json_helper(result_string,at_response);
    esp_at_port_write_data((uint8_t*)at_response,strlen((char*)at_response));
    return ESP_AT_RESULT_CODE_OK;
}

uint8_t at_setupCmd_RpcGasPrice(uint8_t para_num){
    return ESP_AT_RESULT_CODE_OK;
}

uint8_t at_setupCmd_RpcGetTransactionCount(uint8_t para_num){
    return ESP_AT_RESULT_CODE_OK;
}

uint8_t at_setupCmd_RpcSendRawTransaction(uint8_t para_num){
    return ESP_AT_RESULT_CODE_OK;
}
uint8_t at_setupCmd_RpcGetTransactionReceipt(uint8_t para_num){
    return ESP_AT_RESULT_CODE_OK;
}