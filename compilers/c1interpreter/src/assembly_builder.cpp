
#include "assembly_builder.h"

#include <vector>

using namespace llvm;
using namespace c1_recognizer::syntax_tree;



void assembly_builder::visit(assembly &node)
{
    in_global = true;
    // random initialize, avoid segmentation fault
    value_result = ConstantInt::get(Type::getInt32Ty(context), 233);
    bb_count = 1;
    for(auto ptr_def : node.global_defs)
        ptr_def->accept(*this);
}

void assembly_builder::visit(func_def_syntax &node)
{
    in_global = false;
    if(functions.find(node.name) != functions.end()){
        std::string error_info = "Function " + node.name + " repeatly defined.";
        err.error(node.line, node.pos, error_info);
        error_flag = true;
        return;
    }
    Function* func = Function::Create(FunctionType::get(Type::getVoidTy(context), std::vector<Type *>(), false),
                                     GlobalValue::LinkageTypes::ExternalLinkage,
                                     node.name, module.get());
    functions[node.name] = func;
    current_function = func;
    auto func_entry = BasicBlock::Create(context, "entry", func);
    builder.SetInsertPoint(func_entry);
    node.body->accept(*this);
    // return
    builder.CreateRetVoid();
    builder.ClearInsertionPoint();
    in_global = true;
}

void assembly_builder::visit(cond_syntax &node)
{
    constexpr_expected = false;
    node.lhs->accept(*this);
    auto lhs_val = value_result;
    node.rhs->accept(*this);
    auto rhs_val = value_result;
    Value* cmp_res;
    switch(node.op){
    case relop::equal:
        cmp_res = builder.CreateICmpEQ(lhs_val, rhs_val);
        break;
    case relop::non_equal:
        cmp_res = builder.CreateICmpNE(lhs_val, rhs_val);
        break;
    case relop::less:
        cmp_res = builder.CreateICmpSLT(lhs_val, rhs_val);
        break;
    case relop::less_equal:
        cmp_res = builder.CreateICmpSLE(lhs_val, rhs_val);
        break;
    case relop::greater:
        cmp_res = builder.CreateICmpSGT(lhs_val, rhs_val);
        break;
    case relop::greater_equal:
        cmp_res = builder.CreateICmpSGE(lhs_val, rhs_val);
        break;
    }
    value_result = cmp_res;
}

void assembly_builder::visit(binop_expr_syntax &node)
{
    if(constexpr_expected){ // const type
        node.lhs->accept(*this);
        auto lhs_val = const_result;
        node.rhs->accept(*this);
        auto rhs_val = const_result;
        switch(node.op){
        case binop::plus:
            const_result = lhs_val + rhs_val;
            break;
        case binop::minus:
            const_result = lhs_val - rhs_val;
            break;
        case binop::multiply:
            const_result = lhs_val * rhs_val;
            break;
        case binop::divide:
            if(rhs_val == 0)
                std::cerr << node.line << ":" << node.pos
                          << ": warning: division by zero is undefined [-Wdivision-by-zero]\n";
            const_result = lhs_val / rhs_val;
            break;
        case binop::modulo:
            if(rhs_val == 0)
                std::cerr << node.line << ":" << node.pos
                          << ": warning: modulo by zero is undefined [-Wmodulo-by-zero]\n";
            const_result = lhs_val % rhs_val;
        }
    }
    else{   // value result
        node.lhs->accept(*this);
        auto lhs_val = value_result;
        node.rhs->accept(*this);
        auto rhs_val = value_result;
        switch(node.op){
        case binop::plus:
            value_result = builder.CreateAdd(lhs_val, rhs_val);
            break;
        case binop::minus:
            value_result = builder.CreateSub(lhs_val, rhs_val);
            break;
        case binop::multiply:
            value_result = builder.CreateMul(lhs_val, rhs_val);
            break;
        case binop::divide:
            value_result = builder.CreateSDiv(lhs_val, rhs_val);
            break;
        case binop::modulo:
            value_result = builder.CreateSRem(lhs_val, rhs_val);
        }
    }
}

void assembly_builder::visit(unaryop_expr_syntax &node)
{
    node.rhs->accept(*this);
    if(node.op == unaryop::minus){
        if(constexpr_expected){
            const_result = -const_result;
        }
        else{
            Value* const_int32_0 = ConstantInt::get(Type::getInt32Ty(context), 0);
            value_result = builder.CreateSub(const_int32_0, value_result);
        }
    }
    // no need for changing unaryop::plus
}

