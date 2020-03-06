/**

  ICST252 Parser, Translator,  Assembly Code Generator
  parse.cpp
  Purpose: Implements a syntax and semantic analyzer

  @authors  Louie Pascual, John Dinnex Valeros, Al Jamil Arazas
  @version 2.0 3/28/2016

  Honor Code:  We have not received any unauthorized
               help in completing this work.

              Louie Pascual, John Dinnex Valeros, Al Jamil arazas

*/

#include "global.h"

Token lookahead; // current token read

extern ifstream in;
extern int errorCount;
#define MAXCODE 10000
typedef vector<string> vs;

TAC code[MAXCODE];
int codeSize = 0;

stack<string> PS;
map<string,int> label;

struct funcData {
  string funcName;
  int lineNumber;
  bool isVar;
  vector<string> listParams;
  vector<string> listDecls;
  map<string,string> equ;
};

map<string,funcData> func;
string currentFunc;
bool enableInput = false;
bool enableOutput = false;


/**

  Generates the IA32 Assembly Code of the given program

  @param name of output file
  @return none

*/
void genTargetCode(string ofilename) {
  /*
  some issues:
  1. global variables
  2. bug in array creation
  3. no support in floating numbers
  4. no support in ouputting string literals
  */

  // redirect cout to output in ofilename
  freopen(ofilename.c_str(),"w",stdout);


  // setup global variables, if any
  if(func.find("main") == func.end()) {
    cout << "error: main function not found\n";
  }
  else {
    for(map<string,funcData>::iterator it=func.begin(); it != func.end(); it++) {
      if(it->first == "main") {
        cout << genAsmCode(".globl","_main","");
      }
      else {
        cout << genAsmCode(".globl",it->first,"");
      }
    }
  }

  // setup input function, if enabled
  if(enableInput) {
    cout << "input: \n";
    cout << genAsmCode("pushl","%ebp","");
    cout << genAsmCode("movl","%esp","%ebp");
    cout << endl;
    cout << genAsmCode("subl","$8","%esp");
    cout << genAsmCode("movl","%eax","4(%esp)");
    cout << genAsmCode("leal","fmt.int","%eax");
    cout << genAsmCode("movl","%eax","(%esp)");
    cout << genAsmCode("calll","_scanf","");
    cout << genAsmCode("addl","$8","%esp");
    cout << endl;
    cout << genAsmCode("popl","%ebp","");
    cout << genAsmCode("retl","","");
  
    cout << "fmt.int: \n";
    cout << genAsmCode(".asciz","\"%d\"","");
  }

  // setup output function, if enabled
  if(enableOutput) {
    cout << "output: \n";
    cout << genAsmCode("pushl","%ebp","");
    cout << genAsmCode("movl","%esp","%ebp");
    cout << endl;
    cout << genAsmCode("subl","$8","%esp");
    cout << genAsmCode("movl","%eax","4(%esp)");
    cout << genAsmCode("leal","fmt.intnl","%eax");
    cout << genAsmCode("movl","%eax","(%esp)");
    cout << genAsmCode("calll","_printf","");
    cout << genAsmCode("addl","$8","%esp");
    cout << endl;
    cout << genAsmCode("popl","%ebp","");
    cout << genAsmCode("retl","","");
  
    cout << "fmt.intnl: \n";
    cout << genAsmCode(".asciz","\"%d\\n\"","");
  }


  bool startedFunc = false;
  string usingFunc;
  for(int i=0; i<=codeSize; i++) {
    int locDeclSize;
    int stackAlignSize;

    // Outputs any label (L1,L2,etc) in the TAC
    for(map<string,int>::iterator it=label.begin(); it != label.end(); it++) {
      if(it->second == i) {
          cout << it->first << ":" << endl;
      }
    }

    // Outputs any function in the TAC and its contents
    for(map<string,funcData>::iterator it=func.begin(); it != func.end(); it++) {
      if((it->second).lineNumber == i) {
          // outputs LEAVE in function if a function has ended
          if(startedFunc) {
            string n_params = "$" + i_to_s(func[usingFunc].listParams.size()*4);
            cout << genAsmCode("addl","$" + i_to_s(stackAlignSize), "%esp");
            cout << genAsmCode("popl","%ebp","");
            cout << genAsmCode("retl",n_params,"");
          }

          
          // check if it is a global variable
          if((it->second).isVar) {
            continue;
          }

          // output function name
          string funcName = it->first;
          if(funcName == "main"){
            cout << "_" << funcName << ":" << endl;
          }
          else {
            cout << funcName << ":" << endl;
          }
          usingFunc = funcName;

          // set startedFunc if a function has started
          startedFunc = true;

          // initializes an activation record
          cout << genAsmCode("pushl","%ebp","");
          cout << genAsmCode("movl","%esp","%ebp") << endl;

          // assign a .equ to parameters
          int d = 8; // default memory position
          string paramName;
          for(int i=0; i<(it->second).listParams.size(); i++) {
            paramName = (it->second).listParams[i];
            it->second.equ[paramName] = funcName + "." + paramName + "(%ebp)";
            cout << genAsmCode(".equ",it->second.equ[paramName],i_to_s(d));
            d += 4;
          }

          // assign a .equ to local decls
          d = -4; // default memory position
          string declName;
          for(int i=0; i<(it->second).listDecls.size(); i++) {
            declName = (it->second).listDecls[i];
            it->second.equ[declName] = funcName + "." + declName + "(%ebp)";
            cout << genAsmCode(".equ",it->second.equ[declName],i_to_s(d));
            d -= 4;
          }

          // subtract %esp for local variables
          locDeclSize = (it->second).listDecls.size();
          locDeclSize *= 4;
          // 8 bytes for return address and old ebp,
          // locDeclSize for number of locVars * 4,
          // locDeclSize%16 to get remaining bytes to align stack

          stackAlignSize = locDeclSize + (abs(16-(locDeclSize%16))) - 8;

          //locDeclSize
          if(locDeclSize > 0)
            cout << genAsmCode("subl","$" + i_to_s(stackAlignSize), "%esp");

      }
    }

    // exit when TAC conversion is complete
    if(i == codeSize) {
      cout << genAsmCode("addl","$" + i_to_s(stackAlignSize), "%esp");
      cout << genAsmCode("popl","%ebp","");
      cout << genAsmCode("retl","","");
      return;
    }
      

    // prepare value for output
    string codeA = func[usingFunc].equ[code[i].a];
    string codeB = func[usingFunc].equ[code[i].b];
    string codeC = func[usingFunc].equ[code[i].c];
    if(codeA == "")
      codeA = code[i].a;
    if(codeB == "")
      codeB = code[i].b;
    if(codeC == "")
      codeC = code[i].c;
    
    if(isdigit(codeA[0]))
      codeA = "$" + codeA;
    if(isdigit(codeB[0]))
      codeB = "$" + codeB;
    if(isdigit(codeC[0]))
      codeC = "$" + codeC;
    
    cout << endl; // code separator

    if(code[i].op == "add") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("addl",codeB,"%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "sub") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("subl",codeB,"%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "mul") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("imul",codeB,"%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }
    
    if(code[i].op == "div") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("movl",codeB,"%ebx");
      cout << genAsmCode("sarl","$31","%edx");
      cout << genAsmCode("idivl","%ebx","");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "mod") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("movl",codeB,"%ebx");
      cout << genAsmCode("sarl","$31","%edx");
      cout << genAsmCode("idivl","%ebx","");
      cout << genAsmCode("movl","%edx",codeC);
    }

    if(code[i].op == "eq") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl",codeB,"%eax");
      cout << genAsmCode("sete","%cl","");
      cout << genAsmCode("andb","$1","%cl");
      cout << genAsmCode("movzbl","%cl","%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "neq") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl",codeB,"%eax");
      cout << genAsmCode("setne","%cl","");
      cout << genAsmCode("andb","$1","%cl");
      cout << genAsmCode("movzbl","%cl","%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "lte") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl",codeB,"%eax");
      cout << genAsmCode("setle","%cl","");
      cout << genAsmCode("andb","$1","%cl");
      cout << genAsmCode("movzbl","%cl","%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "gte") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl",codeB,"%eax");
      cout << genAsmCode("setge","%cl","");
      cout << genAsmCode("andb","$1","%cl");
      cout << genAsmCode("movzbl","%cl","%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "lt") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl",codeB,"%eax");
      cout << genAsmCode("setl","%cl","");
      cout << genAsmCode("andb","$1","%cl");
      cout << genAsmCode("movzbl","%cl","%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "gt") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl",codeB,"%eax");
      cout << genAsmCode("setg","%cl","");
      cout << genAsmCode("andb","$1","%cl");
      cout << genAsmCode("movzbl","%cl","%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "assign") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "um") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("negl","%eax","");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "ifFalse") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl","$0","%eax");
      cout << genAsmCode("je",codeB,""); 
    }

    if(code[i].op == "ifTrue") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("cmpl","$1","%eax");
      cout << genAsmCode("je",codeA,""); 
    }

    if(code[i].op == "goto") {
      cout << genAsmCode("jmp",codeB,"");
    }

    if(code[i].op == "call") {
      if(codeA == "input") {
        cout << genAsmCode("leal",codeC,"%eax");
        cout << genAsmCode("calll",codeA,"");
      }
      else if(codeA == "output") {
        cout << genAsmCode("popl","%eax","");
        cout << genAsmCode("calll",codeA,"");
        cout << genAsmCode("movl","%eax",codeC);
      }
      else {
        cout << genAsmCode("calll",codeA,"");
        cout << genAsmCode("movl","%eax",codeC);
      }
      
    }

    if(code[i].op == "param") {
      cout << genAsmCode("movl",codeA,"%eax");
      cout << genAsmCode("pushl","%eax","");
    }

    if(code[i].op == "getAEV") {
      string temp = currentFunc + "." + codeA + ".A" + codeB.substr(1,codeB.length()-1) + "(%ebp)";
      cout << genAsmCode("movl",temp,"%eax");
      cout << genAsmCode("movl","%eax",codeC);
    }

    if(code[i].op == "setAEV") {
      string temp = currentFunc + "." + codeA + ".A" + codeB.substr(1,codeB.length()-1) + "(%ebp)";
      cout << genAsmCode("movl",codeC,"%eax");
      cout << genAsmCode("movl","%eax",temp);
    }

    if(code[i].op == "return") {
      cout << genAsmCode("movl",codeA,"%eax");
    }


  }

}

