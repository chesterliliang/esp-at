#ifndef _ESP_WEB3_H
#define _ESP_WEB3_H

#ifdef __cplusplus
extern "C" {
#endif
void web3_init();
uint8_t at_setupCmd_RpcSetNodeUrl(uint8_t para_num);
uint8_t at_setupCmd_RpcBalance(uint8_t para_num);
uint8_t at_setupCmd_RpcGasPrice(uint8_t para_num);
uint8_t at_setupCmd_RpcGetTransactionCount(uint8_t para_num);
uint8_t at_setupCmd_RpcSendRawTransaction(uint8_t para_num);
uint8_t at_setupCmd_RpcGetTransactionReceipt(uint8_t para_num);

#ifdef __cplusplus
}
#endif

#endif