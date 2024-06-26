import subprocess
import time
import redis
import os

TEST_INDEX_NAME = "test_index"
TEST_INDEX_PREFIX = "test_data:"

def flush_db(r):
    r.flushall()

def kill_redis():
    bashCommand = "redis-cli shutdown"
    process = subprocess.Popen(bashCommand.split(), 
                                stdin=subprocess.DEVNULL,
                                stdout=subprocess.DEVNULL,
                                stderr=subprocess.DEVNULL,
                                start_new_session=True)    
    time.sleep(1)

def start_redis():
    current_working_directory = os.getcwd()
    module = current_working_directory + "/bin/redis-graphql.so"
    bashCommand = "redis-stack-server --loadmodule " + module
    subprocess.Popen(bashCommand.split(), 
                    stdin=subprocess.DEVNULL,
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL,
                    start_new_session=True)
    time.sleep(2)


def start_redis_without_module():
    bashCommand = "redis-stack-server"
    subprocess.Popen(bashCommand.split(), 
                    stdin=subprocess.DEVNULL,
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL,
                    start_new_session=True)
    time.sleep(2)    

def connect_redis_with_start():
    start_redis()
    r = redis.Redis(host='localhost', port=6379, decode_responses=True)
    return r

def connect_redis_with_start_without_module():
    start_redis_without_module()
    r = redis.Redis(host='localhost', port=6379, decode_responses=True)
    return r

def connect_redis():
    r = redis.Redis(host='localhost', port=6379, decode_responses=True)
    return r