#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <string>
#include <vector>

class Lexer {
    std::string input;
    size_t pos;
    char currentChar;

    void advance();
    void skipWhitespace();
    Token number();
    Token identifier();
public:
    Lexer(const std::string &text);
    Token getNextToken();
};

#endif // LEXER_H