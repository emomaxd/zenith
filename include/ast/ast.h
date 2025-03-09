#pragma once

#include <memory>
#include <string>
#include <vector>

enum class ASTNodeType {
  Program,
  FunctionDeclaration,
  VariableDeclaration,
  IfStatement,
  ReturnStatement,
  Expression,
  BinaryOperator,
  Identifier,
  Number,
  Block
};

struct ASTNode {
  ASTNodeType Type;
  virtual ~ASTNode() = default;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

struct ProgramNode : ASTNode {
  std::vector<ASTNodePtr> Statements;
  ProgramNode() { Type = ASTNodeType::Program; }
};

struct FunctionDeclarationNode : ASTNode {
  std::string ReturnType;
  std::string Name;
  std::vector<ASTNodePtr> Body;
  FunctionDeclarationNode() { Type = ASTNodeType::FunctionDeclaration; }
};

struct VariableDeclarationNode : ASTNode {
  std::string VarType;
  std::string Name;
  VariableDeclarationNode() { Type = ASTNodeType::VariableDeclaration; }
};

struct IfStatementNode : ASTNode {
  ASTNodePtr Condition;
  std::vector<ASTNodePtr> ThenBranch;
  IfStatementNode() { Type = ASTNodeType::IfStatement; }
};

struct ReturnStatementNode : ASTNode {
  ASTNodePtr Expression;
  ReturnStatementNode() { Type = ASTNodeType::ReturnStatement; }
};

struct ExpressionNode : ASTNode {
  ASTNodePtr Left;
  std::string OperatorSymbol;
  ASTNodePtr Right;
  ExpressionNode() { Type = ASTNodeType::Expression; }
};

struct IdentifierNode : ASTNode {
  std::string Name;
  IdentifierNode(const std::string &name) : Name(name) {
    Type = ASTNodeType::Identifier;
  }
};

struct NumberNode : ASTNode {
  int Value;
  NumberNode(int value) : Value(value) { Type = ASTNodeType::Number; }
};

struct BlockNode : ASTNode {
  std::vector<ASTNodePtr> Statements;
  BlockNode() { Type = ASTNodeType::Block; }
};
