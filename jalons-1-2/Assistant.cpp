//[PROJET S1] Jalon 3: Assistant

#include <iostream>
using namespace std;
#include <cstring> 
#include <stdlib.h>
#include "structures.h"
#include "./jeton.h"
#include "./Assistant.h"


bool estDejaPresent(coordonnees placements[], int x, int y, int nb_case)//pour ne pas mettre deux fois la même case dans la liste des cases accessibles
{   for(int i = 0 ; i<nb_case; i++)
    {
        if( (placements->x == x) && (placements->y == y) )
        {
            return true;
        }
        
    }
    
    return false;
}

void insereCase(coordonnees *placements, int x, int y, int nb_case) //rajoute une case à la liste des cases accessibles 
{
    coordonnees  *new_case;
    new_case=(coordonnees*) malloc (sizeof(coordonnees));
    if (new_case==0) 
    {
       cout << "Memory run out." << endl ;
       exit(1);
    }
    new_case->x=x;
    new_case->y=y;
    placements[nb_case] = *new_case;

}

void assistant_Jeton(Jeu *jeu, Jeton *jeton, coordonnees* placements, int* nb_case)
{
    char couleur = jeton->couleur;

    char couleurAdverse;
    if(couleur=='b')//obligé car il y a en vrai trois couleurs ('b','w',' ')
    {
        couleurAdverse = 'w';
        }
    else
    {
        couleurAdverse = 'b';
    }

    int ligne=jeton->ligne;
    int colonne=jeton->colonne;

// coordonnées des jetons autours du placement sélectionné
    int coordonneesX, coordonneesY;
    // boucles for imbriquées pour vérifier autour de l'emplacement la présence de pion adverse
    for (int col = -1; col < 2; ++col)
    {
        for (int l = -1; l < 2; ++l)
        {
            coordonneesY = colonne + col;
            coordonneesX = ligne + l; 
            if((*jeu).plateau[coordonneesY][coordonneesX].couleur == couleurAdverse)
            {}
                // on vérifie s'il n'y a pas un autre pion adverse qui suit le pion détecté précédemment
                while((*jeu).plateau[coordonneesY][coordonneesX].couleur == couleurAdverse)
                {
                    coordonneesY = coordonneesY+col;
                    coordonneesX = coordonneesX + l;
                }

                if (estCaseVide(jeu,coordonneesX,coordonneesY) && estDejaPresent(placements,coordonneesX,coordonneesY,*nb_case)==false)
                {
                    insereCase(placements,coordonneesX,coordonneesY, *nb_case);
                    (*nb_case)++;
                }
            }
        }
    }
}

void afficheListeCoordonnees(coordonnees placements[], int nb_case)
{//conversion
    cout <<"[ ";
    char lettreConvert[9] = "ABCDEFGH";
    for (int count =0; count<nb_case; count++)
    {
        for (int i = 0; i < 8; ++i)
        {
            if(placements[count].y==i+1)
            {
                cout << lettreConvert[i] << placements[count].x<< " ";
            }
        }
    }
    cout <<"]"<<endl;
}
        
void assistant(Jeu *jeu, Joueur *joueurActif) 
{   
    //initialisation :    
    Jeton* current=joueurActif->first;
    int nb_case =0;
    int MAXPLACEMENTS = 64;
    coordonnees placements[MAXPLACEMENTS];
//    placements* =(coordonnees*) malloc(MAXPLACEMENTS * sizeof(coordonnees));
    
    while(current)
    {
        assistant_Jeton(jeu, current,placements, &nb_case);   
        current=current->next;
    }
    afficheListeCoordonnees(placements, nb_case);

}
