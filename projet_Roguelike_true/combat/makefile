all: cartes.o fonctions.o
	gcc cartes.o fonctions.o -o -g	 cartes
cartes.o: cartes.c constantes.h
	gcc -c cartes.c
fonctions.o: fonctions.c fonctions.h
	gcc -c fonctions.c
clean :
	rm *.o
