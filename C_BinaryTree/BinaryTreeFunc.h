#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2


typedef int status;
typedef int KeyType;
typedef struct {
     KeyType  key;
     char others[20];
} TElemType;

typedef struct BiTNode{ 
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;


status CreateBiTree(BiTree &T,TElemType definition[]);
status DestroyBiTree(BiTree *T);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree &T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T,KeyType e);
status Assign(BiTree &T,KeyType e,TElemType value);
BiTNode* GetSibling(BiTree T,KeyType e);
status InsertNode(BiTree &T,KeyType e,int LR,TElemType c);
status DeleteNode(BiTree &T,KeyType e);
status PreOrderTraverse(BiTree T,void (*visit)(BiTree));
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
status PostOrderTraverse(BiTree T,void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
status MaxPathSum(BiTree T);
BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2);
status InvertTree(BiTree &T);
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);



int max(int x,int y)
{
    return x>y?x:y;
}


void Visit(BiTree T)
{
    printf(" ");
    printf(" (%d,%s)",T->data.key,T->data.others);
}


TElemType val,definition[100];


status CreateBiTree(BiTree &T,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    static TElemType *p=definition;
    if(p->key==-1)//空树
    {
        T=NULL;
        return OK;
    }
    
    if(!p->key)//空结点
    {
        T=NULL;
        p++;
        return OK;
    }
    else
    {
        TElemType *q=definition;
        while(q<p)//判断是否有相同的关键字
        {
            if(q->key==p->key) //有相同的关键字
                return ERROR;
            else 
                q++;
        }
        T=(BiTree)malloc(sizeof(BiTNode));//生成根结点
        T->data=*p;//赋值
        p++;
        if(CreateBiTree(T->lchild,definition)&&CreateBiTree(T->rchild,definition))//递归构造左右子树
            return OK;
    }
}


status ClearBiTree(BiTree &T)
//将二叉树设置成空，并删除所有结点，释放结点空间
{
    if(!T)//空树
        return OK;
    else
    {
        ClearBiTree(T->lchild);//递归删除左子树
        ClearBiTree(T->rchild);//递归删除右子树
        free(T);//释放根结点
        T=NULL;
        return OK;
    }
}


status DestroyBiTree(BiTree *T)
{
	if (*T)//非空树
    {
		if ((*T)->lchild)//递归删除左子树
			DestroyBiTree(&((*T)->lchild));
		if ((*T)->rchild)//递归删除右子树
			DestroyBiTree(&((*T)->rchild));
		free(*T);//释放根结点
		(*T) = NULL;
	}
	return OK;
}


status BiTreeEmpty(BiTree &T)
{
	if(!T)//空树
        return -1;
	if(T==NULL)//空树
        return 1;
    else//非空树
        return 0;
}


int BiTreeDepth(BiTree T)
//求二叉树T的深度
{
    if(!T) //空树
        return 0;
    int d=0,dr=0,dl=0;
    dl=BiTreeDepth(T->lchild);//递归求左子树深度
    dr=BiTreeDepth(T->rchild);//递归求右子树深度
    d=dl>dr?dl:dr;//取左右子树深度的最大值
    return d+1;
}


BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    if(!T) //空树
        return NULL;
    if(T->data.key==e) //找到结点
        return T;
    BiTNode *p=NULL;
    p=LocateNode(T->lchild,e);//递归查找左子树
    if(p) 
        return p;
    p=LocateNode(T->rchild,e);//递归查找右子树
    if(p) //找到结点
        return p;
    return NULL;
}


status Assign(BiTree &T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    if(LocateNode(T,value.key)&&(value.key!=e)) //有相同的关键字
        return ERROR;
    BiTree p=LocateNode(T,e);//查找结点
    if(p)
    {
        p->data=value;//赋值
        return OK;
    }    
    return ERROR;
}


BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{

    if(!(T->lchild&&T->rchild)) //空树或者叶子结点
        return NULL;
    if((T->lchild)->data.key==e)//左子树为e
        return T->rchild;
    if((T->rchild)->data.key==e)//右子树为e
        return T->lchild;
    
    BiTree p=NULL;
    p=GetSibling(T->lchild,e);//递归查找左子树
    if(p) 
        return p;
    p=GetSibling(T->rchild,e);//递归查找右子树
    if(p) 
        return p;
    return NULL;
}


status InsertNode(BiTree &T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    BiTree root=LocateNode(T,e);//查找结点
    if(!root) //没有找到结点
        return ERROR;
    switch(LR)//插入结点
    {
        case 0://左子树
        {
            BiTNode *temp=root->lchild;//原来的左子树
            root->lchild=(BiTNode*)malloc(sizeof(BiTNode));//生成结点
            if(!root->lchild) //生成结点失败
                return ERROR;
            root->lchild->data=c;//赋值
            root->lchild->lchild=NULL;//左子树为空
            root->lchild->rchild=temp;//右子树为原来的左子树
            break;
        }


        case 1://右子树
        {
            BiTNode *temp=root->rchild;//原来的右子树
            root->rchild=(BiTNode*)malloc(sizeof(BiTNode));//生成结点
            if(!root->rchild) //生成结点失败
                return ERROR;
            root->rchild->data=c;//赋值
            root->rchild->lchild=NULL;//左子树为空
            root->rchild->rchild=temp;//右子树为原来的右子树
            break;
        }


        case -1://根结点
        {
            BiTNode *temp=root;//原来的根结点
            root=(BiTNode*)malloc(sizeof(BiTNode));//生成结点
            if(!root) //生成结点失败
                return ERROR;
            root->data=c;//赋值
            root->lchild=NULL;//左子树为空
            root->rchild=temp;//右子树为原来的根结点
            break;
        }
        default:
        return ERROR;
    }
    return OK;
}


