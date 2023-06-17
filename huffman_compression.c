#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_TABLEAU 128  

typedef struct caractereOccurence{
    char caractere;
    int occurence;
    char code[TAILLE_TABLEAU];
}caractereOccurence;

/* Le tableau alphabet contient les caracteres ascii 32-126 d'ou la taille 95 (127-32) - les caracteres ascii possibles et leur donne d'occurence */
caractereOccurence alphabet[TAILLE_TABLEAU]; 

/* Le tableau noeudParent contient les racines obtenus a partir de la somme des occurences selon le principe de huffman */
int noeudParent[TAILLE_TABLEAU]; 

int nbTotalCaractere = 0; //nombre total de caractere contenu dans le fichier a compresser

int nbCaractereUnique = 0; //nombre total de caractere qui forment les mots du fichier a compresser

char *texte;

/*Initialisation de notre alphabet de caractere */
void initialisationTableauAlphabet(){
    for(int indice = 0; indice < TAILLE_TABLEAU; indice++)
    {
        alphabet[indice].caractere = indice;
        alphabet[indice].occurence = 0;
        strcpy(alphabet[indice].code, "");
    }
}

/* Cette fonction  compare deux éléments */
int fonctionDeComparaison (const void *parametre1, const void *parametre2){

    int nombre1 = ((caractereOccurence *)parametre1)->occurence;
    int nombre2 = ((caractereOccurence *)parametre2)->occurence;

    return (nombre1 - nombre2);
}

/*Procedure pour compter le nombre d'occurence et trie le tableau */
void compterOccurence(char *cheminVersFichier){
	char caractereLu;
    	FILE *fichierACompressser;
    	if ((fichierACompressser = fopen(cheminVersFichier,"r")) == NULL){
      		fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",cheminVersFichier);
      		exit(1);
    	}
    	while ((caractereLu = fgetc(fichierACompressser)) != EOF){
		{
			if(alphabet[caractereLu].occurence == 0)
				nbCaractereUnique++;

            		alphabet[caractereLu].occurence++;         
			nbTotalCaractere++;
		}
    	}
    	fclose(fichierACompressser);
    	
    	qsort(alphabet, TAILLE_TABLEAU, sizeof(caractereOccurence), fonctionDeComparaison);
}


/*Construction de l'arbre de compression de huffman */
void ArbreDeCompression(){
    /*
        - feuille est l'indice pour parcourir le tableau alphabet comprenant tous les noeuds enfants (caractere de la chaine)
        - racine est l'indice pour parcourir le tableau des racines de l'arbre   
        - k = feuille + 2  
    */
   int feuille = 0, racine = 0, k; 

    	printf("\nDebut de la construction de l'arbre\n\n");
    	printf("             .........             \n\n");
    	while(feuille < TAILLE_TABLEAU && alphabet[feuille].occurence == 0)
        	feuille++;

    	if(TAILLE_TABLEAU - feuille <= 1 )
       		racine = feuille;
    	else
	{
        	noeudParent[racine] = alphabet[feuille].occurence + alphabet[feuille + 1].occurence;
        	racine++;
        	for(k = feuille+2; k < TAILLE_TABLEAU; k++)
		{
            		noeudParent[racine] = alphabet[k].occurence + noeudParent[racine -1];
            		racine++;
        	}
    	}
    	printf("\nFin de la construction de l'arbre\n\n");

    	racine--;
    	feuille = --k;
    	printf("\nDebut de construction des codes\n\n");
    	char chaine[TAILLE_TABLEAU] = ""; //on se met au niveau de la racine pour commencer le parcours
    	while(racine >= 1)
	{
        	strcpy(alphabet[feuille].code, chaine);
        	if(noeudParent[racine - 1] > alphabet[feuille].occurence)
		{
            		strcat(alphabet[feuille].code, "0");
            		strcat(chaine, "1"); //chaine = chaine + 1
        	}
		else
		{
            		strcat(alphabet[feuille].code, "1");
            		strcat(chaine, "0");
        	}
        	feuille--;
        	racine--; 
    	}

    	strcat(strcpy(alphabet[feuille].code, chaine), "1");
    	strcat(strcpy(alphabet[feuille - 1].code, chaine), "0");

    	for(int indice = 0; indice < TAILLE_TABLEAU; indice++)
       		if(alphabet[indice].occurence != 0)
           		printf("id == %d, caractere == %c , nboccurence == %d, code == %s\n", indice, alphabet[indice].caractere, alphabet[indice].occurence, alphabet[indice].code);

    	printf("\nFin de construction des codes\n\n");
}


/* Ecrire les frequences dans un fichier */
void enregistrerFrequence()
{
	FILE *fichierArbre = fopen("cleDecompression", "w");
	fprintf(fichierArbre, "%d\n", nbCaractereUnique);
	for(int indice = 0; indice < TAILLE_TABLEAU; indice++)
	{
		if(alphabet[indice].occurence != 0)
		{
			char caractere = alphabet[indice].caractere;
			int occurence = alphabet[indice].occurence;
		}
	}
	fclose(fichierArbre);
}

/* Sortir le fichier compresse */
void enregistrerFichierCompresser(char *cheminVersFichier)
{
	char caractereLu;
    	FILE *fichierACompressser;
    	if ((fichierACompressser = fopen(cheminVersFichier,"r")) == NULL){
      		fprintf(stderr, "\nErreur: Impossible de lire le fichier %s\n",cheminVersFichier);
 	     	exit(1);
    	}
	texte = malloc(sizeof(char) * nbTotalCaractere);
	unsigned int car = 0;
    	while ((caractereLu = fgetc(fichierACompressser)) != EOF)
		texte[car++] = caractereLu;

    	fclose(fichierACompressser);


	FILE *fichierCompresse = fopen("fichierCompresse", "w");


	for(car = 0; car < nbTotalCaractere; car++)
	{
		int indice = texte[car];
		int id = TAILLE_TABLEAU;
		while(alphabet[id].caractere != indice)
			id--;
		fprintf(fichierCompresse, "%s", alphabet[id].code);
	}

	

	fclose(fichierCompresse);
	free(texte);
	printf("\n		Compression terminee avec SUCESS		\n");
	printf("\n\nLes fichier suivant ont ete genere:\n");
	printf("		1- fichierCompresse : contient le texte compresse\n");
	printf("		2- cleDecompression : la cle qui va permettre de decompresser\n\n");
}

int main(int nbArgument, char *parametres[]){
    if(nbArgument != 2){
        printf("Usage: %s fichier\n\n", parametres[0]);
        exit(1);
    }

    initialisationTableauAlphabet();
    compterOccurence(parametres[1]);
    ArbreDeCompression();   
    enregistrerFrequence();
	enregistrerFichierCompresser(parametres[1]);

    return 0;
}