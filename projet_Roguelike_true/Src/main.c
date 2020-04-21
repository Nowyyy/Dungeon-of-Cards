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
#include "../include/fonctions.h"
#include "../include/animation.h"
#include "../include/etage_final.h"


/**
*\fn int main(int argc, char* args[])

*\param argc, le nombre d'arguments
*\param args[], le tableau contenant tous les arguments
*\brief Corps principal du jeu

*\return 1 ou 0 si le programme s'est bien exécuté ou non.
*/
int main(int argc, char* args[]){

//************************* DECLARATION VARIABLES************************************************************
	SDL_Window *window;
	SDL_Renderer *rendu;

	srand(time(NULL));

	TTF_Font *police = NULL;

	int continuer = 1, etat = mainMenu/*labyrinthe*/;
	int result = 0;
	int flags = MIX_INIT_MP3;

	init_liste();

	perso_t pers;

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

		if(init_or_quit_ttf(1)){//initialise TTF (permet s d'écrire sur l'écran)
			printf("Erreur init TTF\n");
		}
		else{

			if((IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG){
				printf("Erreur init sdl_image\n");
			}
			else{

				police = TTF_OpenFont(FONT_PATH, 50);//charge la police pour écrire a l'ecran

				if(!police)
					printf("Erreur police\n");
				else{

					if (flags != (result = Mix_Init(flags))) {
						printf("Could not initialize mixer (result: %d).\n", result);
						printf("Mix_Init: %s\n", Mix_GetError());
						exit(1);
					}
					Mix_VolumeMusic(6);


//************************* BOUCLE DE JEU ********************************************************************
					while(continuer){

						if(etat == mainMenu){
							///////////Menu principal
							if(Mix_PlayingMusic() == 0){
								Mix_VolumeMusic(6);
								Mix_PlayMusic(musics[menu], -1);
							}
							main_menu(&continuer, &etat, rendu, police, sounds);

							if(etat == labyrinthe){//cas où une save n'existe pas, on initialise joueur et decks pour lancer la partie directement
								initialise_personnage(&pers);
								readcarte(SAVE_CARTES_NEW_GAME_PATH, DECK);
								readcarte(SAVE_CARTES_NEW_GAME_PATH, COLLEC);
							}
						}
						else if (etat == labyrinthe){
							///////////Exploration du labyrinthe
							saveperso(&pers);
							Mix_HaltMusic();
							animation_niveau(&pers, rendu);
						  	choix_musique(musics, &pers);
						  	savecarte(SAVE_CARTES_DECK_PATH, DECK);
						  	savecarte(SAVE_CARTES_COLLEC_PATH, COLLEC);

						  	if(pers.etage < 5)
								boucle_labyrinthe(&continuer, &etat, rendu, sounds, musics, &pers, police);
							else
								etage_final(rendu, &continuer, &etat, sounds, musics, &pers, police);
						}
						else if(etat == charger_partie){
							///////////charge les données du joueurs afin qu'il reprenne là où il s'était arrêté
							menu_charger_partie(&continuer, &etat, rendu, police, sounds, &pers);
						}
						else if(etat == confirmer_nouveau){
							///////////Affiche un menu pour confirmer l'écrasement de la sauvegarde
							menu_confirmation(&continuer, &etat, rendu, police, sounds, &pers);
							if(etat == labyrinthe){
								initialise_personnage(&pers);
								readcarte(SAVE_CARTES_NEW_GAME_PATH, DECK);
								readcarte(SAVE_CARTES_NEW_GAME_PATH, COLLEC);
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

	init_or_quit_ttf(0);//quitte TTF

	//On libère toutes les variables de son
	free_mixer(musics, sounds);

	quit_sdl(&rendu, &window);
	SDL_Quit();

	detruire_liste(DECK);
	detruire_liste(COLLEC);

	printf("Tout est fermé\n");//affiche dans la console

	return 0;
}
