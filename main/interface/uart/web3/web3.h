#ifndef _ESP_WEB3_H
#define _ESP_WEB3_H

#define MAX_HTTP_RECV_BUFFER 512
#define MAX_NODE_URL_LEN 128

#ifdef __cplusplus
extern "C" {
#endif
void web3Init();
void web3SetDbg(uint32_t dbg);
void web3SetNodeUrl(uint8_t* url);
uint8_t web3Balance(uint8_t* addr, uint8_t* result);
uint8_t web3GasPrice(uint8_t* result);
uint8_t web3GetTransactionCount(uint8_t* addr, uint8_t* result);
uint8_t web3SendRawTransaction(uint8_t* tx, uint8_t* result);
uint8_t web3GetTransactionReceipt(uint8_t* addr, uint8_t* result);
#ifdef __cplusplus
}
#endif

#endif