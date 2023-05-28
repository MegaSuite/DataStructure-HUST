#include"GraphFunc.h"

int main()
{
    //定义变量
    int op=1,flag,x;
    ALGraph G;
    G.arcnum=0,G.vexnum=0;
    VertexType V[30];
    VertexType value;
    KeyType VR[100][2];
    int i=0,j,e,v,w,k;
    char filename[20];
    char name[20];

    while(op)
    {
        system("cls");	
        printf("\n");

        printf("Menu for Linear Table On Sequence Structure\n");
        printf("-------------------------------------------------\n\n");
        printf("1. CreateGraph                 2. DestroyGraph\n");
        printf("3. LocateVex                   4. PutVex\n");
        printf("5. FirstAdjVex                 6. NextAdjVex \n");
        printf("7. InsertVex                   8. DeleteVex\n");
        printf("9. InsertArc                   10.DeleteArc\n");
        printf("11.DFS Traverse                12.BFS Traverse\n");
        printf("13.VerticesSetLessThanK        14.ShortestPathLength\n");
        printf("15.ConnectedComponentsNums     16.SaveGraph\n");
        printf("17.LoadGraph                   0. Exit\n\n");
        printf("-------------------------------------------------\n");
        printf("Choose your operation[0~17]:\n");

        scanf("%d",&op);

        switch(op)
        {
            case 1://InitGraph
                i=0;
                if(pd)//判断是否已经创建图
                {
                    printf("The graph has been created.\n");
                    printf("Please destroy it first!\n");
                }
                else
                {
                    printf("Please enter the vertex sequence,\n");
                    printf("the following pair sequence of the undirected graph,\n");
                    printf("with -1 as the ending mark!\n\n"); 

                    do{
                        scanf("%d %s",&V[i].key,V[i].others);
                    }while(V[i++].key!=-1);//输入顶点序列

                    i=0;
                    do{
                        scanf("%d%d",&VR[i][0],&VR[i][1]);
                    }while(VR[i++][0]!=-1);//输入边序列

                    if (CreateCraph(G,V,VR)==ERROR) 
                        printf("Invalid input!\n");//创建图

                    else 
                    {
                        if (G.arcnum!=i-1) 
                        {
                            printf("The number of arcs is wrong!\n");
                            return 0; 
                        }
                        printf("\n");
                        for(j=0;j<G.vexnum;j++)//输出邻接表
                        {
                            ArcNode *p=G.vertices[j].firstarc;
                            printf("(%d , %s)",G.vertices[j].data.key,G.vertices[j].data.others);
                            while (p)
                            {
                                printf(" %d",p->adjvex);
                                p=p->nextarc;
                            }
                            printf("\n");
                        }
                    }
                }
                getchar();
                getchar();
                break;


            case 2://DestroyGraph
                if(G.vexnum==0)//判断是否已经创建图
                    printf("Fail to destroy!\n");
                else
                {
                    if(DestroyGraph(G)==OK)
                        printf("Success to destroy!\n");
                    else 
                        printf("Fail to destroy!\n");
                }
                getchar();
                getchar();
                break;


            case 3://LocateVex
                if(G.vexnum==0)
                printf("The graph does not exist!\n");
                else
                {
                    printf("Please enter the key of the vertex!\n");
                    scanf("%d",&e);
                    if(LocateVex(G,e)==-1)
                        printf("The vertex does not exist!\n");
                    else 
                    {
                        x=LocateVex(G,e);//定位顶点
                        printf("The vertex is in the No.%d position!\n",x);
                        printf("Its value is (%d , %s)\n",G.vertices[x].data.key,G.vertices[x].data.others);
                    }
                }
                getchar();
                getchar();
                break;


            case 4://PutVex
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("Please input as follows:\n");
                    printf("[key] [newkey] [newothers]\n");
                    scanf("%d%d%s",&j,&value.key,value.others);//输入新的顶点值
                    
                    if(LocateVex(G,j)==-1 || LocateVex(G,j)==-2)
                        printf("The vertex does not exist!\n");
                    else if(PutVex(G,j,value)==OK)
                        printf("Success to modify!\n");
                    else 
                        printf("Fail to modify!\n");//修改顶点值
                }
                getchar();
                getchar();
                break;


            case 5://FirstAdjVex
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("Please enter the key of the vertex!\n");
                    scanf("%d",&e);//输入顶点值

                    if(FirstAdjVex(G,e)==-1)
                        printf("Fail to find!\n");
                    else
                    {
                        x=FirstAdjVex(G,e);//查找第一个邻接点
                        printf("The FirstAdjVex is in the No.%d position!\n",x);
                        printf("Its value is (%d , %s)\n",G.vertices[x].data.key,G.vertices[x].data.others);//输出第一个邻接点的值
                    }
                }
                getchar();
                getchar();
                break;


            case 6://NextAdjVex
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("The format is as follows:\n");
                    printf("[MainVertex Key] [FirstAdjVex Key]\n");
                    scanf("%d%d",&v,&w);  //输入顶点值

                    if(NextAdjVex(G,v,w)==-1)
                        printf("Fail to find!\n");
                    else
                    {
                        x=NextAdjVex(G,v,w);//查找下一个邻接点
                        printf("According to [%d] vertex, the [%d] vertex's nextadjvex is in No.%d position\n",w,v,x); 
                        printf("Its value is (%d , %s)\n",G.vertices[x].data.key,G.vertices[x].data.others);
                    }
                }
                getchar();
                getchar();
                break;


            case 7://InsertVex
                printf("Please input as follows:\n");
                printf("[key] [others]\n");
                scanf("%d%s",&value.key,value.others);//输入新的顶点值

                if(InsertVex(&G,value)==OK)
                    printf("Success to insert!\n");
                else 
                    printf("Fail to insert!\n");
                getchar();
                getchar();
                break;


            case 8://DeleteVex
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("Please enter the key of the vertex!\n");
                    scanf("%d",&v);//输入顶点值

                    if(DeleteVex(G,v)==OK)
                        printf("Success to delete!\n");
                    else 
                        printf("Fail to delete!\n");
                }
                getchar();
                getchar();
                break;


            case 9://InsertArc
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("Please input the two vertexs of the arc!\n");
                    scanf("%d%d",&v,&w);//输入弧尾和弧头
                    
                    if(InsertArc(G,v,w)==OK)
                        printf("Insert the arc successfully!\n");
                    else 
                        printf("Fail to insert!\n");
                }
                getchar();
                getchar();
                break;


            case 10://DeleteArc
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("Please input the two vertexs of the arc!\n");
                    scanf("%d%d",&v,&w);
                    if(DeleteArc(G,v,w)==OK)
                        printf("Success to delete!\n");
                    else 
                        printf("Fail to delete!\n");
                }
                getchar();
                getchar();
                break;


            case 11://DFSTraverse
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("DFS Traverse:\n-------------\n");
                    DFSTraverse(G,visit); 
                    printf("\n-------------\nEND\n");
                }
                getchar();
                getchar();
                break;


            case 12://BFSTraverse
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("BFS Traverse:\n-------------\n");
                    BFSTraverse(G,visit); 
                    printf("\n-------------\nEND\n");
                }
                getchar();
                getchar();
                break;


            case 13://VerticesSetLessThanK
                printf("Please input the key of the vertex and the distance!\n");
                scanf("%d%d",&v,&k);
                flag=VerticesSetLessThank(G,v,k);
                if(!flag)
                    printf("Fail to find!\n");
                else
                    printf("The vertices set less than %d is:%d\n",k,flag);//错误处理
                getchar();
                getchar();
                break;


            case 14://ShortestPathLength
                printf("Please input the two vertexs of the arc!\n");
                scanf("%d%d",&v,&w);
                k=ShortestPathLength(G,v,w);
                if(k==-1)
                    printf("The two vertexs are not connected!\n");
                else
                    printf("The shortest path length is %d\n",k);                
                getchar();
                getchar();
                break;


            case 15://ConnectedComponentsNums
                printf("The number of connected components is %d\n",ConnectedComponentsNums(G));
                
                getchar();
                getchar();
                break;


            case 16://SaveGraph
                if(G.vexnum==0)
                    printf("The graph does not exist!\n");
                else
                {
                    printf("Please input the file name!\n");
                    scanf("%s",filename);
                    if(SaveGraph(G,filename)==OK)
                        printf("Save the graph successfully!\n");
                    else 
                        printf("Fail to save!\n");
                }
                getchar();
                getchar();
                break;


            case 17://LoadGraph
                printf("Please input the file name!\n");
                scanf("%s",filename);
                if(LoadGraph(G,filename)==OK)
                    printf("Load the graph successfully!\n");
                else 
                    printf("Fail to load!\n");
                getchar();
                getchar();
                break;



            case 0://Exit
                exit(0);
                break; 
        }
    }
}

