#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TABLEAU 95                                                                                                               
#define PREMIER_CARACTERE 32    

int alphabet[TAILLE_TABLEAU];

typedef struct caractere_occurence{
    char caractere;
    int occurence;
}caractere_occurence;

/* 
1 - La fonction qui compte le nombre d'occurence d'un mot
    :param -> un mot
    :return -> un tableau (de type enregistrement) qui contient chaque caractere contenus dans le mot avec son nombre d'occurence chacun
*/

void compterOccurenceMot(char *cheminVersFichier){
    char caractereLu;
    FILE *fichierACompressser;
    if ((fichierACompressser = fopen(cheminVersFichier,"r")) == NULL)
    {
      fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",cheminVersFichier);
      exit(1);
    }
    while ((caractereLu = fgetc(fichierACompressser)) != EOF)
    {
        int indice = caractereLu - PREMIER_CARACTERE; //indice represente l'indice du caractere lu dans le tableau
        if(indice >= 0 && indice < TAILLE_TABLEAU)
            alphabet[indice]++;
    }
    fclose(fichierACompressser);
    
    for(int i = 0; i < TAILLE_TABLEAU; i++)
        if(alphabet[i] != 0)
            printf("car == %c , nbocc == %d\n", i + PREMIER_CARACTERE, alphabet[i]);
   
}


int main(int nbArgument, char *parametres[]){
    if(nbArgument != 2)
    {
        printf("Usage: %s fichier\n\n", parametres[0]);
        exit(1);
    }

    compterOccurenceMot(parametres[1]);
    
    return 0;
}