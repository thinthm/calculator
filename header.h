//
//  header.h
//  area.calculator.calChoose.header
//  version 1.0.0.0002
//  Created by Wei Zhou on 2018/4/1 12:35
//  Copyright © 2017年 zhouwei. All rights reserved.
//
/******************************************************************************
//  @Update record:
//  2018/4/1    14:15   1.0.0.0001 
//      int getOperate(char *);
//      int header_getFirstOperate(void); 
//      void header_changeBufferToSuffix(void)               
//      void header_countResult(void)  
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

#ifndef HEADER_H
#define HEADER_H

#include "common.h"

#define NOTICE_LEN   50

static char g_sNotice[NOTICE_LEN+1];

void header_addNewNotice(const char notice[]);
void header_printNotice(void);
int  header_BackOrQuit(char *choose);
void header_logTime(FILE *fp);
int  header_buildLog(void);
int  header_log(char info[], char grabber[], char string[]);
int  header_getFormula(char *formula);
void header_reverseFormula(char *formula, int sign);
void header_initialize(void);
int  header_getFirstOperate(void);
void header_changeBufferToSuffix(void);
void header_reverseSuffix(void);
void header_countResult(char formula[]);

extern int g_administrator;

/******************************************************************************
* @file     header.h
* @function void header_logTime(FILE *fp)
* @describe 向文件里面写入时期时间
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
void header_addNewNotice(const char notice[])
{
    int i;
    for (i = 0; notice[i] != '\0' && i < NOTICE_LEN; i++) {
        g_sNotice[i] = notice[i];
    }
    g_sNotice[i] = '\0';
}

/******************************************************************************
* @file     header.h
* @function void header_logTime(FILE *fp)
* @describe 向文件里面写入时期时间
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
void header_printNotice(void)
{
	if (g_sNotice[0] != '\0') {
		printf("%s\n", g_sNotice);
    	g_sNotice[0] = '\0';
	}
}

/******************************************************************************
* @file     header.h
* @function void header_logTime(FILE *fp)
* @describe 向文件里面写入时期时间
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
void header_logTime(FILE *fp)
{
    long logDate, logTime;

    logDate = time_data(time(0));
    logTime = time_time(time(0), 8);      //北京+8时区
    fprintf(fp, "[%04ld-%02ld-%02ld ",  logDate/10000, logDate%10000/100, logDate%100);
    fprintf(fp, "%02ld:%02ld:%02ld] ", logTime/10000, logTime%10000/100, logTime%100);

}

/******************************************************************************
* @file     header.h
* @function void header_buildLog(void)
* @describe 建立一个日志
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
int header_buildLog(void)
{
    FILE *fp;

    if ((fp = fopen(LOGADDRESS, "r")) == NULL) {
        fp = fopen(LOGADDRESS, "w");
        header_logTime(fp);
        fprintf(fp, "[build] ");
        fprintf(fp, "[console_user_server] ");
        fprintf(fp, "Build log.\n");
        return 1; 
    }
    fclose(fp);
    return 0;
}

/******************************************************************************
* @file     header.h
* @function void header_log(char info[], char grabber[], char string[])
* @describe 向文件里面写入新日志
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
int header_log(char info[], char grabber[], char string[])
{
    FILE *fp;

    if ((fp = fopen(LOGADDRESS, "a")) == NULL) {
        printf("[ error ] Can't open log address '%s'.\n", LOGADDRESS);
        return 0; 
    }
    header_logTime(fp);
    fprintf(fp, "[%s] ", info);
    fprintf(fp, "[%s] ", grabber);
    fprintf(fp, "%s\n",  string);
    fclose(fp);
    return 1;
}

/******************************************************************************
* @file     header.h
* @function int header_getFormula(char *formula)
* @describe 获取一个算式
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/1 12:35
* @include  
******************************************************************************/
int header_getFormula(char *formula)
{
    int i, len;
    char type;

    if ((type = getFromBuffer()) == '+' || type == '-') {       // 以'+','-','*','/'开头的为接下去连续的式子
        for (i = 0; formula[i] != '='; i++)
            ;
        len = i-1;
        formula[i++] = type;
        for (; (type = getFromBuffer()) != '\n'; i++){
            formula[i] = type;
        }
        formula[i++] = '=';
        formula[i] = '\0';
        return len;
    }
    else if (type == '*' || type == '/') {
        for (i = 0; formula[i] != '='; i++)
            ;
        len = i+1;
        for (; i > 0; i--) {
            formula[i] = formula[i-1];
        }
        formula[i] = '(';
        i = len;
        formula[i++] = ')';
        formula[i++] = type;
        for (; (type = getFromBuffer()) != '\n'; i++){
            formula[i] = type;
        }
        formula[i++] = '=';
        formula[i] = '\0';
        return len;
    }
    else {                                      // 以其它方式开头的为新的式子
        i = 0;
        formula[i++] = type;
        for (; (type = getFromBuffer()) != '\n'; i++){
            formula[i] = type;
        }
        formula[i++] = '=';
        formula[i] = '\0';
        return NEWFORMULA;
    }
}

