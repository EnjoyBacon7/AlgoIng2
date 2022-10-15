#ifndef CODETP5_PRIM_H
#define CODETP5_PRIM_H

// Prototype des fonctions
t_graphe* prim(void);
int demanderSommet(void);
void algoPrim(int sommetDepart, t_graphe* graphe, int* sommetsAjoutes, int** tabLiens);
int poidsMinPossible(int** tabLiens, int* sommetsAjoutes, int taille);
int tousAjoutes(int* sommetsAjoutes, int ordre);

#endif //CODETP5_PRIM_H