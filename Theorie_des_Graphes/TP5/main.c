#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Faire un main.h est maladroit

// Prototypes et fonctions communes
#include "main.h"
#include "creationGraphe.h"
#include "prim.h"
#include "kruskal.h"

// Toute utilisation du mot arc est fausse. Le code ne traitera pas de graphe oriente differemment

int main() {

    menu();

    return 0;
}

void menu() {

    t_graphe* graphePrincipal;
    t_graphe* grapheKruskal;
    t_graphe* graphePrim;

    int choix;
    printf("Choisissez un algorithme:\n1) Creation Classique\n2) Kruskal\n3) Prim\n >");
    scanf("%d", &choix);

    switch (choix)
    {
    case 1:
        graphePrincipal = creerGraphe();
        afficherGraphe(graphePrincipal);
        freeGraphe(graphePrincipal);
        break;

    case 2:
        grapheKruskal = kruskal();
        afficherGraphe(grapheKruskal);
        freeGraphe(grapheKruskal);
        break;
    case 3:

        graphePrim = prim();
        afficherGraphe(graphePrim);
        freeGraphe(graphePrim);
        break;
    
    default:
        break;
    }
    menu();
}

void freeGraphe(t_graphe* graphe) {

    for (int i = 0; i < graphe->ordre; i++)
    {
        free(graphe->listeLiens[i]);
    }
    free(graphe->listeLiens);
    free(graphe);
    
}

void afficherGraphe(t_graphe* graphe) {

    printf("\n");
    for (int i = 0; i < graphe->ordre; i++)
    {
        
        t_lien* tmp = graphe->listeLiens[i];
        printf("Sommet %d: ", i);
        while (tmp)
        {
            printf("%d ", tmp->indiceSommet);
            tmp = tmp->lienSuivant;
        }
        printf("\n");
        
    }
    printf("Poids Total: %d", graphe->poidsTot);
    printf("\n\n");
}

//------------------------------------------------------------------------------------------

// Ici se trouvent les fonctions que les trois algos vont utiliser

FILE* ouvrirFichier() {

    FILE* fichier = NULL;
    fichier = fopen("Graphe.txt", "r");

    if (!fichier) {

        printf("Erreur de fichier\n");
        exit(-1);
    }

    return fichier;
}

void ajouterLien(t_graphe* graphe, int s1, int s2, int p) {
    
    t_lien* nouveauLien1 = malloc(sizeof(t_lien));
    t_lien* nouveauLien2 = malloc(sizeof(t_lien));

    nouveauLien1->indiceSommet = s2;
    nouveauLien2->indiceSommet = s1;

    nouveauLien1->poids = p;
    nouveauLien2->poids = p;

    nouveauLien1->lienSuivant = graphe->listeLiens[s1];
    nouveauLien2->lienSuivant = graphe->listeLiens[s2];

    graphe->listeLiens[s1] = nouveauLien1;
    graphe->listeLiens[s2] = nouveauLien2;

    graphe->poidsTot += nouveauLien1->poids;
}

// Fonctions communes a prim et kruskal

// Lit le fichier texte pour tous les liens et les enregistre dans un tableau de liens qui est rendu
int** creerLiens(FILE* fichier, t_graphe* graphe) {

    // Allocation du tableau à deux dimensions
    int** tabLiens = (int**)malloc(sizeof(int*)*graphe->taille);
    // Allocation de la deuxieme dimension et lecture des liens
    for (int i = 0; i < graphe->taille; i++)
    {
        tabLiens[i] = (int*)malloc(sizeof(int)*3);
        fscanf(fichier, "%d%d%d", &tabLiens[i][0], &tabLiens[i][1], &tabLiens[i][2]);
    }

    return tabLiens;
}