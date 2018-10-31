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
	prog(){this->total_fields = NULL;}
	prog(class fields_c * rt)
	{
		this->total_fields = rt;
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
class dfs: public visitor
{
	public:
	virtual int visit(prog *v)
	{
		cout<<"entered programm"<<endl;
		if(v->total_fields)
		v->total_fields->accept(this);
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
};