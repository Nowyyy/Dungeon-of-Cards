/**
* \file main.c
* \date 30/01/2020
* \author {Tudoret Aurélien, Jourry Axel, Malabry Thomas, Marin Timothée}
* \version 0.1
* \brief Le projet de deuxième année de licence, un roguelike/rpg
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/main_menu_screen.h"
#include "../include/salle.h"
#include "../include/personnage.h"
#include "../include/labyrinthe.h"
#include "../include/chargement.h"
#include "../include/sauvegardefonc.h"
#include "../include/confirmer_nouveau.h"
<<<<<<< Updated upstream
#include "../include/fonctions.h"
=======
#include "../include/animation.h"
>>>>>>> Stashed changes



int main(int argc, char* args[]){

//************************* DECLARATION VARIABLES************************************************************

	SDL_Window *window;
	SDL_Renderer *rendu;

	srand(time(NULL));

	TTF_Font *police = NULL;

	int continuer = 1, etat = mainMenu/*labyrinthe*/;
	int result = 0;
	int flags = MIX_INIT_MP3;

	perso_t pers;
	carte_t *cartes = NULL;

	//On initialise les samples et musiques utilisés dans le jeu

	Mix_Chunk *sounds[NB_SON];
	Mix_Music *musics[NB_MUSIC];

	Mix_OpenAudio(44100, AUDIO_S16SYS,6, 4096);
	Mix_AllocateChannels(16);

	init_son(sounds);
	init_music(musics);



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

					}
//************************* BOUCLE DE JEU ********************************************************************

					while(continuer){

						if(etat == mainMenu){
							if(Mix_PlayingMusic() == 0){
								Mix_VolumeMusic(15);
								Mix_PlayMusic(musics[menu], -1);
							}
							main_menu(&continuer, &etat, rendu, police, sounds);

							if(etat == labyrinthe){
								initialise_personnage(&pers);
								readcarte(SAVE_CARTES_CATALOGUE_PATH);
							}
						}
						else if (etat == labyrinthe){
							//tout ce qui sera relatif à l'explo dans le laby
							saveperso(&pers);
							Mix_HaltMusic();
							animation_niveau(&pers, rendu);
							if(pers.etage == 1){
								Mix_VolumeMusic(20);
								Mix_PlayMusic(musics[level1], -1);
							}
							else if(pers.etage == 2){
								Mix_VolumeMusic(80);
								Mix_PlayMusic(musics[level2], -1);
							}
							else if(pers.etage == 3){
								Mix_VolumeMusic(48);

								Mix_PlayMusic(musics[level3], -1);
							}
							else if(pers.etage == 4){
								Mix_VolumeMusic(80);

								Mix_PlayMusic(musics[level4], -1);
							}
							else if(pers.etage == 5){
								Mix_VolumeMusic(20);

								Mix_PlayMusic(musics[level5], -1);
							}
							boucle_labyrinthe(&continuer, &etat, rendu, sounds, musics, &pers, police);
							Mix_HaltMusic();
						}
						else if(etat == charger_partie){
							//charge les données du joueurs afin qu'il reprenne là où il s'était arrêté
							menu_charger_partie(&continuer, &etat, rendu, police, sounds, &pers);
						}
						else if(etat == confirmer_nouveau){
							//Affiche un menu pour confirmer l'écrasement de la sauvegarde
							menu_confirmation(&continuer, &etat, rendu, police, sounds, &pers);
							if(etat == labyrinthe){
								initialise_personnage(&pers);
								readcarte(SAVE_CARTES_CATALOGUE_PATH);
							}
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
	free_mixer(musics, sounds);

	while(!liste_vide())
		oter_elt();


	printf("Tout est fermé\n");//affiche dans la console

	return 0;
}