/**
  Generates the equivalent assembly code block
  of a given Three-Address Code (TAC)
  
  @param 
    command - string representation of an assembly instruction
    ls - left side value of an asm code line
    rs - right side value of an asm code line

  @return 
    string - equivalent assembly code (formatted)
*/
string genAsmCode(string command, string ls, string rs) {
  string temp;
  if(rs != "") {
    temp = "\t" + command + "\t" + ls + ", " + rs + "\n";
  }
  else {
    temp = "\t" + command + "\t" + ls + "\n";
  }
  return temp;
}


/**

  Generates the TAC of a given statement

  @param op, a, b ,c
  @return none

*/
void genCode(string op, string a, string b, string c) {
  if (codeSize < MAXCODE)
    code[codeSize++].set(op, a, b, c);
  else {
    cout << "error: code space is depleted" << endl;
  } 
}

/**

  Shows the TAC of a given program

  @param none
  @return none

*/

/* DISABLED--
    Enable this only for debugging purposes
void showCode() {
  for(int i=0; i<=codeSize; i++) {
    
    for(map<string,int>::iterator it=label.begin(); it != label.end(); it++) {
      if(it->second == i) {
          cout << "----|" << it->first << ":" << endl;
      }
    }

    for(map<string,funcData>::iterator it=func.begin(); it != func.end(); it++) {
      if((it->second).lineNumber == i) {
          cout << "----|" << it->first << ":" << endl;
      }
    }

    if(i == codeSize)
      return;

    printf("%04d|\t", i);
    

    code[i].print();
    if(code[i].op == "goto" ||
        code[i].op == "ifFalse" ||
        code[i].op == "ifTrue") {
      cout << " {=" << setfill('0') << setw(4) << label[code[i].b] << "}";
    }
    
    cout << endl;
  }
}
*/

