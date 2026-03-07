#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <string>
#include <unordered_map>

class SymbolTable {
    std::unordered_map<std::string, double> table;
public:
    void set(const std::string &name, double value);
    double get(const std::string &name);
    bool exists(const std::string &name);
};

#endif // SYMBOLTABLE_H