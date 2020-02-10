#include "esp_at.h"
#include "web3.h"
#include "web3_cmd.h"


void at_cmd_web3_init(){
    web3Init();
}

uint8_t at_setupCmd_RpcSetDbg(uint8_t para_num){
    w3printf("at_setupCmd_RpcSetDbg\n");
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    int32_t dbg = 0;
    if (esp_at_get_para_as_digit (0,&dbg) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    web3SetDbg(dbg);     
    esp_at_response_result(ESP_AT_RESULT_CODE_OK);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_setupCmd_RpcSetNodeUrl(uint8_t para_num){
    w3printf("at_setupCmd_RpcSetNodeUrl\n");
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *url;
    if (esp_at_get_para_as_str (0,&url) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    web3SetNodeUrl(url);
    esp_at_response_result(ESP_AT_RESULT_CODE_OK);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_setupCmd_RpcBalance(uint8_t para_num){
    w3printf("at_setupCmd_RpcBalance\n");
    uint8_t at_response[MAX_HTTP_RECV_BUFFER] = { 0 };
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *addr;
    if (esp_at_get_para_as_str (0,&addr) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    w3printf("addr = %s\n",addr);
    if(web3Balance(addr,at_response)!=ESP_AT_RESULT_CODE_OK){
        return ESP_AT_RESULT_CODE_FAIL;
    }
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    esp_at_port_write_data(at_response,strlen((char*)at_response));
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_queryCmd_RpcGasPrice(uint8_t *cmd_name){
    w3printf("at_queryCmd_RpcGasPrice\n");
    uint8_t at_response[MAX_HTTP_RECV_BUFFER] = { 0 };
    if(web3GasPrice(at_response)!=ESP_AT_RESULT_CODE_OK){
        return ESP_AT_RESULT_CODE_FAIL;
    }
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    esp_at_port_write_data(at_response,strlen((char*)at_response));
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_setupCmd_RpcGetTransactionCount(uint8_t para_num){
    w3printf("at_setupCmd_RpcGetTransactionCount\n");
    uint8_t at_response[MAX_HTTP_RECV_BUFFER] = { 0 };
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *addr;
    if (esp_at_get_para_as_str (0,&addr) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    w3printf("addr = %s\n",addr);
    if(web3GetTransactionCount(addr,at_response)!=ESP_AT_RESULT_CODE_OK){
        return ESP_AT_RESULT_CODE_FAIL;
    }
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    esp_at_port_write_data(at_response,strlen((char*)at_response));
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_setupCmd_RpcSendRawTransaction(uint8_t para_num){
    w3printf("at_setupCmd_RpcSendRawTransaction\n");
    uint8_t at_response[MAX_HTTP_RECV_BUFFER] = { 0 };
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *tx;
    if (esp_at_get_para_as_str (0,&tx) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    w3printf("tx = %s\n",tx);
    if(web3SendRawTransaction(tx,at_response)!=ESP_AT_RESULT_CODE_OK){
        return ESP_AT_RESULT_CODE_FAIL;
    }
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    esp_at_port_write_data(at_response,strlen((char*)at_response));
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}

uint8_t at_setupCmd_RpcGetTransactionReceipt(uint8_t para_num){
    w3printf("at_setupCmd_RpcGetTransactionReceipt\n");
    uint8_t at_response[MAX_HTTP_RECV_BUFFER] = { 0 };
    if (para_num != 1) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    uint8_t *txid;
    if (esp_at_get_para_as_str (0,&txid) != ESP_AT_PARA_PARSE_RESULT_OK) {
        return ESP_AT_RESULT_CODE_ERROR;
    }
    w3printf("txid = %s\n",txid);
    if(web3GetTransactionReceipt(txid,at_response)!=ESP_AT_RESULT_CODE_OK){
        return ESP_AT_RESULT_CODE_FAIL;
    }
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    esp_at_port_write_data(at_response,strlen((char*)at_response));
    esp_at_port_write_data((uint8_t*)"\r\n",2);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}