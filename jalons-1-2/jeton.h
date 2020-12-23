// jeton.h
// [PROJET S1] C++

void PlaceUnJeton(Jeu *jeu,int *nbTours, Joueur *joueurActif, Joueur *joueurAdverse);

Jeton* createJetonJoueur(Jeu *jeu,int ligne, int colonne, Joueur *joueur);

void DeleteJetonJoueur(Jeu *jeu, int ligne, int colonne, Joueur *joueur);

bool IsJetonCorrect(Jeu *jeu, int colonne, int ligne, Joueur *joueurActif,Joueur *joueurAdverse);

bool estCaseVide(Jeu *jeu,int colonne,int ligne);
