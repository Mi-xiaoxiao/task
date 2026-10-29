# 第一章 初识C语言
## 1.对编程语言来说，可移植性意味着什么？
>可移植性是指在一种计算机系统上编写的代码，只需极少修改甚至不修改，就能在另一种完全不同架构的系统上编译并运行。

## 2.解释源代码文件、目标代码文件和可执行文件的区别？

 - **源代码文件（Source Code）：程序员用高级语言（如 C 语言）敲出来的文本文件（如 main.c），人类能看懂，但计算机看不懂。**
 
 - **目标代码文件（Object Code）：编译器将源代码翻译成的机器指令文件（如 main.o 或 main.obj）。它虽然已经是二进制了，但还不能直接运行，因为里面调用的外部函数（比如 printf）还没接上。**
 
 - **可执行文件（Executable File）：链接器把目标代码和系统库（如标准库）打包合并在一起生成的最终文件（如 a.out 或 main.exe）。这是可以直接双击运行的程序。**
 
## 3.编程的 7 个主要步骤是什么？
 
 - 定义程序的目标
 - 设计程序
 - 编写代码
 - 编译
 - 运行程序
 - 测试和调试程序
 - 维护和修改代码
 
 ## 4.编译器的任务是什么？
 >将人类能看懂的高级语言（源代码），翻译成计算机能看懂的底层机器语言（目标代码）。
 
 ## 5.链接器的任务是什么？
 >把编译器生成的多个目标代码文件（.o），以及程序需要用到的系统库文件（比如 C 语言标准库里的 printf 代码），拼装、组合成一个完整的、可直接运行的可执行文件。
 
 # 第二章 C语言概述
 ## 1.C语言的基本模块是什么？
 >函数,C 程序是由一个或多个函数组成的，main() 是所有程序的主入口。
 ## 2.什么是语法错误？写出一个英语例子和 C 语言例子。
>语法错误是违背了语言的拼写或结构规则。
 - 英语例子：I is a student.（主谓不一致）
 - C 语言例子：int a = 5（末尾漏掉了分号 ;）
## 3.什么是语义错误?写出一个英语例子和 C 语言例子
>语义错误是语法正确，但逻辑或意思错了
 - 英语例子：The cat ate the mouse.（改成）The mouse ate the cat.（语法正确，但逻辑荒谬）。
 - C 语言例子：int a = 5; int b = 2; int c = a / b;（本意是做浮点数除法得 2.5，但因为两边都是 int，结果被截断成了 2，丢失了精度，结果错误）。
## 4.Indiana Sloth 编写了下面的程序，并征求你的意见。请帮助他评定。
```text
include studio.h
int main{void} /* 该程序打印一年有多少周 /*
(
    int s
    s := 56;
    printf(There are s weeks in a year.);
    return 0;
```
```
include studio.h 
```
无尖括号"<>"
```
int main{void} /* 该程序打印一年有多少周 /*
```
注释用“/**/”
```
(
```
函数体用大括号”{}“
```
int s
```
结尾无分号“;"
```
 s := 56;
 ```
 ":"多余，会报错
 ```
 printf(There are s weeks in a year.);
 ```
 printf内需要双引号""

# 第三章 数据和C
## 1.指出下面各种数据使用的合适数据类型（有些可使用多种数据类型）：
a. East Simpleton 的人口（unsigned int,long long）
b. DVD 影碟的价格（float,double）
c. 本章出现次数最多的字母（char）
d. 本章出现次数最多的字母次数（int，long long等）
## 2.在什么情况下要用 long 类型的变量代替 int 类型的变量？
>当需要存储的数值超过了 int 类型所能表示的最大范围时
## 3.使用哪些可移植的数据类型可以获得 32 位有符号整数？选择的理由是什么？
>long或者 C99 引入的 <stdint.h> 中的 int32_t。

>理由：int 的位数依赖于系统架构（可能是 16 位或 32 位），而标准保证了 long 的最小宽度是 32 位，使用 long 可以在任何平台上确保容纳 32 位有符号整数。

## 4.指出下列常量的类型和含义（如果有的话）：
| |类型|含义|
| :--- | :--- | :--- |
| '\b' | char|退格 |
| 1066 |int |十进制整数 |
| 99.44 |double |浮点数 |
| 0XAA|int |十六进制整数 |
| 2.0e30|double |科学计数法浮点数 |

## 5.Dottie Cawm 编写了一个程序，请找出程序中的错误。
```c
include <stdio.h> //缺少“#”
main //缺少int
( //应为大括号“{}”
    float g; h; //g的后面多分号“;”
    float tax, rate;

    g = e21; //科学计数法前面必须有数字，应改为 2e21
    tax = rate*g; //变量rate未初始化就被使用了
)
 ```

## 6.写出下列常量在声明中使用的数据类型和在 printf() 中对应的转换说明：
| 常量 | 类型 | 转换说明（%转换字符） |
| :--- | :--- | :--- |
| 12 |int |%d |
| 0X3 |int |%x,%d |
| 'C' |char |%c |
| 2.34E07 |double |%e,%f |
| '\040' |char |%c |
| 7.0 |double |%f,%e |
| 6L |long |%ld |
| 6.0f |fioat |%f |
| 0x5.b6p12 |fioat |%f |

