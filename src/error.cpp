#include "error.h"

namespace Lox {
void report(int line, const std::string &where, const std::string &message) {
  std::cerr << "[line " << line << "] Error" << where << ": " << message
            << std::endl;
}

void error(int line, const std::string &message) {
  report(line, "", message);
  hadError = true;
}
} // namespace Lox
