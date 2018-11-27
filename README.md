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
  
    
