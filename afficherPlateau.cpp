//[PROJET S1] Jalon 1: affichage du plateau

#include <iostream>
using namespace std;
#include <cstring> 

//-----------------------
struct Jeton
{
    char couleur;// 'w' pour blanc; 'b' pour noir;
    int ligne;
    int colonne; //pour la suite ce sera surement plus simple que les 2 soient des entiers plutot que un entier et une lettre 
};

struct Joueur
{
    char nom[20];
    Jeton listeJetons[64] ;
    int nbJetons;
    char couleur; //on le rajoute pour pouvoir relier le joueur avec ses jetons 
                    //(peut être pas utile)
};

struct Jeu
{
    Joueur joueur1;
    Joueur joueur2;
    Jeton plateau[8][8];// plateau = (Jeton*) malloc(8*8*sizeof(Jeton))
};

//----------------------------


void affichePlateau(Jeu jeu){
    for(int ligne=1;ligne<=8;ligne++){
        //traits horizontaux
        for(int colonne=1 ; colonne<=8;colonne++){
            cout << "+---"; 
        }
        cout << '+'<<endl;

        //traits verticaux
        for(int colonne=1 ; colonne<=8;colonne++){
            char cont=' ';
            if(jeu.plateau[colonne][ligne].couleur=='w'){
                cont='0';
            }
            else{
                if(jeu.plateau[colonne][ligne].couleur=='b'){
                    cont='*';
                }
                cout << '|' << ' ' <<cont <<' ' ;
            }
        }
        cout << '|'<< endl;
    }
}

//crée un nouveau joueur dans la structure Joueur
void nouveauJoueur(Joueur *joueur, char nom[20], int nbJetons, char couleur){
    strcpy(joueur->nom, nom);
 /*   joueur->nom=nom;*/
    joueur->nbJetons = nbJetons;
    joueur->couleur = couleur;
}

void nouveauJeton(Jeton *jeton, int colonne,int ligne, char couleur,Jeu jeu){
    jeton->couleur=couleur;
    jeton->colonne=colonne;
    jeton->ligne=ligne;
    //on met à jour le nombre de jeton du joueur correspondant
    if (couleur== jeu.joueur1.couleur && couleur!=' '){
        jeu.joueur1.nbJetons++;
    }
    else {if(couleur== jeu.joueur2.couleur && couleur!=' '){
        jeu.joueur2.nbJetons++;
        }
    }
    //on ajoute le jeton sur le plateau
    jeu.plateau[colonne][ligne]=*jeton;
}


//initialise le plateau avec les 4 jetons de départ
void initJeu(Jeu *jeu, Joueur *j1, Joueur *j2 ){
    jeu->joueur1=*j1;
    jeu->joueur2=*j2;
    Jeton jeton1;
    Jeton jeton2;
    Jeton jeton3;
    Jeton jeton4;
    nouveauJeton(&jeton1, 3, 3, 'w', *jeu);
    nouveauJeton(&jeton2, 4, 3, 'b', *jeu);
    nouveauJeton(&jeton3, 3, 4, 'b', *jeu);
    nouveauJeton(&jeton4, 4, 4, 'w', *jeu);
}



int main(){
    Jeu jeu;
    Joueur j1;
    Joueur j2;
    nouveauJoueur(&j1,"bernard",0,'w');
    nouveauJoueur(&j2,"bob",0,'b');
    cout<< j1.nom<<endl;
    initJeu(&jeu,&j1,&j2);

/*    affichePlateau(jeu);*/
    cout << (char)jeu.plateau[3][3].couleur;//ca ne marche pas !!
return 0;
}