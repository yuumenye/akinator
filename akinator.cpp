#include "akinator.h"
#include "string.h"
#include "tree.h"
#include "draw.h"

void run()
{
        struct tree *tree = tree_ctor();
        tree_read(tree);
        tree_draw(tree);
        tree_dtor(tree);
}
