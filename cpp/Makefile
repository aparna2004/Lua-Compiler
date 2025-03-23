all: main

main: lexer.o parser.tab.o ast.o main.o
	g++ -o main lexer.o parser.tab.o ast.o main.o  

lexer.o: lexer.cpp parser.tab.h
	g++ -c -o lexer.o lexer.cpp

lexer.cpp: lexer.l parser.tab.h
	flex --c++ -o lexer.cpp lexer.l

parser.tab.o: parser.tab.c parser.tab.h
	g++ -c -o parser.tab.o parser.tab.c

parser.tab.c parser.tab.h: parser.y
	bison -d -t -o parser.tab.c parser.y

ast.o: ast.cpp ast.h
	g++ -c -o ast.o ast.cpp

main.o: main.cpp
	g++ -c -o main.o main.cpp

clean:
	rm -f *.o *.tab.* lexer.cpp parser.tab.c main