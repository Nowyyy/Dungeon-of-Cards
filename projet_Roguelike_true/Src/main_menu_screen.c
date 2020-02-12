/** 
* \file main_menu_screen.c
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 30/01/2020
* \version 0.1

* \brief Gère toute la partie représentant le menu principal du jeu

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"


/**
* \fn deplacement_rectangle_selection
* \param jouer, le rectangle contenant le texte "Commencer partie"
* \param charger, le rectangle contenant le texte "Charger partie"
* \param quitter, le rectangle contenant le texte "Quitter"
* \param *rect_sel, le rectangle de sélection permettant de sélectionner une option

* \brief Permet de déplacer d'option en option le rectangle de sélection

* \return retourne False pour fermer la fenetre, True pour la garder  ouverte
*/
int deplacement_rectangle_selection(SDL_Rect jouer, SDL_Rect charger, SDL_Rect quitter, SDL_Rect **rect_sel, int *etat){

	SDL_Event event;

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		if(event.type == SDL_KEYDOWN){	//touche enfoncée
			if(event.key.keysym.sym == SDLK_DOWN){
				if((*rect_sel)->y != quitter.y){//on n'est pas sur la dernière option, on peut descendre
					if((*rect_sel)->y == jouer.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = charger.y - RECT_SELECT_Y_DIFF;
					}
					else if((*rect_sel)->y == charger.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = quitter.y - RECT_SELECT_Y_DIFF;
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_UP){
				if((*rect_sel)->y != jouer.y){//on n'est pas sur la premiere option, on peut monter
					if((*rect_sel)->y == charger.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = jouer.y - RECT_SELECT_Y_DIFF;
					}
					else if((*rect_sel)->y == quitter.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = charger.y - RECT_SELECT_Y_DIFF;
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == jouer.y - RECT_SELECT_Y_DIFF){
					*etat = labyrinthe;
				}
				else if((*rect_sel)->y == quitter.y - RECT_SELECT_Y_DIFF){
					return FALSE;
				}
				else if((*rect_sel)->y == charger.y - RECT_SELECT_Y_DIFF){
					//*etat = charger_partie;
				}
			}
		}

		if(event.type == SDL_QUIT)//croix de la fenetre
			return FALSE;
	}

	return TRUE;
}

/**
* \fn affichage_menu

* \param *rendu, le rendu sur lequel on dessine
* \param *jouer_text la texture pour le texte "Commencer partie"
* \param *charger_text la texture pour le texte "Charger partie"
* \param *quitter_text la texture pour le texte "Quitter"
* \param jouer_rect le rectangle pour le texte "Commencer partie"
* \param jouer_rect le rectangle pour le texte "Charger partie"
* \param quitter_rect le rectangle pour le texte "Quitter"
* \param rect_sel le rectangle de sélection

* \brief Affiche sur le rendu les différentes textures et rectangles passés en paramètre

*/
void affichage_menu(SDL_Renderer *rendu, SDL_Texture *jouer_text, SDL_Texture *charger_text, SDL_Texture *quitter_text, SDL_Rect *rect_sel, SDL_Rect jouer_rect, SDL_Rect charger_rect, SDL_Rect quitter_rect){

	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	SDL_SetRenderDrawColor(rendu, 255,255,255,255); //couleur blanche pour dessiner le rectangle_selection

	SDL_RenderDrawRect(rendu, rect_sel);

	//affichages des textes
	SDL_RenderCopy(rendu, jouer_text, NULL, &jouer_rect);
	SDL_RenderCopy(rendu, charger_text, NULL, &charger_rect);
	SDL_RenderCopy(rendu, quitter_text, NULL, &quitter_rect);

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}




/**
* \fn main_menu
* \param *continuer, permet de savoir si le joueur souhaite quitter le jeu ou non
* \param *etat, représente l'écran dans lequel on est, actuellement me menu du jeu
* \param *rendu, le rendu que l'on utilise pour dessiner à l'écran
* \param *police, la police utilisée pour écrire sur l'écran

* \brief gère l'affichage à l'écran du menu principal, permet de choisir entre différentes options (jouer, charger, quitter)
*/ 
void main_menu(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police){

	SDL_Rect jouer_text, charger_text, quitter_text;
	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));
	SDL_Texture *jouer_texture, *charger_texture, *quitter_texture;

	int x_jouer = WIN_WIDTH / 2-175, x_charger = WIN_WIDTH / 2- 150, x_quitter = WIN_WIDTH / 2 - 100;
	int y_jouer = WIN_HEIGHT * 0.4, y_charger = WIN_HEIGHT * 0.6, y_quitter = WIN_HEIGHT * 0.8;

	char jouer[] = "Commencer une partie", charger[] = "Charger une partie", quitter[] = "Quitter le jeu";

	//On créé les textures qui contiendront les textes
	get_text_and_rect(rendu, x_jouer, y_jouer, jouer, police, &jouer_texture, &jouer_text);
	get_text_and_rect(rendu, x_charger, y_charger, charger, police, &charger_texture, &charger_text);
	get_text_and_rect(rendu, x_quitter, y_quitter, quitter, police, &quitter_texture, &quitter_text);

	rectangle_selection->x = jouer_text.x - RECT_SELECT_X_DIFF;
	rectangle_selection->y = jouer_text.y - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = jouer_text.w +100;
	rectangle_selection->h = jouer_text.h +50;

	while(*continuer && *etat == mainMenu){

		
		affichage_menu(rendu, jouer_texture, charger_texture, quitter_texture, rectangle_selection, jouer_text, charger_text, quitter_text);

		*continuer = deplacement_rectangle_selection(jouer_text, charger_text, quitter_text, &rectangle_selection, etat);

	}

	free(rectangle_selection);

	SDL_DestroyTexture(jouer_texture);
	SDL_DestroyTexture(charger_texture);
	SDL_DestroyTexture(quitter_texture);
}