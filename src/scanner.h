// scanner.h
#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

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

  bool isAtEnd();

public:
  // Constructor to initialize the scanner with the source code
  Scanner(const std::string &source);

  // Scans the entire source code and returns the list of tokens
  std::vector<Token> scanTokens();
  // Scans the next token and adds it to the token list
  void scanToken();

  // Returns the list of tokens generated so far
  const std::vector<Token> &getTokens() const;
};

#endif // SCANNER_H
