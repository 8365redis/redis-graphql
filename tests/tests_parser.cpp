#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../include/query_parser.h"


TEST_CASE( "Parser basic", "[parser]" ) {
    std::string query_text = "\
        query{ \
        persons(where: { age: 25, city: \"San Francisco\" }) { \
        name \
        age  \
        city \
        registerTime \
        tags  } \
        } \
        "; 
    Query q; 
    parse_query(query_text,q);
    REQUIRE(q.type == "persons");
    REQUIRE(q.condition.conditions["age"] == "25");
    REQUIRE(q.condition.conditions["city"] == "San Francisco");

}


TEST_CASE( "Parser basic 2", "[parser]" ) {
    std::string query_text = "\
        query{ \
        persons(where: { age: 25   ,   city:   \"San Francisco\"    }) { \
        name \
        age  \
        city \
        registerTime \
        tags  } \
        } \
        "; 
    Query q; 
    parse_query(query_text,q);
    REQUIRE(q.type == "persons");
    REQUIRE(q.condition.conditions["age"] == "25");
    REQUIRE(q.condition.conditions["city"] == "San Francisco");

}

TEST_CASE( "Parser basic 3", "[parser]" ) {
    std::string query_text = "{\n  persons(where: { age: 25, city: \"San Francisco\" }) {\n    name\n    age\n    city\n    registerTime\n    tags\n  }\n}";
    Query q; 
    parse_query(query_text,q);
    REQUIRE(q.type == "persons");
    REQUIRE(q.condition.conditions["age"] == "25");
    REQUIRE(q.condition.conditions["city"] == "San Francisco");

}