#include <stdio.h>
#include "header.h"

FILE* init(tree *t, char* name)
{
	FILE* f1 = fopen("output.txt", "a+");
	fclose(f1);
	FILE* f2 = fopen(name, "a+");
	t->root = -1;
	t->fh = -1;
	fwrite(t,sizeof(tree),1, f2);
	fclose(f2);
	f2 = fopen(name, "r+");
	fread(t, sizeof(tree),1, f2);
	return f2;

}

void insertnode(FILE *f, tree *t, int key)
{
	node tempnode;
	int temp; int freeused = 0;	

	if(t->fh == -1)		//if there are no free nodes
	{
		fseek(f, 0, SEEK_END);
		temp = ftell(f);
	}

	else
	{
		freeused = 1;			
		temp = t->fh;
		fseek(f, temp, SEEK_SET);		//set file pointer to that
		fread(&tempnode, sizeof(node), 1, f);
		t->fh = tempnode.lo; 	//both left offset and right offset point to the same thing
	}

	tempnode.key = key;
	tempnode.lo = -1;
	tempnode.ro = -1;

	if(t->root == -1)		//if there are no nodes in the tree
	{
		t->root = temp;			//add node to the tree
		
		fseek(f, 0, SEEK_SET);
		fwrite(t, sizeof(tree), 1, f);
		fseek(f, temp, SEEK_SET); 
		fwrite(&tempnode, sizeof(node), 1, f);
	}

	else					//find suitable position if nodes are present in the tree
	{
		int previous = -1;				 
		int present = t->root;

	
		node pres_node; 
		node prev_node;
		
		fseek(f, present, SEEK_SET);		
		fread(&pres_node, sizeof(node), 1, f);
		
		while(present != -1)		//traversing tree to find a place to insert new node
		{
			previous = present;
			prev_node = pres_node;
			
			if(key > pres_node.key)
			{	
				present = pres_node.ro;
			}
			else if(key < pres_node.key)
			{
				present = pres_node.lo;
			}
			else			//if the key already exists
			{
				break;
			}

			if(present != -1)
			{	
				fseek(f, present, SEEK_SET);
				fread(&pres_node, sizeof(node), 1, f);
			}
		}

		if(previous == -1)				//if the position found is the root of the tree
		{
			if(key > pres_node.key)		//add the current root to either the left or the right subtree of the new root
			{
				tempnode.lo = present;
				tempnode.ro = -1;
			}
			else if(key < pres_node.key)
			{
				tempnode.lo = -1;
				tempnode.ro = present;
			}
			else						//if the key exists in the tree
			{
				if(freeused)
				{
					tempnode.lo = t->fh;	
					tempnode.ro = t->fh;
					t->fh = temp;
				}
				return;
			}

			t->root = temp;		//change the root to point to the new root
		}

		else
		{
			if(key < prev_node.key)		//decide where the new node goes in relation to the previous node
				prev_node.lo = temp;
			else if(key > prev_node.key)
				prev_node.ro = temp;
			else
			{
				if(freeused)
				{
					tempnode.lo = t->fh;
					tempnode.ro = t->fh;
					t->fh = temp;
				}
				return;
			}

			fseek(f, previous, SEEK_SET); 
			fwrite(&prev_node, sizeof(node), 1, f);
		}

		fseek(f, 0, SEEK_SET); 
		fwrite(t, sizeof(tree), 1, f);
		fseek(f, temp, SEEK_SET); 
		fwrite(&tempnode, sizeof(node), 1, f);
	}
}

