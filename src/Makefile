parser: parser.ypp scanner.l ast.cpp
		bison -d parser.ypp
		flex scanner.l
		g++ -std=c++11 -o parser parser.tab.cpp ast.cpp lex.yy.c -ll
