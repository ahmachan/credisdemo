#ifndef _REDIS_C_H_
#define _REDIS_C_H_

#include <hiredis/hiredis.h>

// 全局变量声明，注意声明格式
extern redisContext *redis_context;

// 函数声明
void redis_conn();

int redis_set(char *key,char *value);

char *redis_get(char *key);

int redis_strlen(char *key);

#endif