/**

  Creates a new temporary variable

  @param none
  @return name of new temporary variable

*/
string newTemp() {
  static int c = 0;
  char a[256];
  sprintf(a, "t.%d", ++c);

  // add new temp in current function
  func[currentFunc].listDecls.push_back(string(a));

  return string(a);
}

/**

  Creates a new label

  @param none
  @return name of the new label

*/
string newLabel() {
  static int t = 0;
  char a[256];
  sprintf(a, "L.%d", ++t);
  return string(a);
}

/**

  Converts an integer to a string

  @param int number
  @return string equivalent

*/
string i_to_s(int x) {
  char a[256];
  sprintf(a,"%d",x);
  return string(a);
}

/**

  Searches for if Token exists in a First/Follow Set

  @param int array containing Tokens in a specified set
  @return bool, true if found, false if not

*/
bool search(int *s) {
  int i = 0;
  while (s[i] != -1) {
    if (lookahead.value == s[i]) {
      return true;
    }
    i++;
  }

  return false;
}

/**

  Synchronizes the lookahead value to make sure if
    follows specified grammar

  @param int array containing Tokens in a specified set
  @return none

*/
void sync(int set[]) {
  if(!search(set)) {
    errorCount++;
    if (lookahead.value == EOI) {
      cout << "error:" << lookahead.row << ":" << lookahead.col+1;
      cout << ": unexpected end of input" << endl;

      // Report Error Count if unexpected end of input
      cout << endl;
      if(errorCount == 1) {
        cout << errorCount << " error detected.\n"; 
      }
      else {
        cout << errorCount << " errors detected.\n";
      }
      exit(1);
    } 
    else {
      cout << "error:" << lookahead.row << ":" << lookahead.col;
      cout << ": unexpected '" << lookahead.lexeme << "'" << endl;
    }
    
    // PANIC MODE
    while(!search(set)) {
      lookahead = scan(in);
      
      if (lookahead.value == EOI) {
        if(!search(set)) {
          cout << "error:" << lookahead.row << ":" << lookahead.col+1;
          cout << ": unexpected end of input" << endl;

          errorCount++;
          // Report Error Count if unexpected end of input
          cout << endl;
          if(errorCount == 1) {
            cout << errorCount << " error detected.\n"; 
          }
          else {
            cout << errorCount << " errors detected.\n";
          }

          exit(1);
        }
        
      }
    }
  }
  
}

