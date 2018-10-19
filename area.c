//
//  area.c
//  area
//  version 1.0.0.0002
//  Created by Wei Zhou on 2018/9/30 23:39
//  Copyright © 2017年 zhouwei. All rights reserved.
//
/******************************************************************************
//  @Update record:
******************************************************************************/

#include "common.h"

int main(int argc, char const *argv[]) {
    struct users a[99], b;
    char choose[16];
    
    create_dlink();
    account_checkAndBuildAccess(USERADDRESS);	// 如果没有数据库文件，那么建立一个数据库txt
    addNextCatalog("Catalog");
    do {
        system(CLEAR);
        printfCatlogAddress();
        printf(" ------------ Catalog ------------\n");
        printf("| Sign up --------------------- 1 |\n");
        printf("| Sign in --------------------- 2 |\n");
        printf("|   [ Game-tanchishe ] -------- - |\n");
        printf("|   [ Change password ] ------- - |\n");
        printf("| calculator ------------------ 3 |\n");
        printf(" ---------------------------------\n");
        printf("| Show all -------------------- 4 |\n");
        printf("| Unload ---------------------- 5 |\n");
        printf("| quit ------------------------ q |\n");
        printf(" ---------------------------------\n");
        header_printNotice();
        printf("Please input: ");
        scanf("%s", choose);
        if (strcmp(choose, "1") == 0) {                     //输入1注册address
            accChoose_signUp(a, b, USERADDRESS);
        }
        else if (strcmp(choose, "2") == 0) {                //输入2登陆
            accChoose_signIn(a, b, USERADDRESS);
        }
        else if (strcmp(choose, "3") == 0) {                //输入3计算器
            calculator_calculator();
        }
        else if (strcmp(choose, "4") == 0) {                //输入4显示数据库里的所有数据
            accChoose_showAll(a, USERADDRESS, "zhouwei");
        }
        else if (strcmp(choose, "5") == 0) {                //输入5卸载数据库
            accChoose_unLoad();
        }
        else if (strcmp(choose, "q") == 0 || strcmp(choose, "Q") == 0) {                //输入5卸载数据库
            return 0;
        }
    } while(1);
    return 0;
}

