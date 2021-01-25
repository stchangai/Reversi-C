//[PROJET S1] Jalon 0: affichage du plateau

#include <iostream>
using namespace std;
#include <cstring> 
#include "structures.h"
#include "./jeton.h"
#include "./jeu.h"


int LongueurListe(Jeton *listeJetons){
    int count=0;
    while(listeJetons){
        listeJetons = listeJetons->next;
        count++;
    }
    return count;
}

// la fontion retourne un objet de type Jeton
Jeton* createJetonJoueur(Jeu *jeu, int ligne, int colonne, Joueur *joueur)
{
    Jeton* newJeton = (Jeton*) malloc(sizeof (Jeton)); // (ListNode*) malloc(sizeof(ListeNode))
    
    newJeton->ligne = ligne;
    newJeton->colonne = colonne;
    newJeton->couleur = joueur->couleur;
    newJeton->next = NULL;
    joueur->nbJetons = joueur->nbJetons + 1;
    jeu->plateau[colonne][ligne]=*newJeton;
    return newJeton;
}

void DeleteJetonJoueur(Jeu *jeu, int ligne, int colonne, Joueur *joueur) {
    Jeton* previousJeton = NULL;
    Jeton* currentJeton = joueur->first;
    while (currentJeton != NULL) {
        if (currentJeton->colonne == colonne && currentJeton->ligne == ligne) {
            if (previousJeton == NULL) {
                joueur->first = currentJeton->next;
            }
            else {
                previousJeton->next = currentJeton->next;
            }
            joueur->nbJetons = joueur->nbJetons - 1;
        }
        else {
            previousJeton = currentJeton;
        }
        currentJeton = currentJeton->next;
    }
}


void PlaceUnJeton(Jeu *jeu,int *nbTours, Joueur *joueurActif, Joueur *joueurAdverse){
    
    char lettreConvert[9] = "ABCDEFGH", NombreConvert[9] = "12345678";
    int colonne, ligne;
    char coordonnees[2];
    cout << joueurActif->nom << ", vous avez " << joueurActif->nbJetons  << " jetons, et c'est à vous de jouer."<< endl;
    cout << joueurActif->nom << ", donnez les ordonnées d'un nouveau jeton : ";
    cin >> coordonnees;
    ExitJeu(coordonnees);
    //conversion des caractères en entiers
    for (int i = 0; i < 8; ++i)
    {
        if(coordonnees[0] == lettreConvert[i]){colonne = i+1;}
        if(coordonnees[1] == NombreConvert[i]){ligne = i+1;}
    }
    cout << "Vous avez donné comme colonne  : " << colonne << " et comme ligne " << ligne<< endl;
    cout << "Vous avez donné comme coordonnées  : " << coordonnees << endl;

    bool PlacementCorrect = IsJetonCorrect(jeu, colonne, ligne, joueurActif, joueurAdverse/*, *numJoueur*/);
    if(PlacementCorrect){ 
            // si le placement est correct alors on crée un nouveau jeton et on l'ajoute à 
            // la liste chainée de jetons du joueur
            Jeton* newJeton = createJetonJoueur(jeu,ligne, colonne, joueurActif/*, jeu*/);
            newJeton->next = joueurActif->first;
            joueurActif->first = newJeton;
    }
    else{
            cout << "Attention ce placement n'est pas possible. Essayez une autre position."<<endl;
            PlaceUnJeton(jeu, nbTours, joueurActif, joueurAdverse);
    }
}


bool IsJetonCorrect(Jeu *jeu, int colonne, int ligne, Joueur *joueurActif, Joueur *joueurAdverse, int ** placementAI, bool IsAITurn, int* countPlacementAI){
    coordonnees tabcoordonnees[9];
    // coordonnées des jetons autours du placement sélectionné
    int coordonneesX, coordonneesY;
    // compteur = taille du tableau coordonnées
    int compteur = 0;

    int jetonGagne = 0;
    int tourWhile = 0;
    char couleurAdverse = joueurAdverse->couleur;
    if(estCaseVide(jeu, colonne, ligne)){
        // boucles for l'une dans l'autre pour vérifier autour de l'emplacement la présence de pion adverse
        for (int col = -1; col < 2; ++col)
        {
            for (int l = -1; l < 2; ++l)
            {   
                coordonneesY = colonne + col;
                coordonneesX = ligne + l; 
                if((*jeu).plateau[coordonneesY][coordonneesX].couleur == couleurAdverse){
                    tourWhile = 1;
                    // on vérifie s'il n'y a pas un autre pion adverse qui suit le pion détecté précédemment
                    while((*jeu).plateau[coordonneesY+col][coordonneesX+l].couleur == couleurAdverse){
                        coordonneesY = coordonneesY+col;
                        coordonneesX = coordonneesX + l;
                        //compteur = compteur + 1;
                        tourWhile = tourWhile + 1;
                    }
                    // si l'on détecte un pion du joueur actif alors le placement est correct
                    if((*jeu).plateau[coordonneesY+col][coordonneesX+l].couleur == joueurActif->couleur)
                    {   
                        compteur = compteur + 1;
                        coordonneesY = coordonneesY + col;
                        coordonneesX = coordonneesX + l;

                        for (int i = tourWhile; i>0; --i)
                        { 
                            if(!IsAITurn){
                                tabcoordonnees[i].y = coordonneesY-col;
                                tabcoordonnees[i].x = coordonneesX-l;
                                coordonneesY = coordonneesY-col;
                                coordonneesX = coordonneesX-l;
                                
                                DeleteJetonJoueur(jeu,coordonneesX, coordonneesY, joueurAdverse);
                                Jeton* tempJeton = createJetonJoueur(jeu,coordonneesX, coordonneesY, joueurActif);
                                tempJeton->next = joueurActif->first;
                                joueurActif->first = tempJeton;
                            }
                            jetonGagne = jetonGagne + 1;
                            
                        }
                        //if(IsAITurn) cout << "jetonGagné : " << jetonGagne  << " avec coordonnées : " << (coordonneesY-col) << (coordonneesX-l) << endl;
                    }
                    else{
                        if(!IsAITurn){
                            //cout << "il y malheureusement pas de jeton " << joueurActif->couleur <<"  de coordonnées " << coordonneesY+col << " " << coordonneesX+l << endl;
                        }
                    }
                }
            }
        }
    }
    else{
        return false;} // retourne faux si la case proposée par le joueur n'est pas vide 
    if (compteur > 0)
    {
        // Rajoute le pion qui a été joué par le joueur
        jetonGagne = jetonGagne + 1;
        // ne touche pas au pion, permet juste de répertorier le nombre de jetons potentiellement gagnés pour un placement de l'AI
        if(IsAITurn){
            //cout << "placementAI != NULL" << endl;
            //cout << "countPlacementAI :" << *countPlacementAI << " jetonGagne = " << jetonGagne << endl;
             (*placementAI)[*countPlacementAI] = jetonGagne;
             (*countPlacementAI)++;
         }
        return true;
    }
    else{ return false;}
}
