#pragma once

#include <string>

enum class TokenType {
    Identifier,
    Keyword,
    Number,
    String,
    Operator,
    Delimiter,
    EndOfFile,
    Error
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    int column;

    Token(TokenType type, const std::string& value, int line, int column)
        : type(type), value(value), line(line), column(column) {}
};