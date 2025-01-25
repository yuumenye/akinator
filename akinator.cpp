#include <stdlib.h>
#include <stdio.h>
#include "akinator.h"
#include "string.h"
#include "tree.h"
#include "draw.h"
#include "stack.h"

static void print_def(struct tree *tree);
static struct node *get_search_node(struct tree *tree);
static void save_node_path(struct node *node, struct stack *stk);
static void print_node_path(struct stack *stk);

void run_akinator()
{
        struct tree *tree = tree_ctor();
        tree_read(tree);
        tree_draw(tree);

        print_def(tree);

        tree_write(tree);
        tree_dtor(tree);
}

static void print_def(struct tree *tree)
{
        struct node *node = get_search_node(tree);

        const int stk_capacity = 100;
        struct stack stk = {};
        stack_ctor(&stk, stk_capacity, sizeof(struct node *));

        save_node_path(node, &stk);
        printf("%s is ", node->key);
        print_node_path(&stk);

        stack_dtor(&stk);
}

static struct node *get_search_node(struct tree *tree)
{
        struct node *node = NULL;
        while (!node) {
                char key[keylen] = "";
                if (scanf("%s", key) == EOF)
                        exit(0);

                node_find(tree->root, &node, key);

                if (!node)
                        printf("Couldn't find node \"%s\"\n", key);
        }
        return node;
}

static void save_node_path(struct node *node, struct stack *stk)
{
        while (node) {
                stack_push(stk, &node);
                node = node->parent;
        }
}

static void print_node_path(struct stack *stk)
{
        struct node *node1 = NULL;
        struct node *node2 = NULL;

        stack_pop(stk, &node1);
        while (stk->size > 0) {
                stack_pop(stk, &node2);

                if (node2 == node1->left)
                        printf("not ");

                printf("%s ", node1->key);
                node1 = node2;
        }
        printf("\n");
}
