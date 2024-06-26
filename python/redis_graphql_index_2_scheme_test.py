from manage_redis import kill_redis, connect_redis_with_start, connect_redis, flush_db, TEST_INDEX_NAME, TEST_INDEX_PREFIX
import pytest
from redis.commands.json.path import Path
from redis.commands.search.query import GeoFilter, NumericFilter, Query
from redis.commands.search.field import TextField, NumericField, TagField
from redis.commands.search.indexDefinition import IndexDefinition, IndexType
from redis.commands.search.result import Result
import time
import random

@pytest.fixture(autouse=True)
def before_and_after_test():
    print("Start")
    yield
    kill_redis()
    print("End")

def test_create_index_ft_info():
    producer = connect_redis_with_start()
    flush_db(producer) # clean all db first 
    schema = (TextField("$.name", as_name="name", sortable=True), NumericField("$.age", as_name="age", sortable=True),  \
              TextField("$.city", as_name="city", sortable=True), NumericField("$.register_time", as_name="register_time", sortable=True), \
              TagField("$.tags.*", as_name="tags", sortable=True) )
    producer.ft(TEST_INDEX_NAME).create_index(schema, definition=IndexDefinition(prefix=[TEST_INDEX_PREFIX], index_type=IndexType.JSON)) 

    # ADD INITIAL DATA
    for i in range(20):
        key = "key-" + str(i)
        data = {}
        data["name"] = "name-" + str(random.randint(10,50))
        data["age"] = random.randint(20,50)
        data["city"] = "city-" + str(random.randint(0,5))
        data["register_time"] = random.randint(100,1000)
        data["tags"] = []
        for tag_i in range(random.randint(0,4)):
            data["tags"].append("tag-"+ str(tag_i))
        producer.json().set(key, Path.root_path(), data)