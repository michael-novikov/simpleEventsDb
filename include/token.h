#ifndef TOKEN_H
#define TOKEN_H

#include <vector>
#include <string>
#include <sstream>

enum class TokenType {
  DATE,
  EVENT,
  COLUMN,
  LOGICAL_OP,
  COMPARE_OP,
  PAREN_LEFT,
  PAREN_RIGHT,
};

struct Token {
  const std::string value;
  const TokenType type;
};

std::vector<Token> Tokenize(std::istream& cl);

#endif // TOKEN_H
