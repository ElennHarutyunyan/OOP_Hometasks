#include "Lexer.h"
#include "Parser.h"
#include "Evaluator.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    std::string input;

    std::cout << "Enter your code (end with Ctrl+D):" << std::endl;
    while (std::getline(std::cin, line)) {
        input += line + "\n";
    }

    Lexer lexer(input);
    Parser parser(lexer);
    auto tree = parser.parse();

    Evaluator eval;
    eval.visit(tree);

    return 0;
}