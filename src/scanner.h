// scanner.h
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace Lox {

// Enum to define token types
enum class TokenType {
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,

  // One or two character tokens.
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,

  // Literals.
  IDENTIFIER,
  STRING,
  NUMBER,

  // Keywords.
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,

  END_OF_FILE
};

// Token class to represent individual tokens
class Token {
public:
  Token(TokenType type, const std::string &lexeme,
        std::shared_ptr<void> literal, int line);

  TokenType type;
  std::string lexeme;
  std::shared_ptr<void> literal;
  int line;

  std::string toString() {
    std::ostringstream out;
    out << token_string[type] << " " << (lexeme.empty() ? "" : lexeme);
    if (literal) {
      out << " " << *std::static_pointer_cast<std::string>(literal);
    } else {
      out << " null";
    }
    return out.str();
  }

private:
  std::map<TokenType, std::string> token_string = {
      {TokenType::LEFT_PAREN, "LEFT_PAREN"},
      {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
      {TokenType::LEFT_BRACE, "LEFT_BRACE"},
      {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
      {TokenType::COMMA, "COMMA"},
      {TokenType::DOT, "DOT"},
      {TokenType::MINUS, "MINUS"},
      {TokenType::PLUS, "PLUS"},
      {TokenType::SEMICOLON, "SEMICOLON"},
      {TokenType::SLASH, "SLASH"},
      {TokenType::STAR, "STAR"},

      {TokenType::BANG, "BANG"},
      {TokenType::BANG_EQUAL, "BANG_EQUAL"},
      {TokenType::EQUAL, "EQUAL"},
      {TokenType::EQUAL_EQUAL, "EQUAL_EQUAL"},
      {TokenType::GREATER, "GREATER"},
      {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
      {TokenType::LESS, "LESS"},
      {TokenType::LESS_EQUAL, "LESS_EQUAL"},

      {TokenType::IDENTIFIER, "IDENTIFIER"},
      {TokenType::STRING, "STRING"},
      {TokenType::NUMBER, "NUMBER"},

      {TokenType::AND, "AND"},
      {TokenType::CLASS, "CLASS"},
      {TokenType::ELSE, "ELSE"},
      {TokenType::FALSE, "FALSE"},
      {TokenType::FUN, "FUN"},
      {TokenType::FOR, "FOR"},
      {TokenType::IF, "IF"},
      {TokenType::NIL, "NIL"},
      {TokenType::OR, "OR"},
      {TokenType::PRINT, "PRINT"},
      {TokenType::RETURN, "RETURN"},
      {TokenType::SUPER, "SUPER"},
      {TokenType::THIS, "THIS"},
      {TokenType::TRUE, "TRUE"},
      {TokenType::VAR, "VAR"},
      {TokenType::WHILE, "WHILE"},

      {TokenType::END_OF_FILE, "EOF"}};
};

class Scanner {
private:
  std::string source;
  std::vector<Token> tokens;
  int start = 0;
  int current = 0;
  int line = 1;

  // Advances the current position and returns the current character
  char advance();

  // Adds a token of the specified type
  void addToken(TokenType type);

  // Adds a token with a literal value
  void addToken(TokenType type, std::shared_ptr<void> literal);

  char peek();
  bool isAtEnd();
  bool match(char expected);

public:
  // Constructor to initialize the scanner with the source code
  Scanner(const std::string &source);

  // Scans the entire source code and returns the list of tokens
  std::vector<Token> scanTokens();
  // Scans the next token and adds it to the token list
  void scanToken();
  void string();

  // Returns the list of tokens generated so far
  const std::vector<Token> &getTokens() const;
};

} // namespace Lox
#endif // SCANNER_H
