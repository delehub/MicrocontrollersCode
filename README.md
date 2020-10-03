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
## 程序模块化设计

#### 案例

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

4. 其中 a 就是左边对象。

   3. **其中“=”就是关键字。**写法跟我们平时用的等于号是一样，但是在 C 语言里不是等于的意思，而是代
      表赋值的意思。
   4. 它是**代表中文含义的“给”**，而**不是用于判断的“等于”**，跟等于号是两码事。
   5. 其中 **b 就是右边对象**。
   6. 其中**分号“;”**代表一条语句的结束符。
   7. 注意C语言程序是    **等于是  --------》 " == "**

   ### 单片机串口打印部分函数

   ```c
   void View(unsigned long u32ViewData)
   {
       static unsigned char Su8ViewBuffer[43];
       code unsigned char Cu8_0D_0A[]={0x0d,0x0a,0x00};
       code unsigned char Cu8Start[]={"开始..."};
       static unsigned char Su8FirstFlag=0;
       static unsigned int Su16FirstDelay;
       if(0==Su8FirstFlag)
       {
           Su8FirstFlag=1;
           for(Su16FirstDelay=0;Su16FirstDelay<10000;Su16FirstDelay++);
           SendString(Cu8Start);
           SendString(Cu8_0D_0A);
           SendString(Cu8_0D_0A);
       }
       to_BufferData(u32ViewData,Su8ViewBuffer,1);
       SendString(Su8ViewBuffer);
       to_BufferData(u32ViewData,Su8ViewBuffer,2);
       SendString(Su8ViewBuffer);
       to_BufferData(u32ViewData,Su8ViewBuffer,3);
       SendString(Su8ViewBuffer);
       to_BufferData(u32ViewData,Su8ViewBuffer,4);
       SendString(Su8ViewBuffer);
       SendString(Cu8_0D_0A);
   }
   void to_BufferData(unsigned long u32Data,unsigned char *pu8Buffer,unsigned char u8Type) 
   {
       code unsigned char Cu8Array1[]={0xB5,0xDA,0x4E,0xB8,0xF6,0xCA,0xFD,0x00};
    	code unsigned char Cu8Array2[]="十进制:";
   	    code unsigned char Cu8Array3[]="十六进制:";
    	code unsigned char Cu8Array4[]="二进制:";
       static unsigned char Su8SerialNumber=1;
       static unsigned int  Su16BufferCnt;
       static unsigned int  Su16TempCnt;
       static unsigned int  Su16TempSet;
       static unsigned long Su32Temp1;
       static unsigned long Su32Temp2;
       static unsigned long Su32Temp3;
       static unsigned char Su8ViewFlag;
       if(1==u8Type)
     	{
           for(Su16BufferCnt=0;Su16BufferCnt<7;Su16BufferCnt++)
   	        {
   	           pu8Buffer[Su16BufferCnt]=Cu8Array1[Su16BufferCnt];
     	    }
   	        pu8Buffer[2]=Su8SerialNumber+'0';
      	    pu8Buffer[Su16BufferCnt]=0x0d;
      	    pu8Buffer[Su16BufferCnt+1]=0x0a;
   	        pu8Buffer[Su16BufferCnt+2]=0;
    	    Su8SerialNumber++;
   	        return;
      	}
       else if(2==u8Type)
   	    {
   	        for(Su16BufferCnt=0;Su16BufferCnt<7;Su16BufferCnt++)
   	        {
   		       pu8Buffer[Su16BufferCnt]=Cu8Array2[Su16BufferCnt];
   	        }
   	       Su32Temp1=1000000000;
   		   Su32Temp2=10;
   		   Su16TempSet=10;
     	}
       else if(3==u8Type)
    	{
   	        for(Su16BufferCnt=0;Su16BufferCnt<9;Su16BufferCnt++)
   	        {
   		       pu8Buffer[Su16BufferCnt]=Cu8Array3[Su16BufferCnt];
   	        }
   	        Su32Temp1=0x10000000;
   		    Su32Temp2=0x00000010;
   		    Su16TempSet=8;	
       }
       else 
       {
   	        for(Su16BufferCnt=0;Su16BufferCnt<7;Su16BufferCnt++)
   	        {
   		       pu8Buffer[Su16BufferCnt]=Cu8Array4[Su16BufferCnt];
   	        }
   	        Su32Temp1=0x80000000;
   		    Su32Temp2=0x00000002;
   		    Su16TempSet=32;	
      	}
       Su8ViewFlag=0;
       for(Su16TempCnt=0;Su16TempCnt<Su16TempSet;Su16TempCnt++)
       {
          Su32Temp3=u32Data/Su32Temp1%Su32Temp2;
   	       if(Su32Temp3<10)
   	       {
    	        pu8Buffer[Su16BufferCnt]=Su32Temp3+'0';
   	       }
   	       else
   	       {
    	        pu8Buffer[Su16BufferCnt]=Su32Temp3-10+'A';
   	       }
   	       if(0==u32Data)
   	       {
   		       Su16BufferCnt++;
   		       break;
   	       }
   	       else if(0==Su8ViewFlag)
   	       {
   	           if('0'!=pu8Buffer[Su16BufferCnt])
    	       {
                  Su8ViewFlag=1;
   			       Su16BufferCnt++;
              }
   	       }
   	       else
   	       {
   	           Su16BufferCnt++;
   	       }
          Su32Temp1=Su32Temp1/Su32Temp2;
       }
       pu8Buffer[Su16BufferCnt]=0x0d;
       pu8Buffer[Su16BufferCnt+1]=0x0a;
       pu8Buffer[Su16BufferCnt+2]=0;
   }
   void SendString(unsigned char *pu8String)   
   {
     static unsigned int Su16SendCnt;
     static unsigned int Su16Delay;
     SCON=0x50;
     TMOD=0X21;
     TH1=TL1=256-(11059200/12/32/9600);  
     TR1=1;
     ES = 0; 
     TI = 0;
     for(Su16SendCnt=0;Su16SendCnt<43;Su16SendCnt++)
     {
        if(0==pu8String[Su16SendCnt])
   	     {
   	         break;
   	     }
   	     else
   	     {
           SBUF =pu8String[Su16SendCnt]; 
           for(Su16Delay=0;Su16Delay<800;Su16Delay++);
   		   TI = 0;
   	     }
     }
   }
   
   
   ```

   

   ### 赋值语句的覆盖性

   #### 案例 数字交换

   #### demo 1

   ```c
   //view()功能相当于printf()函数，view()单片机的串口打印功能
   void main() //主函数
   {
       unsigned char a=1; //定义的变量 a 被分配了 1 个字节的 RAM 空间，保存的数据被初始化成 1。
       unsigned char b=5; //定义的变量 b 被分配了 1 个字节的 RAM 空间，保存的数据被初始化成 5。
       b=a; //第一步：为了交换，先把 a 的数赋值给 b。
       a=b; //第二步：为了交换，再把 b 的数赋值给 a。
       View(a); //把第 1 个数 a 发送到电脑端的串口助手软件上观察。
       View(b); //把第 2 个数 b 发送到电脑端的串口助手软件上观察。
       while(1)
       {
       }
   }
   //代码分析
   //由于b的数据在执行完“第一步”后，b自己原来的数据5被覆盖丢失了变成新的数据1，
   //接着执行“第二步”后，此时相当于把 b的新数据1赋值给a，并没有5！所以a和b的数据都是1
   
   ```

   ```c
   void main() //主函数
   {
          unsigned char a=1;   //定义的变量a被分配了1个字节的RAM空间，保存的数据被初始化成1。
          unsigned char b=5;   //定义的变量b被分配了1个字节的RAM空间，保存的数据被初始化成5。
          unsigned char t;     //定义一个第三方变量t，用来临时寄存数值。
          t=b; //第一步：为了避免b的数据在赋值后被覆盖丢失，先寄存一份在第三方变量t那里。
          b=a; //第二步：把a的数赋值给b，b原来的数据虽然丢失，但是b在t变量那里有备份。
          a=t; //第三步：再把b在t变量里的备份赋值给a。注意，这里不能用b，因b原数据已被覆盖。
          View(a);   //把第1个数a发送到电脑端的串口助手软件上观察。
      	   View(b);   //把第2个数b发送到电脑端的串口助手软件上观察。
      while(1)  
      { 
      }
   }
   // 代码分析
   //中间变量t  b=a; b--> t <--a 
   
   ```

   z