/******************************************************************************
* @file     header.h
* @function void header_reverseFormula(char *formula, int len)
* @describe 倒转算式
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
void header_reverseFormula(char *formula, int len)
{
    int i;

    if (len != NEWFORMULA) {
        for (i = len; formula[i] != '\0'; i++)
            ;
        for (i--; i > len; i--) {                        //  注意一定要倒序输入输入流
            sendToBuffer(formula[i]);
        }
    }
    else {
        for (i = 0; formula[i] != '\0'; i++)
            ;
        for (i--; i >= 0; i--) {                        //  注意一定要倒序输入输入流
            sendToBuffer(formula[i]);
        }
    }
}

/******************************************************************************
* @file     header.h
* @function void header_initialize(void)
* @describe 初始化函数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
void header_initialize(void)
{
    int i;

    g_dValp = 0;
    g_dBufp = 0;
    g_dSufp = 0;
    g_dCouldAdd0 = 0;
    g_cBuffer[g_dBufp] = '\0';
    g_cSuffix[g_dSufp] = '\0';
    g_cStack[g_dStap]  = '\0';
    if (g_administrator != 0) {
        myPrintf("header_initialize");
    } 
}

/******************************************************************************
* @file     header.h
* @function int header_getFirstOperate(void)
* @describe 获得第一个运算符
* @author   Wei Zhou
* @version  1.0.0.0001
* @date     2018/4/1 12:35
* @include  int getOperate(char *)
*           void sendToSuffix(char)
*           void pushToValue(double)
* @extern   int g_dCouldAdd0;
******************************************************************************/
int header_getFirstOperate(void)
{
    int type;
    char string[BUFSIZE];
    int i = 0;

    if ((type = getOperate(string)) != '\n') {
        if (g_administrator != 0) {
            if (type == NUMBER) {
                printf("[ header_getFirstOperate ]: first type is number\n");
            }
            else {
                printf("[ header_getFirstOperate ]: first type = %c\n", type);
            }
        } 
        g_dCouldAdd0 = 1;      //  输入第一个字符以后，该行不是新算式，g_dCouldAdd0=1
        switch (type)
        {
            case '(' :
            case NUMBER:        //  如果第一个运算单位是数字或者‘（’，放入后缀式
                for (i = 0; string[i] != '\0'; i++) {
                    sendToSuffix(string[i]);
                }
                sendToSuffix(' ');
                break;
            case '+' : case '-' : 
            case '*' : case '/' : 
            case '%' : case '^' : //如果第一个运算单位是运算符，放入待处理栈中
                pushToValue(g_lfLastValue);
                g_cStack[g_dStap++] = type;
                break;
            case SQRT :
            case FABS :
            case SINH :case COSH :case TANH :
            case SIN : case COS : case TAN :
            case LOG : case LN  : 
            case ARCSIN :
            case ARCCOS :
            case ARCTAN :
                g_cStack[g_dStap++] = type;
                break;
            default:
                return MYERROR;
                break;
        }
    }
    return 1;
}