/**

  Matches a Token

  @param int, the token to match
  @return none

*/
void match(int toMatch) {
  //cout << "\t" << lookahead.name  << "\t";
  //cout << "[" << lookahead.lexeme << "]\n";
  
  if (lookahead.value == toMatch) {
    lookahead = scan(in);
  } 
}

/**

  Uses the argList production rule

  @param none
  @return none

*/
void argList() {
  int argListFirst[6] = {LP,ID,SUB,NUM,FLT,-1};
  int argListFollow[2] = {RP,-1};
  string t;
  int numParams = 0;
  
  sync(argListFirst);

  expr();

  t = PS.top(); PS.pop();
  genCode("param",t,"","");
  numParams++;


  while (lookahead.value == COM) {
    match(COM);
    expr();
    
    t = PS.top(); PS.pop();
    genCode("param",t,"","");
    numParams++;
  }

  PS.push(i_to_s(numParams));

  sync(argListFollow);
}

/**

  Uses the args production rule

  @param none
  @return none

*/
void args() {
  int argsFirst[6] = {LP,ID,SUB,NUM,FLT,-1}; //epsilon case
  int argsFollow[2] = {RP,-1};
 
  switch(lookahead.value) {
    case LP:
    case ID:
    case SUB:
    case NUM:
    case FLT:
      argList();
      break;
    case RP:
      PS.push("0");
      break;
  }
  
  sync(argsFollow);
}

/**

  Uses the idRest production rule

  @param none
  @return none

*/
void idRest() {
  int idRestFirst[3] = {LP,LSB,-1}; //epsilon case
  int idRestFollow[16] = {MUL,DIV,MOD,ADD,SUB,RSB,SC,COM,RP,LEQ,LTN,GTN,GEQ,NEQ,EQ,-1};
  string t, a, b, c, r;
  
  if (lookahead.value == LP) {
    match(LP);
    args();

    b = PS.top(); PS.pop();
    a = PS.top(); PS.pop();
    r = newTemp();
    genCode("call",a,b,r);
    PS.push(r);
    
    match(RP);
  }
  else if (lookahead.value == LSB) {
    match(LSB);
    expr();

    b = PS.top(); PS.pop();
    a = PS.top(); PS.pop();
    r = newTemp();
    genCode("getAEV",a,b,r);
    PS.push(r);

    match(RSB);
  }

  sync(idRestFollow);
}

