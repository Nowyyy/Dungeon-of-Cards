all: cartes.o fonctions.o
	gcc cartes.o fonctions.o -o cartes
cartes.o: cartes.c structures.h
	gcc -c cartes.c
fonctions.o: fonctions.c fonctions.h
	gcc -c fonctions.c
