#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"

static void nodes_write(FILE *file, struct node *node);
static struct node *nodes_read(FILE *file, struct node *parent);
static int seek_brace(FILE *file);
static void get_key(FILE *file, struct node *node);
static void seek_str(FILE *file);
static void skip_spaces(FILE *file);

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

void tree_read(struct tree *tree)
{
        FILE *file = fopen("tree.txt", "r");
        tree->root = nodes_read(file, NULL);
        fclose(file);
}

static struct node *nodes_read(FILE *file, struct node *parent)
{
        struct node *node = node_ctor();
        int brace = seek_brace(file);

        if (brace == '{') {
                node->parent = parent;
                get_key(file, node);
        } else {
                ungetc(brace, file);
                node_dtor(node);
                return NULL;
        }

        node->left = nodes_read(file, node);
        node->right = nodes_read(file, node);

        getc(file);
        skip_spaces(file);
        return node;
}

static int seek_brace(FILE *file)
{
        static int ch = EOF;

        while ((ch = getc(file)) != EOF)
                if (ch == '{' || ch == '}')
                        break;
        return ch;
}

static void get_key(FILE *file, struct node *node)
{
        int ch = EOF;
        char str[keylen] = "";
        seek_str(file);

        fscanf(file, "%[^\"]", str);
        getc(file);
        strncpy(node->key, str, keylen);
}

static void seek_str(FILE *file)
{
        int ch = EOF;
        while ((ch = getc(file)) != EOF)
                if (ch == '"')
                        break;
}

static void skip_spaces(FILE *file)
{
        int ch = EOF;
        while ((ch = getc(file)) != EOF)
                if (!isspace(ch))
                        break;
        ungetc(ch, file);
}
