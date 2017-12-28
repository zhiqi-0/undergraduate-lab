#使用手册

##编译执行
在 linux 平台下，cd 进入 resolution.cpp 所在目录路径，并执行以下命令：

```
$ g++ -std=c++11 resolution.cpp -o res
```

运行请输入命令：

```
$ ./res
```

##使用说明
1. 本程序使用 __归结原理__  给出在 L命题逻辑 下的自动定理证明

2. 由于未添加符号转换功能，因此使用者请预先将 __已知公式集__ 和 __待验证命题的非__ 均转化为 __合取范式__ 

3. 程序输入：程序开始会要求输入 degree（命题变元的个数），随后将已经转换好的合取范式按照下列示例输入：  
  
  假设已经转换好的合取范式为：  
  { (x1 v ~x2 v x3) ^ (x2 v x3 v ~x1), (x1 v ~x2) ^ (~x2 v x1) }  
  则将不同的合取范式用 ^ 连接，得到：  
  (x1 v ~x2 v x3) ^ (x2 v x3 v ~x1) ^ (x1 v ~x2) ^ (~x2 v x1)  
  将此表达式按照以上形式输入进程序（其中 degree 为 3），不需要考虑空格等因素。  
  另一种简单的输入方式为：  
  x1 ~x2 x3 ^ x2 x3 ~x1 ^ x1  ~x2 ^ ~x2 x1
  此输入方式效果一样。
 
4. 程序输出： 程序输出会给出证明序列，当出现空集合时即证明成功，显示 “Success in Prove”；当出现无法再使用归结原理时，说明所要证明的公式不能从原公式集中推出，程序最后将显示 “Can't be proved”。

5. 最后所附文件中有可在 linux Ubuntu 16.04下直接可运行的程序，命令行   
``` ./resolution ``` 即可

##源码说明

数据结构：

LogicUnit 为结构体类型，其中 no 为是否为非， xi 为命题变元下标 i，例如可表示 ~x1, x2 等命题变元

Disjunct 为 list<LogicUnit> 类型，为析取表达式，构成合取范式的单元，可以表示 (x1 v x2 v ~x3) 等结构。

LogicSet 为 list<Disjunct> 类型，为合取范式。

函数 setprint(LogicSet &logicset) ：显示 logicset 中存储的合取范式；

函数 DisjunctPrint(Disjunct &d)：显示析取范式

函数 DisjunctSimplify(Disjunct &d): 化简析取范式，将重复的命题逻辑项删去，如果出现 xi v ~xi 则返回 false

函数 FindDisjunct(Disjunct &a, LogicSet &logicset):在 logicset 中寻找是否存在 a 项，如果存在，返回 true；（本函数要求 logicset 中的 Disjunct 项已经经过 DisjunctSimplify 进行化简。

函数 logicsort(LogicSet &logicset): 对 每个Disjunct项按照下标 xi 进行排序，从小到大排。

函数 logicmerge(LogicSet::iterator ls1,LogicSet::iterator ls2,LogicSet &logicset, bool &KO): 将两个 Disjunct 项合并，并删去重复项。

函数 resolution(LogicSet &logicset): 利用归结原证明命题。

  