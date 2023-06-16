#include <iostream>
#include <lexer.h>
#include <vector>
#include <iomanip>
#include <automatonPushDown.h>
#include <grammar.h>
#include <grammarToAutomaton.h>

using namespace std;

#define newfun(...) ("" #__VA_ARGS__ "")

#define newRule(a, b) cvtRule("" #a, "" #b "")

char *rulesComment = newfun(void     -> 'void'
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

void testAutomaton()
{
  State q0("q0");
  State q1("q1");
  State q2("q2");

  Alphabet a("a");
  Alphabet b("b");
  Alphabet c("c");

  Alphabet Z0("Z0");
  Alphabet A("A");
  Alphabet B("B");
  Alphabet S("S");

  vector<Transition> transitions(
      {
          {q0, q0, a, Z0, {a, Z0}},
          {q0, q0, a, a, {a, a}},
          {q0, q1, _eps, a, {a}},
          {q1, q1, b, a, {_eps}},
          {q1, q2, _eps, Z0, {_eps}},
      });

  Word w{a, a, b, b};
  AutomatonPD aut(
      {q0, q1, q2},
      {a, b, c},
      {Z0, A, B, S},
      transitions,
      q0,
      Z0,
      {q2});

  bool r = aut.run(w);
  cout << r << endl;
}

void testLexer()
{
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

  LexerCharN void_R({{'v'}, {'o'}, {'i'}, {'d'}});
  LexerCharN int_R({{'i'}, {'n'}, {'t'}});
  LexerCharN float_R({{'f'}, {'l'}, {'o'}, {'a'}, {'t'}});
  LexerCharN bool_R({{'b'}, {'o'}, {'o'}, {'l'}});
  LexerCharN char_R({{'c'}, {'h'}, {'a'}, {'r'}});

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

  LexerCharN if_R(vector<LexerCharN>{{'i'}, {'f'}});
  LexerCharN else_R({{'e'}, {'l'}, {'s'}, {'e'}});
  LexerCharN while_R({{'w'}, {'h'}, {'i'}, {'l'}, {'e'}});
  LexerCharN for_R({{'f'}, {'o'}, {'r'}});
  LexerCharN return_R({{'r'}, {'e'}, {'t'}, {'u'}, {'r'}, {'n'}});
  LexerCharN break_R({{'b'}, {'r'}, {'e'}, {'a'}, {'k'}});
  LexerCharN continue_R({{'c'}, {'o'}, {'n'}, {'t'}, {'i'}, {'n'}, {'u'}, {'e'}});
  LexerCharN true_R({{'t'}, {'r'}, {'u'}, {'e'}});
  LexerCharN false_R({{'f'}, {'a'}, {'l'}, {'s'}, {'e'}});

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
      void main() {
        int a;
        float b = 0;
        if ((float)a == b)
        {
          return true;
        }
        else
        {
          return false;
        }
      });

  cout << "text: " << text << "\n\n";
  lexer.lexPrint(text);
}

