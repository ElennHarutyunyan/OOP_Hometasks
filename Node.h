#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>
#include <vector>

struct Node {
    virtual ~Node() = default;
};

struct NumberNode : Node {
    double value;
    NumberNode(double val) : value(val) {}
};

struct BinOpNode : Node {
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    char op;
    BinOpNode(std::shared_ptr<Node> l, char o, std::shared_ptr<Node> r)
        : left(l), op(o), right(r) {}
};

struct VarNode : Node {
    std::string name;
    VarNode(const std::string &n) : name(n) {}
};

struct AssignNode : Node {
    std::string name;
    std::shared_ptr<Node> value;
    AssignNode(const std::string &n, std::shared_ptr<Node> val) : name(n), value(val) {}
};

struct PrintNode : Node {
    std::shared_ptr<Node> expr;
    PrintNode(std::shared_ptr<Node> e) : expr(e) {}
};

struct StatementsNode : Node {
    std::vector<std::shared_ptr<Node>> statements;
};

#endif // NODE_H