## 7.写出下列常量在声明中使用的数据类型和在 printf() 中对应的转换说明（假设 int 为 16 位）：
| 常量 | 类型 | 转换说明（%转换字符） |
| :--- | :--- | :--- |
| 012 |int |%o,%d |
| 2.9e05L |long double |%lf |
| 's' |char |%c |
| 100000 |long |%ld |
| '\n' |char |%c |
| 20.0f |float |%f |
| 0x44 |int |%d |
| -40 |int |%d |

## 8.指出下列转义序列的含义：（转11）
|  | 含义 | 
| :--- | :--- | 
|\n |换行符 |
|\\ |反斜杠 |
|\" |双引号 |
|\t |水平制表符|

# 第四章 字符串的格式化输入与输出
## 1.找出下面程序中的错误。（转复4）
```c
define B booboo //少井号'#'
define X 10
main(int) //小括号里写'void'
{
    int age;
    char name; //存储姓名要用字符串，而非单个字符
    printf("Please enter your first name.");
    scanf("%s", name); //无取地址符'&'
    printf("All right, %c, what's your age?\n", name);
    scanf("%f", age); //应用%d
    xp = age + X;
    printf("That's a %s! You must be at least %d.\n", B, xp); //变量xp未声明
    rerun 0;
}
```
## 2.打印下面各项内容要分别使用什么转换说明？（转复8）
>a. 一个字段宽度为 6、最少有 4 位数字的十进制整数
b. 一个在参数列表中给定字段宽度的八进制整数
c. 一个字段宽度为 2 的字符
d. 一个形如 +3.13、字段宽度等于数字中字符数的浮点数
e. 一个字段宽度为 7、左对齐字符串中的前 5 个字符
```
注：'*'表示空格。
a.%6.4d  例如输入12：**0012
b.%*o      例如printf("%*o", 5, 10); 会输出 12（八进制的10，宽度为5）
c.%2c      例如输入A：*A
d.%+.3f，+ 强制显示正负号，例如输入3.13：+3.13
e.%-7.5s - 代表左对齐，7 是宽度，.5 是精度（只打印前 5 个字符）。假设字符串是 HelloWorld，结果会是 Hello
```
## 3.假设要在程序中使用圆括号代替花括号，以下方法是否可行？（转复12）
```
#define ( {
#define ) }
```
```
标识符只能由字母、数字和下划线 _ 组成，且不能以数字开头,(与) 是标点符号，它们不是合法的标识符。预处理器在解析到 #define ( 时就会认为语法错误，直接停止编译。
```
# 第五章 运算符、表达式和语句
## 1.假设所有变量的类型都是 int，下列各项变量的值是多少：
a. x=(2 + 3) * 6;
b. x=(12 + 6)/2*3;
c. y=x=(2 + 3)/4;
d. y=3+2*(x = 7/2);

>30 
>27
>x=y=1
>x=3,y=9

## 2. 假设所有变量的类型都是 int，下列各项变量的值是多少：
a. x = (int)3.8 + 3.3;
b. x = (2 + 3) * 10.5;
c. x = 3 / 5 * 22.0;
d. x = 22.0 * 3 / 5;
>6
>52
>0
>13

## 3.对下列各表达式求值：
a. 30.0 / 4.0 * 5.0;
b. 30.0 / (4.0 * 5.0);
c. 30 / 4 * 5;
d. 30 * 5 / 4;
e. 30 / 4.0 * 5;
f. 30 / 4 * 5.0;
>37.5
>1.5
>35
>37
>37.5
>35.0

## 4.请找出下面的程序中的错误
```c
int main(void)
{
    int i = 1;
    float n;
    printf("Watch out! Here come a bunch of fractions!\n");
    while (i < 30) //循环体无大括号{}
        n = 1/i; //i无变化，无限循环
        printf(" %f", n);
    printf("That's all, folks!\n");
    return; //应为"return 0"
}
```

## 5.下面的程序将打印出什么内容?（转复6）
```c
#include <stdio.h>
#define FORMAT "%s! C is cool!\n" //宏定义
int main(void)
{
    int num = 10; //初始化变量
    printf(FORMAT,FORMAT);
     /*
     展开：("%s! C is cool!\n","%s! C is cool!\n")
     第一个%s是一个占位符，被后面的%s! C is cool!替换，printf之
     后继续打印! C is cool!
     */
    printf("%d\n", ++num); //先加后用，打印11
    printf("%d\n", num++); //先用后加，打印11
    printf("%d\n", num--); //先用后减，打印12
    printf("%d\n", num); //打印11
    return 0;
}
```

## 6.假设下面是完整程序中的一部分，它们分别打印什么？（转复10）
```c
// a 部分
int x = 0; 
while (++x < 3)
    printf("%4d", x); //打印：***1***2（*为空字符）

// b 部分
int x = 100;
while (x++ < 103)
    printf("%4d\n", x); 
   /*
   打印：
   *101
   *102
   *103（*为空字符）
   */
printf("%4d\n", x); //104

//c部分
char ch = 's';
while (ch < 'w')
{
    printf("%c", ch); //打印：stuv
    ch++;
}
printf("%c\n", ch); //打印：w
```

