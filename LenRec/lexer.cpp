#include "lexer.h"
#include <iostream>
#include <math.h>

using namespace std;

size_t ptrdis(char *begin, char *end)
{
  return abs(end - begin);
}



// lexer character

LexerChar::LexerChar(char c)
{
  chars.push_back(c);
}
LexerChar::LexerChar(char from, char to)
{
  for (int i = from; i <= to; i++)
    chars.push_back((char)i);
  continuous = true;
}
void LexerChar::add(char c)
{
  chars.push_back(c);
}
bool LexerChar::cmp(char c)
{
  for (int i = 0; i < chars.size(); i++)
    if (chars[i] == c)
      return true;
  return false;
}
string LexerChar::toString()
{
  string str = "";
  if (chars.size() == 1)
    str += chars[0];
  else
  {
    if (continuous)
    {
      str += "[";
      str += chars[0];
      str += "-";
      str += chars[chars.size() - 1];
      str += "]";
    }
    else {
      str += "[";
      for (int i = 0; i < chars.size(); i++)
      {
        str += chars[i];
        if (i < chars.size() - 1)
          str += ",";
      }
      str += "]";
    }
  }
  return str;
}

// lexer character n
LexerCharN::LexerCharN(LexerChar lexchar)
{
  this->lexchar.push_back(lexchar);
}

LexerCharN::LexerCharN(vector<LexerCharN> chars, int clausure)
{
  this->charsN = chars;
  this->clausure = clausure;
}
// compare once with all characters
bool LexerCharN::compare(char *&c, char * end)
{
  char *beg = c;
  for (int i = 0; i < charsN.size(); i++)
  {
    if(ptrdis(beg, end) < i)
      return false;
    LexerCharN &character = charsN.at(i);
    cout << character.toString() << endl;
    if (!character.cmp(beg, end))
      return false;
    
  }
  return true;
}
bool LexerCharN::cmp(char *&c, char *end)
{
  if(lexchar.size() != 0){
    bool eq = lexchar[0].cmp(*c);
    if(eq)
      c++;
    return eq;
  }
  if (clausure == LEXER_CHAR_NORMAL)
  {
    if (ptrdis(c, end) < charsN.size())
      return false;
    bool eq = compare(c, end);
    if (eq)
    {
      c += charsN.size();
      return true;
    }
  }
  else if (clausure == LEXER_CHAR_PLUS)
  {
    int equals = 0;
    while (ptrdis(c, end) > charsN.size())
    {
      bool eq = compare(c, end);
      if (eq)
      {
        equals++;
        c += charsN.size();
      }
      else
        break;
    }
    if (equals > 0)
      return true;
    else
      return false;
  }
  else
  {
    int equals = 0;
    
    while (ptrdis(c, end) > charsN.size())
    {
      bool eq = compare(c, end);
      if (eq)
      {
        equals++;
        c += charsN.size();
      }
      else
        break;
    }
    if (equals >= 0)
      return true;
    else
      return false;
  }
}
string LexerCharN::toString()
{
  if(lexchar.size() != 0)
    return lexchar[0].toString();
  string str = "(";
  for (int i = 0; i < charsN.size(); i++)
    str += " " + charsN[i].toString() + " ";
  str += ")";
  if (clausure == LEXER_CHAR_PLUS)
    str += "+";
  else if (clausure == LEXER_CHAR_CLAIN)
    str += "*";
  return str;
}

// lexer token
LexerToken::LexerToken(vector<LexerCharN> tokens, int clausure)
{
  this->token = tokens;
}
void LexerToken::add(LexerCharN &character)
{
  token.push_back(character);
}
bool LexerToken::cmp(char *&str, int len)
{
  char *cfinal = str + len;
  for (int i = 0; i < token.size(); i++)
  {
    LexerCharN &character = token.at(i);
    cout << "token: " << character.toString() << endl;
    if (!character.cmp(str, cfinal))
      return false;
  }
  return true;
}

// lexer rules
LexerRule::LexerRule(vector<LexerToken> tokens)
{
  // this->tokens = tokens;
  // this->type = type;
}


Lexer::Lexer()
{
}

Lexer::~Lexer()
{
}

void Lexer::addToken(LexerRule &rule)
{
  rules.push_back(rule);
}

void Lexer::lex(char *str, int len)
{
  input = str;
  inputLen = len;
  idx = 0;
}
