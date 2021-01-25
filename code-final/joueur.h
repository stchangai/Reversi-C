// joueur.h
// [PROJET S1] C++
#ifndef JOUEUR_H
#define JOUEUR_H

Joueur resetJoueur();

Joueur nouveauJoueur(int *IsWhite, bool IsAI = false);

Joueur* WhoIsPlaying(Jeu *jeu, int *nbTours);

Joueur* WhoIsNotPlaying(Jeu *jeu, int *nbTours);

void GameOneVsOne(Jeu *jeu,int *nbTours,Joueur *joueurActif, Joueur *joueurAdverse, Jeton *curseurJ1, Jeton *curseurJ2);

#endif