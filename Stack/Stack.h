#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

/// -------------------------------------------------------------------------- pile & file
typedef struct list_node
{
    int n;//champ d'info
    struct list_node *succ;
}list_node;
typedef list_node* List_tree;

/** structure de pile réalisée avec une LSC dont la tête est le sommet**/
typedef struct lStack
{
    List_tree top;
    int depth;
}stack;


stack *newEmptyStack();
int isEmptyStack(stack ps);
void sPush(int n, stack *ps); //ajout dans la pile
int sPop(stack *ps); //retrait de la pile


#endif // STACK_H_INCLUDED
