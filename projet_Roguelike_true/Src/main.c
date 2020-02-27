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
#include "sauvegardefonc.h"



int main(int argc, char* args[]){

//************************* DECLARATION VARIABLES************************************************************

	SDL_Window *window;
	SDL_Renderer *rendu;

	TTF_Font *police = NULL;

	int continuer = 1, etat = mainMenu/*labyrinthe*/;
	int result = 0;
	int flags = MIX_INIT_MP3;

	perso_t pers;
	carte_t *cartes;

	//On initialise les samples et musiques utilisés dans le jeu
	const char *MOVE = "../Sound/menu_move.wav";
	const char *SELECT = "../Sound/menu_select.wav";
	const char *CHANGE = "../Sound/laby_change.wav";
	const char *FOOT = "../Sound/footstep.wav";
	const char *GAMEOVERFRAME = "../Sound/gameover_frame.wav";

	const char *MENU = "../Sound/menu_song.mp3";
	const char *LVL1 = "../Sound/level1.mp3";
	const char *GAMEOVER = "../Sound/gameover.mp3";

	//On charge les samples et musiques dans des variables
	Mix_OpenAudio(44100, AUDIO_S16SYS,6, 4096);
	Mix_AllocateChannels(6);
	Mix_Chunk *move = Mix_LoadWAV(MOVE);
	Mix_Chunk *select = Mix_LoadWAV(SELECT);
	Mix_Chunk *change_salle = Mix_LoadWAV(CHANGE);
	Mix_Chunk *footsteps = Mix_LoadWAV(FOOT);
	Mix_Chunk *gameOverFrame = Mix_LoadWAV(GAMEOVERFRAME);

	Mix_Music *level1 = Mix_LoadMUS(LVL1);
	Mix_Music *music = Mix_LoadMUS(MENU);
	Mix_Music *gameOverMusic = Mix_LoadMUS(GAMEOVER);



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
							Mix_VolumeChunk(change_salle, 128);
							Mix_VolumeChunk(footsteps, 64);
							Mix_VolumeChunk(gameOverFrame, 32);

							Mix_VolumeMusic(24);

						}

					}
//************************* BOUCLE DE JEU ********************************************************************

					while(continuer){

						if(etat == mainMenu){
							if(Mix_PlayingMusic() == 0){
								Mix_PlayMusic(music, 1);
							}
							main_menu(&continuer, &etat, rendu, police, select, move, music);

							if(etat == labyrinthe){
								//initialise_deck_cartes(cartes);
								initialise_personnage(&pers);
								saveperso(&pers);
							}
						}
						else if (etat == labyrinthe){
							//tout ce qui sera relatif à l'explo dans le laby
							Mix_PauseMusic();
							Mix_PlayMusic(level1, 1);
							boucle_labyrinthe(&continuer, &etat, rendu, change_salle, footsteps, gameOverMusic, gameOverFrame, &pers, cartes);
							Mix_HaltMusic();
							Mix_VolumeMusic(24);
						}
						else if(etat == charger_partie){
							//charge les données du joueurs afin qu'il reprenne là où il s'était arrêté
							menu_charger_partie(&continuer, &etat, rendu, police, select, move, &pers, cartes);
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

	//On libère toutes les variables de son
	Mix_FreeChunk(select);
	Mix_FreeChunk(move);
	Mix_FreeChunk(change_salle);
	Mix_FreeChunk(footsteps);
	Mix_FreeChunk(gameOverFrame);

	Mix_FreeMusic(music);
	Mix_FreeMusic(level1);
	Mix_FreeMusic(gameOverMusic);
	Mix_CloseAudio();


	printf("Tout est fermé\n");//affiche dans la console

	return 0;
}
