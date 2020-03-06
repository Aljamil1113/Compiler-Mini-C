/**

   ICST252 ASMGEN
   global.h
   Purpose: Centralizes all definitions and #include declarations
  
   @author  Louie Pascual
   @subauthors  Al Arazas, Dinnex Valeros
   @version 2.0 3/26/2016

   Honor code: We have not received any unauthorized help
               in completing this work.

      Al Arazas, Louie Pascual, Dinnex Valeros

*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <map>
#include <iomanip>
using namespace std;

enum {STR, ID, NUM, FLT,
      ADD, MUL, SUB, DIV, MOD,
      COM, SC, LCB, RCB, LP, RP, LSB, RSB,
      LEQ, LTN, GEQ, GTN, EQ, ASSIGN, NEQ,
      ERR, EOI,
      VOID, INT, FLOAT, IF, ELSE, WHILE, RETURN};

// Scanner Functions
struct Token {
  int value;
  string lexeme;
  int row, col;
  string name;

  Token (int v, string l, int r, int c, string n) {
    value = v;
    lexeme = l;
    row = r;
    col = c;
    name = n;
  }
  Token() {

  }

};

struct SymTable {
  string name;
  int id;
};


struct TAC {
  string op, a, b, c;
  void set(string _op, string _a, string _b, string _c) {
    op = _op;
    a = _a;
    b = _b;
    c = _c;
  }

  TAC () {
    set("","","","");
  }

  void print() {
    if(op == "add")
      cout << c << " := " << a << " + " << b;
    
    if(op == "sub")
      cout << c << " := " << a << " - " << b;

    if(op == "mul")
      cout << c << " := " << a << " * " << b;

    if(op == "div")
      cout << c << " := " << a << " / " << b;

    if(op == "mod")
      cout << c << " := " << a << " % " << b;

    if(op == "eq")
      cout << c << " := " << a << " == " << b;

    if(op == "neq")
      cout << c << " := " << a << " != " << b;

    if(op == "lte")
      cout << c << " := " << a << " <= " << b;

    if(op == "gte")
      cout << c << " := " << a << " >= " << b;

    if(op == "lt")
      cout << c << " := " << a << " < " << b;

    if(op == "gt")
      cout << c << " := " << a << " > " << b;

    if(op == "assign")
      cout << c << " := " << a;

    if(op == "um")
      cout << c << " := " << " - " << a;

    if(op == "getAEV")
      cout << c << " := " << a << " [ " << b << " ] ";

    if(op == "setAEV")
      cout << a << " [ " << b << " ]" << " := " << c;

    if(op == "ifFalse")
      cout << "if " << a << " is false goto " << b;

    if(op == "ifTrue")
      cout << "if " << a << " is true goto " << b;

    if(op == "goto")
      cout << "goto " << b;

    if(op == "call")
      cout << c << " := " << "call " << a << " " << b;

    if(op == "param")
      cout << "param " << a;

    if(op == "copyAdd")
      cout << c << " := " << "& " << a;

    if(op == "getPV")
      cout << c << " := " << "* " << a;

    if(op == "setPV")
      cout << "* " << a << " := " << a;

    if(op == "return")
      cout << "return " << a;
    
  }
};

// Assembly Generator Functions
string genAsmCode(string command, string ls, string rs);
void genTargetCode(string);


// Translator Functions
void showCode();
void generate_code();
string i_to_s(int x);

// Parser Functions
void parse();
void match(int);
bool search(int);
void sync(int*);
void program();
void decl();
void typeSpec();
void declRest();
void params();
void paramsList();
void param();
void compStmt();
void locDecls();
void varDecl();
void stmtList();
void stmt();
void procStmt();
void procRest();
void selStmt();
void iterStmt();
void retStmt();
void var();
void expr();
void relOp();
void addExpr();
void addOp();
void term();
void mulOp();
void factor();
void idRest();
void args();
void argList();

// Scanner Functions
Token scan(ifstream &in);
