#include <stdio.h>
#include <string.h>

#define TAILLE_TABLEAU 95                                                                                                               
#define PREMIER_CARACTERE 32    

int ALPHABET[TAILLE_TABLEAU];

typedef struct caractere_occurence{
    char caractere;
    int occurence;
}caractere_occurence;

/* 
1 - La fonction qui compte le nombre d'occurence d'un mot
    :param -> un mot
    :return -> un tableau (de type enregistrement) qui contient chaque caractere contenus dans le mot avec son nombre d'occurence chacun
*/

void compterOccurenceMot(){
    char *chaine = "maman";
    for(int i=0; i < 5; i++)
    {
        char car = chaine[i];
        ALPHABET[car - PREMIER_CARACTERE]++;
    }
    
    for(int i = 0; i < TAILLE_TABLEAU; i++)
        if(ALPHABET[i] != 0)
            printf("car == %c , nbocc == %d\n", i + PREMIER_CARACTERE, ALPHABET[i]);
   
}




int main(){



    //code test pour compter le nombre d'occurence d'un mot 

    compterOccurenceMot();
    
    return 0;
}