# 第六章 C控制语句：循环
## 1.假设用户输入的是 Go west, young man!（注意：后面有一个感叹号，且在 ASCII 码中 ! 紧跟在空格字符后面），下面各程序的输出是什么？（转复8）
```c
// a
#include <stdio.h>
int main(void)
{
    char ch;
    scanf("%c", &ch); //录入'G'
    while (ch != 'g') //'G'!='g',为真，进入循环
    {
        printf("%c", ch); //读取每一个字符，包含空格与','等
        //最终打印：Go west, youn
        scanf("%c", &ch); //读入'g',条件不成立
    }
    return 0;
}

// b
#include <stdio.h>
int main(void)
{
    char ch;
    scanf("%c", &ch);//录入'G'
    while (ch != 'g')
    {
        printf("%c", ++ch); //打印上一次录入的下一个字符
        //最终打印：Hp!xftu-!zpvo（空格的下一个是'!'，'，‘下一个为'-'
        scanf("%c", &ch); //读入'g',条件不成立
    }
    return 0;
}

// c
#include <stdio.h>
int main(void)
{
    char ch;
    do {
        scanf("%c", &ch);//录入'G',直到录入'g'
        printf("%c", ch); //依次打印：Go west, young
    } while (ch != 'g');
    return 0;
}

// d
#include <stdio.h>
int main(void)
{
    char ch;
    scanf("%c", &ch);//录入'G'
    for (ch = '$'; ch != 'g'; scanf("%c", &ch))
        printf("%c", ch);
        /*
        进入循环：判断 $ != 'g'，打印 $。执行迭代部分 scanf，读入 o。
        下一次：判断 o != 'g'，打印 o。读入空格，以此类推，相当于用 $ 替换了首字母 G。
        最终打印：$o west, youn
        */
    return 0;
}
```

## 2.Noah 先生喜欢以 2 计数，所以编写了下面的程序，创建了一个存储 2、4、6、8 等数字的数组。这个程序是否有错误之处？如果有，请指出（转复11）

```c
#include <stdio.h>
#define SIZE 8
int main(void)
{
    int by_twos[SIZE];
    int index;

    for (index = 1; index <= SIZE; index++)
        by_twos[index] = 2 * index;
    for (index = 1; index <= SIZE; index++)
        printf("%d ", by_twos);
    printf("\n");
    return 0;
}
```

 - 数组越界：

    C 语言的数组下标是从 0 开始的。数组 int by_twos[SIZE];（大小是 8），下标范围是 0 到 7。

    代码中 for (index = 1; index <= SIZE; index++)，当 index 等于 8 时，循环依然成立，程序会执行 by_twos[8] = 16，会访问数组之外的数据。而第一个元素 by_twos[0] 被抛弃了，没有被赋值。

 - 打印格式错误：

    printf("%d ", by_twos);中，by_twos 是数组名，直接打印数组名会输出一个内存地址，而非数组里的值，应该写成 printf("%d ", by_twos[index]);。

## 3.下面的程序打印什么内容？（转复14）
```c
#include <stdio.h>
int main(void) {
    int k;
    for (k = 1, printf("%d: Hi!\n", k); printf("k = %d\n", k), k*k < 26; k += 2, printf("Now k is %d\n", k))
        printf("k is %d in the loop\n", k);
    return 0;
}
```
# 循环执行过程表

| 轮次 | 阶段 | 执行动作 | k 值变化 | 条件计算 | 判断结果 | 屏幕输出 |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| 第 1 轮 | 初始化 | 初始化 `k = 1`，执行 `printf` | `k = 1` | — | — | `1: Hi!` |
| 第 1 轮 | 条件判断 | 先打印 `k`，再计算条件 | `k = 1` | `1 * 1 < 26` | 真 | `k = 1` |
| 第 1 轮 | 循环体 | 执行循环体 | `k = 1` | — | — | `k is 1 in the loop` |
| 第 1 轮 | 更新 | 先执行 `k += 2`，再打印 | `k: 1 → 3` | — | — | `Now k is 3` |
| 第 2 轮 | 条件判断 | 先打印 `k`，再计算条件 | `k = 3` | `3 * 3 < 26`（即 `9 < 26`） | 真 | `k = 3` |
| 第 2 轮 | 循环体 | 执行循环体 | `k = 3` | — | — | `k is 3 in the loop` |
| 第 2 轮 | 更新 | 执行 `k += 2`，再打印 | `k: 3 → 5` | — | — | `Now k is 5` |
| 第 3 轮 | 条件判断 | 先打印 `k`，再计算条件 | `k = 5` | `5 * 5 < 26`（即 `25 < 26`） | 真 | `k = 5` |
| 第 3 轮 | 循环体 | 执行循环体 | `k = 5` | — | — | `k is 5 in the loop` |
| 第 3 轮 | 更新 | 执行 `k += 2`，再打印 | `k: 5 → 7` | — | — | `Now k is 7` |
| 第 4 轮 | 条件判断 | 先打印 `k`，再计算条件 | `k = 7` | `7 * 7 < 26`（即 `49 < 26`） | 假 | `k = 7` |
| 第 4 轮 | 退出循环 | 条件为假，退出循环 | `k = 7` | — | — | — |

最终打印：
```text
1: Hi!
k = 1
k is 1 in the loop
Now k is 3
k = 3
k is 3 in the loop
Now k is 5
k = 5
k is 5 in the loop
Now k is 7
k = 7
```

