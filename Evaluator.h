#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Node.h"
#include "SymbolTable.h"
#include <memory>

class Evaluator {
    SymbolTable symbols;
public:
    void visit(std::shared_ptr<Node> node);
    double evaluate(std::shared_ptr<Node> node);
};

#endif // EVALUATOR_H