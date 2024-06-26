#include <vector>
#include <string>
#include <iostream>

#include "graphql_command_query.h"
#include "query_parser.h"

int Query_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc){
    RedisModule_AutoMemory(ctx);
    std::vector<RedisModuleString*> arguments_redis_string_vector(argv+1, argv + argc);
    std::string query;
    for(auto &query_arg : arguments_redis_string_vector) {
        std::string arg_str = RedisModule_StringPtrLen(query_arg, NULL);
        std::cout<<arg_str<<std::endl;
        query = arg_str;
    }

    Query parsed_query = parse_query(query);
    print_query(parsed_query);

    RedisModule_ReplyWithSimpleString(ctx, "OK");
    return REDISMODULE_OK;
}