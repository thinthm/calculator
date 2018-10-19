//
//  operate.h
//  area.calculator.calCho.header.operate
//  version 1.0.0.0002
//  Created by Wei Zhou on 2018/4/1 12:35
//  Copyright © 2017年 zhouwei. All rights reserved.
//
/******************************************************************************
//  @Update record:
//  2018/4/1    14:15   1.0.0.0001 
//      int getOperate(char *);
//      int header_getFirstOperate(void); 
//      void header_changeBufferToSuffix_sendToBuffer(void)               
//      void header_count(void)  
//  2018/4/1    14:28   1.0.0.0002
//      int getOperate(char *)
//  2018/4/1    14:50   1.0.0.0003
//      int getOperate(char string[])
//  重大修复  
//  2018/4/2    15:07   1.0.1.0021  
//  修复了运算符如ln太短，但是输入以测试的字符串太长，
//  可能导致匹配到后面的运算符的bug，如ln2*log100，匹配时匹配到了log，
//  因为匹配结构体中时log在ln前面
******************************************************************************/

#ifndef operate_h
#define operate_h

#include "common.h"

#define MAXOP     100
#define MAXVAL    100
#define BUFSIZE   200
#define OPLEN_MAX 8

#define PO_FLOAT  1e6
#define NE_FLOAT  1e-6

#define YES       1
#define NO        0
#define MYERROR   -1
#define SCTERROR  -32767

#define PI        3.14159265358979
#define E         2.718281828459
#define PIPI      "3.14159265358979"
#define EE        "2.718281828459"
#define DPI       PI/128

#define NUMBER    '0'

#define SQRT      '['
#define FABS      '|'

#define SIN       's'
#define COS       'c'
#define TAN       't'
#define SINH      'S'
#define COSH      'C'
#define TANH      'T'

#define LN        'l'
#define LOG       'L'

#define ARCSIN    'i'   //  取第5个字符i，注意操作符不能用数字
#define ARCCOS    'o'
#define ARCTAN    'a'

#define NEWFORMULA 0
#define QUIT       -1
#define RETURN     -2

extern int g_administrator;

double g_lfValue[MAXVAL];       //  值栈
char g_cBuffer[BUFSIZE];        //  输入流栈
char g_cSuffix[BUFSIZE];        //  后缀式栈
char g_cStack[BUFSIZE];         //  待处理栈
int g_dValp = 0;
int g_dBufp = 0;
int g_dSufp = 0;
int g_dStap = 0;

int g_dLastIsNumber = 0;
int g_dCouldAdd0 = 0;
double g_lfLastValue = 0;
int g_dPrecision = 6;

void myPrintf(char string[]);
double arcsin(double num);
double arccos(double num);
double arctan(double num);
int  operateLevel(int c);
void sendToBuffer(int c); 
int  getFromBuffer(void);
void sendToSuffix(int c); 
int  getFromSuffix(void);
void sendToSuffix(int c);
void pushToValue(double f); 
double nextValue(void);
int  mathOperate(char c);
int  getOperate(char string[]);
int  whenCountGetOperate(char string[]);
int  d_digits(double num);

/******************************************************************************
* @file     operate.h
* @function void myPrintf(int num)
* @describe 测试的时候显示用到的函数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void myPrintf(char string[])
{
    static int i = 0;

    printf("\n[ %s ]\n", string);
    printf(" ---------------------------------------------\n");
    printf("| g_dBufp: [%d], g_cBuffer: [%s]\n", g_dBufp, g_cBuffer);
    printf("| g_dSufp: [%d], g_cSuffix: [%s]\n", g_dSufp, g_cSuffix);
    printf("| g_dStap: [%d], g_cStack:  [%s]\n", g_dStap, g_cStack);
    printf(" --------------------------------------------- [ %d ]\n\n", i);
    i++;
}

/******************************************************************************
* @file     operate.h
* @function double arcsin(double num)
* @describe 计算arcsin()
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
//  2018/4/2    23:15   1.0.0.0023  精度可调
******************************************************************************/
double arcsin(double num)
{
    const double dPI = DPI;
    double d = NE_FLOAT;
    double x, match, low, top, max;
    int i;

    if (num < -1 || num > 1) {              //  定义域[-1,1]
        return SCTERROR;
    }
    max = PI/2;
    for (low = -PI/2, top = low + dPI; low < max; low += dPI, top += dPI) {
        if (sin(low) - d <= num && num <= sin(top) + d) {
            break;
        }
    }
    if (low > max - dPI + d) {
        return SCTERROR;
    }
    x = low;
    for (i = 0; i < g_dPrecision + 1; i++) {
        for (; x <= top; x += d) {
            match = sin(x);                 //  sin在定义域内随x增大而增大
            if (match - d <= num && num <= match + d) {
                d = d / 10;
                if (match <= num) {
                    break;
                }
            }
        }
    }
    if (i == g_dPrecision + 1) {
        return x;
    }
    return SCTERROR;
}