/******************************************************************************
* @file     header.h
* @function void header_changeBufferToSuffix(void)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0001
* @date     2018/4/1 12:35
* @include  int operateLevel(int)
*           int getOperate(char *)
*           void sendToSuffix(char)
******************************************************************************/
void header_changeBufferToSuffix(void)
{
    int i = 0;
    char string[MAXOP];
    int j = 0;
    int type;
    int level;              //运算等级
    int typeLevel;

    if (g_dStap == 0) {
        level = 0;
    } 
    else {
        level = operateLevel(g_cStack[g_dStap-1]);   //g_dStap-1
    }
    while ((type = getOperate(string)) != '=' && i < BUFSIZE) {
        i++;
        switch (type) {
            case NUMBER:
                for (j = 0; string[j] != '\0'; j++) {
                    sendToSuffix(string[j]);
                }
                sendToSuffix(' ');
                break;
            case '+' : case '-' : 
            case '*' : case '/' : 
            case '%' : case '^' : 
            case SQRT :
            case FABS :
            case SINH :case COSH :case TANH :
            case SIN : case COS : case TAN :
            case LOG : case LN  : 
            case ARCSIN :
            case ARCCOS :
            case ARCTAN :
            	typeLevel = operateLevel(type);
                if (typeLevel > level) {
                    level = typeLevel;
                    g_cStack[g_dStap++] = type; 
                }
                else {
                    g_dStap--;
                    while (operateLevel(g_cStack[g_dStap]) >= typeLevel) {
                        sendToSuffix(g_cStack[g_dStap]);
                        sendToSuffix(' ');
                        g_cStack[g_dStap] = '\0';
                        g_dStap--;
                    }
                    g_dStap++;
                    g_cStack[g_dStap++] = type;
                }
                break;
            case '(':
                level = operateLevel(type);
                g_cStack[g_dStap++] = type;
                break;
            case ')':
                g_dStap--;
                while (operateLevel(g_cStack[g_dStap]) > 0) {
                    sendToSuffix(g_cStack[g_dStap]);
                    sendToSuffix(' ');
                    g_cStack[g_dStap] = '\0';
                    g_dStap--;
                }
                g_dStap--;
                level = operateLevel(g_cStack[g_dStap++]);
                break;
            default:
                printf("\n[ header_changeBufferToSuffix ] error: unknown command [ %s ]\n", string);
                break;
        }
        if (g_administrator != 0) {
            myPrintf("header_changeBufferToSuffix");
        }
    }
    while (g_dStap > 0) {
        sendToSuffix(g_cStack[--g_dStap]);
        sendToSuffix(' ');
        g_cStack[g_dStap] = '\0';
    }
    sendToSuffix('=');
}

