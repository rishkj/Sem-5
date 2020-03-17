#include<stdio.h>
#include<string.h>
#include"tree.h"

int main()
{
    FILE *fp;
    char *file_name = "tree.dat";
    tree t;

    fp = init_tree(&t,file_name);

    int choice;
    do
    {
        int key;
        int offset;
        
        printf("Enter the operation you wish to perform. Enter :\n");
        printf("1-To insert an element into the tree.\n");
        printf("2-To display current tree stored in file system.\n");
        printf("3-To search for an element in the tree.\n");
        printf("Any other number to quit.\n\n");
        
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            printf("Enter value of key you wish to insert.\n");
            scanf("%d",&key);
            insert(&t,fp,key);
            printf("\n");
            break;

            case 2:
            preorder(fp,&t);
            printf("\n");
            break;

            case 3:
            printf("Enter value of key to search for.\n");
            scanf("%d",&key);
            offset = search(fp,key,&t);
            if(offset == -1)
            {
                printf("Element not in tree.\n");
            }
            else
            {
                printf("Element occurs at offset %d in file.\n",offset);
            }
            printf("\n");
            break;

            default:
            printf("You will exit now.\n");

        }
    } while ( (choice == 1) || (choice == 2) || (choice == 3));
    
}
