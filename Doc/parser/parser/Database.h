//
// Created by Coline Constantinian on 03/11/2025.
//

#ifndef PARSER_DATABASE_H
#define PARSER_DATABASE_H
#include <map>
#include <vector>
#include <string>

class Database {
    std::map<std::string, std::vector<std::string>> m_data;
public:
    Database();
    void Load();
    std::vector<std::string> GetData(std::string _key);
};


#endif //PARSER_DATABASE_H