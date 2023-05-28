/*
* ==================================================================

* Description: LinkedListFunc.h
* Author: Konrad Locas.
* (C)Copyright Konrad Locas.
* All rights reserved.
* Date: 2023/04/18 17:24:23

* ===================================================================
*/
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_NUM 10
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10


typedef int status;
typedef int ElemType; //type of element


typedef struct LNode{
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;


FILE *fp;//file pointer


//initiate the functions
status InitList(LinkList *L);
status DestroyList(LinkList *L);
status ClearList(LinkList *L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L, int i, ElemType *e);
int LocateElem(LinkList L, ElemType e, status(*compare)(ElemType a, ElemType b));
status compare(ElemType a, ElemType b);
status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e);
status NextElem(LinkList L, ElemType cur_e, ElemType *next_e);
status ListInsert(LinkList *L, int i, ElemType e);
status ListDelete(LinkList *L, int i,ElemType *e);
status ListTrabverse(LinkList L);
status SaveList(LinkList L, char* filename);
status LoadList(LinkList *L, char *filename);
status ReverseList(LinkList *L);

status InitList(LinkList *L)
//initiate a list
{
	*L = (LinkList)malloc(sizeof(LNode));//malloc a node
	if(*L == NULL)
	{
		exit(OVERFLOW);//malloc failed
	}
	(*L)->data = 0;
	(*L)->next = NULL;//the list is empty
	return OK;
}



status DestroyList(LinkList *L)
//destroy a list
{
	LinkList p, q;
	p = *L;
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	*L = NULL;
	return OK;
}


status ClearList(LinkList *L)
//clear a list
{
	LinkList p, q;
	p = (*L)->next;//point to the first node
	while(p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}


status ListEmpty(LinkList L)
//judge if the list is empty
{
	if(L->next)
		return FALSE;
	else
		return TRUE;
}


int ListLength(LinkList L)
//get the length of the list
{
	int i = 0;
	LinkList p = L->next;
	while(p)
	{
		i++;
		p = p->next;
	}
	return i;
}



status GetElem(LinkList L, int i, ElemType *e)
//get the element of the No.i node
{
	int j = 1;
	LinkList p;
	p = L->next;
	while(p && j < i)
	{
		p = p->next;
		++j;
	}
	if(!p || j>i)
		return ERROR;
	*e = p->data;
	return OK;
}


int LocateElem(LinkList L, ElemType e, status(*compare)(ElemType a, ElemType b))
//get the position of the element
{
	int i = 0;
	LinkList p = L->next;
	while(p)
	{
		i++;
		if((*compare)(p->data, e))
			return i;
		p = p->next;
	}
	return 0;
}

		status compare(ElemType a, ElemType b)
		{
			if(a == b)
				return TRUE;
			else
				return FALSE;
		}



status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
//get the element before the cur_e
{
	LinkList p = L->next;
	if(p->data==cur_e) 
		return ERROR;
	while(p->next != NULL && p->next->data != cur_e)
		p = p->next;

	if(p->next == NULL)
		return OVERFLOW;

	*pre_e = p->data;
	return OK;
}



status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
//get the element after the cur_e
{
	LinkList p = L->next;
	while(p->next != NULL && p->data != cur_e)
		p = p->next;
	
	if(p->next == NULL && p->data != cur_e)	
		return ERROR;
	if(p->next == NULL && p->data == cur_e)	
		return OVERFLOW;
	*next_e = p->next->data;	
	return OK;
}



status ListInsert(LinkList *L, int i, ElemType e)
//insert a node before the No.i node
{
	int j = 1;
	LinkList p, q;
	p = *L;
	while(p && j < i)
	{
		p = p->next;
		++j;
	}
	if(!p || j > i)
		return ERROR;
	
	q = (LinkList)malloc(sizeof(LNode));
	if(q == NULL)
		exit(OVERFLOW);
	
	q->data = e;
	q->next = p->next;
	p->next = q;
	return OK;
}



status ListDelete(LinkList *L, int i,ElemType *e)
//delete the No.i node
{
	int j = 1;
	LinkList p ,q;
	p = *L;
	while(p->next && j < i)
	{
		p = p->next;
		++j;
	}
	if(!(p->next) || j>i)
		return ERROR;

	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);

	return OK;
}



status ListTrabverse(LinkList L)
//traverse the list
{
   LinkList p = L;
    if(!p)
        return INFEASIBLE;
    else if (!p->next)
        return ERROR;
    else
    {
        printf("\n---------------------------- elements -------------------------------------\n");
        while(p)
        {
            if(p->data!=0)
                printf("%d ",p->data);	
            p = p->next;
        }
        printf("\n------------------------------ end ----------------------------------------\n");
        return OK;
    }
}



status SaveList(LinkList L, char* filename)
//save the list to a file
{
	LinkList p = L->next;
	int listsize=LIST_INIT_SIZE;	
	if ((fp = fopen(filename, "w")) == NULL)
	{
		printf("File open error!\n");
		return ERROR;
	}
	fprintf(fp, "%d ", ListLength(L));
	fprintf(fp, "%d ", listsize);
	while(p)
    {
		fprintf(fp, "%d ", p->data);
		p = p->next;
    }
	fclose(fp);
	return OK;
}



status LoadList(LinkList *L, char *filename)
//load the list from a file
{
	int i = 1,length = 0,listsize;
	ElemType e;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("File open error!\n");
		return ERROR;
	}
	fscanf(fp, "%d ", &length);
	fscanf(fp, "%d ", &listsize);
	fscanf(fp, "%d ", &e);
	while(i<=length)
    {
		ListInsert(L,i,e);
		fscanf(fp, "%d ", &e);
		i++;
    }
	fclose(fp);
	return OK;
}


status ReverseList(LinkList *L)
//reverse the list
{
    if(L)
    {
        LinkList prev=NULL;
		LinkList cur=*L;
		LinkList next=NULL;
		while(cur)
		{
			next=cur->next;
			cur->next=prev;
			prev=cur;
			cur=next;
		}
		*L=prev;
		return OK;
	}
    else  
		return INFEASIBLE;
}


status RemoveNthFromEnd(LinkList &L, int n, ElemType& e)
//delete the nth node from the end of the list
{
    if(!L) 
		return INFEASIBLE;
    else
	{
		int k,j; 
        if(L->next==NULL) 
			return ERROR;
        k = ListLength(L);
        j = k - n + 1;
        ListDelete(&L, j, &e);
        return OK;
    }
}


status SortList(LinkList L)
// sort the list
{
    LinkList p, q;
    if(!L) 
		return INFEASIBLE;
    else
	{
        if(L->next==NULL) 
			return ERROR;
        int n = ListLength(L);
        int i, j, temp;
        for(i = 0,p = L -> next; i < n-1; i++,p = p -> next)
            for(j = i + 1,q = p -> next; j < n; j++,q = q -> next)
                if(p -> data > q -> data)
				{
                    temp = p -> data;
                    p -> data = q -> data;
                    q -> data = temp;
                }

        return OK;
    }
}