//
//  accChoose.h
//  area.accChoose
//
//  Created by 周炜 on 2017/11/26.
//  Copyright © 2017年 zhouwei. All rights reserved.
//

#ifndef accChoose_h
#define accChoose_h

#include "common.h"

void accChoose_signUp(struct users a[], struct users b, const char address[]);
void accChoose_signIn(struct users a[], struct users b, const char address[]);
void accChoose_showAll(struct users a[], const char address[], const char key[]);
void accChoose_unLoad(void);

/******************************************************************************
* @file     accChoose.h
* @function void accChoose_signUp(struct users [], struct users, const char [])
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void accChoose_signUp(struct users a[], struct users b, const char address[])
{
    FILE *fp;
    int i, numOfAccount, flag = 1;
    
    if ((fp = fopen(address, "r")) == NULL) {
        fp = fopen(address, "w+");
        fprintf(fp, "%-5d",  0);
        fprintf(fp, "%-13s", "Account");
        fprintf(fp, "%-13s", "Password");
        fprintf(fp, "%-19s", "E_mail");
        fprintf(fp, "%-9s",  "Name");
        fprintf(fp, "%-d\n", 0);
    }
    numOfAccount = account_readAllAccount(a, fp);
    fclose(fp);
    addNextCatalog("Sgin up");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ------------ Sgin up ------------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    header_printNotice();
    printf("Account: ");
    scanf("%s", b.account);
    if (dlink_backOrQuit(b.account) == 1) {
        return;
    }
    while (strlen(b.account) < ACCOUNT_MIN
            || strlen(b.account) > ACCOUNT_MAX){//检测账号是否超过12位
        printf("[sign]: Your Account is %lu digits.\n", strlen(b.account));
        printf("[sign]: It must be between %d and %d digits.\n"
            , ACCOUNT_MIN, ACCOUNT_MAX);
        printf("Account: ");
        scanf("%s", b.account);
        if (dlink_backOrQuit(b.account) == 1) {
            return;
        }
    }
    for (i = 0; i < numOfAccount; i++) {//检测是否有重复的账号
        if (strcmp(a[i].account, b.account) == 0){
            printf("[sign]: Your account is repetited.\n");
            break;
        }
    }
    if(i == numOfAccount){
        flag = account_checkLength(b.password, "password"
            , PASSWORD_MIN, PASSWORD_MAX);
        if (flag == 1) {
            flag = account_checkLength(b.e_mail, "e-mail"
                , E_MAIL_MIN, E_MAIL_MAX);
        }
        if (flag == 1) {
            flag = account_checkLength(b.name, "name"
                , USERNAME_MIN, USERNAME_MAX);
        }
        // if (flag == 1){
        //     flag = account_checklengthOfIDcard(b.ID_card, "ID_card"
        //         , ID_CARD1_LEN, ID_CARD2_LEN);
        // }
        if (flag == 1) {
            if ((fp = fopen(address, "a")) == NULL) {
                header_addNewNotice("Unable to open database.");
                return;
            }
            /*sscanf(a[numOfAccount-1].numble, "%d", &numble);//把字符串转化为整型
            numble++;
            sprintf(b.numble, "%d", numble);//把整型转化为字符串*/
            b.numble = a[numOfAccount-1].numble;
            b.numble++;
            b.score = 0; 
            account_writeSingleAccount(b,fp);
            fclose(fp);
            header_addNewNotice("[sign]: Sgin up succeedly!");
            return;
        }
    }
}

