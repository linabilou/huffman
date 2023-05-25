#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TABLEAU 95                                                                                                               
#define PREMIER_CARACTERE 32    

#define FICHIEROCCURENCE "caractereOccurence.txt"

typedef struct caractereOccurence{
    char caractere;
    int occurence;
}caractereOccurence;

/*
- Le tableau alphabet contient les caracteres ascii 32-126 d'ou la taille 95 (127-32)
- Il contient les caracteres ascii possibles et leur donne d'occurence
*/
caractereOccurence alphabet[TAILLE_TABLEAU]; 


/*
- Le tableau noeudParent contient les racines obtenus a partir de la somme des occurences selon le principe de huffman
*/
caractereOccurence noeudParent[TAILLE_TABLEAU]; 

/*
cette fonction permet d'initialiser le tableau de l'alphabet
- Lors de l'initialisation, les caracteres de chaque case correspondent aux indices du tableau et les occurences sont mis a 0 pour tout le monde
Tout ceci pour nous faciliter la manipulation. 
*/
void initialisationTableauAlphabet(){
    for(int indice = 0; indice < TAILLE_TABLEAU; indice++)
    {
        alphabet[indice].caractere = indice;
        alphabet[indice].occurence = 0;
    }
}


/*
Cette fonction  compare deux éléments > Elle va etre utilise dans qsort qui est une fonction deja definie en C et a une structure bien definie
- Elle prend en parametre deux pointeurs sur des constantes de n'importe quel type d'ou le void; et renvoie un entier
- Dans notre cas on fait en sorte qu'elle prenne des pointeurs sur le type qu'on a defini
*/
int fonctionDeComparaison (const void *parametre1, const void *parametre2){

    int nombre1 = ((caractereOccurence *)parametre1)->occurence;
    int nombre2 = ((caractereOccurence *)parametre2)->occurence;

    return (nombre1 - nombre2);
}

/* 
1 & 2 - Cette fonction  compte le nombre d'occurence des caracteres de notre fichier
    :param -> le chemin vers le fichier (le fichier a compresser)
    :return -> un tableau (de type enregistrement) qui contient chaque caractere contenus dans le fichier avec son nombre d'occurence chacun
*/
void compterOccurenceMot(char *cheminVersFichier){
    char caractereLu;
    FILE *fichierACompressser, *fichierDesOccurences;
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


/*
 3- 7 Fonction pour creer l'arbre

    :param -> un tableau (dans notre cas ce sera le tableau deja trie des caracteres et leur occurence)
    :return -> un autre tableau qui contient les racines de notre arbre - suivant le principe de huffman 
*/

void construireArbre(){
    int i = 0, racine = 0; 
    while(i < TAILLE_TABLEAU && alphabet[i].occurence == 0)
        i++;
    
    if(TAILLE_TABLEAU - i <= 1 )
       racine = i;
    else{
        noeudParent[racine].occurence = alphabet[i].occurence + alphabet[i + 1].occurence;
        racine++;
        for(int k=i+2; k<TAILLE_TABLEAU; k++){
            noeudParent[racine].occurence = alphabet[k].occurence + noeudParent[racine -1].occurence;
            racine++;
        }
    }
    
    for(int indice = 0; indice < TAILLE_TABLEAU; indice++)
        if(noeudParent[indice].occurence != 0)
            printf(" racine == %d\n", noeudParent[indice].occurence);
}

int main(int nbArgument, char *parametres[]){
    if(nbArgument != 2){
        printf("Usage: %s fichier\n\n", parametres[0]);
        exit(1);
    }

    initialisationTableauAlphabet();
    compterOccurenceMot(parametres[1]);

    construireArbre();
    
    return 0;
}