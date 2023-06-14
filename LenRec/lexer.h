#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#define LEXER_CHAR_NORMAL 0  // normal
#define LEXER_CHAR_CLAIN 1  // clain clausure
#define LEXER_CHAR_PLUS 2  // range

class LexerChar;
class LexerCharN;
// class LexerToken;
class LexerRule;
class Lexer;


typedef std::vector<LexerCharN> LexerToken;

class LexerChar
{
private:
  bool continuous = false;
  std::vector<char> chars;
public:
  LexerChar(char c);
  LexerChar(char from, char to);

  void add(char c);
  void add(char from, char to);
  bool cmp(char c);
  std::string toString();
};



class LexerCharN {
private:
  std::vector<LexerChar> lexchar;
  std::vector<LexerToken> tokens;
  // int currentToken;
  int clausure;

public:
  LexerCharN(LexerChar lexchar);
  LexerCharN(LexerToken token, int clausure = LEXER_CHAR_NORMAL);
  bool cmp(char* &c, char *end);
  void or(LexerToken token);

  std::string toString();
};

class Lexer
{
  private:
  std::vector<std::pair<LexerCharN, char*>> rules;
  std::vector<char*> out;

  char *input;
  int inputLen;
  int idx = 0;

public:
  Lexer();
  ~Lexer();


  void addRule(LexerCharN &rule, char* tokenName);
  void lexPrint(char* str);
  std::vector<char*> lex(char* str);
};








#endif // LEXER_H