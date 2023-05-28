/*
* ==================================================================

* Description: Sequence_List.cpp
* Author: Konrad Locas.
* (C)Copyright Konrad Locas.
* All rights reserved.
* Date: 2023/04/04 16:45:09

* ===================================================================
*/
#include"SequenceListFunc.h"


// main function
int main(void)
{
    SqList L; 
    L.elem=NULL; // Initialize the Sequence List
    int op=1;   
    int flag=0;

    while(op)
    {
        system("cls");	// Clear the screen

        // Menu
        printf("\n\n");
        printf("  Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    1. InitList       7. LocateElem\n");
        printf("    2. DestroyList    8. PriorElem\n");
        printf("    3. ClearList      9. NextElem \n");
        printf("    4. ListEmpty      10. ListInsert\n");
        printf("    5. ListLength     11. ListDelete\n");
        printf("    6. GetElem        12. ListTraverse\n");
        printf("    ———————————————————————————————————\n");
        printf("    13.MaxSubArray    14.SubArrayNum\n");
        printf("    15.SortList       16.SaveList\n");
        printf("    17.LoadList\n");
        printf("    ———————————————————————————————————\n");
        printf("    0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("Choose your operation[0~17]:\n");
        printf("Press Enter to continue after a certain operation...\n");
        

        // input the operation number
        scanf("%d",&op);


        // Switch the operation
        switch(op)
        {
            case 1:// InitList
            {
                if(InitList(L)==OK) 
                    printf("Success!\n");
                else 
                    printf("Failed!\n");

                getchar();// pause
                getchar();
                break;
            }

            case 2:// DestroyList
            {
                if(DestroyList(L)==OK)  
                    printf("Success!\n");
                else 
                    printf("Failed!\n");   

                getchar();// pause
                getchar();
                break;
            }

            case 3:// ClearList
            {
                if(ClearList(L)==OK)    
                    printf("Success!\n"); 
                else 
                    printf("Failed!\n");

                getchar();// pause
                getchar();
                break;
            }

            case 4:// ListEmpty
            {
                if(ListEmpty(L)==TRUE)   
                    printf("The Sequence List is empty!\n");
                else if(ListEmpty(L)==FALSE) 
                    printf("The Sequence List is not empty!\n");
                else 
                    printf("Failed!\n");

                getchar();// pause
                getchar();
                break;
            }

            case 5:// ListLength
            {
                if(ListLength(L)!=INFEASIBLE)
                {
                    int Length=0;
                    Length=ListLength(L);
                    printf("Success!\n THe length of the Sequence List is %d .\n",Length);
                }
                else 
                    printf("Failed!\n");

                getchar();// pause
                getchar();
                break;
            }

            case 6:// GetElem
            {
                int i=0; 
                ElemType e=0;

                printf("Which element(->position) do you want to get?\n");
                scanf("%d",&i);

                if(GetElem(L,i,e)==ERROR)
                    printf("The value of i is illegal!\n");
                else if(GetElem(L,i,e)==INFEASIBLE) 
                    printf("Failed to get the element!\n");
                else if(GetElem(L,i,e)==OK) 
                {
                    printf("Success!\n");
                    printf("The element is %d .\n",e);
                }     

                getchar();// pause
                getchar();
                break;
            }

            case 7:// LocateElem
            {   
                int i=0;
                ElemType e=0;

                printf("Which element do you want to locate?\n");
                scanf("%d",&e);

                i=LocateElem(L,e);

                if(i==INFEASIBLE)
                    printf("The Sequence List is not exist!\n");
                if(i==0)
                    printf("The element is not exist.\n");
                if(i!=INFEASIBLE&&i!=0)
                    printf("The element is in the No.%d position.\n",i);

                getchar();// pause
                getchar();
                break;
            }

            case 8:// PriorElem
            {
                ElemType e=0;
                printf("Which element(->value) do you want to get the prior element?\n");
                scanf("%d",&e);
                ElemType pre_e=0;

                if(PriorElem(L,e,pre_e)==ERROR)
                    printf("The element has no prior element!\n");
                if(PriorElem(L,e,pre_e)==INFEASIBLE)
                    printf("The Sequence List is not exist!\n");
                if(PriorElem(L,e,pre_e)==OK)
                {
                    printf("Success!\n");
                    printf("The prior element is %d .\n",pre_e);
                }  

                getchar();// pause
                getchar();
                break;
            }

            case 9:// NextElem
            {
                ElemType e=0;
                printf("Which element(->value) do you want to get the next element?\n");
                scanf("%d",&e);
                ElemType next_e=0;
                if(NextElem(L,e,next_e)==ERROR)
                    printf("The element has no next element!\n");
                if(NextElem(L,e,next_e)==INFEASIBLE)
                    printf("The Sequence List is not exist!\n");
                if(NextElem(L,e,next_e)==OK)
                {
                    printf("Success!\n");
                    printf("The next element is %d .\n",next_e);
                }   

                getchar();// pause
                getchar();
                break;
            }

            case 10:// ListInsert
            {   
                int i;
                ElemType e;
                printf("format: [serial number] [element]\n");
                scanf("%d%d", &i, &e);
                if(ListInsert(L, i, e)==OK) 
                    printf("Success!\n");
                else if(ListInsert(L, i, e)==INFEASIBLE) 
                    printf("Sequence is empty! Initialize first!\n");
                else 
                    printf("Insertion failed! Check your input!\n");

                getchar();// pause
                getchar();
                break;
            }

            case 11:// ListDelete
            {
                int i=0,j=0;
                ElemType e=0;
                printf("Which element(->serial number) do you want to delete?\n");
                scanf("%d",&i);
                j=ListDelete(L,i,e);
                if(j==ERROR)
                    printf("The position is illegal!\n");
                if(j==INFEASIBLE)
                    printf("The Sequence List is not exist!\n");
                if(j==OK)
                {
                    printf("Success!\n");
                    printf("The deleted element is %d .\n",e);
                }    

                getchar();// pause
                getchar();
                break;
            }

            case 12:// ListTraverse
            {
                if(!ListTraverse(L)) 
                    printf("The Sequence List is not exist!\n");

                getchar();// pause
                getchar();
                break;
            }

            case 13:// MaxSubArray
            {
                MaxSubArray(L);
                printf("The maximum sum of the subarray is %d .\n",ans);

                getchar();// pause
                getchar();
                break;
            }

            case 14:// SubArrayNum
            {
                int k=0;
                printf("Please input the sum of the subarray.\n");
                scanf("%d",&k); 
                SubArrayNum(L,k);
                printf("The number of the subarray whose sum is %d is %d .\n",k,ans);

                getchar();// pause
                getchar();
                break;
            }

            case 15:// SortList
            {
                printf("The Sequence List is being sorted.\n\n");
                SortList(L);

                getchar();// pause
                getchar();
                break;
            } 

            case 16:// SaveList
            {
                char FileName[100];
                printf("Please input the file name.\n");
                scanf("%s",&FileName); 
                if(SaveList(L,FileName))
                    printf("The Sequence List has been saved in the txt file successfully!\n");
                else 
                    printf("Failed!\n");

                getchar();// pause
                getchar();
                break;
            }

            case 17:// LoadList
            {
                if(!L.elem)
                {
                    char FileName[100];
                    printf("Please input the file name.\n");
                    scanf("%s",&FileName); 
                    if(LoadList(L,FileName))
                        printf("The Sequence List has been loaded successfully!\n");
                    else 
                        printf("Failed!\n");

                    getchar();// pause
                    getchar();
                    break;
                }
                else
                {
                    printf("The Sequence List had existed!\n");

                    getchar();// pause
                    getchar();
                    break;
                }
            }

            case 0:// Exit
                break;
        }
    }
    printf("Bye!\n");
    return 0;
}



