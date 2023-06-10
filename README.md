# Code de Compression et de decompression de Huffman

# Manuel d'utilisation 

gcc huffman_compression && ./a.out fichierACompresser //doit renvoyer le fichier comprenant : 
Caractere	Occurence / Frequence	Code

# Compression 
Description detaille de chaque fonction
...
# la fonction compterOccurence(char *cheminVersFichier) 
    - prend en parametre le fichier a compresser
    - calcule le nombre d'occurence de chaque caractere contenu dans le fichier a compresser
    - trie le tableau alphabet[TAILLE_TABLEAU] dans l'ordre croissant des occurences
        - le trie se fait avec l'aide de la fonction qsort de la bibliothèque C ; 
        - elle est definie comme suit:  void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*)) 
    - ne retourne rien mais nous donne le tableau trie a la fin de la procedure


/* Le tableau alphabet contient les caracteres ascii 32-126 d'ou la taille 95 (127-32)
- Il contient les caracteres ascii possibles et leur donne d'occurence
*/
caractereOccurence alphabet[TAILLE_TABLEAU]; 



/*
 3- 7 Fonction pour creer l'arbre
    :param -> un tableau (dans notre cas ce sera le tableau deja trie des caracteres et leur occurence)
    :return -> un autre tableau qui contient les racines de notre arbre - suivant le principe de huffman 
*/

void ArbreDeCompression()


*
Cette fonction  compare deux éléments > Elle va etre utilise dans qsort qui est une fonction deja definie en C et a une structure bien definie
- Elle prend en parametre deux pointeurs sur des constantes de n'importe quel type d'ou le void; et renvoie un entier
- Dans notre cas on fait en sorte qu'elle prenne des pointeurs sur le type qu'on a defini
*/
int fonctionDeComparaison (const void *parametre1, const void *parametre2)



*
cette fonction permet d'initialiser le tableau de l'alphabet
- Lors de l'initialisation, les caracteres de chaque case correspondent aux indices du tableau et les occurences sont mis a 0 pour tout le monde
Tout ceci pour nous faciliter la manipulation. 
*/
void initialisationTableauAlphabet()


# Decompression 
