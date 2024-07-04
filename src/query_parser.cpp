#include "query_parser.h"
#include <iostream>
#include <map>
#include <sstream>
#include <algorithm>

void remove_whitespace(std::string& str){
    str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
    str.erase(std::remove(str.begin(), str.end(), '\"'), str.end());
}

bool extractConditionsFromWhere(const std::string& input, Query& query) {
    std::size_t start = input.find('{');
    std::size_t end = input.find('}');
    
    if (start == std::string::npos || end == std::string::npos) {
        return false; // Return fail
    }
    
    std::string content = input.substr(start + 1, end - start - 1);
    std::stringstream ss(content);
    std::string key, value;
    
    while (ss >> key) {
        if (key.back() == ',') {
            key.pop_back(); // Remove trailing comma from key
        }
        if (key.back() == ':') {
            key.pop_back(); // Remove trailing colon from key
        }
        if (ss.peek() == ' ') {
            ss.ignore(); // Ignore the space after the colon
        }
        
        std::getline(ss, value, ',');
        if (value.back() == ' ') {
            value.pop_back(); // Remove trailing space from value
        }
        if (value.front() == '"') {
            value.erase(0, 1); // Remove leading quote from value
        }
        if (value.back() == '"') {
            value.pop_back(); // Remove trailing quote from value
        }
        remove_whitespace(key);
        remove_whitespace(value);
        query.condition.conditions[key] = value;
    }
    
    return true;
}


bool parse_query(std::string& query_text, Query& query){
    //std::cout<<query_text<<std::endl;
    remove_whitespace(query_text);

    // TODO Add check for curly count to fail early

    size_t first_curly_pos = query_text.find("{");
    if (first_curly_pos != std::string::npos) {
        query_text = query_text.substr(first_curly_pos);
    } else {
        return false;
    }

    std::size_t paranthesis_before_where_pos = query_text.find('(');
    if(paranthesis_before_where_pos == std::string::npos){
        return false;
    }
    std::size_t paranthesis_after_where_pos = query_text.find(')', paranthesis_before_where_pos);
    if(paranthesis_after_where_pos == std::string::npos){
        return false;
    }

    std::string type = query_text.substr(first_curly_pos + 1, paranthesis_before_where_pos - first_curly_pos - 1);
    remove_whitespace(type);

    std::cout<<"Type:" ;
    std::cout<<type<<std::endl;
    query.type = type;

    std::string where_statement = query_text.substr(paranthesis_before_where_pos + 1, paranthesis_after_where_pos - paranthesis_before_where_pos - 1);
    std::cout<<"Where statement:" ;
    std::cout<<where_statement<<std::endl;

    extractConditionsFromWhere(where_statement, query);

    std::cout<<"Conditions:"<<std::endl ;
    for (const auto& pair : query.condition.conditions) {
        std::cout << "Key:" << pair.first << "-Value:" << pair.second <<"-"<<std::endl;
    }

    std::size_t fields_start_pos = query_text.find('{', paranthesis_after_where_pos);
    if(fields_start_pos == std::string::npos){
        return false;
    }    
    std::size_t fields_end_pos = query_text.find('}', fields_start_pos);
    if(fields_end_pos == std::string::npos){
        return false;
    } 

    std::string field_statement = query_text.substr(fields_start_pos + 1, fields_end_pos - fields_start_pos - 1);
    std::cout<<"Fields statement:" ;
    std::cout<<field_statement<<std::endl;

    std::stringstream field_statement_stream(field_statement);
    std::string field_raw;
    while (field_statement_stream >> field_raw) {
        remove_whitespace(field_raw);
        query.fields.push_back(Query_Field(field_raw));
    }

    std::cout<<"Fields:"<<std::endl;
    for (const auto& f : query.fields) {
        std::cout << "Field: " << f.name <<  std::endl;
    }

    return true;
}

/*
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
*/

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
