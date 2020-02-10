#include "web3_helper.h"

const char* g_eth_template = "{\"jsonrpc\":\"2.0\",\"method\":\"\",\"params\":[],\"id\":1}";

void post_json_helper(const char* method, cJSON* params, const int32_t id, char* post_string ){
    memset(post_string,0,MAX_HTTP_RECV_BUFFER);
    //Init Object
    cJSON* send=cJSON_Parse(g_eth_template); 
    //Set method name
    cJSON* new_method_item = cJSON_CreateString(method);
    cJSON_ReplaceItemInObject(send,"method",new_method_item);
    //Set params
    if(params!=NULL)
        cJSON_ReplaceItemInObject(send,"params",params);
    //set id
    cJSON* new_id_item = cJSON_CreateNumber(id);
    cJSON_ReplaceItemInObject(send, "id", new_id_item);
    //dump string
    memcpy(post_string,cJSON_Print(send), strlen(cJSON_Print(send)));
    //delete
    cJSON_Delete(send);
}

void result_json_helper(const char* result, char* result_string){
    memset(result_string,0,MAX_HTTP_RECV_BUFFER);
    //init object
    cJSON* receive=cJSON_Parse(result); 
    //try to get error
    cJSON *e=cJSON_GetObjectItem(receive,"error");
    if(e!=NULL){
        memcpy(result_string,cJSON_Print(e), strlen(cJSON_Print(e)));
        cJSON_Delete(receive);
        return;
    }
    //get result
    cJSON *r=cJSON_GetObjectItem(receive,"result"); 
    if(r==NULL){
        cJSON_Delete(receive);
        result_string = NULL;
        return;
    }
    if(strlen(cJSON_Print(r))==0){
        strcpy(result_string,(const char*)"<empty>");
        cJSON_Delete(receive);
        return;
    }
    if(strlen(cJSON_Print(r))>MAX_HTTP_RECV_BUFFER){
        strcpy(result_string,(const char*)"<too long>");
        cJSON_Delete(receive);
        return;
    }
    //cp result
    memcpy(result_string,cJSON_Print(r), strlen(cJSON_Print(r)));
    //del object 
    cJSON_Delete(receive);
}
char **string = NULL;

cJSON* params_helper(char* data, bool latest, bool isfree, cJSON* tofree){
    if(isfree){
        free(string);
        cJSON_Delete(tofree);
        return NULL;
    }
    if(latest){
        string = (char**)malloc(sizeof(char*)*2);
        string[0] = (char*)malloc(strlen((char*)data)+1);
        string[1] = (char*)malloc(strlen((const char*)"latest"));
        strcpy(string[0],(char*)data);
        strcpy(string[1],(const char*)"latest");
        return cJSON_CreateStringArray((const char**)string,2); 
    }else{
        string = (char**)malloc(sizeof(char*));
        string[0] = (char*)malloc(strlen((char*)data)+1);
        strcpy(string[0],(char*)data);
        return cJSON_CreateStringArray((const char**)string,1); 
    }
    
   
}