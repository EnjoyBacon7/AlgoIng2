#include <stdio.h>
#include <stdlib.h>

// Prototypes et fonctions communes aux algorithmes
#include "main.h"
#include "creationGraphe.h"

// Ici le code qui va construire un graphe selon le fichier txt sans traitement.
// La structure contiendra l'ordre, la taille, l'orientation et les aretes ou arcs du graphe.
// Pour un graphe non oriente (comme ici), les aretes seront ajoutees deux fois, une fois par sommet lie
// Cette structure de graphe final est la meme pour les trois algorithmes, ils vont juste chacun decider quels liens ajouter

// Ce code va:
// 1. Lire le fichier texte et enregistrer les valeurs de l'ordre, taille et orientation du graphe
// 2. Lire le fichier et ajouter toutes les aretes au tableau directement
// 3. Return le graphe cree


// Fonction d'initialisation du graphe
t_graphe* creerGraphe() {

    // Ouverture du fichier texte
    FILE* fichier = ouvrirFichier();

    // Allocation d'un nouveau graphe et affectation des valeurs d'ordre, taille et orientation, ainsi que l'allocation de la liste des liens (aretes ou arcs du graphe selon l'ordre)
    t_graphe* nouveauGraphe = malloc(sizeof(t_graphe));
    fscanf(fichier, "%d%d%d", &nouveauGraphe->ordre, &nouveauGraphe->taille, &nouveauGraphe->orientation);
    nouveauGraphe->listeLiens = malloc(sizeof(t_lien*)*nouveauGraphe->ordre);
    for (int i = 0; i < nouveauGraphe->ordre; i++)
    {
        nouveauGraphe->listeLiens[i] = NULL;
    }
    
    // Lecture des liens et affectation dans nouveauGraphe
    lireLiens(nouveauGraphe, fichier);
    
    // Fermeture du fichier et liberation de la memoire qui ne nous est plus utile
    fclose(fichier);

    return nouveauGraphe;
}

// Fonction qui ajoute toutes les aretes au graphe
void lireLiens(t_graphe* graphe, FILE* fichier) {
    
    // Boucle qui va lire l'entierete du fichier, et pour chaque ligne, ajouter une arete au graphe
    int s1, s2, p;
    while (!feof(fichier))
    {
        fscanf(fichier, "%d%d%d", &s1, &s2, &p);
        ajouterLien(graphe, s1, s2, p);
    }
}