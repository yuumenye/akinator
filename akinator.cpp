#include "akinator.h"
#include "tree.h"

void run()
{
        struct tree *tree = tree_ctor();
        tree_dtor(tree);
}
