#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../include/query_parser.h"

std::string query_v1 = "\
    query{ \
    persons(where: { age: 25, city: \"San Francisco\" }) { \
    name \
    age  \
    city \
    registerTime \
    tags  } \
    } \
    "; 

std::string query_v2 = "\
    query{ \
    persons(where: { age: 25   ,   city:   \"San Francisco\"    }) { \
    name \
    age  \
    city \
    registerTime \
    tags  } \
    } \
    "; 


std::string query_v3 = "{\n  persons(where: { age_gt: 25, city: \"San Francisco\" }) {\n    name\n    age\n    city\n    registerTime\n    tags\n  }\n}";


TEST_CASE( "Parser basic", "[parser]" ) {
    Query q; 
    parse_query(query_v2,q);
    REQUIRE(q.type == "persons");
    /*REQUIRE(q.type == "persons");
    REQUIRE(q.condition.conditions["city"] == "San Francisco");
    REQUIRE(q.condition.conditions["age"] == "25");
    
    std::vector<std::string> field_names;
    for (const auto& field : q.fields) {
        field_names.push_back(field.name);
    }
    for (const auto& pair : field_names) {
        std::cout << "Names: " << pair <<  std::endl;
    }*/

}
