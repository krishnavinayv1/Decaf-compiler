#include <bits/stdc++.h>
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/Interval.h"
#include <llvm/IR/CFG.h>
#include "llvm/IR/BasicBlock.h"
#include <llvm/IR/Function.h>
#include <utility>
#include <llvm/IR/Value.h>

using namespace llvm;
using namespace std;
#include "ast.h"
map<string,bool> mp;
map<string,pair<int,int > > tp;

void fields_c::push_back(class field_c *fie) {
    dec_list.push_back(fie);
}
field_c::field_c(string Type, class vars_c *variables) {
    this->Type1 = Type;
    this->var_list = variables->getVarsList();
    for(int i=0;i<this->var_list.size();i++)
    {
        if(mp[this->var_list[i]->name]==true)
        {
            cout<<"Already initiaized variable. Reinitialized could not be done "<<this->var_list[i]->name<<endl;
            //exit(0);
        }
        mp[this->var_list[i]->name]=true;
        if(this->var_list[i]->declType==1)
        {
            pair<int,int>temp;
            if(Type=="int")
                temp.first = 3;
            if(Type=="boolean")
                temp.first = 4;
            temp.second = this->var_list[i]->length;
            tp[this->var_list[i]->name]=temp;
        }
        else
        {
            pair<int,int>temp;
            if(Type=="int")
                temp.first = 1;
            if(Type=="boolean")
                temp.first = 2;
            temp.second = 0;
            tp[this->var_list[i]->name]=temp;
        }
    }
}
var_c::var_c(string name, int array_size) {
    this->declType = 1;
    this->name = name;
    if(array_size<=0)
    {
        cout<<"Array_size could not be less than or equal to 0"<<endl;
        //exit(0);
    }
    this->length = array_size;
}
llvm::Value *reportError(string error_str) {
    cerr << error_str << endl;
    return nullptr;
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
    this->Type1 = type;
    this->names.push_back(id);
}
void vars_d_c::push_back(class var_d_c *fie) {
    var_d_c_list.push_back(fie);
    this->add_to_map(fie);
}
vars_d_c::vars_d_c(class var_d_c *fie) {
    this->var_d_c_list.push_back(fie);
    this->add_to_map(fie);
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
    this->add_to_map();
}
void args_c::add_to_map()
{
    cout<<"args_c::Adding to map "<<endl;
    if(v.size()==0)
        return;
    pair<int,int>temp;

    for(int i=0;i<v.size();i++)
    {
        if(mp[v[i].second]==true)
        {
            cout<<"Already initiaized variable. Reinitialized could not be done "<<v[i].second<<endl;
            //exit(0);
        }
        cout<<v[i].first<<" "<<v[i].second<<endl;
        temp.second=0;
        if(v[i].first=="int")
            temp.first = 1;
        else
            temp.first=2;
        mp[v[i].second]=true;
        tp[v[i].second]=temp;
    }
}
void args_c::push_back(class arg_c *tie) {
    for(int i=0;i<tie->v.size();i++)
        v.push_back(tie->v[tie->v.size()-i-1]);
    this->add_to_map();
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
    if(t->return_type=="boolean")
        return true;
    return false;
}
void meth_c::remove_from_map()
{
    if(arguments!=NULL){
        if(arguments->v.size()==0)
            return;
        for(int i=0;i<arguments->v.size();i++)
        {
            cout<<"meth_c::"<<arguments->v[i].second<<endl;
            if(mp[arguments->v[i].second]==true)
            {
                mp[arguments->v[i].second]=false;
            }

        }
    }
};
string expr_c::get_type(class expr_c *a,class expr_c *c,string b)
{
    if(((b=="<" or b=="<=") or (b==">=" or b==">"))
            or ((b=="+" or b=="-") or ((b=="*" or b=="%") or b=="/")))
    {
        if(a->return_type!="int" or c->return_type!="int")
        {
            cout<<"This binary relative or arithmetic operator has operators other than int"<<endl;
            //exit(0);
        }
        else
        {
            if((b=="<" or b=="<=") or (b==">=" or b==">"))
            {
                return "boolean";
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
            cout<<a->return_type<<" "<<c->return_type<<endl;
            cout<<"for the <eq_op> both operands have no same type"<<endl;
            //exit(0);
        }
        else
            return "boolean";
    }
    else if(b=="&&" or b=="||")
    {
        if(a->return_type!="boolean" or c->return_type!="boolean")
        {
            cout<<"This binary cond operator has operators other than boolean"<<endl;
            //exit(0);
        }
        else
            return "boolean";
    }
    else
    {
        return "boolean";
    }

}
bool assignment_c::check_equal_types(class location_c *a,class expr_c *b)
{
    //cout<<"#"<<a->return_type<<" "<<a->a <<" "<<b->return_type<<"$"<<endl;
    return (a->return_type==b->return_type);
}
void vars_d_c::add_to_map(class var_d_c *v)
{
    if(v==NULL)
        return;
    pair<int,int>temp;
    if(v->Type1=="int")
        temp.first = 1;
    if(v->Type1=="boolean")
        temp.first = 2;

    for(int j=0;j<v->names.size();j++)
    {
        if(mp[v->names[j]]==true)
        {
            cout<<"Already initiaized variable. Reinitialized could not be done "<<v->names[j]<<endl;
            //exit(0);
        }
        temp.second=0;
        mp[v->names[j]]=true;
        tp[v->names[j]]=temp;
    }
}
void block_c::remove_from_map(class vars_d_c *v)
{

    if(v==NULL)
        return;
    for(int i=0;i<v->var_d_c_list.size();i++)
    {
        for(int j=0;j<v->var_d_c_list[i]->names.size();j++)
        {
            if(mp[v->var_d_c_list[i]->names[j]]==true)
            {
                mp[v->var_d_c_list[i]->names[j]]=false;
            }
        }
    }
}
string location_c::get_type(class expr_c *a)
{
    return a->return_type;
}
int meth_c::get_size(class args_c *c)
{
    return c->v.size();
}
bool block_c::has_return()
{
    return total_st->has_return();
}
bool block_c::has_break()
{
    return total_st->has_break();
}
bool block_c::has_continue()
{
    return total_st->has_continue();
}
bool statements_c::has_return() {
    for (int i = 0; i < stats_list.size(); i++) {
        //  cout<<"statement "<<stats_list[i]->type<<endl;
        if (stats_list[i]->has_return()){
            return true;
        }
    }
    return false;
}


bool statements_c::has_continue() {
    for (int i = 0; i < stats_list.size(); i++) {
        if (stats_list[i]->has_continue()) {
            return true;
        }
    }
    return false;
}

bool statements_c::has_break() {
    for (int i = 0; i < stats_list.size(); i++) {
        if (stats_list[i]->has_break()) {
            return true;
        }
    }
    return false;
}
bool statement_c::has_return()
{
    if(type==6 or type==7)
        return true;
    if(type==3)
    {
        if(!b_second)
            return b_first->has_return();
        else
            return b_second->has_return()|b_first->has_return();
    }
    if(type==10)
    {
        return b_first->has_return();
    }
    if(type==4)
        return b_first->has_return();
    return false;
}
bool statement_c::has_break()
{
    if(type==8)
        return true;
    if(type==3)
    {
        if(!b_second)
            return b_first->has_break();
        else
            return b_second->has_break()|b_first->has_break();
    }
    if(type==10)
    {
        return b_first->has_break();
    }
    if(type==4)
        return b_first->has_break();
    return false;
}
bool statement_c::has_continue()
{
    if(type==9)
        return true;
    if(type==3)
    {
        if(!b_second)
            return b_first->has_continue();
        else
            return b_second->has_continue()|b_first->has_continue();
    }
    if(type==10)
    {
        return b_first->has_continue();
    }
    if(type==4)
        return b_first->has_continue();
    return false;
}
// -------------- LLVM code started ---------------------//

Constructs::Constructs() {
    this->Builder = new IRBuilder<>(Context);
    this->loops = new std::stack<loopInfo*>();
    errors = 0;
    this->TheModule = new Module("Decaf compiler", Context);
    this->TheFPM = new llvm::legacy::FunctionPassManager(TheModule);
    TheFPM->doInitialization();
}

AllocaInst *Constructs::CreateEntryBlockAlloca(Function *TheFunction, std::string VarName, std::string type) {
    /* Get the builder for current context */
    IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
    AllocaInst *alloca_instruction = nullptr;
    if (type == "int") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt32Ty(this->Context), 0, VarName);
    } else if (type == "boolean") {
        alloca_instruction = TmpB.CreateAlloca(Type::getInt1Ty(this->Context), 0, VarName);
    }
    return alloca_instruction;
}
Value *prog::generateCode()
{
    Value *v;
    if(total_fields!=NULL)
    {
        v=total_fields->generateCode(this->compilerConstructs);
        if(v==nullptr)
        {
            cerr<<"Invalid field Declarations"<<endl;
            cout<<"ERROR 2"<<endl;
            return nullptr;
        }
    }
    if(total_methods!=NULL)
    {
        v=total_methods->generateCode(this->compilerConstructs);

        if(v==nullptr)
        {
            cout<<"ERROR 1"<<endl;
            return nullptr;
        }
    }
    return v;
}
// void prog::generateCodeDump()
// {
// 	cerr << "Generating LLVM IR Code\n";
//     this->compilerConstructs->TheModule->print(llvm::outs(), nullptr);
// }
raw_ostream &file_write()
{
    FILE *fp=fopen("outfile","w");
    static raw_fd_ostream S(fileno(fp), true);
    return S;
}
void prog::generateCodeDump()
{
    cerr << "Generating LLVM IR Code\n";

    this->compilerConstructs->TheModule->print(file_write(), nullptr);
}

