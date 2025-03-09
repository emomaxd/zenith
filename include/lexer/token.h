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
  TokenType Type;
  std::string Value;
  int Line;
  int Column;

  Token(TokenType type, const std::string &value, int line, int column)
      : Type(type), Value(value), Line(line), Column(column) {}
};
