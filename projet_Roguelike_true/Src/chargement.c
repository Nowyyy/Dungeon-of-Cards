/**
* \file chargement.c
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 18/02/2020
* \version 0.1

* \brief Gère toute la partie concernant le chargement de partie

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"
#include "sauvegardefonc.h"
#include "personnage.h"


/**
* \fn affichage_chagrer_partie

* \param*rendu, le renderer sur lequel on dessine
* \param rect_sel, le rectangle de sélection du menu
* \param *charger_texture la texture pour le texte "Charger partie"
* \param *retour_texture la texture pour le texte "Quitter"
* \param charger_rect le rectangle pour charger une sauvegarde
* \param retour_rect le rectangle pour le texte "retour"

* \brief Affiche sur le rendu les différentes textures et rectangles passés en paramètre

*/
void afficher_chagrer_partie(SDL_Renderer *rendu, SDL_Rect rect_sel, SDL_Texture *charger_texture, SDL_Rect charger_rect, SDL_Texture *retour_texture, SDL_Rect retour_rect){


	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	SDL_SetRenderDrawColor(rendu, 255,255,255,255); //couleur blanche pour dessiner le rectangle_selection

	SDL_RenderDrawRect(rendu, &rect_sel);

	SDL_RenderCopy(rendu, charger_texture, NULL, &charger_rect);
	SDL_RenderCopy(rendu, retour_texture, NULL, &retour_rect);

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}



/**
* \fn deplacement_rectangle_selection

* \param *etat, permet de changer l'affuchage selon l'écran dans lequel se trouve le jeu
* \param charger_rect, le rectangle contenant le texte relatif à la sauvegarde
* \param retour_rect, le rectangle contenant le texte "retour", pour retourner au menu principal
* \param **rect_sel, le rectangle de sélection permettant de sélectionner une option

* \brief Permet de déplacer d'option en option le rectangle de sélection

* \return retourne False pour fermer la fenetre, True pour la garder  ouverte
*/
int deplacement_rectangle_selection_charger(int *etat, SDL_Rect charger_rect, SDL_Rect retour_rect, SDL_Rect **rect_sel, Mix_Chunk *select, Mix_Chunk *move){

	SDL_Event event;

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		if(event.type == SDL_KEYDOWN){	//touche enfoncée
			if(event.key.keysym.sym == SDLK_DOWN){
				if((*rect_sel)->y != retour_rect.y){//on n'est pas sur la dernière option, on peut descendre
					if((*rect_sel)->y == charger_rect.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = retour_rect.y - RECT_SELECT_Y_DIFF;
						Mix_PlayChannel(0, move, 1);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_UP){
				if((*rect_sel)->y != charger_rect.y){//on n'est pas sur la premiere option, on peut monter
					if((*rect_sel)->y == retour_rect.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = charger_rect.y - RECT_SELECT_Y_DIFF;
						Mix_PlayChannel(0, move, 1);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == charger_rect.y - RECT_SELECT_Y_DIFF){
					*etat = labyrinthe;
					Mix_PlayChannel(1, select, 1);
				}
				else if((*rect_sel)->y == retour_rect.y - RECT_SELECT_Y_DIFF){
					*etat = mainMenu;
					Mix_PlayChannel(1, select, 1);
				}
			}
		}

		if(event.type == SDL_QUIT)//croix de la fenetre
			return FALSE;
	}

	return TRUE;
}






/**
* \fn menu_charger_partie

* \param *continuer, pointeur sur un int permettant de savoir si le joueur veut quitter le jeu
* \param *etat, pointeur sur un int permettant de connaitre le prochain écran auquel le joueur veut accèder
* \param *rendu, le renderer sur lequel on dessine
* \param *police, la police d'écriture pour TTF
* \param *select, don't know
* \param *move, don't know
* \param *pers, la structure du personnage

* \brief Permet d'afficher et de récupèrer une sauvegarde éventuelle puis de lancer le jeu 

*/
void menu_charger_partie(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police, Mix_Chunk *select, Mix_Chunk *move, perso_t *pers, carte_t *cartes){

	SDL_Rect retour_rect, charger_rect;
	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

	SDL_Texture *retour_texture, *charger_texture;

	char retour_text[] = "Retourner au menu principal", *charger_text = malloc(sizeof(char)* 500);
	char intermediaire[50];

	int x_retour = WIN_WIDTH * 0.30, y_retour = WIN_HEIGHT * 0.75;
	int x_charger = WIN_WIDTH * 0.30, y_charger = WIN_HEIGHT * 0.50;

	if(!save_existe()){

		charger_text = strcpy(charger_text, "Pas de sauvegarde trouvee");
		initialise_personnage(pers);
		//initialise_deck_cartes(cartes);
	}
	else{
		readperso(pers);
		readcarte(cartes);
		sprintf(intermediaire,"Etage %d, Points de vie %d", pers->etage, pers->pv);
		charger_text = strcpy(charger_text, intermediaire);
	}

	//On créé les textures qui contiendront les textes
	get_text_and_rect(rendu, x_charger, y_charger, charger_text, police, &charger_texture, &charger_rect);
	get_text_and_rect(rendu, x_retour, y_retour, retour_text, police, &retour_texture, &retour_rect);

	rectangle_selection->x = x_charger - RECT_SELECT_X_DIFF;
	rectangle_selection->y = y_charger - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = charger_rect.w + 100;
	rectangle_selection->h = charger_rect.h + 50;

	while(*continuer && *etat == charger_partie){

		afficher_chagrer_partie(rendu, *rectangle_selection, charger_texture, charger_rect, retour_texture, retour_rect);

		*continuer = deplacement_rectangle_selection_charger(etat, charger_rect, retour_rect, &rectangle_selection, select, move);
	}

	free(rectangle_selection);
	free(charger_text);
	SDL_DestroyTexture(retour_texture);
	SDL_DestroyTexture(charger_texture);
}
