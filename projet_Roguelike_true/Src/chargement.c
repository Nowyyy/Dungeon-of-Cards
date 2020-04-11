/**
*\file chargement.c
*\author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
*\date 18/02/2020
*\version 0.1

*\brief Gère toute la partie concernant le chargement de partie
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/sauvegardefonc.h"
#include "../include/personnage.h"


/**
*\fn void afficher_charger_partie(SDL_Renderer *rendu, SDL_Rect rect_sel, SDL_Texture *charger_texture, SDL_Rect charger_rect, SDL_Texture *retour_texture, SDL_Rect retour_rect, SDL_Texture *message_texture, SDL_Rect message_rect)

*\param*rendu, le renderer sur lequel on dessine
*\param rect_sel, le rectangle de sélection du menu
*\param *charger_texture la texture pour le texte "Charger partie"
*\param charger_rect le rectangle pour charger une sauvegarde
*\param *retour_texture la texture pour le texte "Quitter"
*\param retour_rect le rectangle pour le texte "retour"
*\param message_texture la texture pour le texte "charger une partie ?"
*\param message_rect le rectangle pour le texte "charger une partie ?"


*\brief Affiche sur le rendu les différentes textures et rectangles passés en paramètre
*/
void afficher_charger_partie(SDL_Renderer *rendu, SDL_Rect rect_sel, SDL_Texture *charger_texture, SDL_Rect charger_rect, SDL_Texture *retour_texture, SDL_Rect retour_rect, SDL_Texture *message_texture, SDL_Rect message_rect){


	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	SDL_SetRenderDrawColor(rendu, 255,255,255,255); //couleur blanche pour dessiner le rectangle_selection

	SDL_RenderDrawRect(rendu, &rect_sel);

	SDL_RenderCopy(rendu, charger_texture, NULL, &charger_rect);
	SDL_RenderCopy(rendu, retour_texture, NULL, &retour_rect);
	SDL_RenderCopy(rendu, message_texture, NULL, &message_rect);


	SDL_RenderPresent(rendu);//applique les modifs précédentes
}