/******************************************************************************
* @file     accChoose.h
* @function void accChoose_signIn(struct users [],struct users ,const char [])
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void accChoose_enter(FILE *fp, struct users a[], struct users b, 
                        const char address[], int i, int numOfAccount);
void accChoose_signIn(struct users a[], struct users b, const char address[])
{
    FILE *fp;
    int  i, numOfAccount, flag;
    char choose[16];
	
	if ((fp = fopen(address, "r")) == NULL) {
        fp = fopen(address, "w+");
        fprintf(fp, "%-5d",  0);
        fprintf(fp, "%-13s", "Account");
        fprintf(fp, "%-13s", "Password");
        fprintf(fp, "%-19s", "E_mail");
        fprintf(fp, "%-9s",  "Name");
        fprintf(fp, "%-d\n", 0);
    }
    numOfAccount = account_readAllAccount(a, fp);
    if (numOfAccount == 1) {
    	header_addNewNotice("There is no account, please sign up.");
	}
    fclose(fp);
    addNextCatalog("Sgin in");
    while(1){
        system(CLEAR);
        printfCatlogAddress();
        printf(" ------------ Sign in ------------\n");
        printf("| Back ------------------------ r |\n");
        printf("| quit ------------------------ q |\n");
        printf(" ---------------------------------\n");
        header_printNotice();
        printf("Account: ");
        scanf("%s", b.account);
        if (dlink_backOrQuit(b.account) == 1) {
            return;
        }
        printf("password: ");
        scanf("%s", b.password);
        if (dlink_backOrQuit(b.password) == 1) {
            return;
        }
        flag = 0;
        for (i = 0; i < numOfAccount; i++) {//检测用户名和密码是否正确
            if (strcmp(a[i].account, b.account) == 0){
                if (strcmp(a[i].password, b.password) == 0){
                    flag = 1;
                    header_addNewNotice("[sign]: Enter succeedly!");
                	accChoose_enter(fp, a, b, address, i, numOfAccount);
                    continue;
                }
            }
        }
        if (i == numOfAccount && flag == 0) {
            header_addNewNotice("[sign]: No account, please sgin up, or enter again!");
        }
    }
}

void accChoose_enter(FILE *fp, struct users a[], struct users b, 
                        const char address[], int i, int numOfAccount)
{
    char choose[16];

    addNextCatalog("Enter catalog");
    do{
        system(CLEAR);
        printfCatlogAddress();
        printf(" --------- Enter catalog ---------\n");
        printf("| Change password ------------- 1 |\n");
        printf(" ---------------------------------\n");
        printf("| Back ------------------------ r |\n");
        printf("| quit ------------------------ q |\n");
        printf(" ---------------------------------\n");
        header_printNotice();
        account_outputSingleAccount(a, i);//以方式0单个表格方式输出
        printf("Please input: ");
        scanf("%s", choose);
        if (strcmp(choose, "1") == 0) {
            if (account_checkLength(b.password, "password"
                , PASSWORD_MIN, PASSWORD_MAX) == 1) {
                memcpy(a[i].password, b.password, 13);
                remove(address);
                if ((fp = fopen(address, "w+")) == NULL) {
                    header_addNewNotice("Unable to open database.");
                    return;
                }
                account_writeAllAccount(a, numOfAccount, fp);
                fclose(fp);
                header_addNewNotice("[sign]: Change password succeedly!");
            }
        }
    }while(dlink_backOrQuit(choose) == 0);
}
/******************************************************************************
* @file     accChoose.h
* @function void accChoose_showAll(struct users [], const char [], const char [])
* @describe 日历主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void accChoose_showAll(struct users a[], const char address[], const char key[])
{
    FILE *fp;
    int i, numOfAccount;
    char choose[16];

    addNextCatalog("Show all information");
    system(CLEAR);
    printfCatlogAddress();
    printf(" ----- Show all information ------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    header_printNotice();
    do{
        printf("Enter manager's key: ");
        scanf("%s", choose);
        if(strcmp(choose, key) == 0){            
            if ((fp = fopen(address, "r")) == NULL) {
                header_addNewNotice("Unable to open database.");
                return;
            }
            numOfAccount = account_readAllAccount(a, fp);
            fclose(fp);
            do{
                printf("[sign]: The numble of all access is: %d\n", numOfAccount-1);
                printf("[sign]: Excel type (0 or 1): ");
                scanf("%s", choose);
                if (strcmp(choose, "0") == 0){
                    for (i = 1; i < numOfAccount; i++) {//输出所有数据
                        account_outputSingleAccount(a, i);//以方式0单个表格方式输出
                    }
                }
                else if(strcmp(choose, "1") == 0){
                    account_outputAllAccount(a, numOfAccount);//以方式1一排表格方式输出所有数据
                }
            }while(dlink_justBackOrQuit(choose) == 0);
        }
    }while(dlink_backOrQuit(choose) == 0);
}

/******************************************************************************
* @file     accChoose.h
* @function accChoose_unLoad(struct users [], const char [])
* @describe 日历主程序
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void accChoose_unLoad(void)
{
    char choose[16];

    addNextCatalog("Unload database");
    system(CLEAR);
    printfCatlogAddress();
    printf(" -------- Unload database---------\n");
    printf("| Unload database ------------- 1 |\n");
    printf(" ---------------------------------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    header_printNotice();
    printf("Are you sure to unload database ? [It can not recover]\n");
    do{
        printf("Please select an option: ");
        scanf("%s", choose);
        if(strcmp(choose, "1") == 0){
            remove(USERADDRESS);
            printf("[unload]: '%s' had removed from your computer.\n", USERADDRESS);
            remove(LOGADDRESS);
            printf("[unload]: '%s' had removed from your computer.\n", LOGADDRESS);
        }
    }while(dlink_backOrQuit(choose) == 0);
}

#endif /* accChoose_h */

