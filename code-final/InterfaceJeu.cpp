//[PROJET S1] Jalon 0: affichage du plateau

#include <iostream>
using namespace std;
#include <cstring>
#include "structures.h"
#include "./jeu.h"
#include "./jeton.h"
#include "./joueur.h"

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

// l'utilisateur peut choisir entre jouer contre l'ordinateur ou contre un autre joueur
char ChooseYourGame(Joueur *j1, Joueur *j2, int *IsWhite){
    char playWithAI = 'z'; // random character 
    while(playWithAI != 'n' && playWithAI != 'y'){
        cout << "Voulez vous jouer contre l'Ordinateur ? y/n : ";
        cin >> playWithAI;
    }
    if(playWithAI == 'y'){
        *j1 = nouveauJoueur(IsWhite);
        *j2 = nouveauJoueur(IsWhite, true);
        return 'c'; // 'c' for computer
    }
    else{
        *j1 = nouveauJoueur(IsWhite);
        *j2 = nouveauJoueur(IsWhite);
        return 'p'; // 'p' for person/people
    }
}

bool estCaseVide(Jeu *jeu,int colonne,int ligne){
    Joueur *joueur1 = jeu->joueur1;
    Jeton *current= joueur1->first;
    for(int i=0; i<(joueur1->nbJetons); i++){
        if(current->colonne==colonne && current->ligne==ligne){
            return false;
        }
        else{current=current->next;}
    }

    Joueur *joueur2=jeu->joueur2;
    current=joueur2->first;
    for(int i=0; i<(joueur2->nbJetons); i++){
        if(current->colonne==colonne && current->ligne==ligne){
            return false;
        }
        else{current=current->next;}
    }

    return true;
}

bool PlateauRempli(Jeu jeu){
    Joueur *winner;
    bool estFini = false;
    int totalJetons = jeu.joueur1->nbJetons + jeu.joueur2->nbJetons;
    cout << "nomb total jetons plateau : " << totalJetons << endl;  

    if(totalJetons == 64){
        estFini = true;
    }
    if(estFini){
        if(jeu.joueur1->nbJetons < jeu.joueur2->nbJetons){
            winner = jeu.joueur2;
        }
        else{
            winner = jeu.joueur1;
        }
        cout << "Le plateau est rempli, impossible de continuer la partie ! " << endl;
        cout << "EEET le gagnant de cette partie est... ";
        for (int x=0; x<strlen(winner->nom); x++){
            putchar(toupper(winner->nom[x]));
        }
        cout << endl;
        return true;
    }
    // aucune case n'est vide, le plateau est donc rempli
    return false;
}