# 第七章 C控制语句：分支和跳转
## 1.下面的程序关系表达式过于复杂，而且还有些错误，请简化并改正（转复3）

```c
#include <stdio.h>
int main(void)
{
    int weight, height; /* weight 以磅为单位，height 以英寸为单位 */
    /* 4 */
    scanf("%d , weight, height); /* 5 */
    if (weight < 100 && height > 64) /* 6 */
        if (height >= 72) /* 7 */
            printf("You are very tall for your weight.\n"); /* 8 */
        else if (height < 72 && >= 64) /* 9 */
            printf("You are tall for your weight.\n"); /* 10 */
        else if (weight > 300 && ! (weight <= 300)
            && height < 48) /* 11 */
            if (!(height >= 48) ) /* 12 */
                printf(" You are quite short for your weight.\n"); /* 13 */
        else
            printf("Your weight is ideal.\n"); /* 15 */
    return 0;
}
```

 1. 第 5 行缺少取地址符 &，引号少打了
 2. 第9行&&的右侧变变量
 3. 第11行直接写 weight > 300 即可


## 2.下面的程序将打印什么？（转复6）
```c
#include <stdio.h>
int main(void)
{
    int i = 0;
    while (i < 3) {
        switch (i++) {
            case 0: printf("fat ");
            case 1: printf("hat ");
            case 2: printf("cat ");
            default: printf("Oh no! ");
        }
        putchar('\n');
    }
    return 0;
}
```

 1. 第 1 次循环：i=0。进入 switch(i++)，先取 i 的值 0 进行匹配，随后 i 自增变成 1。
    匹配 case 0，打印 fat ，没有 break，发生穿透，继续执行 case 1，打印 hat 。穿透到case 2，打印 cat ，穿透到 default，打印 Oh no!。 遇到 switch 结束，随后遇到 putchar('\n')，换行。
 2. 此时 i=1。i < 3 成立。switch(i++) 取 i 的值 1 匹配，i 随后变成 2。 匹配 case 1，打印 hat ，穿透打印 cat ，穿透打印 Oh no!，换行。
 3. 此时 i=2。i < 3 成立。switch(i++) 取 i 的值 2 匹配，i 随后变成 3。 匹配 case 2，打印 cat ，穿透打印 Oh no!，换行。
 4. 第 4 次循环：此时 i=3。i < 3 不成立，退出循环。
 
 最终打印：
 ```text
 fat hat cat Oh no!
hat cat Oh no!
cat Oh no!
```

## 3.给定下面的输入时，以下程序将打印什么？（转复9）
>q
>c
>h
>b

```c
#include <stdio.h>
int main(void)
{
    char ch;
    while ((ch = getchar()) != '#')
    {
        if (ch == '\n')
            continue;
        printf("Step 1\n");
        if (ch == 'c')
            continue;
        else if (ch == 'b')
            break;
        else if (ch == 'h')
            goto laststep;
        printf("Step 2\n");
    laststep: printf("Step 3\n");
    }
    printf("Done\n");
    return 0;
}
```

 1. 读入 q：不等于 #,循环条件成立。不是 \n。打印 Step 1。不满足 c、b、h 的条件。打印 Step 2。执行 laststep 处的语句，打印 Step 3。
 2. 读入 \n (回车)：不等于 #，满足 if (ch == '\n')，执行 continue。跳过后面的所有内容，进入下一轮 while 循环。
 3. 读入 c：不等于 #，打印 Step 1。满足 if (ch == 'c')，执行 continue。直接跳过后面的 Step 2 和 Step 3，进入下一轮。
 4. 读入 \n (回车)：执行 continue。
 5. 读入 h：不等于 #，打印 Step 1。满足 else if (ch == 'h')，执行 goto laststep。直接跳转到 laststep 标签，打印 Step 3。
 6. 读入 \n (回车)：执行 continue。
 7. 读入 b：不等于 #。打印 Step 1。满足 else if (ch == 'b')，执行 break。直接跳出整个 while 循环。执行最后的 printf("Done\n");。

 最终打印：
 ```text
 Step 1
Step 2
Step 3
Step 1
Step 1
Step 3
Step 1
Done
```

# 第八章 字符输入/输出和输入验证
## 1.EOF是什么？

 1. 字面含义：EOF 的全称是 End Of File（文件结束符）
 2. 本质：它是一个定义在 <stdio.h> 头文件里的宏定义,它的值通常是 -1,它本质上是一个整数（int），而不是字符。
 3. 作用：当程序从文件（或键盘）读取数据时，读到末尾没东西可读了，系统就会给 getchar() 或 scanf() 等函数返回一个 EOF，告诉程序读取结束。
 4. 


## 2.对于给定的输入（ch 是 int 类型，而且是缓冲输入），下面程序段的输出是什么？（转复6）
a.输入如下：
>If you quit,I will.[enter]

程序段如下：
```c
while((ch=getchar())!='i')
putchar(ch);
```
直接输出：If you qu

b.输入如下：
>Harhar[enter]

