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
    else
    {
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

LexerCharN::LexerCharN(LexerToken token, int clausure)
{
  this->tokens.push_back(token);
  this->clausure = clausure;
}
// bool LexerCharN::cmp(char *&c, char *end)
// {
//   for (int i = 0; i < tokens.size(); i++)
//   {
//     currentToken = i;
//     if (cmp2(c, end))
//       return true;
//   }
//   return false;
// }

bool LexerCharN::cmp(char *&c, char *end)
{
  // LexerToken charsN = tokens[currentToken];
  if (lexchar.size() != 0)
  {
    bool eq = lexchar[0].cmp(*c);
    if (eq)
      c++;
    return eq;
  }
  char *original = c;
  vector<int> tokenDistance(tokens.size());

  for (int tokenIdx = 0; tokenIdx < tokens.size(); tokenIdx++)
  {

    if (clausure == LEXER_CHAR_NORMAL)
    {
      if (ptrdis(c, end) < tokens[tokenIdx].size()){
        tokenDistance[tokenIdx] = -1;
        continue;
        // return false;
      }

      bool eq = true; // compare(c, end);
      for (int i = 0; i < tokens[tokenIdx].size(); i++)
      {
        LexerCharN &character = tokens[tokenIdx].at(i);
        cout << character.toString() << endl;

        if (!character.cmp(c, end))
        {
          eq = false;
          break;
        }
      }

      if (eq)
      {
        // c += charsN.size();
        tokenDistance[tokenIdx] = ptrdis(c, original);
        continue;
        // return true;
      }
      else{
        tokenDistance[tokenIdx] = -1;
        continue;
        // return false;
      }
    }
    else if (clausure == LEXER_CHAR_PLUS)
    {
      int equals = 0;
      while (ptrdis(c, end) > tokens[tokenIdx].size())
      {
        bool eq = true; // compare(c, end);
        for (int i = 0; i < tokens[tokenIdx].size(); i++)
        {
          LexerCharN &character = tokens[tokenIdx].at(i);
          cout << character.toString() << endl;

          if (!character.cmp(c, end))
          {
            eq = false;
            break;
          }
        }
        if (eq)
        {
          equals++;
          // c += charsN.size();
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

      while (ptrdis(c, end) > tokens[tokenIdx].size())
      {
        bool eq = true; // compare(c, end);
        for (int i = 0; i < tokens[tokenIdx].size(); i++)
        {
          LexerCharN &character = tokens[tokenIdx].at(i);
          cout << character.toString() << endl;

          if (!character.cmp(c, end))
          {
            eq = false;
            break;
          }
        }
        if (eq)
        {
          equals++;
          // c += charsN.size();
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
}
string LexerCharN::toString()
{
  if (lexchar.size() != 0)
    return lexchar[0].toString();

  string str = "(";
  for (int i = 0; i < tokens.size(); i++)
  {
    str += "(";
    for (int j = 0; j < tokens[i].size(); j++)
      str += " " + tokens[i][j].toString() + " ";
    str += ")";
    if (clausure == LEXER_CHAR_PLUS)
      str += "+";
    else if (clausure == LEXER_CHAR_CLAIN)
      str += "*";
    str += ")";

    if (i != tokens.size() - 1)
      str += " | ";
  }
  return str;
}
void LexerCharN:: or (LexerToken token)
{
  this->tokens.push_back(token);
}

/*
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
*/