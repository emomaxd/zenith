#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <string>
#include <vector>

#include "token.h"

class Lexer {
public:
  Lexer(const std::string &source);
  std::vector<Token> tokenize();

private:
  std::string Source;
  size_t Position;
  int Line;
  int Column;

  char currentChar();
  void advance();
  Token nextToken();
  Token identifier(int tokenStartColumn);
  Token number(int tokenStartColumn);
  Token string(int tokenStartColumn);
  Token delimiter(int tokenStartColumn);
  Token oper(int tokenStartColumn);

  bool isKeyword(const std::string &value);
  bool isDelimiter(char c);
  bool isOperator(char c);
};

#endif // LEXER_LEXER_H
