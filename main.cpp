#include <iostream>
#include <lexer.h>
#include <vector>
#include <iomanip>
// #include <Convert/grammarToAutomaton.h>
#include <Grammar/grammar.h>
#include <Grammar/grammarDerivation.h>

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

// void testAutomaton()
// {
//   State q0("q0");
//   State q1("q1");
//   State q2("q2");

//   Alphabet a("a");
//   Alphabet b("b");
//   Alphabet c("c");

//   Alphabet Z0("Z0");
//   Alphabet A("A");
//   Alphabet B("B");
//   Alphabet S("S");

//   vector<Transition> transitions(
//       {
//           {q0, q0, a, Z0, {a, Z0}},
//           {q0, q0, a, a, {a, a}},
//           {q0, q1, _eps, a, {a}},
//           {q1, q1, b, a, {_eps}},
//           {q1, q2, _eps, Z0, {_eps}},
//       });

//   AWord w{a, a, b, b};
//   AutomatonPD aut(
//       {q0, q1, q2},
//       {a, b, c},
//       {Z0, A, B, S},
//       transitions,
//       q0,
//       Z0,
//       {q2});

//   bool r = aut.run(w);
//   cout << r << endl;
// }

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

void testCLang()
{
  char *token_if = "if";
  char *token_else = "else";
  char *token_while = "while";
  char *token_for = "for";
  char *token_return = "return";
  char *token_break = "break";
  char *token_continue = "continue";
  char *token_true = "true";
  char *token_false = "false";
  char *token_void = "void";
  char *token_int = "int";
  char *token_float = "float";
  char *token_bool = "bool";
  char *token_char = "char";
  char *token_name = "name";
  char *token_number = "number";
  char *token_numberF = "numberF";
  char *token_plusplus = "plusplus";
  char *token_minusminus = "minusminus";
  char *token_sum = "sum";
  char *token_sub = "sub";
  char *token_mult = "mult";
  char *token_div = "div";
  char *token_mod = "mod";
  char *token_assign = "assign";
  char *token_greater = "greater";
  char *token_lower = "lower";
  char *token_greaterE = "greaterE";
  char *token_lowerE = "lowerE";
  char *token_equals = "equals";
  char *token_notEquals = "notEquals";
  char *token_and = "and";
  char *token_or = "or";
  char *token_not = "not";
  char *token_parO = "parO";
  char *token_parC = "parC";
  char *token_brO = "brO";
  char *token_brC = "brC";
  char *token_sqBrO = "sqBrO";
  char *token_sqBrC = "sqBrC";
  char *token_semiColon = "semi";
  char *token_comma = "comma";
  char *token_dot = "dot";
  char *token_colon = "colon";
  char *token_percent = "percent";
  char *token_slash = "slash";
  char *token_space = "space";

  Lexer lexer;
  if (true) // lexer.addRule
  {
    LexerCharN lrVoid({{'v'}, {'o'}, {'i'}, {'d'}});
    LexerCharN lrInt({{'i'}, {'n'}, {'t'}});
    LexerCharN lrFloat({{'f'}, {'l'}, {'o'}, {'a'}, {'t'}});
    LexerCharN lrBool({{'b'}, {'o'}, {'o'}, {'l'}});
    LexerCharN lrChar({{'c'}, {'h'}, {'a'}, {'r'}});

    LexerChar name_C('a', 'z');
    name_C.add('A', 'Z');
    LexerCharN lrName({name_C}, LEXER_CHAR_PLUS);

    LexerChar number_C('0', '9');
    LexerCharN lrNumber({number_C}, LEXER_CHAR_PLUS);

    LexerCharN numberF_L({number_C}, LEXER_CHAR_CLAIN);
    LexerCharN lrNumberF({number_C, {'.'}, numberF_L}, LEXER_CHAR_PLUS);

    LexerCharN lrPlusplus({LexerChar('+'), LexerChar('+')});
    LexerCharN lrMinusminus({LexerChar('-'), LexerChar('-')});
    LexerCharN lrSum(LexerChar('+'));
    LexerCharN lrSub(LexerChar('-'));
    LexerCharN lrMult(LexerChar('*'));
    LexerCharN lrDiv(LexerChar('/'));
    LexerCharN lrMod(LexerChar('%'));
    LexerCharN lrAssign(LexerChar('='));
    LexerCharN lrGreater(LexerChar('>'));
    LexerCharN lrLower(LexerChar('<'));
    LexerCharN lrGreaterE({LexerChar('>'), LexerChar('=')});
    LexerCharN lrLowerE({LexerChar('<'), LexerChar('=')});
    LexerCharN lrEquals({LexerChar('='), LexerChar('=')});
    LexerCharN lrNotEquals({LexerChar('!'), LexerChar('=')});
    LexerCharN lrAnd({LexerChar('&'), LexerChar('&')});
    LexerCharN lrOr({LexerChar('|'), LexerChar('|')});
    LexerCharN lrNot(LexerChar('!'));
    LexerCharN lrParO(LexerChar('('));
    LexerCharN lrParC(LexerChar(')'));
    LexerCharN lrBrO(LexerChar('{'));
    LexerCharN lrBrC(LexerChar('}'));
    LexerCharN lrSqBrO(LexerChar('['));
    LexerCharN lrSqBrC(LexerChar(']'));
    LexerCharN lrSemiColon(LexerChar(';'));
    LexerCharN lrComma(LexerChar(','));
    LexerCharN lrDot(LexerChar('.'));
    LexerCharN lrColon(LexerChar(':'));
    LexerCharN lrPercent(LexerChar('%'));
    LexerCharN lrSlash(LexerChar('/'));
    LexerCharN lrSpace(LexerChar(' '));

    LexerCharN lrIf(vector<LexerCharN>{{'i'}, {'f'}});
    LexerCharN lrElse({{'e'}, {'l'}, {'s'}, {'e'}});
    LexerCharN lrWhile({{'w'}, {'h'}, {'i'}, {'l'}, {'e'}});
    LexerCharN lrFor({{'f'}, {'o'}, {'r'}});
    LexerCharN lrReturn({{'r'}, {'e'}, {'t'}, {'u'}, {'r'}, {'n'}});
    LexerCharN lrBreak({{'b'}, {'r'}, {'e'}, {'a'}, {'k'}});
    LexerCharN lrContinue({{'c'}, {'o'}, {'n'}, {'t'}, {'i'}, {'n'}, {'u'}, {'e'}});
    LexerCharN lrTrue({{'t'}, {'r'}, {'u'}, {'e'}});
    LexerCharN lrFalse({{'f'}, {'a'}, {'l'}, {'s'}, {'e'}});

    lexer.addRule(lrIf, token_if);
    lexer.addRule(lrElse, token_else);
    lexer.addRule(lrWhile, token_while);
    lexer.addRule(lrFor, token_for);
    lexer.addRule(lrReturn, token_return);
    lexer.addRule(lrBreak, token_break);
    lexer.addRule(lrContinue, token_continue);
    lexer.addRule(lrTrue, token_true);
    lexer.addRule(lrFalse, token_false);
    lexer.addRule(lrVoid, token_void);
    lexer.addRule(lrInt, token_int);
    lexer.addRule(lrFloat, token_float);
    lexer.addRule(lrBool, token_bool);
    lexer.addRule(lrChar, token_char);
    lexer.addRule(lrName, token_name);
    lexer.addRule(lrNumber, token_number);
    lexer.addRule(lrNumberF, token_numberF);

    lexer.addRule(lrPlusplus, token_plusplus);
    lexer.addRule(lrMinusminus, token_minusminus);
    lexer.addRule(lrSum, token_sum);
    lexer.addRule(lrSub, token_sub);
    lexer.addRule(lrMult, token_mult);
    lexer.addRule(lrDiv, token_div);
    lexer.addRule(lrMod, token_mod);
    lexer.addRule(lrAssign, token_assign);
    lexer.addRule(lrGreater, token_greater);
    lexer.addRule(lrLower, token_lower);
    lexer.addRule(lrGreaterE, token_greaterE);
    lexer.addRule(lrLowerE, token_lowerE);
    lexer.addRule(lrEquals, token_equals);
    lexer.addRule(lrNotEquals, token_notEquals);
    lexer.addRule(lrAnd, token_and);
    lexer.addRule(lrOr, token_or);
    lexer.addRule(lrNot, token_not);
    lexer.addRule(lrParO, token_parO);
    lexer.addRule(lrParC, token_parC);
    lexer.addRule(lrBrO, token_brO);
    lexer.addRule(lrBrC, token_brC);
    lexer.addRule(lrSqBrO, token_sqBrO);
    lexer.addRule(lrSqBrC, token_sqBrC);
    lexer.addRule(lrSemiColon, token_semiColon);
    lexer.addRule(lrComma, token_comma);
    lexer.addRule(lrDot, token_dot);
    lexer.addRule(lrColon, token_colon);
    lexer.addRule(lrPercent, token_percent);
    lexer.addRule(lrSlash, token_slash);
    lexer.addRule(lrSpace, token_space);
  }

  {
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
    vector<Token> tokens = lexer.lex(text);
  }

  Grammar grammar;
  // terminal symbols
  Symbol if_s("if");
  Symbol else_s("else");
  Symbol while_s("while");
  Symbol for_s("for");
  Symbol return_s("return");
  Symbol break_s("break");
  Symbol continue_s("continue");
  Symbol true_s("true");
  Symbol false_s("false");
  Symbol void_s("void");
  Symbol int_s("int");
  Symbol float_s("float");
  Symbol bool_s("bool");
  Symbol char_s("char");
  Symbol name_s("name");
  Symbol number_s("number");
  Symbol numberF_s("numberF");
  Symbol plusplus_s("plusplus");
  Symbol minusminus_s("minusminus");
  Symbol sum_s("sum");
  Symbol sub_s("sub");
  Symbol mult_s("mult");
  Symbol div_s("div");
  Symbol mod_s("mod");
  Symbol assign_s("assign");
  Symbol greater_s("greater");
  Symbol lower_s("lower");
  Symbol greaterE_s("greaterE");
  Symbol lowerE_s("lowerE");
  Symbol equals_s("equals");
  Symbol notEquals_s("notEquals");
  Symbol and_s("and");
  Symbol or_s("or");
  Symbol not_s("not");
  Symbol parO_s("parO");
  Symbol parC_s("parC");
  Symbol brO_s("brO");
  Symbol brC_s("brC");
  Symbol sqBrO_s("sqBrO");
  Symbol sqBrC_s("sqBrC");
  Symbol semiColon_s("semi");
  Symbol comma_s("comma");
  Symbol dot_s("dot");
  Symbol colon_s("colon");
  Symbol percent_s("percent");
  Symbol slash_s("slash");
  Symbol space_s("space");

  Symbol Identifier_s("identifier");
  Symbol Type_s("type");
  Symbol FuncArgs_s("funcArgs");

  Symbol HeaderArgs_s("headerArgs");
  Symbol Header_s("header");
  Symbol Root_s("Root");
  Symbol StmtList_s("StmtList");
  Symbol Stmt_s("Stmt");
  Symbol ExprStmt_s("ExprStmt");
  Symbol DeclStmt_s("DeclStmt");
  Symbol AssignStmt_s("AssignStmt");
  Symbol RetStmt_s("RetStmt");
  Symbol IfStmt_s("IfStmt");
  Symbol WhileStmt_s("WhileStmt");
  Symbol ForStmt_s("ForStmt");
  Symbol FuncCall_s("FuncCall");
  Symbol FuncCallArgs_s("FuncCallArgs");
  Symbol FuncCallArg_s("FuncCallArg");
  Symbol Expr_s("Expr");
  Symbol ExprN_s("ExprN");
  Symbol ExprB_s("ExprB");
  Symbol ExprN0_s("ExprN0");
  Symbol ExprN1_s("ExprN1");
  Symbol ExprB1_s("ExprB1");
  Symbol ExprB2_s("ExprB2");
  Symbol ExprB3_s("ExprB3");
  Symbol ExprB4_s("ExprB4");
  Symbol NameNum1_s("NameNum1");
  Symbol NameNum_s("NameNum2");

  // identifier -> name
  grammar.addRule({Identifier_s, {name_s}});
  // identifier -> name[ExprN]
  grammar.addRule({Identifier_s, {name_s, sqBrO_s, Expr_s, sqBrC_s}});

  // type -> int | float | bool | char | void
  grammar.addRule({Type_s, {int_s}});
  grammar.addRule({Type_s, {float_s}});
  grammar.addRule({Type_s, {bool_s}});
  grammar.addRule({Type_s, {char_s}});
  grammar.addRule({Type_s, {void_s}});

  // funcArgs -> __epsilon__
  grammar.addRule({FuncArgs_s, {gEps}});
  // funcArgs -> Expr
  grammar.addRule({FuncArgs_s, {Expr_s}});
  // funcArgs -> Expr, funcArgs
  grammar.addRule({FuncArgs_s, {Expr_s, comma_s, FuncArgs_s}});

  // funcCall -> name(funcArgs)
  grammar.addRule({FuncArgs_s, {name_s, parO_s, FuncArgs_s, parC_s}});

  // headerArgs -> __epsilon__
  grammar.addRule({HeaderArgs_s, {gEps}});
  // headerArgs -> type name
  grammar.addRule({HeaderArgs_s, {Type_s, name_s}});
  // headerArgs -> type name, headerArgs
  grammar.addRule({HeaderArgs_s, {Type_s, name_s, comma_s, HeaderArgs_s}});

  // header -> < Args >
  grammar.addRule({Header_s, {lower_s, HeaderArgs_s, greater_s}});

  // Root -> header { StmtList }
  grammar.addRule({Root_s, {brO_s, StmtList_s, brC_s}});

  // StmtList -> Stmt
  grammar.addRule({StmtList_s, {Stmt_s}});
  // StmtList -> Stmt StmtList
  grammar.addRule({StmtList_s, {Stmt_s, StmtList_s}});

  // Stmt -> ExprStmt
  grammar.addRule({Stmt_s, {ExprStmt_s}});
  // Stmt -> DeclStmt
  grammar.addRule({Stmt_s, {DeclStmt_s}});
  // Stmt -> AssignStmt
  grammar.addRule({Stmt_s, {AssignStmt_s}});
  // Stmt -> RetStmt
  grammar.addRule({Stmt_s, {RetStmt_s}});
  // Stmt -> IfStmt
  grammar.addRule({Stmt_s, {IfStmt_s}});
  // Stmt -> WhileStmt
  grammar.addRule({Stmt_s, {WhileStmt_s}});
  // Stmt -> ForStmt
  grammar.addRule({Stmt_s, {ForStmt_s}});
  // Stmt -> { StmtList }
  grammar.addRule({Stmt_s, {brO_s, StmtList_s, brC_s}});

  // ExprStmt -> Expr
  grammar.addRule({ExprStmt_s, {Expr_s}});
  // DeclStmt -> type name = Expr;
  grammar.addRule({DeclStmt_s, {Type_s, name_s, assign_s, Expr_s, semiColon_s}});
  // DeclStmt -> type name;
  grammar.addRule({DeclStmt_s, {Type_s, name_s, semiColon_s}});
  // AssignStmt -> identifier = Expr;
  grammar.addRule({AssignStmt_s, {Identifier_s, assign_s, semiColon_s}});
  // RetStmt -> return Expr;
  grammar.addRule({RetStmt_s, {return_s, Expr_s, semiColon_s}});
  // RetStmt -> return;
  grammar.addRule({RetStmt_s, {return_s, semiColon_s}});
  // IfStmt -> if(Expr) Stmt else Stmt
  grammar.addRule({IfStmt_s, {IfStmt_s, parO_s, Expr_s, parC_s, Stmt_s, else_s, Stmt_s}});
  // WhileStmt -> while(Expr) Stmt
  grammar.addRule({WhileStmt_s, {while_s, parO_s, Expr_s, parC_s, Stmt_s}});
  // ForStmt -> for(Expr; Expr; Expr) Stmt
  grammar.addRule({ForStmt_s, {for_s, parO_s, Expr_s, semiColon_s, Expr_s, semiColon_s, Expr_s, parC_s, Stmt_s}});

  // Expr -> ExprN
  grammar.addRule({Expr_s, {ExprN_s}});
  // Expr -> ExprB
  grammar.addRule({Expr_s, {ExprB_s}});

  // nameNum1 -> identifier++
  grammar.addRule({NameNum1_s, {Identifier_s, plusplus_s}});
  // nameNum1 -> identifier--
  grammar.addRule({NameNum1_s, {Identifier_s, minusminus_s}});
  // nameNum -> nameNum1
  grammar.addRule({NameNum_s, {NameNum1_s}});
  // nameNum -> ++nameNum1
  grammar.addRule({NameNum_s, {sub_s, sum_s, NameNum1_s}});
  // nameNum -> --nameNum1
  grammar.addRule({NameNum_s, {sub_s, sub_s, NameNum1_s}});
  // nameNum -> number
  grammar.addRule({NameNum_s, {number_s}});
  // nameNum -> numberF
  grammar.addRule({NameNum_s, {numberF_s}});

  // ExprN0 -> nameNum
  grammar.addRule({ExprN0_s, {ExprN_s}});
  // ExprN0 -> (ExprN)
  grammar.addRule({ExprN0_s, {parO_s, Expr_s, parC_s}});
  // ExprN0 -> FuncCall
  grammar.addRule({ExprN0_s, {FuncCall_s}});

  // ExprN1 -> ExprN0
  grammar.addRule({ExprN1_s, {ExprN0_s}});
  // ExprN1 -> ExprN0 * ExprN1
  grammar.addRule({ExprN1_s, {ExprN0_s, mult_s, ExprN1_s}});
  // ExprN1 -> ExprN0 / ExprN1
  grammar.addRule({ExprN1_s, {ExprN0_s, div_s, ExprN1_s}});
  // ExprN1 -> ExprN0 % ExprN1
  grammar.addRule({ExprN1_s, {ExprN0_s, mod_s, ExprN1_s}});
  // ExprN -> ExprN1
  grammar.addRule({ExprN_s, {ExprN1_s}});
  // ExprN1 + ExprN
  grammar.addRule({ExprN_s, {ExprN1_s, sum_s, ExprN_s}});
  // ExprN1 - ExprN
  grammar.addRule({ExprN_s, {ExprN1_s, sub_s, ExprN_s}});

  // ExprB1 -> ExprN
  grammar.addRule({ExprB1_s, {ExprN_s}});
  // ExprB1 -> ExprN > ExprB1
  grammar.addRule({ExprB2_s, {ExprN_s, lower_s, ExprB1_s}});
  // ExprB1 -> ExprN < ExprB1
  grammar.addRule({ExprB2_s, {ExprN_s, greater_s, ExprB1_s}});
  // ExprB1 -> ExprN >= ExprB1
  grammar.addRule({ExprB2_s, {ExprN_s, lowerE_s, ExprB1_s}});
  // ExprB1 -> ExprN <= ExprB1
  grammar.addRule({ExprB2_s, {ExprN_s, greaterE_s, ExprB1_s}});

  // ExprB2 -> ExprB1
  grammar.addRule({ExprB2_s, {ExprB1_s}});
  // ExprB2 -> !ExprB1
  grammar.addRule({ExprB2_s, {not_s, ExprB1_s}});
  // ExprB2 -> true
  grammar.addRule({ExprB2_s, {true_s}});
  // ExprB2 -> false
  grammar.addRule({ExprB2_s, {false_s}});
  // ExprB2 -> ExprB1 == ExprB2
  grammar.addRule({ExprB2_s, {ExprB1_s, equals_s, ExprB2_s}});
  // ExprB2 -> ExprB1 != ExprB2
  grammar.addRule({ExprB2_s, {ExprB1_s, notEquals_s, ExprB2_s}});

  // ExprB -> ExprB2
  grammar.addRule({ExprB_s, {ExprB2_s}});
  // ExprB -> ExprB2 && ExprB
  grammar.addRule({ExprB_s, {ExprB2_s, and_s, ExprB_s}});
  // ExprB -> ExprB2 || ExprB
  grammar.addRule({ExprB_s, {ExprB2_s, or_s, ExprB_s}});
}

