## variables
^ = main.o initialisation_sdl_fonctions.o main_menu_screen.o salle.o personnage.o labyrinthe.o chargement.o fonctions.o combat_tour_par_tour.o sauvegardefonc.o etage_final.o clavier.o ennemi.o coffre.o confirmer_nouveau.o animation.o
@ = ../bin/DungeonOfCards
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o
SDL = `sdl2-config --cflags --libs`


## preprocessing, compiling, assembling, linking
$@ : $^
	gcc -g -Wall $^ $(SDL) $(LIBS) $@

%o : %c
	gcc $*c -c



## Cleaning temps
clean :
	rm *.o && rm ../Sauvegarde/cartes_deck.txt ../Sauvegarde/cartes_collec.txt && clear

##launch a test

test :
	./../bin/DungeonOfCards
