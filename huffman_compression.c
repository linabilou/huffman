#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TABLEAU 95                                                                                                               
#define PREMIER_CARACTERE 32    

typedef struct caractereOccurence{
    char caractere;
    int occurence;
}caractereOccurence;

/*Strucuture pour un noeud dans un arbre binaire*/
typedef struct noeud{
    caractereOccurence valeur; //la valeur ou l'info contenu dans le noeud est le caractere et son nombre d'occurence
    struct noeud *filsGauche;
    struct noeud *filsDroit;
}noeud;

/*
- Le tableau alphabet contient les caracteres ascii 32-126 d'ou la taille 95 (127-32)
- Il contient les caracteres ascii possibles et leur donne d'occurence
*/
caractereOccurence alphabet[TAILLE_TABLEAU]; 

/*
La fonction initialisation permet d'initialiser le tableau 
- Lors de l'initialisation, les caracteres de chaque case correspondent aux indices du tableau et les occurences sont mis a 0 pour tout le monde
Tout ceci pour nous faciliter la manipulation. 
*/
void initialisationTableau(){
    for(int indice = 0; indice < TAILLE_TABLEAU; indice++)
    {
        alphabet[indice].caractere = indice;
        alphabet[indice].occurence = 0;
    }
}

/*
La fonction qui compare deux éléments > va etre utilise dans qsort qui est une fonction deja definie en C et a une structure bien definie
- Elle prend en parametre deux pointeurs sur des constantes de n'importe quel type d'ou le void; et renvoie un entier
- Dans notre cas on fait en sorte qu'elle prenne des pointeurs sur le type qu'on a defini
*/
int fonctionDeComparaison (const void *parametre1, const void *parametre2){

    int nombre1 = ((caractereOccurence *)parametre1)->occurence;
    int nombre2 = ((caractereOccurence *)parametre2)->occurence;

    return (nombre1 - nombre2);
}

/* 
1 - La fonction qui compte le nombre d'occurence d'un mot
    :param -> le chemin vers le fichier (le fichier a compresser)
    :return -> un tableau (de type enregistrement) qui contient chaque caractere contenus dans le fichier avec son nombre d'occurence chacun
*/
void compterOccurenceMot(char *cheminVersFichier){
    char caractereLu;
    FILE *fichierACompressser;
    if ((fichierACompressser = fopen(cheminVersFichier,"r")) == NULL){
      fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",cheminVersFichier);
      exit(1);
    }
    while ((caractereLu = fgetc(fichierACompressser)) != EOF){
        int indice = caractereLu - PREMIER_CARACTERE; //indice represente l'indice du caractere lu dans le tableau
        if(indice >= 0 && indice < TAILLE_TABLEAU)
            alphabet[indice].occurence++;
            
    }
    fclose(fichierACompressser);

    // La fonction de la bibliothèque C void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) trie un tableau.
    /*Elle va donc nous permettre de trier notre tableau de caractere dans l'ordre croissant du nombre d'occurence*/
    qsort(alphabet, TAILLE_TABLEAU, sizeof(caractereOccurence), fonctionDeComparaison);
    
    for(int indice = 0; indice < TAILLE_TABLEAU; indice++)
        if(alphabet[indice].occurence != 0)
            printf("caractere == %c , nboccurence == %d\n", alphabet[indice].caractere + PREMIER_CARACTERE, alphabet[indice].occurence);
}

/*Fonction pour creer un nouveau noeud dans un arbre binaire*/
noeud *creerNoeud(caractereOccurence valeur){
    noeud *nouveauNoeud;
    nouveauNoeud->valeur = valeur;
    nouveauNoeud->filsGauche = NULL;
    nouveauNoeud->filsDroit = NULL;

    return nouveauNoeud;    
}

/*Fonction pour inserer un noeud dans un arbre*/
void insererNoeud(){

}

int main(int nbArgument, char *parametres[]){
    if(nbArgument != 2){
        printf("Usage: %s fichier\n\n", parametres[0]);
        exit(1);
    }

    initialisationTableau();
    compterOccurenceMot(parametres[1]);
    
    return 0;
}