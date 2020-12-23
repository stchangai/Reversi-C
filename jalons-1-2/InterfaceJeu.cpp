//[PROJET S1] Jalon 0: affichage du plateau

#include <iostream>
using namespace std;
#include <cstring> 
#include "structures.h"
#include "./jeu.h"
#include "./jeton.h"

void affichePlateau(Jeu jeu){
    int lettres = 65;
    //Lettres colonne du plateau
    cout << "   ";
    for(int i=0 ; i<8;i++){
        cout << "  " <<(char)(lettres+i) << " "; 
    }
    cout << endl;
    //grille de jeu
    for(int ligne=1;ligne<=8;ligne++){
        
        //traits horizontaux
        cout << "   "; // espace laissé pour la colonne de numéros de la grille 
        for(int colonne=1 ; colonne<=8;colonne++){
            cout << "+---"; 
        }
        cout << '+'<<endl;

        //traits verticaux
        cout <<" " << ligne << " "; // affichage du numéro de la ligne de la grille  
        for(int colonne=1 ; colonne<=8;colonne++){
            char cont=' ';
            if(jeu.plateau[colonne][ligne].couleur=='w'){
                cont='0';
            }
            else if(jeu.plateau[colonne][ligne].couleur=='b'){
                    cont='*';
            }
                cout << '|' << ' ' <<cont <<' ' ;
        }
        cout << '|' << endl;
    }
    //dernière ligne de la grille
    cout << "   "; // espace laissé pour la colonne de numéros de la grille 
    for(int colonne=1 ; colonne<=8;colonne++){
            cout << "+---"; 
        }
        cout << '+'<<endl;
}

//initialise le plateau avec les 4 jetons de départ
void initJeu(Jeu *jeu, Joueur *j1, Joueur *j2 ){

    /*(*j1).listeJetons[0]= nouveauJeton(4, 4, j1->couleur, jeu);
    (*j1).listeJetons[1]= nouveauJeton(5, 5, j1->couleur, jeu);
    (*j2).listeJetons[0]= nouveauJeton(4, 5, j2->couleur, jeu);
    (*j2).listeJetons[1]= nouveauJeton(5, 4, j2->couleur, jeu);*/

    j1->first = createJetonJoueur(jeu,4, 4, j1);
    j1->first->next = createJetonJoueur(jeu,5, 5, j1);
 
    j2->first = createJetonJoueur(jeu,5, 4, j2);
    j2->first->next = createJetonJoueur(jeu,4, 5, j2);

    jeu->joueur1=j1;
    jeu->joueur2=j2;
}

Jeu nouveauJeu(){
    Jeu newJeu;
    return newJeu;
}

void ExitJeu(char coordonnees[2]){
    if(coordonnees[0] == 'q' || coordonnees[1] == 'q'){
        exit(0);
    }
}