void deletenode(FILE *f, tree *t, int key)
{
	if(t->root != -1)		//if tree is not empty
	{
		int previous = -1; 
		int present = t->root;
		
		node pres_node; 
		node prev_node;
		
		fseek(f, present, SEEK_SET);
		fread(&pres_node, sizeof(node), 1, f);
		
		while(present != -1 && pres_node.key != key)		//traversing thre tree to find the node
		{
			previous = present;
			prev_node = pres_node;
			
			if(key > pres_node.key)
			{	
				present = pres_node.ro;
			}
			else
			{
				present = pres_node.lo;
			}

			if(present != -1)
			{	
				fseek(f, present, SEEK_SET);
				fread(&pres_node, sizeof(node), 1, f);
			}
		}

		if(pres_node.key == key) //node is found
		{
			if(previous == -1) //to delete in the beginning or root node
			{
				if(pres_node.lo == -1 && pres_node.ro == -1)			//if root to be deleted is leaf node
				{
					t->root = -1;
				}

				else if(pres_node.lo == -1)	//root has only right subtree then make that root
				{
					t->root = pres_node.ro;
				}

				else if(pres_node.ro == -1) //root has only left subtree then make that root
				{
					t->root = pres_node.lo;
				}
				else //find the inorder successor of the root, make that the new root
				{
					
					int newprevious = -1;
					int newpresent = pres_node.ro;

					node newpres_node; 
					node newprev_node;
					
					fseek(f, newpresent, SEEK_SET);
					fread(&newpres_node, sizeof(node), 1, f);
					
					while(newpres_node.lo != -1)		//this loop is to find the inorder successor
					{
						newprevious = newpresent;					//newpresent is the inorder successor
						newprev_node = newpres_node;		//newprevious is the node previous to it
						newpresent = newpres_node.lo;

						fseek(f, newpresent, SEEK_SET);
						fread(&newpres_node, sizeof(node), 1, f);

					}

					if(newprevious != -1)			//if the inorder successor is not immediately after root
					{
						newprev_node.lo = newpres_node.ro;	//change its offsets accordingly
						newpres_node.ro = pres_node.ro;
					}
					
					newpres_node.lo = pres_node.lo;

					t->root = newpresent; 		//now change the root to the inorder successor

					fseek(f, newpresent, SEEK_SET);
					fwrite(&newpres_node, sizeof(node), 1, f);		//write the new changed nodes

					if(newprevious != -1)			//if the previous node has also been changed, write that
					{
						fseek(f, newprevious, SEEK_SET);
						fwrite(&newprev_node, sizeof(node), 1, f);
					}
				}
			}

			else 
			{
				if(pres_node.lo == -1 && pres_node.ro == -1)			//node to be deleted is leaf node
				{
					if(prev_node.key < pres_node.key) //if present node is right subtree of previous node
						prev_node.ro  = -1;
					else
						prev_node.lo = -1;	
				}

				else if(pres_node.lo == -1)	//present has only right subtree shift it to previous node
				{
					if(prev_node.key < pres_node.key) //if pres node is right subtree of previous node
						prev_node.ro  = pres_node.ro;
					else
						prev_node.lo = pres_node.ro;
				}

				else if(pres_node.ro == -1)
				{
					if(prev_node.key < pres_node.key)
						prev_node.ro  = pres_node.lo;
					else
						prev_node.lo = pres_node.lo;
				}
				else //if the node to be deleted is in the middle
				{					
					int newprevious = -1;		//find the inorder successor
					int newpresent = pres_node.ro;

					node newpres_node; 
					node newprev_node;
					
					fseek(f, newpresent, SEEK_SET);
					fread(&newpres_node, sizeof(node), 1, f);
					
					while(newpres_node.lo != -1)		//run this loop to find the inorder successor
					{
						newprevious = newpresent;
						newprev_node = newpres_node;

						fseek(f, newpresent, SEEK_SET);
						fread(&newpres_node, sizeof(node), 1, f);
					}

					if(newprevious != -1)
					{
						newprev_node.lo = newpres_node.ro;
						newpres_node.ro = pres_node.ro;
					}
					
					newpres_node.lo = pres_node.lo;

					if(present == prev_node.lo)
					{
						prev_node.lo = newpresent;
					}
					else
					{
						prev_node.ro = newpresent;
					}


					fseek(f, newpresent, SEEK_SET);
					fwrite(&newpres_node, sizeof(node), 1, f);

					if(newprevious != -1)
					{
						fseek(f, newprevious, SEEK_SET);
						fwrite(&newprev_node, sizeof(node), 1, f);
					}
				}

				fseek(f, previous, SEEK_SET);
				fwrite(&prev_node, sizeof(node), 1, f);
			}

			//add the node to be deleted to the free list

			pres_node.lo = t->fh;
			pres_node.ro = t->fh;
			t->fh = present;
	
			fseek(f, 0, SEEK_SET);
			fwrite(t, sizeof(tree), 1, f);
			fseek(f, present, SEEK_SET);
			fwrite(&pres_node, sizeof(node), 1, f);

		}
		else	//if node is not found
		{
			printf("-1\n");
		}
	}

	else	//if there exists no tree
	{
		printf("-1\n");
	}
}

