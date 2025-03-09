#include <cctype>
#include <unordered_set>

#include "lexer/lexer.h"

Lexer::Lexer(const std::string &source)
    : Source(source), Position(0), Line(1), Column(1) {}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  while (true) {
    Token token = nextToken();
    tokens.push_back(token);
    if (token.Type == TokenType::EndOfFile || token.Type == TokenType::Error) {
      break;
    }
  }
  return tokens;
}

char Lexer::currentChar() {
  if (Position >= Source.length())
    return '\0';
  return Source[Position];
}

void Lexer::advance() {
  if (currentChar() == '\n') {
    Line++;
    Column = 1;
  } else {
    Column++;
  }
  Position++;
}

Token Lexer::nextToken() {
  while (isspace(currentChar()))
    advance();

  char c = currentChar();
  int tokenStartColumn = Column;

  if (c == '\0')
    return Token(TokenType::EndOfFile, "", Line, Column);

  if (isalpha(c))
    return identifier(tokenStartColumn);
  if (isdigit(c))
    return number(tokenStartColumn);
  if (c == '"')
    return string(tokenStartColumn);
  if (isDelimiter(c))
    return delimiter(tokenStartColumn);
  if (isOperator(c))
    return oper(tokenStartColumn);

  return Token(TokenType::Error, std::string(1, c), Line, Column);
}

Token Lexer::identifier(int tokenStartColumn) {
  size_t start = Position;
  while (isalnum(currentChar()) || currentChar() == '_')
    advance();
  std::string value = Source.substr(start, Position - start);
  TokenType type =
      isKeyword(value) ? TokenType::Keyword : TokenType::Identifier;
  return Token(type, value, Line, tokenStartColumn);
}

Token Lexer::number(int tokenStartColumn) {
  size_t start = Position;
  while (isdigit(currentChar()))
    advance();
  std::string value = Source.substr(start, Position - start);
  return Token(TokenType::Number, value, Line, tokenStartColumn);
}

Token Lexer::string(int tokenStartColumn) {
  advance(); // Skip the opening quote
  size_t start = Position;
  while (currentChar() != '"' && currentChar() != '\0')
    advance();
  if (currentChar() == '\0')
    return Token(TokenType::Error, "Unterminated string", Line, Column);
  std::string value = Source.substr(start, Position - start);
  advance(); // Skip the closing quote
  return Token(TokenType::String, value, Line, tokenStartColumn);
}

Token Lexer::delimiter(int tokenStartColumn) {
  char c = currentChar();
  advance();
  return Token(TokenType::Delimiter, std::string(1, c), Line, tokenStartColumn);
}

Token Lexer::oper(int tokenStartColumn) {
  char c = currentChar();
  advance();
  if (c == '=' && currentChar() == '=') {
    advance();
    return Token(TokenType::Operator, "==", Line, tokenStartColumn);
  }
  return Token(TokenType::Operator, std::string(1, c), Line, tokenStartColumn);
}

bool Lexer::isKeyword(const std::string &value) {
  static const std::unordered_set<std::string> keywords = {"int", "if", "else",
                                                           "while", "return"};
  return keywords.find(value) != keywords.end();
}

bool Lexer::isDelimiter(char c) {
  static const std::unordered_set<char> delimiters = {'(', ')', '{',
                                                      '}', ';', ','};
  return delimiters.find(c) != delimiters.end();
}

bool Lexer::isOperator(char c) {
  static const std::unordered_set<char> operators = {'=', '+', '-', '*',
                                                     '/', '<', '>', '!'};
  return operators.find(c) != operators.end();
}
