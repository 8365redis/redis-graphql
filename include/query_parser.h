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
    std::vector<Query_Field> sub_fields; // Later maybe will be used for multi layer
};

struct Query {
    std::string type;
    Query_Condition condition;
    std::vector<Query_Field> fields;
};

Query parse_query(const std::string& query);
void print_query(const Query& query);

#endif /* GRAPH_PARSER */