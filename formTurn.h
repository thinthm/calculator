//
//  formTurn.h
//  area.calculator.calChoose.formTurn
//  17电子信息类A4班第六组讨论3
//
//  Created by 17电信A4班第六组 on 2017/12/2.
//  2017/12/13
//  Copyright 2017年 . All rights reserved.
//
//  2017/12/13 23:31修复了十进制输入[ 0 ]进制转换输出为[ 空 ]的BUG
//  2017/12/13 23:33修复了十进制输入[ 0.*** ]进制转换输出为[ .*** ]的BUG
//

#ifndef formTurn_h
#define formTurn_h

#include "common.h"

void formTurn_binary(void);
void formTurn_decimal(void);
void formTurn_octal(void);
void formTurn_hexadecimal(void);
void formTurn_codeTurn(char codeName[], char code[][5]);
void formTurn_BCDcode(void);

/******************************************************************************
* @file     formTurn.h
* @function void reverse(char str[])
* @describe 串倒转函数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void reverse(char str[])
{
    int i, len;
    char ch;

    for (len = 0; str[len] != '\0'; len++){
    }
    for(i = 0; i < len/2; i++){
        ch = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = ch;
    }
}

/******************************************************************************
* @file     formTurn.h
* @function char *D_to_BOH(double num, int form)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
char *D_to_BOH(double num, int form)
{
    int    i;	              //字符串序列
    int    j;	              //循环变量，计算小数位数
    long   n1;	                 //n1输入的数的整数位
    double n2;	             //n2输入的数的小数位
    short  n_int;               //下面的整数运算//也可以用long n1
    static char turn[99];

    if (num == 0) {                    //无if，则十进制输入[ 0 ]进制转换输出为[ 空 ]
        turn[0] = '0';
        turn[1] = '\0';
        return turn;
    }
    i  = 0;
    n1 = num;
    n2 = num - n1;
    if (n1 == 0) {                      //无if，则十进制输入[ 0.*** ]进制转换输出为[ .*** ]
        turn[0] = '0';
        i++;
    }
    else {                           //n1>0
        while (n1>0) {
            if ((0 <= n1%form) && (n1%form <= 9)) {
                turn[i] = n1 % form + '0';
            }
            else {
                turn[i] = n1 % form + 'A' - 10;
            }
            n1 = n1 / form;
            i++;
        }
    }
    turn[i] = '\0';                 //串倒转
    reverse(turn);                	//这里的turn的i位后半部分是上调用用后的值，这里要输入长度来限制
    if (n2 > 0) {
        turn[i] = '.';
        i++;                        //十六进制
        for (j = 0; j < g_dPrecision; j++) {
            if (n2 * form == 0)
                break;
            n_int = n2*form;
            if ((0 <= n_int) && (n_int <= 9))
                turn[i] = n_int + '0';
            else
                turn[i] = n_int + 'A' - 10;
            n2 = n2 * form - n_int;
            i++;
        }                           //十六进制和二，八进制分开可以加快运行速度
    }
    turn[i] = '\0';
    return turn;
}

/******************************************************************************
* @file     formTurn.h
* @function double BO_to_D(int form, double num)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
double BO_to_D(int form, double num)
{
    int    i;
    long   n1;                  //n1输入的数的整数位
    double n2;                  //n2输入的数的小数位
    int    n_int;               //计算时用来保存整数
    long   turn1 = 0;
    double turn2 = 0;
    double power;

    n1 = num;
    n2 = num-n1;
    power = 1;
    while (n1 > 0){
        turn1 = turn1 + n1 % 10 * power;   	 	//各位上的数乘以其对应位置的指数
        power = power * form;              		//重新计算指数
        n1    = n1 / 10;                  	//刷新个位上的数
    }
    power = 1.0/form;
    if (n2 > 0) {
        for (i = 0; i <= g_dPrecision && n2 > 0; i++) {//这个1e-6很重要因为例如0.1011被保存为0.10109999999997398845152929425240
            n_int = n2 * 10 + 1e-6;       	//保存n2*10之后的整数，
            n2    = n2 * 10 - n_int;         	//重新获得小数
            turn2 = turn2 + n_int * power;	//将刚刚得到的整数乘以其对应位置的指数
            power = power / form;          		//重新计算指数
        }
    }
    turn2 = turn1 + turn2;
    return turn2;
}

/******************************************************************************
* @file     formTurn.h
* @function double BOH_to_D(int form, char number[])
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
double BOH_to_D(int form, char number[])
{
    int    i = 0, j = 0, k;
    int    n1[99];	//n1输入的数的整数位
    int    n2[99];	//n2输入的数的小数位
    long   turn1 = 0;
    double turn2 = 0;
    double power;
	int    flag = 0;
	
    while (number[i] != '\0'){         // 翻译字符串的'.'之前部分
        if ('0' <= number[i] & number[i] <= '9') {
            n1[i] = number[i] - '0';
        }
        else if ('A' <= number[i] && number[i] <= 'F') {
            n1[i] = number[i] - 'A' + 10;
        }
        else if ('a' <= number[i] && number[i] <= 'f') {
            n1[i] = number[i] - 'a' + 10;
        }
        else if (number[i] == '.') {
            break;
        }
        i++;
    }
    while (number[j+i] != '\0'){     	// 翻译字符串'.'之后部分
        if ('0' <= number[j+i+1] && number[j+i+1] <= '9') {
            n2[j] = number[j+i+1] - '0';
        }
        else if ('A' <= number[j+i+1] && number[j+i+1] <= 'F') {
            n2[j] = number[j+i+1] - 'A' + 10;
        }
        else if ('a' <= number[j+i+1] && number[j+i+1] <= 'f') {
            n2[j] = number[j+i+1] - 'a' + 10;
        }
        j++;
    }
    power = 1;
    for (i--; i >= 0; i--) {          	 // 整数部分运算
        turn1 = turn1 + n1[i] * power;
        power = power * form;
    }
    power = 1.0 / form;
    for (k = 0; k < j-1; k++) {            //小数部分运算
        turn2 = turn2 + n2[k] * power;
        power = power / form;
    }
    turn2 = turn1 + turn2;
    return turn2;
}

/******************************************************************************
* @file     formTurn.h
* @function int isError(char number[], char low, char high)
* @describe 检查进制转换时输入的字符串中有没有当前进制的错误字符
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
int isError(char number[], char low, char high)
{
	int i;
	int decimalPoint = 0;

	for (i = 0; number[i] != '\0'; i++) {
		if (number[i] == '.') {
			if (decimalPoint == 0) {
				decimalPoint = 1;
			}
			else {
                printf("[ error ]: There are extra decimal point.\n");
				return 1;
			}
		}
		else if (number[i] < low || number[i] > high) {
            printf("[ error ]: Invalid format.\n");
			return 1;
		}
	}
	return 0;
}

/******************************************************************************
* @file     formTurn.h
* @function void formTurn_binary(void)
* @describe 2进制转换函数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void formTurn_binary(void)
{
    char number[99];
    double num;
    int d = g_dPrecision;

    addNextCatalog("binary");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ------------ binary -------------\n");
    printf("| return ---------------------- r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    while (1) {
        printf("Please enter a [ 2 ] binary number: ");
        scanf("%s", number);
        if (strcmp(number, "r") == 0 || strcmp(number, "R") == 0) {
            deleteLastCatlog();
            return;
        }
        else if (strcmp(number, "q") == 0 || strcmp(number, "Q") == 0) {
            destroy_dlink();
            exit(0);
        }
        else{
            if (isError(number, '0', '1') == 0) {
                num = atof(number);
                printf("[ 8  ]Octal: %s\n", D_to_BOH(BO_to_D(2, num), 8));
                printf("[ 10 ]Decimal: %.*g\n", d, BO_to_D(2, num));
                printf("[ 16 ]Hexadecimal: %s\n\n", D_to_BOH(BO_to_D(2, num), 16));
                header_log("binary", "user", number);
            }
        }
    }
}

/******************************************************************************
* @file     formTurn.h
* @function void formTurn_decimal(void)
* @describe 10进制转换函数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void formTurn_decimal(void)
{
    char number[99];
    double num;

    addNextCatalog("decimal");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ------------ decimal ------------\n");
    printf("| return ---------------------- r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    while (1) {
        printf("Please enter a [ 10 ] decimal number: ");
        scanf("%s", number);
        if (dlink_backOrQuit(number) == 1) {
            return;
        }
        else{
            if (isError(number, '0', '9') == 0) {
                num = atof(number);
                printf("[ 2  ]Binary: %s\n", D_to_BOH(num,2));
                printf("[ 8  ]Octal: %s\n",  D_to_BOH(num,8));
                printf("[ 16 ]Hexadecimal: %s\n\n", D_to_BOH(num,16));
                header_log("decimal", "user", number);
            }
        }
    }
}

/******************************************************************************
* @file     formTurn.h
* @function void formTurn_octal(void)
* @describe 8进制转换函数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void formTurn_octal(void)
{
    char number[99];
    double num;
    int d = g_dPrecision;

    addNextCatalog("octal");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ------------- octal -------------\n");
    printf("| return ---------------------- r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    while (1) {
        printf("Please enter a [ 8 ] octal number: ");
        scanf("%s", number);
        if (dlink_backOrQuit(number) == 1) {
            return;
        }
        else{
            if (isError(number, '0', '7') == 0) {
                num = atof(number);
                printf("[ 2  ]Binary: %s\n", D_to_BOH(BO_to_D(8, num), 2));
                printf("[ 10 ]Decimal: %.*g\n", d, BO_to_D(8, num));
                printf("[ 16 ]Hexadecimal: %s\n\n", D_to_BOH(BO_to_D(8, num), 16));
                header_log("octal", "user", number);
            }
        }
    }
}

/******************************************************************************
* @file     formTurn.h
* @function void formTurn_hexadecimal(void)
* @describe 16进制转换函数
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void formTurn_hexadecimal(void)
{
    int decimalPoint = 0;
    int i, doubleBreak;
    char number[99];
    double num;
    int d = g_dPrecision;

    addNextCatalog("hexadecimal");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ---------- hexadecimal ----------\n");
    printf("| return ---------------------- r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    while (1) {
    	decimalPoint = 0;
        printf("Please enter a [ 16 ] hexadecimal number: ");
        scanf("%s", number);
        if (dlink_backOrQuit(number) == 1) {
            return;
        }
        else{
            for (i = 0; number[i] != '\0'; i++) {
                if (number[i] == '.') {
                    if (decimalPoint == 0) {
                        decimalPoint = 1;
                    }
                    else {
                        printf("[ error ]: There are extra decimal point.\n");
                        doubleBreak = 1;
                        break;
                    }
                }
                else if ((number[i] < '0' || number[i] > '9')
                        && (number[i] < 'A' || number[i] > 'F')
                        && (number[i] < 'a' || number[i] > 'f')) {
                    printf("[ error ]: Invalid format.\n");
                    doubleBreak = 1;
                    break;
                }
            }
            if (doubleBreak == 1) {
                doubleBreak = 0;
            }
            else {
                printf("[ 2  ]Binary: %s\n", D_to_BOH(BOH_to_D(16, number), 2));
                printf("[ 8  ]Octal: %s\n", D_to_BOH(BOH_to_D(16, number), 8));
                printf("[ 10 ]Decimal: %.*g\n\n", d, BOH_to_D(16, number));
                header_log("hexadecimal", "user", number);
            }
        }
    }
}

/******************************************************************************
* @file     formTurn.h
* @function void formTurn_codeTurn(char codeName[], char code[][5]);
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/

char code8421[10][5] = {
    "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001"
};

char codeExcess_3[10][5] = {
    "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100"
};

char code2421[10][5] = {
    "0000", "0001", "0010", "0011", "0100", "1011", "1100", "1101", "1110", "1111"
};

char code5421[10][5] = {
    "0000", "0001", "0010", "0011", "0100", "1000", "1001", "1010", "1011", "1100"
};

char codeExcess_3cyclic[10][5] = {
    "0010", "0110", "0111", "0101", "0100", "1100", "1101", "1111", "1110", "1010"
};

void formTurn_codeTurn(char codeName[], char code[][5])
{
    int i;
    char number[99];

    addNextCatalog("BCD code");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ------------ BCD code -----------\n");
    printf("| return ---------------------- r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    while (1) {
        printf("[ %s ]. Please enter a number: ", codeName);
        scanf("%s", number);
       if (dlink_backOrQuit(number) == 1) {
            return;
        }
        else {
            for (i = 0; number[i] != '\0'; i++) {
                if ('0' <= number[i] & number[i] <= '9') {
                    printf("%s", code8421[number[i] - '0']);
                }
                else {
                    printf("\n[ error ]: An unrecognized character.\n");
                    break;
                }
            }
            printf("\n");
        }
    }
}

/******************************************************************************
* @file     formTurn.h
* @function void formTurn_BCDcode(void);
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void formTurn_BCDcode(void)
{
    char choose[8];
    
    addNextCatalog("BCD code");
    do{
    	system(CLEAR);
        printfCatlogAddress();
    	printf(" ------------------------ BCD code -----------------------\n");
    	printf("|  cho  |   1  |     2    |   3  |   4  |         5       |\n");
		printf(" ---------------------------------------------------------\n");
    	printf("|  code | 8421 | Excess-3 | 2421 | 5421 | Excess-3 cyclic |\n");
    	printf(" ---------------------------------------------------------\n");
    	printf("|   0   | 0000 |   0011   | 0000 | 0000 |       0010      |\n");
    	printf("|   1   | 0001 |   0100   | 0001 | 0001 |       0110      |\n");
    	printf("|   2   | 0010 |   0101   | 0010 | 0010 |       0111      |\n");
    	printf("|   3   | 0011 |   0110   | 0011 | 0011 |       0101      |\n");
    	printf("|   4   | 0100 |   0111   | 0100 | 0100 |       0100      |\n");
    	printf("|   5   | 0101 |   1000   | 1011 | 1000 |       1100      |\n");
    	printf("|   6   | 0110 |   1001   | 1100 | 1001 |       1101      |\n");
    	printf("|   7   | 0111 |   1010   | 1101 | 1010 |       1111      |\n");
    	printf("|   8   | 1000 |   1011   | 1110 | 1011 |       1110      |\n");
    	printf("|   9   | 1001 |   1100   | 1111 | 1100 |       1010      |\n");
    	printf(" ---------------------------------------------------------\n");
    	printf("| return -------------- r | quit ---------------------- q |\n");
    	printf(" ---------------------------------------------------------\n");
        printf("Please select an option: ");
        scanf("%s", choose);
        if (strcmp(choose, "1") == 0) {
            formTurn_codeTurn("8421", code8421);
        }
        else if (strcmp(choose, "2") == 0) {
            formTurn_codeTurn("Excess-3", codeExcess_3);
        }
        else if (strcmp(choose, "3") == 0) {
            formTurn_codeTurn("2421", code2421);
        }
        else if (strcmp(choose, "4") == 0) {
            formTurn_codeTurn("5421", code5421);
        }
        else if (strcmp(choose, "5") == 0) {
            formTurn_codeTurn("Excess-3 cyclic", codeExcess_3cyclic);
        }
    }while(dlink_backOrQuit(choose) == 0);
}
#endif /* formTurn_h */
