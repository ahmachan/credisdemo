#ifndef _REDIS_PLUS_H_
#define _REDIS_PLUS_H_

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>

#include <hiredis/hiredis.h>

class RedisPlus
{
public:
  RedisPlus() {}

  ~RedisPlus()
  {
    this->_connect = NULL;
    this->_reply = NULL;
  }

  bool connect(std::string host, int port)
  {
    this->_connect = redisConnect(host.c_str(), port);
    if (this->_connect != NULL && this->_connect->err)
    {
      printf("connect error: %s\n", this->_connect->errstr);
      return 0;
    }
    return 1;
  }

  std::string get(std::string key)
  {
    this->_reply = (redisReply *)redisCommand(this->_connect, "GET %s", key.c_str());
    std::string str = this->_reply->str;
    freeReplyObject(this->_reply);
    return str;
  }

  void set(std::string key, std::string value)
  {
    redisCommand(this->_connect, "SET %s %s", key.c_str(), value.c_str());
  }

  std::string hget(std::string key, std::string field)
  {
    this->_reply = (redisReply *)redisCommand(this->_connect, "HGET %s %s", key.c_str(), field.c_str());
    std::string str = this->_reply->str;
    freeReplyObject(this->_reply);
    return str;
  }

  void hset(std::string key, std::string field, std::string value)
  {
    redisCommand(this->_connect, "HSET %s %s %s", key.c_str(), field.c_str(), value.c_str());
  }

  //SETEX key seconds value 将值 value 关联到 key ，并将 key 的生存时间设为 seconds (以秒为单位)。返回值:设置成功时返回 OK ,否则返回一个错误
  int setex(std::string key, int seconds, std::string value)
  {
    this->_reply = (redisReply *)redisCommand(this->_connect, "SETEX %s %d %s", key.c_str(), seconds, value.c_str());

    if (this->_reply == NULL)
    {
      printf("Error: SET error!\n");
      return 0;
    }

    if (this->_reply->type == REDIS_REPLY_NIL)
    {
      printf("The key doesn't exist.\n");
      freeReplyObject(this->_reply);
      return 0;
    }

    //std::string playload = this->_reply->str;
    if (!(this->_reply->type == REDIS_REPLY_STATUS && memcmp(this->_reply->str, "OK", 2) == 0))
    {
      printf("Error: SET error!\n");
      freeReplyObject(this->_reply);
      return 0;
    }

    freeReplyObject(this->_reply);
    return 1; //if success is 1
  }

  //TTL key  以秒为单位，返回给定 key 的剩余生存时  # 当 key 不存在时，返回 -2 。当 key 存在但没有设置剩余生存时间时，返回 -1 。否则，以秒为单位，返回 key 的剩余生存时间。
  int ttl(std::string key)
  {
    this->_reply = (redisReply *)redisCommand(this->_connect, "TTL %s", key.c_str());
    if (this->_reply == NULL)
    {
      printf("Error: TTL error!\n");
      return 0;
    }

    if (this->_reply->type == REDIS_REPLY_NIL)
    {
      printf("The key doesn't exist.\n");
      freeReplyObject(this->_reply);
      return 0;
    }

    int seconds = this->_reply->integer;
    freeReplyObject(this->_reply);
    return seconds;
  }

  //DEL key [key ...]删除给定的一个或多个 key 。不存在的 key 会被忽略。返回值:被删除 key 的数量
  int del(std::string key)
  {
    this->_reply = (redisReply *)redisCommand(this->_connect, "DEL %s", key.c_str());
    int count = this->_reply->integer;
    freeReplyObject(this->_reply);
    return count;
  }

  //EXISTS key 检查给定 key 是否存在。返回值:若 key 存在，返回 1 ，否则返回 0 。
  int exists(std::string key)
  {
    this->_reply = (redisReply *)redisCommand(this->_connect, "EXISTS %s", key.c_str());
    if (this->_reply == NULL)
    {
      printf("Error: EXISTS error!\n");
      return 0;
    }

    int count = this->_reply->integer;
    freeReplyObject(this->_reply);
    return count;
  }

private:
  redisContext *_connect;
  redisReply *_reply;
};

#endif //_REDIS_PLUS_H_