/**

  Uses the factor production rule

  @param none
  @return none

*/
void factor() {
  int factorFirst[6] = {LP,ID,SUB,NUM,FLT,-1};
  int factorFollow[16] = {MUL,DIV,MOD,ADD,SUB,RSB,SC,COM,RP,LEQ,LTN,GTN,GEQ,NEQ,EQ,-1};
  string t, r;

  sync(factorFirst);

  switch(lookahead.value) {
    case LP:
      match(LP);
      expr();
      match(RP);
      break;
    case ID:
      PS.push(lookahead.lexeme);
      if(lookahead.lexeme == "input") {
        enableInput = true;
      }
      if(lookahead.lexeme == "output") {
        enableOutput = true;
      }
      match(ID);
      idRest();
      break;
    case SUB:
      match(SUB);
      factor();

      t = PS.top(); PS.pop();
      r = newTemp();
      genCode("um",t,"",r); // um = unary minus
      PS.push(r);

      break;
    case NUM:
      PS.push(lookahead.lexeme);
      match(NUM);
      break;
    case FLT:
      PS.push(lookahead.lexeme);
      match(FLT);
  }

  sync(factorFollow);
}

/**

  Uses the mulOp production rule

  @param none
  @return none

*/
void mulOp() {
  int mulOpFirst[4] = {MUL,DIV,MOD,-1};
  int mulOpFollow[6] = {LP,ID,SUB,NUM,FLT,-1};

  sync(mulOpFirst);

  switch(lookahead.value) {
    case MUL:
      PS.push("mul");
      match(MUL);
      break;
    case DIV:
      PS.push("div");
      match(DIV);
      break;
    case MOD:
      PS.push("mod");
      match(MOD);
  }

  sync(mulOpFollow);
}

/**

  Uses the term production rule

  @param none
  @return none

*/
void term() {
  int termFirst[6] = {LP,ID,SUB,NUM,FLT,-1};
  int termFollow[13] = {ADD,SUB,LEQ,LTN,GTN,GEQ,NEQ,EQ,RP,RSB,SC,COM,-1};
  string t, a, b, op, r;

  sync(termFirst);
  factor();

  while(lookahead.value == MUL ||
        lookahead.value == DIV ||
        lookahead.value == MOD) {
    mulOp();
    op = PS.top(); PS.pop();

    factor();
    b = PS.top(); PS.pop();
    a = PS.top(); PS.pop();

    r = newTemp();
    genCode(op, a, b, r);
    PS.push(r);

  }

  sync(termFollow);
}

/**

  Uses the addOp production rule

  @param none
  @return none

*/
void addOp() {
  int addOpFirst[3] = {ADD,SUB,-1};
  int addOpFollow[6] = {LP,ID,SUB,NUM,FLT,-1};

  sync(addOpFirst);

  if(lookahead.value == ADD) {
    PS.push("add");
    match(ADD);
  }
  else if(lookahead.value == SUB) {
    PS.push("sub");
    match(SUB);
  }

  sync(addOpFollow);
}

/**

  Uses the addExpr production rule

  @param none
  @return none

*/
void addExpr() {
  int addExprFirst[6] = {LP,ID,SUB,NUM,FLT,-1};
  int addExprFollow[11] = {RSB,SC,RP,LEQ,LTN,GTN,GEQ,NEQ,EQ,COM,-1};
  string t, a, b, op, r;

  sync(addExprFirst);

  term();

  while(lookahead.value == ADD || lookahead.value == SUB) {
    addOp();
    op = PS.top(); PS.pop();

    term();
    b = PS.top(); PS.pop();
    a = PS.top(); PS.pop();

    r = newTemp();
    genCode(op, a, b, r);
    PS.push(r);
  }

  sync(addExprFollow);
}

