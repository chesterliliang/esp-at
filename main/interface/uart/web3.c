#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "esp_at.h"
#include "web3.h"

static uint8_t at_queryCmdRpcBalance(uint8_t *cmd_name)
{
    esp_at_response_result(ESP_AT_RESULT_CODE_OK);
    return ESP_AT_RESULT_CODE_PROCESS_DONE;
}