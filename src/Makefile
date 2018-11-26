parser: parser.ypp scanner.l ast.cpp
		bison -d parser.ypp
		flex scanner.l
		g++ -std=c++11 -o parser parser.tab.cpp ast.cpp lex.yy.c -ll -g -ldl -lfl `llvm-config --cppflags --libs --libfiles core --ldflags --system-libs`
