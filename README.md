# Code de Compression et de decompression de Huffman : Version 1.0

# Reference utilise pour ecrire le code : https://www.programiz.com/dsa/huffman-coding

# Description

	Code de huffman compression et decompression ecrit en C.


# Manuel d'utilisation 
	
	1- pour la compression 
		1.1 compiler le code source : gcc huffman_compression.c
		1.2 ./a.out chemin/vers/fichier/a/compressee

	2- pour la decompression
		2.1 compiler le code source: gcc huffman_decompression.c
		2.2 ./a.out chemin/vers/fichier/compresse chemin/vers/la/cle  

# PRINCIPE DE COMPRESSION # 

# constante TAILLE_TABLEAU 
    - C'est la taille de notre tableau de caractere. On part sur la base du code ASCII (127 caracteres)

# constante PREMIER_CARACTERE
    - Notre 1er caractere est le 32e caractere du code ASCII

# int noeudParent[TAILLE_TABLEAU];
    - Contient les racines obtenus a partir de la somme des occurences selon le principe de huffman

# int nbTotalCaractere = 0; 
    - Nombre total de caractere contenu dans le fichier a compresser

# int nbCaractereUnique = 0; 
    - Nombre total de caractere qui forment les mots du fichier a compresser

# caractereOccurence alphabet[TAILLE_TABLEAU]; 
    - Le tableau alphabet contient les caracteres ascii 32-126 d'ou la taille 95 (127-32)
    - Il contient les caracteres ascii possibles et leur donne d'occurence

Description detaille de chaque fonction

# La fonction initialisationTableauAlphabet()
    - Permet d'initialiser le tableau de l'alphabet
    - Lors de l'initialisation, les caracteres de chaque case correspondent aux indices du tableau et les occurences sont mis a 0 pour tout le monde
    - Tout ceci pour nous faciliter la manipulation. 

# La fonctionDeComparaison(const void *parametre1, const void *parametre2)
    - Compare deux éléments 
    - Va etre utilise dans qsort qui est une fonction deja definie en C et a une structure bien definie
    - Elle prend en parametre deux pointeurs sur des constantes de n'importe quel type d'ou le void; et renvoie un entier
    - Dans notre cas on fait en sorte qu'elle prenne des pointeurs sur le type qu'on a defini
    - Renvoie


# La fonction compterOccurence(char *cheminVersFichier) 
    - prend en parametre le fichier a compresser
    - calcule le nombre d'occurence de chaque caractere contenu dans le fichier a compresser
    - trie le tableau alphabet[TAILLE_TABLEAU] dans l'ordre croissant des occurences
        - le trie se fait avec l'aide de la fonction qsort de la bibliothèque C ; 
        - elle est definie comme suit:  void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) 
    - ne retourne rien mais nous donne le tableau trie a la fin de la procedure

# La fonction ArbreDeCompression()
    - Permet de construire l'arbre binaire de compression selon le principe de huffman

# La fonction void enregistrerFrequence()
    - Permet d'ecrire les caracteres sous leur valeur numerique ascii et leur frequences ou occurences 
    - On obtient un fichier nomme "cleDecompression" qui servira a la decompression

# La fonction enregistrerFichierCompresser(char *cheminVersFichier)
    - Permet d'enregistrer le fichier compresse

# PRINCIPE DE DECOMPRESSION # 

# La fonction void lireCleDecompression(char *cheminVersFichier) 
    - Permet de lire le contenu de la cle de decompression et inscrire dans le tableau alphabet
