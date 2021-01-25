// structure.h
//[PROJET S1] C++

//-----------------------
struct Jeton
{
    char couleur;// 'w' pour blanc; 'b' pour noir;
    int ligne;
    int colonne; //pour la suite ce sera surement plus simple que les 2 soient des entiers plutot que un entier et une lettre 
    Jeton* next;
};

struct Joueur
{
    char nom[20];
    //Jeton listeJetons[64] ;
    Jeton* first;
    int nbJetons;
    char couleur; //on le rajoute pour pouvoir relier le joueur avec ses jetons 
                    //(peut être pas utile)
};

struct Jeu
{
    Joueur *joueur1;
    Joueur *joueur2;
    Jeton plateau[8][8];// plateau = (Jeton*) malloc(8*8*sizeof(Jeton))
};

typedef struct coordonnees{int y;int x;}coordonnees;

//----------------------------