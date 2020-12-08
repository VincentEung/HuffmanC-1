#ifndef HUFFMANTREE_H_INCLUDED
#define HUFFMANTREE_H_INCLUDED

typedef struct maillon
{
    int poids;
    char lettre;
    struct maillon* next;

}maillon;


typedef struct noeudModif
{
    int poids;
    char lettre;
    struct noeudModif* next;
    struct noeudModif* sag;
    struct noeudModif* sad;

}noeudModif;


void affichageListe(maillon *maillonCurseur);
void affichageListeNoeud(noeudModif *noeudCurseur);
maillon* creationMaillonOccurrence(maillon *maillonListe,maillon *maillonCurseur);
noeudModif* convertisseur(maillon *maillonCurseur,noeudModif* noeudCurseur,noeudModif* noeudListe);
noeudModif* list_remove(noeudModif *noeudListe,noeudModif *noeudCurseur);
noeudModif* indice_min(noeudModif* noeudCurseur,noeudModif* noeudListe);
noeudModif* creationArbreHuffman(noeudModif *noeudCurseur, noeudModif *noeudListe);
noeudModif* fusion(noeudModif* temp1, noeudModif* temp2,noeudModif* tempFinal);

///fonction supplémenataire
void print_tree(noeudModif* noeudCurseur);
void viderBuffer();




#endif // HUFFMANTREE_H_INCLUDED