## 进制

## 1.二进制 字节单位

**二进制**：二进制数只有0和1两个数码，它的每一位都可以用电子元件来实现，且运算规则简单，运算电路也容易实现。

**位**(bit)：位的英文名是用bit来表示。一个变量的位数越大就意味着这个变量的取值范围越大。一个单片机的位数越大，就说明这个单片机一次处理的数据范围就越大，意味着运算和处理速度就越快。

**字节**(Byte)： 什么是字节？字节是计算机很重要的一个基本单位，一个字节有8位。（1B = 8bit）

**字：**16个位(bit)为一个字，它代表计算机处理指令或数据的二进制数位数。

**位是最小的存储单位，每一个位存储一个1位的二进制码，一个字节由8位组成。而字通常为16、32或64个位组成。**

```markdown
千，1KB=2的10次方＝bai1024B，du
兆，1MB=2的20次方zhi＝dao1024*1024B＝1024KB，
吉，1GB=2的30次方＝1024*1024*1024B=1024MB，
太，1TB=2的40次方＝1024*1024*1024*1024B=1024GB,
拍，1PB=2的50次方＝1024*1024*1024*1024*1024B=1024TB,
艾，1EB=2的60次方＝1024*1024*1024*1024*1024*1024B=1024PB,
泽，1ZB=2的70次方＝1024*1024*1024*1024*1024*1024*1024B=1024EB,
尧，1YB=2的80次方＝1024*1024*1024*1024*1024*1024*1024*1024B=1024ZB
```

