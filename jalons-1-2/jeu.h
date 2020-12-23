// jeu.h
// [PROJET S1] C++

//reset jeu
Jeu nouveauJeu();

// initialisation de l'objet Jeu
void initJeu(Jeu *jeu, Joueur *j1, Joueur *j2 );

//Affichage du plateau sur la console avec les jetons que l'objet Jeu contient
//utilisation de cette fonction à chaque tour
void affichePlateau(Jeu jeu);

void ExitJeu(char coordonnees[2]);