/******************************************************************************
* @file     operate.h
* @function double arccos(double num)
* @describe 计算arccos()
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
//  2018/4/2    23:15   1.0.0.0023  精度可调
******************************************************************************/
double arccos(double num)
{
    const double dPI = DPI;
    double d = NE_FLOAT;
    double x, match, low, top, max;
    int i;

    if (num < -1 || num > 1) {          //  定义域[-1,1]
        return SCTERROR;
    }
    max = PI;
    for (low = 0, top = low + dPI; low < max; low += dPI, top += dPI) {
        if (cos(top) - d <= num && num <= cos(low) + d) {
            break;                      //  切记这里cos是从1到0的
        }
    }
    if (low > max - dPI + d) {
        return SCTERROR;
    }
    x = low;
    for (i = 0; i < g_dPrecision + 1; i++) {
        for (; x <= top; x += d) {  
            match = cos(x);             //  cos(-1) < cos(0) < cos(1)
            if (match - d <= num && num <= match + d) {
                d = d / 10;
                if (match <= num) {     //  与arcsin不同，要从两个方向判断
                    break;
                }
                else if (num <= match) {
                    break;
                }
            }
        }
    }
    if (i == g_dPrecision + 1) {
        return x;
    }
    return SCTERROR;
}

/******************************************************************************
* @file     operate.h
* @function double arctan(double num)
* @describe 计算arctan()
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
//  2018/4/2    23:15   1.0.0.0023  精度可调
******************************************************************************/
double arctan(double num)
{
    const double dPI = DPI;
    double d = NE_FLOAT, keepD;
    double match, keepMatch;
    double x, low, top;
    int i, j = 63;

    low = 0;                                    //  定义域R
    top = low + dPI;
    while (j--) {
        x = low;
        for (i = 0; i < g_dPrecision + 1; i++) {
            for (; x <= top; x += d) {
                keepD = d;
                keepMatch = match = tan(x);
                if (match - d <= num && num <= match + d) {
                    d = d / 10;
                    if (match <= num) {         //与arcsin不同，要从两个方向判断
                        return x;
                    }
                    else if (num <= match) {
                        return x;
                    }
                }
                d = keepD;
                match = keepMatch;
                if (-match - d <= num && num <= -match + d) {
                    d = d / 10;
                    if (-match <= num) {        //与arcsin不同，要从两个方向判断，x输入R全集
                        return -x;
                    }
                    else if (num <= -match) {
                        return -x;
                    }
                }
            }
        }
        low = top;
        top = low + dPI;
    }
    return SCTERROR;
} 

/******************************************************************************
* @file     operate.h
* @function int operateLevel(int)
* @describe 返回一个运算符的运算等级
* @author   Wei Zhou
* @version  1.0.0.0002
* @date     2018/4/1 12:35
* @include  
*
* Update record:
* 2018/4/2  15:07   1.0.0.0002  支持了反三角函数的计算
******************************************************************************/
int operateLevel(int c) 
{
    switch(c) 
    {
        case '(' : return 0;
        case ')' : return 0;
        case '+' : return 1;
        case '-' : return 1;
        case '*' : return 2;
        case '/' : return 2;
        case '%' : return 2;
        case '^' : return 3;
        case SQRT :return 3;    //  '[' 开根号
        case FABS :return 3;    //  '|' 取绝对值
        case SINH :return 3;
        case COSH :return 3;
        case TANH :return 3;
        case SIN : return 3;
        case COS : return 3;
        case TAN : return 3;
        case LOG : return 3;
        case LN  : return 3;
        case ARCSIN : return 3;
        case ARCCOS : return 3;
        case ARCTAN : return 3;
        default  : return MYERROR;
    }
}