void assembly_builder::visit(lval_syntax &node)
{
    // declare check
    auto look_res = lookup_variable(node.name);
    if(!std::get<0>(look_res)){
        std::string error_info = node.name + " is undeclared.";
        err.error(node.line, node.pos, error_info);
        error_flag = true;
        return;
    }
    // type check
    if(constexpr_expected){ // should have const value
            err.error(node.line, node.pos, "Const value expected.");
            error_flag = true;
            return;
    }
    if(!node.array_index){
        // check whether it is a variable type
        if(std::get<2>(look_res)){
            err.error(node.line, node.pos, "\"" + node.name + "\" is not a variable");
            error_flag = true;
            return;
        }
        if(lval_as_rval){ // used for rval
            value_result = builder.CreateLoad(std::get<0>(look_res));
        }
        else{           // used for lval
            if(std::get<1>(look_res)){  // is a const variable
                err.error(node.line, node.pos, "\"" + node.name + "\" const-value can't be lval.");
                error_flag = true;
                return;
            }
            value_result = std::get<0>(look_res);
        }
    }
    else{
        // check whether it is a array type
        if(!std::get<2>(look_res)){
            err.error(node.line, node.pos, "\"" + node.name + "\" is not an array");
            error_flag = true;
            return;
        }
        bool temp_lar = lval_as_rval;
        lval_as_rval = true;
        node.array_index->accept(*this);
        lval_as_rval = temp_lar;
        std::vector<Value*> index;
        index.push_back((Value*)ConstantInt::get(Type::getInt32Ty(context), 0));
        index.push_back(value_result);
        auto array_ptr = builder.CreateGEP(std::get<0>(look_res), index);
        if(lval_as_rval) // used for rval
            value_result = builder.CreateLoad(array_ptr);
        else{
            if(std::get<1>(look_res)){  // is a const array
                err.error(node.line, node.pos, "const-value can't be lval.");
                error_flag = true;
                return;
            }
            value_result = array_ptr;
        }
    }
}

void assembly_builder::visit(literal_syntax &node)
{
    if(constexpr_expected)
        const_result = node.number;
    else
        value_result = ConstantInt::get(Type::getInt32Ty(context), node.number);
}

void assembly_builder::visit(var_def_stmt_syntax &node)
{
    if(variables.front().count(node.name)){
        std::string error_info = "variable \"" + node.name + "\" has already declared.";
        err.error(node.line, node.pos, error_info);
        error_flag = true;
        return;
    }
    if(!node.array_length){ // variable
        const_result = 0; // only pre-initialize global variables
        //value_result = ConstantInt::get(Type::getInt32Ty(module->getContext()), const_result);
        Value * var;
        if(in_global){
            constexpr_expected = true;
            if(!node.initializers.empty())
                node.initializers[0]->accept(*this);
            var = new GlobalVariable(*module,
                                    Type::getInt32Ty(module->getContext()),
                                    node.is_constant,
                                    GlobalValue::ExternalLinkage,
                                    ConstantInt::get(Type::getInt32Ty(module->getContext()), const_result),
                                    node.name);
        }
        else{
            constexpr_expected = false; 
            var = builder.CreateAlloca(Type::getInt32Ty(context), nullptr, node.name);
            if(!node.initializers.empty()){
                node.initializers[0]->accept(*this);
                builder.CreateStore(value_result, var);
            }
        }
        declare_variable(node.name, var, node.is_constant, false);
    }
    else{   // array
        constexpr_expected = true;
        node.array_length->accept(*this);
        unsigned array_len = const_result , init_len = node.initializers.size();
        // array definition check
        if(const_result < 0){
            err.error(node.line, node.pos, node.name + " declared as an array with a negative size");
            error_flag = true;
            return;
        }
        if(init_len > array_len){
            err.error(node.line, node.pos, "excess elements in array initializer");
            error_flag = true;
            return;
        }
        Value *array;
        // global array definition
        if(in_global){
            // set initializers
            std::vector<Constant *> init_array;
            for(unsigned len = 0; len < array_len; ++len){
                if(len < init_len){
                    node.initializers[len]->accept(*this); // init value will store in const_result
                    Constant* init = ConstantInt::get(Type::getInt32Ty(context), const_result);
                    init_array.push_back(init);
                }
                else{
                    Constant* init_0 = ConstantInt::get(Type::getInt32Ty(context), 0);
                    init_array.push_back(init_0);
                }
            }
            // create global array
            array = new GlobalVariable(*module,
                                      ArrayType::get(Type::getInt32Ty(context), array_len), 
                                      node.is_constant,
                                      GlobalValue::ExternalLinkage,
                                      ConstantArray::get(ArrayType::get(Type::getInt32Ty(context), array_len), init_array),
                                      node.name,
                                      nullptr,
                                      GlobalValue::NotThreadLocal
                                      );
        }
        else{
            // set initilizers
            constexpr_expected = false;
            array = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), array_len), nullptr, node.name);
            Value* element;
            std::vector<Value*> index;
            index.push_back((Value*)ConstantInt::get(Type::getInt32Ty(context), 0));
            for(unsigned len = 0; len < array_len && node.initializers.size(); ++len){
                // get index
                index.push_back((Value*)ConstantInt::get(Type::getInt32Ty(context), len));
                element = builder.CreateGEP(array, index);
                index.pop_back();
                if(len < init_len){
                    node.initializers[len]->accept(*this); // init value will store in value_result
                    builder.CreateStore(value_result, element);
                }
                else{
                    auto init_0 = ConstantInt::get(Type::getInt32Ty(context), 0);
                    builder.CreateStore(init_0, element);
                }
            }
        }
        declare_variable(node.name, array, node.is_constant, true);
    }
}

