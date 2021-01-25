// AI.h
// [PROJET S1] C++
#ifndef AI_H
#define AI_H

#define MAXPLACEMENT 40

void FindAllPlacementsPossible(Jeu *jeu, Joueur *joueurActif, Joueur *joueurAdverse, int placementAI[MAXPLACEMENT],int* countPlacementAI=0, int indexPlacementAI = -1);

int ChooseTheBestPlacement(Joueur *joueurActif, int placementAI[MAXPLACEMENT]);

void GameOneVsComputer(Jeu *jeu, Joueur* joueurActif,Joueur* joueurAdverse);

#endif