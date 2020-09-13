# MicrocontrollersPlan
## C程序设计复习
## 单片机复习
1. 单片机案例实验与仿真 (51单片机100实例源码)
2. C51单片机开源项目合集
3. 单片机编程技巧与分析(手把手教你单片机程序框架 )(从单片机基础到程序框架.pdf)
4. 项目课程设计

### 参考资料 吴坚鸿《从单片机基础到程序框架》 
===================================================================================
## 复习1.md 程序模块化设计
### 程序模块化设计

## 案例

```c
#include"REG52.H"   //进入主程序前的区域：头文件包含

sbit beep_dr=P3^4; //进入主程序前的区域：宏定义
sbit led_dr=P1^6; //进入主程序前的区域：宏定义

unsigned long i; //进入主程序前的区域：内存分配

void main() //主程序入口，即将进入初始化区域
{
    beep_dr=0; //第一步：初始化区域：蜂鸣器开始鸣叫。
    for(i=0;i<6250;i++); //第二步：初始化区域：延时 0.5 秒左右。也就是蜂鸣器鸣叫的持续时间。
    beep_dr=1; //第三步：初始化区域：蜂鸣器停止鸣叫。
	while(1) //执行完上面的初始化区域，即将进入循环区域
    {
        led_dr=0; //第四步：循环区域：LED 开始点亮。
        for(i=0;i<6250;i++); //第五步：循环区域：延时 0.5 秒左右。也就是 LED 点亮的持续时间。
        led_dr=1; //第六步：循环区域：LED 开始熄灭。
        for(i=0;i<6250;i++); //第七步：循环区域：延时 0.5 秒左右。也就是 LED 熄灭的持续时间。
    } 
    //执行完上面第七步后，单片机又马上返回到上面第四步继续往下执行。
}
```

```c
//...进入主程序前的区域
main.c
// 官方库文件导入 
#include<reg51.h>
// 第三方库文件导入(个人)
#include"led.h"
#include"oled.h"
.....
// 模块引脚定义
void main()
{
     Iint();//模块初始化
     while(1)
     {
         //代码执行部分
         //代码循环部分
     
     }
    
}

void Iint(void)
{
    oled_Iint();
    led_Iint();
    beep_Iint();
    dht_11_Iint();
    //....... 
}

void main()
{
    //...初始化区域
    while(1)
    {
      //...循环区域
     // led_on;
     // led_off;
    }
}
```

### 变量定义

定义变量的关键字。常用有 3 种容量的变量，每种变量的取值范围不一样。

1. 第一种是”unsigned char”  **0~2^8-1**
   变量，取值范围从 0 到 255，占用 RAM 一个字节，比喻成一房一厅。

2. 第二种是”unsigned int”变量，取值  **0~2^16-1**
   范围从 0 到 65535，占用 RAM 两个字节，比喻成两房一厅。

3. 第三种是“unsigned long”变量，取值范围从 0  
   到 4294967295，占用 RAM 四个字节，比喻成四房一厅。**0~2^32-1**

**注意：多说一句，上述的变量范围是针对本教程所用的单片机，当针对不同的单片机时上述变量的范围可能会有一些小差异，比如在 stm32 单片机中，unsigned int 的字节数就不是两个字节，而是四个字节，这些都是由所选的编译器决定.**

定义变量的语法格式

1. 关键字，变量名，分号

   ```C
   unsigned char a;
   //其中 unsigned char 就是关键字，a 就是变量名，分号”;”就是一条语句的结束符号
   ```

2. 关键字标识符一些注意点

   ```c
   /*不合法标识符*/
   unsigned char 3a; //不合法，第一个字符不能是数字。
   unsigned char char; //不合法，char 是编译器已征用的关键字。
   unsigned char a b; //不合法，ab 是一个变量名，a 与 b 的中间不能有空格。
   unsigned char a,b; //合法，a 和 b 分别是一个独立的变量名，a 与 b 的中间可以用逗号隔开。
   
   /*合法标识符*/
   unsigned char a; //合法。
   unsigned char abc; //合法。
   unsigned char _ab; //合法。
   unsigned char _3ab; //合法。
   unsigned char a123; //合法。
   unsigned char a12ced; //合法。
   ```

   **<u>规则：</u>**

   1. **变量名的第一个字符不能是数字。**
   2. **必须是字母或者下划线，字母或者下划线后面可以带数字。**
   3. **一个变量名之间的字符不能带空格，两个独立变量名之间也不能用空格隔开（但是两个独立变量**
      **名之间可以用逗号隔开）。**
   4. **变量名不能跟编译器已征用的关键字重名，不能跟函数名重名。**

### 变量 RAM关系

1. 定义变量与 RAM 的内在关系。**当我们定义一个变量时，相当于向单片机申请了一个 RAM 空间。**C 编译器
   会**自动为这个变量名分配一个 RAM 空间**，**每个字节的 RAM 空间都有一个固定唯一的地址**。

   ```c
   unsigned char a; //a 占用一个字节的 RAM 空间，这个空间的地址由 C 编译自动分配。
   unsigned char b; //b 占用一个字节的 RAM 空间，这个空间的地址由 C 编译自动分配。
   unsigned char c; //c 占用一个字节的 RAM 空间，这个空间的地址由 C 编译自动分配。
   ```

2. 只需要记住这个变量的名称就可以了。**操作某个变量名，就相当于操作某个对应地址的 RAM 空间**。

### 变量的赋值

1. 赋值：把右边对象的内容复制一份给左边对象。

2. 特性：就是覆盖性，左边对象原来的内容会被右边对象复制过来的新内容所覆盖。

3. 格式

   1. 赋值语句的格式。赋值语句的语法格式由 4 部分组成：左边对象，关键字，右边对象，分号。

   ```c
   unsigned char a;
   unsigned char b=3;    
   a = b;
   ```
   
2. 其中 a 就是左边对象。
   3. **其中“=”就是关键字。**写法跟我们平时用的等于号是一样，但是在 C 语言里不是等于的意思，而是代表赋值的意思。
   4. 它是**代表中文含义的“给”**，而**不是用于判断的“等于”**，跟等于号是两码事。
   5. 其中 **b 就是右边对象**。
   6. 其中**分号“;”**代表一条语句的结束符。
   7. 注意C语言程序是    **等于是  --------》 " == "**
