#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20


typedef int status;
typedef int KeyType; 
typedef enum {DG,DN,UDG,UDN} GraphKind;

typedef struct {
    KeyType  key;
    char others[20];
} VertexType;//顶点类型定义

typedef struct ArcNode {//表结点类型定义
   	int adjvex;//顶点位置编号 
    struct ArcNode  *nextarc;//下一个表结点指针
} ArcNode;

typedef struct VNode{//头结点及其数组类型定义
   	VertexType data;//顶点信息
    ArcNode *firstarc;//指向第一条弧
} VNode,AdjList[MAX_VERTEX_NUM];

typedef  struct {//邻接表的类型定义
    AdjList vertices;//头结点数组
    int vexnum,arcnum;//顶点数、弧数
    GraphKind  kind;//图的类型
} ALGraph;

struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;

typedef struct QNode{
	VertexType data;
	struct QNode *next;
}QNode,*Queue;

typedef struct{
	Queue front;
	Queue rear;
}Linkqueue;

void free0(void *p)
{
    pm.pfree[pm.len_free++]=p;
    memset(p,0,sizeof(ArcNode));
    free(p);
}

bool visited[MAX_VERTEX_NUM];
int pd;

void visit(VertexType v)
{
    printf(" (%d , %s)",v.key,v.others);
}


status issame(VertexType V[])//判断顶点重复 
{
	int i=0;
	int mark[100000]={0};
	while(V[i].key!=-1)
	{
		if(mark[V[i].key]>0)
            return 1;

		mark[V[i].key]++;//标记
		i++;
	}
	return 0;
}


int Locate (ALGraph G,KeyType VR)
{
    int i=0;
    for(;i<G.vexnum;i++)
        if(G.vertices[i].data.key==VR) 
            return i;
    
    return -1;
}


status CreateCraph(ALGraph &G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    int i=0,j=0;
    while(V[i].key!=-1)
    {
        for(int k=0;k<i;k++)
            if(V[i].key==V[k].key) 
                return ERROR;

        if(i>=MAX_VERTEX_NUM) 
            return ERROR;
        G.vertices[i].data=V[i];//赋值
		G.vertices[i].firstarc=NULL;
		i++;
    }
    if(i==0) 
        return ERROR;
    G.vexnum=i;//顶点数

    while(VR[j][0]!=-1)
    {
        int a=Locate(G,VR[j][0]),b=Locate(G,VR[j][1]);
        if(!(a>=0&&b>=0)) 
            return ERROR;
        ArcNode *q=(ArcNode*)malloc(sizeof(ArcNode)) ;
        q->adjvex=b;
        q->nextarc=G.vertices[a].firstarc;//头插法
        G.vertices[a].firstarc=q;
        q=(ArcNode*)malloc(sizeof(ArcNode)) ;
        q->adjvex=a;
        q->nextarc=G.vertices[b].firstarc;//头插法
        G.vertices[b].firstarc=q;
        j++;
    }
    G.arcnum=j;
    return OK;
}



status DestroyGraph(ALGraph &G)
/*销毁无向图G,删除G的全部顶点和边*/
{
    ArcNode *p=NULL,*q=NULL;
    for(int k=0;k<G.vexnum;k++)
    {
        if(G.vertices[k].firstarc!=NULL)//释放边
        {
            p=G.vertices[k].firstarc;
            while(p!=NULL)
            {
                q=p->nextarc;//释放
                free(p);
                p=q;
            }
            G.vertices[k].firstarc=NULL;
        }
    }
    G.arcnum=0;
	G.vexnum=0;
    return OK;
}


int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
    int i=0;
    for(i;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u) //找到
            return i;
    
    return -1;
}


status PutVex(ALGraph &G,KeyType u,VertexType value)
//根据u在图G中查找顶点，查找成功将该顶点值修改成value，返回OK；
//如果查找失败或关键字不唯一，返回ERROR
{
    int i=0;
    for(;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u) 
        {
            for(int k=0;k<G.vexnum;k++)
                // if(G.vertices[k].data.key==value.key) //找到
                //     return ERROR;
            
            G.vertices[i].data=value;  
            return OK;
        }
    
    return ERROR;  
}


int FirstAdjVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序，否则返回-1；
{
    int i=0;
    for(;i<G.vexnum;i++)
        if(G.vertices[i].data.key==u&&G.vertices[i].firstarc) 
            return G.vertices[i].firstarc->adjvex;//找到
    return -1;
}


int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
    while(i!=-1&&j!=-1)
    {
        if(G.vertices[i].firstarc==NULL) 
            return -1;
        else
        {
            ArcNode *p=G.vertices[i].firstarc;//找到
            while(p->adjvex!=j&&p)
                p=p->nextarc;
            
            if(p->nextarc)
                return p->nextarc->adjvex;
            else 
                return -1;
        }
    }
    return -1;
}


status InsertVex(ALGraph *G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    if(LocateVex(*G,v.key)>=0) 
        return ERROR;
    if((*G).vexnum==MAX_VERTEX_NUM) 
        return ERROR;
    (*G).vertices[(*G).vexnum].data=v;//赋值
    (*G).vertices[(*G).vexnum].firstarc=NULL;
    (*G).vexnum++;
    return OK;
}


status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    int i=LocateVex(G,v),j=-1;
    if(i==-1) 
        return ERROR;
    if(G.vexnum==1 || G.vexnum==0)
        return ERROR;
    ArcNode *p=G.vertices[i].firstarc;
    ArcNode *q=NULL;
    ArcNode *temp=NULL;
    while(p)
    {  
        j=p->adjvex;
        q=G.vertices[j].firstarc;
        if(q->adjvex==i)
        {
            temp=q;
            G.vertices[j].firstarc=q->nextarc;
            free(temp); 
        }
        else
        {
            while(q->nextarc->adjvex!=i)
                q=q->nextarc;
            
            temp=q->nextarc;
            q->nextarc=temp->nextarc;//删除
            free(temp);
        }
        temp=p->nextarc;
        free(p);
        p=temp;
        G.arcnum--;
    }
    for(int k=i;k<G.vexnum;k++)
        G.vertices[k]=G.vertices[k+1];//删除    
    
    G.vexnum--;
    for(int k=0;k<G.vexnum;k++)
	{
		p=G.vertices[k].firstarc;
		while(p!=NULL)
		{
			if(p->adjvex>i)
			    p->adjvex--;
			p=p->nextarc;
		}
	}
    return OK;
}


status Locatearc(ALGraph G,KeyType v,KeyType w)
{
	ArcNode *p=G.vertices[v].firstarc;
	while(p!=NULL)
	{
		if(p->adjvex==w)//查找<v,w>
		    return OK;
		p=p->nextarc;
	}
	return ERROR;
}


int LocateArc(ALGraph G,KeyType v,KeyType w)
{
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
    if(i==-1||j==-1) 
        return ERROR;
    ArcNode *p=G.vertices[i].firstarc;//查找<v,w>
	while(p!=NULL)
	{
		if(p->adjvex==j)
		    return OK;
		p=p->nextarc;
	}
	return ERROR;
}


status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);
    if(i==-1||j==-1) 
        return ERROR;
    if(LocateArc(G,v,w)!=ERROR) 
        return ERROR;
    ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));//插入<v,w>
    p->adjvex=j;
    p->nextarc=G.vertices[i].firstarc;
    G.vertices[i].firstarc=p;
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=i;
    p->nextarc=G.vertices[j].firstarc;
    G.vertices[j].firstarc=p;
    G.arcnum++;
    return OK;
}


status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    if(LocateArc(G,v,w)==ERROR) 
        return ERROR;
    int i=LocateVex(G,v);
    int j=LocateVex(G,w);//删除<v,w>
    ArcNode *p=G.vertices[i].firstarc;//删除<v,w>
    ArcNode *temp=NULL;
    if(p->adjvex==j)
    {
        temp=p;
        G.vertices[i].firstarc=p->nextarc;//删除<v,w>
        free(temp);
    }
    else 
    {
        while(p->nextarc->adjvex!=j)
            p=p->nextarc;
        
        temp=p->nextarc;
        p->nextarc=p->nextarc->nextarc;//删除<v,w>
        free(temp);
    }
    p=G.vertices[j].firstarc;//删除<v,w>的对称弧<w,v>
    temp=NULL;//删除<v,w>的对称弧<w,v>
    if(p->adjvex==i)
    {
        temp=p;
        G.vertices[j].firstarc=p->nextarc;
        free(temp);
    }
    else 
    {
        while(p->nextarc->adjvex!=i)
            p=p->nextarc;

        temp=p->nextarc;
        p->nextarc=p->nextarc->nextarc;
        free(temp);
    }
    G.arcnum--;
    return OK;
}


