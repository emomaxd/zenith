#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

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
    ASTNodeType type;
    virtual ~ASTNode() = default;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

struct ProgramNode : ASTNode {
    std::vector<ASTNodePtr> statements;
    ProgramNode() { type = ASTNodeType::Program; }
};

struct FunctionDeclarationNode : ASTNode {
    std::string returnType;
    std::string name;
    std::vector<ASTNodePtr> body;
    FunctionDeclarationNode() { type = ASTNodeType::FunctionDeclaration; }
};

struct VariableDeclarationNode : ASTNode {
    std::string varType;
    std::string name;
    VariableDeclarationNode() { type = ASTNodeType::VariableDeclaration; }
};

struct IfStatementNode : ASTNode {
    ASTNodePtr condition;
    std::vector<ASTNodePtr> thenBranch;
    IfStatementNode() { type = ASTNodeType::IfStatement; }
};

struct ReturnStatementNode : ASTNode {
    ASTNodePtr expression;
    ReturnStatementNode() { type = ASTNodeType::ReturnStatement; }
};

struct ExpressionNode : ASTNode {
    ASTNodePtr left;
    std::string operatorSymbol;
    ASTNodePtr right;
    ExpressionNode() { type = ASTNodeType::Expression; }
};

struct IdentifierNode : ASTNode {
    std::string name;
    IdentifierNode(const std::string& name) : name(name) { type = ASTNodeType::Identifier; }
};

struct NumberNode : ASTNode {
    int value;
    NumberNode(int value) : value(value) { type = ASTNodeType::Number; }
};

struct BlockNode : ASTNode {
    std::vector<ASTNodePtr> statements;
    BlockNode() { type = ASTNodeType::Block; }
};
