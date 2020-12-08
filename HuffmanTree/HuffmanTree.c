#include <stdio.h>
#include <stdlib.h>
#include "HuffmanTree.h"


void affichageListe(maillon *maillonCurseur)
{
    if(maillonCurseur==NULL)
        return;
    printf("%c",maillonCurseur->lettre);
    printf("%d\n",maillonCurseur->poids);
    affichageListe(maillonCurseur->next);
}

void affichageListeNoeud(noeudModif *noeudCurseur)
{
    while(noeudCurseur!=NULL)
    {
        printf("%c",noeudCurseur->lettre);
        printf("%d\n",noeudCurseur->poids);
        noeudCurseur=noeudCurseur->next;
    }

}

maillon* creationMaillonOccurrence(maillon *maillonListe,maillon *maillonCurseur)
{
    FILE* texte=NULL;
    texte=fopen("texte.txt","r");
    if (texte==NULL)
    {
        printf("erreur\n");
    }
    if (texte!=NULL)
    {


        char caractere;
        caractere=fgetc(texte);///on crée le 1er maillon qui est a la base de la liste, qui n'a besoin d'aucune verification
        maillonCurseur->lettre=caractere;
        maillonCurseur->poids=1;
        maillonCurseur->next=NULL;
        maillonListe->next=maillonCurseur;
        int jamaisTraite;
        while(caractere!=EOF)///boucle lecture fichier
        {
            caractere=fgetc(texte);
            jamaisTraite=1;
            maillonCurseur=maillonListe->next;///on init le curseur au debut de la liste +1
            int possibiliteAvancement=1;
            while(possibiliteAvancement==1)
            {
                if(caractere==maillonCurseur->lettre)
                {
                    maillonCurseur->poids++;
                    jamaisTraite=0;
                }
                if(maillonCurseur->next==NULL)
                    possibiliteAvancement=0;
                if(maillonCurseur->next!=NULL)
                    maillonCurseur=maillonCurseur->next;
            }
            if (jamaisTraite==1 && caractere!=EOF)
            {
                maillon *newMaillon;          ///on crée un new maillon
                newMaillon=malloc(sizeof(maillon));

                newMaillon->poids=1;
                newMaillon->lettre=caractere;
                newMaillon->next=NULL;
                maillonCurseur->next=newMaillon;
            }
        }
        maillonCurseur=maillonListe->next;
    }


    return maillonListe;
}

noeudModif* convertisseur(maillon *maillonCurseur,noeudModif* noeudCurseur,noeudModif* noeudListe)
{
    noeudListe->next=noeudCurseur;///pour transferer une liste chainée a une liste de noeud, on va considérer que sad sera suivant


    int possibiliteAvancement=1;
    while(possibiliteAvancement==1)
            {

                noeudCurseur->lettre=maillonCurseur->lettre;
                noeudCurseur->poids=maillonCurseur->poids;

                if(maillonCurseur->next==NULL)
                    possibiliteAvancement=0;
                if(maillonCurseur->next!=NULL)
                {

                    noeudModif *newNoeud;          ///on crée un new noeud tant qu'il y aura un maillon a faire correspondre
                    newNoeud=malloc(sizeof(noeudModif));
                    newNoeud->next=NULL;
                    newNoeud->sad=NULL;
                    newNoeud->sag=NULL;
                    noeudCurseur->next=newNoeud;

                    noeudCurseur=noeudCurseur->next;
                    maillonCurseur=maillonCurseur->next;

                }

            }
            noeudCurseur=noeudListe->next;///on reset noeud curseur
    return noeudListe;
}

noeudModif* indice_min(noeudModif* noeudCurseur,noeudModif* noeudListe)
{
    noeudCurseur=noeudListe->next;
    int occurenceMin;
    while(noeudCurseur!=NULL)
    {

        if(noeudCurseur==noeudListe->next)
            occurenceMin=noeudCurseur->poids;

        if(noeudCurseur->poids<=occurenceMin)
            occurenceMin=noeudCurseur->poids;///on a maintenant l'occurence minimum possible


        noeudCurseur=noeudCurseur->next;

    }
    noeudCurseur=noeudListe->next;///on réinit pour parcourir une deuxieme fois la boucle et pour s'arreter la ou on voit l'occurence

    while(noeudCurseur->poids!=occurenceMin)
        noeudCurseur=noeudCurseur->next;

    return noeudCurseur;

}