void testCLang(){
 char* token_if = "if";
 char* token_else = "else";
 char* token_while = "while";
 char* token_for = "for";
 char* token_return = "return";
 char* token_break = "break";
 char* token_continue = "continue";
 char* token_true = "true";
 char* token_false = "false";
 char* token_void = "void";
 char* token_int = "int";
 char* token_float = "float";
 char* token_bool = "bool";
 char* token_char = "char";
 char* token_name = "name";
 char* token_number = "number";
 char* token_numberF = "numberF";
 char* token_opPlus = "opPlus";
 char* token_opMinus = "opMinus";
 char* token_opMult = "opMult";
 char* token_opDiv = "opDiv";
 char* token_assign = "assign";
 char* token_gt = "gt";
 char* token_lt = "lt";
 char* token_ge = "ge";
 char* token_le = "le";
 char* token_equals = "equals";
 char* token_notEquals = "notEquals";
 char* token_and = "and";
 char* token_or = "or";
 char* token_not = "not";
 char* token_parL = "parL";
 char* token_parR = "parR";
 char* token_brL = "brL";
 char* token_brR = "brR";
 char* token_sqBrL = "sqBrL";
 char* token_sqBrR = "sqBrR";
 char* token_semi = "semi";
 char* token_comma = "comma";
 char* token_dot = "dot";
 char* token_colon = "colon";
 char* token_percent = "percent";
 char* token_slash = "slash";
 char* token_space = "space";


  LexerCharN void_R({{'v'}, {'o'}, {'i'}, {'d'}});
  LexerCharN int_R({{'i'}, {'n'}, {'t'}});
  LexerCharN float_R({{'f'}, {'l'}, {'o'}, {'a'}, {'t'}});
  LexerCharN bool_R({{'b'}, {'o'}, {'o'}, {'l'}});
  LexerCharN char_R({{'c'}, {'h'}, {'a'}, {'r'}});

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

  LexerCharN if_R(vector<LexerCharN>{{'i'}, {'f'}});
  LexerCharN else_R({{'e'}, {'l'}, {'s'}, {'e'}});
  LexerCharN while_R({{'w'}, {'h'}, {'i'}, {'l'}, {'e'}});
  LexerCharN for_R({{'f'}, {'o'}, {'r'}});
  LexerCharN return_R({{'r'}, {'e'}, {'t'}, {'u'}, {'r'}, {'n'}});
  LexerCharN break_R({{'b'}, {'r'}, {'e'}, {'a'}, {'k'}});
  LexerCharN continue_R({{'c'}, {'o'}, {'n'}, {'t'}, {'i'}, {'n'}, {'u'}, {'e'}});
  LexerCharN true_R({{'t'}, {'r'}, {'u'}, {'e'}});
  LexerCharN false_R({{'f'}, {'a'}, {'l'}, {'s'}, {'e'}});

  Lexer lexer;
  lexer.addRule(if_R, token_if);
  lexer.addRule(else_R, token_else);
  lexer.addRule(while_R, token_while);
  lexer.addRule(for_R, token_for);
  lexer.addRule(return_R, token_return);
  lexer.addRule(break_R, token_break);
  lexer.addRule(continue_R, token_continue);
  lexer.addRule(true_R, token_true);
  lexer.addRule(false_R, token_false);
  lexer.addRule(void_R, token_void);
  lexer.addRule(int_R, token_int);
  lexer.addRule(float_R, token_float);
  lexer.addRule(bool_R, token_bool);
  lexer.addRule(char_R, token_char);
  lexer.addRule(name_R, token_name);
  lexer.addRule(number_R, token_number);
  lexer.addRule(numberF_R, token_numberF);
  lexer.addRule(opPlus_R, token_opPlus);
  lexer.addRule(opMinus_R, token_opMinus);
  lexer.addRule(opMult_R, token_opMult);
  lexer.addRule(opDiv_R, token_opDiv);
  lexer.addRule(assign_R, token_assign);
  lexer.addRule(gt_R, token_gt);
  lexer.addRule(lt_R, token_lt);
  lexer.addRule(ge_R, token_ge);
  lexer.addRule(le_R, token_le);
  lexer.addRule(equals_R, token_equals);
  lexer.addRule(notEquals_R, token_notEquals);
  lexer.addRule(and_R, token_and);
  lexer.addRule(or_R, token_or);
  lexer.addRule(not_R, token_not);
  lexer.addRule(parL_R, token_parL);
  lexer.addRule(parR_R, token_parR);
  lexer.addRule(brL_R, token_brL);
  lexer.addRule(brR_R, token_brR);
  lexer.addRule(sqBrL_R, token_sqBrL);
  lexer.addRule(sqBrR_R, token_sqBrR);
  lexer.addRule(semi_R, token_semi);
  lexer.addRule(comma_R, token_comma);
  lexer.addRule(dot_R, token_dot);
  lexer.addRule(colon_R, token_colon);
  lexer.addRule(percent_R, token_percent);
  lexer.addRule(slash_R, token_slash);
  lexer.addRule(space_R, token_space);

  char *text = newfun(
      void main() {
        int a;
        float b = 0;
        double c = a + (b + 1) + 2;
        if ((float)a == b)
        {
          return true;
        }
        else
        {
          return false;
        }
      });

  cout << "text: " << text << "\n\n";
  vector<Token> tokens = lexer.lexPrint(text);
  
  Grammar grammar;

  newfun(
    Expr1 -> name | number | numberF;
    Expr1 -> (Expr);
    Expr1 -> name * Expr1 | number * Expr1 | numberF * Expr1;
    Expr1 -> name / Expr1 | number / Expr1 | numberF / Expr1;
    Expr2 -> Expr1;
    Expr2 -> Expr2 + Expr1 | Expr2 - Expr1;
    Expr3 -> Expr2;
    Expr3 -> Expr3 > Expr2 | Expr3 < Expr2 | Expr3 >= Expr2 | Expr3 <= Expr2;
    Expr4 -> Expr3;
    Expr4 -> Expr4 == Expr3 | Expr4 != Expr3;
    Expr5 -> Expr4;
    Expr5 -> Expr5 && Expr4;
    Expr6 -> Expr5;
    Expr6 -> Expr6 || Expr5;
    Expr7 -> Expr6;
    Expr7 -> !Expr7;
    Expr8 -> Expr7;
    Expr8 -> Expr8 ? Expr8 : Expr8;
    Expr9 -> Expr8;
    Expr9 -> Expr9[Expr9];
    Expr10 -> Expr9;
    Expr10 -> Expr10(Expr10);
    Expr11 -> Expr10;
    Expr11 -> Expr11 = Expr11;
    Expr12 -> Expr11;
    Expr12 -> Expr12++ | Expr12--;
    Expr13 -> ++Expr12 | --Expr12;
    Expr -> Expr13;
    Expr -> true | false;
    Expr -> Expr;
    Expr -> name(Expr) | name(Expr, Expr) | name(Expr, Expr, Expr) | name(Expr, Expr, Expr, Expr);
    Expr -> Expr;
    Expr -> Expr;
    




    Expr -> Expr + Expr
    Expr -> Expr - Expr
    Expr -> Expr * Expr
    Expr -> Expr / Expr
    Expr -> Expr % Expr
    Expr -> Expr > Expr
    Expr -> Expr < Expr
    Expr -> Expr >= Expr
    Expr -> Expr <= Expr
    Expr -> Expr == Expr
    Expr -> Expr != Expr
    Expr -> Expr && Expr
    Expr -> Expr || Expr
    Expr -> !Expr
    Expr -> (Expr)
    Expr -> Expr ? Expr : Expr
    Expr -> Expr[Expr]
    Expr -> Expr(Expr)
    Expr -> Expr = Expr
    Expr -> Expr++
    Expr -> Expr--
    Expr -> ++Expr
    Expr -> --Expr
    Expr -> Expr
    Expr -> true
    Expr -> false
    Expr -> number
    Expr -> numberF
    Expr -> name
    Expr -> name(Expr)
    Expr -> name(Expr, Expr)
    Expr -> name(Expr, Expr, Expr)
    Expr -> name(Expr, Expr, Expr, Expr)

  );

  Rule r1{{"S"}, {'(', "S", ')'}};



}


int main()
{
  

  Lexer lexer;

  Symbol parenO("(");
  Symbol parenC(")");
  Symbol sqParO("[");
  Symbol sqParC("]");
  Symbol Sa("S");

  Rule r1{Sa, {parenO, Sa, parenC}};
  Rule r2{Sa, {sqParO, Sa, sqParC}};
  Rule r3{Sa, {Sa, Sa}};
  Rule r4{Sa, {gEps}};

  Grammar grammar(
      {parenO, parenC, sqParO, sqParC},
      {Sa},
      Sa,
      {r1, r2, r3, r4});

  AutomatonPD autom = grammarToAutomaton(grammar);
  Alphabet pO{"("};
  Alphabet pC{")"};
  Alphabet sqPO{"["};
  Alphabet sqPC{"]"};

  bool runa = autom.run({pO, pO, pC, pC, sqPO, sqPC});

  cout << "run grammar: " << runa << endl;

  return 0;
}