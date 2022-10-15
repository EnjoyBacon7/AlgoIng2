#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Prototypes et fonctions communes aux algorithmes
#include "main.h"
#include "kruskal.h"

// Ici le code qui va construire un graphe selon l'algorithme de Kruskal.
// Ce code va:
// 1. Lire le fichier texte et enregistrer les valeurs de l'ordre, taille et orientation du graphe
// 2. Lire le fichier texte et enregistrer toutes les aretes (ou arcs) dans un tableau
// 3. Creer un tableau de connexite qui va garder en memoire le nombre de graphes connexes que nous avons au fil de l'algorithme
// 4. Pour chaque iteration de l'algorithme:
//      a. Regarder si l'on a un graphe connexe
//          * Si oui: l'algorithme est fini
//          * Si non: l'algorithme continue
//      b. Chercher le lien le plus "leger" (dont le poids est le plus petit)
//      c. Verifier si ce lien cree un cycle (si il connecte deux sommets de meme "indice" de connexite)
//          * Si oui: Rien ne se passe
//          * Si non: Ajouter ce lien au graphe et "harmoniser" tous les indices de connexite des sommets lies
//      d. Affecter INT_MAX au poids du lien traite pour ne pas le reprendre
// 5. Fermer le fichier et liberer la memoire qui n'est plus utile
// 6. Return le graphe cree


// Fonction d'initialisation de l'algo de Kruskal
t_graphe* kruskal() {

    // Ouverture du fichier texte
    FILE* fichier = ouvrirFichier();

    // Allocation d'un nouveau graphe et affectation des valeurs d'ordre, taille et orientation, ainsi que l'allocation de la liste des liens (aretes ou arcs du graphe selon l'ordre)
    t_graphe* nouveauGraphe = (t_graphe*)malloc(sizeof(t_graphe));
    fscanf(fichier, "%d%d%d", &nouveauGraphe->ordre, &nouveauGraphe->taille, &nouveauGraphe->orientation);
    nouveauGraphe->listeLiens = (t_lien**)malloc(sizeof(t_lien*)*nouveauGraphe->ordre);
    for (int i = 0; i < nouveauGraphe->ordre; i++)
    {
        nouveauGraphe->listeLiens[i] = NULL;
    }

    // Affectation d'un tableau de liens. Celui-ci stocke tout les liens du graphe original
    int** tabLiens = creerLiens(fichier, nouveauGraphe);
    
    // Creation d'un tableau de connexite qui garde en memoire les differentes parties connexes de notre graphe
    int connexite[nouveauGraphe->ordre];
    for (int i = 0; i < nouveauGraphe->ordre; i++)
    {
        // Au debut, aucun sommet n'est lie, il y a autant de composantes connexes que de sommets
        connexite[i] = i;
    }

    // Lancement de l'algo avec les arguments necessaires
    algoKruskal(tabLiens, connexite, nouveauGraphe);

    // Fermeture du fichier et liberation de la memoire qui ne nous est plus utile
    fclose(fichier);
    for (int i = 0; i < nouveauGraphe->taille; i++)
    {
        free(tabLiens[i]);
    }
    free(tabLiens);

    // Rendu du graphe a la fonction appelante
    return nouveauGraphe;
}

// Fonction qui effectue l'algo de kruskal
void algoKruskal(int** tabLiens, int* connexite, t_graphe* graphe) {

    // Variable qui stocke l'indice du lien le plus leger
    int lienLeger;
    // Contient le lien actuellement traite: Lecture plus simple
    int* lienActuel;
    
    // Boucle de Kruskal: Verification du nombre de composantes connexes du graphe
    while (!uniConnexite(connexite, graphe->ordre))
    {   
        // Trouve le lien dont le poids est le plus petit, et le garde en memoire
        lienLeger = poidsMin(tabLiens, graphe->taille);
        // Affecte ce lien a lienActuel (question de lisibilite)
        lienActuel = tabLiens[lienLeger];
        // Si les deux sommets ont le meme indice de connexite, il existe deja un chemin qui les relie (on ne fait rien)
        if (connexite[lienActuel[0]] == connexite[lienActuel[1]]) {}
        // Sinon, on ajoute le lien Actuel au graphe et on harmonise les indices de connexite
        else 
        {
            ajouterLien(graphe, lienActuel[0], lienActuel[1], lienActuel[2]);
            harmoniserConnexite(connexite, lienActuel, graphe->taille);
        }
        // Le poids du lien est modifie pour qu'il ne soit pas reselectionne a la prochaine iteration
        lienActuel[2] = INT_MAX;
    }
    
}

// Fonction qui verifie si tous les sommets font partie du meme graphe
int uniConnexite(int* connexite, int ordre) {

    // Prend un numero de connexite de reference
    int numReference = connexite[0];

    // Si un sommet ne possede pas le meme numero de reference, il ne fait pas partie du meme graphe. Kruskal n'est pas fini
    for(int i = 0; i < ordre; i++)
    {
        if(connexite[i] != numReference) return 0; // Pas d'uniconnexite
    }
    return 1;   // Uniconnexite accomplie
}

// Fonction qui a pour but de donner un meme indice a tous les sommets qui sont connexe
void harmoniserConnexite(int* connexite, int* lienActuel, int taille) {

    // Prend le numero de connexite du premier sommet
    int numeroConnexite = connexite[lienActuel[0]];
    for (int i = 0; i < taille; i++)
    {
        // Si le sommet traite a le meme numero que le deuxieme sommet, il est connexe: on harmonise son indice
        if(connexite[i] == connexite[lienActuel[1]]) 
        {
            connexite[i] = numeroConnexite;
        }
    }
    
}// Fonction qui parcours le tableau de liens pour trouver celui dont le poids est le plus petit
int poidsMin(int** tabLiens, int taille) {

    // Indice du lien selectionne
    int indiceMin = 0;
    // Poids du lien selectionne
    int poidsMin = INT_MAX;

    // Parcours du tableau en comparant les poids et en affectant les valeurs si le lien est moins lourd
    for (int i = 0; i < taille; i++)
    {
        if(tabLiens[i][2] < poidsMin)
        {
            indiceMin = i;
            poidsMin = tabLiens[i][2];
        }
    }

    return indiceMin;
}