Value *fields_c::generateCode(Constructs *compilerConstructs)
{
    for(auto &i:dec_list)
    {
        i->generateCode(compilerConstructs);
    }
    Value *v=ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
    return v;
}
Value *field_c::generateCode(Constructs *compilerConstructs)
{
    llvm::Type *ty = nullptr;
    if(Type1=="int")
    {
        ty = Type::getInt32Ty(compilerConstructs->Context);
    }
    else if(Type1=="boolean")
    {
        ty = Type::getInt1Ty(compilerConstructs->Context);
    }

    for(auto var:var_list)
    {
        if(var->isArray())
        {
            ArrayType *arrType = ArrayType::get(ty, var->getLength());
            GlobalVariable *gv = new GlobalVariable(*(compilerConstructs->TheModule), arrType, false,
                    GlobalValue::ExternalLinkage, nullptr,
                    var->getName());
            gv->setInitializer(ConstantAggregateZero::get(arrType));
        }
        else
        {
            GlobalVariable *gv = new GlobalVariable(*(compilerConstructs->TheModule), ty, false,
                    GlobalValue::ExternalLinkage, nullptr,
                    var->getName());
            gv->setInitializer(Constant::getNullValue(ty));
        }
    }
    Value *v = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
    return v;
}
Value *meths_c::generateCode(Constructs *compilerConstructs)
{
    Value *V = ConstantInt::get(compilerConstructs->Context, APInt(32, 0));
    for(auto &i:method_list)
    {
        V=i->generateCode(compilerConstructs);
        if(V==nullptr)
            return V;
    }
    return V;
}
Function* meth_c::generateCode(Constructs *compilerConstructs)
{
    std::vector<std::string> argNames;
    std::vector<std::string> argTypes;
    std::vector<pair<string,string > > args;
    if(arguments!=NULL)
    {
        args = arguments->v;
    }

    std::vector<Type *> argumens;
    auto arg_size = args.size();
    for (auto &arg : args) {
        std::string arg_type = arg.first;
        std::string arg_name = arg.second;
        if (arg_type == "int") {
            argumens.push_back(Type::getInt32Ty(compilerConstructs->Context));
        } else if (arg_type == "boolean") {
            argumens.push_back(Type::getInt1Ty(compilerConstructs->Context));
        } else {
            compilerConstructs->errors++;
            cerr<<"Arguments can only be int or boolean"<<endl;
            return nullptr;
        }
        argTypes.emplace_back(arg_type);
        argNames.emplace_back(arg_name);
    }

    Type *returnType;
    /* Get the return Type */
    if (Type1 == "int") {
        returnType = Type::getInt32Ty(compilerConstructs->Context);
    } else if (Type1 == "boolean") {
        returnType = Type::getInt1Ty(compilerConstructs->Context);
    } else if (Type1 == "void") {
        returnType = Type::getVoidTy(compilerConstructs->Context);
    } else {
        compilerConstructs->errors++;
        cerr<<"Invalid Return Type for " + method_name + ". Return Type can only be int or boolean or bool"<<endl;
        return nullptr;
    }

    FunctionType *FT = llvm::FunctionType::get(returnType, argumens, false);
    Function *F = llvm::Function::Create(FT, Function::ExternalLinkage, method_name, compilerConstructs->TheModule);

    unsigned Idx = 0;
    for (Function::arg_iterator AI = F->arg_begin(); Idx != arg_size; ++AI, ++Idx) {
        AI->setName(argNames[Idx]);
    }

    /* Create a New block for this Function */
    BasicBlock *BB = BasicBlock::Create(compilerConstructs->Context, "entry", F);
    compilerConstructs->Builder->SetInsertPoint(BB);
    Idx = 0;

    /* Allocate memory for the arguments passed */
    for (auto &Arg : F->args()) {
        AllocaInst *Alloca = compilerConstructs->CreateEntryBlockAlloca(F, argNames[Idx], argTypes[Idx]);
        compilerConstructs->Builder->CreateStore(&Arg, Alloca);
        compilerConstructs->NamedValues[argNames[Idx]] = Alloca;
        Idx++;
    }

    Value *RetVal;
    RetVal = block->generateCode(compilerConstructs);
    if (RetVal) {
        //  cout<<"Entered"<<RetVal<<endl;
        /* make this the return value */
        if (Type1 == "void")
            compilerConstructs->Builder->CreateRetVoid();
        // compilerConstructs->Builder->CreateRet(RetVal);
        // else

        /// Iterate through each basic block in this function and remove any dead code
        // for (auto &basicBlock : *F) {
        //     BasicBlock *block = &basicBlock;
        //     removeDeadCode(block);
        // }
        /* Verify the function */
        verifyFunction(*F);
        compilerConstructs->TheFPM->run(*F);
        return F;
    }

    /* In case of errors remove the function */
    F->eraseFromParent();
    return nullptr;
}
Value* block_c::generateCode(Constructs *compilerConstructs)
{
    Value *V;
    std::map<std::string, llvm::AllocaInst *> Old_vals;
    if(total_vars!=NULL)
    {
        V = total_vars->generateCode(Old_vals, compilerConstructs);
        if (V == nullptr) {
            return V;
        }
    }
    if(total_st!=NULL)
    {
        V=total_st->generateCode(compilerConstructs);
        for (auto it = Old_vals.begin(); it != Old_vals.end(); it++) {
            compilerConstructs->NamedValues[it->first] = Old_vals[it->first];
        }
    }
    return V;
}
Value* vars_d_c::generateCode(map<string, AllocaInst *> &oldValues, Constructs *compilerConstructs)
{
    Value *v = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
    for (auto &decl : var_d_c_list) {
        /// Generate the code for each declaration
        v = decl->generateCode(oldValues, compilerConstructs);
        if (v == nullptr) {
            return v;
        }
    }
    return v;
}
Value* var_d_c::generateCode(map<string, llvm::AllocaInst *> &Old_vals, Constructs *compilerConstructs)
{
    llvm::Function *TheFunction = compilerConstructs->Builder->GetInsertBlock()->getParent();
    for (const auto &var : names) {
        llvm::Value *initval = nullptr;
        llvm::AllocaInst *Alloca = nullptr;
        if (Type1 == "int") {
            initval = ConstantInt::get(compilerConstructs->Context, APInt(32, 0));
            Alloca = compilerConstructs->CreateEntryBlockAlloca(TheFunction, var, "int");
        } else if (Type1 == "boolean") {
            initval = ConstantInt::get(compilerConstructs->Context, APInt(1, 0));
            Alloca = compilerConstructs->CreateEntryBlockAlloca(TheFunction, var, "boolean");
        }
        compilerConstructs->Builder->CreateStore(initval, Alloca);
        /* Store the old value to old_vals and new value to named values */
        Old_vals[var] = compilerConstructs->NamedValues[var];
        compilerConstructs->NamedValues[var] = Alloca;
    }
    Value *v = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
    return v;
}
Value *statements_c::generateCode(Constructs* compilerConstructs)
{
    Value *v = ConstantInt::get(compilerConstructs->Context, llvm::APInt(32, 1));
    for (auto &stmt : stats_list) {
        v = stmt->generateCode(compilerConstructs);
    }
    return v;
}
Value *statement_c::generateCode(Constructs* compilerConstructs)
{
    Value *v=nullptr;
    if(type==1)
    {
        v = ass->generateCode(compilerConstructs);
    }
    if(type==3)
    {
        Value *cond = e_first->generateCode(compilerConstructs);
        if (cond == nullptr) {
            compilerConstructs->errors++;
            return reportError("Invalid Expression in the IF");
        }

        /* Create blocks for if, else and next part of the code */
        Function *TheFunction = compilerConstructs->Builder->GetInsertBlock()->getParent();
        BasicBlock *ifBlock = BasicBlock::Create(compilerConstructs->Context, "if", TheFunction);
        BasicBlock *elseBlock = BasicBlock::Create(compilerConstructs->Context, "else");
        BasicBlock *nextBlock = BasicBlock::Create(compilerConstructs->Context, "ifcont");
        BasicBlock *otherBlock = elseBlock;
        bool ret_if = b_first->has_return(), ret_else = false;
        bool break_if=b_first->has_break();
        bool continue_if=b_first->has_continue();
        /// Create a conditional break and an insert point
        if (b_second == nullptr) {
            otherBlock = nextBlock;
        }

        compilerConstructs->Builder->CreateCondBr(cond, ifBlock, otherBlock);
        compilerConstructs->Builder->SetInsertPoint(ifBlock);

        /// generate the code for if block
        Value *if_val = b_first->generateCode(compilerConstructs);
        if (if_val == nullptr) {
            return nullptr;
        }
        cout<<ret_if<<" "<<break_if<<" "<<continue_if<<endl;
        /// Create a break for next part of the code after else block

        if (!ret_if && !break_if && !continue_if) {
            compilerConstructs->Builder->CreateBr(nextBlock);
        }

        ifBlock = compilerConstructs->Builder->GetInsertBlock();
        /// Create insert point for else block

        Value *else_val = nullptr;

        if (b_second != nullptr) {
            /// Generate code for else block
            TheFunction->getBasicBlockList().push_back(elseBlock);
            compilerConstructs->Builder->SetInsertPoint(elseBlock);
            else_val = b_second->generateCode(compilerConstructs);
            if (else_val == nullptr) {
                return nullptr;
            }
            ret_else = b_second->has_return();
            cout<<"Else block "<<ret_else<<endl;
            if (!ret_else)
                compilerConstructs->Builder->CreateBr(nextBlock);
        }
        // Create a break for the next part of the code
        TheFunction->getBasicBlockList().push_back(nextBlock);
        compilerConstructs->Builder->SetInsertPoint(nextBlock);
        if (ret_else && ret_if) {
            // if both if and else block have a return statement create a dummy instruction to hold a next block
            Type *retType = compilerConstructs->Builder->GetInsertBlock()->getParent()->getReturnType();
            if (retType == Type::getVoidTy(compilerConstructs->Context))
                compilerConstructs->Builder->CreateRetVoid();
            else {
                compilerConstructs->Builder->CreateRet(ConstantInt::get(compilerConstructs->Context, APInt(32, 0)));
            }
        }
        Value *V = ConstantInt::get(compilerConstructs->Context, APInt(32, 0));
        return V;
    }
    if(type==5)
    {
        Value *start = e_first->generateCode(compilerConstructs);
        if (start == nullptr) {
            return nullptr;
        }
        if (e_first->type==0) {
            start = compilerConstructs->Builder->CreateLoad(start);
        }
        /* Get the parent method of this for loop */
        Function *TheFunction = compilerConstructs->Builder->GetInsertBlock()->getParent();
        /* Create memory for the loop variable */
        llvm::AllocaInst *Alloca = compilerConstructs->CreateEntryBlockAlloca(TheFunction, a, string("int"));
        compilerConstructs->Builder->CreateStore(start, Alloca);

        Value *step_val = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
        BasicBlock *pre_header_basic_block = compilerConstructs->Builder->GetInsertBlock();
        BasicBlock *loop_body = BasicBlock::Create(compilerConstructs->Context, "loop", TheFunction);
        BasicBlock *afterBB = BasicBlock::Create(compilerConstructs->Context, "afterloop", TheFunction);
        compilerConstructs->Builder->CreateBr(loop_body);
        compilerConstructs->Builder->SetInsertPoint(loop_body);

        PHINode *Variable = compilerConstructs->Builder->CreatePHI(Type::getInt32Ty(compilerConstructs->Context), 2,a);
        Variable->addIncoming(start, pre_header_basic_block);
        /* Store the old value */
        Value *cond = e_second->generateCode(compilerConstructs);
        if (cond == nullptr) {
            compilerConstructs->errors++;
            return reportError("Invalid Condition");
        }

        // Check if condition is a location
        if (e_second->type==0) {
            cond = compilerConstructs->Builder->CreateLoad(cond);
        }
        compilerConstructs->loops->push(new loopInfo(afterBB, loop_body, cond, a, Variable));
        llvm::AllocaInst *OldVal = compilerConstructs->NamedValues[a];
        compilerConstructs->NamedValues[a] = Alloca;
        /* Generate the code for the body */
        if (b_first->generateCode(compilerConstructs) == nullptr) {
            return nullptr;
        }

        Value *cur = compilerConstructs->Builder->CreateLoad(Alloca, a);
        Value *next_val = compilerConstructs->Builder->CreateAdd(cur, step_val, "NextVal");
        compilerConstructs->Builder->CreateStore(next_val, Alloca);
        cond = compilerConstructs->Builder->CreateICmpSLT(next_val, cond, "loopcondition");
        BasicBlock *loopEndBlock = compilerConstructs->Builder->GetInsertBlock();
        compilerConstructs->Builder->CreateCondBr(cond, loop_body, afterBB);
        compilerConstructs->Builder->SetInsertPoint(afterBB);
        Variable->addIncoming(next_val, loopEndBlock);

        if (OldVal) {
            compilerConstructs->NamedValues[a] = OldVal;
        } else {
            compilerConstructs->NamedValues.erase(a);
        }
        llvm::Value *V = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
        return V;
    }
    if(type==6 or type==7)
    {
        llvm::Value *V = nullptr;
        if (type==7) {
            /// Generate IR for expression to be returned
            V = e_first->generateCode(compilerConstructs);
            if (e_first->type==0) {
                /// Generate IR for returning it
                V = compilerConstructs->Builder->CreateLoad(V);
            }
            compilerConstructs->Builder->CreateRet(V);
            return V;
        }
        compilerConstructs->Builder->CreateRetVoid();
        return V;
    }
    if(type==8)
    {
        llvm::Value *V = llvm::ConstantInt::get(compilerConstructs->Context, llvm::APInt(32, 1));
        loopInfo *currentLoop = compilerConstructs->loops->top();
        compilerConstructs->Builder->CreateBr(currentLoop->getAfterBlock());
        return V;
    }
    if(type==9)
    {
        llvm::Value *V = llvm::ConstantInt::get(compilerConstructs->Context, llvm::APInt(32, 1));
        loopInfo *currentLoop = compilerConstructs->loops->top();
        string var = currentLoop->getLoopVariable();
        AllocaInst *Alloca = compilerConstructs->NamedValues[var];
        Value *step_val = ConstantInt::get(compilerConstructs->Context, APInt(32, 1));
        Value *cur = compilerConstructs->Builder->CreateLoad(Alloca, var);
        Value *next_val = compilerConstructs->Builder->CreateAdd(cur, step_val, "NextVal");
        compilerConstructs->Builder->CreateStore(next_val, Alloca);
        llvm::Value *cond = compilerConstructs->Builder->CreateICmpULE(next_val, currentLoop->getCondition(),
                "loopcondition");
        BasicBlock *loopEndBlock = compilerConstructs->Builder->GetInsertBlock();
        compilerConstructs->Builder->CreateCondBr(cond, currentLoop->getCheckBlock(), currentLoop->getAfterBlock());
        return V;
    }
    if(type==2)
    {
        v = ff->generateCode(compilerConstructs);
    }
    if(type==10)
    {
        v = b_first->generateCode(compilerConstructs);
    }
    return v;
}
Value* function_call_c::generateCode(Constructs *compilerConstructs)
{
    if(type==1)
    {
        Function *calle = compilerConstructs->TheModule->getFunction(name);
        if (calle == nullptr) {
            compilerConstructs->errors++;
            return reportError("Unknown Function name" + name);
        }
        /* Check if required number of parameters are passed */
        vector<class expr_c*> args_listt;
        //  if(pp->call_expr_list.size()!=0)
        args_listt = pp->call_expr_list;
        if (calle->arg_size() != args_listt.size()) {
            compilerConstructs->errors++;
            return reportError("Incorrect Number of Parameters Passed");
        }
        /// Generate the code for the arguments
        vector<Value *> Args;
        for (auto &arg : args_listt) {
            Value *argVal = arg->generateCode(compilerConstructs);
            if (arg->type == 0) {
                argVal = compilerConstructs->Builder->CreateLoad(argVal);
            }
            if (argVal == nullptr) {
                compilerConstructs->errors++;
                reportError("Argument is not valid");
                return nullptr;
            }
            Args.push_back(argVal);
        }
        // Reverse the order of arguments as the parser parses in the reverse order
        // std::reverse(Args.begin(), Args.end());
        // Generate the code for the function call
        Value *v = compilerConstructs->Builder->CreateCall(calle, Args);
        return v;
    }
    if(type==2)
    {
        //  cout<<"TYPE2"<<"                      "<<"ERER"<<meth<<endl;
        std::vector<llvm::Type *> argTypes;
        std::vector<Value *> Args;
        std::vector<class callout_arg_c *> args_list;
        if(cc->callout_arg_list.size()!=0)
            args_list= cc->callout_arg_list;
        /**
         * Iterate through the arguments and generate the code required for each one of them
         */
        for (auto &i : args_list) {
            Value *tmp = i->generateCode(compilerConstructs);
            if (tmp == nullptr) {
                return nullptr;
            }
            Args.push_back(tmp);
            argTypes.push_back(tmp->getType());
        }
        /* Generate the code for the function execution */
        llvm::ArrayRef<llvm::Type *> argsRef(argTypes);
        llvm::ArrayRef<llvm::Value *> funcargs(Args);
        llvm::FunctionType *FType = FunctionType::get(Type::getInt32Ty(compilerConstructs->Context), argsRef, false);
        Constant *func = compilerConstructs->TheModule->getOrInsertFunction(meth, FType);
        if (!func) {
            return reportError("Error in inbuilt function. Unknown Function name " + meth);
        }
        Value *v = compilerConstructs->Builder->CreateCall(func, funcargs);
        return v;
    }
}
Value *callout_arg_c::generateCode(Constructs *compilerConstructs)
{
    if (exp1 == nullptr && str=="") {
        compilerConstructs->errors++;
        return reportError("Invalid Callout Arg");
    }
    Value *v;
    if(type==0)
    {
        v = exp1->generateCode(compilerConstructs);
        if (exp1->type==0) {

            v = compilerConstructs->Builder->CreateLoad(v);
        }
    }
    else
    {
        //cout<<str<<"                                                 "<<"$"<<endl;
        v = compilerConstructs->Builder->CreateGlobalStringPtr(str);
    }
    return v;
}
Value* assignment_c::generateCode(Constructs *compilerConstructs)
{

    Value *cur = compilerConstructs->NamedValues[ll->a];

    if (cur == nullptr) {
        cur = compilerConstructs->TheModule->getGlobalVariable(ll->a);
    }
    if (cur == nullptr) {
        compilerConstructs->errors++;
        return reportError("Unknown Variable Name " + ll->a);
    }

    Value *val = ee->generateCode(compilerConstructs);
    if (ee->type==0) {
        val = compilerConstructs->Builder->CreateLoad(val);
    }

    Value *lhs = ll->generateCode(compilerConstructs);
    cur = compilerConstructs->Builder->CreateLoad(lhs);


    if (val == nullptr) {
        compilerConstructs->errors++;
        return reportError("Error in right hand side of the Assignment");
    }
    if (a =="+=") {
        val = compilerConstructs->Builder->CreateAdd(cur, val, "addEqualToTmp");
    } else if (a== "-=") {
        val = compilerConstructs->Builder->CreateSub(cur, val, "subEqualToTmp");
    }
    return compilerConstructs->Builder->CreateStore(val, lhs);
}
Value *expr_c::generateCode(Constructs* compilerConstructs)
{
    if(type==2)
    {
        Value *left = first->generateCode(compilerConstructs);
        Value *right = second->generateCode(compilerConstructs);
        if (first->type == 0) {
            left = compilerConstructs->Builder->CreateLoad(left);
        }
        if (second->type == 0) {
            right = compilerConstructs->Builder->CreateLoad(right);
        }
        string opr=operato;
        if (left == 0) {
            compilerConstructs->errors++;
            return reportError("Error in left operand of " + opr);
        } else if (right == 0) {
            compilerConstructs->errors++;
            return reportError("Error in right operand of " + opr);
        }
        Value *v = nullptr;
        if (opr == "+") {
            v = compilerConstructs->Builder->CreateAdd(left, right, "addtmp");
        } else if (opr == "-") {
            v = compilerConstructs->Builder->CreateSub(left, right, "subtmp");
        } else if (opr == "*") {
            v = compilerConstructs->Builder->CreateMul(left, right, "multmp");
        } else if (opr == "/") {
            v = compilerConstructs->Builder->CreateSDiv(left, right, "divtmp");
        } else if (opr == "%") {
            v = compilerConstructs->Builder->CreateSRem(left, right, "modtmp");
        } else if (opr == "<") {
            v = compilerConstructs->Builder->CreateICmpSLT(left, right, "ltcomparetmp");
        } else if (opr == ">") {
            v = compilerConstructs->Builder->CreateICmpSGT(left, right, "gtcomparetmp");
        } else if (opr == "<=") {
            v = compilerConstructs->Builder->CreateICmpSLE(left, right, "lecomparetmp");
        } else if (opr == ">=") {
            v = compilerConstructs->Builder->CreateICmpSGE(left, right, "gecomparetmp");
        } else if (opr == "==") {
            v = compilerConstructs->Builder->CreateICmpEQ(left, right, "equalcomparetmp");
        } else if (opr == "!=") {
            v = compilerConstructs->Builder->CreateICmpNE(left, right, "notequalcomparetmp");
        }
        else if (opr=="&&"){
            v = compilerConstructs->Builder->CreateAnd(left, right, "andtmp");
        }
        else if (opr=="||"){
            v = compilerConstructs->Builder->CreateOr(left, right, "ortmp");
        }
        return v;
    }
    else if(type==1)
    {
        Value *v = first->generateCode(compilerConstructs);
        if (first->type==0) {
            v = compilerConstructs->Builder->CreateLoad(v);
        }

        if (operato == "-") {
            return compilerConstructs->Builder->CreateNeg(v, "negtmp");
        } else if (operato == "!") {
            return compilerConstructs->Builder->CreateNot(v, "nottmp");
        }
    }
    else if(type==0)
    {
        Value *v = loc->generateCode(compilerConstructs);
        return v;
    }
    else if(type==3)
    {
        Value *v = first->generateCode(compilerConstructs);
        return v;
    }
    else if(type==4)
    {
        Value *v = lit->generateCode(compilerConstructs);
        return v;
    }
    else if(type==10)
    {
        Value *v = ff->generateCode(compilerConstructs);
        return v;
    }
}


