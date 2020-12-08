#ifndef DICO_H_INCLUDED
#define DICO_H_INCLUDED
#include "Stack.h"

///------------------------------------------SDD spéciale aux branches

typedef struct LSC
{
    int numero;
    char lettre;
    struct LSC* succ;
}LSC;

typedef LSC* List_lettre;
List_lettre create_LSC(int n);
void modif(LSC *l);

void conversion_bin (char* path); ///A
void nb_char(); ///B

LSC* reverse_LSC (LSC *l, noeudModif* noeudCurseur);
void add_fichier(LSC *l, noeudModif* noeudCurseur);

void afficher_LSC(LSC *l, noeudModif* noeudCurseur);
void Afficher(noeudModif* noeudCurseur, stack* ps,int n,stack* refps,LSC *l,int* pi);

int profondeur_tree(noeudModif* noeudCurseur);
int nb_feuille(noeudModif* noeudCurseur);




#endif // DICO_H_INCLUDED
