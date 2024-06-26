#ifndef GRAPHQL_COMMAND_QUERY
#define GRAPHQL_COMMAND_QUERY

#include "redismodule.h"

int Query_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc);

#endif /* GRAPHQL_COMMAND_QUERY */