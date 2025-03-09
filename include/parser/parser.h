#pragma once

#include <memory>
#include <vector>

#include "ast/ast.h"
#include "lexer/token.h"

/// @brief Parser class for converting tokens into an Abstract Syntax Tree (AST)
class Parser {
public:
  /// @brief Constructs a parser with a vector of tokens
  /// @param tokens The input tokens to parse
  explicit Parser(const std::vector<Token> &tokens);

  /// @brief Parses the tokens into an AST
  /// @return Pointer to the root AST node, or nullptr on failure
  ASTNodePtr parse();

private:
  std::vector<Token> Tokens; ///< Vector of input tokens
  size_t Position;           ///< Current position in token vector

  /// @brief Gets the current token without advancing
  /// @return Current token, or EOF token if at end
  Token currentToken();

  /// @brief Consumes and returns the current token, advancing position
  /// @return The consumed token
  Token consumeToken();

  /// @brief Checks if current token matches expected type
  /// @param type Expected token type
  /// @return True if match, false otherwise
  bool expectToken(TokenType type);

  /// @brief Parses a complete program
  /// @return Program node or nullptr on failure
  ASTNodePtr parseProgram();

  /// @brief Parses a function declaration
  /// @return Function declaration node or nullptr on failure
  ASTNodePtr parseFunctionDeclaration();

  /// @brief Parses a statement
  /// @return Statement node or nullptr on failure
  ASTNodePtr parseStatement();

  /// @brief Parses an if statement
  /// @return If statement node or nullptr on failure
  ASTNodePtr parseIfStatement();

  /// @brief Parses a return statement
  /// @return Return statement node or nullptr on failure
  ASTNodePtr parseReturnStatement();

  /// @brief Parses a variable declaration
  /// @return Variable declaration node or nullptr on failure
  ASTNodePtr parseVariableDeclaration();

  /// @brief Parses an expression
  /// @return Expression node or nullptr on failure
  ASTNodePtr parseExpression();

  /// @brief Parses a primary expression (identifier or number)
  /// @return Primary node or nullptr on failure
  ASTNodePtr parsePrimary();
};

/// @brief Prints the AST structure to console
/// @param node Root node of the AST to print
/// @param indent Indentation level (default 0)
void printAST(const ASTNodePtr &node, int indent = 0);
