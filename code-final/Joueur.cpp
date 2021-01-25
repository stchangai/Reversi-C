//[PROJET S1] Jalon 0: affichage du plateau

#include <iostream>
using namespace std;
#include <cstring> 
#include <stdio.h>
#include "structures.h"
#include "./joueur.h"
#include "./jeton.h"
#include "./assistant.h"

//crée un nouveau joueur 
Joueur resetJoueur(){
    Joueur newJoueur;
    return newJoueur;
}

Joueur nouveauJoueur(int *IsWhite, bool IsAI){
        // initialisation d'un joueur normal
        if(IsAI == false){
                Joueur newJoueur = resetJoueur();
                //Joueur newJoueur;
                char nom[20];
                cout << "nom JOUEUR: ";
                cin >> nom;
                strcpy(newJoueur.nom, nom);
                //cout << "IsWhite : " << *IsWhite << endl;
                if(*IsWhite == 0){
                    cout << "couleur de jeton du JOUEUR " << nom << "(b/w): ";
                    cin >> newJoueur.couleur;
                    while(newJoueur.couleur != 'b' && newJoueur.couleur != 'w'){
                        cout << "erreur : vous n'avez pas indiqué une couleur de jeton correcte --> b/w ";
                        cin >> newJoueur.couleur;
                        if(newJoueur.couleur == 'q'){exit(1);}
                    }
                    switch(newJoueur.couleur){
                        case 'w':
                            *IsWhite = 1; // 1 signifie true, 2 signifie false, 0 signifie null
                            break;
                        case 'b':
                            *IsWhite = 2;
                            break;
                    }
                }
                else if(*IsWhite == 1) {newJoueur.couleur = 'b'; }
                else if(*IsWhite == 2) {newJoueur.couleur = 'w'; }

                newJoueur.nbJetons = 0;
                return newJoueur;
            }
        // initialisation de l'AI
        else{
                Joueur newJoueur = resetJoueur();
                //Joueur newJoueur;
                char nom[20] = "AI";
                strcpy(newJoueur.nom, nom);
                if(*IsWhite == 1) {newJoueur.couleur = 'b'; }
                else if(*IsWhite == 2) {newJoueur.couleur = 'w'; }
                newJoueur.nbJetons = 0;
                return newJoueur;
            }
}

// détermine le joueur actif
Joueur* WhoIsPlaying(Jeu *jeu, int *nbTours){
    (*nbTours)++;
    if(*nbTours%2 != 0){
            cout << *nbTours%2 << " c'est donc aux noirs de jouer" << endl;
            if(jeu->joueur1->couleur == 'b'){
                cout << "joueur jeton noir : " << jeu->joueur1->nom << endl;
                return jeu->joueur1;
            }
            else{
                return jeu->joueur2;
            }      
    }
    else{
            cout << *nbTours%2 << " c'est donc aux blancs de jouer" << endl;
            if(jeu->joueur1->couleur == 'w'){
                return jeu->joueur1;
            }
            else{
                return jeu->joueur2;
            } 
        }

}
// détermine le joueur adverse
Joueur* WhoIsNotPlaying(Jeu *jeu, int *nbTours){
    if(*nbTours%2 != 0){
            cout << *nbTours%2 << " joueur1 : "<< jeu->joueur1->nom << " " << jeu->joueur1->couleur << endl;
            if(jeu->joueur1->couleur == 'w'){
                return jeu->joueur1;
            }
            else{
                return jeu->joueur2;
            }      
    }
    else{
            if(jeu->joueur1->couleur == 'b'){
                return jeu->joueur1;
            }
            else{
                return jeu->joueur2;
            } 
        }
    (*nbTours)++;

}

// Tour pour un joueur normal
void GameOneVsOne(Jeu *jeu,int *nbTours,Joueur *joueurActif, Joueur *joueurAdverse, Jeton *curseurJ1, Jeton *curseurJ2){
    int FinTourJoueur; // 1 s'il n'y a pas de coup à jouer (donc fin de tour pour le joueur)
                        // 0 s'il y a au moins un coup à jouer
    FinTourJoueur = assistant(jeu,joueurActif);
    if(FinTourJoueur == 0)
    {
        PlaceUnJeton(jeu,nbTours,joueurActif, joueurAdverse);
    }
    // Vérification enregistrement jetons dans le joueur 
    curseurJ1 = joueurActif->first; // current, iterator
    curseurJ2 = joueurAdverse->first;
    /*while(curseurJ1 != NULL){
        cout << curseurJ1->colonne << " " << curseurJ1->ligne << " "  << curseurJ1->couleur << endl;
        curseurJ1 = curseurJ1->next;
    }
    while(curseurJ2 != NULL){
        cout << curseurJ2->colonne << " " << curseurJ2->ligne << " "  << curseurJ2->couleur << endl;
        curseurJ2 = curseurJ2->next;
    }*/
    
}