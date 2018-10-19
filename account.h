//
//  account.h
//  area.accChoose.account
//
//  Created by 周炜 on 2017/11/24.
//  Copyright © 2017年 zhouwei. All rights reserved.
//

#ifndef account_h
#define account_h

#define ACCOUNT_MAX  12
#define PASSWORD_MAX 12
#define E_MAIL_MAX   18
#define USERNAME_MAX 8

#define ACCOUNT_MIN  4
#define PASSWORD_MIN 4
#define E_MAIL_MIN   4
#define USERNAME_MIN 2

#define ID_CARD1_LEN 16
#define ID_CARD2_LEN 18

struct users{
    int numble;//编号
    char account[ACCOUNT_MAX+1];
    char password[PASSWORD_MAX+1];
    char e_mail[E_MAIL_MAX+1];
    char name[USERNAME_MAX+1];
    //char ID_card[ID_CARD2_LEN+1];//16或18位
    long score;
};

void account_checkAndBuildAccess(const char address[]);
int  account_checkLength(char b[], const char type[], int min, int max);
int  account_checklengthOfIDcard(char b[], const char type[], int num1, int num2);
int  account_readAllAccount(struct users a[], FILE *fp);
void account_writeAllAccount(struct users a[], int n, FILE *fp);
void account_writeSingleAccount(struct users b, FILE *fp);
void account_outputSingleAccount(struct users a[], int i);
void account_outputAllAccount(struct users a[], int n);

void account_checkAndBuildAccess(const char address[])
{
	FILE *fp;
    if ((fp = fopen(address, "r")) == NULL) {
        fp = fopen(address, "w+");
        fprintf(fp, "%-5d",  0);
        fprintf(fp, "%-13s", "Account");
        fprintf(fp, "%-13s", "Password");
        fprintf(fp, "%-19s", "E_mail");
        fprintf(fp, "%-9s",  "Name");
        fprintf(fp, "%-d\n", 0);
    }
    fclose(fp);
}

int account_checkLength(char b[], const char type[], int min, int max)
{
    printf("%s: ", type);
    scanf("%s", b);
    if (dlink_backOrQuit(b) == 1) {
        return 0;
    }
    while (strlen(b) < min || strlen(b) > max) {//检测b[].type是否超过length位
        printf("[sign]: Your %s is %lu digits.\n", type, strlen(b));
        printf("[sign]: It must be between %d and %d digits.\n", min, max);
        printf("%s: ", type);
        scanf("%s", b);
        if (dlink_backOrQuit(b) == 1) {
            return 0;
        }
    }
    return 1;
}

int account_checklengthOfIDcard(char b[], const char type[], int num1, int num2)
{
    printf("%s: ", type);
    scanf("%s", b);
    if (dlink_backOrQuit(b) == 1) {
        return 0;
    }   //检测身份证号是否为16或18位
    while(strcmp(b, "0") != 0 && (strlen(b) != num1) && (strlen(b) != num2)) {
        printf("[sign]: Your %s is %lu digits.\n", type, strlen(b));
        printf("[sign]: It must be %d or %d digits.\n", num1, num2);
        printf("[sign]: If you donot want to input, please enter '0'.\n");
        printf("%s: ", type);
        scanf("%s", b);
        if (dlink_backOrQuit(b) == 1) {
            return 0;
        }
    }
    return 1;
}

int account_readAllAccount(struct users a[], FILE *fp)
{
    int n = 0;
    rewind(fp);
    while (!feof(fp)) {//先把所有的信息放入内存
        fscanf(fp, "%d", &a[n].numble);
        fscanf(fp, "%s", a[n].account);
        fscanf(fp, "%s", a[n].password);
        fscanf(fp, "%s", a[n].e_mail);
        fscanf(fp, "%s", a[n].name);
        // fscanf(fp, "%s", a[n].ID_card);
        fscanf(fp, "%ld",&a[n].score);
        n++;
    }
    return n-1;
}

void account_writeAllAccount(struct users a[], int n, FILE *fp)
{
    int i;
    for (i = 0; i < n; i++){
        fprintf(fp, "%-5d",  a[i].numble);
        fprintf(fp, "%-13s", a[i].account);
        fprintf(fp, "%-13s", a[i].password);
        fprintf(fp, "%-19s", a[i].e_mail);
        fprintf(fp, "%-9s",  a[i].name);
        // fprintf(fp, "%-s\n", a[i].ID_card);
        fprintf(fp, "%-ld\n",a[i].score);
    }
}

void account_writeSingleAccount(struct users b, FILE *fp)
{
    fprintf(fp, "%-5d",  b.numble);
    fprintf(fp, "%-13s", b.account);
    fprintf(fp, "%-13s", b.password);
    fprintf(fp, "%-19s", b.e_mail);
    fprintf(fp, "%-9s",  b.name);
    // fprintf(fp, "%-s\n", b.ID_card);
    fprintf(fp, "%-ld\n",b.score);
}

void account_outputSingleAccount(struct users a[], int i)   //以方式0单个表格方式输出
{
    printf(" ------------------------------\n");
    printf("| Numble:   %18d |\n", a[i].numble);
    printf("| Account:  %18s |\n", a[i].account);
    printf("| Password: %18s |\n", a[i].password);
    printf("| E_mail:   %18s |\n", a[i].e_mail);
    printf("| Name:     %18s |\n", a[i].name);
    //printf("| ID_card:  %18s |\n", a[i].ID_card);
    printf("| Score:    %18ld |\n",a[i].score);
    printf(" ------------------------------\n\n");
}

void account_outputAllAccount(struct users a[], int n)  //以方式1一排表格方式输出
{
    int i;
    printf(" ");
    for (i = 0; i < 78; i++){
        printf("-");
    }
    printf("\n");
    for (i = 0; i < n; i++) {
        printf("|%-5d", a[i].numble);
        printf("%-13s", a[i].account);
        printf("%-13s", a[i].password);
        printf("%-19s", a[i].e_mail);
        printf("%-9s",  a[i].name);
        // printf("%-19s|\n", a[i].ID_card);
        printf("%-19ld|\n",  a[i].score);
    }
    printf(" ");
    for (i = 0; i < 78; i++){
        printf("-");
    }
    printf("\n\n");
}

#endif /* account_h */
