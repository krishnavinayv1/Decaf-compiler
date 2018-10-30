parser: parser.ypp scanner.l
		bison -d parser.ypp
		flex scanner.l
		g++ -o parser parser.tab.cpp lex.yy.c -ll
