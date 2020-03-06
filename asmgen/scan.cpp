/**

  ICST252 Scanner
  scan.cpp
  Purpose: Implement a lexical analyzer

  @author  Louie Pascual
  @version 2.1 1/7/2016

  Changes in this version:
  1. Fixed issue regarding negative columns
  2. Fixed row/col problem on multi-lined strings
  3. Changed error of '.' character, this involves adding a new state

  In 2.1:
  1. Added error displaying message when see unexpected end of input

  Honor Code: I have not received any unauthorized help in 
              completing this work.

              Louie Pascual

*/

#include "global.h"

extern int errorCount;

int delta[41][28] = {
  /*     0   1   2   3   4  5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27 */  
/* 0 */ {  3,  3,  4,  3,  3, 10,  1, 35, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 29, 31, 33,  0,125, 35},
/* 1 */ {  1,  1,  1,  1,  1,  1, 38,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 36,  1},
/* 2 */ {  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 36,  1},
/* 3 */ {  3,  3,  3,  3,  3,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102,102},
/* 4 */ {103,103,  4,  7,  7,  5,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103,103},
/* 5 */ {104,104,  6,  7,  7,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
/* 6 */ {104,104,  6,  7,  7,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
/* 7 */ { 37, 37,  9, 37, 37, 37, 37, 37,  8, 37,  8, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37},
/* 8 */ { 37, 37,  9, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37, 37},
/* 9 */ {104,104,  9,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
/*10 */ { 40, 40, 11, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40},
/*11 */ {104,104, 11,  7,  7,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104,104},
/*12 */ {105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105,105},
/*13 */ {106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106,106},
/*14 */ {107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107,107},
/*15 */ {108,108,108,108,108,108,108,108,108, 16,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108,108},
/*16 */ { 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 36, 16},
/*17 */ { 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 16,  0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 36, 16},
/*18 */ {109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109,109},
/*19 */ {110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110,110},
/*20 */ {111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111,111},
/*21 */ {112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112,112},
/*22 */ {113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113,113},
/*23 */ {114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114,114},
/*24 */ {115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115,115},
/*25 */ {116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116,116},
/*26 */ {117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117,117},
/*27 */ {119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119,119, 28,119,119,119,119},
/*28 */ {118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118,118},
/*29 */ {121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121,121, 30,121,121,121,121},
/*30 */ {120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120},
/*31 */ {123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123,123, 32,123,123,123,123},
/*32 */ {122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122,122},
/*33 */ { 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 39, 34, 39, 39, 39, 39},
/*34 */ {124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124,124},
/*35 */ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
/*36 */ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
/*37 */ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
/*38 */ {101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101,101},
/*39 */ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
/*40 */ {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
};

/**

  Returns the name of the token

  @param none
  @return string Name of the specificed token

*/
string tokenNames[] = 
  {"STR", "ID", "NUM", "FLT",
    "+", "*", "-", "/", "%",
    ",", ";", "{", "}", "(", ")", "[", "]",
    "LEQ", "<", "GEQ", ">", "EQ", "=", "NEQ",
    "ERR", "EOI",
    "VOID", "INT", "FLOAT", "IF", "ELSE", "WHILE", "RETURN"};

int row = 1, col = 0;

// Returns token name of a reserved keyword
SymTable reserved[] = {
  {"void", VOID}, {"int", INT}, {"float",FLOAT}, {"if",IF}, {"else",ELSE}, 
  {"while",WHILE}, {"return", RETURN}
};

/**

  Searches the string at the symbol table

  @param name := string etc
  @return token, representing either a reserved keyword
          or an identifier

*/
Token search(string name, int r, int c, string t) {
  for(int i=0; i<7; i++) {
    if(name == reserved[i].name) {
      return Token(reserved[i].id, name, r, c, tokenNames[26+i]);
    }
  }
  return Token(ID, name, r, c, t);
}

/**
  Classify a character symbol

  @param c, a character
  @return category of character

*/
int getCateg(int c) {
  if (c == '_') return 0;
  if (('a' <= c) && (c <= 'z') && (c != 'e')) return 1;
  if (('A' <= c) && (c <= 'Z') && (c != 'E')) return 1;
  if (('0' <= c) && (c <= '9')) return 2;
  if (c == 'e') return 3;
  if (c == 'E') return 4;
  if (c == '.') return 5;
  if (c == '"') return 6;
  if (c == '\\') return 7;
  if (c == '+') return 8;
  if (c == '*') return 9;
  if (c == '-') return 10;
  if (c == '/') return 11;
  if (c == '%') return 12;
  if (c == ',') return 13;
  if (c == ';') return 14;
  if (c == '{') return 15;
  if (c == '}') return 16;
  if (c == '(') return 17;
  if (c == ')') return 18;
  if (c == '[') return 19;
  if (c == ']') return 20;
  if (c == '<') return 21;
  if (c == '>') return 22;
  if (c == '=') return 23;
  if (c == '!') return 24;
  if (c == ' ') return 25;
  if (c == '\t') return 25;
  if (c == '\n') return 25;
  if (c == EOF) return 26;
  return 27;
}


/**

  Reads characters from an input source
  and returns a token value representing
  a pattern matched.

  @param  in, an ifstream object representing input from a file
  @return token, representing a pattern matched

*/
Token scan(ifstream &in) {
  string lexeme = "";
  int tempCol;
  int strRow;
  int strCol;
  bool strProc = false;

  int c = in.get();

  if(c == '\n') {
    row++;
    col = 0;
  }
  else {
    col++;
  }

  int categ = getCateg(c);
  int state = 0;

  while(true) {
    state = delta[state][categ];
  
    if(state == 0) {
      lexeme = "";
    }
    else if(state == 35) {
      cout << "error:" << row << ":" << col << ": unknown symbol '" << (char)c << "'" << " (" << c <<")\n";
      lexeme = "";
      state = 0;
      errorCount++;
    }
    else if(state == 36) {
      cout << "error:" << row << ":" << col << ": unexpected end of input\n";
      lexeme = "";
      state = 0;
      in.putback(c);
      errorCount++;

      cout << endl;
      if(errorCount == 1) {
        cout << errorCount << " error detected.\n"; 
      }
      else {
        cout << errorCount << " errors detected.\n";
      }
      exit(1);
    }
    else if(state == 37) {
      cout << "error:" << row << ":" << col-lexeme.length() << ": malformed float literal '" << lexeme << "'\n";
      state = 0;
      lexeme = ""; 
      in.putback(c);
      col--;
      errorCount++;
    }
    else if(state == 39) {
      char t = '!';

      in.putback(c);
      col--;

      cout << "error:" << row << ":" << col << ": unknown symbol '" << t << "'" << " (" << (int)t <<")\n";
      
      lexeme = "";
      state = 0;
      errorCount++;
    }
    else if(state == 40) {
      char t = '.';

      in.putback(c);
      col--;

      cout << "error:" << row << ":" << col << ": unknown symbol '" << t << "'" << " (" << (int)t <<")\n";
      
      lexeme = "";
      state = 0;
      errorCount++;
    }
    else if(state >= 101) {
      in.putback(c);
      col--;
      
      if(c == '\n') {
        row--;
        col = tempCol;
      }
        
      break;
    } 
    else {
      lexeme += c;
    }

    c = in.get();
    
    if(c == '\n') {
      if (state == 1 && !strProc) {
        strRow = row;
        strCol = col-lexeme.length()+1;
        strProc = true;

        row++;
        tempCol = col;
        col = 0;
      }
      else if (state != 33 && state != 10) {
        row++;
        tempCol = col;
        col = 0;
      }
      else {
        col++;
      }
        
    }
    else {
      col++;
    }

    //cout << col << endl;
    categ = getCateg(c);
  }

  switch(state) {
    case 101: 
      // Solution for multi-lined strings row/col problem
      if(strProc) {
        return Token(STR, lexeme, strRow, strCol,tokenNames[0]);
      }
      else {
        return Token(STR, lexeme, row, col-lexeme.length()+1,tokenNames[0]);
      }
    case 102: return search(lexeme, row, col-lexeme.length()+1, tokenNames[1]);
    case 103: return Token(NUM, lexeme, row, col-lexeme.length()+1,tokenNames[2]);
    case 104: return Token(FLT, lexeme, row, col-lexeme.length()+1,tokenNames[3]);
    case 105: return Token(ADD, lexeme, row, col,tokenNames[4]);
    case 106: return Token(MUL, lexeme, row, col,tokenNames[5]);
    case 107: return Token(SUB, lexeme, row, col,tokenNames[6]);
    case 108: return Token(DIV, lexeme, row, col,tokenNames[7]);
    case 109: return Token(MOD, lexeme, row, col,tokenNames[8]);
    case 110: return Token(COM, lexeme, row, col,tokenNames[9]);
    case 111: return Token(SC,  lexeme, row, col,tokenNames[10]);
    case 112: return Token(LCB, lexeme, row, col,tokenNames[11]);
    case 113: return Token(RCB, lexeme, row, col,tokenNames[12]);
    case 114: return Token(LP,  lexeme, row, col,tokenNames[13]);
    case 115: return Token(RP,  lexeme, row, col,tokenNames[14]);
    case 116: return Token(LSB, lexeme, row, col,tokenNames[15]);
    case 117: return Token(RSB, lexeme, row, col,tokenNames[16]);
    case 118: return Token(LEQ, lexeme, row, col-1,tokenNames[17]);
    case 119: return Token(LTN, lexeme, row, col,tokenNames[18]);
    case 120: return Token(GEQ, lexeme, row, col-1,tokenNames[19]);
    case 121: return Token(GTN, lexeme, row, col,tokenNames[20]);
    case 122: return Token(EQ,  lexeme, row, col-1,tokenNames[21]);
    case 123: return Token(ASSIGN, lexeme, row, col,tokenNames[22]);
    case 124: return Token(NEQ, lexeme, row, col-1,tokenNames[23]);
    case 125: return Token(EOI, lexeme, row, col,tokenNames[24]);
  }
  return Token(EOI, lexeme, row, col,tokenNames[24]); //default return
}