/******************************************************************************
* @file     operate.h
* @function void sendToBuffer(int)
* @describe 将一个字符返回的输入流中
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
void sendToBuffer(int c)    
{
    if (g_dBufp >= BUFSIZE) {
        printf("sendToBuffer: too many characters\n");
        exit(0);
    }
    else {
        g_cBuffer[g_dBufp++] = c;
    }
}

/******************************************************************************
* @file     operate.h
* @function int getFromBuffer(void)
* @describe 从输入流返回一个字符
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
int getFromBuffer(void)
{
    return (g_dBufp > 0) ? g_cBuffer[--g_dBufp] : getchar();
}

/******************************************************************************
* @file     operate.h
* @function void sendToSuffix(int)
* @describe 把c压入到后缀式的栈中
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
void sendToSuffix(int c)
{
    if (g_dSufp >= BUFSIZE) {
        printf("[ sendToSuffix ]: too many characters\n");
        exit(0);
    }
    else {
        g_cSuffix[g_dSufp++] = c;
    }
}

/******************************************************************************
* @file     operate.h
* @function int getFromSuffix(void)
* @describe 从g_cSuffix[]后缀式返回一个字符
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
int getFromSuffix(void)
{
    return g_cSuffix[--g_dSufp];
}

/******************************************************************************
* @file     operate.h
* @function void pushToValue(double)
* @describe 把f压入到值栈中
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
void pushToValue(double f)                      
{
    int i = 0;

    if (g_dValp < MAXVAL) {
        g_lfValue[g_dValp++] = f;
        do {
            printf("%10g ", g_lfValue[i]);
            i++;
        } while (i < 100 && g_lfValue[i] != 0.0);
        printf("\n");
    }
    else {
        printf("\n[ pushToValue ] error: g_cStack full, can't push [%g] to g_lfValue \n", f);
    }
}

/******************************************************************************
* @file     operate.h
* @function double nextValue(void)
* @describe 弹出并返回栈顶的值
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
double nextValue(void) 
{
    if (g_dValp > 0) {
        g_lfValue[g_dValp] = 0;     //  主要是为了计算过程可读
        return g_lfValue[--g_dValp];
    }
    else {
        printf("\n[ nextValue ] error: g_cStack empty\n");
        return 0.0;
    }
}

/******************************************************************************
* @file     operate.h
* @function int mathOperate(char c)
* @describe 匹配运算符
* @author   Wei Zhou
* @version  1.0.0.0003
* @date     2018/4/2 13:16
* @include  int getFromBuffer(void)
*           void sendToBuffer(char)
*
* @Update record:
* 2018/4/1  23:21   1.0.0.0001  修复了式子太短，无法计算ln9，等只有3个字符的式子
* 2018/4/2  13:14   1.0.0.0002  支持了运算操作符号的大写输入
* 2018/4/2  15:07   1.0.0.0003  支持了反三角函数的计算
* 2018/4/19 22:16   1.0.0.0004  算法优化
//  重大修复  
//  2018/4/2    15:07   1.0.1.0021  
//  修复了运算符如ln太短，但是输入以测试的字符串太长，
//  可能导致匹配到后面的运算符的bug，如ln2*log100，匹配时匹配到了log，
//  因为匹配结构体中时log在ln前面
******************************************************************************/
struct operation  
{
    char  word[OPLEN_MAX];      // 运算符字符串
    int   time;                 // 出现次数
    int   op;                   // 运算符值（单字符）
};