void searchnode(FILE *f, tree *t, int key)
{
	if(t->root != -1)		//if tree is not empty, then check for the key in the tree
	{
		int previous = -1; 
		int present = t->root;
		
		node pres_node; 
		node prev_node;
		
		fseek(f, present, SEEK_SET);
		fread(&pres_node, sizeof(node), 1, f);
		
		while(present != -1 && pres_node.key != key)		//traversing the tree to find the node
		{
			previous = present;
			prev_node = pres_node;
			
			if(key > pres_node.key)
			{	
				present = pres_node.ro;
			}
			else
			{
				present = pres_node.lo;
			}

			if(present != -1)
			{	
				fseek(f, present, SEEK_SET);
				fread(&pres_node, sizeof(node), 1, f);
			}
		}

		if(pres_node.key == key)
		{
			// return("Yes");
			FILE* fp = fopen("output.txt", "a");
			fprintf(fp, "%d EXISTS\n", key);
			fclose(fp);
		}
		else
		{
			// return("No");
			FILE* fp = fopen("output.txt", "a");
			fprintf(fp, "%d DOES NOT EXIST\n", key);
			fclose(fp);
		}
	}
	else
	{
		// return("No");
		FILE* fp = fopen("output.txt", "a");
		fprintf(fp, "%d DOES NOT EXIST\n", key);
		fclose(fp);
	}
}

void preorder_compute(const tree *t, FILE *f, int offset, FILE* f1)
{
    if(offset == -1)
        return;
    else
    {
        node temp;
        fseek(f, offset, SEEK_SET);
        fread(&temp, sizeof(node), 1, f);
        
        fprintf(f1, "%d ", temp.key);		

        preorder_compute(t, f, temp.lo, f1);
        preorder_compute(t, f, temp.ro, f1);
    }
    
}

void preorder(FILE *f, tree *t)
{
    int off = t->root;
	node n;

    FILE* fp = fopen("output.txt", "a");
    preorder_compute(t, f, off, fp);
    fprintf(fp, "\n");

	int off1 = t->fh;
	while(off1 != -1)
	{
		fprintf(fp,"%d ",off1);
		
		fseek(f,off1,SEEK_SET);
		fread(&n,sizeof(node),1,f);

		off1 = n.lo;
	}
	fprintf(fp,"%d\n",off1);

    fclose(fp);
}

void close(FILE *f, tree *t)
{
	fclose(f);
}


int recursive_compare(FILE *f1, FILE *f2, int offset1, int offset2)
{
	if(offset1 == -1 || offset2 == -1)
	{
		if(offset1 == -1 && offset2 == -1)
		{
			return 1;
		}
		return 0;
	}
	
	node temp1;
	node temp2;
	
	fseek(f1,offset1,SEEK_SET);
	fread(&temp1,sizeof(node),1,f1);

	fseek(f2,offset2,SEEK_SET);
	fread(&temp2,sizeof(node),1,f2);
	
	if(temp1.key != temp2.key)
	{
		return 0;
	}
	
	return recursive_compare(f1,f2,temp1.lo,temp2.lo) && recursive_compare(f1,f2,temp1.ro,temp2.ro);
}


int compare(FILE *f1, FILE *f2, tree *t1, tree *t2)
{
	fseek(f1,0,SEEK_SET);
	fread(t1,sizeof(tree),1,f1);

	fseek(f2,0,SEEK_SET);
	fread(t2,sizeof(tree),1,f2);

	node temp1;
	node temp2;

	int offset1 = t1->root;
	int offset2 = t2->root;

	// fseek(f1,offset1,SEEK_SET);
	// fread(&temp1,sizeof(node),1,f1);

	// fseek(f2,offset2,SEEK_SET);
	// fread(&temp2,sizeof(node),1,f2);

	return recursive_compare(f1,f2,offset1,offset2);

	return 1;
}