/**

  Uses the relOp production rule

  @param none
  @return none

*/
void relOp() {
  int relOpFirst[7] = {LEQ,GTN,LTN,GEQ,NEQ,EQ,-1};
  int relOpFollow[6] = {LP,ID,SUB,NUM,FLT,-1};

  sync(relOpFirst);

  switch(lookahead.value) {
    case LEQ:
      PS.push("lte");
      match(LEQ);
      break;
    case LTN:
      PS.push("lt");
      match(LTN);
      break;
    case GTN:
      PS.push("gt");
      match(GTN);
      break;
    case GEQ:
      PS.push("gte");
      match(GEQ);
      break; 
    case NEQ:
      PS.push("neq");
      match(NEQ);
      break;
    case EQ: //EQ
      PS.push("eq");
      match(EQ);
  }

  sync(relOpFollow);
}

/**

  Uses the expr production rule

  @param none
  @return none

*/
void expr() {
  int exprFirst[6] = {LP,ID,SUB,NUM,FLT,-1};
  int exprFollow[5] = {RSB,SC,RP,COM,-1};
  string a, b, c, r, op;

  sync(exprFirst);

  addExpr();
  
  switch(lookahead.value) {
    case LEQ:
    case LTN:
    case GTN:
    case GEQ: 
    case NEQ:
    case EQ: 
    {
      relOp();
      op = PS.top(); PS.pop();

      addExpr();
      b = PS.top(); PS.pop();
      a = PS.top(); PS.pop();
      r = newTemp();
      genCode(op, a, b, r);
      PS.push(r);

      break;
    }
  }

  
  sync(exprFollow);
}

/**

  Uses the var production rule

  @param none
  @return none

*/
void var() {
  //NOTE: var is not reachable using stated grammar
  match(ID);
  expr();
}

/**

  Uses the retStmt production rule

  @param none
  @return none

*/
void retStmt() {
  int retStmtFirst[2] = {RETURN,-1};
  int retStmtFollow[9] = {LCB,IF,WHILE,RETURN,ID,SC,RCB,ELSE,-1};
  string a, b, c, op, r;

  sync(retStmtFirst);

  match(RETURN);

  if (lookahead.value == SC) {
    genCode("return", "0", "", "");
    match(SC);    
  }
  else {
    expr();
    a = PS.top(); PS.pop();
    
    genCode("return",a,"","");
    match(SC);
  }

  sync(retStmtFollow);
}

/**

  Uses the iterStmt production rule

  @param none
  @return none

*/
void iterStmt() {
  int iterStmtFirst[2] = {WHILE,-1};
  int iterStmtFollow[9] = {LCB,IF,WHILE,RETURN,ID,SC,RCB,ELSE,-1};
  string L1, L2, t, a, b, c, r;

  sync(iterStmtFirst);

  L1 = newLabel();
  L2 = newLabel();

  match(WHILE);
  match(LP);
 
  label[L1] = codeSize;

  expr();
  match(RP);

  t = PS.top(); PS.pop();
  genCode("ifFalse",t,L2,"");
  
  stmt();

  genCode("goto","",L1,"");
  label[L2] = codeSize;

  sync(iterStmtFollow);
}

/**

  Uses the selStmt production rule

  @param none
  @return none

*/
void selStmt() {
  int selStmtFirst[2] = {IF,-1};
  int selStmtFollow[9] = {LCB,IF,WHILE,RETURN,ID,SC,RCB,ELSE,-1};
  string L1, L2, t, a, b, c, op, r;

  sync(selStmtFirst);

  L1 = newLabel();

  match(IF);
  match(LP);
  expr();
  match(RP);

  t = PS.top(); PS.pop();
  genCode("ifFalse",t,L1,"");

  stmt();

  if(lookahead.value == ELSE) {
    L2 = newLabel();
    genCode("goto","",L2,"");
    label[L1] = codeSize;

    match(ELSE);
    stmt();

    label[L2] = codeSize;
  }
  else {
    label[L1] = codeSize;
  }

  sync(selStmtFollow);
}

