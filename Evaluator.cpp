#include "Evaluator.h"
#include <stdexcept>
#include <iostream>

void Evaluator::visit(std::shared_ptr<Node> node) {
    if (auto n = std::dynamic_pointer_cast<StatementsNode>(node)) {
        for (auto &stmt : n->statements) visit(stmt);
    } else if (auto n = std::dynamic_pointer_cast<PrintNode>(node)) {
        std::cout << evaluate(n->expr) << std::endl;
    } else if (auto n = std::dynamic_pointer_cast<AssignNode>(node)) {
        symbols.set(n->name, evaluate(n->value));
    } else {
        evaluate(node);
    }
}

double Evaluator::evaluate(std::shared_ptr<Node> node) {
    if (auto n = std::dynamic_pointer_cast<NumberNode>(node)) {
        return n->value;
    } else if (auto n = std::dynamic_pointer_cast<VarNode>(node)) {
        return symbols.get(n->name);
    } else if (auto n = std::dynamic_pointer_cast<BinOpNode>(node)) {
        double left = evaluate(n->left);
        double right = evaluate(n->right);
        switch (n->op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return left / right;
        }
    }
    throw std::runtime_error("Unknown node");
}