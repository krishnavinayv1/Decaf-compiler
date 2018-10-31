#include<bits/stdc++.h>
using namespace std;
class visitor;
class AST;
class prog;
class dfs;
class fields_c;
class field_c;
class vars_c;
class var_c;
class meth_c;
class meths_c;
class args_c;
class arg_c;
class block_c;
class vars_d_c;
class var_d_c;
class var_names_c;
class statements_c ;
class statement_c ;
class expr_c;
class location_c;
class pars_c;
class function_call_c;
class literal_c;
class callout_args_c;
class callout_arg_c;
class assignment_c;
class visitor
{
public:
	virtual int visit(prog* val){};
	virtual int visit(AST* val){};
	virtual int visit(fields_c* val){};
	virtual int visit(field_c* val){};
	virtual int visit(vars_c* val){};
	virtual int visit(var_c* val){};
	virtual int visit(meth_c* val){};
	virtual int visit(meths_c* val){};
	virtual int visit(args_c* val){};
	virtual int visit(block_c* val){};
	virtual int visit(vars_d_c* val){};
	virtual int visit(var_d_c* val){};
	virtual int visit(var_names_c* val){};
	virtual int visit(statements_c* val){};
	virtual int visit(statement_c* val){};
	virtual int visit(expr_c* val){};
	virtual int visit(location_c* val){};
	virtual int visit(pars_c* val){};
	virtual int visit(function_call_c* val){};
	virtual int visit(literal_c* val){};
	virtual int visit(callout_args_c* val){};
	virtual int visit(callout_arg_c* val){};
	virtual int visit(assignment_c* val){};
};

class AST
{
	public:
  		AST(){}
  	virtual int accept(visitor *v){v->visit(this);}
};
class prog: public AST 
{
	public:
	class fields_c *total_fields;
	class meths_c *total_methods=NULL;
	prog(){this->total_fields = NULL;}
	prog(class fields_c *rt,class meths_c *rt1)
	{
		this->total_fields = rt;
		this->total_methods = rt1;
	}
	virtual int accept(visitor *v){v->visit(this);}
};
class fields_c: public AST{
public:
	vector<class field_c *> dec_list;
	fields_c() = default;
    void push_back(class field_c *);
    virtual int accept(visitor *v){v->visit(this);}
};
class field_c: public AST{
public:
	string Type;
    vector<class var_c *> var_list;
    field_c(string, class vars_c *);
    virtual int accept(visitor *v){v->visit(this);}
};
class vars_c: public AST{
public:
	vector<class var_c*> vars_list;
    vars_c() = default;
    void push_back(class var_c *);
    vector<class var_c *> getVarsList();
    virtual int accept(visitor *v){v->visit(this);}
};

class var_c: public AST{
public:
    int declType;
    string name;
    int length;
    var_c(string, int);
    explicit var_c(std::string);
    bool isArray() { return (declType == 1); }
    string getName();
    int getLength() { return length; }
    virtual int accept(visitor *v){v->visit(this);}
};
class meths_c: public AST{
public:
	vector<class meth_c *> method_list;
	meths_c() = default;
	void push_back(class meth_c *);
	virtual int accept(visitor *v){v->visit(this);}
};
class meth_c: public AST{
public:
	string Type;
	string method_name;
	class args_c *arguments;
	class block_c *block;
	meth_c(string a,string b,class args_c *c,class block_c *d){
			this->Type = a;
			this->method_name = b;
			this->arguments = c;
			this->block = d;
	}
	virtual int accept(visitor *v){v->visit(this);}
};
class args_c: public AST{
public:
	args_c(string,string);
	std::vector<pair<string,string> >v;
	args_c()=default;
	void push_back(class arg_c *);
	virtual int accept(visitor *v){v->visit(this);}
};
class arg_c: public AST{
public:
	arg_c(string,string);
	std::vector<pair<string,string> >v;
	void push_back(string,string);
	virtual int accept(visitor *v){v->visit(this);}
};
class block_c: public AST{
public:
	class vars_d_c *total_vars=NULL;
	class statements_c *total_st=NULL;
	block_c(){this->total_vars = NULL;}
	block_c(class vars_d_c *rt,class statements_c *rt1)
	{
		this->total_vars = rt;
		this->total_st = rt1;
	}
	virtual int accept(visitor *v){v->visit(this);}
};
class vars_d_c: public AST{
public:
	std::vector<class var_d_c *> var_d_c_list;
	vars_d_c(class var_d_c *);
	void push_back(class var_d_c *);
	virtual int accept(visitor *v){v->visit(this);}
};
class var_d_c: public AST{
public:
	string Type;
	std::vector<string> names;
	var_d_c(string,string);
	void push_back(class var_names_c *);
	virtual int accept(visitor *v){v->visit(this);}
};
class var_names_c: public AST{
public:
	std::vector<string> var_strings;
	var_names_c() = default;
	void push_back(string);
	virtual int accept(visitor *v){v->visit(this);}
};

