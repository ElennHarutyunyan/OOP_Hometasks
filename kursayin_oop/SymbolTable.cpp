#include "SymbolTable.h"
#include <stdexcept>

void SymbolTable::set(const std::string &name, double value) {
    table[name] = value;
}

double SymbolTable::get(const std::string &name) {
    if (!exists(name)) throw std::runtime_error("Variable not found: " + name);
    return table[name];
}

bool SymbolTable::exists(const std::string &name) {
    return table.find(name) != table.end();
}