# lab1-2 Answer
PB15111672 林郅琦

## 实验内容
分析 antlr v4 处理左递归的方式以及支持左递归的类型

## 实验编译执行
* 本次实验环境: 
  * 操作系统 MacOS High Sierra
  * virtualenv (配置 python3.6)
  * pip3 以及 antlr4-python3-runtime 包
  * antlr4 和 grun 都能正常使用
* 编译前准备:
  * 使用 virtualenv：  

    `$virtualenv --python=python3.6 ~/python3`   

  * 激活 python3 虚拟环境

    `$source ~/python3/bin/activate`  

  * 使用 pip3 安装 antlr4-python3-runtime 包  

    `(python3)$pip3 install antlr4-python3-runtime`  

* 编译和执行：  
  * 对 MultFirst.g4:  

```  sh
  (python3)$antlr4 -Dlanguage=Python3 MultFirst.g4
  (python3)$python multfirst.py  
```

  * 对 PlusFirst.g4:  

```  sh
  (python3)$antlr4 -Dlanguage=Python3 PlusFirst.g4
  (python3)$python plusfirst.py
```

  * 编译 UnsupportedLeftRecursive (报错为正确情况):
```  sh
$antlr4 UnsupportedLeftRecursiveLexer.g4 UnsupportedLeftRecursiveParser.g4
```

  * 结束后关闭 python 虚拟环境:  

  `(python3)$deactive`  

* 执行过程：
  *  输入不带括号的含加法或乘法的计算表达式
  *  输出为根据不同 parser 对应的计算输出值

## 运行时图

* 同时运行 MultFirst 和 PlusFirst 后得到的结果图如下所示 
  ![res](res.jpg)

* 从上图可以看出，当使用 MultFirst 时，实际计算的表达式为 3 + （5 * 4） + 2 = 25 ，即符合数学中定义的加法乘法优先级
* 当使用 PlusFirst 时，实际计算的表达式为 (3 + 5) * (4 + 2) = 48, 此时加法的优先级高于乘法

## 分析

* 由实验结果可以看出，产生式 '|' 之间顺序不同会导致不同的结果。在 MultFirst 中，分析树为数学约定正确的优先级表现方式，即乘法(\*)优先于加法(+)，而在 PlusFirst 中，分析树的输出不符合数学约定正确的优先级表现方式，即加法(+)优先于乘法(\*)。 由此可以得出结论，在处理左递归时，antlr4 会默认优先匹配产生式 '|' 前面的内容，即 '|' 隐式决定了匹配式(在此含义为运算符)的优先级。

## Antlr v4 支持左递归类型

* 如果将类似  `CompUnit -> [ CompUnit ] ( Decl | FuncDef )` 的左递归 (即左递归第一项出现作为可选形式，不出现时为非左递归，出现时为左递归) 归类为间接左递归形式，则 antlr 能够支持所有直接左递归形式，而不支持间接左递归形式。
* 对于直接左递归形式，antlr 通过重写直接左递归产生式（类似书上的方法）来消除直接左递归。
* 实验过程（即实现 CompilationUnit) 已经证明了 A -> (A)? ... 这样的左递归 antlr4 不能够支持，test/test_cases/unsupport 测试示例将证明 antlr4 无法支持间接左递归, 其中的内容为:

```
s: a | Int;
a: b | Int;
b: s | Int;
```

* 支持与不支持原因分析:
  * 由于课上已经知道对直接左递归的消除有通用简单的公式，因此在实现上消除直接左递归可以非常简单。
  * 而间接左递归的消除方式并不简单，查询资料可得间接左递归式转化成直接左递归式要求文法不存在环和ε产生式，而并非所有的间接左递归式都能满足这样的性质，且即便满足了这样的性质在算法上实现也并不容易。

* 上式在编译时将出现报错:  
```
error(119): UnsupportedLeftRecursiveParser.g4::: The following sets of rules are mutually left-recursive [s, b, a]
```
