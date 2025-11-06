//
// Created by Coline Constantinian on 03/11/2025.
//

#include "Database.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Tokenizer.h"

Database::Database() : m_data(){
    Load();

}

void Database::Load() {
    std::ifstream t("assets/data.propriety");
    std::stringstream buffer;
    buffer << t.rdbuf();

    Tokenizer tokenizer(buffer.str());

    std::vector<Token> tokens = tokenizer.Process();

    bool isKey = true;
    bool isArray = false;
    std::string key;
    std::vector<std::string> values;
    for (Token token: tokens) {
        switch (token.id) {
            case STRING:
                if (isKey) {
                    key = token.value;
                } else {
                    values.push_back(token.value);
                    if (!isArray) {
                        m_data[key] = values;
                        isKey = true;
                        values = {};
                        key = {};
                    }
                }
                continue;
            case COLON:
                isKey = false;
                continue;
            case BRACKET_OPEN:
                isArray = true;
                continue;
            case BRACKET_CLOSE:
                m_data[key] = values;
                isArray = false;
                isKey = true;
                values = {};
                key = {};
                continue;
            default:
                continue;
        }
    }
}

std::vector<std::string> Database::GetData(std::string _key) {
    if (m_data.contains(_key)) {
        return m_data[_key];
    }
    return {};
}
