#ifndef CODETP5_KRUSKAL_H
#define CODETP5_KRUSKAL_H

// Prototypes des fonctions
t_graphe* kruskal(void);
void algoKruskal(int** tabLiens, int* connexite, t_graphe* graphe);
int uniConnexite(int* connexite, int ordre);
void harmoniserConnexite(int* connexite, int* lienActuel, int taille);
int poidsMin(int** tabLiens, int taille);

#endif //CODETP5_KRUSKAL_H