/**
*\fn int deplacement_rectangle_selection_charger(int *etat, SDL_Rect charger_rect, SDL_Rect retour_rect, SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON])

*\param *etat, permet de changer l'affuchage selon l'écran dans lequel se trouve le jeu
*\param charger_rect, le rectangle contenant le texte relatif à la sauvegarde
*\param retour_rect, le rectangle contenant le texte "retour", pour retourner au menu principal
*\param **rect_sel, le rectangle de sélection permettant de sélectionner une option
*\param *sounds[NB_SON], tableau contenant les sons

*\brief Permet de déplacer d'option en option le rectangle de sélection

*\return retourne False pour fermer la fenetre, True pour la garder  ouverte
*/
int deplacement_rectangle_selection_charger(int *etat, SDL_Rect charger_rect, SDL_Rect retour_rect, SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON]){

	SDL_Event event;

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		if(event.type == SDL_KEYDOWN){	//touche enfoncée
			if(event.key.keysym.sym == SDLK_DOWN){
				if((*rect_sel)->y != retour_rect.y){//on n'est pas sur la dernière option, on peut descendre
					if((*rect_sel)->y == charger_rect.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = retour_rect.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = retour_rect.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->w = retour_rect.w + 100;
						(*rect_sel)->h = retour_rect.h + 50;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_UP){
				if((*rect_sel)->y != charger_rect.y){//on n'est pas sur la premiere option, on peut monter
					if((*rect_sel)->y == retour_rect.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = charger_rect.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = charger_rect.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->w = charger_rect.w + 100;
						(*rect_sel)->h = charger_rect.h + 50;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == charger_rect.y - RECT_SELECT_Y_DIFF){
					*etat = labyrinthe;
					Mix_PlayChannel(1, sounds[selection], 0);
				}
				else if((*rect_sel)->y == retour_rect.y - RECT_SELECT_Y_DIFF){
					*etat = mainMenu;
					Mix_PlayChannel(1, sounds[selection], 0);
				}
			}
		}

		if(event.type == SDL_QUIT)//croix de la fenetre
			return FALSE;
	}

	return TRUE;
}






/**
*\fn void menu_charger_partie(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police, Mix_Chunk *sounds[NB_SON], perso_t *pers)

*\param *continuer, pointeur sur un int permettant de savoir si le joueur veut quitter le jeu
*\param *etat, pointeur sur un int permettant de connaitre le prochain écran auquel le joueur veut accèder
*\param *rendu, le renderer sur lequel on dessine
*\param *police, la police d'écriture pour TTF
*\param *sounds[NB_SON], tableau contenant les sons
*\param *pers, la structure du personnage

*\brief Permet d'afficher et de récupèrer une sauvegarde éventuelle puis de lancer le jeu
*/
void menu_charger_partie(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police, Mix_Chunk *sounds[NB_SON], perso_t *pers){

	SDL_Rect retour_rect, charger_rect, message_rect;
	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

	SDL_Texture *retour_texture, *charger_texture, *message_texture;

	char retour_text[] = "Retourner au menu principal", *charger_text = malloc(sizeof(char)* 500), message_text[] = "Charger la partie ?";
	char intermediaire[50];

	int x_retour, x_charger, y_retour, y_charger, x_message, y_message;

	x_retour = WIN_WIDTH * 0.30-30;
	y_retour = WIN_HEIGHT * 0.75;

	x_message = WIN_WIDTH * 0.35;
  y_message = WIN_HEIGHT * 0.15;

	SDL_Color color_text={134, 134, 134};

	if(!save_existe()){

		charger_text = strcpy(charger_text, "Pas de sauvegarde trouvee");
		initialise_personnage(pers);
		x_charger = WIN_WIDTH * 0.30;
		y_charger = WIN_HEIGHT * 0.50;
		readcarte(SAVE_CARTES_NEW_GAME_PATH, DECK);
		readcarte(SAVE_CARTES_NEW_GAME_PATH, COLLEC);
	}
	else{
		readperso(pers);
		readcarte(SAVE_CARTES_DECK_PATH, DECK);
		readcarte(SAVE_CARTES_COLLEC_PATH, COLLEC);
		x_charger = WIN_WIDTH * 0.33-15;
		y_charger = WIN_HEIGHT * 0.50;
		sprintf(intermediaire,"Etage %d, Points de vie %d", pers->etage, pers->pv);
		charger_text = strcpy(charger_text, intermediaire);
	}

	//On créé les textures qui contiendront les textes
	get_text_and_rect(rendu, x_charger, y_charger, charger_text, police, &charger_texture, &charger_rect);
	get_text_and_rect(rendu, x_retour, y_retour, retour_text, police, &retour_texture, &retour_rect);
	get_text_and_rect_color(rendu, x_message, y_message, message_text, police, &message_texture, &message_rect, color_text);


	rectangle_selection->x = x_retour - RECT_SELECT_X_DIFF;
	rectangle_selection->y = y_retour - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = retour_rect.w + 100;
	rectangle_selection->h = retour_rect.h + 50;

	while(*continuer && *etat == charger_partie){

		afficher_charger_partie(rendu, *rectangle_selection, charger_texture, charger_rect, retour_texture, retour_rect, message_texture, message_rect);

		*continuer = deplacement_rectangle_selection_charger(etat, charger_rect, retour_rect, &rectangle_selection, sounds);
	}

	if(rectangle_selection != NULL){
		free(rectangle_selection);
		rectangle_selection=NULL;
	}

	if(charger_text != NULL){
		free(charger_text);
		charger_text=NULL;
	}

	if(retour_texture != NULL){
		SDL_DestroyTexture(retour_texture);
		retour_texture=NULL;
	}
	if(charger_texture != NULL){
		SDL_DestroyTexture(charger_texture);
		charger_texture=NULL;
	}

	if(message_texture != NULL){
		SDL_DestroyTexture(message_texture);
		message_texture=NULL;
	}
}
