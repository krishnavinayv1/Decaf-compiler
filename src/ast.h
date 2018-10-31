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
enum variableType {
    Array = 1, Normal = 2
};
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
    variableType declType;
    string name;
    int length;
    var_c(string, int);
    explicit var_c(std::string);
    bool isArray() { return (declType == variableType::Array); }
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
	class vars_d_c *total_vars;
	block_c(){this->total_vars = NULL;}
	block_c(class vars_d_c *rt)
	{
		this->total_vars = rt;
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
		cout<<"Starting the main block"<<endl;
		if(v->total_vars)
			v->total_vars->accept(this);
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
};