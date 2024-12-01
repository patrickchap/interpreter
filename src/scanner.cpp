#include "scanner.h"
#include "error.h"

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

void Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') {
      line++;
    }
    advance();
  }

  if (isAtEnd()) {
    error(line, "Unterminated string.");
    return;
  }
  // handle second '"'
  advance();
  std::string value = source.substr(start + 1, current - start - 2);
  addToken(TokenType::STRING, std::make_shared<std::string>(value));
}

char Scanner::peek() {
  if (isAtEnd()) {
    return '\0';
  }
  return source[current];
}
bool Scanner::isAtEnd() { return current >= source.size(); }

// check if the current character is the expected one
bool Scanner::match(char expected) {
  if (isAtEnd()) {
    return false;
  }
  if (source[current] != expected) {
    return false;
  }
  current++;
  return true;
}

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
    break;
  case ')':
    addToken(TokenType::RIGHT_PAREN);
    break;
  case '{':
    addToken(TokenType::LEFT_BRACE);
    break;
  case '}':
    addToken(TokenType::RIGHT_BRACE);
    break;
  case ',':
    addToken(TokenType::COMMA);
    break;
  case '.':
    addToken(TokenType::DOT);
    break;
  case '-':
    addToken(TokenType::MINUS);
    break;
  case '+':
    addToken(TokenType::PLUS);
    break;
  case ';':
    addToken(TokenType::SEMICOLON);
    break;
  case '*':
    addToken(TokenType::STAR);
    break;
  case '!':
    addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
    break;
  case '=':
    addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
    break;
  case '<':
    addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
    break;
  case '>':
    addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
    break;
  case '/':
    if (match('/')) {
      while (peek() != '\n' && !isAtEnd()) {
        advance();
      }
    } else {
      addToken(TokenType::SLASH);
    }

    break;
  case '"':
    string();
    break;

  case ' ':
  case '\r':
  case '\t':
    // Ignore whitespace.
    break;
  case '\n':
    line++;
    break;
  default:
    std::ostringstream ss;
    ss << "Unexpected character: " << c;
    error(line, ss.str());
    break;
  }
}

const std::vector<Token> &Scanner::getTokens() const { return tokens; }
} // namespace Lox
