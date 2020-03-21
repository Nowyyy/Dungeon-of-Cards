/**

*\file combat_tour_par_tour.c

*\author {Tudoret Aurélien, Jourry Axel, Marin Timothée, Malabry Thomas}

*\date 14/03/2020

*\version 0.1

*\brief contient et fait appel a toutes fonctions nécessaires pour le combat
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"
#include "../include/clavier.h"


/**
*\fn int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir,SDL_Rect carte1,SDL_Rect carte2,SDL_Rect carte3,SDL_Rect carte4, SDL_Rect **rect_sel)

*\param defausse, Correspond aux coordonnées du texte défausse
*\param fuir, Correspond aux coordonnées du texte fuir
*\param carte1, Correspond aux coordonnées de la carte 1
*\param carte2, Correspond aux coordonnées de la carte 2
*\param carte3, Correspond aux coordonnées de la carte 3
*\param carte4, Correspond aux coordonnées de la carte 4
*\param **rect_sel Correspond aux coordonnées du rectangle de sélection

*\brief Permet de déplacer le rectangle de selection

*/
int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir,SDL_Rect carte1,SDL_Rect carte2,SDL_Rect carte3,SDL_Rect carte4, SDL_Rect **rect_sel){

	SDL_Event event;
 	int choix=0;

	while(SDL_PollEvent(&event) && choix==0){ //On attend un évènement au clavier
		if(event.type == SDL_KEYDOWN){	//touche enfoncée
			if(event.key.keysym.sym == SDLK_RIGHT){
				if((*rect_sel)->y != fuir.y){//on n'est pas sur la dernière option, on peut descendre
					if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = fuir.y - RECT_SELECT_Y_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte4.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = defausse.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte3.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte4.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte2.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte3.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte1.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte2.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_LEFT){
				if((*rect_sel)->y != defausse.y){//on n'est pas sur la premiere option, on peut monter
					if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->x = carte4.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->y = carte4.y - RECT_SELECT_Y_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte4.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte3.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte3.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte2.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte2.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte1.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
					return -2;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				else if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
					return -1;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				/*SOIN*/
				else if((*rect_sel)->x == carte1.x - RECT_SELECT_X_DIFF){
					return 0;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				else if((*rect_sel)->x == carte2.x - RECT_SELECT_X_DIFF){
					return 1;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				else if((*rect_sel)->x == carte3.x - RECT_SELECT_X_DIFF){
					return 2;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				/*BOUE*/
				else if((*rect_sel)->x == carte4.x - RECT_SELECT_X_DIFF){
					return 3;
					/*Mix_PlayChannel(1, select, 0);*/
				}
			}
		}

		if(event.type == SDL_QUIT)//croix de la fenetre
			return QUIT_SDL;
	}
	return PAS_QUIT_SDL;
}





/**
*\fnvoid affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi,SDL_Texture *defausse_texture ,SDL_Texture *fuir_texture,SDL_Rect defausse_rect ,SDL_Rect fuir_rect,SDL_Rect *rect_sel,image_t images[NB_TEXTURES])

*\param *rendu, le renderer sur lequel on dessine
*\param *ennemi, la structure contenant tous les ennemis
*\param pers, la structure contenant le personnage
*\param *defausse_texture, Les textures du texte defausse
*\param *fuir_texture, Les textures du texte fuir
*\param defausse_rect, les coordonnées du texte defausse
*\param fuir_rect, les coordonnées du texte fuir
*\param *rect_sel, Les coordonnées et taille du rectangle de selection
*\param images[NB_TEXTURES], Un tableau contenant les cartes

*\brief Permet d'afficher toutes la partie combat

*/
void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi,SDL_Texture *defausse_texture ,SDL_Texture *fuir_texture,SDL_Rect defausse_rect ,SDL_Rect fuir_rect,SDL_Rect *rect_sel,image_t images[NB_TEXTURES]){
  //écran noir puis nettoie l'écran
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  /*Mise en place des fonds*/
  SDL_RenderCopy(rendu, images[fond2].img, NULL, &images[fond2].rectangle);

  SDL_RenderCopy(rendu, images[fond].img, NULL, &images[fond].rectangle);

  /*Mise en place des cartes */
  SDL_RenderCopy(rendu, images[carte1].img, NULL, &images[carte1].rectangle);

  SDL_RenderCopy(rendu, images[carte2].img, NULL, &images[carte2].rectangle);

  SDL_RenderCopy(rendu, images[carte3].img, NULL, &images[carte3].rectangle);

  SDL_RenderCopy(rendu, images[carte4].img, NULL, &images[carte4].rectangle);
  /*afficher le rectangle*/
  SDL_SetRenderDrawColor(rendu, 255,255,255,255);
  SDL_RenderDrawRect(rendu, rect_sel);
  /*Texte Défausse et fuir*/
  SDL_RenderCopy(rendu, defausse_texture, NULL, &defausse_rect);
  SDL_RenderCopy(rendu, fuir_texture, NULL, &fuir_rect);

  /*Mise en place du personnage*/
  int w=pers->sprites[idle_droite].rectangle.w;
  int h=pers->sprites[idle_droite].rectangle.h;
  int x=pers->sprites[idle_droite].rectangle.x;
  int y=pers->sprites[idle_droite].rectangle.y;
  pers->sprites[idle_droite].rectangle.w *= 1.5;
  pers->sprites[idle_droite].rectangle.h *= 1.5;
  pers->sprites[idle_droite].rectangle.x = 150;
  pers->sprites[idle_droite].rectangle.y = 250;
  pers->sprites[courant] = pers->sprites[idle_droite];
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);

  /*Afficher l'ennemi*/
  int xe=ennemi->sprites.rectangle.x;
  int ye=ennemi->sprites.rectangle.y;
  int he=ennemi->sprites.rectangle.h;
  int we=ennemi->sprites.rectangle.w;

  ennemi->sprite_courant.x = 0;
  ennemi->sprite_courant.y = ennemi->sprite_courant.h;
  ennemi->sprites.rectangle.x = 750;
  ennemi->sprites.rectangle.y = 240;
  ennemi->sprites.rectangle.w *= 3;
  ennemi->sprites.rectangle.h *= 3;
  ennemi->sprites = ennemi->sprites;
  SDL_RenderCopy(rendu, ennemi->sprites.img, &ennemi->sprite_courant, &ennemi->sprites.rectangle);

  SDL_RenderPresent(rendu);
	/*Reinitialise les coordonnées du perso et des ennemis*/
  pers->sprites[idle_droite].rectangle.w = w;
  pers->sprites[idle_droite].rectangle.h = h;
  pers->sprites[idle_droite].rectangle.x = x;
  pers->sprites[idle_droite].rectangle.y = y;
  ennemi->sprites.rectangle.w = we;
  ennemi->sprites.rectangle.h = he;
  ennemi->sprites.rectangle.x = xe;
  ennemi->sprites.rectangle.y = ye;
}



void charge_textures_combat(image_t images[], SDL_Renderer *rendu, carte_t *cartes[]){

	charge_image(FOND_COMBAT_PATH,&images[fond2], rendu);
	charge_image(COMBAT_PATH,&images[fond], rendu);
	charge_image(cartes[0]->path,&images[carte1], rendu);
	charge_image(cartes[1]->path,&images[carte2], rendu);
	charge_image(cartes[2]->path,&images[carte3], rendu);
	charge_image(cartes[3]->path,&images[carte4], rendu);
}


void donne_valeur_rect_images(image_t images[]){

	images[fond2].rectangle.x= -50;
	images[fond2].rectangle.y= -415;
	images[fond2].rectangle.w *= 2;
	images[fond2].rectangle.h *= 2;

 	images[fond].rectangle.x=0;
	images[fond].rectangle.y= 450;
  	images[fond].rectangle.w *= 4;

  	images[carte1].rectangle.x=50;
  	images[carte1].rectangle.y= 450;

	images[carte2].rectangle.x=250;
  	images[carte2].rectangle.y= 450;

 	images[carte3].rectangle.x=450;
  	images[carte3].rectangle.y= 450;

  	images[carte4].rectangle.x=650;
  	images[carte4].rectangle.y= 450;
}



void free_image(image_t images[]){

	for(int i = fond; i<= carte4; i++){
		SDL_DestroyTexture(images[i].img);
	}
}


void creer_texte_combat(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu, TTF_Font *font){

	image->rectangle.x = x;
	image->rectangle.y = y;

	get_text_and_rect(rendu,image->rectangle.x, image->rectangle.y, txt, font, &image->img, &image->rectangle);
}



void tour_joueur(perso_t *pers, ennemi_t *ennemi, carte_t carte){

	if(carte.type == ATTAQUE){
		ennemi->pv -= carte.valeur;
	}
	else{

		if(pers->pv + carte.valeur <= PV_DEPART_PERSONNAGE)
			pers->pv += carte.valeur;
		else
			pers->pv = PV_DEPART_PERSONNAGE;
	}
}



void tour_ennemi(perso_t *pers, ennemi_t *ennemi){

	pers->pv -= ennemi->attaque;
}

/**
*\fn void combat(perso_t * perso, ennemi_t * ennemi, SDL_Renderer *rendu)
*\param *perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param *ennemi Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\param *rendu, le renderer sur lequel on dessine

*\brief Fonction qui permet de gérer les choix de l'utilisateur via la SDL sur le combat
*/
void combat_t_p_t(perso_t * perso, ennemi_t * ennemi,SDL_Renderer *rendu)
{
////////////////Déclaration variables
	image_t images[NB_TEXTURES];

	carte_t *cartes[NB_CARTES_COMBAT];

	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

  	image_t def;
  	image_t fui;

  	int choix=0, i,fuite=1, alea = rand()%2;

  	TTF_Font * police = NULL;

  	police=TTF_OpenFont(FONT_PATH,40);

//////////////Intialisation, chargement, allocation
	tire_carte_deck(cartes);

	charge_textures_combat(images, rendu, cartes);

	donne_valeur_rect_images(images);

	creer_texte_combat("Defausse", &def, 875, 475, rendu, police);
	creer_texte_combat("Fuir", &fui, 875, 550, rendu, police);

	/*Mise en place du rectangle de selection*/
  	rectangle_selection->x = (def.rectangle).x - RECT_SELECT_X_DIFF;
	rectangle_selection->y = (def.rectangle).y - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = (def.rectangle).w +100;
	rectangle_selection->h = (def.rectangle).h +30;

////////////////boucle combat

  	while((ennemi->pv > 0 && perso->pv > 0) && fuite==1 ){

  		//affichage de l'écran et déplacement de rectangle de sélection
  		affichage_combat_personnage(rendu, perso, ennemi, def.img, fui.img, def.rectangle, fui.rectangle, rectangle_selection, images);
  		choix = deplacement_rectangle_selection_combat(def.rectangle, fui.rectangle, images[carte1].rectangle, images[carte2].rectangle, images[carte3].rectangle, images[carte4].rectangle, &rectangle_selection);


  		if(choix == -1){//le joueur fuit le combat
  			perso->fuite = 1;
  			fuite = 0;
  		}
  		else if(choix == -2){//défausse de carte(s)

  		}
  		else if(choix < NB_CARTES_COMBAT){//le joueur a selectionné une carte

  			if(alea){//le joueur commence

  				tour_joueur(perso, ennemi, *cartes[choix]);
  				tour_ennemi(perso, ennemi);
  			}
  			else{//l'ennemi commence

  				tour_ennemi(perso, ennemi);
  				tour_joueur(perso, ennemi, *cartes[choix]);
  			}
  		}
	}

  	TTF_CloseFont(police);
  	SDL_DestroyTexture(def.img);
  	SDL_DestroyTexture(fui.img);

  	free_image(images);
}
