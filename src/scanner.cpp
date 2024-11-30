#include "scanner.h"

namespace Lox {

Token::Token(TokenType type, const std::string &lexeme,
             std::shared_ptr<void> literal, int line)
    : type(type), lexeme(lexeme), literal(literal), line(line) {}

Scanner::Scanner(const std::string &source) : source(source) {}

char Scanner::advance() { return source[current++]; }

void Scanner::addToken(TokenType type) { addToken(type, nullptr); }

void Scanner::addToken(TokenType type, std::shared_ptr<void> literal) {
  std::string text = source.substr(start, current - start);
  tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::isAtEnd() { return current >= source.size(); }

std::vector<Token> Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back(Token(TokenType::END_OF_FILE, "", nullptr, line));
  return tokens;
}
void Scanner::scanToken() {
  char c = advance();
  switch (c) {
  case '(':
    addToken(TokenType::LEFT_PAREN);
    std::cout << "LEFT_PAREN ( null" << std::endl;
    break;
  case ')':
    addToken(TokenType::RIGHT_PAREN);
    std::cout << "RIGHT_PAREN ) null" << std::endl;
    break;
  case '{':
    addToken(TokenType::LEFT_BRACE);
    std::cout << "LEFT_BRACE { null" << std::endl;
    break;
  case '}':
    addToken(TokenType::RIGHT_BRACE);
    std::cout << "RIGHT_BRACE } null" << std::endl;
    break;
  case ',':
    addToken(TokenType::COMMA);
    std::cout << "COMMA , null" << std::endl;
    break;
  case '.':
    addToken(TokenType::DOT);
    std::cout << "DOT . null" << std::endl;
    break;
  case '-':
    addToken(TokenType::MINUS);
    std::cout << "MINUS - null" << std::endl;
    break;
  case '+':
    addToken(TokenType::PLUS);
    std::cout << "PLUS + null" << std::endl;
    break;
  case ';':
    addToken(TokenType::SEMICOLON);
    std::cout << "SEMICOLON ; null" << std::endl;
    break;
  case '*':
    addToken(TokenType::STAR);
    std::cout << "STAR * null" << std::endl;
    break;
  case '\n':
    line++;
    break;
  default:
    std::cout << "[line" << line << "] Error: Unexpected character: " << c
              << std::endl;
    break;
  }
}

const std::vector<Token> &Scanner::getTokens() const { return tokens; }
} // namespace Lox
