// Assistant.h
// [PROJET S1] C++

bool estDejaPresent(coordonnees placements[], int x, int y,int nb_case);

void insereCase(coordonnees placements[], int x, int y, int nb_case);

//rajoute les cases accessibles par un jeton
void assistant_Jeton(Jeu *jeu, Jeton *jeton, coordonnees *placements,int *nb_case);

void afficheListeCoordonnees(coordonnees tab_case[], int nb_case);

//renvoie toutes les cases accessibles par le joueur
int assistant(Jeu *jeu, Joueur *joueurActif);