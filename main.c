#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.h"
#include "Dico.h"
#include "Stack.h"
#include "D_Compress.h"

int main()
{
    conversion_bin ("start.txt");///ouverture fichier "start.txt" et codage en code ASCI dans le fichier "result.txt" A
    nb_char();///affiche le nombre de caractère du fichier "result.txt" B

    maillon *maillonListe;          ///on crée le 1er maillon
    maillonListe=malloc(sizeof(maillon));

    maillon *maillonCurseur;    ///on crée le mailon curseur, qui va nous permettre de parcourir la liste chainé et vérifier si il y a des occurences
    maillonCurseur=malloc(sizeof(maillon));

    maillonListe=creationMaillonOccurrence(maillonListe,maillonCurseur);/// ALGO C PRINCIPALEMENT
    maillonCurseur=maillonListe->next;

    affichageListe(maillonCurseur);
    maillonCurseur=maillonListe->next;

    printf("\n\n");

    noeudModif *noeudListe;///on créer les 2 maillons mais dans le main cette fois-ci
    noeudListe=malloc(sizeof(noeudModif));

    noeudModif *noeudCurseur;
    noeudCurseur=malloc(sizeof(noeudModif));
    noeudCurseur->next=NULL;

    noeudListe=convertisseur(maillonCurseur,noeudCurseur,noeudListe);///on recup le pointeur a la fin de la conversion
    free(maillonCurseur);
    maillonCurseur=NULL;
    free(maillonListe);
    maillonListe=NULL;

    noeudCurseur=noeudListe->next;///on se sert du pointeur récup avant pour définir notre curseur

    noeudListe=creationArbreHuffman(noeudCurseur,noeudListe);/// ALGO D PRINCIPALEMENT
    noeudCurseur=noeudListe->next;

    affichageListeNoeud(noeudCurseur);///affiche la liste de noeud (ici il n'y en a plus qu'un aka l'arbre)


    print_tree(noeudCurseur);
    printf("ok\n");

    printf("ok\n");
    stack *ps = newEmptyStack();
    stack *refps = newEmptyStack();
    printf("ok2\n");
    int resultat;
    resultat=profondeur_tree(noeudCurseur);
    printf("ok3\n");
    printf("resultat: %d\n",resultat);
    List_lettre l = create_LSC(profondeur_tree(noeudCurseur)*nb_feuille(noeudCurseur)); /// la taille de notre LSC correspond au nombre de feuille x profondeur de l'arbre
    modif(l); /// modif(l) permet de remplir la LSC de 2 car on sait que notre LSC sera composé de 0 ou de 1
    int i=0;
    int *pi=&i;
    int n=0;
    ///-------------------
    /// t  : l'arbre binaire
    /// ps : pile principale qui va contenir le chemin dans un moment précis
    /// n  : une varibale temporaire pour vider les piles ou pour se déplacer sur la LSC
    /// l  : la LSC qui va contenir le chemin de chaque lettre
    /// pi : un pointeur sur i qui va permettre à chaque moment de l'execution de la fonction de savoir où on est sur la LSC
    ///-------------------
    printf("ok3\n");
    Afficher(noeudCurseur,ps,n,refps,l,pi);

    printf("LSC dans le main :");
    afficher_LSC(l, noeudCurseur);

    l = reverse_LSC(l, noeudCurseur);
    printf("\nLSC reverse      :");
    afficher_LSC(l, noeudCurseur);

    add_fichier(l, noeudCurseur);

    creationFichierCodage();

    printf("WTF sa march pa\n");
    decodage();

    return 0;
}
