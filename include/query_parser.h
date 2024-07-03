#ifndef GRAPH_PARSER
#define GRAPH_PARSER

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

struct Query_Condition {
    std::unordered_map<std::string, std::string> conditions; // For now map is enough
};

struct Query_Field {
    std::string name;
    Query_Field(const std::string& field_name) : name(field_name) {}
};

struct Query {
    std::string type;
    Query_Condition condition;
    std::vector<Query_Field> fields;
};

bool parse_query(std::string& query_text, Query& query);
void print_query(const Query& query);

#endif /* GRAPH_PARSER */