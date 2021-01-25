# makefile
# [PROJET S1] C++ 
#Jeu complet

play:	InterfaceJeu.o Jeton.o Joueur.o AI.o Assistant.o main.o
	gcc -o init InterfaceJeu.o Jeton.o Joueur.o AI.o Assistant.o main.o -Wall -lstdc++

Joueur.o: Joueur.cpp structures.h joueur.h jeton.h assistant.h
	gcc -c Joueur.cpp -Wall

InterfaceJeu.o: InterfaceJeu.cpp structures.h jeu.h jeton.h joueur.h
	gcc -c InterfaceJeu.cpp -Wall

Jeton.o: Jeton.cpp structures.h jeton.h jeu.h
	gcc -c Jeton.cpp -Wall

AI.o: AI.cpp structures.h AI.h jeu.h joueur.h jeton.h
	gcc -c AI.cpp -Wall

Assistant.o : Assistant.cpp assistant.h structures.h jeu.h jeton.h
	gcc -c Assistant.cpp -Wall

main.o: main.cpp structures.h jeu.h joueur.h jeton.h Ai.h assistant.h
	gcc -c main.cpp -Wall

clean :
	rm -f *.o