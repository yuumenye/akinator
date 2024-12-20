#ifndef TREE_H
#define TREE_H

const int keylen = 100;

struct node {
        char key[keylen];
        struct node *left;
        struct node *right;
        struct node *parent;
};

struct tree {
        struct node *root;
};

struct tree *tree_ctor(void);
void tree_dtor(struct tree *tree);
struct node *node_ctor();
void node_dtor(struct node *node);

void tree_write(struct tree *tree);
void tree_read(struct tree *tree);

#endif
