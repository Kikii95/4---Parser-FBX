//
// Created by Coline Constantinian on 03/11/2025.
//

#ifndef PARSER_TOKENIZER_H
#define PARSER_TOKENIZER_H
#include <string>
#include <vector>

enum ETokenIdentifier {
    INVALID,
    END,
    STRING,

    BRACKET_OPEN = '[',
    BRACKET_CLOSE = ']',
    COLON = ':',
    COMMA = ','

};

struct Token {
    ETokenIdentifier id;
    std::string value;
};

class Tokenizer {
    std::string m_data;

    void ProcessCharacter(ETokenIdentifier _id, char _value, Token& _token, std::vector<Token>& _tokens);
    bool isValidCharacter(char _value);
public:
    Tokenizer(std::string _data);

    std::vector<Token> Process();

};


#endif //PARSER_TOKENIZER_H