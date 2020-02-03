/*
* \file main.c
* \date 30/01/2020
* \author Tudoret Aurélien, Jourry Axel, Malabry Thomas, Marin Timothée
* \version 0.1
* \brief Le projet de deuxième année de licence, un roguelike/rpg 

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"
#include "main_menu_screen.h"


int main(void){

//************************* DECLARATION VARIABLES************************************************************

	SDL_Window *window;
	SDL_Renderer *rendu;

	TTF_Font *police = NULL;

	int continuer = 1, etat = mainMenu;

//************************* INITIALISATION SDL + TTF ********************************************************

	if(initialisation_sdl(&window, &rendu)){
		printf("Erreur création fenetre ou rendu\n");
		goto QUIT;
	}

	if(init_or_quit_ttf(1))//initialise TTF (permet s d'écrire sur l'écran)
		goto QUIT;

	police = TTF_OpenFont(FONT_PATH, 50);//charge la police pour écrire a l'ecran

	if(!police)
		printf("Erreur police\n");

//************************* BOUCLE DE JEU ********************************************************************

	while(continuer){

		if(etat == mainMenu){

			main_menu(&continuer, &etat, rendu, police);
			
		}
		else if (etat == labyrinthe){
			//tout ce qui sera relatif à l'explo dans le laby
		}
		else if(etat == tourParTour){
			//le combat tour par tour, le fait de le séparer fera une pause automatique dans
			//toutes les actions qui pourraient se passer dans le laby pendant le combat
		}
		else if(etat == pauseScreen){

			//ecran de pause en jeu tpt ou laby
		}
	}

//************************* FERMETURES ***********************************************************************
FINI:
	TTF_CloseFont(police); //on libère la police
	quit_sdl(&rendu, &window);
QUIT: //quitte la SDL
	SDL_Quit();
	init_or_quit_ttf(0);//quitte TTF

	printf("Tout est fermé\n");//affiche dans la console

	return 0;
}
