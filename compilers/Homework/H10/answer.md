## 配置说明

本此两道题目均运行于：
* 操作系统： MacOS High Sierra
* 编译器： clang 4.0.1
* 编译参数: 问题1无，问题2  -O3（具体编译指令可见 Makefile 文件)

## 目录说明
本次两题的源码均在 test/ 目录下，分别为 test1.c(对应问题1)，test2.c（对应问题2)。  
编译可直接通过 `$make` 指令. 程序在 MacOS 操作系统下均能成功编译。

## 问题1
### 问题描述
类型检查在 C 程序编译过程中必不可少，在此过程中，编译器需要确定类型是否存在以及类型运算的合法性等问题。其中隐式类型转换是编译器检测到不同类型进行运算时所给出的一种解决方案。考虑下面一个完整的 C 语言程序：
``` c
#include <stdio.h>
int main(){
    int a = 2;
    unsigned b = 2;
    int count = 0;
    printf("start counting...\n");
    while(a + b >= 0){
        count = count + 1;
        a = a - 1;
    }
    printf("count result: %d\n", count);
    return 0;
}
```
回答以下问题：  
(a). a + b 产生的类型是什么？
(b). 最后程序的输出结果中 count 值是什么？并给出原因。  
### 问题参考答案
(a). 产生的类型为 unsigned int 类型
(b). 程序不会有输出结果。原因如下：由于 a + b 类型为 unsigned int 类型，此类型恒大于0，即使当 a = -3 时， 相加时会先将 a 转化为 unsigned int 类型，此时 a 不再是-3，而是一个很大的整数，所以 a + b 依旧大于等于0。  

[汇编代码参考]  
```
_main:                                  ## @main
## BB#0:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	calll	L0$pb
L0$pb:
	popl	%eax
	leal	L_str-L0$pb(%eax), %eax
	movl	%eax, (%esp)
	calll	_puts
	.p2align	4, 0x90
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	jmp	LBB0_1
```
从优化后的汇编结果来看，LBB0_1 这个 label 将陷入无限循环。

[考察知识点]： 类型转换

## 问题2
### 问题描述
编译器实现往往需要对代码进行优化。优化方案中，当发现一个函数内产生的中间变量没有被利用的情况时，或者某些语句不可能被执行时，那么这些语句可以视为无效语句，不会对程序运行造成任何影响，而只会徒增运算量，因此这些语句可以在优化过程中被删去。在早期 GCC 编译器实现时，GCC 编译器认为利用 C 语言的未定义行为对代码进行优化是合理的，对性能提升是非常重要的。在利用未定义行为对代码的优化方案中，其中一种情况为：当出现一条赋值语句，其中指针指向的一个数值赋值给另外一个变量时（如 int i = *p;)，编译器便认定此时指针(p)已经指向一个数值，因而 p 非 0，则可以针对这个特性减少一些代码的执行操作(-O3 编译选项）。请看以下 C 语言程序：  
``` c
#include<stdio.h>
void test(int *p){
    int c = *p;
    if(p == 0)
        return;
    *p = 2333;
}

int main(){
    int* p = NULL;
    test(p);
    return 0;
}
```
回答以下问题：
(a). 在没有进行上述编译优化之前，程序是否能够正常退出？
(b). 给出通过上述编译优化方案后的 C 程序代码（仅考虑 test 函数优化），并解释为什么会产生这样的代码。
(c). 没有经过优化的编译程序和经过优化后的编译程序执行结果是否相同？
(d). 说明早期 GCC 版本编译器优化带来的启示。
(e). 阅读以下内容了解早期 GCC 编译此优化方案的详细信息。  
[点击阅读（需要梯子,不要用 chrome）](http://blog.llvm.org/2011/05/what-every-c-programmer-should-know_14.html)

### 问题参考答案
(a). 不能正常退出，原因是 *p 访问非法地址 ( 注意这段代码在 clang 上如果不加-O3 编译选项则会出现 Segmentation Fault，而加了-O3选项可以正常退出，原因就是因为变量 c 没被使用而优化删除了本次赋值操作。对于 GCC 编译器（5.4.0），不添加-O3编译选项可也正常退出，即已经做过一部分优化了)
(b). 经过上述方案优化过后的 C 语言代码：
``` c
#include<stdio.h>
void test(int *p){
    // int c = *p;  变量 c 不会在 test 中被用到
    // if(p == 0)   由于 p 在上一条语句中已经被编译器确定非0，因此条件始终为 false，此段代码不会被执行
    //     return;  所以可以被删除
    *p = 2333;
}

int main(){
    int* p = NULL;
    test(p);
    return 0;
}
```
(c). 结果不相同。没有被优化的程序能够正常退出，优化后的程序由于 *p = 2333; 从而产生 Segmentation Fault 
(d). 认为利用 C 指针未定义行为而做出的优化是错误的。（注意此优化行为出现在早期 GCC 版本中，后来经过 issue 得到修复，具体内容请看(e) ）

[考察知识点]： 编译器代码优化，知识运用能力