int main()
{

  Lexer lexer;
  if(false)
  {
    Symbol parenO("(");
    Symbol parenC(")");
    Symbol sqParO("[");
    Symbol sqParC("]");
    Symbol S("S");

    Grammar grammar;
    grammar.addTerminal(parenO);
    grammar.addTerminal(parenC);
    grammar.addTerminal(sqParO);
    grammar.addTerminal(sqParC);
    grammar.addNoTerminal(S);

    grammar.addRule({S, {parenO, S, parenC}});
    grammar.addRule({S, {sqParO, S, sqParC}});
    grammar.addRule({S, {S, S}});
    grammar.addRule({S, {gEps}});

    grammar.setStart(S);

    bool der = derive(grammar, {parenO, S, parenC, sqParO, S, sqParC});
    cout << "derivation: " << der << endl;
  }
  
  if(true)
  {
    Symbol a("a");
    Symbol b("b");
    Symbol c("c");
    Symbol _s("-");

    Symbol S("S");
    Symbol A("A");
    Symbol B("B");
    Symbol C("C");

    Grammar grammar;
    grammar.addTerminal(a);
    grammar.addTerminal(b);
    grammar.addTerminal(c);
    grammar.addTerminal(_s);
    grammar.addNoTerminal(S);
    grammar.addNoTerminal(A);
    grammar.addNoTerminal(B);
    grammar.addNoTerminal(C);

    grammar.addRule({S, {A, _s, C}});
    grammar.addRule({A, {a, B, b, c}});
    grammar.addRule({B, {b}});
    grammar.addRule({B, {b, B}});
    grammar.addRule({C, {a}});
    grammar.addRule({C, {a, C}});

    grammar.setStart(S);

    bool der = derive(grammar, {a, b, b, b, c, _s, a, a});
    cout << "derivation: " << der << endl;
  }
  
  // AutomatonPD autom = grammarToAutomaton(grammar);
  // Alphabet pO{"("};
  // Alphabet pC{")"};
  // Alphabet sqPO{"["};
  // Alphabet sqPC{"]"};

  // bool runa = autom.run({pO, pO, pC, pC, sqPO, sqPC});

  // cout << "run grammar: " << runa << endl;

  return 0;
}