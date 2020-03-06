# Makefile

asmgen : codegen.o parse.o scan.o main.o
	g++ -o asmgen codegen.o parse.o scan.o main.o
	
codegen.o : codegen.cpp global.h
	g++ -c codegen.cpp

parse.o : parse.cpp global.h
	g++ -c parse.cpp

scan.o : scan.cpp global.h
	g++ -c scan.cpp

main.o : main.cpp global.h
	g++ -c main.cpp

clean :
	rm parse.o scan.o main.o 
