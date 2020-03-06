/**

  ICST252 Assembly Code Generator
  main.cpp
  Purpose: Implements the driver of ASMGEN 

  @author  Louie Pascual
  @subauthors Al Arazas, Dinnex Valeros
  @version 2.0 3/26/2016

  Honor Code: We have not received any unauthorized help
              in completing this work.

            
      Al Arazas, Dinnex Valeros, Louie Pascual
*/

#include "global.h"
ifstream in;
int errorCount = 0;


int main(int argc, char *argv[])
{
  // Checks the number of files, exits if it does not 
  //  follow the specified format
  
  if(argc <= 1) {
    cout << "no input file provided.\nformat: asmgen 'file_name'\n";
    exit(1);
  }
  else if (argc > 2) {
    cout << "too many input files provided.\nformat: asmgen 'file_name'\n";
    exit(1);
  }
    
  in.open(argv[1]);
  
  // Checks if it can open the file, exits if it can't
  if(!in) {
    cout << "cannot open '" << argv[1] << "'\n";
    exit(1);
  }
  
  parse();

  cout << endl;
  if(errorCount == 0) {
    //showCode();  
    string outputFileName(argv[1]);
    outputFileName = outputFileName.substr(0,outputFileName.length()-3) + ".s";
    genTargetCode(outputFileName);
    
  }
  else if(errorCount == 1) {
    cout << errorCount << " error detected.\n"; 
  }
  else {
    cout << errorCount << " errors detected.\n";
  }



  return 0;
}

