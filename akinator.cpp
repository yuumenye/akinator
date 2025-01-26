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

static void print_menu(void);
static int get_input(void);
static void check_answer(struct node *node);
static void node_append(struct node *node);
static int perform_action(int input, struct tree *tree);
static void play_guesser(struct tree *tree);

void run_akinator()
{
        struct tree *tree = tree_ctor();
        tree_read(tree);

        while (1) {
                print_menu();
                int input = get_input();
                if (perform_action(input, tree) == -1)
                        break;
        }

        tree_write(tree);
        tree_dtor(tree);
}

static void print_menu(void)
{
        printf("(0) Save and exit\n"
               "(1) Play\n"
               "(2) Print definition\n");
}

static int get_input(void)
{
        const int buf_size = 128;
        char buf[buf_size] = "";

        int num = 0;
        int success = 0;

        do {
                fgets(buf, buf_size, stdin);
                if (feof(stdin) != 0)
                        exit(0);

                char *endptr = NULL;
                num = strtol(buf, &endptr, 10);
                if (endptr == buf)
                        success = 0;
                else if (*endptr && *endptr != '\n')
                        success = 0;
                else
                        success = 1;
        } while (!success);

        return num;
}

static int perform_action(int input, struct tree *tree)
{
        switch (input) {
                case 0:
                        return -1;
                case 1:
                        tree_draw(tree);
                        play_guesser(tree);
                        tree_draw(tree);
                        break;
                case 2:
                        print_def(tree);
                        break;
                default:
                        printf("Invalid option. Try again\n");
                        return 1;
        }
        return 0;
}

static void play_guesser(struct tree *tree)
{
        struct node *node = tree->root;

        while (node->left || node->right) {
                printf("%s?\n", node->key);
                printf("(0) No\n"
                       "(1) Yes\n");
                int answer = get_input();
                if (answer == 1)
                        node = node->right;
                else
                        node = node->left;
        }

        check_answer(node);
}

static void check_answer(struct node *node)
{
        printf("Is it \"%s\"?\n", node->key);
        printf("(0) No\n"
               "(1) Yes\n");
        int answer = get_input();
        if (answer == 1)
                printf("I guessed it!\n");
        else
                node_append(node);
}

static void node_append(struct node *node)
{
        char right_answer[keylen] = "";
        printf("What was it?\n");
        fgets(right_answer, keylen, stdin);
        right_answer[strcspn(right_answer, "\n")] = 0;

        char new_key[keylen] = "";
        printf("What is it that differentiates \"%s\" and \"%s\"?\n",
                        node->key, right_answer);
        fgets(new_key, keylen, stdin);
        new_key[strcspn(new_key, "\n")] = 0;

        printf("Is \"%s\" a \"yes\" or \"no\" answer to \"%s\"?\n",
                        right_answer, new_key);
        printf("(0) No\n"
               "(1) Yes\n");
        int answer = get_input();

        struct node *answer_node = node_ctor();
        struct node *new_node = node_ctor();

        strncpy(new_node->key, new_key, keylen);
        new_node->parent = node->parent;
        if (node == node->parent->left)
                node->parent->left = new_node;
        else
                node->parent->right = new_node;
        node->parent = new_node;
        answer_node->parent = new_node;
        strncpy(answer_node->key, right_answer, keylen);

        if (answer == 1) {
                new_node->right = answer_node;
                new_node->left = node;
        } else {
                new_node->left = answer_node;
                new_node->right = node;
        }
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
                fgets(key, keylen, stdin);
                key[strcspn(key, "\n")] = 0;

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
