#pragma once

#include <string>
#include <unordered_map>
template<typename T>
class SymbolicExpression {

    std::unordered_map<std::string, T> varManager;

    public:



    void putVariable(const std::string& var, const T& value) { varManager[var] = value; }

    




};