#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <string>

namespace Lox {
extern bool hadError;

void report(int line, const std::string &where, const std::string &message);

void error(int line, const std::string &message);
} // namespace Lox

#endif // ERROR_H
