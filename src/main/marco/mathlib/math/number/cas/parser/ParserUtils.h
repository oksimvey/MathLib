//
// Created by hapoe on 5/27/2026.
//

#ifndef MATHLIB_PARSERUTILS_H
#define MATHLIB_PARSERUTILS_H
#include <string>

class ParserUtils {

    public:
    static constexpr bool isDigit(char c) {
        return (c >= '0' && c <= '9') || c == '.';
    }

    static double parseDoubleFromLeft(const std::string& str, size_t pos) {
        size_t i = pos;
        while (i > 0 && isDigit(str[i - 1])) {
            i--;
        }

        const std::string token = str.substr(i, pos - i);
        return std::stod(token);
    }

    static double parseDoubleFromRight(const std::string& str, size_t pos) {
        size_t i = pos;

        while (i + 1 < str.length() && isDigit(str[i + 1])) {
            i++;
        }

        const std::string token = str.substr(pos, i - pos + 1);
        return std::stod(token);
    }

    static std::string parseFromParenthesis(const std::string& str) {

    }
};

#endif //MATHLIB_PARSERUTILS_H
