#include <iostream>
#include <lexer.h>
#include <vector>

using namespace std;

int main(){
  bool eq;
  char *str = "hola   mundomundosmundass";
  char *stro = str;
  cout << "string lenght: " << strlen(str) << endl;

  LexerChar c('o');
  c.add('a');

  // LexerCharN mundos({{'o'}});
  LexerCharN space({{' '}}, LEXER_CHAR_PLUS);

  LexerCharN mondos({c, {'s'}});
  mondos.or({c});

  LexerCharN mundo_rule({{'m'}, {'u'}, {'n'}, {'d'}, mondos}, LEXER_CHAR_PLUS);
  LexerCharN chars1({{'h'}, {'o'}, {'l'}, c, space, mundo_rule});

  eq = chars1.cmp(str, str + strlen(str));

  cout << "left:" << (str - stro) << endl;
  cout << str << endl;

  // LexerToken token1({chars1, chars3});
  // eq = token1.cmp(str, strlen(str));
  cout << "equals: " << eq << endl;
  
  // LexerRule rule(LexerToken('a', 'z'));

  // cout << rule.cmp("abc", 3) << endl;



  return 0;
}