#include "web3_inc.h"
#include "cJSON.h"
void post_json_helper(const char* method, cJSON* params, const int32_t id, char* post_string);
void result_json_helper(const char* result, char* result_string);
cJSON* params_helper(char* addr, bool latest, bool free, cJSON* tofree);