class statements_c: public AST{
public:
	vector<class statement_c *> stats_list;
	statements_c() = default;
	void push_back(class statement_c *);
	virtual int accept(visitor *v){v->visit(this);}
};
class statement_c: public AST{
public:
	class assignment_c *ass=NULL;
	class function_call_c *ff=NULL;
	class expr_c *e_first=NULL;
	class expr_c *e_second=NULL;
	class block_c *b_first=NULL;
	class block_c *b_second=NULL;
	string a;
	int type;
	statement_c(class assignment_c *a)
	{
		this->ass = a;
		this->type = 1;
	}
	statement_c(class function_call_c *a)
	{
		this->ff = a;
		this->type = 2;
	}
	statement_c(class expr_c *a,class block_c *b)
	{

		if(check_return_bool(a)==false)
		{
			cout<<"Not a bool Expression for if statement"<<endl;
			exit(0);
		}
		this->e_first = a;
		this->b_first = b;
		this->type = 3;
	}
	statement_c(class expr_c *a, class block_c *b,class block_c *c)
	{

		if(check_return_bool(a)==false)
		{
			cout<<"Not a bool Expression for if else statement"<<endl;
			exit(0);
		}
		this->e_first = a;
		this->b_first = b;
		this->b_second = c;
		this->type = 4;	
	}
	statement_c(string a,class expr_c *b,class expr_c *c,class block_c *d)
	{
		this->a = a;
		this->e_first = b;
		this->e_second = c;
		this->b_first = d;
		this->type = 5;
	}
	statement_c(string a)
	{
		this->a = a;
		if(a=="RETURN")this->type = 6;
		if(a=="BREAK")this->type = 8;
		if(a=="CONTINUE")this->type =9;
	}
	statement_c(string a,class expr_c *b)
	{
		this->a = a;
		this->e_first = b;
		this->type = 7;
	}
	statement_c(class block_c *a)
	{
		this->b_first = a;
		this->type = 10;
	}
	bool check_return_bool(class expr_c *e);
	virtual int accept(visitor *v){v->visit(this);}
};
class assignment_c: public AST{
public:
	class location_c *ll;
	string a;
	class expr_c *ee;
	int type;
	assignment_c(class location_c *a,string b,class expr_c *c)
	{
		this->ll = a;
		this->a =b;
		this->ee = c;
		if(b=="=")this->type=1;
		if(b=="-=")this->type=2;
		if(b=="+=")this->type=3;
	}
	virtual int accept(visitor *v){v->visit(this);}
};
class function_call_c: public AST{
public:
	int type;
	string name;
	class pars_c *pp=NULL;
	string meth;
	class callout_args_c *cc = NULL;
	function_call_c(string a,class pars_c *rt)
	{
		this->name = a;
		this->pp = rt;
		type = 1;
	}
	function_call_c(string a,string b,class callout_args_c *rt)
	{
		this->name = a;
		this->cc = rt;
		this->meth = b;
		type = 2;
	}
	virtual int accept(visitor *v){v->visit(this);}
};
class pars_c: public AST{
public:
	vector<class expr_c *> call_expr_list;
	pars_c()= default;
	void push_back(class expr_c *);
	virtual int accept(visitor *v){v->visit(this);}
};
class location_c: public AST{
public:
	string a;
	class expr_c *er=NULL;
	int type;
	location_c(string a)
	{
		this->a = a;
		this->type = 1;
	}
	location_c(string a,class expr_c *b)
	{
		this->a = a;
		this->er = b;
		this->type = 2;
	}
	virtual int accept(visitor *v){v->visit(this);}
};
class callout_args_c: public AST{
public:
	std::vector<class callout_arg_c *> callout_arg_list;
	callout_args_c() = default;
	void push_back(class callout_arg_c *);
	virtual int accept(visitor *v){v->visit(this);}
};
class callout_arg_c: public AST{
public:
	class expr_c *exp=NULL;
	string str;
	int type;
	callout_arg_c(class expr_c *a)
	{
		this->exp = a;
		this->type = 0;
	}
	callout_arg_c(string a)
	{
		this->str= a;
		this->type = 1;  
	}
	virtual int accept(visitor *v){v->visit(this);}
};
class literal_c: public AST{
public:
	int a;bool b;char c;
	int flag;
	literal_c(int a){this->a = a;this->flag=1;}
	literal_c(bool b){this->b =b;this->flag=2;}
	literal_c(char c){this->c =c;this->flag=3;}
	virtual int accept(visitor *v){v->visit(this);}
};
class expr_c: public AST{
public:
	int type=0;
	string return_type;
	string operato;
	class expr_c *first=NULL;
	class expr_c *second=NULL;
	class location_c *loc=NULL;
	class literal_c *lit=NULL;
	expr_c(class expr_c *a,string b,class expr_c *c)
	{
		this->first = a;
		this->second = c;
		this->operato = b;
		this->type = 2;
		this->return_type = get_type(this->first,this->second,b);
	}
	expr_c(string b,class expr_c *c)
	{
		this->first = c;
		this->second = NULL;
		this->operato = b;
		this->type = 1;
		if(b=="!")
		{
			if(c->return_type!="bool")
			{
				cout<<"For not expr operand is not bool"<<endl;
				exit(0);
			}
			this->return_type = "bool";
		}
		if(b=="-")
		this->return_type = c->return_type;
	}
	expr_c(class location_c *a)
	{
		this->loc = a;
		this->type = 0;
		this->return_type = "int";
	}
	expr_c(class literal_c *a)
	{
		this->lit = a;
		this->type = 4;
		if(a->flag==1)this->return_type="int";
		if(a->flag==2)this->return_type="bool";
	}
	expr_c(class expr_c *a)
	{
		this->first = a;
		this->return_type = a->return_type;
		this->type = 3;
	}
	string get_type(class expr_c *,class expr_c *,string);
	virtual int accept(visitor *v){v->visit(this);}
};