status DeleteNode(BiTree &T,KeyType e)
//删除结点
{
    if(!T)  
        return 0;
    if(T->data.key==e)//找到结点
    {
        BiTree p=T;
        if(!T->lchild&&!T->rchild)//叶子结点
            T=NULL;
        else if(!T->rchild)//只有左子树
            T=T->lchild;
        else if(!T->lchild)//只有右子树
            T=T->rchild;
        else
        {
            T=T->lchild;//左子树
            BiTree t=T;
            while(t->rchild)//找到左子树的最右结点
                t=t->rchild;
            t->rchild=p->rchild;//将原来的右子树连接到左子树的最右结点
        }
        free(p);//释放结点
        return OK;
    }
    return DeleteNode(T->lchild,e)||DeleteNode(T->rchild,e);//递归查找
}


status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
//先序遍历二叉树T
{
    BiTree a[100];
    int i=-1;
    a[0]=T;
    BiTree p=T;
    while(p||i!=-1)//栈不为空
    {
        while(p)//遍历左子树
        {
            visit(p);//访问结点
            a[++i]=p;//入栈
            p=p->lchild;//左子树
        }
        if(i!=-1)//栈不为空
        {
            p=a[i--];//出栈
            p=p->rchild;//右子树
        }
    }
}


status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//中序遍历二叉树T
{

    if(!T) 
        return ERROR;
    InOrderTraverse(T->lchild,visit);//递归遍历左子树
    visit(T);//访问结点
    InOrderTraverse(T->rchild,visit);//递归遍历右子树
    return OK;
}


status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
//后序遍历二叉树T
{
    if(!T) 
        return ERROR;
    PostOrderTraverse(T->lchild,visit);//递归遍历左子树
    PostOrderTraverse(T->rchild,visit);//递归遍历右子树
    visit(T);
    return OK;
}


status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    BiTree a[100];
    int come=0,go=0;
    a[come++]=T;//根结点入队
    while(come>go)//队不为空
    {
        
        if(a[go]) //结点不为空
        {
            visit(a[go]);//访问结点
            a[come++]=a[go]->lchild;//左子树入队
            a[come++]=a[go]->rchild;//右子树入队
        }
        go++;
    }
}


void fpr(BiTree T,FILE* fout)
{
    if(!T)
    {
        fprintf(fout,"0 null ");//空结点
        return;
    }
    fprintf(fout,"%d %s ",T->data.key,T->data.others);//结点数据
    fpr(T->lchild,fout);//左子树
    fpr(T->rchild,fout);//右子树
    return;
}


void fread(BiTree& T,FILE* fin)
{
    int key;
    char s[20];
    fscanf(fin,"%d %s",&key,s);//读入结点数据
    if(key==0)//空结点
    {
        T=NULL;
        return;
    }
    if(key==-1)  //根结点
        return;
    T=(BiTree)malloc(sizeof(BiTNode));//生成结点
    T->data.key=key;//赋值
    strcpy(T->data.others,s);//赋值
    fread(T->lchild,fin);//左子树
    fread(T->rchild,fin);//右子树
    return;
}


status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    FILE* fout=fopen(FileName,"w");//打开文件
    fpr(T,fout);//写入数据
    fprintf(fout,"-1 null");//根结点
    fclose(fout);//关闭文件
    return OK;
}


status LoadBiTree(BiTree &T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
    FILE* fin=fopen(FileName,"r");//打开文件
    if(fin==NULL)
        return 0;
    fread(T,fin);//读入数据
    fclose(fin);//关闭文件
    return OK;
}


status MaxPathSum(BiTree T)
//最大路径和
{
    if(!T) 
        return 0;
	int l=MaxPathSum(T->lchild);//左子树
	int r=MaxPathSum(T->rchild);//右子树
	return max(l,r)+T->data.key;//返回最大值
}


BiTNode* LowestCommonAncestor(BiTree T,KeyType e1,KeyType e2)
//最近公共祖先
{
	if(LocateNode(T->lchild,e1))//左子树
    {
		if(LocateNode(T->lchild,e2))  //左子树
            return LowestCommonAncestor(T->lchild,e1,e2);//递归
		return T;
	}
	else
	{
		if(LocateNode(T->rchild,e2))  
            return LowestCommonAncestor(T->rchild,e1,e2);
		return T;
	}
}


status InvertTree(BiTree &T)
//翻转二叉树
{
	if(!T)  
        return OK;
	BiTNode*t;
	t=T->lchild;//交换左右子树
	T->lchild=T->rchild;//交换左右子树
	T->rchild=t;//交换左右子树
	InvertTree(T->lchild);//左子树
	InvertTree(T->rchild);//右子树
	return 1;
}