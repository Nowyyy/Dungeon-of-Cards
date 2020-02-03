## variables
^ = main.o initialisation_sdl_fonctions.o main_menu_screen.o
@ = main
LIBS = -lSDL2_ttf -o
SDL = `sdl2-config --cflags --libs`


## preprocessing, compiling, assembling, linking
$@ : $^
	gcc $^ $(SDL) $(LIBS) $@

%o : %c
	gcc $*.c -c



## Nettoyage fichiers temporaires
clean : 
	rm *.o $@
