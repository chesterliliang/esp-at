#include "cJSON.h"

const char* g_eth_template = "{\"jsonrpc\":\"2.0\",\"method\":\"eth_getTransactionReceipt\",\"params\":[\"0xb903239f8543d04b5dc1ba6579132b143087c68db1b2168786408fcbce568238\"],\"id\":1}";



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
    w3printf("send_string = %s\n",post_string); 
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

char** params_helper(char* addr, bool latest, cJSON* params){
    char **string = (char**)malloc(sizeof(char*)*2);
    string[0] = (char*)malloc(strlen((char*)addr)+1);
    string[1] = (char*)malloc(strlen((const char*)"latest"));
    strcpy(string[0],(char*)addr);
    strcpy(string[1],(const char*)"latest");

    params = cJSON_CreateStringArray((const char**)string,2); 
    return string;
}