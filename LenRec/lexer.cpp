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
void LexerChar::add(char from, char to)
{
  for (int i = from; i <= to; i++)
    chars.push_back((char)i);
  continuous = false;
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
  if (lexchar.size() != 0)
  {
    bool eq = lexchar[0].cmp(*c);
    if (eq)
      c++;
    return eq;
  }

  if (clausure == LEXER_CHAR_NORMAL)
  {
    vector<char *> tokenDistance(tokens.size());

    for (int tokenIdx = 0; tokenIdx < tokens.size(); tokenIdx++)
    {
      LexerToken &charsN = tokens[tokenIdx];
      char *cToken = c;

      if (ptrdis(cToken, end) < charsN.size())
      {
        tokenDistance[tokenIdx] = nullptr;
        continue;
      }

      bool eq = true; // compare(c, end);
      for (int i = 0; i < charsN.size(); i++)
      {
        LexerCharN &character = charsN.at(i);
        // cout << character.toString() << endl;

        if (!character.cmp(cToken, end))
        {
          eq = false;
          break;
        }
      }

      if (eq)
        tokenDistance[tokenIdx] = cToken;
      else
        tokenDistance[tokenIdx] = nullptr;
    }
    int max = 0;
    int id = -1;
    for (int i = tokenDistance.size() - 1; i >= 0; i--)
    {
      if (tokenDistance[i] != nullptr)
      {
        int dis = ptrdis(c, tokenDistance[i]);
        if (dis >= max)
        {
          max = dis;
          id = i;
        }
      }
    }
    if (id != -1)
    {
      c = tokenDistance[id];
      return true;
    }
    else
      return false;
  }
  else if (clausure == LEXER_CHAR_PLUS)
  {
    vector<char *> tokenDistance(tokens.size());

    for (int tokenIdx = 0; tokenIdx < tokens.size(); tokenIdx++)
    {
      LexerToken &charsN = tokens[tokenIdx];
      char *cToken = c;

      int equals = 0;
      while (ptrdis(c, end) > charsN.size())
      {
        bool eq = true;
        for (int i = 0; i < charsN.size(); i++)
        {
          LexerCharN &character = charsN.at(i);
          // cout << character.toString() << endl;

          if (!character.cmp(cToken, end))
          {
            eq = false;
            break;
          }
        }
        if (eq)
          equals++;
        else
          break;
      }
      if (equals > 0)
        tokenDistance[tokenIdx] = cToken;
      else
        tokenDistance[tokenIdx] = nullptr;
    }
    int max = 0;
    int id = -1;
    for (int i = tokenDistance.size() - 1; i >= 0; i--)
    {
      if (tokenDistance[i] != nullptr)
      {
        int dis = ptrdis(c, tokenDistance[i]);
        if (dis >= max)
        {
          max = dis;
          id = i;
        }
      }
    }
    if (id != -1)
    {
      c = tokenDistance[id];
      return true;
    }
    else
      return false;
  }
  else
  {
    vector<char *> tokenDistance(tokens.size());

    for (int tokenIdx = 0; tokenIdx < tokens.size(); tokenIdx++)
    {
      LexerToken &charsN = tokens[tokenIdx];
      char *cToken = c;

      int equals = 0;
      while (ptrdis(c, end) > charsN.size())
      {
        bool eq = true;
        for (int i = 0; i < charsN.size(); i++)
        {
          LexerCharN &character = charsN.at(i);
          // cout << character.toString() << endl;

          if (!character.cmp(cToken, end))
          {
            eq = false;
            break;
          }
        }
        if (eq)
          equals++;
        else
          break;
      }
      if (equals >= 0)
        tokenDistance[tokenIdx] = cToken;
      else
        tokenDistance[tokenIdx] = nullptr;
    }
    int max = 0;
    int id = -1;
    for (int i = tokenDistance.size() - 1; i >= 0; i--)
    {
      if (tokenDistance[i] != nullptr)
      {
        int dis = ptrdis(c, tokenDistance[i]);
        if (dis >= max)
        {
          max = dis;
          id = i;
        }
      }
    }
    if (id != -1)
    {
      c = tokenDistance[id];
      return true;
    }
    else
      return false;
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

Lexer::Lexer()
{
}
Lexer::~Lexer()
{
}
void Lexer::addRule(LexerCharN &rule, char *tokenName)
{
  rules.push_back({rule, tokenName});
}

void Lexer::lexPrint(char *c)
{
  int len = strlen(c);
  char *end = c + len;

  while (c != end)
  {
    vector<char *> tokenDistance(rules.size());
    for (int i = 0; i < rules.size(); i++)
    {
      LexerCharN &rule = rules[i].first;
      char *tokenName = rules[i].second;

      char *cToken = c;
      if (!rule.cmp(cToken, end))
        tokenDistance[i] = nullptr;
      else
        tokenDistance[i] = cToken;
    }
    int max = 0;
    int id = -1;
    for (int i = tokenDistance.size() - 1; i >= 0; i--)
    {
      if (tokenDistance[i] != nullptr)
      {
        int dis = ptrdis(c, tokenDistance[i]);
        if (dis >= max)
        {
          max = dis;
          id = i;
        }
      }
    }
    if (id != -1)
    {
      c = tokenDistance[id];
      cout << rules[id].second << endl;
    }
    else 
      break;
  }
}

vector<char*> Lexer::lex(char *c)
{
  vector<char*> tokens;
  int len = strlen(c);
  char *end = c + len;

  while (c != end)
  {
    vector<char *> tokenDistance(rules.size());
    for (int i = 0; i < rules.size(); i++)
    {
      LexerCharN &rule = rules[i].first;
      char *tokenName = rules[i].second;

      char *cToken = c;
      if (!rule.cmp(cToken, end))
        tokenDistance[i] = nullptr;
      else
        tokenDistance[i] = cToken;
    }
    int max = 0;
    int id = -1;
    for (int i = tokenDistance.size() - 1; i >= 0; i--)
    {
      if (tokenDistance[i] != nullptr)
      {
        int dis = ptrdis(c, tokenDistance[i]);
        if (dis >= max)
        {
          max = dis;
          id = i;
        }
      }
    }
    if (id != -1)
    {
      c = tokenDistance[id];
      tokens.push_back(rules[id].second);
    }
    else 
      break;
  }
  return tokens;
}
