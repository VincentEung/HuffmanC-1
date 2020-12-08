#include <stdio.h>
#include <stdlib.h>
#include "../Stack/Stack.h"


stack *newEmptyStack()
{
    stack *ps = malloc(sizeof(stack));
    ps->top = NULL;
    ps->depth = 0;
    return ps;
}
int isEmptyStack(stack ps)
{
    return(ps.depth==0);
}
void sPush(int n,stack *ps)
{
    List_tree top = new_singleton_list(n); //on cast le void en int
    top->succ = ps->top;
    ps->top = top;
    ps->depth++;
}
int sPop (stack* ps)
{
    int n = ps->top->n;
    List_tree kill = malloc(sizeof(List_tree));
    kill = ps->top;
    ps->top = kill->succ;
    ps->depth--;
    free(kill);
    return n;
}