/**

  Uses the procRest production rule

  @param none
  @return none

*/
void procRest() {
  int procRestFirst[4] = {LSB,ASSIGN,LP,-1};
  int procRestFollow[9] = {LCB,IF,WHILE,RETURN,ID,SC,RCB,ELSE,-1};
  string a, b, c, r;
  
  sync(procRestFirst);

  switch(lookahead.value) {
    case LSB:
      match(LSB);
      expr();
      match(RSB);
      match(ASSIGN);
      expr();

      c = PS.top(); PS.pop();
      b = PS.top(); PS.pop();
      a = PS.top(); PS.pop();
      genCode("setAEV",a,b,c);
      PS.push(r);

      match(SC);
      break;
    case ASSIGN:
      match(ASSIGN);
      expr();

      a = PS.top(); PS.pop();
      c = PS.top(); PS.pop();
      genCode("assign",a,"",c);
      PS.push(r);

      match(SC);
      break;
    case LP:
      match(LP);
      args();

      b = PS.top(); PS.pop();
      a = PS.top(); PS.pop();
      r = newTemp();
      genCode("call",a,b,r);
      PS.push(r);

      match(RP);
      match(SC);
  }

  sync(procRestFollow);
}

/**

  Uses the procStmt production rule

  @param none
  @return none

*/
void procStmt() {
  int procStmtFirst[2] = {ID,-1};
  int procStmtFollow[9] = {LCB,IF,WHILE,RETURN,ID,SC,RCB,ELSE,-1};
  string t, c, a, op, r;

  sync(procStmtFirst);

  PS.push(lookahead.lexeme);
  match(ID);
  procRest();

  sync(procStmtFollow);
}

/**

  Uses the stmt production rule

  @param none
  @return none

*/
void stmt() {
  int stmtFirst[7] = {LCB,IF,WHILE,RETURN,ID,SC,-1};
  int stmtFollow[13] = {EOI,LCB,IF,WHILE,RETURN,ID,SC,RCB,ELSE,FLOAT,INT,VOID,-1};

  sync(stmtFirst);

  switch(lookahead.value) {
    case LCB:
      compStmt();
      break;
    case IF:
      selStmt();
      break;
    case WHILE:
      iterStmt();
      break;
    case RETURN:
      retStmt();
      break;
    case ID:
      if(lookahead.lexeme == "output") {
        enableOutput = true;
      } 
      procStmt();

      break;
    case SC:
      match(SC);
  }
 
  sync(stmtFollow);
}

/**

  Uses the stmtList production rule

  @param none
  @return none

*/
void stmtList() {
  int stmtListFirst[7] = {LCB,IF,WHILE,RETURN,ID,SC,-1};
  int stmtListFollow[2] = {RCB,-1};

  //sync(stmtListFirst);

  while(lookahead.value == LCB ||
        lookahead.value == IF ||
        lookahead.value == WHILE ||
        lookahead.value == RETURN ||
        lookahead.value == ID ||
        lookahead.value == SC) {
    stmt();
  }

  sync(stmtListFollow);
}

/**

  Uses the varDecl production rule

  @param none
  @return none

*/
void varDecl() {
  int varDeclFirst[4] = {FLOAT,INT,VOID,-1};
  int varDeclFollow[11] = {FLOAT,INT,VOID,LCB,IF,WHILE,RETURN,ID,SC,RCB,-1};

  sync(varDeclFirst);

  typeSpec();
  string varName = lookahead.lexeme; // temporarily store variable name
  //func[currentFunc].listDecls.push_back(lookahead.lexeme);
  match(ID);

  if (lookahead.value == SC) {
    match(SC);
    func[currentFunc].listDecls.push_back(varName);
  }
  else if(lookahead.value == LSB) {
    func[currentFunc].listDecls.push_back(varName + ".A0");
    match(LSB);
    
    string temp = lookahead.lexeme;
    match(NUM);

    char buffer[256];
    strcpy(buffer,temp.c_str());
    int sizeOfArray = atoi(buffer);
    
    for(int i=1; i<sizeOfArray; i++) {
      func[currentFunc].listDecls.push_back(varName + ".A" + i_to_s(i));
    }

    match(RSB);
    match(SC);
  }

  sync(varDeclFollow);
}

/**

  Uses the locDecls production rule

  @param none
  @return none

*/
void locDecls(){
  int locDeclsFirst[4] = {FLOAT,INT,VOID,-1};
  int locDeclsFollow[8] = {LCB,IF,WHILE,RETURN,ID,SC,RCB,-1};

  //sync(locDeclsFirst);

  while(lookahead.value == FLOAT ||
        lookahead.value == INT ||
        lookahead.value == VOID) {
    varDecl();

  }

  sync(locDeclsFollow);
}

