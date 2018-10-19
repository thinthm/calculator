//
//  calculator.h
//  area.calculator
//  version 1.0.1.0025
//  Created by Wei Zhou on 2018/5/24 23:05
//  Copyright © 2017年 zhouwei. All rights reserved.
//  
//  Update record:
//	2018/4/1 	14:15 	1.0.0.0001 	新增了运算符: 根号'[' , 乘方'^' 
//	2018/4/1 	14:28 	1.0.0.0002 	新增了pi和e的运算, 目前PI=3.1415926, e=2.7....
//  2018/4/1 	14:50 	1.0.0.0003 	修复了初始计算机不能计算多个pi连写相乘的bug: 如PP
//  2018/4/1 	23:05 	1.0.0.0010 	新增了sin等运算操作
//  2018/4/1  	23:21   1.0.0.0011  修复了式子太短，无法计算ln9，等只有3个字符的式子
//                                  * 重构算法之后已无影响，采用b树法
//  2018/4/2  	11:14   1.0.0.0012  优化了sin，cos等函数的结果显示
//  2018/4/2  	11:35   1.0.0.0013  新增了取负值的运算
//  2018/4/2  	13:14   1.0.0.0014  支持了运算操作符号的大写输入
//  2018/4/2  	15:07   1.0.0.0020  支持了反三角函数的计算
//  2018/4/2  	17:20   1.0.0.0021  小bug
//  2018/4/2  	21:28   1.0.0.0022  提高了反三角函数的精度
//  2018/4/2  	23:15   1.0.0.0023  反三角函数的精度可调
//  2018/5/24   20:00   1.0.0.0025  优化了内存
//
//	重大修复  
//	2018/4/2  	15:07   1.0.1.0021
//  修复了运算符如ln太短，但是输入以测试的字符串太长，
//	可能导致匹配到后面的运算符的bug，如ln2*log100，匹配时匹配到了log，
//  因为匹配结构体中时log在ln前面
//  * 重构算法之后已无影响，采用b树法



#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "common.h"

/******************************************************************************
* @file 	calculator.c
* @function main()
* @author 	Wei Zhou
* @version 	1.0.0.0001
* @date 	2018/4/1 12:35
* @include  header_initialize(int)
*           header_getFirstOperate()
*           header_changeBufferToSuffix_sendToBuffer()
*           header_count_result()
*
* #include "header.h"
* @define   BUFSIZE 100
* @extern   char g_cEveryBuffer[BUFSIZE];
*    		int g_dEvBp = 0;
*    		double g_lfLastValue;
*		    int g_dCouldAdd0 = 1;
******************************************************************************/
int calculator_calculator(void)
{
	char choose[8];

    if (header_buildLog() == 1) {
    	calCho_instructions();
	}
    addNextCatalog("calculator");
	do{
		system(CLEAR);
        printfCatlogAddress();
		printf(" ----------- calculator ----------\n");
        printf("| calculator ------------------ 1 |\n");
        printf("| precision ------------------- 2 |\n");
        printf("| calendar -------------------- 3 |\n");
        printf("| form conversion ------------- 4 |\n");
        printf(" ---------------------------------\n");
        printf("| instructions ---------------- 5 |\n");
        printf("| administrator --------------- 6 |\n");
        printf("| Back ------------------------ r |\n");
    	printf("| quit ------------------------ q |\n");
        printf(" ---------------------------------\n");
        header_printNotice();
        printf("Please select an option: ");
    	scanf("%s", choose);
        getchar();
	    if (strcmp(choose, "1") == 0) {
            calCho_calculator();
		}
		else if (strcmp(choose, "2") == 0) {
            calCho_precision();
		}
		else if (strcmp(choose, "3") == 0) {
            calCho_calendar();
        }
		else if (strcmp(choose, "4") == 0) {
            calCho_formConversion();
        }
        else if (strcmp(choose, "5") == 0) {
            calCho_instructions();
        }
        else if (strcmp(choose, "6") == 0) {
            calCho_administrator();
        }
	}while(dlink_backOrQuit(choose) == 0);
	return 0;
}

#endif /* CALCULATOR_H */
