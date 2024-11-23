#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

static void nodes_write(FILE *file, struct node *node);

struct tree *tree_ctor(void)
{
        struct tree *tree = (struct tree*) calloc(1, sizeof(struct tree));
        if (!tree) {
                fprintf(stderr, "error: couldn't allocate memory\n");
                exit(1);
        }
        return tree;
}

void tree_dtor(struct tree *tree)
{
        free(tree);
        tree = NULL;
}

struct node *node_ctor(void)
{
        struct node *node = (struct node*) calloc(1, sizeof(struct node));
        if (!node) {
                fprintf(stderr, "error: couldn't allocate memory\n");
                exit(1);
        }
        return node;
}

void node_dtor(struct node *node)
{
        free(node);
        node = NULL;
}

void tree_write(struct tree *tree)
{
        FILE *file = fopen("tree.txt", "w");
        nodes_write(file, tree->root);
        fclose(file);
}

static void nodes_write(FILE *file, struct node *node)
{
        if (!node)
                return;
        
        fprintf(file, "{\n");
        fprintf(file, "\"%s\"\n", node->key);
        
        nodes_write(file, node->left);
        nodes_write(file, node->right);

        fprintf(file, "}\n");
}
