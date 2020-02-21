/**
* \file main.c
* \date 30/01/2020
* \author {Tudoret Aurélien, Jourry Axel, Malabry Thomas, Marin Timothée}
* \version 0.1
* \brief Le projet de deuxième année de licence, un roguelike/rpg

*/

// gcc main.c initialisation_sdl_fonctions.c main_menu_screen.c salle.c personnage.c labyrinthe.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o main
//pour compiler sous windows avec sdl2, sdl2  ttf et sdl2 image installés

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"
#include "main_menu_screen.h"
#include "salle.h"
#include "personnage.h"
#include "labyrinthe.h"
#include "chargement.h"
#include "musique.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

int main(int argc, char* args[]){

//************************* DECLARATION VARIABLES************************************************************

	SDL_Window *window;
	SDL_Renderer *rendu;

	TTF_Font *police = NULL;

	int continuer = 1, etat = mainMenu/*labyrinthe*/;
	int result = 0;
	int flags = MIX_INIT_MP3;

	//On initialise le sample joué dans le menu principal
	const char *MOVE = "../Sound/menu_move.wav";
	const char *SELECT = "../Sound/menu_select.wav";
	const char *MENU = "../Sound/menu_song.mp3";


	//On charge le sample dans une variable
	Mix_OpenAudio(44100, AUDIO_S16SYS,6, 4096);
	Mix_AllocateChannels(6);
	Mix_Chunk *move = Mix_LoadWAV(MOVE);
	Mix_Chunk *select = Mix_LoadWAV(SELECT);
	Mix_Music *music = Mix_LoadMUS(MENU);




//************************* INITIALISATION SDL + TTF ********************************************************

	if(initialisation_sdl(&window, &rendu)){
		printf("Erreur création fenetre ou rendu\n");
	}
	else{

		if(init_or_quit_ttf(1))//initialise TTF (permet s d'écrire sur l'écran)
			printf("Erreur init TTF\n");
		else{

			if((IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG){
				printf("Erreur init sdl_image\n");
			}
			else{

				police = TTF_OpenFont(FONT_PATH, 50);//charge la police pour écrire a l'ecran

				if(!police)
					printf("Erreur police\n");
				else{

					if (SDL_Init(SDL_INIT_AUDIO) < 0) {
			        printf("Failed to init SDL\n");
			        exit(1);
			    }
					else{


						if (flags != (result = Mix_Init(flags))) {
								printf("Could not initialize mixer (result: %d).\n", result);
								printf("Mix_Init: %s\n", Mix_GetError());
								exit(1);
						}
						else {

							//On met le volume à fond pour couvrir par dessus la musique
							Mix_VolumeChunk(move, 128);
							Mix_VolumeChunk(select, 128);
							Mix_VolumeMusic(64);
						}

					}
//************************* BOUCLE DE JEU ********************************************************************

					while(continuer){

						if(etat == mainMenu){
							if(Mix_PlayingMusic() == 0){
								Mix_PlayMusic(music, 1);
							}
							main_menu(&continuer, &etat, rendu, police, select, move, music);

						}
						else if (etat == labyrinthe){
							//tout ce qui sera relatif à l'explo dans le laby
							Mix_PauseMusic();
							boucle_labyrinthe(&continuer, &etat, rendu);

						}
						else if(etat == charger_partie){
							//charge les données du joueurs afin qu'il reprenne là où il s'était arrêté
							menu_charger_partie(&continuer, &etat, rendu, police, select, move);
						}
					}
				}
			}
		}
	}

//************************* FERMETURES ***********************************************************************
	IMG_Quit();
	TTF_CloseFont(police); //on libère la police
	quit_sdl(&rendu, &window);
	SDL_Quit();
	init_or_quit_ttf(0);//quitte TTF
	Mix_FreeChunk(select);
	Mix_FreeChunk(move);
	Mix_FreeMusic(music);
	Mix_CloseAudio();


	printf("Tout est fermé\n");//affiche dans la console

	return 0;
}
