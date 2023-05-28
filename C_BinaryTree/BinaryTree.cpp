#include "BinaryTreeFunc.h"


int main()
{
	int op=1,flag=0,i,lr;
	KeyType key,key1,key2;

	BiTree T=NULL;
	BiTNode* t;
	char FileName[30],TreeName[30];
	T=NULL; 

	while(op)
    {
		system("cls");

        printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("----------------------------------------------------------------\n");
		printf("    	  1. CreateBiTree           2. DestroyBiTree\n");
		printf("    	  3. ClearBiTree            4. BiTreeEmpty\n");
		printf("    	  5. BiTreeDepth            6. LocateNode\n");
		printf("    	  7. Assign                 8. GetSibling\n");
		printf("    	  9. InsertNode             10.DeleteNode\n");
		printf("    	  11.PreOrderTraverse       12.InOrderTraverse\n");
		printf("    	  13.PostOrderTraverse      14.LevelOrderTraverse\n");
		printf("    	  15.MaxPathSum             16.LowestCommonAncestor\n");
		printf("    	  17.InvertTree             18.SaveBiTree\n");
		printf("    	  19.LoadBiTree             0. Exit\n");
		printf("----------------------------------------------------------------\n");
		printf("Choose your operation[0~19]:\n");


		scanf("%d",&op);


	    switch(op)
        {
	    	case 1://CreateBiTree
	    		if(T)  
                    printf("The tree has been existed!\n");
                else
                {
                    printf("Please input the definition of the tree with empty node:\n");
                    i=0;
                    do
                    {
                        scanf("%d%s",&definition[i].key,definition[i].others);//输入结点的值
                    } while (definition[i++].key!=-1);
                    flag=CreateBiTree(T,definition);//创建二叉树
                    if(flag==1)
                        printf("The tree has been created successfully!\n");
                    else if(flag==0)
                        printf("The tree has been created failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 2://DestroyBiTree
	    		flag=DestroyBiTree(&T);//销毁二叉树
	    		if(flag==1)
                    printf("The tree has been destroyed successfully!\n");
                else 
                    printf("The tree has been destroyed failed!\n");
	    		getchar();
                getchar();
	    		break;


	    	case 3://ClearBiTree
	    		if(!T)
                    printf("The tree has not been created!\n");
                else
                {
                    flag=ClearBiTree(T);//清空二叉树
                    if(flag==OK)
                        printf("The tree has been cleared successfully!\n");
                    else 
                        printf("The tree has been cleared failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 4://BiTreeEmpty
	    		flag=BiTreeEmpty(T);
	    		if(flag==1)
                    printf("The tree is empty!\n");
                else if(flag==0)
                    printf("The tree is not empty!\n");
                else 
                    printf("The tree has not been created!\n");

	    		getchar();
                printf("Press Enter to continue...");
                getchar();
	    		break;


	    	case 5://BiTreeDepth
	    		flag=BiTreeDepth(T);//求二叉树的深度
	    		if(flag!=-1) 
                    printf("The depth of the tree is %d.\n",flag);
                else 
                    printf("The tree has not been created!\n");
	    		getchar();
                getchar();
	    		break;


	    	case 6://LocateNode
				if(!T)
                    printf("The tree has not been created!\n");
                else
                {
                    printf("Please input the key of the node:");
                    scanf("%d",&key);
                    t=LocateNode(T,key);
                    if(t)  
                        printf("The node is (%d,%s).\n",t->data.key,t->data.others);
                    else   
                        printf("The node is not existed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 7://Assign
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("Please input as follows:\n");
                    printf("[key] [new key] [new data]\n");
                    scanf("%d%d%s",&key,&val.key,val.others);
                    flag=Assign(T,key,val);
                    if(flag==1)
                        printf("The node has been assigned successfully!\n");
                    else 
                        printf("The node has been assigned failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 8://GetSibling
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("Please input the key of the node:");
                    scanf("%d",&key);
                    t=GetSibling(T,key);
                    if(t)  
                        printf("The sibling of the node is (%d,%s).\n",t->data.key,t->data.others);
                    else 
                        printf("The node is not existed or the node has no sibling!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 9://InsertNode
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("Please input as below:\n");
                    printf("[key] [0:insert left child/1:insert right child] [new key] [new data]\n");
                    scanf("%d%d%d%s",&key,&lr,&val.key,val.others);
                    flag=InsertNode(T,key,lr,val);
                    if(flag==1)
                        printf("The node has been inserted successfully!\n");
                    else 
                        printf("The node has been inserted failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 10://DeleteNode
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("Please input the key of the node:");
                    scanf("%d",&key);
                    flag=DeleteNode(T,key);
                    if(flag==1)
                        printf("The node has been deleted successfully!\n");
                    else 
                        printf("The node has been deleted failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 11://PreOrderTraverse
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("PreOrderTraverse:\n-------------\n\n");
                    PreOrderTraverse(T,Visit);
                    printf("\n\n-------------\nEND\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 12://InOrderTraverse
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("InOrderTraverse:\n-------------\n\n");
                    InOrderTraverse(T,Visit);
                    printf("\n\n-------------\nEND\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 13://PostOrderTraverse
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("PostOrderTraverse:\n-------------\n\n");
                    PostOrderTraverse(T,Visit);
                    printf("\n\n-------------\nEND\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 14://LevelOrderTraverse
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("LevelOrderTraverse:\n-------------\n\n");
                    LevelOrderTraverse(T,Visit);
                    printf("\n\n-------------\nEND\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 15://MaxPathSum
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                    printf("The max path sum is %d.\n",MaxPathSum(T));
        
	    		getchar();
                getchar();
	    		break;


	    	case 16://LowestCommonAncestor
	    		if(!T) 
                    printf("The tree has not been created!\n");
                else
                {
                    printf("Please input the key of the two nodes:\n");
                    scanf("%d%d",&key1,&key2);
                    t=LowestCommonAncestor(T,key1,key2);
                    if(t)
                        printf("The lowest common ancestor of the two nodes is (%d,%s).\n",t->data.key,t->data.others);
                    else 
                        printf("The two nodes are not existed or the tree is empty!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 17://InvertTree
	    		if(!T) 
                    printf("The tree has not been created!\n");
                else
                {
                    flag=InvertTree(T);
                    if(flag==1)  
                        printf("The tree has been inverted successfully!\n");
                    else 
                        printf("The tree has been inverted failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 18://SaveBiTree
	    		if(!T)  
                    printf("The tree has not been created!\n");
                else
                {
                    printf("Please input the file name:");
                    scanf("%s",FileName);
                    flag=SaveBiTree(T,FileName);
                    if(flag==1)
                        printf("The tree has been saved successfully!\n");
                    else 
                        printf("The tree has been saved failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 19://LoadBiTree
	    		if(T)  
                    printf("The tree has been created!\n");
                else
                {
                    printf("Please input the file name:");
                    scanf("%s",FileName);
                    flag=LoadBiTree(T,FileName);
                    if(flag==1)
                        printf("The tree has been loaded successfully!\n");
                    else 
                        printf("The tree has been loaded failed!\n");
                }
	    		getchar();
                getchar();
	    		break;


	    	case 0:
	    		break;


		}
    }
	getchar();
    getchar();
}