void dfs(ALGraph &G,KeyType v,void(*visit)(VertexType))
{
	visited[v]=TRUE;
	int x=LocateVex(G,v);
	visit(G.vertices[x].data);//访问顶点v
	for(int w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,G.vertices[w].data.key)) 
		if(!visited[G.vertices[w].data.key])
            dfs(G,G.vertices[w].data.key,visit);//递归调用
}


status DFSTraverse(ALGraph &G,void(*visit)(VertexType))
{
	int i;
	for(i=0;i<G.vexnum;i++)
	    visited[G.vertices[i].data.key]=FALSE;//标记数组记录关键字 

	for(i=0;i<G.vexnum;i++)
		if(!visited[G.vertices[i].data.key])//若未访问
			dfs(G,G.vertices[i].data.key,visit);
	
	return OK;
} 


status InitQueue(Linkqueue &Q)
{
	Q.front=Q.rear=(QNode *)malloc(sizeof(QNode));
	if(!Q.front)
        return ERROR;
	Q.front->next=NULL;//头结点指针域置空
	return OK;
} 


status QueueEmpty(Linkqueue Q)
{
	if(Q.front==Q.rear)
        return TRUE;//队列为空
	else 
        return FALSE;
}


status enQueue(Linkqueue &Q,VertexType value)
{
	Queue p=(Queue)malloc(sizeof(QNode));
	if(!p)
        return ERROR;
	p->data=value;
	p->next=NULL;//新结点指针域置空
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}


status deQueue(Linkqueue &Q,VertexType &value)
{
	if(Q.front==Q.rear)
        return ERROR;
	Queue p=Q.front->next;
	value=p->data;
	Q.front->next=p->next;
	if(Q.rear==p)
	    Q.rear=Q.front;
	free(p);
	return OK;
}


status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
	int i=0,j;
	VertexType value;
	Linkqueue Q;
	InitQueue(Q);
	for(i=0;i<G.vexnum;i++)
		visited[G.vertices[i].data.key]=FALSE;  //标记数组记录关键字
	
	for(i=0;i<G.vexnum;i++)
		if(!visited[G.vertices[i].data.key])
		{
			visited[G.vertices[i].data.key]=TRUE;//标记已访问
			visit(G.vertices[i].data);
			enQueue(Q,G.vertices[i].data);
			while(!QueueEmpty(Q))
			{
				deQueue(Q,value);
				for(int w=FirstAdjVex(G,value.key);w>=0;w=NextAdjVex(G,value.key,G.vertices[w].data.key))
					if(!visited[G.vertices[w].data.key])//如果未访问过
					{
						visited[G.vertices[w].data.key]=TRUE;//标记已访问
						visit(G.vertices[w].data);
						enQueue(Q,G.vertices[w].data);
					}
				
			}
		}
	
	return OK;
}


status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp=fopen(FileName,"w");
    fprintf(fp,"%d %d ",G.vexnum,G.arcnum);//输出顶点数和边数

    int i=0;
    for(i=0;i<G.vexnum;i++)
   {
        fprintf(fp,"%d,%s ",G.vertices[i].data.key,G.vertices[i].data.others);
        ArcNode *p=G.vertices[i].firstarc;
        while(p!=NULL)
        {
            fprintf(fp,"%d ",p->adjvex);//输出邻接点
            p=p->nextarc;
        }
        fprintf(fp,"%d ",-1);
    }
    fclose(fp);
    return OK;
}


