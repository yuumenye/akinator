#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"

static struct node *node_ctor();
static void node_dtor(struct node *node);

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

static struct node *node_ctor(void)
{
        struct node *node = (struct node*) calloc(1, sizeof(struct node));
        if (!node) {
                fprintf(stderr, "error: couldn't allocate memory\n");
                exit(1);
        }
        return node;
}

static void node_dtor(struct node *node)
{
        free(node);
        node = NULL;
}
