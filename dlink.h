//
//  dlink.h
//  area.Link
//  version 1.0.0.0002
//  Created by Wei Zhou on 2018/4/1 12:35
//  Copyright © 2017年 zhouwei. All rights reserved.
//
#ifndef DLINK_H
#define DLINK_H

#include "common.h"

typedef struct tag_node
{
	struct tag_node *prev;
	struct tag_node *next;
	void   *p;
}node;

static node *phead = NULL;
static int  count = 0;

/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
static node* create_node(void *pval)
{
	node *pnode = NULL;
	pnode = (node *)malloc(sizeof(node));
	if (!pnode) {
		printf("create node error!\n");
		return NULL;
	}
	pnode->prev = pnode->next = pnode;	// 默认的，pnode的前一节点和后一节点都指向它自身
	pnode->p = pval; // 节点的值为pval
	return pnode;
 }

/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
int create_dlink(void)
{
    phead = create_node(NULL);
    if (!phead) {
    	printf("can not create catalog link.\n");
    	return -1;
    }
    count = 0;
    return 0;
}

/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
int dlink_is_empty(void)
{
	return count == 0;
}

int dlink_size(void) {
	return count;
}

/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
static node* get_node(int index) 
{
	if (index < 0 || index >= count)
	{
		printf("%s failed! index out of bound!\n", __func__);
		return NULL;
	}
	// 正向查找
	if (index <= (count/2))
	{
		int i=0;	
		node *pnode = phead->next;
		while ((i++) < index) {
			pnode = pnode->next;
		}
		return pnode;
	}
	// 反向查找
	int j=0;
	int rindex = count - index - 1;
	node *rnode = phead->prev;
	while ((j++) < rindex) {
		rnode = rnode->prev;
	}
	return rnode;
}

static node* get_first_node()
{
	return get_node(0);
}

static node* get_last_node()
{
	return get_node(count-1);
}

/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void *dlink_get(int index)
{
	node *pindex = get_node(index);
	if (!pindex) 
	{
 		printf("%s failed!\n", __func__);
 		return NULL;
	}
	return pindex->p;
}
 

// 获取“双向链表中第1个元素的值”
void *dlink_get_first()
{
     return dlink_get(0);
}

 // 获取“双向链表中最后1个元素的值”
void *dlink_get_last()
{
     return dlink_get(count-1);
}

/******************************************************************************
* @file     dlink
* @function 
* @describe 将“pval”插入到index位置。成功，返回0；否则，返回-1。
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
// 将“pval”插入到表头位置
int dlink_insert_first(void *pval) 
{
    node *pnode = create_node(pval);
    if (!pnode){
        return -1;
    }
    pnode->prev = phead;
    pnode->next = phead->next;
    phead->next->prev = pnode;
    phead->next = pnode;
    count++;
    return 0;
}

// 将“pval”插入到末尾位置
int dlink_append_last(void *pval) 
{
    node *pnode = create_node(pval);
    if (!pnode) {
        return -1;
    }
    pnode->next = phead;
    pnode->prev = phead->prev;
    phead->prev->next = pnode;
    phead->prev = pnode;
    count++;
    return 0;
}

int dlink_insert(int index, void* pval) 
{
	// 插入表头
	if (index == 0) {
		return dlink_insert_first(pval);
	}
   	// 获取要插入的位置对应的节点
   	node *pindex = get_node(index);
    if (!pindex) {
		return -1;
    }
   	// 创建“节点”
   	node *pnode = create_node(pval);
    if (!pnode) {
    	return -1;
    }
    pnode->prev = pindex->prev;
    pnode->next = pindex;
    pindex->prev->next = pnode;
    pindex->prev = pnode;
    // 节点个数+1
    count++;
    return 0;
}
/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
int dlink_delete(int index)
{
	node *pindex = get_node(index);
	if (!pindex) 
	{
		printf("%s failed! the index in out of bound!\n", __func__);
		return -1;
	}
	pindex->next->prev = pindex->prev;
	pindex->prev->next = pindex->next;
	free(pindex);
	count--;
	return 0;
}    

int dlink_delete_first(void) 
{
return dlink_delete(0);
}

int dlink_delete_last(void) 
{
    return dlink_delete(count-1);
}

/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
int destroy_dlink(void)
{
	if (!phead)
	{
		printf("%s failed! dlink is null!\n", __func__);
		return -1;
	}
	node *pnode = phead->next;
	node *ptmp  = NULL;
	while(pnode != phead)
	{
		ptmp  = pnode;
		pnode = pnode->next;
		free(ptmp);
	}
	free(phead);
	phead = NULL;
	count = 0;
	return 0;
}

/******************************************************************************
* @file     dlink
* @function 
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
* @Update record:
******************************************************************************/
void addNextCatalog(void *p)
{
	dlink_append_last(p);
}

void deleteLastCatlog(void)
{
	dlink_delete_last();
}

void printfCatlogAddress(void)
{
	int i;
	int sz = dlink_size();
	char *p;

	if (sz == 1) {
		p = (char *)dlink_get(0);
		printf(" %s\n", p);
	}
	else {
		p = (char *)dlink_get(0);
		printf(" %s", p);
		for (i = 1; i < sz; i++) {
			p = (char *)dlink_get(i);
			printf(" > %s", p);
		}
		printf("\n");
	}
	
}

/******************************************************************************
* @file     header.h
* @function void header_BackOrQuit(char *choose)
* @describe 
* @author   Wei Zhou
* @version  1.0.0.0000
* @date     
* @include  
******************************************************************************/
int dlink_justBackOrQuit(char *choose)
{
    if (strcmp(choose, "r") == 0 || strcmp(choose, "R") == 0) {
        return 1;
    }
    else if (strcmp(choose, "q") == 0 || strcmp(choose, "Q") == 0) {
        destroy_dlink();
        exit(0);
        return 1;
    }
    return 0;
}

int dlink_backOrQuit(char *choose)
{
    if (strcmp(choose, "r") == 0 || strcmp(choose, "R") == 0) {
        deleteLastCatlog();
        return 1;
    }
    else if (strcmp(choose, "q") == 0 || strcmp(choose, "Q") == 0) {
        destroy_dlink();
        exit(0);
        return 1;
    }
    return 0;
}

#endif /* DLINK_H */