Value *location_c::generateCode(Constructs* compilerConstructs)
{
    Value *V = compilerConstructs->NamedValues[a];
    if (V == nullptr)
    {
        V = compilerConstructs->TheModule->getNamedGlobal(a);
    }
    if (V == nullptr)
    {
        compilerConstructs->errors++;
        return reportError("Unknown Variable name " + a);
    }
    /* If location is variable return the code generated */
    if (this->type == 1) {
        return V;
    }
    /* Check if we have an index for array */
    if (this->er == nullptr) {
        return reportError("Invalid array index");
    }
    /* Generate the code for index of the array */
    Value *index = er->generateCode(compilerConstructs);
    if (er->type == 0) {
        index = compilerConstructs->Builder->CreateLoad(index);
    }
    /* If index is invalid then report error */
    if (index == nullptr) {
        return reportError("Invalid array index");
    }
    /* Generate the code required for accessing the array at the given index */
    vector<Value *> array_index;
    array_index.push_back(compilerConstructs->Builder->getInt32(0));
    array_index.push_back(index);
    V = compilerConstructs->Builder->CreateGEP(V, array_index, a + "_Index");
    return V;
}
Value* literal_c::generateCode(Constructs *compilerConstructs)
{
    Value *v=nullptr;
    if(flag==1)
    {
        Value *v = ConstantInt::get(compilerConstructs->Context, llvm::APInt(32, static_cast<uint64_t>(a)));
        return v;
    }
    if(flag==2)
    {
        Value *v = ConstantInt::get(compilerConstructs->Context, llvm::APInt(1, b));
        return v;
    }
    return v;
}
