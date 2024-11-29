#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "draw.h"

static void generate_filename(char *filename, int namelen);
static void compile_dot(char *filename);
static void write_all(FILE *file, struct node *node);
static void write_params(FILE *file);
static void write_nodes(FILE *file, struct node *node);
static void write_edges(FILE *file, struct node *node);

/* draw tree using graphviz */
void tree_draw(struct tree *tree)
{
        const int namelen = 25;
        char filename[namelen] = "";
        generate_filename(filename, namelen);

        FILE *file = fopen(filename, "w");
        write_all(file, tree->root);
        fclose(file);

        compile_dot(filename);
}

static void generate_filename(char *filename, int namelen)
{
        static int filenum = 0;
        snprintf(filename, namelen, "log/tree%03d.dot", filenum++);
}

static void compile_dot(char *filename)
{
        const int cmdlen = 100;
        char cmd[cmdlen] = "";
        snprintf(cmd, cmdlen, "dot -T png %s -o %.11s.png", filename, filename);
        system(cmd);
}

static void write_all(FILE *file, struct node *node)
{
        fprintf(file, "digraph grph {\n");
        write_params(file);
        write_nodes(file, node);
        fprintf(file, "}\n");
}

static void write_params(FILE *file)
{
        fprintf(file, "  node [\n");
        fprintf(file, "    shape = Mrecord;\n");
        fprintf(file, "    style = filled;\n");
        fprintf(file, "    fillcolor = \"#D3E29D\";\n");
        fprintf(file, "  ]\n");
        fprintf(file, "  edge [label = \" \"];\n");
}

static void write_nodes(FILE *file, struct node *node)
{
        if (!node)
                return;

        fprintf(file, "  n%p [label = \"{<k>%s|{<l>%s|<r>%s}}\"];\n",
                        node, node->key,
                        (node->left)  ? "-" : "",
                        (node->right) ? "+" : "");
        write_edges(file, node);
        write_nodes(file, node->left);
        write_nodes(file, node->right);
}

static void write_edges(FILE *file, struct node *node)
{
        if (!node->parent)
                return;

        if (node->parent->left == node)
                fprintf(file, "  n%p:l -> n%p:k;\n", node->parent, node);
        else
                fprintf(file, "  n%p:r -> n%p:k;\n", node->parent, node);
}
