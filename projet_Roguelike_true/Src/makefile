## variables
^ = main.o initialisation_sdl_fonctions.o main_menu_screen.o salle.o personnage.o labyrinthe.o chargement.o musique.o fonctions.o sauvegardefonc.o clavier.o
@ = main
LIBS = -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o
SDL = `sdl2-config --cflags --libs`


## preprocessing, compiling, assembling, linking
$@ : $^
	gcc -g $^ $(SDL) $(LIBS) $@

%o : %c
	gcc $*c -c



## Cleaning temps
clean :
	rm *.o
