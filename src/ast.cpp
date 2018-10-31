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
    this->declType = 1;
    this->name = name;
    this->length = array_size;
}

var_c::var_c(string name) {
    this->declType = 2;
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
void var_names_c::push_back(string a) {
    var_strings.push_back(a);
}
void var_d_c::push_back(class var_names_c *fie) {
    for(int i=0;i<fie->var_strings.size();i++)
    	names.push_back(fie->var_strings[i]);
}
var_d_c::var_d_c(string type, string id) {
    this->Type = type;
    this->names.push_back(id);
}
void vars_d_c::push_back(class var_d_c *fie) {
    var_d_c_list.push_back(fie);
}
vars_d_c::vars_d_c(class var_d_c *fie) {
    this->var_d_c_list.push_back(fie);
}
arg_c::arg_c(string a,string b)
{
	pair<string,string> ty;
	ty.first = a;
	ty.second = b;
	this->v.push_back(ty);
}
void arg_c::push_back(string a,string b) {
	pair<string,string> ty;
	ty.first = a;
	ty.second = b;
	v.push_back(ty);
}
args_c::args_c(string a,string b)
{
	pair<string,string> ty;
	ty.first = a;
	ty.second = b;
	this->v.push_back(ty);
}
void args_c::push_back(class arg_c *tie) {
	for(int i=0;i<tie->v.size();i++)
	v.push_back(tie->v[i]);
}
void meths_c::push_back(class meth_c *tie) {
	method_list.push_back(tie);
}
void callout_args_c::push_back(class callout_arg_c *tie) {
	callout_arg_list.push_back(tie);
}
void pars_c::push_back(class expr_c *tie) {
	call_expr_list.push_back(tie);
}
void statements_c::push_back(class statement_c *tie) {
	stats_list.push_back(tie);
}
bool statement_c::check_return_bool(class expr_c *t) 
{
	if(t->return_type=="bool")
		return true;
	return false;
}
string expr_c::get_type(class expr_c *a,class expr_c *c,string b)
{
	if(((b=="<" or b=="<=") or (b==">=" or b==">"))
	  or ((b=="+" or b=="-") or ((b=="*" or b=="%") or b=="/"))) 
	{
		if(a->return_type!="int" or c->return_type!="int")
		{
			cout<<"This binary relative or arithmetic operator has operators other than int"<<endl;
			exit(0);
		}
		else
		{
			if((b=="<" or b=="<=") or (b==">=" or b==">"))
			{
				return "bool";
			}
			else
			{
				return "int";
			}
		}
	}
	else if(b=="!=" or b=="==")
	{
		if(a->return_type!=c->return_type)
		{
			cout<<"for the <eq_op> both operands have no same type"<<endl;
			exit(0);
		}		
		else
			return "bool";
	}
	else if(b=="&&" or b=="||")
	{
		if(a->return_type!="bool" or c->return_type!="bool")
		{
			cout<<"This binary cond operator has operators other than bool"<<endl;
			exit(0);
		}
		else
		return "bool";
	}
	else
	{
		return "bool";
	}
		
}