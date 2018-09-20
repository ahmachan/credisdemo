#include "redisplus.h"

int main()
{
	RedisPlus *r = new RedisPlus();
	//在物理机中，链接redis的docker（进入docker查ip）
	std::string redisHost = "172.19.0.4";
	//在phpdocker里，链接redis的docker
	//std::string redisHost = "redis";
	if(!r->connect(redisHost, 6379))
	{
		printf("connect error!\n");
		return 0;
	}
	r->set("tc_cpp_nickname", "Mayuyu");
	printf("Get the value of tc_cpp_nickname is %s\n", r->get("tc_cpp_nickname").c_str());

	printf("Get the value of tc_clang_01 is %s\n", r->get("tc_clang_01").c_str());


	r->hset("tc_hash_person", "xin","chan");
	printf("Get the value of tc_hash_person.xin is %s\n", r->hget("tc_hash_name", "xin").c_str());
	r->hset("tc_hash_person", "name","Jeely");
	printf("Get the value of tc_hash_person.name is %s\n", r->hget("tc_hash_name", "name").c_str());
	r->hset("tc_hash_person", "age","32");
	r->hset("tc_hash_person", "time_diamond","172.32");
	r->hset("tc_hash_person", "add_time","1537350623");
	delete r;

	return 0;
}
