//[PROJET S1] Jalon 3 : joueur artificiel

#include <iostream>
using namespace std;
#include <cstring> 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "./AI.h"
#include "./jeu.h"
#include "./joueur.h"
#include "./jeton.h"


void FindAllPlacementsPossible(Jeu *jeu, Joueur *joueurActif, Joueur *joueurAdverse, int placementAI[MAXPLACEMENT],int* countPlacementAI, int indexPlacementAI){
    coordonnees tabcoordonnees[MAXPLACEMENT] = {};
    int compteur = 0;
    int nbjetons = LongueurListe(joueurActif->first);
    Jeton *current = joueurActif->first;
    int jetonGagne = 0;
    int tourWhile = 0;
    int ligne, colonne, coordonneesX, coordonneesY;
    for (int i = 0; i < nbjetons && current !=0; ++i)
    {
        ligne = current->ligne;
        colonne = current->colonne;
        for (int col = -1; col < 2; ++col)
        {
            for (int l = -1; l < 2; ++l)
            {   
                coordonneesY = colonne + col;
                coordonneesX = ligne + l; 
                if(jeu->plateau[coordonneesY][coordonneesX].couleur == joueurAdverse->couleur){
                    tourWhile = 1;
                    // on vérifie s'il n'y a pas un autre pion adverse qui suit le pion détecté précédemment
                    while(jeu->plateau[coordonneesY+col][coordonneesX+l].couleur == joueurAdverse->couleur){
                        coordonneesY = coordonneesY+col;
                        coordonneesX = coordonneesX + l;
                        tourWhile = tourWhile + 1;
                    }
                    /*si l'on ne détecte ni un pion du joueur actif ni un pion du joueur adverse
                     alors le placement est possible*/
                    if(jeu->plateau[coordonneesY+col][coordonneesX+l].couleur != joueurActif->couleur && jeu->plateau[coordonneesY+col][coordonneesX+l].couleur != joueurAdverse->couleur)
                    {   
                        compteur = compteur + 1;
                        coordonneesY = coordonneesY + col;
                        coordonneesX = coordonneesX + l;
                        for (int i = tourWhile; i>=0; --i)
                        { 
                            jetonGagne = jetonGagne + 1;                            
                        }
                        // on cherche tous les placements possibles (donc corrects) que pourrait jouer l'AI, le meilleur placement n'existe donc pas d'où le indexPacementAI négatif
                        if(indexPlacementAI == -1){
                            int *pointerToArray = &placementAI[0];
                            //on place le nombre de jetons que l'AI peut potentiellement gagner si elle joue ce placement
                            bool IsPlacementCorrect = IsJetonCorrect(jeu, coordonneesY, coordonneesX, joueurActif, joueurAdverse,(int**)&pointerToArray, true, countPlacementAI);
                            tabcoordonnees[compteur].y = coordonneesY;
                            tabcoordonnees[compteur].x = coordonneesX;
                            // remise à séro du nombre de jetons gagnés
                            jetonGagne = 0;
                        }
                        // le meilleur placement pour l'AI a été sélectionné : elle peut donc jouer son tour
                        if(indexPlacementAI > -1 && compteur == indexPlacementAI){
                            bool IsPlacementCorrect = IsJetonCorrect(jeu, coordonneesY, coordonneesX, joueurActif, joueurAdverse);
                            // on verifie si le placement est correct dans l'autre sens cette fois : en partant de la position éventuelle du pion qui sera joué
                            // dans la fonction IsJetonCorrect() les pions intermédiaires ont été ajoutés à la liste du joueur
                            if(IsPlacementCorrect)
                            {
                                // il ne reste plus qu'à ajouter dans la liste du joueur le jeton qui remplira 
                                // la case vide dans laquelle l'AI a "décidé" de placer son pion
                                Jeton* CaseVideJeton = createJetonJoueur(jeu,coordonneesX, coordonneesY, joueurActif);
                                CaseVideJeton->next = joueurActif->first;
                                joueurActif->first = CaseVideJeton;
                            }

                        }
                        
                    }
                    else{
                        //cout << "coordonnées : " << coordonneesY << " ; " << coordonneesX <<" de couleur : " << jeu->plateau[coordonneesY][coordonneesX].couleur << " : la case n'est pas vide !!"<< endl;
                    }
                }
            
            }
        }
       current = current->next;
    }
    if(indexPlacementAI == -1){
        // indique la fin du tableau
        placementAI[compteur+1] = -1;
        countPlacementAI--;  
    }
}

int ChooseTheBestPlacement(Joueur *joueurActif, int placementAI[MAXPLACEMENT]){
    int max = 0;
    int count = 0;
    int placementsAreEven = 0;
    int indexPlacementsEven[MAXPLACEMENT]={};
    int placementsAreBest = 0;
    int random;
    //on cherche l'entier le plus grand dans le tableau des placements possibles
    for (int i = 1;placementAI[i]>0 ; i++)
    {
        if(max < placementAI[i]){
            max = placementAI[i];
            placementsAreBest = i;
            /* si un nouveau max est trouvé alors la variable des placements 
            qui ont le même nombre de jetons gagnés est remise à 1 */
            placementsAreEven = 1;
        }
        if(max == placementAI[i]){
            indexPlacementsEven[placementsAreEven] = i;
            placementsAreEven++;
        }
        count++;
    }
    if(placementsAreEven == count || (placementsAreEven-1) > 1){
        /* initialize random seed: */
        srand (time(NULL));

        /* generate a random number between 1 and the number of elements = max in placementAI */
         random = rand() % (placementsAreEven-1) + 1;
        //cout << "le meilleur placementAI random est : "<< indexPlacementsEven[random] << " à l'index " << random<< endl;
        return indexPlacementsEven[random];
    }
    // s'il n'y a qu'un seul placement avec le max de jetons gagnés alors on le prend directement
    else{    
        //cout << "le meilleur placementAI est : "<< placementAI[placementsAreBest] << " à l'index " << placementsAreBest<< endl;
        return placementAI[placementsAreBest];
    }
}

//Tour pour l'ordinateur
void GameOneVsComputer(Jeu *jeu, Joueur* joueurActif,Joueur* joueurAdverse){
    int placementAI[MAXPLACEMENT];
    int indexPlacementAI = -1;
    int countPlacementAI = 1;
    // on cherche tous les coups possibles pour l'ordinateur
    FindAllPlacementsPossible(jeu, joueurActif, joueurAdverse, placementAI, &countPlacementAI);
    // on choisit un des meilleurs placements possibles parmi la liste fournie au-dessus
    indexPlacementAI = ChooseTheBestPlacement(joueurActif, placementAI);
    // on relance la fonction mais dans une autre configuration :
    // grâce à l'index récupéré la fonction retrouve les coordonnées (colonne,ligne) de la future position du jeton
    //et l'envoie à la fonction IsJetonCorrect() pour créer et enregistrer le jeton dans la liste de jeton de l'AI
    FindAllPlacementsPossible(jeu,joueurActif, joueurAdverse, placementAI,&countPlacementAI,indexPlacementAI);
}