程序段如下：
```c
while ((ch = getchar()) != '\n')
{
    putchar(ch++);
    putchar(++ch);
}
```
```
getchar() 每次从缓冲区读一个字符,putchar(ch++) 先打印 ch 的当前值，再将 ch 加 1,putchar(++ch) 先将 ch 加 1，再打印。

第 1 轮：getchar() 读入 'H'

    putchar(ch++)：打印 'H'，随后 ch 变成 'a' 

    putchar(++ch)：ch 先加 1 变成 'b' (74)，打印 'b'

    输出：Hb

第 2 轮：getchar() 读入 'a'，覆盖原来的 ch，ch = 'a' 

    putchar(ch++)：打印 'a'，随后 ch 变成 'r' 

    putchar(++ch)：ch 先加 1 变成 's' ，打印 's'。

    输出：as

第 3 轮：getchar() 读入 'h'

    putchar(ch++)：打印 'h'，随后 ch 变成 'a' 

    putchar(++ch)：ch 先加 1 变成 'b' ，打印 'b'

    本轮输出：hb

第 4 轮：getchar() 读入 'r'（第 6 个字符），ch = 'r' 

    putchar(ch++)：打印 'r'，随后 ch 变成 '\n' 

    putchar(++ch)：ch 先加 1 变成 '\v'，打印 '\v'
    输出：r 

第 5 轮：getchar() 读入最后的换行符 '\n'，循环条件 ch != '\n' 不成立，退出。
```

## 3.在使用缓冲输入的系统中，把数值和字符混合输入会遇到什么潜在的问题？（转复8）
***举例说明***：
```c
#include<stdio.h>
int main (){
int num;
char c;
printf("Enter a number: ");
scanf("%d", &num);   // 例如输入 10，并按下回车
printf("Enter a character: ");
scanf("%c", &c);    // 程序直接跳过，不会等待用户输入
return 0;
}
```
解释：在用户输入10后，会按下回车，缓冲区会留下'\n',第二个scanf会直接录入'\n',不会等待用户输入，造成错误。

# 第九章 函数
## 1.根据下面各函数的描述，分别编写它们的 ANSI C 函数头。注意，只需写出函数头，不用写函数体。（转复3）

 - n_to_char() 接受一个 int 类型的参数，返回一个 char 类型的值
 ```
 char n_to_char(int n)
 ```
 - digit() 接受一个 double 类型的参数和一个 int 类型的参数，返回一个 int 类型的值
 ```
 int digit(double d, int n)
```
 - which() 接受两个可存储 double 类型变量的地址，返回一个 double 类型的地址
 ```
 double * which(double *p1, double *p2)
 ```
 
 - random() 不接受参数，返回一个 int 类型的值
 ```
 int random()
 ```

## 2.下面的函数定义是否正确？（转复7）
```c
void salami(num)//括号内应写“int num”
{
    int num, count; //num重复定义
    for (count = 1; count <= num; num++) //程序循环的迭代部分是 num++。num 越来越大，导致条件 count <= num 永远成立，陷入死循环
        printf(" O salami mio!\n");
}
```
## 3.给定下面的输出：
```
Please choose one of the following:
1) copy files       2) move files
3) remove files     4) quit
Enter the number of your choice:
```
a. 编写一个函数，显示一份有4个选项的菜单，提示用户进行选择（输出如上所示）。该函数从用户的输入中读取整数。如果整数超出规定上下限（1-4），函数再次打印菜单（使用 a 部分的函数）提示用户输入，然后获取一个新值。如果用户输入的整数在规定范围内，该函数则把该整数返回主调函数。如果用户输入一个非整数字符，该函数应返回 4。

b. 编写一个函数，接受两个 int 类型的参数分别表示上限和下限。该函数从用户的输入中读取整数。如果整数超出规定上下限，函数再次打印菜单（使用 a 部分的函数）提示用户输入，然后获取一个新值。如果用户输入的整数在规定范围内，该函数则把该整数返回主调函数。如果用户输入一个非整数字符，该函数应返回 4。

c. 使用本题 a 和 b 部分的函数编写一个最小型的程序。最小型的意思是，该程序不需要实现菜单中各选项的功能，只需显示这些选项并获取有效的响应即可。

**eg.**
```c
#include <stdio.h>
int s(){
	printf("Please choose one of the following:\n");
	printf("1) copy files       2) move files\n");
	printf("3) remove files     4) quit\n");
	printf("Enter the number of your choice:\n");
	int n;
	if((scanf("%d",&n))!=1){
		getchar();
		return 4;
	}
	if(n<1||n>4){
		return s();
	}
	return n;
}
int main(void)
{
	int g=s();
	printf("%d\n",g);
	return 0;
}
```
# 第十章 数组和指针
## 1.在下面的代码中，*ptr 和 *(ptr + 2) 的值分别是什么？（转复4）
```
a.
int *ptr;
int torf[2][2] = {12, 14, 16};
ptr = torf[0];

b.
int *ptr;
int fort[2][2] = { {12}, {14,16} };
ptr = fort[0];
```
**解答**：

 1. 对于a,torf[2][2]中应有4个元素，但实际有三个，于是自动补零为torf[2][2]={{12,14},{16,0}}。*ptr指第一行第一个元素，为12，*(ptr+2)向后两个元素为16。
 2. 对于b,forf[2][2]中应有4个元素，但实际有三个，于是自动补零为torf[2][2]={{12,0},{14,16}}。*ptr指第一行第一个元素，为12，*(ptr+2)向后两个元素为14。
 
 ## 2.在下面的代码中，**ptr 和 **(ptr + 1) 的值分别是什么？（转复5）
 ```
a.
int (*ptr)[2];
int torf[2][2] = {12, 14, 16};
ptr = torf;

b.
int (*ptr)[2];
int fort[2][2] = { {12}, {14,16} };
ptr = fort;
```
**解答**：

 1. 对于a，torf[2][2]中应有4个元素，但实际有三个，于是自动补零为torf[2][2]={{12,14},{16,0}}。ptr指针指向一个有两个元素的数组，即{12,14}，*ptr指针指向数组的地址，即{12,14}的首地址，**ptr即首元素12。同理，**(ptr+1)指16。
 2.  对于b，forf[2][2]中应有4个元素，但实际有三个，于是自动补零为torf[2][2]={{12,0},{14,16}}。ptr指针指向一个有两个元素的数组，即{12,0}，*ptr指针指向数组的地址，即{12,14}的首地址，**ptr即首元素12。同理，**(ptr+1)指14。

