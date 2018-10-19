//
//  myTime.h
//  area.calculator.calChoose.myTime
//  version 1.0.0.0000
//  Created by Wei Zhou on 2018/4/1 12:35
//  Copyright © 2017年 zhouwei. All rights reserved.
//
/******************************************************************************
//  @Update record:
******************************************************************************/

#ifndef MYTIME_H
#define MYTIME_H

#include "common.h"

long time_data(long time);
long time_time(long time, int n);
void myTime_calendarYearMonth(void);
void myTime_calendarYear(void);

/******************************************************************************
* @file     myTime.h
* @function int year(int y)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
int year(int y)
{
    return (y%4 == 0 && y%100 != 0) || y%400 == 0;
}

/******************************************************************************
* @file     myTime.h
* @function long day_data(long day)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
long day_data(long day)
{
	int y, m, d;
	int month[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	y = 1970;
	while (day > 365) {
        if (year(y) == 1) {
            day = day - 366;
        }
        else {
            day = day - 365;
        }
        y++;
    }
    if (year(y) == 1) {
        month[1] = 29;
    }
    m = 1;
    while (day > month[1]) {
        day = day - month[m-1];
        m++;
    }
    d = day;
	return y*10000 + m*100 + d;
}

/******************************************************************************
* @file     myTime.h
* @function long data_day(long data)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
long data_day(long data)
{
	int i;
	int y = data / 10000;
	int m = data % 10000 / 100;
	int d = data % 100;
	int month[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	data = 0;
	if (year(y) == 1) {
        month[1] = 29;
    }
    for (i = 1970; i < y; i++) {
		if (year(i) == 1) {
            data = data + 366;
        }
        else {
            data = data + 365;
        }
	}
	for (i = 0; i < m - 1; i++) {
		data = data + month[i];
	}
	data = data + d;
	return data;
}

/******************************************************************************
* @file     myTime.h
* @function long time_data(long time)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
long time_data(long time)
{
	int y, m, d;
	int month[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	time = time / 3600 / 24 + 1;
	y = 1970;
	while (time > 365) {
        if (year(y) == 1) {
            time = time - 366;
        }
        else {
            time = time - 365;
        }
        y++;
    }
    if (year(y) == 1) {
        month[1] = 29;
    }
    m = 1;
    while (time > month[1]) {
        time = time - month[m-1];
        m++;
    }
    d = time;
	return y*10000 + m*100 + d;
}

/******************************************************************************
* @file     myTime.h
* @function long time_time(long time, int n)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
long time_time(long time, int n)    //n = 时区
{
	int h, m, s;

	s = time - time / 3600 / 24 * 24 * 3600;
	h = s / 3600;
	m = (s - h * 3600) / 60;
	s = s % 60;
	h = (h + n) % 24;
	return h* 10000 + m*100 + s;
}

/******************************************************************************
* @file     myTime.h
* @function void mytime_printDATEandTIME(void) 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void myTime_printDATEandTIME(void) 
{
    long a;

    a = time_data(time(0));
    printf("%04ld / %02ld / %02ld \t", a/10000, a%10000/100, a%100);
    a = time_time(time(0), 8);      //北京+8时区
    printf("%02ld : %02ld : %02ld\n", a/10000, a%10000/100, a%100);
}

/******************************************************************************
* @file     myTime.h
* @function void calendarMonth(int y, int m)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void calendarMonth(int y, int m)
{
    int w;
    int i;                          //用来计数该天在该月的天数
    int month[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (year(y)) {                  //如果是闰年那么2月份为29天
        month[2] = 29;
    }
    w = (y + (y-1)/4 - (y-1)/100 + (y-1)/400) % 7;//求得该年第一天的星期
    for (i = 1; i < m; i++) {           //求得该月第一天的星期
        w = (w + month[i]) % 7;
    }
    printf("\n%04d %02d\n", y, m);
    printf("***************************\n");
    printf("Sun Mon Tue Wen Thu Fri Sat\n");
    for (i = 0; i < w; i++) {
        printf("    ");
    }
    for (i = 1; i <= month[m]; i++) {
        if (w < 6) {
            printf("%3d ", i);
            w++;
        }
        else{
            printf("%3d\n", i);
            w = 0;
        }
    }
    if (w != 0) {                     //如果w==0则说明，最后一行写满，则不换行
        printf("\n");
    }
    printf("***************************\n");
    return;
}

/******************************************************************************
* @file     myTime.h
* @function void calendarYear(int y)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void calendarYear(int y)
{
    int m, w;
    int i;                          //用来计数该天在该月的天数
    int month[13]={0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (year(y)) {                  //如果是闰年那么2月份为29天
        month[2] = 29;
    }
    w = (y + (y-1)/4 - (y-1)/100 + (y-1)/400) % 7;//求得该年第一天的星期
    for (m = 1; m <= 12; m++) {
        printf("\n%04d %02d\n", y, m);
        printf("***************************\n");
        printf("Sun Mon Tue Wen Thu Fri Sat\n");
        for (i = 0; i < w; i++) {
            printf("    ");
        }
        for (i = 1; i <= month[m]; i++) {
            if (w < 6) {
                printf("%3d ", i);
                w++;
            }
            else{
                printf("%3d\n", i);
                w = 0;
            }
        }
        if (w != 0) {                 //如果w==0则说明，最后一行写满，则不换行
            printf("\n");
        }
        printf("***************************\n");
    }
    return;
}

/******************************************************************************
* @file     myTime.h
* @function void myTime_calendarYearMonth(void)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void myTime_calendarYearMonth(void){
    char year[8], month[8];
    int  y, m;

    addNextCatalog("month");
    system(CLEAR);
    printfCatlogAddress();
    printf(" -------------- month ------------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    while(1) {
        printf("Please input: \"year\"\n");
        scanf("%s", year);
        if (dlink_backOrQuit(year) == 1) {
            return;
        }
        else if ((y = atol(year)) <= 0 && strcmp(year, "0") != 0) {
        	printf("\nThe year is wrong!!!\n");
		}
        else{
        	while(1) {
        		printf("Please input: \"month\"\n");
            	scanf("%s", month);
            	if (dlink_backOrQuit(month) == 1) {
                    return;
                }
				else if((m = atol(month)) <= 0 || (m = atol(month)) > 12) {
					printf("\nThe month is wrong!!!\n");
				}
            	else {
            	    calendarMonth(y, m);
            	    break;
            	}
			}
        }
    }
}

/******************************************************************************
* @file     myTime.h
* @function void myTime_calendarYear(void)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     2018/4/2 13:47
* @include  
******************************************************************************/
void myTime_calendarYear(void){
    char year[8];
    int  y;

    addNextCatalog("year");
    system(CLEAR);
    printfCatlogAddress();
    printf(" -------------- year -------------\n");
    printf("| Back ------------------------ r |\n");
    printf("| quit ------------------------ q |\n");
    printf(" ---------------------------------\n");
    while(1){
        printf("Please input: \"year\"\n");
        scanf("%s", year);
        if (dlink_backOrQuit(year) == 1) {
            return;
        }
        else if ((y = atol(year)) <= 0) {
        	printf("\nThe year is wrong!!!\n");
		}
        else {
            calendarYear(y);
        }
    }
}

#endif /* MYTIME_H */
