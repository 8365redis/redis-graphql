#ifndef REDIS_GRAPHQL_LOGGER_H
#define REDIS_GRAPHQL_LOGGER_H

#include <string>
#include "redismodule.h"


#ifdef _DEBUG
#define LOG(ctx, level, log) Log_Std_Output(ctx, level, log)
#else
#define LOG(ctx, level, log) Log_Redis(ctx, level, log)
#endif

void Log_Std_Output(RedisModuleCtx *ctx, const char *levelstr, std::string fmt );
void Log_Redis(RedisModuleCtx *ctx, const char *levelstr, std::string fmt );

#endif /* REDIS_GRAPHQL_LOGGER_H */
