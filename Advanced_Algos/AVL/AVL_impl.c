#include<stdio.h>
#include"tree.h"

FILE *init_tree(tree *t, const char *name)
{
    FILE *fp = fopen(name,"w");

    t->free_pos = -1;
    t->root = -1;

    fwrite(t,sizeof(tree),1,fp);
    fclose(fp);

    fp = fopen(name,"r+");
    fread(t,sizeof(tree),1,fp);
    return fp;

}


int cal_height(FILE *fp, int pos)
{
    if(pos == -1)
    {
        return 0;
    }
    fseek(fp,pos,SEEK_SET);
    node temp;
    fread(&temp,sizeof(node),1,fp);
    
    int l = cal_height(fp,temp.left_branch);
    int r = cal_height(fp,temp.right_branch);

    if(l>r)
    {
        return 1 + l;
    }
    return 1 + r;
}


int cal_bal(FILE *fp, node n, int pres)
{
    if(pres == -1)
    {
        return 0;
    }
    return cal_height(fp,n.left_branch) - cal_height(fp,n.right_branch);
}


node right_rotate(FILE *fp, node pres_n, node temp, tree *t, int pres)
{
    node new_node;
    node new_node1;
    
    int par_key = pres_n.key;
    int par_offset = pres;
    int right_offset = pres_n.right_branch;
    int left_offset = pres_n.left_branch;

    int child_key = temp.key;
    int child_offset = pres_n.left_branch;
    int child_right_offset = temp.right_branch;
    int child_left_offset = temp.left_branch;

    new_node.key = par_key;
    new_node.left_branch = child_right_offset;
    new_node.right_branch = right_offset;
    int pos1;
    if(t->free_pos == -1)
    {
        fseek(fp,0,SEEK_END);
        pos1 = ftell(fp);
    }
    else
    {
        pos1 = t->free_pos;
        fseek(fp,pos1,SEEK_SET);
        fread(&new_node1,sizeof(node),1,fp);
        t->free_pos = new_node1.left_branch;
    }

    fseek(fp,pos1,SEEK_SET);
    fwrite(&new_node,sizeof(node),1,fp);
        
    pres_n.key = child_key;
    pres_n.left_branch = child_left_offset;
    pres_n.right_branch = pos1;

    fseek(fp,pres,SEEK_SET);
    fwrite(&pres_n,sizeof(node),1,fp);

    temp.left_branch = t->free_pos;
    temp.right_branch = t->free_pos;
    t->free_pos = child_offset;
        
    fseek(fp,0,SEEK_SET);
    fwrite(t,sizeof(tree),1,fp);

    return pres_n;    
}


node left_rotate(FILE *fp, node pres_n, node temp, tree *t, int pres)
{
    node new_node;
    node new_node1;
    
    int par_key = pres_n.key;
    int par_offset = pres;
    int right_offset = pres_n.right_branch;
    int left_offset = pres_n.left_branch;

    int child_key = temp.key;
    int child_offset = pres_n.left_branch;
    int child_right_offset = temp.right_branch;
    int child_left_offset = temp.left_branch;

    new_node.key = par_key;
    new_node.left_branch = left_offset;
    new_node.right_branch = child_left_offset;
    int pos1;
    if(t->free_pos == -1)
    {
        fseek(fp,0,SEEK_END);
        pos1 = ftell(fp);
    }
    else
    {
        pos1 = t->free_pos;
        fseek(fp,pos1,SEEK_SET);
        fread(&new_node1,sizeof(node),1,fp);
        t->free_pos = new_node1.left_branch;
    }

    fseek(fp,pos1,SEEK_SET);
    fwrite(&new_node,sizeof(node),1,fp);

    pres_n.key = child_key;
    pres_n.left_branch = pos1;
    pres_n.right_branch = child_right_offset;

    fseek(fp,pres,SEEK_SET);
    fwrite(&pres_n,sizeof(node),1,fp);
        

    temp.left_branch = t->free_pos;
    temp.right_branch = t->free_pos;
    t->free_pos = child_offset;
        
    fseek(fp,0,SEEK_SET);
    fwrite(t,sizeof(tree),1,fp);

    return pres_n;
}


