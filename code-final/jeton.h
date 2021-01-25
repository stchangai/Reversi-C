// jeton.h
// [PROJET S1] C++
#ifndef JETON_H
#define JETON_H

int LongueurListe(Jeton *listeJetons);

void PlaceUnJeton(Jeu *jeu,int *nbTours, Joueur *joueurActif, Joueur *joueurAdverse);

Jeton* createJetonJoueur(Jeu *jeu,int ligne, int colonne, Joueur *joueur);

void DeleteJetonJoueur(Jeu *jeu, int ligne, int colonne, Joueur *joueur);

bool IsJetonCorrect(Jeu *jeu, int colonne, int ligne, Joueur *joueurActif, Joueur *joueurAdverse, int ** placementAI=NULL, bool IsAITurn = false, int* countPlacementAI=0);

#endif