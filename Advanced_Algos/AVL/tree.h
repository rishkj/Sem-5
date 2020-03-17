#ifndef TREE_H
#define TREE_H

typedef struct node
{
    int key;
    int left_branch;
    int right_branch;
    // int height_diff;
}node;

typedef struct tree
{
    int free_pos;
    int root;
}tree;

FILE *init_tree(tree *,const char *);

int cal_height(FILE *,int);

int cal_bal(FILE *,node,int);

void insert(tree *,FILE *,int);

node recursive_insert(tree *,FILE *,int,node,int,int);

void preorder_compute(const tree *,FILE *,int,FILE *);

void preorder(FILE *,tree *);

node right_rotate(FILE *,node,node,tree *,int);

node left_rotate(FILE *,node,node,tree *,int);

int search(FILE *,int,tree *);

#endif