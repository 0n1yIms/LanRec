#include <iostream>
#include <lexer.h>
#include <vector>

using namespace std;

int main(){
  bool eq;
  char *str = "hola   mundomundomundo";
  char *stro = str;
  cout << "string lenght: " << strlen(str) << endl;

  LexerChar c('o');
  c.add('a');

  LexerCharN space({{' '}}, LEXER_CHAR_PLUS);

  LexerCharN mundo_rule({{'m'}, {'u'}, {'n'}, {'d'}, c}, LEXER_CHAR_PLUS);
  LexerCharN chars1({{'h'}, {'o'}, {'l'}, c, space, mundo_rule});

  cout << "left:" << (str - stro) << endl;
  eq = chars1.cmp(str, str + strlen(str));



  // LexerToken token1({chars1, chars3});
  // eq = token1.cmp(str, strlen(str));
  cout << "equals: " << eq << endl;
  
  // LexerRule rule(LexerToken('a', 'z'));

  // cout << rule.cmp("abc", 3) << endl;



  return 0;
}