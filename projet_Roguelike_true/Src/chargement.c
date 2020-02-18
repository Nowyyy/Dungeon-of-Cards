/** 
* \file chargement.c
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 18/02/2020
* \version 0.1

* \brief Gère toute la partie concernant le chargement de partie

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"



void menu_charger_partie(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police){

	SDL_Rect retour_rect, charger_rect;
	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

	SDL_Texture *retour_texture, *charger_texture;

	char retour_text[] = "Retourner au menu principal", *charger_text;

	int x_retour = WIN_WIDTH * 0.75, y_retour = WIN_HEIGHT * 0.75;
	int x_charger = WIN_WIDTH * 0.50, y_charger = WIN_HEIGHT * 0.50;

	if(!save_existe()){

		strcpy(charger_text, "Pas de sauvegarde trouvée");
	}
	else{
		//lire info pour afficher
	}

	//On créé les textures qui contiendront les textes
	get_text_and_rect(rendu, x_charger, y_charger, charger_text, police, &charger_texture, &charger_rect);
	get_text_and_rect(rendu, x_retour, y_retour, retour_text, police, &retour_texture, &retour_rect);

	rectangle_selection->x = x_charger - RECT_SELECT_X_DIFF;
	rectangle_selection->y = y_charger - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = charger_rect.w + 100;
	rectangle_selection->h = charger_rect.h + 50;





	free(rectangle_selection);
	free(charger_text);
	SDL_DestroyTexture(retour_texture);
	SDL_DestroyTexture(charger_texture);
}