//[PROJET S1] Jalon 0: affichage du plateau

#include <iostream>
using namespace std;
#include <cstring> 
#include "structures.h"
#include "./jeton.h"
#include "./jeu.h"


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

bool estCaseVide(Jeu *jeu,int colonne,int ligne){
    Joueur *joueur1 = jeu->joueur1;
    Jeton *current= joueur1->first;
    for(int i=0; i<(joueur1->nbJetons); i++){
        if(current->colonne==colonne && current->ligne==ligne){
            return true;}
        else{current=current->next;}
    }

    Joueur *joueur2=jeu->joueur2;
    current=joueur2->first;
    for((i=0; i<(joueur2->nbJetons); i++){
        if(current->colonne==colonne && current->ligne==ligne){
            return true;}
        else{current=current->next;}
    }

    return true;
}

bool IsJetonCorrect(Jeu *jeu, int colonne, int ligne, Joueur *joueurActif, Joueur *joueurAdverse/*, int numJoueur*/){
    coordonnees tabcoordonnees[9];
    // coordonnées des jetons autours du placement sélectionné
    int coordonneesX, coordonneesY;
    // compteur = taille du tableau coordonnées
    int compteur = 0;

    int jetonGagne = 0;
    int tourWhile = 0;
    char couleurAdverse=joueurAdverse->couleur;
    /*
    if(joueurActif->couleur == 'w'){couleurAdverse = 'b';}   
    if(joueurActif->couleur == 'b'){couleurAdverse = 'w';}*/
    
    if (estCaseVide(jeu,colonne,ligne)){
    
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
                    compteur = compteur + 1;
                    tourWhile = tourWhile + 1;
                }
                // si l'on détecte un pion du joueur actif alors le placement est correct
                if((*jeu).plateau[coordonneesY+col][coordonneesX+l].couleur == joueurActif->couleur)
                {   
                    compteur = compteur + 1;
                    coordonneesY = coordonneesY + col;
                    coordonneesX = coordonneesX + l;
                    //une fois détecté, on remplit un tableau de tous les pions gagnés en faisant l'opération inverse
                    for (int i = tourWhile; i>0; --i)
                    { 
                        tabcoordonnees[i].y = coordonneesY-col;
                        tabcoordonnees[i].x = coordonneesX-l;
                        coordonneesY = coordonneesY-col;
                        coordonneesX = coordonneesX-l;
                        jetonGagne = jetonGagne + 1;
                        //on supprime le jeton gagné de la liste de jetons de l'adversaire
                        DeleteJetonJoueur(jeu,coordonneesX, coordonneesY, joueurAdverse);
                        // puis on l'ajoute à la liste de jetons du joueur actif
                        Jeton* tempJeton = createJetonJoueur(jeu,coordonneesX, coordonneesY, joueurActif);
                        tempJeton->next = joueurActif->first;
                        joueurActif->first = tempJeton;
                        
                    }
                    cout << "jetonGagné : " << jetonGagne+1 << endl;
                }
                else{
                    cout << "il n'y malheureusement pas de jeton " << joueurActif->couleur
                    <<"  de coordonnées " << coordonneesY+col << " " << coordonneesX+l  
                    << endl;
                }
            }
        
        }
    }
    // si le compteur > 0 cela veut dire qu'il y a des jetons gagnés et donc que le placement est correct
    if (compteur > 0)
    {
        return true;
    }
    else{ return false;}
    }
    else{return false;}//si la case est pleine
}