noeudModif* list_remove(noeudModif *noeudListe,noeudModif *noeudCurseur)///il nous faut retrouver ou faire le branchement juste avant la ou c supprimé pour pas couper la liste
{
    int lettreSuppr;
    lettreSuppr=noeudCurseur->lettre;///on va faire les comparatifs avec cette lettre
    noeudCurseur=noeudListe->next;///on réinit le curseur
    int pasPremiereLettre=1;
    noeudModif **pointeurNoeudSuppr;
    if (noeudCurseur->lettre==lettreSuppr)///si on rentre icic c'est que c'est la 1ere lettre qui doit etre changé on a donc pas les memes branchements a faire
    {
        pasPremiereLettre=0;
        pointeurNoeudSuppr=&noeudCurseur;///ce pointeur permet de pas perdre ce que l'on veut supprimer
        noeudListe->next=noeudListe->next->next;

    }
    if(pasPremiereLettre==1)
    {
        while(lettreSuppr!=noeudCurseur->next->lettre)///on arrive ainsi au noeud avant la suppression et on peut changer les branchements
        {
            noeudCurseur=noeudCurseur->next;
        }
        pointeurNoeudSuppr=&noeudCurseur->next;///ce pointeur permet de pas perdre ce que l'on veut supprimer
        noeudCurseur->next=noeudCurseur->next->next;///on passe au dessus du prochain maillon
    }

    free(pointeurNoeudSuppr);
    pointeurNoeudSuppr=NULL;


    noeudCurseur=noeudListe->next;
    return noeudListe;
}

noeudModif* fusion(noeudModif* temp1, noeudModif* temp2,noeudModif* tempFinal)
{

    tempFinal->lettre = '$';///sert juste a bien identifier les noeud pour nous travailler
    tempFinal->poids = temp1->poids + temp2->poids;
    tempFinal->sad = temp1;
    tempFinal->sag = temp2;

    return tempFinal;

}

noeudModif* creationArbreHuffman(noeudModif *noeudCurseur, noeudModif *noeudListe)
{
    noeudModif *temp1;///on créé les 2 maillons temporaires
    temp1=malloc(sizeof(noeudModif));

    noeudModif *temp2;
    temp2=malloc(sizeof(noeudModif));
/*
    noeudModif *tempFinal;///et le temporaire final
    tempFinal=malloc(sizeof(noeudModif));
    tempFinal->next=NULL;
    tempFinal->sad=NULL;
    tempFinal->sag=NULL;
*/

    while(noeudListe->next->next!=NULL)///tant qu'il ne reste pas plus qu'un noeud dans la liste de noeud, qui correspondra à  l'arbre
    {
        affichageListeNoeud(noeudCurseur);
        printf("\n\n");

        noeudCurseur=noeudListe->next;
        noeudCurseur=indice_min(noeudCurseur,noeudListe);
        temp1=noeudCurseur;
        noeudListe=list_remove(noeudListe,noeudCurseur);

        noeudCurseur=indice_min(noeudCurseur,noeudListe);
        temp2=noeudCurseur;
        noeudListe=list_remove(noeudListe,noeudCurseur);

        noeudCurseur=noeudListe->next;
        while (noeudCurseur && noeudCurseur->next)///on va a la fin de la liste...
            noeudCurseur=noeudCurseur->next;


        noeudModif *tempFinal;///...pour rajouter le temp final
        tempFinal=malloc(sizeof(noeudModif));
        tempFinal->next=NULL;
        tempFinal->sad=NULL;
        tempFinal->sag=NULL;

        if (noeudCurseur)
            noeudCurseur->next=tempFinal;

        if (!noeudCurseur)///a la derniere opération il n'y a plus de noeud curseur du coup on rajoute le temp directement a noeud liste
            noeudListe->next=tempFinal;

        tempFinal=fusion(temp1,temp2,tempFinal);///on modifie le tempFinal

        noeudCurseur=noeudListe->next;

    }

    return noeudListe;
}



///fonction supplémentaire

/// -------------------------------------------------------------------------- fonction annexe
int profondeur_tree(noeudModif *noeudCurseur)
{
    if (noeudCurseur==NULL) return 0;
    else{

        int cote_gauche;
        int cote_droite;
        cote_gauche = profondeur_tree(noeudCurseur->sag);
        cote_droite = profondeur_tree(noeudCurseur->sad);
        if(cote_gauche > cote_droite){
            return cote_gauche + 1;
        }
        else{
            return cote_droite + 1;
        }
    }
}

int nb_feuille(noeudModif *noeudCurseur){
    if (noeudCurseur==NULL) return 0;
    else {
            if ((noeudCurseur->sad==NULL)&&(noeudCurseur->sag==NULL)){
                return 1;
            }
            return (nb_feuille(noeudCurseur->sad)+nb_feuille(noeudCurseur->sag));
        }
}

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void print_tree(noeudModif* noeudCurseur)
{
    if(noeudCurseur != NULL){

        printf("%d-%c\n", noeudCurseur->poids,noeudCurseur->lettre);
        print_tree(noeudCurseur->sag);
        print_tree(noeudCurseur->sad);
    }
}




