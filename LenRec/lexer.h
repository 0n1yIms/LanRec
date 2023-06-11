#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#define LEXER_CHAR_NORMAL 0  // normal
#define LEXER_CHAR_CLAIN 1  // clain clausure
#define LEXER_CHAR_PLUS 2  // range

class LexerChar;
class LexerCharN;
class LexerToken;
class LexerRule;
class Lexer;



class LexerChar
{
private:
  bool continuous = false;
  std::vector<char> chars;
public:
  LexerChar(char c);
  LexerChar(char from, char to);

  void add(char c);
  bool cmp(char c);
  std::string toString();
};

class LexerCharN {
private:
  std::vector<LexerChar> lexchar;
  std::vector<LexerCharN> charsN;
  int clausure;

  bool compare(char*& c, char *end);
public:
  LexerCharN(LexerChar lexchar);
  LexerCharN(std::vector<LexerCharN> chars, int clausure = LEXER_CHAR_NORMAL);
  bool cmp(char* &c, char *end);
  std::string toString();
};


class LexerToken{
private:            
  std::vector<LexerCharN> token;
  int type;
public:
  LexerToken(std::vector<LexerCharN> tokens, int type = LEXER_CHAR_NORMAL);

  void add(LexerCharN &character);

  bool cmp(char* &str, int len);
};


class LexerRule
{
  private:
  std::vector<LexerToken> rules;
  public:

  LexerRule(std::vector<LexerToken> token);

  void or(LexerToken &token);

  bool cmp(char* str, int len);
};

class Lexer
{
  private:
  std::vector<LexerRule> rules;
  std::vector<LexerRule> out;

  char *input;
  int inputLen;
  int idx = 0;

public:
  Lexer();
  ~Lexer();


  void addToken(LexerRule &token);
  void lex(char* str, int len);

};










#endif // LEXER_H