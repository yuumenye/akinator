#include "akinator.h"
#include "string.h"
#include "tree.h"
#include "draw.h"

void run_akinator()
{
        struct tree *tree = tree_ctor();
        tree_read(tree);
        tree_draw(tree);
        tree_write(tree);
        tree_dtor(tree);
}
