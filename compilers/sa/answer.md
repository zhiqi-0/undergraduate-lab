## 问题回答

### 问题3.1.5：简要说明 test.c, AST.svg, CFG.svg, ExplodedGraph.svg 之间的联系和区别

```
int main(){
    int i = 1;
    int j = 2;
    for(i = 1; i < 5; ++i){
        if(i > 3)
            ++j;
        else
            --j;
    }
    return 0;
}
```

回答：AST.svg 根据 test.c 获得了分析树，分析树的结构中：for 循环有4个子树，分别为初始值子树，条件子树，更新子树，循环内部子树；if 语句中（包含 else）会有3个子树，分别是条件判断子树，条件成立执行子树，条件失败执行子树；其他的部分也由 C 文法来决定生成树的情况。CFG.svg 中展示的是大体的 BasicBlock 的调用情况，由 lab2 可以知道，CFG 的 BasicBlock 一般是通过访问者模式遍历分析树来获得，如果我们将 for 循环内部的 if 所形成的子树看为一体的话，我们可以看到 for 循环的 BasicBlock 中，条件比较、for 循环执行体、迭代更新将分别位于三个不同的 BasicBlock 中，与当时我们实现 lab2 时情况相似。ExplodedGraph 由 CFG 得到，图中的每个节点都是 ExplodedNode，它由一个 ProgramPoint 和 一个 ProgramState 组成。ProgramPoint 表示程序（或CFG）中的相应位置，ProgramState 表示程序执行到当前的状态。

### 问题3.2.1：Checker 对于程序的分析主要在 AST 还是在 CFG 上

回答： 从文档中可以看出，Checker 要求路径敏感，所以 Checker 对程序的分析主要集中 CFG 上。当然也有特殊情况：有些 Checker 可能不会对路径敏感有要求，所以简单的 AST 对某些 Checker 有时也是可以的。(然而实际上 AST 和 CFG 这两个很难做区分，因为 CFG 是根据 AST 进行生成的，也就是说归根结底 Checker 还是要求有 AST 的基础)

### 问题3.2.2：Checker 在分析程序时需要记录程序状态，这些状态一般保存在哪里

回答：ProgramState. 每当分析器引擎探索一个新的语句，分析器会通知对该条语句进行注册的所有 Checker，然后此时 Checker 可以报告问题或者更改状态。

### 问题3.2.3：简要解释分析器在分析下面程序片段的过程，在过程中产生了哪些 symbolic values？ 他们的关系是什么？

``` c
int x = 3, y = 4;
int *p = &x;
int z = *(p + 1);
```

回答：

* symbolic values 为： 'x', 'y', 'p', 'p + 1'. 

* 它们的关系：它们都是自上而下创建的，会转变成 SVal。

### 问题3.3.1：LLVM 大量使用了 C++11/14的智能指针，请简要描述几种智能指针的特点、使用场合，如有疑问也可以记录在报告中.

回答：

* `unique_ptr` : 独享所有权的智能指针，他提供严格意义上的所有权,包括：拥有它指向的对象; 无法进行复制构造，无法进行复制赋值操作。即无法使两个unique_ptr指向同一个对象。但是可以进行移动构造和移动赋值操作; 保存指向某个对象的指针，当它本身被删除释放的时候，会使用给定的删除器释放它指向的对象; 适用场合：对象禁止被复制构造、复制赋值的场合。

* `share_ptr` : 资源可以被多个指针共享,通过计数器来实现, 适用于对象能被多个指针所引用的场合。

* `weak_ptr` : 用来解决shared_ptr相互引用时的死锁问题, 适用于资源共享且可能发生死锁的场合。

### 问题3.3.2：如果你想写一个函数，它的参数既可以是数组，也可以是std::vector，那么你可以声明该参数为什么类型？如果你希望同时接受 C 风格字符串和 std::string 呢？

回答：

* 对于 std::vector 和 数组，则可以把参数声明为 std::vector 的类型，因为有构造函数 `std::vector<T>(&p[0], &p[N])` (p 的类型为 T*)；

* 对于 C 风格字符串和 std::string, 则可以直接将参数声明为 std::string, 有隐式类型转换（也由 std::string 的构造函数实现）可以将 C 风格字符串转化为 std::string;

### 问题3.3.3：LLVM 不使用 C++ 的运行时类型推断（RTTI），理由是什么？LLVM 提供了怎样的机制来代替它？

回答：不使用 RTTI 的原因是为了减少代码和可执行文件的大小，也因为 RTTI 违法了 C++ 语言原则："you only pay for what you use". LLVM 提供了像 isa<>, cast<>, dyn_cast<> 这样的模板的形式。

### 问题3.3.4：你有时会在cpp文件中看到匿名命名空间的使用，这是出于什么考虑？

回答：这是为了防止外界使用此名称空间中的内容,也就是说匿名名称空间用来保证生成的符号是局部的，对外不可见的。这样做为了防止出现名称冲突，减少依赖，并且也防止不恰当的调用。

### 问题3.4.1：这个 checker 对于什么对象保存了哪些状态？保存在哪里？

