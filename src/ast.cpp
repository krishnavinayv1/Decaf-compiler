#include <bits/stdc++.h>
using namespace std;
#include "ast.h"
void fields_c::push_back(class field_c *fie) {
    dec_list.push_back(fie);
}
field_c::field_c(string Type, class vars_c *variables) {
    this->Type = Type;
    this->var_list = variables->getVarsList();
}
var_c::var_c(string name, int array_size) {
    this->declType = variableType::Array;
    this->name = name;
    this->length = array_size;
}

var_c::var_c(string name) {
    this->declType = variableType::Normal;
    this->name = name;
}
string var_c::getName() {
    return name;
}
vector<class var_c *> vars_c::getVarsList() {
    return vars_list;
}
void vars_c::push_back(class var_c *var) {
    vars_list.push_back(var);
}