## 3.正确声明以下各变量：（转复7）

 - a.digits 是一个内含 10 个 int 类型值的数组
 - b.rates 是一个内含 6 个 float 类型值的数组
 - c.mat 是一个内含 3 个元素的数组，每个元素都是内含 5 个整数的数组
 - d.psa 是一个内含 20 个元素的数组，每个元素都是指向 char 的指针
 - e.pstr 是一个指向数组的指针，该数组内含 20 个 char 类型的值
 ```
a. int digits[10];
b. float rates[6];
c. int mat[3][5];
d. char *psa[20];
e. char (*pstr)[20];
```

# 第十一章 字符串和字符串函数
## 1.下面的程序将打印什么？（转复3）
```c
#include <stdio.h>
#include <string.h>
int main(void)
{
    char food [] = "Yummy";
    char *ptr;

    ptr = food + strlen(food);
    /*
    strlen(food)大小为5，food退化为指针指向首元素Y，加5后指向'\0'
    */
    while (--ptr >= food)
    /*
    ptr先自减一次，指向'y'的地址，符合>=food(首地址)
    */
        puts(ptr); //于是从'y'开始打印，直至到'\0'为止，后续由于--ptr，指针前移，直到首地址
    return 0;
}
```
最终打印：
```
y
my
mmy
ummy
Yummy
```
# 2.下面的练习涉及字符串、循环、指针和递增指针。（转复5）
```c
#include <stdio.h>
char *pr(char *str)
{
    char *pc; //定义指针
    pc = str;
    while (*pc)
        putchar(*pc++); //循环体正向打印str
    do {
        putchar(*--pc); //逆向打印str
    } while (pc - str);
    return (pc);//最终pc==str
}
int main() {
    char *x;
    x = pr("Ho Ho Ho!");
    return 0;
}
```
回答以下问题：
a. 将打印什么？
```
Ho Ho Ho!!oH oH oH
```

b. x 是什么类型？
```
char类型的指针
```

c. x 的值是什么？
```
指向字符串的首地址
```

d. 表达式 *- -pc 是什么意思？与 --*pc 有何不同？
```
*--pc：前缀自减。先将指针 pc 减 1，然后取出该位置的值
--*pc：先解引用取出 *pc，然后对取出的字符进行自减
```
e. 如果用 *pc-- 替换 *- -pc，会打印什么？
```
会无限循环
```

f. 两个 while 循环用来测试什么？
```
第一个 while 测试正序遍历,第二个 do-while 测试逆序遍历
```
g. 如果 pr() 函数的参数是空字符串，会怎样？
```
 pc 指向 \0，第一个循环不执行。进入 do-while，*--pc 会使指针退到数组前面（越界访问）
 ```

h. 必须在主调函数中做什么，才能让 pr() 函数正常运行？
```
主调函数传入的必须是可修改的字符数组,不能是字符串字面量
```

# 3.下面的程序会打印出什么？（转复7）
```c
#include <stdio.h>
#include <string.h>
#define M1 "How are ya, sweetie? "
char M2[40] = "Beat the clock.";
char * M3 = "chat";
int main(void)
{
    char words[80];
    printf(M1); //打印 "How are ya, sweetie? "（不换行）。
    puts(M1); //打印同上，并在末尾补一个换行。
    puts(M2); //打印 "Beat the clock." 并换行。
    puts(M2 + 1); //跳过首字母 'B'，打印 "eat the clock." 并换行。
    strcpy(words, M2);
    strcat(words, " Win a toy."); //words 变成 "Beat the clock. Win a toy."。
    puts(words); ///打印words并换行。
    words[4] = '\0'; //改为：Beat\0the clock. Win a toy.
    puts(words); //打印 "Beat" 并换行。
    while (*M3) //M3 初始指向 'c'
    puts(M3++); 
    /*循环体语句，依次：
    打印 "chat"，指针后移指向 'h'。
    打印 "hat"，指针后移指向 'a'。
    打印 "at"，指针后移指向 't'。
    打印 "t"，指针后移指向 '\0'，结束循环
    */
    puts(--M3); //指针退回 't'，打印 "t"。
    puts(--M3); //指针再退回 'a'，打印 "at"。
    M3 = M1; //M3 指向宏替换后的字符串字面量。打印 "How are ya, sweetie? "。
    puts(M3);
    return 0;
}
```
最终打印：
```
How are ya, sweetie? How are ya, sweetie? 
Beat the clock.
eat the clock.
Beat the clock. Win a toy.
Beat
chat
hat
at
t
t
at
How are ya, sweetie? 
```
# 第十二章 存储类别、链接和内存管理
## 1.考虑下面两行代码，就输出的结果而言有何异同：（转复6）
```c
int * p1 = (int *)malloc(100 * sizeof(int));
int * p1 = (int *)calloc(100, sizeof(int));
```
  - 相同：
  都在堆区（Heap）动态分配了 100 个 int 类型的内存空间，都返回一个指向该内存首地址的指针。
  - 不同：
  malloc 只是分配内存，不会初始化，calloc 分配内存后，会自动把这块内存全部初始化。

