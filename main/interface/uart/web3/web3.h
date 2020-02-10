#ifndef _ESP_WEB3_H
#define _ESP_WEB3_H
#include "web3_inc.h"

#ifdef __cplusplus
extern "C" {
#endif
void w3printf(const char *cmd, ...);
void web3Init();
void web3SetDbg(uint32_t dbg);
void web3SetNodeUrl(uint8_t* url);
uint8_t web3Balance(uint8_t* addr, uint8_t* result);
uint8_t web3GasPrice(uint8_t* result);
uint8_t web3GetTransactionCount(uint8_t* addr, uint8_t* result);
uint8_t web3SendRawTransaction(uint8_t* tx, uint8_t* result);
uint8_t web3GetTransactionReceipt(uint8_t* txid, uint8_t* result);
#ifdef __cplusplus
}
#endif

#endif