class dfs: public visitor
{
	public:
	virtual int visit(prog *v)
	{
		cout<<"entered programm"<<endl;
		if(v->total_fields)
		v->total_fields->accept(this);
		if(v->total_methods)
		v->total_methods->accept(this);
	}
	virtual int visit(fields_c *v)
	{
		cout<<"fieds_declarations"<<endl;
		for(int i=0;i<v->dec_list.size();i++)
			v->dec_list[i]->accept(this);
	}
	virtual int visit(field_c *v)
	{
		cout<<"field_declaration"<<endl;
		cout<<v->Type<<endl;
		for(int i=0;i<v->var_list.size();i++){
			v->var_list[i]->accept(this);
		}
	}
	virtual int visit(vars_c *v)
	{
		cout<<"vars_declarations"<<endl;
	}
	virtual int visit(var_c *v)
	{
		if(v->declType==1)
		{
			cout<<"Array: "<<v->getName()<<" "<<v->getLength()<<endl; 
		}
		else
		{
			cout<<"Normal "<<v->getName()<<endl;
		}
	}
	virtual int visit(meths_c *v)
	{
		cout<<"calling method_declarations"<<endl;
		for(int i=0;i<v->method_list.size();i++)
			v->method_list[i]->accept(this);
	}
	virtual int visit(meth_c *v)
	{
		cout<<"Method: - "<<endl;
		cout<<v->Type<<endl;
		cout<<v->method_name<<endl;
		v->arguments->accept(this);
		v->block->accept(this);
	}
	virtual int visit(args_c *v) 
	{
		cout<<"Arguments for the method"<<endl;
		for(int i=0;i<v->v.size();i++)
		{
			cout<<v->v[i].first<<" "<<v->v[i].second<<endl;
		}
	}
	virtual int visit(block_c *v)
	{
		cout<<"Starting the block"<<endl;
		if(v->total_vars)
			v->total_vars->accept(this);
		if(v->total_st)
			v->total_st->accept(this);
	} 
	virtual int visit(vars_d_c *v)
	{
		for(int i=0;i<v->var_d_c_list.size();i++)
		{
			v->var_d_c_list[i]->accept(this);
		}
	} 
	virtual int visit(var_d_c *v)
	{
		cout<<v->Type<<endl;
		for(int i=0;i<v->names.size();i++)
			cout<<v->names[i]<<endl;
	}
	virtual int visit(statements_c* val){
		cout<<"visited statement_list"<<endl;
		for(int i=0;i<val->stats_list.size();i++)
		{
			val->stats_list[i]->accept(this);
		}
	};
	virtual int visit(statement_c* val)
	{
		cout<<"Statement: "<<endl;
		if(val->type==1)
		{
			cout<<"ass"<<endl;
			val->ass->accept(this);
		}
		if(val->type==3)
		{
			cout<<"IF"<<endl;
			val->e_first->accept(this);
			val->b_first->accept(this);
		}
		if(val->type==4)
		{
			cout<<"IF ELSE"<<endl;
			val->e_first->accept(this);
			val->b_first->accept(this);
			val->b_second->accept(this);
		}
		if(val->type==5)
		{
			cout<<"for loop"<<endl;
			cout<<val->a<<endl;
			val->e_first->accept(this);
			val->e_second->accept(this);
			val->b_first->accept(this);
		}
	};
	virtual int visit(expr_c* val)
	{
			cout<<"Expression"<<endl;
		if(val->type==2)
		{
			cout<<"Binary operator"<<endl;
			cout<<"First: "<<endl;
			val->first->accept(this);
			cout<<"Operand: "<<val->operato<<endl;
			cout<<"second: "<<endl;
			val->second->accept(this);
		}
		else if(val->type==1)
		{
			cout<<"Unary operator"<<endl;
			cout<<"First: "<<val->first->accept(this)<<endl;
			cout<<"Operand: "<<val->operato<<endl;
		}
		else if(val->type==0)
		{
			val->loc->accept(this);
		}
		else if(val->type == 4)
		{
			val->lit->accept(this);
		}
		else
		{
			val->first->accept(this);
		}
	};
	virtual int visit(location_c* val)
	{
		cout<<"location_c: "<<endl;
		if(val->type==1)
		{
			cout<<"Not an array"<<endl;
			cout<<val->a<<endl;
		}
		else
		{
			cout<<"Array"<<endl;
			cout<<val->a<<endl;
			val->er->accept(this);
		}
	};
	virtual int visit(pars_c* val){};
	virtual int visit(function_call_c* val){};
	virtual int visit(literal_c* val)
	{
		cout<<"literal_c: "<<endl;
			if(val->flag==1)
				cout<<val->a<<endl;
			if(val->flag==2)
				cout<<val->b<<endl;
			if(val->flag==3)
				cout<<val->c<<endl;
	};
	virtual int visit(callout_args_c* val){};
	virtual int visit(callout_arg_c* val){};
	virtual int visit(assignment_c* val)
	{
		cout<<"Assignment operator"<<endl;
		if(val->type == 1)cout<<"= operator"<<endl;
		if(val->type == 3)cout<<"+= operator"<<endl;
		if(val->type == 2)cout<<"-= operator"<<endl;
		val->ll->accept(this);
		val->ee->accept(this);
	};
};