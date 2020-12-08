#include <stdio.h>
#include <stdlib.h>
#include "../HuffmanTree/HuffmanTree.h"
#include "../Dico/Dico.h"



void conversion_bin (char* path){///A
    FILE* texte = NULL;
    FILE* result = NULL;
    int tab[10];
    int lettre = 0,i = 0;
    texte = fopen(path,"r");
    result = fopen("result.txt","w+");
    lettre = fgetc(texte); // On lit le caractère
    do
    {
        for( i=0; lettre > 0; i++)
        {
            tab[i] = lettre % 2;
            lettre = lettre / 2;
        }
        while (i<=7)
        {
            tab[i]= 0;
            i++;
        }
        for( i = i-1; i >= 0; i--)
            fprintf(result,"%d",tab[i]);


        lettre = fgetc(texte); // On lit le caractère
    } while (lettre != EOF);
    fclose(texte);
    fclose(result);

}

void nb_char(){///B
    FILE* texte = NULL;
    texte = fopen("result.txt","r");

    int lettre = 0, compteur = -1; // Le compteur est à -1 car le dernier caractère EOF est compté à la fin
    do
    {
        lettre = fgetc(texte); // On lit le caractère
        compteur++;
    } while (lettre != EOF);

    fclose(texte);
    printf("nbr chara : %d\n",compteur);
}

void Afficher(noeudModif* noeudCurseur, stack* ps, int n, stack* refps,LSC *l,int* pi){ /// il faut utiliser une pile : dès qu'on monte on ajoute dans la pile et inversement on dépile.

    if (noeudCurseur==NULL);
    else {  /// parcours en préfixe car on veut connaitre le chemin du maillon donc les parents d'abords
        if (noeudCurseur->sag!=NULL){
            sPush(1,ps);/// dès qu'on se déplace à gauche on traduit ça par 1 en binaire
            Afficher(noeudCurseur->sag,ps,n,refps,l,pi);
            sPop(ps);///dès qu'on sort de la fenêtre précédente cela signifit que nous avons "monté" dans l'arbre donc on enlève le chemin
        }
        if (noeudCurseur->sad!=NULL){
            sPush(0,ps); /// dès qu'on se déplace à droite on traduit ça par 0 en binaire
            Afficher(noeudCurseur->sad,ps,n,refps,l,pi);
            sPop(ps);///dès qu'on sort de la fenêtre précédente cela signifit que nous avons "monté" dans l'arbre donc on enlève le chemin
        }
        if ((noeudCurseur->sad==NULL)&&(noeudCurseur->sag==NULL)){
            n=0;
            while (n<*pi){///on utilise un pointeur sur pi pour savoir où il faut commencer à ecrire
                l=l->succ;
                n++;
            }
            l->lettre=noeudCurseur->lettre; /// dans notre LSC la lettre apparait avant  le chemin
            l->numero=0;
            l=l->succ;
            (*pi)++;
            while (isEmptyStack(*ps)==0){ /// on utilise deux pile pour pouvoir extraire les données de la pile ps avec l'aide de la pile refps
                n = sPop(ps); /// donc ici on vide la pile ps
                sPush(n,refps); /// ici on remplie refps
                l->numero=n; /// on extrait les données pour les mettres dans notre LSC
                l=l->succ;
                (*pi)++;
            }
            while (isEmptyStack(*refps)==0){
                n = sPop(refps); /// ici on vide la pile refps
                sPush(n,ps); /// ici on reremplie ps
            }
        }
    }
}

List_tree new_singleton_list(int n)
{
    List_tree l = (List_tree) malloc(sizeof(list_node));
    l->n = n;
    l->succ = NULL;
    return l;
}

List_lettre create_LSC(int n)
{
    printf("hey\n");
	if (!n) return NULL;
	List_lettre l = malloc(sizeof(LSC));
	List_lettre q = l;
	int i = 1;
	while (i < n) {
		i++;
		q->lettre = NULL;
		q->numero= NULL;
		q = q->succ = malloc(sizeof(LSC));
	}
	q->succ = NULL;
	return l;
}

void afficher_LSC(LSC *l,noeudModif *noeudCurseur)
{
    int nbr_tour = nb_feuille(noeudCurseur);
	while (l != NULL) {
        if (((int)l->lettre==0)&&(l->numero<2)) printf("(%d)->",l->numero);
        else if (nbr_tour>0)
        {
            printf("[%c]->",l->lettre);
            nbr_tour--;
        }
        l=l->succ;
	}
	printf("x\n");
}

void modif(LSC *l){
    if (l==NULL);
    else{
        l->numero=2;
        modif(l->succ);
    }
}

LSC* reverse_LSC (LSC *l, noeudModif* noeudCurseur)
{
    int n;
    List_lettre refl = create_LSC(profondeur_tree(noeudCurseur)*nb_feuille(noeudCurseur));
    List_lettre pointeur = refl;
    stack *pile = newEmptyStack();
    int nbr_tour = nb_feuille(noeudCurseur);
	while (l != NULL) {
        if (((int)l->lettre==0)&&(l->numero<2)) sPush(l->numero, pile);
        else if (nbr_tour>0)
        {
            sPush(l->lettre,pile);
            nbr_tour--;
        }
		l = l->succ;
	}

	nbr_tour = nb_feuille(noeudCurseur);
	while (isEmptyStack(*pile)==0){
        n=sPop(pile);
        if ((n==1)||(n==0)) refl->numero=n;
        else if (nbr_tour>0)
            {
                refl->lettre=(char) n;
                nbr_tour--;
            }
        refl=refl->succ;
	}
    return pointeur;
}

void add_fichier(LSC *l, noeudModif* noeudCurseur){
    FILE* dico = NULL;
    dico = fopen("dico.txt","w+");
    List_lettre refl = create_LSC(profondeur_tree(noeudCurseur)*nb_feuille(noeudCurseur));
    int nbr_tour_char = nb_feuille(noeudCurseur);

    while (l!=NULL){
        refl=l;
        while (((int)refl->lettre==0)&&(nbr_tour_char>0))
        {
            refl=refl->succ;
        }
        if (nbr_tour_char>0) fprintf(dico,"%c\n",refl->lettre);
        while (((int)l->lettre==0)&&(nbr_tour_char>0))
        {
            fprintf(dico,"%d",l->numero);
            l=l->succ;
        }
        if (nbr_tour_char>0) fprintf(dico,"\n");
        l=l->succ;
        nbr_tour_char--;
    }
    fclose(dico);
}
