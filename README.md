# decaff-compiler-krishnavinayv1

## File Structure
- dcf_codes
  - All the example codes which can be run by decaf compiler.
    - prime.dcf -- It checks a number is prime or not
    - arraysum.dcf -- It calculates the sum of array
    - linear.dcf -- It is the code for linear search.
    - even.dcf -- It prints all the even numbers of a range
    - maxmin.dcf -- It prints max element and min element in an array.
- extra_dcf_codes
- src
  - Makefile: 
    - A makefile to compile and to make executable
  - scanner.l:
    - File to return tokens by comparing the input text
  - parser.ypp
    - Reads the input and get tokens from scanner file and creates root node.
    - File which contains all the grammars and calls the visitor design pattern and make the program node
  - ast.h
    - Has all the classes of the non terminals of parser file
    - Has the code of visitor designer pattern
    - Takes care of semantic analysis also
  - ast.cpp
    - It has all the methods of the classes and also some part of the semantic analysis code.
    - It also has the complete code of llvm codegen part
   
 ## Description
  - Decaf compiler is a compiler for specific language which can be parsed by some rules. All the grammar resides in the parser file. We get the tokens from scanner file and matches it with the grammar and makes match. Here defining classes for each non terminal and starting from the very child to the creation of root and makes the root object. And as all the methods for visitor designer pattern and also llvm gen part is there in ast.cpp. We call those methods from root to visit every method and makes appropriate codegen. It will redirects to outfile. And in final we just need to compile llvm code with lli to get output. All the semantic analysis also taken care by the ast.h file.
  
 ## Sample Code run
 ```
 - prime.dcf
  krishnav1@krishnav1-Flex-3-1480:~/Desktop/compilers/decaff-compiler-krishnavinayv1/src$ make
  bison -d parser.ypp
  flex scanner.l
  g++ -std=c++11 -o parser parser.tab.cpp ast.cpp lex.yy.c -ll -g -ldl -lfl `llvm-config --cppflags --libs --libfiles core --ldflags --system-libs`
  krishnav1@krishnav1-Flex-3-1480:~/Desktop/compilers/decaff-compiler-krishnavinayv1/src$ ./parser ./../dcf_codes/prime.dcf 
  Parsing Done
  DFS CALLED
  DFS DONE
  LLVM GENERATION SUCCESUL
  krishnav1@krishnav1-Flex-3-1480:~/Desktop/compilers/decaff-compiler-krishnavinayv1/src$ lli outfile 
  Given number which is 91 is a composite number
  ```
 ## Things not implemented
 - Run Time checking not done
    - The subscript of an array must be in bounds.( Here if the subscript is a literal then no problem, but if the subsript is literal from the evaluation of expression not works (Interpreter not done)
    - Control must not fall off the end of a method that is declared to return a result.
