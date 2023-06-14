#include <iostream>
#include <lexer.h>
#include <vector>
#include <automatonPushDown.h>
#include <iomanip>

using namespace std;

#define newfun(...) ("" #__VA_ARGS__ "")

int main(){

  char *code = newfun(<buffer<int> in, buffer<float> out> {
    out[0] = in[0] + in[1];
  });

  cout << code << endl;

  char *allTerms = newfun(
    void f;
    int a;
    float b;
    bool c;
    char d;
    b = a + 1;

  );

  newfun(void     -> 'void'
  int             -> 'int'
  float           -> 'float'
  bool            -> 'bool'
  char            -> 'char'
  name            -> [a-zA-Z]+
  number          -> [0-9]+
  numberF         -> [0-9]+.[0-9]*
  opPlus          -> '+'
  opMinus         -> '-'
  opMult          -> '*'
  opDiv           -> '/'
  assign          -> '='
  greaterT        -> '>'
  lowestT         -> '<'
  greaterEq       -> '>='
  lowestEq        -> '<='
  equals          -> '=='
  NotEquals       -> '!='
  opAnd           -> '&&'
  opOr            -> '||'
  opNot           -> '!'
  parL            -> '('
  parR            -> ')'
  brL             -> '{'
  brR             -> '}'
  sqBrL           -> '['
  sqBrR           -> ']'
  semi            -> ';'
  comma           -> ','
  dot             -> '.'
  colon           -> ':'
  percent         -> '%'
  slash           -> '/'
  space           -> ' '
  if              -> 'if'
  else            -> 'else'
  while           -> 'while'
  for             -> 'for'
  return          -> 'return'
  break           -> 'break'
  continue        -> 'continue'
  true            -> 'true'
  false           -> 'false'

  );

  

  LexerCharN void_R({ {'v'}, {'o'}, {'i'}, {'d'} });
  LexerCharN int_R({ {'i'}, {'n'}, {'t'} });
  LexerCharN float_R({ {'f'}, {'l'}, {'o'}, {'a'}, {'t'} });
  LexerCharN bool_R({ {'b'}, {'o'}, {'o'}, {'l'} });
  LexerCharN char_R({ {'c'}, {'h'}, {'a'}, {'r'} });

  LexerChar name_C('a', 'z');
  name_C.add('A', 'Z');
  LexerCharN name_R({name_C}, LEXER_CHAR_PLUS);

  LexerChar number_C('0', '9');
  LexerCharN number_R({number_C}, LEXER_CHAR_PLUS);

  LexerCharN numberF_L({number_C}, LEXER_CHAR_CLAIN);
  LexerCharN numberF_R({number_C, {'.'}, numberF_L}, LEXER_CHAR_PLUS);

  LexerCharN opPlus_R(LexerChar('+'));
  LexerCharN opMinus_R(LexerChar('-'));
  LexerCharN opMult_R(LexerChar('*'));
  LexerCharN opDiv_R(LexerChar('/'));
  LexerCharN assign_R(LexerChar('='));
  LexerCharN gt_R(LexerChar('>'));
  LexerCharN lt_R(LexerChar('<'));
  LexerCharN ge_R({LexerChar('>'), LexerChar('=')});
  LexerCharN le_R({LexerChar('<'), LexerChar('=')});
  LexerCharN equals_R({LexerChar('='), LexerChar('=')});
  LexerCharN notEquals_R({LexerChar('!'), LexerChar('=')});
  LexerCharN and_R({LexerChar('&'), LexerChar('&')});
  LexerCharN or_R({LexerChar('|'), LexerChar('|')});
  LexerCharN not_R(LexerChar('!'));
  LexerCharN parL_R(LexerChar('('));
  LexerCharN parR_R(LexerChar(')'));
  LexerCharN brL_R(LexerChar('{'));
  LexerCharN brR_R(LexerChar('}'));
  LexerCharN sqBrL_R(LexerChar('['));
  LexerCharN sqBrR_R(LexerChar(']'));
  LexerCharN semi_R(LexerChar(';'));
  LexerCharN comma_R(LexerChar(','));
  LexerCharN dot_R(LexerChar('.'));
  LexerCharN colon_R(LexerChar(':'));
  LexerCharN percent_R(LexerChar('%'));
  LexerCharN slash_R(LexerChar('/'));
  LexerCharN space_R(LexerChar(' '));

  LexerCharN if_R(vector<LexerCharN>{ {'i'}, {'f'} });
  LexerCharN else_R({ {'e'}, {'l'}, {'s'}, {'e'} });
  LexerCharN while_R({ {'w'}, {'h'}, {'i'}, {'l'}, {'e'} });
  LexerCharN for_R({ {'f'}, {'o'}, {'r'} });
  LexerCharN return_R({ {'r'}, {'e'}, {'t'}, {'u'}, {'r'}, {'n'} });
  LexerCharN break_R({ {'b'}, {'r'}, {'e'}, {'a'}, {'k'} });
  LexerCharN continue_R({ {'c'}, {'o'}, {'n'}, {'t'}, {'i'}, {'n'}, {'u'}, {'e'} });
  LexerCharN true_R({ {'t'}, {'r'}, {'u'}, {'e'} });
  LexerCharN false_R({ {'f'}, {'a'}, {'l'}, {'s'}, {'e'} });



  Lexer lexer;
  lexer.addRule(if_R, "if");
  lexer.addRule(else_R, "else");
  lexer.addRule(while_R, "while");
  lexer.addRule(for_R, "for");
  lexer.addRule(return_R, "return");
  lexer.addRule(break_R, "break");
  lexer.addRule(continue_R, "continue");
  lexer.addRule(true_R, "true");
  lexer.addRule(false_R, "false");
  lexer.addRule(void_R, "void");
  lexer.addRule(int_R, "int");
  lexer.addRule(float_R, "float");
  lexer.addRule(bool_R, "bool");
  lexer.addRule(char_R, "char");
  lexer.addRule(name_R, "name");
  lexer.addRule(number_R, "number");
  lexer.addRule(numberF_R, "numberF");
  lexer.addRule(opPlus_R, "opPlus");
  lexer.addRule(opMinus_R, "opMinus");
  lexer.addRule(opMult_R, "opMult");
  lexer.addRule(opDiv_R, "opDiv");
  lexer.addRule(assign_R, "assign");
  lexer.addRule(gt_R, "gt");
  lexer.addRule(lt_R, "lt");
  lexer.addRule(ge_R, "ge");
  lexer.addRule(le_R, "le");
  lexer.addRule(equals_R, "equals");
  lexer.addRule(notEquals_R, "notEquals");
  lexer.addRule(and_R, "and");
  lexer.addRule(or_R, "or");
  lexer.addRule(not_R, "not");
  lexer.addRule(parL_R, "parL");
  lexer.addRule(parR_R, "parR");
  lexer.addRule(brL_R, "brL");
  lexer.addRule(brR_R, "brR");
  lexer.addRule(sqBrL_R, "sqBrL");
  lexer.addRule(sqBrR_R, "sqBrR");
  lexer.addRule(semi_R, "semi");
  lexer.addRule(comma_R, "comma");
  lexer.addRule(dot_R, "dot");
  lexer.addRule(colon_R, "colon");
  lexer.addRule(percent_R, "percent");
  lexer.addRule(slash_R, "slash");
  lexer.addRule(space_R, "space");

  

  char *text = newfun(
    void main(){
      int a;
      float b = 0;
      if((float)a == b){
        return true;
      }
      else{
        return false;
      }
    }
  );

  cout << "text: " << text << "\n\n";
  lexer.lexPrint(text);
  



  

  // Alphabet alp = newAlphabet(a, b, c, d);
  // Alphabet NoTerminals = newAlphabet(S, A, B, C, D);
  // Rules rules = newRules(
    // A -> aAa,
    // B -> bBc,
    // S -> AB
  // );

  // Grammar grammar = newGrammar(alp, NoTerminals, rules, S);


  // w1 = abbbccca;
  // w2 = aabbbccc;

  // Grammar grammar;
  // Terminal a = grammar.addTerminal('a');
  // Terminal b = grammar.addTerminal('b');
  // Terminal c = grammar.addTerminal('c');

  // NoTerminal A = grammar.addNoTerminal('A');
  // NoTerminal B = grammar.addNoTerminal('B');
  // NoTerminal S = grammar.addNoTerminal('S');

  // A -> __E;
  // A -> a + A + a;

  // B -> a;
  // B -> b + B + c;
  // S -> A + B;


  AutomatonPD aut;

  State q0 = aut.addState();
  State q1 = aut.addState();
  State q2 = aut.addState();

  SigmaT a = aut.addSigmaTerminal();
  SigmaT b = aut.addSigmaTerminal();
  SigmaT c = aut.addSigmaTerminal();

  SigmaN A = aut.addSigmaNoTerminal();
  SigmaN B = aut.addSigmaNoTerminal();
  SigmaN S = aut.addSigmaNoTerminal();

  //        (entrada, pila, salida)
  // q0, q1  (q0, a, A, aA)

  aut.addTransitions(
  {
    {q0, q1, a, A, {a, A}},
    {q0, q0, _epsilon, A, {_epsilon}}
    
  });



  // S.run("aabbbccc");
  // //find A, find B

  // A.run("aabbbccc");


  // LexerCharN dataType_R({void_R});
  // dataType_R.or({int_R});
  // dataType_R.or({float_R});
  // dataType_R.or({bool_R});


  // LexerCharN space_R({{' '}}, LEXER_CHAR_CLAIN);
  // LexerCharN decl_R({space_R, dataType_R, space_R, name_R, space_R, {';'}}, LEXER_CHAR_CLAIN);


  // LexerCharN mundos({{'o'}});

  // eq = decl_R.cmp(str, str + strlen(str));

  // cout << "left:" << (str - stro) << endl;
  // cout << str << endl;

  // LexerToken token1({chars1, chars3});
  // eq = token1.cmp(str, strlen(str));
  // cout << "equals: " << eq << endl;
  
  // LexerRule rule(LexerToken('a', 'z'));

  // cout << rule.cmp("abc", 3) << endl;



  return 0;
}