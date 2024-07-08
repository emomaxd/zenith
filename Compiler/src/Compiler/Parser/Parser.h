#pragma once

#include "AST.h"

class Parser {
public:
    Parser(const std::vector<Token>& tokens) : tokens(tokens), position(0) {}

    ASTNodePtr parse() {
        return parseProgram();
    }

private:
    std::vector<Token> tokens;
    size_t position;

    Token currentToken() {
        if (position >= tokens.size()) return Token(TokenType::EndOfFile, "", 0, 0);
        return tokens[position];
    }

    Token consumeToken() {
        Token token = currentToken();
        position++;
        return token;
    }

    void expectToken(TokenType type) {
        if (currentToken().type != type) {
            throw std::runtime_error("Unexpected token: " + currentToken().value);
        }
        consumeToken();
    }

    ASTNodePtr parseProgram() {
        auto program = std::make_shared<ProgramNode>();
        while (currentToken().type != TokenType::EndOfFile) {
            if (currentToken().type == TokenType::Keyword && currentToken().value == "int") {
                program->statements.push_back(parseFunctionDeclaration());
            }
            else {
                throw std::runtime_error("Unexpected token in program: " + currentToken().value);
            }
        }
        return program;
    }

    ASTNodePtr parseFunctionDeclaration() {
        auto funcDecl = std::make_shared<FunctionDeclarationNode>();
        funcDecl->returnType = consumeToken().value;  // int
        funcDecl->name = consumeToken().value;  // main
        expectToken(TokenType::Delimiter);  // (
        expectToken(TokenType::Delimiter);  // )
        expectToken(TokenType::Delimiter);  // {
        while (currentToken().type != TokenType::Delimiter || currentToken().value != "}") {
            funcDecl->body.push_back(parseStatement());
        }
        expectToken(TokenType::Delimiter);  // }
        return funcDecl;
    }

    ASTNodePtr parseStatement() {
        if (currentToken().type == TokenType::Keyword && currentToken().value == "if") {
            return parseIfStatement();
        }
        else if (currentToken().type == TokenType::Keyword && currentToken().value == "return") {
            return parseReturnStatement();
        }
        else if (currentToken().type == TokenType::Keyword) {
            return parseVariableDeclaration();
        }
        else {
            throw std::runtime_error("Unexpected token in statement: " + currentToken().value);
        }
    }

    ASTNodePtr parseIfStatement() {
        auto ifStmt = std::make_shared<IfStatementNode>();
        consumeToken();  // if
        expectToken(TokenType::Delimiter);  // (
        ifStmt->condition = parseExpression();
        expectToken(TokenType::Delimiter);  // )
        expectToken(TokenType::Delimiter);  // {
        while (currentToken().type != TokenType::Delimiter || currentToken().value != "}") {
            ifStmt->thenBranch.push_back(parseStatement());
        }
        expectToken(TokenType::Delimiter);  // }
        return ifStmt;
    }

    ASTNodePtr parseReturnStatement() {
        auto returnStmt = std::make_shared<ReturnStatementNode>();
        consumeToken();  // return
        returnStmt->expression = parseExpression();
        expectToken(TokenType::Delimiter);  // ;
        return returnStmt;
    }

    ASTNodePtr parseVariableDeclaration() {
        auto varDecl = std::make_shared<VariableDeclarationNode>();
        varDecl->varType = consumeToken().value;  // type
        varDecl->name = consumeToken().value;  // name
        expectToken(TokenType::Delimiter);  // ;
        return varDecl;
    }

    ASTNodePtr parseExpression() {
        auto expr = std::make_shared<ExpressionNode>();
        expr->left = parsePrimary();
        if (currentToken().type == TokenType::Operator) {
            expr->operatorSymbol = consumeToken().value;
            expr->right = parsePrimary();
        }
        return expr;
    }

    ASTNodePtr parsePrimary() {
        if (currentToken().type == TokenType::Identifier) {
            return std::make_shared<IdentifierNode>(consumeToken().value);
        }
        else if (currentToken().type == TokenType::Number) {
            return std::make_shared<NumberNode>(std::stoi(consumeToken().value));
        }
        else {
            throw std::runtime_error("Unexpected token in expression: " + currentToken().value);
        }
    }
};


void printAST(const ASTNodePtr& node, int indent = 0) {
    std::string indentStr(indent, ' ');

    switch (node->type) {
    case ASTNodeType::Program: {
        auto program = std::dynamic_pointer_cast<ProgramNode>(node);
        std::cout << indentStr << "Program:" << std::endl;
        for (const auto& statement : program->statements) {
            printAST(statement, indent + 2);
        }
        break;
    }
    case ASTNodeType::FunctionDeclaration: {
        auto funcDecl = std::dynamic_pointer_cast<FunctionDeclarationNode>(node);
        std::cout << indentStr << "Function: " << funcDecl->name << std::endl;
        for (const auto& bodyStmt : funcDecl->body) {
            printAST(bodyStmt, indent + 2);
        }
        break;
    }
    case ASTNodeType::VariableDeclaration: {
        auto varDecl = std::dynamic_pointer_cast<VariableDeclarationNode>(node);
        std::cout << indentStr << "Variable: " << varDecl->name << " of type " << varDecl->varType << std::endl;
        break;
    }
    case ASTNodeType::IfStatement: {
        auto ifStmt = std::dynamic_pointer_cast<IfStatementNode>(node);
        std::cout << indentStr << "If Statement:" << std::endl;
        std::cout << indentStr << "  Condition:" << std::endl;
        printAST(ifStmt->condition, indent + 4);
        std::cout << indentStr << "  Then Branch:" << std::endl;
        for (const auto& stmt : ifStmt->thenBranch) {
            printAST(stmt, indent + 4);
        }
        break;
    }
    case ASTNodeType::ReturnStatement: {
        auto returnStmt = std::dynamic_pointer_cast<ReturnStatementNode>(node);
        std::cout << indentStr << "Return Statement:" << std::endl;
        printAST(returnStmt->expression, indent + 2);
        break;
    }
    case ASTNodeType::Expression: {
        auto expr = std::dynamic_pointer_cast<ExpressionNode>(node);
        std::cout << indentStr << "Expression: " << expr->operatorSymbol << std::endl;
        std::cout << indentStr << "  Left:" << std::endl;
        printAST(expr->left, indent + 4);
        std::cout << indentStr << "  Right:" << std::endl;
        printAST(expr->right, indent + 4);
        break;
    }
    case ASTNodeType::Identifier: {
        auto ident = std::dynamic_pointer_cast<IdentifierNode>(node);
        std::cout << indentStr << "Identifier: " << ident->name << std::endl;
        break;
    }
    case ASTNodeType::Number: {
        auto num = std::dynamic_pointer_cast<NumberNode>(node);
        std::cout << indentStr << "Number: " << num->value << std::endl;
        break;
    }
    default:
        std::cout << indentStr << "Unknown AST Node" << std::endl;
    }
}