int getop(char *string, char c)
{   
    int i;
    char type;

    string[0] = c;              // 持续检测下一个字符，直到下一个字符是回车或者不是字母
    for (i = 1; (type = getFromBuffer()) != '\n' && isalpha(type); i++) 
    {
        string[i] = type;
        if (type == '(') {      // 检测到左括号(，停止检测
            i++;
            break;
        }
    }                           // i始终指向srting的下一个地址
    string[i] = '\0';
    if (i < OPLEN_MAX) {                // 操作得到的string运算符一般小于8个字节
        if (type != '\n') {     // 如果下一个字符不是回车结束符，那么把这个字符重新返回到输入流中
            sendToBuffer(type);
        }
        return 1;
    }
    return MYERROR;             // 如果i == OPLEN_MAX，就返回错误值-1
}

/******************************************************************************
* @file     operate.h
* @function int binSearch(char *word, struct operation operate[], int ops)
* @describe 在字符串集中中搜索匹配word字符串的字符串，返回找到的字符串集的下标，ops为字符串的长度
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
int binSearch(char *word, struct operation operate[], int ops)  
{
    int cond;
    int low, high, mid;

    low = 0;
    high = ops - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, operate[mid].word)) < 0) {
            high = mid - 1;
        }
        else if (cond > 0) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return MYERROR;
}

/******************************************************************************
* @file     operate.h
* @function int mathOperate(char c)
* @describe 匹配数学运算符
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
int mathOperate(char c)
{
    struct operation operate[] = { //按ascll码顺序从小到大排放
        "ARCCOS", 0, ARCCOS,
        "ARCSIN", 0, ARCSIN,
        "ARCTAN", 0, ARCTAN,
        "COSH", 0, COSH,
        "COS" , 0, COS,
        "FABS", 0, FABS,
        "LN"  , 0, LN,
        "LOG" , 0, LOG,
        "SINH", 0, SINH,
        "SIN" , 0, SIN,
        "SQRT", 0, SQRT,
        "TANH", 0, TANH,
        "TAN" , 0, TAN,

        "arccos", 0, ARCCOS,
        "arcsin", 0, ARCSIN,
        "arctan", 0, ARCTAN,
        "cosh", 0, COSH,
        "cos" , 0, COS,
        "fabs", 0, FABS,
        "ln"  , 0, LN,
        "log" , 0, LOG,
        "sinh", 0, SINH,
        "sin" , 0, SIN,
        "sqrt", 0, SQRT,
        "tanh", 0, TANH,
        "tan" , 0, TAN,
    };
    char string[8];
    int find;
    int ops = (int)(sizeof(operate) / sizeof(struct operation)); // 字符串个个数

    getop(string, c);
    if ((find = binSearch(string, operate, ops)) != MYERROR)
    {
        operate[find].time++;           // 运算符出现的次数++
        return operate[find].op;        // 返回运算符（单字符）
    }
    return MYERROR;
}
/******************************************************************************
* @file     operate.h
* @function int getOperate(char string[])
* @describe 获取下一个运算符或者数值操作数
* @author   Wei Zhou
* @version  1.0.0.0007
* @date     2018/4/2 13:16
* @include  int getFromBuffer(void)
*           int isdigit(double)
*           void sendToBuffer(char)
*           int mathOperate(char)
*
* @Update record:
* 2018/4/1  14:28   1.0.0.0002  新增了pi和e的运算, 目前PI = 3.1415926, e = 2.7....
* 2018/4/1  14:50   1.0.0.0003  修复了初始计算机不能计算多个pi连写相乘的bug: 如PP
* 2018/4/1  23:05   1.0.0.0005  新增了sin等运算操作
* 2018/4/2  13:14   1.0.0.0006  支持了运算操作符号的大写输入
* 2018/4/2  15:07   1.0.0.0007  支持了反三角函数的计算
******************************************************************************/
int getOperate(char string[])
{
    int i, c;
	static int times = 0;
	
    while ((string[0] = c = getFromBuffer()) == ' ' || c == '\t')   // 跳过所有的空格
        ;
    if (g_administrator != 0) {                                     // g_administrator管理员显示运算过程变量 != 0时
        printf("times = [ %d ], getOperate = [ %c ]\n", times, c);
        times++;
    }
    string[1] = '\0';
    if (!isdigit(c) && c != '.') {
        if (g_dLastIsNumber == YES) {       // 上一个值是数字，但是下一个是运算符，两者之间没有乘，自动添加一个
            if (c == '(' || c == '[' || c == '|' 
                || c == 'f' || c == 's' || c == 'c' || c == 't' || c == 'l'
                || c == 'p' || c == 'e' || c == 'a'
                || c == 'F' || c == 'S' || c == 'C' || c == 'T' || c == 'L'
                || c == 'P' || c == 'E' || c == 'A') {  //  数字 (,[ 之间没有乘*
                sendToBuffer(c);
                g_dLastIsNumber = NO;
                g_dCouldAdd0 = NO;
                return '*';
            }
        }
        else {
            if (c == 'f' ||c == 's' ||c == 'c'||c == 't'||c == 'l'||c == 'a'
                ||c == 'F'||c == 'S'||c == 'C'||c == 'T'||c == 'L'||c == 'A') {
                g_dLastIsNumber = NO;
                g_dCouldAdd0 = YES;
                if (g_administrator != 0) {
                    printf("getOperate, c = %c\n", c);
                }
                return mathOperate(c);
            }
            else if (c == 'p' || c == 'P') {//  是pi = PI = 3.1415926, e = 2.7     
                g_dLastIsNumber = YES;
                g_dCouldAdd0 = NO;
                strcpy(string, PIPI);
                return NUMBER;
            }
            else if (c == 'e' || c == 'E') {
                g_dLastIsNumber = YES;
                g_dCouldAdd0 = NO;
                strcpy(string, EE);
                return NUMBER;
            }                               //  运算符+-前面没有数字，自动添加一个0
            else if (g_dCouldAdd0 == YES 
                && (c == '-' || c == '+' || c == '*' || c == '/' || c == '%')){
                sendToBuffer(c);
                g_dLastIsNumber = YES;
                g_dCouldAdd0 = NO;
                strcpy(string, "0");
                return NUMBER;
            }
        }
        if (c == '(' || c == '[' || c == '|') {
            g_dCouldAdd0 = YES;
        }
        else {
            g_dCouldAdd0 = NO;
        }
        g_dLastIsNumber = NO;
        return c;               //  不是数
    }
    i = 0;
    if (isdigit(c)) {           //  收集整数部分
        while (isdigit(string[++i] = c = getFromBuffer()))
            ;
    }
    if (c == '.') {             //  收集小数部分
        while (isdigit(string[++i] = c = getFromBuffer()))
            ;
    }
    string[i] = '\0';
    if (c != EOF) {
        sendToBuffer(c);
    }
    g_dLastIsNumber = YES;
    return NUMBER;
}

