#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

#include "Token.h"

class Lexer {
public:
    Lexer(const std::string& source) : source(source), position(0), line(1), column(1) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (true) {
            Token token = nextToken();
            tokens.push_back(token);
            if (token.type == TokenType::EndOfFile || token.type == TokenType::Error) {
                break;
            }
        }
        return tokens;
    }

private:
    std::string source;
    size_t position;
    int line;
    int column;

    char currentChar() {
        if (position >= source.length()) return '\0';
        return source[position];
    }

    void advance() {
        if (currentChar() == '\n') {
            line++;
            column = 1;
        }
        else {
            column++;
        }
        position++;
    }

    Token nextToken() {
        while (isspace(currentChar())) advance();

        char c = currentChar();
        int tokenStartColumn = column;

        if (c == '\0') return Token(TokenType::EndOfFile, "", line, column);

        if (isalpha(c)) return identifier(tokenStartColumn);
        if (isdigit(c)) return number(tokenStartColumn);
        if (c == '"') return string(tokenStartColumn);
        if (isDelimiter(c)) return delimiter(tokenStartColumn);
        if (isOperator(c)) return oper(tokenStartColumn);

        return Token(TokenType::Error, std::string(1, c), line, column);
    }

    Token identifier(int tokenStartColumn) {
        size_t start = position;
        while (isalnum(currentChar()) || currentChar() == '_') advance();
        std::string value = source.substr(start, position - start);
        TokenType type = isKeyword(value) ? TokenType::Keyword : TokenType::Identifier;
        return Token(type, value, line, tokenStartColumn);
    }

    Token number(int tokenStartColumn) {
        size_t start = position;
        while (isdigit(currentChar())) advance();
        std::string value = source.substr(start, position - start);
        return Token(TokenType::Number, value, line, tokenStartColumn);
    }

    Token string(int tokenStartColumn) {
        advance(); // Skip the opening quote
        size_t start = position;
        while (currentChar() != '"' && currentChar() != '\0') advance();
        if (currentChar() == '\0') return Token(TokenType::Error, "Unterminated string", line, column);
        std::string value = source.substr(start, position - start);
        advance(); // Skip the closing quote
        return Token(TokenType::String, value, line, tokenStartColumn);
    }

    Token delimiter(int tokenStartColumn) {
        char c = currentChar();
        advance();
        return Token(TokenType::Delimiter, std::string(1, c), line, tokenStartColumn);
    }

    Token oper(int tokenStartColumn) {
        char c = currentChar();
        advance();
        if (c == '=' && currentChar() == '=') {
            advance();
            return Token(TokenType::Operator, "==", line, tokenStartColumn);
        }
        return Token(TokenType::Operator, std::string(1, c), line, tokenStartColumn);
    }

    bool isKeyword(const std::string& value) {
        static const std::unordered_set<std::string> keywords = { "int", "if", "else", "while", "return" };
        return keywords.find(value) != keywords.end();
    }

    bool isDelimiter(char c) {
        static const std::unordered_set<char> delimiters = { '(', ')', '{', '}', ';', ',' };
        return delimiters.find(c) != delimiters.end();
    }

    bool isOperator(char c) {
        static const std::unordered_set<char> operators = { '=', '+', '-', '*', '/', '<', '>', '!' };
        return operators.find(c) != operators.end();
    }
};
