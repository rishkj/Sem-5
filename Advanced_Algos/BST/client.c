#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main()
{
	FILE *f;
	FILE *f2;
	FILE *f_selected;
	tree t;
	tree t2;
	tree t_selected;
	f = init(&t, "bin.dat");
	f2 = init(&t2, "bin1.dat");
	// FILE *f_array[2]={f,f2};
	// tree t_array[2] = {t,t2};
	
	int choice, key;
	scanf("%d", &choice);

	/*
	1 - Insert
	2 - Delete
	3 - Search
	4 - Preorder
	5 - Create new tree
	-1 - Exit 
	*/

	while(choice != -1)
	{
		int selected;
		if(choice != 5)
		{
			printf("Enter the tree you want -(1 or 2)?.\n");
			scanf("%d",&selected);
		}
		// selected -= 1;
		// f_selected = f_array[selected];
		// t_selected = t_array[selected];
		int x;
		switch(choice)
		{
			case 1: scanf("%d",&key);
					if(selected == 1)
					{
						insertnode(f,&t,key);
					}
					else
					{
						insertnode(f2,&t2,key);
					}
					
					// insertnode(f_selected,&t_selected,key);
					break;

			case 2: scanf("%d",&key);
					if(selected == 1)
					{
						deletenode(f,&t,key);
					}
					else
					{
						deletenode(f2,&t2,key);
					}
					
					// deletenode(f_selected,&t_selected,key);
					break;

			case 3: scanf("%d",&key);
					if(selected == 1)
					{
						searchnode(f,&t,key);
					}
					else
					{
						searchnode(f2,&t2,key);
					}
					
					// searchnode(f_selected,&t_selected,key);
					break;

			case 4: if(selected == 1)
					{
						preorder(f,&t);
					}
					else
					{
						preorder(f2,&t2);
					}
					
					// preorder(f_selected,&t_selected);
					break;
			
			case 5: x = compare(f,f2,&t,&t2);
					if(x == 0)
					{
						printf("Not equal.\n");
					}
					else
					{
						printf("Equal.\n");
					}
					

		}
		scanf("%d", &choice);
	}
	close(f,&t);
}