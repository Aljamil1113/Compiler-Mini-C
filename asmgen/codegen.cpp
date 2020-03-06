/**

  ICST252 Code Generation
  codegen.cpp
  Purpose: Convert a Three Address Code (TAC) to its equivalent ASM program

  @author  Louie Pascual, John Dinnex Valeros, Al Jamil Arazas
  @version 1.0 2/28/2016

  Honor Code:  We have not received any unauthorized
               help in completing this work.

             Louie Pascual, John Dinnex Valeros, Al Jamil arazas

*/

#include "global.h"

void generate_code() {
	ifstream fin("tac.in");
	ofstream fout("gen.s");

	string s;
	fout << "\t.globl _main\n";


}