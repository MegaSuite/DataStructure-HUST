/*
* ==================================================================

* Description: Linked_List.cpp
* Author: Konrad Locas.
* (C)Copyright Konrad Locas.
* All rights reserved.
* Date: 2023/04/18 17:24:13

* ===================================================================
*/
#include "LinkedListFunc.h"

//main function
int main()
{
	char filename[40];
	int op=1;
    int i,flag=0,i_num=0;
    LinkList L[MAX_NUM];


    for (i = 0; i<MAX_NUM; i++)
    	L[i]=NULL;

	ElemType e, cur_e, pre_e, next_e;


    while(op)
	{
		system("cls");

		printf("\n\n");
		printf("  	   Menu for Linear Table On LinkedList \n");
		printf("----------------------------------------------------------------------------\n");
		printf("     		1.InitList         2.DestroyList\n");
		printf("     		3.ClearList        4.ListEmpty\n");
		printf("     		5.ListLength       6.GetElem \n");
		printf("    		7.LocateElem       8.PriorElem \n");
		printf("     		9. NextElem        10.ListInsert\n");
		printf("     		11.ListDelete      12.ListTraverse\n");
		printf("     		13.SaveList        14.LoadList\n");
		printf("        ------------------------------------------------\n");		
		printf("     		15.ReverseList     16.RemoveNthFromEnd\n\n");
		printf("     		17.SortList        0. Exit\n\n");
		printf("		The max number of lists is %d.\n", MAX_NUM);
		printf("----------------------------------------------------------------------------\n");

		printf("Choose your operation[0--15]:\n");
		scanf("%d",&op);


		switch(op)
		{
			case 1://InitList
				if(InitList(&L[i_num])==OK)
				{
					printf("Input the filename to save the list:\n");
					scanf("%s", filename);
					printf("Success!\n");
				}
				else 
					printf("Failed!\n");

				getchar();
				getchar();
				break;

			case 2://DestroyList
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				if(DestroyList(&L[i_num])==OK)
					printf("Success!\n");
				else 
					printf("Failed!\n");

				getchar();
				getchar();
				break;

			case 3://ClearList
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				if(ClearList(&L[i_num])==OK)
					printf("Success!\n");
				else 
					printf("Failed!\n");

				getchar();
				getchar();
				break;

			case 4://ListEmpty
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				if(ListEmpty(L[i_num])==TRUE)
					printf("The file is empty!\n");

				else 
					printf("The file is not empty!\n");

				getchar();
				getchar();
				break;

			case 5://ListLength
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				printf("The length of the list is %d\n",ListLength(L[i_num]));

				getchar();
				getchar();
				break;

			case 6://GetElem
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				printf("Input the position of the element you wanna get:\n");
				scanf("%d",&i);
				if(GetElem(L[i_num],i,&e)==OK)
					printf("The element of the position %d is %d\n",i,e);
				else  
					printf("The position is invalid!\n");

				getchar();
				getchar();
				break;

			case 7://LocateElem
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				printf("Input the element you wanna locate:\n");

				scanf("%d",&e);

				if(i=LocateElem(L[i_num],e,compare))
					printf("The element %d is in the position %d\n",e,i);
				else  
					printf("The element doesn't exist!\n");

				getchar();
				getchar();
				break;

			case 8://PriorElem
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				printf("Input the element you wanna get its prior element:\n");

				scanf("%d",&cur_e);

				PriorElem(L[i_num],cur_e,&pre_e);

				if(PriorElem(L[i_num],cur_e,&pre_e)==OK)
					printf("The prior element of %d is %d\n",cur_e,pre_e);
				else if(PriorElem(L[i_num],cur_e,&pre_e)==OVERFLOW)
					printf("The element doesn't exist!\n");
				else 
					printf("The element doesn't have a prior element!\n");

				getchar();
				getchar();
				break;


			case 9://NextElem
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				printf("Input the element you wanna get its next element:\n");

				scanf("%d",&cur_e);

				if(NextElem(L[i_num],cur_e,&next_e)==OK)
					printf("The next element of %d is %d\n",cur_e,next_e);
				else if(NextElem(L[i_num],cur_e,&pre_e)==ERROR)
					printf("The element doesn't exist!\n");
				else
					printf("The element doesn't have a next element!\n");

				getchar();
				getchar();
				break;

			case 10://ListInsert
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				printf("Input the element and its position :\n");
				printf("format:[position] [element]\n");
				
				scanf("%d %d",&i,&e);

				if(ListInsert(&L[i_num],i,e)==OK)
					printf("Success!\n");
				else
					printf("Failed!\n");

				getchar();
				getchar();
				break;

			case 11://ListDelete
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				printf("Input the position of the element you wanna delete:\n");
				scanf("%d",&i);
				if(ListDelete(&L[i_num],i,&e)==OK)
					printf("Success!\n");
				else
					printf("Failed!\n");

				getchar();
				getchar();
				break;

			case 12://ListTrabverse
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				if(ListTrabverse(L[i_num])==0) 
					printf("The list is empty!\n");

				getchar();
				getchar();
				break;

			case 13://SaveList
				if(L[i_num] == NULL)
				{
					printf("The list doesn't exist!\n");

					getchar();
					getchar();
					break;
				}
				if(SaveList(L[i_num], filename)==OK)
					printf("file named %s has been saved!\n",filename);

					getchar();
					getchar();
				break;

			case 14://LoadList
				InitList(&L[i_num]);

				printf("Input the filename you wanna load:\n");

				scanf("%s", filename);

				if(LoadList(&L[i_num], filename)==OK)
					printf("file named %s has been loaded!\n",filename);
					getchar();
					getchar();
				break;

			case 15://ReverseList
				flag=ReverseList(&L[i_num]);
				if(flag== INFEASIBLE) 
					printf("The list doesn't exist!\n");
				else if(flag == ERROR) 
					printf("The list is empty!\n");
				else
					printf("Success!\n");

				getchar(); 
				getchar();
				break;


			case 16://RemoveNthFromEnd
				printf("Input the position of the element you wanna delete:\n");
				scanf("%d",&i);
				flag=RemoveNthFromEnd(L[i_num],i,e);
				if(flag== INFEASIBLE) 
					printf("The list doesn't exist!\n");
				else if(flag == ERROR) 
					printf("The list is empty!\n");
				else
					printf("Success!\n");

				getchar(); 
				getchar();
				break;

			
			case 17://SortList
				flag=SortList(L[i_num]);
				if(flag== INFEASIBLE) 
					printf("The list doesn't exist!\n");
				else if(flag == ERROR) 
					printf("The list is empty!\n");
				else
					printf("Success!\n");

				getchar(); 
				getchar();
				break;

			case 0://Exit
				break;
		}
	}
	printf("Bye!\n");
}


