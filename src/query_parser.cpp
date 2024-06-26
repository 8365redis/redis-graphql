#include "query_parser.h"
#include <iostream>

Query parse_query(const std::string& query) {
    Query parsed_query;
    std::istringstream stream(query);
    std::string line;

    while (std::getline(stream, line)) {
        // Remove leading/trailing whitespace (Refactor this)
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);
        std::cout << "Parsing line: " << line << std::endl;
        if (line.empty()) {
            continue;
        }

        if (line.find("persons") != std::string::npos) { // Hard Coded for now
            parsed_query.type = "persons";

            size_t where_pos = line.find("where:");
            if (where_pos != std::string::npos) {
                size_t start = line.find('{', where_pos) + 1;
                size_t end = line.find('}', where_pos);
                std::string condition_str = line.substr(start, end - start);
                std::istringstream cond_stream(condition_str);
                std::string condition;

                while (std::getline(cond_stream, condition, ',')) {
                    size_t colon_pos = condition.find(':');
                    if (colon_pos != std::string::npos) {
                        std::string key = condition.substr(0, colon_pos);
                        std::string value = condition.substr(colon_pos + 1);

                        // Remove leading/trailing whitespace and quotes (Refactor this)
                        key.erase(0, key.find_first_not_of(" \t\n\r\f\v"));
                        key.erase(key.find_last_not_of(" \t\n\r\f\v") + 1);
                        value.erase(0, value.find_first_not_of(" \t\n\r\f\v\""));
                        value.erase(value.find_last_not_of(" \t\n\r\f\v\"") + 1);

                        parsed_query.condition.conditions[key] = value;
                    }
                }
            }
        } else if (line.find('{') != std::string::npos) {
            continue;
        } else if (line.find('}') != std::string::npos) {
            continue;
        } else {
            Query_Field field;
            field.name = line;
            parsed_query.fields.push_back(field);
        }
    }

    return parsed_query;
}

void print_query(const Query& query) {
    std::cout << "Type: " << query.type << std::endl;
    std::cout << "Conditions:" << std::endl;
    for (const auto& cond : query.condition.conditions) {
        std::cout << "  " << cond.first << ": " << cond.second << std::endl;
    }
    std::cout << "Fields:" << std::endl;
    for (const auto& field : query.fields) {
        std::cout << "  " << field.name << std::endl;
    }
}
