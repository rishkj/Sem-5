#include<stdio.h>

typedef struct tree
{
	int root;
	int fh;
}tree;

typedef struct node
{
	int key;
	int lo;
	int ro;
}node;

FILE* init(tree*, char* name);
void insertnode(FILE *f, tree *t, int key);
void deletenode(FILE *f, tree *t, int key);
void searchnode(FILE *f, tree *t, int key);
void preorder(FILE *f, tree *t);
void close(FILE *f, tree *t);
int compare(FILE *, FILE *, tree *, tree *);
int recursive_compare(FILE *, FILE *, int , int );