## 2.下面的变量对哪些函数可见？程序是否有误？（转复7）
```c
/* 文件 1 */
int daisy;
int main(void)
{
    int lily;
    // ...
}
int petal()
{
    extern int daisy, lily;
    // ...
}

/* 文件 2 */
extern int daisy;
static int lily;
int rose;
int stem()
{
    int rose;
    // ...
}
void root()
{
    // ...
}
```

 1. daisy（全局变量）：在文件 1 定义，默认是外部链接。所以在文件 2 里用 extern int daisy; 声明后，文件 2 的所有函数都能看见它。文件 1 的 petal 也能看见。

 2. rose（全局变量）：在文件 2 定义。但由于文件 1 没有 extern 声明它，所以在文件 1 中不可见。在文件 2 的 stem() 中，局部变量 int rose; 会遮蔽全局的 rose。

 3. lily：
在文件 1 的 main 中，lily 是普通局部变量（栈区）。在文件 1 的 petal 中，写了 extern int lily, extern 只能用于引用全局变量，而 main 里的 lily 只是局部变量，生命周期在 main 结束就没了，其他函数根本无法通过 extern 访问它。在文件 2 中，static int lily; 是一个内部链接（私有）的全局变量，只能在文件 2 中用。它和文件 1 里的任何 lily 都毫无关系。

## 3.下面程序会打印什么？（转复8）
```c
#include <stdio.h>
char color = 'B';
void first(void);
void second(void);

int main(void)
{
    extern char color;
    printf("color in main() is %c\n", color);
    first();
    printf("color in main() is %c\n", color);
    second();
    printf("color in main() is %c\n", color);
    return 0;
}

void first(void)
{
    char color;
    color = 'R';
    printf("color in first() is %c\n", color);
}

void second(void)
{
    color = 'G';
    printf("color in second() is %c\n", color);
}
```

 1. 文件顶部定义了全局变量 color = 'B'。
 2. main 函数：里面的 extern char color; 只是告诉编译器“我要用外部的全局 color”。打印 B。
 3. first 函数：内部重新定义了 char color;（局部变量）。局部变量会遮蔽（Shadow）全局变量。把它赋值为 'R' 并打印 R。全局变量 color 毫无波澜，依然是 'B'。
 4. 回到 main 函数：打印全局 color，依然是 B。
 5. second 函数：内部没有定义局部变量，直接使用了全局 color。赋值为 'G' 并打印 G。此时，内存中的全局变量被永久修改了。
 6. 回到 main 函数：再次打印全局 color，为G。

# 第十三章 文件输入/输出
## 1.下面的程序有什么问题？（转复1）
```c
int main(void)
{
    int * fp; //操作文件，指针用FILE*类型，而非int*
    int k;

    fp = fopen("gelatin"); //缺少第二个参数，无操作模式
    for (k = 0; k < 30; k++)
        fputs(fp, "Nanette eats gelatin."); //参数顺序写反
    fclose("gelatin"); //参数错误，应传入fp指针
    return 0;
}
```
## 2. a.分别用 fprintf() 和 fwrite() 存储 8238201 有何区别？b.分别用 putc() 和 fwrite() 存储字符 S 有何区别？

 - a.：fprintf()：会将数字转换为文本字符串。它会把 8238201 变成 7 个 ASCII 字符，fwrite()：直接将内存中的二进制补码原封不动地写入文件。
 - b.：putc()：把一个字符写入文件。它占用 1 个字节。

fwrite()：如果你只写 fwrite(&ch, sizeof(char), 1, fp)，那它和 putc 的效果完全一样，也是 1 个字节。但如果你用 fwrite 写的是一个字符串 "S"，它可能会把后面的 \0 也一起按字节写入

## 3."a+"、"r+" 和 "w+" 模式打开的文件都是可读写的。哪种模式更适合用来更改文件中已有的内容？（转复9）

 1. "r+"（读写模式）：
文件必须已经存在。他保留文件原有内容，读写指针在文件开头。你可以定位到文件的任意位置进行读取或修改。
适用修改文件中间的内容
 2. "w+"（写读模式）：
如果文件存在，原内容会被瞬间清空（截断为0字节）；如果不存在，则创建新文件。适用覆盖重写整个文件。
 3. "a+"（追加读模式）：
文件不存在则创建。他允许读取整个文件，但所有的写入操作只能强制追加到文件末尾，无法用指针去覆盖文件中间的内容。适用写日志，只能往后加，不能改前面的。

综上所述，为“r+”

