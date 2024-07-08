#include "Compiler.h"

int main() {
    std::string source = R"(
        int main() {
            if (a == 10) {
                return 0;
            }
        }
    )";

    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    ASTNodePtr ast = parser.parse();

    std::cout << "Parsed AST:" << std::endl;
    printAST(ast);

    return 0;
}