/******************************************************************************
* @file     operate.h
* @function int whenCountGetOperate(char string[])
* @describe 计算时获取下一个运算符或者数值操作数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  int getFromBuffer(void)
*           int isdigit(double)
*           void sendToBuffer(char)
******************************************************************************/
int whenCountGetOperate(char string[])
{
    int i, c;
    
    while ((string[0] = c = getFromSuffix()) == ' ' || c == '\t')
        ;
    string[1] = '\0';
    if (!isdigit(c) && c != '.') {
        g_dLastIsNumber = 0;
        return c;               //  不是数
    }
    i = 0;
    if (isdigit(c)) {           //  收集整数部分
        while (isdigit(string[++i] = c = getFromSuffix()))
            ;
    }
    if (c == '.') {             //  收集小数部分
        while (isdigit(string[++i] = c = getFromSuffix()))
            ;
    }
    string[i] = '\0';
    if (c != EOF) {
        sendToSuffix(c);
    }
    g_dLastIsNumber = 1;
    return NUMBER;
}

/******************************************************************************
* @file     operate.h
* @function int d_digits(double num)
* @describe 计算小数位数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
int d_digits(double num)
{
    int a, n = 0;
    const double b = 1e-6;
    
    a = num;
    num = num - a;
    while((b < num && num < 1 - b) || (b - 1 < num && num < -b)){
        num = num * 10;
        a = num;
        num = num - a;
        n++;
    }
    return n;
}

#endif /* operate_h */