/**

  Uses the compStmt production rule

  @param none
  @return none

*/
void compStmt() {
  int compStmtFirst[2] = {LCB,-1};
  int compStmtFollow[13] = {EOI,FLOAT,INT,VOID,LCB,IF,WHILE,RETURN,ID,SC,RCB,ELSE,-1};

  sync(compStmtFirst);

  match(LCB);
  locDecls();
  stmtList();
  match(RCB);

  sync(compStmtFollow);
}

/**

  Uses the param production rule

  @param none
  @return none

*/
void param() {
  int paramNodeFirst[4] = {FLOAT,INT,VOID,-1};
  int paramNodeFollow[3] = {COM,RP,-1};

  sync(paramNodeFirst);

  typeSpec();
  func[currentFunc].listParams.push_back(lookahead.lexeme);
  match(ID);

  if(lookahead.value == LSB) {
    match(LSB);
    match(RSB);
  }

  sync(paramNodeFollow);
}

/**

  Uses the paramList production rule

  @param none
  @return none

*/
void paramList() {
  int paramListFirst[4] = {FLOAT,INT,VOID,-1};
  int paramListFollow[2] = {RP,-1};

  sync(paramListFirst);

  param();
  while(lookahead.value == COM) {
    match(COM);
    param();
  }

  sync(paramListFollow);
}

/**

  Uses the params production rule

  @param none
  @return none

*/
void params() {
  int paramsFirst[4] = {VOID,FLOAT,INT,-1};
  int paramsFollow[2] = {RP,-1};

  sync(paramsFirst);

  if(lookahead.value == VOID) {
    match(VOID);
  }
  else {
    paramList();
  } 

  sync(paramsFollow);
}

/**

  Uses the declRest production rule

  @param none
  @return none

*/
void declRest() {
  int declRestFirst[4] = {SC,LSB,LP,-1};
  int declRestFollow[5] = {EOI,FLOAT,INT,VOID,-1};

  sync(declRestFirst);

  switch(lookahead.value) {
    case SC:
      func[currentFunc].isVar = true;
      match(SC);
      break;
    case LSB:
      func[currentFunc].isVar = true;
      match(LSB);
      match(NUM);
      match(RSB);
      match(SC);
      break;
    case LP:
      func[currentFunc].isVar = false;
      match(LP);
      params();
      match(RP);
      compStmt();
  }

  sync(declRestFollow);
}

/**

  Uses the typeSpec production rule

  @param none
  @return none

*/
void typeSpec() {
  int typeSpecFirst[4] = {FLOAT,INT,VOID,-1};
  int typeSpecFollow[2] = {ID,-1};

  sync(typeSpecFirst);

  switch(lookahead.value) {
    case FLOAT:
      match(FLOAT);
      break;
    case INT:
      match(INT);
      break;
    case VOID:
      match(VOID);
  }

  sync(typeSpecFollow);
}

/**

  Uses the decl production rule

  @param none
  @return none

*/
void decl() {
  int declFirst[4] = {FLOAT,INT,VOID,-1};
  int declFollow[5] = {EOI,FLOAT,INT,VOID,-1};

  sync(declFirst);

  typeSpec();

  func[lookahead.lexeme].lineNumber = codeSize;
  func[lookahead.lexeme].funcName = lookahead.lexeme;
  currentFunc = lookahead.lexeme;

  match(ID);

  declRest();
  
  sync(declFollow);
}

/**

  Uses the program production rule

  @param none
  @return none

*/
void program() {
  int programFirst[4] = {FLOAT,INT,VOID,-1};
  int programFollow[2] = {EOI,-1};

  sync(programFirst);

  decl();

  while(lookahead.value == FLOAT ||
        lookahead.value == INT ||
        lookahead.value == VOID) {
      int t = lookahead.value;
      decl();
      if(t == VOID) {
        genCode("return","0","","");
      }

  }

  sync(programFollow);
}

/**

  Starts the parsing

  @param none
  @return none

*/
void parse() {
  lookahead = scan(in);

  program();
}