/******************************************************************************
* @file     header.h
* @function void header_reverseSuffix(void)
* @describe 倒转缓存栈
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void header_reverseSuffix(void)
{
    int i;
    char ch;

    for (i = g_dSufp - 1; i > (g_dSufp - 1) / 2; i--) {
        ch = g_cSuffix[g_dSufp - 1 - i];
        g_cSuffix[g_dSufp - 1 - i] = g_cSuffix[i];
        g_cSuffix[i] = ch;
    }
}

/******************************************************************************
* @file     header.h
* @function void header_countResult(void)
* @describe 计算结果函数
* @author   Wei Zhou
* @version  1.0.0.0003
* @date     2018/4/2 13:16
* @include  int whenCountGetOperate(char *)
*           void pushToValue(double)
*           double atof(char *)
*           double nextValue()
*           int d_digits(double)
*           double pow(double, double)
*           double sqrt(double)
*			double log(double)
*			double log10(double)
*           double arcsin(double numble)
*           double arccos(double numble)
*           double arctan(double numble)
*
* @Update record:
* 2018/4/2  11:14   1.0.0.0002  优化了sin，cos等函数的结果显示
* 2018/4/2  15:07   1.0.0.0003  支持了反三角函数的计算
******************************************************************************/
void header_countResult(char formula[])
{
    int type;
    double op1, op2;
    double lfResult;
    long ldResult;
    char string[MAXOP];

    while ((type = whenCountGetOperate(string)) != EOF) 
    {
        switch (type) 
        {
            case NUMBER :
                pushToValue(atof(string));
                break;
            case '+' :
                pushToValue(nextValue() + nextValue());
                break;
            case '-' :
                op2 = nextValue();
                pushToValue(nextValue() - op2);
                break;
            case '*' :
                op2 = nextValue();
                pushToValue(nextValue() * op2);
                break;
            case '/' :
                op2 = nextValue();
                if (op2 != 0.0) {
                    pushToValue(nextValue() / op2);
                }
                else {
                    printf("\n[ header_countResult ] error: zero divisor\n");
                }
                break;
            case '%' :
                op2 = nextValue();          //不可以互换顺序
                if (d_digits(op2) == 0) {
                    op1 = nextValue();
                    if (d_digits(op1) == 0) {
                        pushToValue((double)((int)op1 % (int)op2));
                    }
                }
                else {
                    printf("\n[ header_countResult ] error: can't operate '%%'\n");
                }
                break;
            case '^' :
                op2 = nextValue();
                op1 = nextValue();          //不可以互换顺序
                if (op1 == 0.0 && op2 >= 0.0) {
                    pushToValue(0.0);
                }
                else if (op1 == 0.0 && op2 < 0.0) {
                    printf("\n[ header_countResult ] error: can't operate 'pow()'\n");
                }
                else if (op2 == 0.0) {
                    pushToValue(1.0);
                }
                else {
                    pushToValue(pow(op1, op2));
                }
                break;
            case SQRT :
                op2 = nextValue();
                if (op2 >= 0) {
                    pushToValue(sqrt(op2)); 
                }
                else {
                    printf("\n[ header_countResult ]error: can't operate 'fabs()'\n");
                }
                break;
            case FABS :pushToValue(fabs(nextValue())); break;
            case SINH :pushToValue(sinh(nextValue())); break;
            case COSH :pushToValue(cosh(nextValue())); break;
            case TANH :pushToValue(tanh(nextValue())); break;
            case SIN : 
                op2 = nextValue();
                lfResult = ((double)((long)(fabs(op2 - PI) * PO_FLOAT))) 
                                  / ((long)(PI * PO_FLOAT));
                ldResult = lfResult * PO_FLOAT;
                if (ldResult % ((long)(PO_FLOAT/1)) < 10) {     //  可以容忍小数点后第6位上的误差
                    pushToValue(0.0);
                }
                else {
                    pushToValue(sin(op2));
                }
                break;
            case COS : 
                pushToValue(cos(nextValue()));
                break;
            case TAN : 
                op2 = nextValue();
                lfResult = ((double)((long)(fabs(op2 - PI) * PO_FLOAT))) 
                                  / ((long)(PI * PO_FLOAT));
                ldResult = lfResult * PO_FLOAT;
                if (ldResult % ((long)(PO_FLOAT/2)) < 10) {
                    pushToValue(LONG_MAX);
                    printf("[ header_countResult ] error: tan((+/-)p/2) is worse!\n");
                }
                else {
                    pushToValue(tan(op2));
                }
                break;
            case LOG : pushToValue(log10(nextValue())); break;
            case LN  : pushToValue(log(nextValue()));   break;
            case ARCSIN : pushToValue(arcsin(nextValue())); break;
            case ARCCOS : pushToValue(arccos(nextValue())); break;
            case ARCTAN : pushToValue(arctan(nextValue())); break;
            case '=' :
                printf("-------------------------------------------------\n");
                printf("Value = [ %.*g ]\n\n", g_dPrecision + 1, g_lfValue[0]);
                g_lfLastValue = g_lfValue[0];
                header_log("count", "user", formula);
                return;
            default:
                printf("\n[ header_countResult ] error: unknown command [ %s ]\n", string);
                break;
        }
    }
}
#endif /* HEADER_H */
