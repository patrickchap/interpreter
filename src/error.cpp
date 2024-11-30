#include "error.h"

namespace Lox {
bool hadError = false;
void report(int line, const std::string &where, const std::string &message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << std::endl;
  hadError = true;
}

void error(int line, const std::string &message) { report(line, "", message); }
} // namespace Lox
