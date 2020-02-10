#ifndef _ESP_WEB3_CMD_H
#define _ESP_WEB3_CMD_H
#include "web3_inc.h"
#ifdef __cplusplus
extern "C" {
#endif
void at_cmd_web3_init();
uint8_t at_setupCmd_RpcSetDbg(uint8_t para_num);
uint8_t at_setupCmd_RpcSetNodeUrl(uint8_t para_num);
uint8_t at_setupCmd_RpcBalance(uint8_t para_num);
uint8_t at_queryCmd_RpcGasPrice(uint8_t *cmd_name);
uint8_t at_setupCmd_RpcGetTransactionCount(uint8_t para_num);
uint8_t at_setupCmd_RpcSendRawTransaction(uint8_t para_num);
uint8_t at_setupCmd_RpcGetTransactionReceipt(uint8_t para_num);

#ifdef __cplusplus
}
#endif

#endif