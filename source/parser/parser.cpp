#include "parser/parser.h"
#include <iostream>

Parser::Parser(const std::vector<Token> &tokens)
    : Tokens(tokens), Position(0) {}

ASTNodePtr Parser::parse() { return parseProgram(); }

Token Parser::currentToken() {
  if (Position >= Tokens.size()) {
    return Token(TokenType::EndOfFile, "", 0, 0);
  }
  return Tokens[Position];
}

Token Parser::consumeToken() {
  Token token = currentToken();
  Position++;
  return token;
}

bool Parser::expectToken(TokenType type) {
  if (currentToken().Type != type) {
    std::cerr << "Unexpected token: " << currentToken().Value << std::endl;
    return false;
  }
  consumeToken();
  return true;
}

ASTNodePtr Parser::parseProgram() {
  auto program = std::make_shared<ProgramNode>();
  while (currentToken().Type != TokenType::EndOfFile) {
    if (currentToken().Type == TokenType::Keyword &&
        currentToken().Value == "int") {
      ASTNodePtr func = parseFunctionDeclaration();
      if (!func)
        return nullptr;
      program->Statements.push_back(func);
    } else {
      std::cerr << "Unexpected token in program: " << currentToken().Value
                << std::endl;
      return nullptr;
    }
  }
  return program;
}

ASTNodePtr Parser::parseFunctionDeclaration() {
  auto funcDecl = std::make_shared<FunctionDeclarationNode>();
  funcDecl->ReturnType = consumeToken().Value; // int
  funcDecl->Name = consumeToken().Value;       // main
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // (
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // )
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // {
  while (currentToken().Type != TokenType::Delimiter ||
         currentToken().Value != "}") {
    ASTNodePtr stmt = parseStatement();
    if (!stmt)
      return nullptr;
    funcDecl->Body.push_back(stmt);
  }
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // }
  return funcDecl;
}

ASTNodePtr Parser::parseStatement() {
  if (currentToken().Type == TokenType::Keyword &&
      currentToken().Value == "if") {
    return parseIfStatement();
  } else if (currentToken().Type == TokenType::Keyword &&
             currentToken().Value == "return") {
    return parseReturnStatement();
  } else if (currentToken().Type == TokenType::Keyword) {
    return parseVariableDeclaration();
  } else {
    std::cerr << "Unexpected token in statement: " << currentToken().Value
              << std::endl;
    return nullptr;
  }
}

ASTNodePtr Parser::parseIfStatement() {
  auto ifStmt = std::make_shared<IfStatementNode>();
  consumeToken(); // if
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // (
  ifStmt->Condition = parseExpression();
  if (!ifStmt->Condition)
    return nullptr;
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // )
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // {
  while (currentToken().Type != TokenType::Delimiter ||
         currentToken().Value != "}") {
    ASTNodePtr stmt = parseStatement();
    if (!stmt)
      return nullptr;
    ifStmt->ThenBranch.push_back(stmt);
  }
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // }
  return ifStmt;
}

ASTNodePtr Parser::parseReturnStatement() {
  auto returnStmt = std::make_shared<ReturnStatementNode>();
  consumeToken(); // return
  returnStmt->Expression = parseExpression();
  if (!returnStmt->Expression)
    return nullptr;
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // ;
  return returnStmt;
}

ASTNodePtr Parser::parseVariableDeclaration() {
  auto varDecl = std::make_shared<VariableDeclarationNode>();
  varDecl->VarType = consumeToken().Value; // type
  varDecl->Name = consumeToken().Value;    // name
  if (!expectToken(TokenType::Delimiter))
    return nullptr; // ;
  return varDecl;
}

ASTNodePtr Parser::parseExpression() {
  auto expr = std::make_shared<ExpressionNode>();
  expr->Left = parsePrimary();
  if (!expr->Left)
    return nullptr;
  if (currentToken().Type == TokenType::Operator) {
    expr->OperatorSymbol = consumeToken().Value;
    expr->Right = parsePrimary();
    if (!expr->Right)
      return nullptr;
  }
  return expr;
}

ASTNodePtr Parser::parsePrimary() {
  if (currentToken().Type == TokenType::Identifier) {
    return std::make_shared<IdentifierNode>(consumeToken().Value);
  } else if (currentToken().Type == TokenType::Number) {
    return std::make_shared<NumberNode>(std::stoi(consumeToken().Value));
  }

  std::cerr << "Unexpected token in expression: " << currentToken().Value
            << std::endl;
  return nullptr;
}

void printAST(const ASTNodePtr &node, int indent) {
  std::string indentStr(indent, ' ');

  if (!node) {
    std::cout << indentStr << "Null AST Node" << std::endl;
    return;
  }

  switch (node->Type) {
  case ASTNodeType::Program: {
    auto program = std::dynamic_pointer_cast<ProgramNode>(node);
    std::cout << indentStr << "Program:" << std::endl;
    for (const auto &statement : program->Statements) {
      printAST(statement, indent + 2);
    }
    break;
  }
  case ASTNodeType::FunctionDeclaration: {
    auto funcDecl = std::dynamic_pointer_cast<FunctionDeclarationNode>(node);
    std::cout << indentStr << "Function: " << funcDecl->Name << std::endl;
    for (const auto &bodyStmt : funcDecl->Body) {
      printAST(bodyStmt, indent + 2);
    }
    break;
  }
  case ASTNodeType::VariableDeclaration: {
    auto varDecl = std::dynamic_pointer_cast<VariableDeclarationNode>(node);
    std::cout << indentStr << "Variable: " << varDecl->Name << " of type "
              << varDecl->VarType << std::endl;
    break;
  }
  case ASTNodeType::IfStatement: {
    auto ifStmt = std::dynamic_pointer_cast<IfStatementNode>(node);
    std::cout << indentStr << "If Statement:" << std::endl;
    std::cout << indentStr << "  Condition:" << std::endl;
    printAST(ifStmt->Condition, indent + 4);
    std::cout << indentStr << "  Then Branch:" << std::endl;
    for (const auto &stmt : ifStmt->ThenBranch) {
      printAST(stmt, indent + 4);
    }
    break;
  }
  case ASTNodeType::ReturnStatement: {
    auto returnStmt = std::dynamic_pointer_cast<ReturnStatementNode>(node);
    std::cout << indentStr << "Return Statement:" << std::endl;
    printAST(returnStmt->Expression, indent + 2);
    break;
  }
  case ASTNodeType::Expression: {
    auto expr = std::dynamic_pointer_cast<ExpressionNode>(node);
    std::cout << indentStr << "Expression: " << expr->OperatorSymbol
              << std::endl;
    std::cout << indentStr << "  Left:" << std::endl;
    printAST(expr->Left, indent + 4);
    std::cout << indentStr << "  Right:" << std::endl;
    printAST(expr->Right, indent + 4);
    break;
  }
  case ASTNodeType::Identifier: {
    auto ident = std::dynamic_pointer_cast<IdentifierNode>(node);
    std::cout << indentStr << "Identifier: " << ident->Name << std::endl;
    break;
  }
  case ASTNodeType::Number: {
    auto num = std::dynamic_pointer_cast<NumberNode>(node);
    std::cout << indentStr << "Number: " << num->Value << std::endl;
    break;
  }
  default:
    std::cout << indentStr << "Unknown AST Node" << std::endl;
  }
}
