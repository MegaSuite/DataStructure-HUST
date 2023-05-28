/*
* ==================================================================

* Description: SequenceListFunc.h
* Author: Konrad Locas.
* (C)Copyright Konrad Locas.
* All rights reserved.
* Date: 2023/04/18 17:23:43

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
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

typedef int status; 
typedef int ElemType; 

typedef struct{ 
	ElemType * elem;
	int length;
	int listsize;
}SqList;//type of Sequence List


// Function declaration
status InitList(SqList& L);
status DestroyList(SqList& L);
status ClearList(SqList&L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L,int i,ElemType& e);
status LocateElem(SqList L,ElemType e); 
status PriorElem(SqList L,ElemType cur,ElemType &pre_e);
status NextElem(SqList L,ElemType cur,ElemType &next_e);
status ListInsert(SqList &L,int i,ElemType e);
status ListDelete(SqList&L,int i,ElemType& e);
status ListTraverse(SqList L); 
status MaxSubArray(SqList L);
status SubArrayNum(SqList L,int k);
status SortList(SqList &L);
status SaveList(SqList L,char Filename[]);
status LoadList(SqList &L,char Filename[]);

int ans=0,sum=0;

// function definition

    status InitList(SqList& L)
    // 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
    {
        if(L.elem==NULL)
        {
            L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
            L.length=0;
            L.listsize=LIST_INIT_SIZE;
            return OK;
        }
        else
            return INFEASIBLE;
    }


    status DestroyList(SqList &L)
    // 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
    {
        if(L.elem!=NULL)
        {
            free(L.elem);
            L.elem=NULL;
            L.length=0;
            L.listsize=0;
            return OK;
        }
        else 
            return INFEASIBLE;
    }


    status ClearList(SqList& L)
    // 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
    {
        if(L.elem!=NULL)
        {
            int length = L.length;
            int i;

            for (i = 0; i < length; i++)
                L.elem[i] = 0;

            L.length = 0;
            return OK;
        }
        else
            return INFEASIBLE;
    }



    status ListEmpty(SqList L)
    // 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
    {
        if(L.elem==NULL)
            return INFEASIBLE;
        else
            if(L.length==0)
                return TRUE;
            else
                return FALSE;
    }


    status ListLength(SqList L)
    // 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
    {
        if(L.elem!=NULL)
            return L.length;
        else
            return INFEASIBLE;
    }


    status GetElem(SqList L,int i,ElemType &e)
    // 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    {
        if (L.elem==NULL)
            return INFEASIBLE;
        else if(L.elem!=NULL&&(i<1||i>L.length))
            return ERROR;
        e=L.elem[i-1];
        return OK;
    }


    int LocateElem(SqList L,ElemType e)
    // 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE（即-1）。
    {
        if(L.elem!=NULL)
        {
            int i=1;
            while(L.elem[i-1]!=e&&(i-1)<=L.length-1)
                i++;

            if(i>=1&&i<=L.length)
                return i;
            else
                return 0;
        }
        else 
            return INFEASIBLE;
    }


    status PriorElem(SqList L,ElemType e,ElemType &pre)
    // 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    {
        if(L.elem!=NULL)
        {
            int i=0;
            if(L.elem[i]==e) 
                return ERROR;
            else 
            {
                i=1;
                while(i<L.length)
                {
                    if(L.elem[i]==e) 
                    {
                        pre=L.elem[i-1];
                        return OK;
                    }
                    else 
                        i++;
                }
                return ERROR;
            }
        }
        else 
            return INFEASIBLE;
    }


    status NextElem(SqList L,ElemType e,ElemType &next)
    // 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    {
        if(L.elem!=NULL)
        {
            int i=L.length-1;
            if(L.elem[i]==e)
                return ERROR;
            else
            {
                i=i-1;
                while(i>=0)
                {
                    if(L.elem[i]==e)
                    {
                        next=L.elem[i+1];
                        return OK;
                    }
                    i--;
                }
                if(i<0)
                    return ERROR;
            }
        }
        else
            return INFEASIBLE;
        return ERROR;
    }


    status ListInsert(SqList &L,int i,ElemType e)
    // 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    {
        if(L.elem==NULL)
            return INFEASIBLE;
        if(L.length>=L.listsize)
        {
            ElemType *newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
            L.elem=newbase;
            L.listsize+=LISTINCREMENT;
        }
        if(L.elem!=NULL)
        {
            if(L.length==0)
            {
                L.elem[0]=e;
                L.length++;
                return OK;
            }
            if(i>=1&&i<=L.length+1)
            {
                for(int j=L.length;j>=i;j--)
                    L.elem[j]=L.elem[j-1];

                L.elem[i-1]=e;
                L.length++;
                return OK;
            }
        }
        return ERROR;
    }


    status ListDelete(SqList &L,int i,ElemType &e)
    // 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
    {
        if(L.elem)
        {
            if((i<1)||(i>L.length))
                return ERROR;

            int *p,*q;

            p=&(L.elem[i-1]);
            e=*p;
            q=L.elem+L.length-1;

            for(++p;p<=q;++p)
                *(p-1)=*p;

            L.length--;
            return OK;
        }
        else 
            return INFEASIBLE;
    }


    status ListTraverse(SqList L)
    // 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
    {
        if(L.elem==NULL)
            return INFEASIBLE;
        if(L.length>=L.listsize)
        {
            ElemType *newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
            L.elem=newbase;
            L.listsize+=LISTINCREMENT;
        }
        if(L.elem)
        {
            if(L.length)
            {
                printf("======= Elements in Sequence List =======\n\n");
                for(int i=0;i<L.length;i++)
                {
                    if(i != L.length-1)
                        printf("%d ",L.elem[i]);
                    else
                        printf("%d\n\n",L.elem[i]);
                }
                printf("=========================================\n");
            }
            return OK;
        }
        return L.length;
    }


    status MaxSubArray(SqList L)
    // 初始条件是线性表L已存在且非空，请找出一个具有最大和的连续子数组（子数组最少包含一个元素），操作结果是其最大和；
    {
        sum=0;
        ans=0;
        if(!L.elem) 
            return ERROR;
        for(int i=0;i<L.length;i++)
        {
            sum+=L.elem[i];
            if(ans<sum)
                ans=sum;
        }
        return OK;
    }


    status SubArrayNum(SqList L,int k)
    // 初始条件是线性表L已存在且非空，请找出一个具有和为k的连续子数组的个数，操作结果是其个数；
    {
        ans=0;
        if(!L.elem)     
            return ERROR;
        for(int i=0;i<L.length;i++)
        {
            sum=0;
            for(int j=i;j<L.length;j++)
            {
                sum+=L.elem[j];
                if(sum==k) 
                    ans++;
            }
        }
        return OK;
    }


    status SortList(SqList &L)
    // 如果线性表L存在，将线性表L中的元素按从小到大的顺序排列，返回OK；如果线性表L不存在，返回INFEASIBLE。
    {
        if(!L.elem) 
            return ERROR;
        int temp=0;
        
        for(int i=0;i<L.length-1;i++)
            for(int j=0;j<L.length-1-i;j++)
                if(L.elem[j]>L.elem[j+1])
                {
                    temp=L.elem[j];
                    L.elem[j]=L.elem[j+1];
                    L.elem[j+1]=temp; 
                }
        ListTraverse(L);
        return OK;
    }


    status  SaveList(SqList L,char FileName[])
    // 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
    {
        if(L.elem==NULL)
            return INFEASIBLE;
        else
        {
            FILE *fp=fopen(FileName,"w");
            if(!fp)
                return ERROR;

            fprintf(fp,"%d\n",L.length);

            for(int i=0;i<L.length;i++)
                fprintf(fp,"%d ",L.elem[i]);
            
            fclose(fp);
            return OK;
        }
    }


    status  LoadList(SqList &L,char FileName[])
    // 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
    {

        if(L.elem!=NULL)
            return INFEASIBLE;
        else
        {
            L.elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
            L.length=0;
            L.listsize=LIST_INIT_SIZE;
            FILE *fp=fopen(FileName,"r");
            if(!fp)
                return ERROR;
            fscanf(fp,"%d",&L.length);
            for(int i=0;i<L.length;i++)
                fscanf(fp,"%d",&L.elem[i]);
            
            fclose(fp);
            return OK;
        }
    }