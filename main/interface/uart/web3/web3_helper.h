void post_json_helper(const char* method, cJSON* params, const int32_t id, char* post_string);
void result_json_helper(const char* result, char* result_string);
char** params_helper(char* addr, bool latest, cJSON* params);
