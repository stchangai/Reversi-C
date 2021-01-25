# jeu.mak - JALONS 0,1,2
# [PROJET S1] C++ 
#Initialisation de début de jeu + Placement jetons + capture jetons + comptage jetons

play:	InterfaceJeu.o Jeton.o Joueur.o Assistant.o main.o 
	gcc -o init InterfaceJeu.o Jeton.o Joueur.o Assistant.o main.o -Wall -lstdc++

InterfaceJeu.o: InterfaceJeu.cpp structures.h jeu.h jeton.h
	gcc -c InterfaceJeu.cpp -Wall

Jeton.o: Jeton.cpp structures.h jeton.h
	gcc -c Jeton.cpp -Wall

Joueur.o: Joueur.cpp structures.h joueur.h
	gcc -c Joueur.cpp -Wall

Assistant.o: Assistant.cpp structures.h jeton.h Assistant.h
	gcc -c Assistant.cpp -Wall

main.o: main.cpp structures.h jeu.h joueur.h jeton.h
	gcc -c main.cpp -Wall

clean :
	rm -f *.o