//
//  calCho.h
//  area.calculator.calCho
//  version 1.0.0.0000
//  Created by Wei Zhou on 2018/9/10 16:48
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

#ifndef calCho_h
#define calCho_h

#include "common.h"

int g_administrator = 0;

extern int g_dPrecision;
extern double g_lfLastValue;

void calCho_calculator(void);
void calCho_precision(void);
void calCho_calendar(void);
void calCho_formConversion(void);
void calCho_instructions(void);
void calCho_administrator(void);

/******************************************************************************
* @file     calCho.h
* @function void calCho_calculator(void)
* @describe 计算器主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void calCho_calculator(void)
{
    char formula[BUFSIZE];
    int  len;

    addNextCatalog("calculator");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ---------- calculator ----------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    header_printNotice();
    while(1){
        header_initialize();
        printf("Please enter a formula:\n");
        len = header_getFormula(formula);
        if (formula[0] == 'r' || formula[0] == 'R') {
            deleteLastCatlog();
            return;
        }
        else if (formula[0] == 'q' || formula[0] == 'Q') {
            destroy_dlink();
            exit(0);
        }
        else{
            header_reverseFormula(formula, len);
            if (g_administrator != 0) {
                myPrintf("header_reverseFormula");
            }
            if (header_getFirstOperate() == MYERROR) {
                continue;
            }
            if (g_administrator != 0) {
                myPrintf("header_getFirstOperate");
            }
            header_changeBufferToSuffix();
            if (g_administrator != 0) {
                myPrintf("header_changeBufferToSuffix");
            }
            header_reverseSuffix();
            if (g_administrator == 0) {
                system(CLEAR);
            }
            printfCatlogAddress();
    		printf(" ---------- calculator ----------\n");
    		printf("| Back ------------------------ r |\n");
    		printf("| quit ------------------------ q |\n");
    		printf(" ---------------------------------\n");
            header_printNotice();
            printf("LaxtValue = [ %.*g ]\n", g_dPrecision + 1, g_lfLastValue);
            printf("formula: %s\n\n", formula);
            header_countResult(formula);
        }
    }
}

/******************************************************************************
* @file     calCho.h
* @function void calCho_precision(void)
* @describe 更改精度主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void calCho_precision(void)
{
    char precision[16];
    int temp;

    addNextCatalog("calendar");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ----------- precision -----------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    header_printNotice();
    printf("Now, precision is [ %d ].\n", g_dPrecision);
    printf("Please enter the precision you need.\n");
    do {
        printf("[ It must be between 2 and 16, integer. ]\n");
        printf("Precision: ");
        scanf("%s", precision);
        g_dPrecision = atoi(precision);
    } while(g_dPrecision < 2 || g_dPrecision > 16 ||
            dlink_backOrQuit(precision) == 0);
}

/******************************************************************************
* @file     calCho.h
* @function void calCho_calendar(void)
* @describe 日历主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void calCho_calendar(void)
{
    char choose[8];

    addNextCatalog("calendar");
    do{
        system(CLEAR);
        printfCatlogAddress();
        printf(" ------------ calendar -----------\n");
        printf("| year month ------------------ 1 |\n");
        printf("| year ------------------------ 2 |\n");
        printf(" ---------------------------------\n");
    	printf("| Back ------------------------ r |\n");
    	printf("| quit ------------------------ q |\n");
    	printf(" ---------------------------------\n");
        header_printNotice();
        printf("Please select an option: ");
        scanf("%s", choose);
        if(strcmp(choose, "1") == 0) {
            myTime_calendarYearMonth();
        }
        else if(strcmp(choose, "2") == 0) {
            myTime_calendarYear();
        }
        else {
            printf("[ error ]!\n");
        }
    }while(dlink_backOrQuit(choose) == 0);
}

/******************************************************************************
* @file     calCho.h
* @function void calCho_formConversion(void)
* @describe 进制转换主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void calCho_formConversion(void)
{
    char choose[8];

    addNextCatalog("form conversion");
    do{
        system(CLEAR);
        printfCatlogAddress();
        printf(" -------- form conversion --------\n");
        printf("| binary ---------------------- 2 |\n");
        printf("| octal ----------------------- 8 |\n");
        printf("| decimal -------------------- 10 |\n");
        printf("| hexadecimal ---------------- 16 |\n");
        printf("| BCD code -------------------- b |\n");
        printf(" ---------------------------------\n");
        printf("| Back ------------------------ r |\n");
    	printf("| quit ------------------------ q |\n");
        printf(" ---------------------------------\n");
        header_printNotice();
        printf("Please select an option: ");
        scanf("%s", choose);
        if (strcmp(choose, "b") == 0 || strcmp(choose, "B") == 0) {
            formTurn_BCDcode();
        }
        else if (strcmp(choose, "2") == 0) {
            formTurn_binary();
        }
        else if (strcmp(choose, "10") == 0) {
            formTurn_decimal();
        }
        else if (strcmp(choose, "8") == 0){
            formTurn_octal();
        }
        else if (strcmp(choose, "16") == 0){
            formTurn_hexadecimal();
        }
    }while(dlink_backOrQuit(choose) == 0);
}

/******************************************************************************
* @file     calCho.h
* @function void calCho_instructions(void)
* @describe 说明主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void calCho_instructions(void)
{
    char choose[8];

    addNextCatalog("instructions");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ---------- instructions ---------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    header_printNotice();
    printf(" This calculator supports mixed computing.\n");
    printf(" Currently supported calculations include:\n");
    printf("\n");
    printf(" Operator        Instructions\n");
    printf(" p e             p = 3.1415926, e = 2.718281828.\n");
    printf(" + - * / %% ^     + - * / %% ^.\n");
    printf(" arccos()        Inverse cosine function.\n");
    printf(" arcsin()        Inverse sine.\n");
    printf(" arctan()        Inverse tangent function.\n");
    printf(" cosh()          It is cos-1().\n");
    printf(" sinh()          It is sin-1().\n");
    printf(" tanh()          It is tan-1().\n");
    printf(" cos()           Cosine.\n");
    printf(" sin()           Sine.\n");
    printf(" tan()           Tangent.\n");
    printf(" fabs()          Could use '|' instead, such as |1=1.\n");
    printf(" ln()            Natural logarithm.\n");
    printf(" log()           Logarithmic.\n");
    printf(" sqrt()          Square root.\n");
    printf(" # pow()         please use '^' instead, such as 2^3=8.\n");
    printf("\n");
    printf(" The final ownership of this program belongs to the author zhou wei.\n");
    printf(" 2018-9-11.\n\n");
    do{
        printf("Please select an option: ");
        scanf("%s", choose);
    }while(dlink_backOrQuit(choose) == 0);
}

/******************************************************************************
* @file     calCho.h
* @function void calCho_administrator(void)
* @describe 进入管理模式主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void calCho_administrator(void)
{
    char choose[8];

    addNextCatalog("administrator");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ---------- administrator --------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    header_printNotice();
    do{
        printf("Please enter the password: ");
        scanf("%s", choose);
        if (strcmp(choose, "zhouwei") == 0) {
            printf("g_administrator = %d\n", g_administrator);
            do{
            	printf("Please enter g_administrator: ");
                scanf("%s", choose);
                g_administrator = atoi(choose);
            	printf("g_administrator = %d\n", g_administrator);
            }while(dlink_justBackOrQuit(choose) == 0);
		}
    }while(dlink_backOrQuit(choose) == 0);
}

#endif /* calCho_h */
