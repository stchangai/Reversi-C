#include <iostream>
using namespace std;
#include <cstring> 
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"
#include "./joueur.h"
#include "./jeton.h"
#include "./jeu.h"
#include "./AI.h"
#include "./assistant.h"

int main()
{
	Jeu jeu;
	int IsWhite = 0;
	int nbTours = 0; 
    char typeOfGame;

	Joueur j1;
    Joueur j2;
    typeOfGame = ChooseYourGame(&j1, &j2, &IsWhite); //typeOfGame = 'c' pour computer, 'p' pour person/people 
    jeu.joueur1 = &j1;
	jeu.joueur2 = &j2;

    Joueur* joueurActif;
    Joueur* joueurAdverse;
    //int placementAI[MAXPLACEMENT];

    // creation des premiers jetons de chaque joueur
    j1.first = createJetonJoueur(&jeu,4, 4, &j1);
    j1.first->next = createJetonJoueur(&jeu,5, 5, &j1);
 
    j2.first = createJetonJoueur(&jeu,5, 4, &j2);
    j2.first->next = createJetonJoueur(&jeu,4, 5, &j2);


    Jeton* curseurJ1 = j1.first; 
    Jeton* curseurJ2 = j2.first;

    //on enregistre les nouveaux jetons des joueurs dans les joueurs de l'objet Jeu
    jeu.joueur1 = &j1;
	jeu.joueur2 = &j2;

 	do{
        affichePlateau(jeu);
        // PLACEMENT DES JETONS - DÉBUT JEU
        joueurActif = WhoIsPlaying(&jeu, &nbTours);
        joueurAdverse = WhoIsNotPlaying(&jeu, &nbTours);
        cout << "joueurAdverse : " << joueurAdverse->nom << " " << joueurAdverse->couleur << endl;
        switch(typeOfGame){
            case 'p':
                    GameOneVsOne(&jeu,&nbTours,joueurActif,joueurAdverse, curseurJ1, curseurJ2);
                    break;
            case 'c':
                //on part du principe que l'AI sera toujours le joueur n°2
                    if(joueurActif->couleur == j2.couleur){
                         GameOneVsComputer(&jeu,joueurActif,joueurAdverse);
                    }
                    else if(joueurActif->couleur == j1.couleur){
                         GameOneVsOne(&jeu,&nbTours,joueurActif,joueurAdverse, curseurJ1, curseurJ2);
                    }
                    break;
        }
        cout << "nbJetons " << joueurActif->nom << " : " <<  joueurActif->nbJetons << endl;
        cout << "nbJetons " << joueurAdverse->nom << " : " << joueurAdverse->nbJetons << endl;
    }while(!PlateauRempli(jeu));
    affichePlateau(jeu);
    return 0;
}