#include <iostream>
using namespace std;
#include <cstring> 
#include "structures.h"
#include "./joueur.h"
#include "./jeton.h"
#include "./jeu.h"

int main()
{
    /** Initialisation des variables du jeu **/
	Jeu jeu;
	int IsWhite = 0;
	int nbTours = 0; 
	Joueur j1 = nouveauJoueur(&IsWhite);
    Joueur j2 = nouveauJoueur(&IsWhite);
    // synchronisation des éléments Joueur de la struct Jeu aux structures Joueur
    jeu.joueur1 = &j1;
	jeu.joueur2 = &j2;
    // initialisation de pointeurs sur Joueur
    Joueur* joueurActif;
    Joueur* joueurAdverse;
    
    initJeu(&jeu, &j1, &j2);

    Jeton* curseurJ1 = j1.first; 
    Jeton* curseurJ2 = j2.first;

    affichePlateau(jeu);

    for (int i = 0; i < 4; ++i)
    {

	    
	    /** PLACEMENT DES JETONS - DÉBUT JEU **/
	    joueurActif = WhoIsPlaying(&jeu, &nbTours);
	    joueurAdverse = WhoIsNotPlaying(&jeu, &nbTours);
	    cout << "joueurAdverse : " << joueurAdverse->nom << " " << joueurAdverse->couleur << endl;
	    PlaceUnJeton(&jeu,&nbTours,joueurActif, joueurAdverse);
	    // Vérification enregistrement jetons dans le joueur 
	    curseurJ1 = joueurActif->first; // current, iterator
    	curseurJ2 = joueurAdverse->first;
	    while(curseurJ1 != NULL){
	    	cout << curseurJ1->colonne << " " << curseurJ1->ligne << " "  << curseurJ1->couleur << endl;
	    	curseurJ1 = curseurJ1->next;
	    }
	    while(curseurJ2 != NULL){
	    	cout << curseurJ2->colonne << " " << curseurJ2->ligne << " "  << curseurJ2->couleur << endl;
	    	curseurJ2 = curseurJ2->next;
	    }
	    affichePlateau(jeu);
	    cout << "nbJetons " << joueurActif->nom << " : " <<  joueurActif->nbJetons << endl;
	    cout << "nbJetons " << joueurAdverse->nom << " : " << joueurAdverse->nbJetons << endl;
	}
}