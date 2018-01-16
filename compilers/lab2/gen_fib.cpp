#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>

#include <memory>
#include <map>

using namespace llvm;

LLVMContext context;
IRBuilder<> builder(context);
auto module = new Module("fib_cal", context);
Function* func_fib = Function::Create(FunctionType::get(Type::getInt32Ty(context), Type::getInt32Ty(context), false),
                                      GlobalValue::LinkageTypes::ExternalLinkage,
                                      "fib", module);
Function* func_main = Function::Create(FunctionType::get(Type::getInt32Ty(context), Type::getInt32Ty(context), false),
                                       GlobalValue::LinkageTypes::ExternalLinkage,
                                       "main", module);

void FuncFib(LLVMContext& context, IRBuilder<> &builder, Module *module){
    // ==================================== Function fib ========================================
    std::map<std::string, Value*> FibSymbolValue;
    auto fib_entry = BasicBlock::Create(context, "", func_fib);
    auto fib_check_1 = BasicBlock::Create(context, "check_1", func_fib);
    auto fib_cal_recursive = BasicBlock::Create(context, "cal_recursive", func_fib);
    auto fib_func_out = BasicBlock::Create(context, "func_out", func_fib);
    // set parameter name to 'n'
    for(auto &arg : func_fib->args()){
        arg.setName("n");
        FibSymbolValue["n"] = &arg;
    }
    // ================================== entry BB ==================================
    builder.SetInsertPoint(fib_entry);
    // line2
    auto var_1 = builder.CreateAlloca(Type::getInt32Ty(context), nullptr);
    var_1->setAlignment(4);
    // line3
    builder.CreateStore(FibSymbolValue["n"], var_1)->setAlignment(4);
    // line4
    Value* const_int32_0 = ConstantInt::get(Type::getInt32Ty(context), 0);
    Value* var_fib_cmp1 = builder.CreateICmpEQ(FibSymbolValue["n"], const_int32_0, "fib_cmp1");
    // line5
    builder.CreateCondBr(var_fib_cmp1, fib_func_out, fib_check_1);
    // ================================== check_1 BB ==================================
    builder.SetInsertPoint(fib_check_1);
    // line8
    Value* const_int32_1 = ConstantInt::get(Type::getInt32Ty(context), 1);
    Value* var_cmp_res1 = builder.CreateICmpEQ(FibSymbolValue["n"], const_int32_1, "cmp_res1");
    // line9
    builder.CreateCondBr(var_cmp_res1, fib_func_out, fib_cal_recursive);
    // ================================== cal_recursive BB ==================================
    builder.SetInsertPoint(fib_cal_recursive);
    // line12
    auto var_cal1 = builder.CreateSub(FibSymbolValue["n"], const_int32_1, "cal1", false, true);
    //line 13
    auto var_res1 = builder.CreateCall(func_fib, var_cal1, "res1");
    //line 14
    Value* const_int32_2 = ConstantInt::get(Type::getInt32Ty(context), 2);
    auto var_cal2 = builder.CreateSub(FibSymbolValue["n"], const_int32_2, "cal2", false, true);
    //line 15
    auto var_res2 = builder.CreateCall(func_fib, var_cal2, "res2");
    //line 16
    auto var_res = builder.CreateAdd(var_res1, var_res2, "res", false, true);
    //line 17
    builder.CreateStore(var_res, var_1)->setAlignment(4);
    //line 18
    builder.CreateBr(fib_func_out);
    // ================================== func_out BB ==================================
    builder.SetInsertPoint(fib_func_out);
    //line 21
    auto var_out = builder.CreateLoad(var_1, "out");
    var_out->setAlignment(4);
    //line 22
    builder.CreateRet(var_out);
    builder.ClearInsertionPoint();
}

void FuncMain(LLVMContext& context, IRBuilder<> &builder, Module *module){
    // ====================================== function main =================================
    auto main_entry = BasicBlock::Create(context, "", func_main);
    auto main_loop_control = BasicBlock::Create(context, "loop.control", func_main);
    auto main_loop_content = BasicBlock::Create(context, "loop.content", func_main);
    auto main_func_out =BasicBlock::Create(context, "func_out", func_main);
    // ===================================== entry BB ==================================
    builder.SetInsertPoint(main_entry);
    // line26
    auto var_1 = builder.CreateAlloca(Type::getInt32Ty(context), nullptr);
    var_1->setAlignment(4);
    // lin27
    auto var_2 = builder.CreateAlloca(Type::getInt32Ty(context), nullptr);
    var_2->setAlignment(4);
    // line28
    auto var_3 = builder.CreateAlloca(Type::getInt32Ty(context), nullptr);
    var_3->setAlignment(4);
    // line 29 - 31
    Value* const_int32_0 = ConstantInt::get(Type::getInt32Ty(context), 0);
    builder.CreateStore(const_int32_0, var_1)->setAlignment(4);
    builder.CreateStore(const_int32_0, var_2)->setAlignment(4);
    builder.CreateStore(const_int32_0, var_3)->setAlignment(4);
    // line 32
    builder.CreateBr(main_loop_control);
    // ====================================== loop.control BB ============================
    builder.SetInsertPoint(main_loop_control);
    // lin35
    auto var_control_i = builder.CreateLoad(var_3, "control.i");
    var_control_i->setAlignment(4);
    // line36
    Value* const_int32_10 = ConstantInt::get(Type::getInt32Ty(context), 10);
    auto var_cmp_res2 = builder.CreateICmpSLT(var_control_i, const_int32_10, "cmp_res2");
    // line37
    builder.CreateCondBr(var_cmp_res2, main_loop_content, main_func_out);
    // ====================================== loop.content BB ============================
    builder.SetInsertPoint(main_loop_content);
    // line40
    auto var_pre_i = builder.CreateLoad(var_3, "pre.i");
    var_pre_i->setAlignment(4);
    // line41
    auto var_res1 = builder.CreateCall(func_fib, var_pre_i, "res1");
    // line42
    auto var_pre_x = builder.CreateLoad(var_2, "pre.x");
    var_pre_x->setAlignment(4);
    // line43
    auto var_new_x = builder.CreateAdd(var_res1, var_pre_x, "new.x", false, true);
    // line44
    builder.CreateStore(var_new_x, var_2)->setAlignment(4);
    // line45
    Value* const_int32_1 = ConstantInt::get(Type::getInt32Ty(context), 1);
    auto var_new_i = builder.CreateAdd(var_pre_i, const_int32_1, "new.i", false, true);
    // line46
    builder.CreateStore(var_new_i, var_3)->setAlignment(4);
    // line47
    builder.CreateBr(main_loop_control);
    // ====================================== loop.content BB ============================
    builder.SetInsertPoint(main_func_out);
    // line50
    auto var_out = builder.CreateLoad(var_2, "out");
    var_out->setAlignment(4);
    // line51
    builder.CreateRet(var_out);
    builder.ClearInsertionPoint();
}

int main(){
    FuncFib(context, builder, module);
    FuncMain(context, builder, module);
    module->print(outs(), nullptr);
    delete module;
    return 0;
}