回答：checker 对于一个文件句柄保存了两种状态：打开（Kind::Opened) 和 关闭（Kind::Closed)，这些状态保存在 ProgramState 里面

### 问题3.4.2：状态在哪些时候会发生变化？

回答：在 `SimpleStreamChecker::checkPostCall` 方法中，可以看出这是用于文件打开时状态的设置，当调用 `fopen` 的时候, 会通过 StreamMap 和 ProgramState 设置这个文件句柄为打开状态；同样，在 `SimpleStreamChecker::checkPreCall` 方法中，可以看出这是用于文件关闭时状态的设置，当调用 `fclose` 的时候，会检查这个句柄的状态，如果已经处于关闭状态，则报 “Double fclose” 的错误，否则，设置这个句柄的状态为关闭状态; 在 `SimpleStreamChecker::checkDeadSymbols` 方法中，当一个变量离开他的作用域时, 会删除这些 Dead Symbol 的状态; 在 `SimpleStreamChecker::checkPointerEscape`方法, 也会有删除 Escaped 指针的状态操作； 在 `SimpleStreamChecker::VisitSymbol` 方法中，也会有删除状态的操作。

### 问题3.4.3：在哪些地方有对状态的检查？

回答：在 `SimpleStreamChecker::checkPreCall` 方法中，会检查在关闭前是否已经有关闭的判断；在 `IsLeaked` 函数中，会检测是否打开，所以调用 `IsLeaked` 函数如 `SimpleStreamChecker::checkDeadSymbols` 也会对状态进行检查; `SimpleStreamChecker::checkPointerEscape` 方法中会对是否能关闭文件进行检查，如果不能关闭文件，那么直接 return。

### 问题3.4.4：函数SimpleStreamChecker::checkPointerEscape的逻辑是怎样的？实现了什么功能？用在什么地方？

回答：

* 在这个方法中，首先判断这个CallEvent是否能关闭文件，如果不行，那么直接返回，接下来，取出所有的 Escaped 指针，并将它们的状态都删除；

* 实现了的功能：删去 Escaped 指针的有关状态

* 用在什么地方：当指针出现 Escaped 状态时，调用这个函数。 


### 问题3.4.5：根据以上认识，你认为这个简单的checker能够识别出怎样的bug？又有哪些局限性？请给出测试程序及相关的说明。

回答：这个简单的 checker 能够识别出的 bug：重复关闭 和 潜在泄露（文件最后没有被关闭）；

局限性：

* 在某些平台下（如 MacOS High Sierra）出现两次 fclose 同一文件指针时不提示 `Closing a previously closed file stream` warning。
* 如果文件指针被修改，如文件指针在打开一个文件后，又被另一个文件指针覆盖后，则第一个被打开的文件不会再被检测是否关闭。 

测试示例位于 sa/test 文件夹目录下，为 test1.c

### 问题3.5.1：增加一个checker需要增加哪些文件？需要对哪些文件进行修改？

回答： 
* 需要增加一个自己的 checker 实现文件，位于 clang/lib/StaticAnalyzer/Checkers 下；
* 需要修改的文件：
  * clang/lib/StaticAnalyzer/Checkers/CMakeLists.txt 中加入新增加的 Checker 的 cpp 文件名。
  * clang/include/clang/StaticAnalyzer/Checkers.td 中加入新的 Checker 的定义。

### 问题3.5.2：阅读clang/include/clang/StaticAnalyzer/Checkers/CMakeLists.txt，解释其中的 clang_tablegen 函数的作用。

回答：clang_tablegen 用于将（在此例中）Checker.td 翻译成 C++ 代码。

### 问题3.5.3：.td文件在clang中出现多次，比如这里的clang/include/clang/StaticAnalyzer/Checkers/Checkers.td。这类文件的作用是什么？它是怎样生成C++头文件或源文件的？这个机制有什么好处？

回答：*.td 文件包含了 TableGen 的代码. TableGen是一个解释性的语言来描述“特定于领域的信息的记录”。TableGen 在 llvm 和 clang 中的应用主要目的之一就是生成llvm/clang C/C++ 源代码的一部分; 这类文件通过 TableGen 转化为.inc 文件，.inc 文件是一种通用型的对声明、函数的定义，这个文件可以转化为 C++，C, Java 等多种不同语言;这个机制的好处是：使得 LLVM 移植更加容易，因为这一机制减少了必要的 C++ 代码编写的数量，其次，它使得改变事情变得容易，比如我们可以只更改一个地方(tblgen)就可以更改所有目标到一个新的接口。

## 拓展内容

### 分析现有 Checker 的缺陷

* 异常处理机制目前不能很好地被实现，有待加强

* CFG 对 new 和 delete 这两个 C++ 操作支持不完善，new 无法提供一个简单的方法来调用内存分配，而 delete 则无法自动调用析构函数。

* 对 casts 中的类型推断不够精准

### 以动态内存、或文件等资源有关的缺陷检查为例，对clang 静态分析器进行如下使用和分析工作：

* 是否能检查该类缺陷?

  回答：可以

