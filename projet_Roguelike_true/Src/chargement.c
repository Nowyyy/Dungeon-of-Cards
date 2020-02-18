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

	char retour_text[] = "Retourner au menu principal", pas_de_save[] = "Pas de sauvegarde trouvée.";




	free(rectangle_selection);
}