status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    FILE *fp=fopen(FileName,"r");
    char c,d;
    char other[20];
    int i,j,k;
    fscanf(fp,"%d%d",&G.vexnum,&G.arcnum);//读入顶点数和边数

    for(i=0;i<G.vexnum;i++)
    {
    	fscanf(fp,"%d%c%s",&k,&c,other);//c用来接收逗号
    	G.vertices[i].data.key=k;
        strcpy(G.vertices[i].data.others,other);//字符串复制函数
    	j=0;
    	ArcNode *rear=G.vertices[i].firstarc=NULL;
    	while(j!=-1)
    	{
    		fscanf(fp,"%d",&j);
    		if(j!=-1)
            {
                ArcNode *p=(ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex=j;
                p->nextarc=NULL;
                if(G.vertices[i].firstarc==NULL)
                {
                    G.vertices[i].firstarc=p;//头指针指向第一个结点
                    rear=G.vertices[i].firstarc;
                }
                else
                {
                    rear->nextarc=p;
                    rear=p;
                }
    	    }
		}
		rear=NULL;
	}
	fclose(fp);
	return OK;
}



int ShortestPathLength(ALGraph G,KeyType v,KeyType w)
{//返回顶点v与顶点w的最短路径的长度
    int x,y;
    x=LocateVex(G,v);
    y=LocateVex(G,w);
    if(x==-1||y==-1||x==y) 
        return -1;
    int vexcheck[21],vexdistance[21];
    for(int i=0;i<G.vexnum;i++)
    {
        vexcheck[i]=0;
        vexdistance[i]=0;
    }
    ArcNode *p;
    int line[21],front=0,end=0;
    line[0]=x;
    end++;
    vexcheck[x]=1;
    while(front<end)
    {
        p=G.vertices[line[front]].firstarc;
        while(p!=NULL)
        {
            if(vexcheck[p->adjvex]==0)
            {
                line[end]=p->adjvex;
                vexcheck[p->adjvex]=1;
                vexdistance[p->adjvex]=vexdistance[line[front]]+1;
                end++;
            }
            p=p->nextarc;
        }
        front++;
    }
    if(vexcheck[y]==0) 
        return -1;
    else
        return vexdistance[y];
    
}


status VerticesSetLessThank(ALGraph G,KeyType v,int k)
{//输出与顶点v距离小于k的顶点
    int vexcheck[21],vexdistance[21];
    for(int i=0;i<G.vexnum;i++)
    {
        vexcheck[i]=0;
        vexdistance[i]=0;
    }
    int groud;
    ArcNode *p;
    groud=LocateVex(G,v);
    if(groud==-1) 
        return ERROR;
    int line[21],front=0,end=0;
    line[0]=groud;
    end++;
    vexcheck[groud]=1;
    while(front<end)
    {
        p=G.vertices[line[front]].firstarc;
        while(p!=NULL)
        {
            if(vexcheck[p->adjvex]==0)
            {
                line[end]=p->adjvex;
                vexcheck[p->adjvex]=1;
                vexdistance[p->adjvex]=vexdistance[line[front]]+1;
                end++;
            }
            p=p->nextarc;
        }
        front++;
    }
    int sum=0;
    for(int i=0;i<G.vexnum;i++)
    {
        if(i!=groud&&vexcheck[i]==1&&vexdistance[i]<k)
        {
            printf(" %d %s\n",G.vertices[i].data.key,G.vertices[i].data.others);
            sum++;
        }
    }
    if(sum==0) 
        return ERROR;
    return sum;
}


bool mark[20];
void dfs(ALGraph &G,KeyType v)
{
	mark[v]=TRUE;
	for(int w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v,G.vertices[w].data.key)) 
		if(!mark[G.vertices[w].data.key])//如果没有访问过
            dfs(G,G.vertices[w].data.key);
	
}


status ConnectedComponentsNums(ALGraph G)//求图中连通分量个数 
{
	int count=0,i;
	for(i=0;i<G.vexnum;i++)
	    mark[G.vertices[i].data.key]=FALSE;//标记数组记录关键字 
	for(i=0;i<G.vexnum;i++)//遍历所有顶点
		if(!mark[G.vertices[i].data.key])
		{
			dfs(G,G.vertices[i].data.key);
			count++;
		}
	
	return count;
 } 