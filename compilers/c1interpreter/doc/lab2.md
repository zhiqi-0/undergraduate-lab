# Lab2 实验报告
PB15111672 林郅琦

## 实验环境
* 实验系统：MacOS High Sierra
* 实验参考编译器: clang 4.01

## 实验目的
* 利用 c1interpretor 访问者模式完成中间代码生成
* 熟悉访问者设计模式
* 熟悉中间代码生成

## 代码说明
* c1interpretor 下已经放置补充好后的 assembly_builder.cpp 文件。使用 lab2 给出的编译指令即可正常使用
* 测试示例说明：测试示例位于 c1interpretor/test_cases 下，其中 test1.c 提供了广泛的测试，并提供了已经注释的可能出现的各种应当报错错误情况，测试示例已经成功执行。（执行后如果输出为1~29同花顺序列，则执行成功）

## 实验设计
* 首先是访问者模式
  访问者模式是通过 accept 函数回调对应的 visit 函数，这个设计的好处是在进行 accept 时无需考虑访问者的类型，而只需要在 visit 函数中执行相关的代码即可。因此代码设计十分方便。
* 中间代码生成
  需要注意一下几点：
  * 全局变量应该在 assembly 类型中 accept 前设置 `in_global = true` 来指示为全局变量，之后在访问函数定义时重置为 false
  * 数组行为给出如下定义（具体行为与 clang 个别有所出入）
    * 数组定义时如果长度小于0则报错（等于0认为正确）
    * 数组初始化时如果如果初始化数据长度大于数组定义长度，则报错（实际上 clang 在编译 c 文件给 warning，在执行 c++ 文件给 error）
    * 数组访问不检查是否越界
    * 数组定义时数组长度如果给定变量（无论是否为 const），报错。（实际上 clang 和 gcc 都允许数组定义长度可以为 const 变量，此问题特地询问过曹助教）
    * 无论是全局数组还是局部数组变量，如果初始化数据长度小于数组定义长度时，剩下的数组初始化为0.
  *  变量作用域由 deque 内嵌 map 类型的 variable 符号表来维护，在进入一个 Block 时使用 `enter_scope()` 加入一张符号表，在离开一个 Block 时使用 `exit_scope()` 弹出当前符号表，查询符号表时遍历所有队列中的符号表，新增一个变量时需要查看当前（栈的最前面）符号表是否有这个符号，而不是遍历所有符号表中的 map。
  * 访问时需要特别注意 constexpr_expected 变量的设置，具体的：
    * 数组定义索引要求 `array_length` 为常量（即赋值不可以是变量，无论是否为 const），则要求返回值必须是 constexpr expected, 而在局部数组初始化列表中允许设置为为变量初始化，所以为 `constexpr_expr = false`, 而全局初始化不允许用变量进行初始化，因此 `constexpr_expr = true`
    * 赋值语句中需要设置 `constexpr_expected = false`，但是需要注意左值在 visit 过程中必须要检查是否为常量，若常量则必须报错，右值无所谓常量和变量，统一返回到 value_result 中进行调用
    * 其他地方无需再设置 constexpr_expected, 但是如 exp 等表达式进行运算时，应该结合 `constexpr_expected` 来考虑返回值为 `value_result` 还是 `const_result`
  * `lval_as_rval` 在赋值语句中会用到，访问前等号左边应设置为 false, 等号右边应设置为 true
  * 其他相关事项已经在 lab2 的实验文档中说明的很清楚了，具体实现按照 lab2 的 5 个步骤一次实现即可
* 类型检查
  由于 c1 语言只有 int，array，void 三种类型，而 void 只会用于函数申明，且在文法中已经规定，所以在 c1interpretor 类型检查实现中，无需再检查 void 类型，只需要检查 int 和 array 类型。 
  类型检查需要检查：
  * 当期待的值为 variable 时，查看从符号表中获得的变量是否为变量类型，如果是数组类型则报错
  * 当期待的值为 数组时（如 k[3], 则 k 期待为数组类型），则查看从符号表取出的变量是否为数组类型，如果是变量则报错
* SSA 设计
  * 总体设计：主要处理 if 语句和 while 语句。每次处理结束后使插入指针指向新的没有被插入的 BasicBlock 中，等待下个语句的执行操作。
  * if-then-else 语句
    * 为 then-body, else-body 分别创建两个 Basicblock， 进行逻辑跳转，注意由于 then 和 else 不可能再跳转回 if-cond 的 basicblock，所以不需要为 if-cond 进行 basicblock 创建，直接使用上一次函数的插入点进行 cond 语句插入即可。如果有 else，则还需新建一个 basicblock 来作为执行完这一套操作后的新的语句插入点，如果没有 else，则之前创建的 else-body 即可作为新的 basicblock 供下一条语句做插入使用
  * while 语句
    * 由于 while-body 需要无条件返回 while-cond, 所以方便起见，直接创建 while-cond, while-body, while-out 三个 basicblock，其中 while-out 供下一条语句进行插入操作。注意此处需要先跳转值 while-cond 再对 while-cond 进行 cond 插入。

## 实验结果
实验结果在提供的测试示例内均能正确执行。暂时没有发现执行错误。

## 问题记录
1. 问题描述：数组申明过程中，不清楚接口。
   解决方案：查看 llvm 手册以及相应源码，以及通过 clang 的 llvm ir 输出，发现数组类型的通用接口为 `ArrayType::get(Type::getInt32Ty(context), int array_len)`, 从而解决了数组申明的难点。
2. 通过助教给出的编译指令，原先在 MacOS High Sierra 下 lab1 中按助教指令无法成功执行的问题，现在可以通过添加 cmake 安装路径再进行 `$make install` 安装即可圆满解决。
3. 在测试过程中出现下面代码使程序崩溃：  
   ``` c
   int i = 1;
   int b[3];
   int b[i] = 2;
   ```
   解决方案：崩溃的地方在获得 b[i] 左值时，由于访问 lval 时，数组索引 i 也为 lval，而 i 此时应当作为右值处理，但是 b[i]访问期间 `lval_as_rval = false`，所以出现错误。只需要在访问 index 之前把当前 `lval_as_rval` 保存后并修改为 true, 访问结束后再改回到原来的值就可以。