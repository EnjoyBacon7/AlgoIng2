#ifndef CODETP5_MAIN_H
#define CODETP5_MAIN_H

typedef struct graphe {

    int ordre, taille, orientation;
    struct lien** listeLiens;
    int poidsTot;
} t_graphe;

typedef struct lien {

    int indiceSommet;
    int poids;
    struct lien* lienSuivant;
} t_lien;

void menu();
void freeGraphe(t_graphe* graphe);
FILE* ouvrirFichier(void);
void ajouterLien(t_graphe* graphe, int s1, int s2, int p);
void afficherGraphe(t_graphe* graphe);

// Fonctions communes a prim et kruskal

int** creerLiens(FILE* fichier, t_graphe* graphe);

#endif //CODETP5_MAIN_H