void assembly_builder::visit(assign_stmt_syntax &node)
{
    constexpr_expected = false;
    lval_as_rval = false;
    node.target->accept(*this);
    auto tar = value_result;
    lval_as_rval = true;
    constexpr_expected = false;
    node.value->accept(*this);
    // store the value into tar
    builder.CreateStore(value_result, tar); // tar = value_result
}

void assembly_builder::visit(func_call_stmt_syntax &node)
{
    if(functions.find(node.name) == functions.end()){
        std::string error_info = "function " + node.name + "() is not declared";
        err.error(node.line, node.pos, error_info);
        error_flag = true;
        return;
    }
    auto func = functions[node.name];
    builder.CreateCall(func); // no param & return value
}

void assembly_builder::visit(block_syntax &node)
{
    enter_scope();
    for(auto ptr_stmt : node.body)
        ptr_stmt->accept(*this);
    exit_scope();
}

void assembly_builder::visit(if_stmt_syntax &node)
{
    auto then_body = BasicBlock::Create(context, "if.then" + std::to_string(bb_count++), current_function);
    auto else_body = BasicBlock::Create(context, "if.else" + std::to_string(bb_count++), current_function);
    // if.cond
    node.pred->accept(*this);
    builder.CreateCondBr(value_result, then_body, else_body);
    // if.then_body
    builder.SetInsertPoint(then_body);
    node.then_body->accept(*this);
    // if.else_body or future_body
    if(!node.else_body){ // now else_body as future bb insert point
        builder.CreateBr(else_body);
        builder.SetInsertPoint(else_body);
        return;
    }
    else{
        auto future = BasicBlock::Create(context, "future" + std::to_string(bb_count++), current_function);
        builder.CreateBr(future);
        // if.else_body
        builder.SetInsertPoint(else_body);
        node.else_body->accept(*this);
        builder.CreateBr(future);
        // future body, for next stmt using
        builder.SetInsertPoint(future);
    }
}

void assembly_builder::visit(while_stmt_syntax &node)
{
    auto cond = BasicBlock::Create(context, "while.cond" + std::to_string(bb_count++), current_function);
    auto while_body = BasicBlock::Create(context, "while.body" + std::to_string(bb_count++), current_function);
    auto out_body = BasicBlock::Create(context, "while.out" + std::to_string(bb_count++), current_function);
    builder.CreateBr(cond);
    // while.cond
    builder.SetInsertPoint(cond);
    node.pred->accept(*this);
    builder.CreateCondBr(value_result, while_body, out_body);
    // while.body
    builder.SetInsertPoint(while_body);
    node.body->accept(*this);
    builder.CreateBr(cond);
    // while.out
    builder.SetInsertPoint(out_body);
}

void assembly_builder::visit(empty_stmt_syntax &node)
{
}
