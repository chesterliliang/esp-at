#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_at.h"
#include "esp_log.h"
#include "cJSON.h"
#include "web3_def.h"
#include "web3_helper.h"
#include "web3_http.h"
#include "web3.h"

char *g_node_url;
bool g_dbg_print = true;

char send_string[MAX_HTTP_RECV_BUFFER] = { 0 };
char result_string[MAX_HTTP_RECV_BUFFER] = { 0 };

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
/*
        "https://geth:Ushu764Yshdl73jsd@eth-node-wookong.nbltrust.com",
        "https://geth:Ushu764Yshdl73jsd@node.wooko.ng/eth",
        "https://mainnet.infura.io",
*/ 

void web3_init(){
    g_node_url = (char*)malloc(MAX_NODE_URL_LEN);
    g_dbg_print = false;
    strcpy(g_node_url,"https://mainnet.infura.io");
    w3printf("url %s\n", g_node_url);
}

void web3SetNodeUrl(uint8_t* url){
    strcpy(g_node_url,(char*)url);
}

void web3SetDbg(uint32_t dbg){
    if(dbg==0)
        g_dbg_print=false;
    else
        g_dbg_print=true;
}

uint8_t web3Balance(uint8_t* addr, uint8_t* result){

    cJSON *params;
    char** string = params_helper(addr,true,params);
    post_json_helper("eth_getBalance",params, 1, send_string);
    free(string);
    cJSON_Delete(params);

    uint32_t rv = http_post(g_node_url,send_string,result_string);
    if(rv!=WEB3_OK){
        return rv;
    }
    
    result_json_helper(result_string,result);
    return WEB3_OK;
}

uint8_t web3GasPrice(uint8_t* result){
    return WEB3_OK;
}

uint8_t web3GetTransactionCount(uint8_t* addr, uint8_t* result){
    return WEB3_OK;
}

uint8_t web3SendRawTransaction(uint8_t* tx, uint8_t* result){
    return WEB3_OK;
}

uint8_t web3GetTransactionReceipt(uint8_t* addr, uint8_t* result){
    return ESP_AT_RESULT_CODE_OK;
}