***变量取值范围：***

```c
 unsigned char的变量占用1个字节RAM，共8位，取值范围是从0到255。 
 unsigned int的变量占用2个字节RAM，共16位，取值范围是从0到65535。
 //对于51内核的单片机，unsigned int的变量是占用2个字节。
 //如果是在32位的stm32单片机，unsigned int的变量是占用4个字节的，所以不同的单片机不同的编译器是会有一些差异的。
unsigned long的变量占用4个字节RAM，共32位，根据前面LED灯的例子，取值范围是从0到4294967295。 

```



## **2.进制**

###  数制：

1.   进位制：表示数时，仅用一位数码往往不够用，必须用进位计数的方法组成多位数码。多位数码每一位的构成以及从低位到高位的进位规则称为进位计数制，简称进位制。
2.   基 数：进位制的基数，就是在该进位制中可能用到的数码个数。
3.   位 权（位的权数）：在某一进位制的数中，每一位的大小都对应着该位上的数码乘上一个固定的数，这个固定的数就是这一位的权数。权数是一个幂。

### 二进制：（B）

1. 数码为：0、1；基数是2。
2. 运算规律：逢二进一，即：1＋1＝10
3. 加法规则：0+0=0，0+1=1，1+0=1，1+1=10
4. 乘法规则：0.0=0， 0.1=0 ，1.0=0，1.1=1
5. 二进制数只有0和1两个数码，它的每一位都可以用电子元件来实现，且运算规则简单，相应的运算电路也容易实现。

### 十进制：(D)

1. 数码为：0～9；基数是10。
2. 运算规律：逢十进一，即：9＋1＝10
3. 任意一个十进制数都可以表示为各个数位上的数码与其对应的权的乘积之和，称权展开式。

### 八进制：(O)

1. 数码为：0～7；基数是8。
2. 运算规律：逢八进一，即：7＋1＝10

### 16进制：(H)

1. 数码为：0～9、A～F；基数是16。
2. 运算规律：逢十六进一，即：F＋1＝10
3. 16进制表示为 0X?? 
4. 16进制转成二进制 0X?? ？对应二进制数

### 结论：

**①一般地，N进制需要用到N个数码，基数是N；运算规律为逢N进一。**

**②如果一个N进制数M包含ｎ位整数和ｍ位小数, (an-1 an-2 … a1 a0 · a－1 a－2 … a－m)2**

**则该数的权展开式为：**

**(M)2 ＝ an-1×Nn-1 ＋ an-2 ×Nn-2 ＋  …  ＋a1×N1＋ a0 ×N0＋a－1 ×N-1＋a－2 ×N-2＋… ＋a－m×N-m**                          

**③由权展开式很容易将一个N进制数转换为十进制数**

**常见的进制转换**

![img](https://i.loli.net/2020/09/19/GuZlvoYdQxJmhPi.jpg)

## **3.数制转换**

### **1.二进制数与八进制数的相互转换**

（1）二进制数转换为八进制数： 将二进制数由小数点开始，整数部分向左，小数部分向右，每3位分成一组，不够3位补零，则每组二进制数便是一位八进制数。

![img](https://i.loli.net/2020/09/19/Hot9kAlFDuiP76M.jpg)

八进制数转换为二进制数：将每位八进制数用3位二进制数表示。	

![img](https://i.loli.net/2020/09/19/ALBvMQwYSk8dJl7.jpg)

### **2.二进制数与十六进制数的相互转换**

1.二进制数与十六进制数的相互转换，按照每4位二进制数对应于一位十六进制数进行转换。

![img](https://i.loli.net/2020/09/19/OapsivEVWHgkCAU.jpg)

### **3.十进制数转换为二进制数**

采用的方法 — 基数连除、连乘法

原理：将整数部分和小数部分分别进行转换。整数部分采用基数连除法，小数部分采用基数连乘法再合并。

1. 整数部分采用基数连除法，先得到的余数为低位，后得到的余数为高位。
2. 小数部分采用基数连乘法，先得到的整数为高位，后得到的整数为低位。

![img](https://i.loli.net/2020/09/19/q7RrQtvUgOcw6Jj.jpg)

采用基数连除、连乘法，可将十进制数转换为任意的N进制数。

![img](https://i.loli.net/2020/09/19/ealxOqtJTBrA6hD.jpg)

![img](https://i.loli.net/2020/09/19/5RcpvmB7n43NETd.jpg)

![img](https://i.loli.net/2020/09/19/Fg2xRXKNhPOuJYZ.jpg)

![img](https://i.loli.net/2020/09/19/MONsuW4pKq6DPXm.jpg)

![img](https://i.loli.net/2020/09/19/BGfv7jkQRD3EuFe.jpg)

![img](https://i.loli.net/2020/09/19/WslAwO6dqHpi7gK.jpg)

![img](https://i.loli.net/2020/09/19/FVyrZusMk9IeAUj.jpg)

![img](https://i.loli.net/2020/09/19/H3Jhfjy8PbgDOMZ.jpg)