void insert(tree *t, FILE *fp, int key)
{
    node n;
    int pos;

    // In case there is no free position in file, we find available position at end of file.
    if(t->free_pos == -1)
    {
        fseek(fp,0,SEEK_END);
        pos = ftell(fp);
    }

    // If free position exists, we use that to store new element, and update position of free space in file.
    else
    {
        pos = t->free_pos;
        fseek(fp,pos,SEEK_SET);
        fread(&n,sizeof(node),1,fp);
        t->free_pos = n.left_branch;
    }

    //When there are no nodes in the tree
    if(t->root == -1)
    {
        t->root = pos;

        n.key = key;
        n.left_branch = -1;
        n.right_branch = -1;

        fwrite(&n,sizeof(node),1,fp);

        fseek(fp,0,SEEK_SET);
        fwrite(t,sizeof(tree),1,fp);

        return;
    }

    int pres = t->root;

    node pres_n;

    fseek(fp,pres,SEEK_SET);
    fread(&pres_n,sizeof(node),1,fp);

    recursive_insert(t,fp,key,pres_n,pres,pos);

}

node recursive_insert(tree *t, FILE *fp, int key, node pres_n, int pres, int pos)
{
    node temp;
    int new_offset;
    node new_node;
    node new_node1;


    if(pres == -1)
    {
        fseek(fp,pos,SEEK_SET);
        fread(&temp,sizeof(node),1,fp);
        temp.key = key;
        temp.left_branch = -1;
        temp.right_branch = -1;

        fseek(fp,pos,SEEK_SET);
        fwrite(&temp,sizeof(node),1,fp);

        return temp;
    }

    else if(key < pres_n.key)
    {
        new_offset = pres_n.left_branch;
        fseek(fp,new_offset,SEEK_SET);
        fread(&new_node,sizeof(node),1,fp);

        temp = recursive_insert(t,fp,key,new_node,new_offset,pos);

        if(temp.key == key)
        {
            pres_n.left_branch = pos;
            fseek(fp,pres,SEEK_SET);
            fwrite(&pres_n,sizeof(node),1,fp);
        }
    }

    else if(key > pres_n.key)
    {
        new_offset = pres_n.right_branch;
        fseek(fp,new_offset,SEEK_SET);
        fread(&new_node,sizeof(node),1,fp);

        temp = recursive_insert(t,fp,key,new_node,new_offset,pos);

        if(temp.key == key)
        {
            pres_n.right_branch = pos;
            fseek(fp,pres,SEEK_SET);
            fwrite(&pres_n,sizeof(node),1,fp);
        }
    }

    else
    {
        return pres_n;
    }

    int balance = cal_bal(fp,pres_n,pres);

    if( (balance > 1) && (key < temp.key) )
    {
        pres_n = right_rotate(fp,pres_n,temp,t,pres);
        return pres_n;
    }

    else if( (balance < -1) && (key > temp.key) )
    {
        pres_n = left_rotate(fp,pres_n,temp,t,pres);
        return pres_n;
    }

    else if( (balance > 1) && (key > temp.key) )
    {
        node child_temp;
        int temp_child_offset = temp.right_branch;

        fseek(fp,temp_child_offset,SEEK_SET);
        fread(&child_temp,sizeof(node),1,fp);

        temp = left_rotate(fp,temp,child_temp,t,pres_n.left_branch);

        pres_n = right_rotate(fp,pres_n,temp,t,pres);

        return pres_n;
    }

    else if( (balance < -1) && (key < temp.key) )
    {
        node child_temp;
        int temp_child_offset = temp.left_branch;

        fseek(fp,temp_child_offset,SEEK_SET);
        fread(&child_temp,sizeof(node),1,fp);

        temp = right_rotate(fp,temp,child_temp,t,pres_n.right_branch);

        pres_n = left_rotate(fp,pres_n,temp,t,pres);

        return pres_n;
    }

    return pres_n;
}


void preorder_compute(const tree *t, FILE *fp, int offset, FILE* f1)
{
    if(offset == -1)
        return;
    else
    {
        node temp;
        fseek(fp, offset, SEEK_SET);
        fread(&temp, sizeof(node), 1, fp);
        
        fprintf(f1, "%d ", temp.key);		

        preorder_compute(t, fp, temp.left_branch, f1);
        preorder_compute(t, fp, temp.right_branch, f1);
    }
    
}

void preorder(FILE *fp, tree *t)
{
    int off = t->root;

    FILE* f = fopen("output.txt", "a");
    preorder_compute(t, fp, off, f);
    fprintf(f, "\n");

    fclose(f);
}


int search(FILE *fp, int key, tree *t)
{
    fseek(fp,0,SEEK_SET);
    fread(t,sizeof(tree),1,fp);

    int offset = t->root;
    node temp;

    fseek(fp,offset,SEEK_SET);
    fread(&temp,sizeof(temp),1,fp);

    while(offset != -1 && temp.key != key)
    {
        if(key < temp.key)
        {
            offset = temp.left_branch;
        }
        else
        {
            offset = temp.right_branch;
        }

        fseek(fp,offset,SEEK_SET);
        fread(&temp,sizeof(temp),1,fp);
    }

    return offset;
}