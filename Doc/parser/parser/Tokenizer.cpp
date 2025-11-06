//
// Created by Coline Constantinian on 03/11/2025.
//

#include "Tokenizer.h"

#include <iostream>

void Tokenizer::ProcessCharacter(ETokenIdentifier _id, char _value, Token &_token, std::vector<Token> &_tokens) {
    if (_token.id == STRING) {
        _tokens.push_back(_token);
        _token = {};
    }
    _tokens.push_back(Token{_id, std::string{_value}});
}

bool Tokenizer::isValidCharacter(char _value) {
    if (_value == ' ' || _value == '\t') {
        return false;
    }
    return true;
}

Tokenizer::Tokenizer(std::string _data) : m_data(_data) {
}

std::vector<Token> Tokenizer::Process() {
    std::vector<Token> ret;
    Token t = {};

    for (char c : m_data) {
        if (!isValidCharacter(c))
            continue;
        switch (c) {
            case COLON:
                ProcessCharacter(COLON, c, t, ret);
                continue;
            case BRACKET_OPEN:
                ProcessCharacter(BRACKET_OPEN, c, t, ret);
                continue;
            case BRACKET_CLOSE:
                ProcessCharacter(BRACKET_CLOSE, c, t, ret);
                continue;
            case COMMA:
                ProcessCharacter(COMMA, c, t, ret);
                continue;
            case '\r': case '\n':
                if (t.id == STRING) {
                    ret.push_back(t);
                    t = {};
                }
                continue;
            default:
                t.id = STRING;
                t.value += c;
                continue;
        }
    }
    if (t.id == STRING) {
        ret.push_back(t);
        t = {};
    }
    ret.push_back(Token{END, ""});
    return ret;
}