# 第十四章 结构和其他数据形式
 ## 1.考虑下面的程序段：（转复7）
 ```c
struct name {
    char first[20];
    char last[20];
};

struct bem {
    int limbs;
    struct name title;
    char type[30];
};

struct bem * pb;
struct bem deb = {
    6,
    { "Berbnazel", "Gwolkapwolk" },
    "Arcturan"
};
pb = &deb;
```

 - a. 下面的语句分别打印什么？
printf("%d\n", deb.limbs);
printf("%s\n", pb->type);
printf("%s\n", pb->type + 2);
 - b. 如何用结构表示法（两种方法）表示 "Gwolkapwolk"？
```
a.
6
Arcturan （通过指针访问）
cturan （pb->type 指向字符串首地址，+2 偏移 2 个字符，跳过了 A 和 r）

b.
1.deb.title.last
2.pb->title.last
```
## 2.假设有如下结构：（转复10）
```c
struct gas {
    float distance; //距离
    float gals; //加仑
    float mpg; //每消耗一加仑行走的距离
};
```

 - a. 设计一个函数，接受 struct gas 类型的参数。假设传入的结构包含 distance 和 gals 信息。该函数为 mpg 成员计算正确的值，并把值返回该结构。
 - b. 设计一个函数，接受 struct gas 类型的参数。假设传入的结构包含 distance 和 gals 信息。该函数为 mpg 成员计算正确的值，并把该值赋给合适的成员。
 ```c
 // a.
 struct gas a (struct gas g) {
    g.mpg = g.distance / g.gals;
    return g; 
}

// b.
void b (struct gas *g) {
    g->mpg = g->distance / g->gals;
}
```
## 3.声明 4 个函数，并初始化一个指向这些函数的指针数组。每个函数都接受两个 double 类型的参数，返回 double 类型的值。另外，用两种方法使用该数组调用带 10.0 和 2.5 实参的第 2 个函数。（转复13）
```c
#include<stdio.h>
double a(double x,double y){return x+y;}
double b(double x,double y){return x-y;}
double c(double x,double y){return x*y;}
double d(double x,double y){return x/y;}
int main (){
double (*z[4])(double, double) = { a, b, c, d };
double n1=z[1](10.0,2.5);
double n2=(*z[1])(10.0,2.5);
return 0;
}
```
# 第十五章 位操作
## 1.把下面的十进制转换为二进制
>3
>13
>59
>119
```
0011
1101
00111011
11110111
```
 ## 2.因为 ASCII 码只使用最后 7 位，所以有时需要用掩码关闭其他位，其相应的二进制掩码是什么？分别用十进制、八进制和十六进制来表示这个掩码。（转复5）
```
二进制：0111 1111
八进制：177
十进制：127
十六进制：7F
然后将其与目标数据做按位与（&）操作
```
## 3.*= 2 等同于 <<= 1？ += 是否等同于 |=？（转复6）
```
对于无符号整数（unsigned）且不溢出时，完全等价。 左移 1 位就是乘以 2。现代编译器（如 GCC）在底层甚至会把 *= 2 优化成移位指令，因为移位指令在 CPU 层面执行速度更快。

但在有符号负数时不同：对负数进行左移在 C 标准中是未定义行为（UB），而乘以 2 是确定的。

在这道题里，bitval 每次左移（1, 2, 4, 8...），它的二进制永远只有一个 1。而 mask 之前累加的值对应的位置都是 0，所以相加不会产生进位，此时 += 和 |= 结果一样。
```
# 第十六章 C预处理器和C库
## 1.下面的几组代码由一个或多个宏组成，其后是使用宏的源代码。在每种情况下代码的结果是什么？这些代码是否是有效代码？（假设其中的变量已声明）（转复1）
```
a.
#define FPM 5280 /*每英里的英尺数*/
dist = FPM * miles;

b.
#define FEET 4
#define POD FEET + FEET
plort = FEET * POD;

c.
#define SIX = 6;
nex = SIX;

d.
#define NEW(X) X + 5
y = NEW(y);
berg = NEW(berg) * lob;
est = NEW(berg) / NEW(y);
nilp = lob * NEW(-berg);
```

 - a.有效,dist = 5280 * miles完全正确
 - b.宏展开后变成了 plort = 4 * 4 + 4;。因为乘号 * 优先级高于加号 +，结果是 16 + 4 = 20。而本意应该是 4 * (4 + 4) = 32
 - c.语法错误。预处理后变成 nex = = 6;;，因为宏里多了一个等号
 - y = NEW(y); 变成 y = y + 5,berg = NEW(berg) * lob; 变成 berg = berg + 5 * lob;（由于优先级，本该先算加法，现在变成了先算乘法，结果错误）。
est = NEW(berg) / NEW(y); 变成 est = berg + 5 / y + 5,nilp = lob * NEW(-berg); 变成 nilp = lob * -berg + 5

## 2.假设在测试程序时要暂时跳过一块代码，如何在不移除这块代码的前提下完成这项任务？（转复8）
```
使用 #if 0 ... #endif 预处理指令,方便随时切换,把 0 改成 1 就可以恢复编译
```

## 3.假设 scores 是内含 1000 个 int 类型元素的数组，要按降序排序该数组中的值。假设你使用 qsort() 和 comp() 比较函数。（转复13）
a. 如何正确调用 qsort()？
b. 如何正确定义 comp()？
```
a.调用： qsort(scores, 1000, sizeof(int), comp);
b.定义：
int comp(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}


