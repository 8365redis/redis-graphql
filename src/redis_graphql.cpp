#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <thread>
#include "json.hpp"
#include "redismodule.h"
#include "logger.h"
#include "version.h"

#include "graphql_command_query.h"

#ifndef REDIS_GRAPHQL_MODULE_VERSION
#define REDIS_GRAPHQL_MODULE_VERSION "unknown"
#endif

using json = nlohmann::json;


#ifdef __cplusplus
extern "C" {
#endif


int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {

    int version_int = Get_Module_Version(REDIS_GRAPHQL_MODULE_VERSION);
    const char* version_string = { REDIS_GRAPHQL_MODULE_VERSION " compiled at " __TIME__ " "  __DATE__  };
    LOG(ctx, REDISMODULE_LOGLEVEL_WARNING , "REDIS_GRAPHQL_MODULE_VERSION : " + std::string(version_string));

    #ifdef _DEBUG
    LOG(ctx, REDISMODULE_LOGLEVEL_WARNING , "THIS IS A DEBUG BUILD." );
    #endif
    #ifdef NDEBUG
    LOG(ctx, REDISMODULE_LOGLEVEL_WARNING , "THIS IS A RELEASE BUILD." );
    #endif 

    if (RedisModule_Init(ctx, "REDIS_GRAPHQL", version_int, REDISMODULE_APIVER_1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }

    if (RedisModule_CreateCommand(ctx,"REDIS_GRAPHQL.QUERY", Query_RedisCommand , "readonly", 0, 0, 0) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    } else {
        LOG(ctx, REDISMODULE_LOGLEVEL_DEBUG , "REDIS_GRAPHQL.QUERY command created successfully.");
    }

    return REDISMODULE_OK;
}

#ifdef __cplusplus
}
#endif

