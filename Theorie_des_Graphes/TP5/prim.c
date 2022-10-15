#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Prototypes et fonctions communes aux algorithmes
#include "main.h"
#include "prim.h"

// Ici le code qui va construire un graphe selon l'algorithme de Prim.
// Ce code va:
// 1. Lire le fichier texte et enregistrer les valeurs de l'ordre, taille et orientation du graphe
// 2. Lire le fichier texte et enregistrer toutes les aretes (ou arcs) dans un tableau
// 3. Demander à l'utilisateur le sommet de depart et initialiser
// 3. Creer un tableau d'ajout de sommets qui va garder en memoire les sommets deja visites
// 4. Pour chaque iteration de l'algorithle:
//      a. Indiquer le sommet de depart comme "visite"
//      b. Regarder si l'on a un graphe connexe
//          * Si oui: l'algorithme est fini
//          * Si non: l'algorithme continue
//      c. Chercher le lien le plus "leger" (dont le poids est le plus petit) qui part d'un sommet deja visite vers un sommet inconnu
//      d. ajouter ce lien au graphe et marquer les deux sommets impliques comme visites
//      e. Affecter INT_MAX au poids du lien traite pour ne pas le reprendre
// 5. Fermer le fichier et liberer la memoire qui n'est plus utile
// 6. return le graphe cree

// A noter que cet algorithme ne fonctionne correctement que pour des graphes non orientes ne présentant qu'une composante connexe

// Fonction d'initialisation de l'algo de Prim
t_graphe* prim() {

    // Ouverture du fichier texte
    FILE* fichier = ouvrirFichier();

    // Allocation d'un nouveau graphe et affectation des valeurs d'ordre, taille et orientation, ainsi que l'allocation de la liste des liens (aretes ou arcs du graphe selon l'ordre)
    t_graphe* nouveauGraphe = malloc(sizeof(t_graphe));
    fscanf(fichier, "%d%d%d", &nouveauGraphe->ordre, &nouveauGraphe->taille, &nouveauGraphe->orientation);
    nouveauGraphe->listeLiens = (t_lien**)malloc(sizeof(t_lien*)*nouveauGraphe->ordre);
    for (int i = 0; i < nouveauGraphe->ordre; i++)
    {
        nouveauGraphe->listeLiens[i] = NULL;
    }

    // Affectation d'un tableau de lien. Celui-ci stocke tout les liens du graphe original
    int** tabLiens = creerLiens(fichier, nouveauGraphe);
    
    // Demande du sommet de depart et initialisation du tableau des sommets visites
    int sommetDepart = demanderSommet();
    int sommetsAjoutes[nouveauGraphe->ordre];
    for (int i = 0; i < nouveauGraphe->ordre; i++)
    {
        sommetsAjoutes[i] = 0;
    }

    // Lancement de l'algo avec les arguments necessaires
    algoPrim(sommetDepart, nouveauGraphe, sommetsAjoutes, tabLiens);

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

// Fonction qui demande le sommet de depart a l'utilisateur
int demanderSommet() {

    int sommet;
    printf("Choisissez un sommet de depart: ");
    scanf("%d", &sommet);

    return sommet;
}

// Fonction qui effectue l'algo de prim
void algoPrim(int sommetDepart, t_graphe* graphe, int* sommetsAjoutes, int** tabLiens) {

    // Marquage du sommet de depart comme vu
    sommetsAjoutes[sommetDepart] = 1;

    // Variable qui stocke l'indice du lien le plus leger
    int lienLeger;
    // Contient le lien actuellement traite: Lecture plus simple
    int* lienActuel;

    // Boucle de Prim: Verification des sommets ajoutes au graphe
    while (!tousAjoutes(sommetsAjoutes, graphe->ordre))
    {
        // Trouve le lien utilisable dont le poids est le plus petit, et le garde en memoire
        lienLeger = poidsMinPossible(tabLiens, sommetsAjoutes, graphe->taille);
        // Affecte ce lien a lienActuel (question de lisibilite)
        lienActuel = tabLiens[lienLeger];

        // Ajoute le lien Actuel au graphe et indique que les deux sommets du lien sont visite
        ajouterLien(graphe, lienActuel[0], lienActuel[1], lienActuel[2]);
        sommetsAjoutes[lienActuel[0]] = 1;
        sommetsAjoutes[lienActuel[1]] = 1;

        // Le poids du lien est modifie pour qu'il ne soit pas reselectionne a la prochaine iteration
        lienActuel[2] = INT_MAX;
    }
    
}

// Fonction qui parcours le tableau de liens pour trouver celui dont le poids est le plus petit
int poidsMinPossible(int** tabLiens, int* sommetsAjoutes, int taille) {

    // Contient le lien actuellement traite: Lecture plus simple
    int* lienActuel;
    // Variables pour facilite la lecture et pour stocker l'indice du lien a utiliser
    int s1, s2, indiceMin, poidsMin;

    // Obtention d'un premier lien possible en parcourant le tableu
    for (int i = 0; i < taille; i++)
    {
        lienActuel = tabLiens[i];
        s1 = sommetsAjoutes[lienActuel[0]];
        s2 = sommetsAjoutes[lienActuel[1]];

        // Un lien n'est candidat que si il relie un lien visite a un lien non visite
        if((s1 == 1 && s2 == 0) || (s1 == 0 && s2 == 1)) {
            indiceMin = i;
            poidsMin = lienActuel[2];
            break;
        }
    }
    
    // Un lien possible a ete selectionne, il faut maintenant determiner si il s'agit du meilleur
    for (int i = 0; i < taille; i++)
    {
        lienActuel = tabLiens[i];
        s1 = sommetsAjoutes[lienActuel[0]];
        s2 = sommetsAjoutes[lienActuel[1]];

        // On va maintenant regarder si le lien selectionne est le plus petit. Si on en trouve un mieux, on prend celui la
        if(lienActuel[2] < poidsMin && ((s1 == 1 && s2 == 0) || (s1 == 0 && s2 == 1))) {
            indiceMin = i;
            poidsMin = lienActuel[2];
        }
    }

    return indiceMin;
}

// Fonction qui verifie si tous les sommets ont ete ajoute
int tousAjoutes(int* sommetsAjoutes, int ordre) {

    for(int i = 0; i < ordre; i++)
    {
        if(sommetsAjoutes[i] != 1) return 0; // Tous les sommets pas ajoutes
    }
    return 1; // Tous les sommets sont ajoutes. C'est termine
}