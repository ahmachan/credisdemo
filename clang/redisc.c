#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <hiredis/hiredis.h>
#include "redisc.h"

redisContext *redis_context = NULL;

void redis_conn()
{
	char ip[] = "172.19.0.4"; //"127.0.0.1";redis;172.19.0.4
	unsigned int port = 6379;
	//redis默认监听端口为6387 可以再配置文件中修改
	redis_context = redisConnect(ip, port);
	if (redis_context->err)
	{
		redisFree(redis_context);
		printf("Connect to redisServer faile\n");
		return;
	}
	printf("Connect to the redis server Success , at %s:%d\n", ip, port);
}

int redis_set(char *key, char *value)
{
	const char *commandSet = "set %s %s";
	redisReply *r = (redisReply *)redisCommand(redis_context, commandSet, key, value);

	if (NULL == r)
	{
		printf("Execut command failure\n");
		redisFree(redis_context);
		return 0;
	}
	if (!(r->type == REDIS_REPLY_STATUS && strcasecmp(r->str, "OK") == 0))
	{
		printf("Failed to execute command[%s]\n", commandSet);
		freeReplyObject(r);
		redisFree(redis_context);
		return 0;
	}
	freeReplyObject(r);
	printf("Succeed to execute command[%s]\n", commandSet);
	redisFree(redis_context);

	return 1;
}

char *redis_get(char *key)
{
	const char *command3 = "get %s";
	char *emptyStr = "";
	redisReply *r = (redisReply *)redisCommand(redis_context, command3, key);
	if (r->type == REDIS_REPLY_NIL)
	{
		printf("Failed to execute command[%s]\n", command3);
		freeReplyObject(r);
		redisFree(redis_context);
		return emptyStr;
	}

	if (r->type != REDIS_REPLY_STRING)
	{
		printf("Failed to execute command[%s]\n", command3);
		freeReplyObject(r);
		redisFree(redis_context);
		return emptyStr;
	}
	printf("The value of 'tc_clang_01' is %s\n", r->str);
	freeReplyObject(r);
	printf("Succeed to execute command[%s]\n", command3);
	redisFree(redis_context);

	return r->str;
}

int redis_strlen(char *key)
{
	const char *command2 = "strlen %s";
	redisReply *r = (redisReply *)redisCommand(redis_context, command2, key);
	if (r->type != REDIS_REPLY_INTEGER)
	{
		printf("Failed to execute command[%s]\n", command2);
		freeReplyObject(r);
		redisFree(redis_context);
		return 0;
	}
	int length = r->integer;
	freeReplyObject(r);
	printf("The length of 'tc_clang_01' is %d.\n", length);
	printf("Succeed to execute command[%s]\n", command2);

	redisFree(redis_context);

	return length;
}
