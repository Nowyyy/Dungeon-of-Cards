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
int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir, image_t images[NB_TEXTURES_LABY], SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC]){

	SDL_Event event;
 	int choix= NB_CARTES_COMBAT +1;

	while(SDL_PollEvent(&event) && choix== NB_CARTES_COMBAT +1){ //On attend un évènement au clavier

		if(event.type == SDL_KEYDOWN){	//touche enfoncée

			if(event.key.keysym.sym == SDLK_RIGHT){
				if((*rect_sel)->x < defausse.x){//on n'est pas sur la dernière option, on peut descendre

					if((*rect_sel)->x == images[carte4].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = defausse.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->w = defausse.w + RECT_SELECT_X_DIFF * 2;
						(*rect_sel)->h = defausse.h + RECT_SELECT_Y_DIFF * 2;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte3].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte4].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte2].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte3].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte1].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte2].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_LEFT){

				if((*rect_sel)->x > images[carte1].rectangle.x){//on n'est pas sur la premiere option, on peut aller a gauche

					if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->x = images[carte4].rectangle.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->y = images[carte4].rectangle.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->h = images[carte4].rectangle.h + RECT_SELECT_Y_DIFF * 2;
						(*rect_sel)->w = images[carte4].rectangle.w + RECT_SELECT_X_DIFF * 2;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == fuir.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte4].rectangle.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->y = images[carte4].rectangle.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->h = images[carte4].rectangle.h + RECT_SELECT_Y_DIFF * 2;
						(*rect_sel)->w = images[carte4].rectangle.w + RECT_SELECT_X_DIFF * 2;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte4].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte3].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte3].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte2].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
					else if((*rect_sel)->x == images[carte2].rectangle.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = images[carte1].rectangle.x - RECT_SELECT_X_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_UP){//touche haut
				if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
				}
			}
			else if(event.key.keysym.sym == SDLK_DOWN){//touche bas
				if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = fuir.y - RECT_SELECT_Y_DIFF;
						Mix_PlayChannel(0, sounds[move], 0);
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return -2;
				}
				else if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return -1;
				}
				/*SOIN*/
				else if((*rect_sel)->x == images[carte1].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 0;
				}
				else if((*rect_sel)->x == images[carte2].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 1;
				}
				else if((*rect_sel)->x == images[carte3].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 2;
				}
				/*BOUE*/
				else if((*rect_sel)->x == images[carte4].rectangle.x - RECT_SELECT_X_DIFF){
					Mix_PlayChannel(0, sounds[selection], 0);
					return 3;
				}
			}
		}
	}
	return NB_CARTES;
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
void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi, image_t def, image_t fuir, SDL_Rect *rect_sel,image_t images[NB_TEXTURES_COMBAT],
hud_combat_t ennemi_hud, hud_combat_t pers_hud, hud_combat_t action){

	int w5 = images[gui_bar].rectangle.w;
	images[gui_bar].rectangle.w = action.texte.rectangle.w *1.25;
  //écran noir puis nettoie l'écran
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  /*Mise en place des fonds*/
  SDL_RenderCopy(rendu, images[fond2].img, NULL, &images[fond2].rectangle);

  SDL_RenderCopy(rendu, images[fond].img, NULL, &images[fond].rectangle);

  images[coeur].rectangle.x = WIN_WIDTH * 0.10;
  images[coeur].rectangle.y = WIN_HEIGHT * 0.02;

  SDL_RenderCopy(rendu, pers_hud.pv.img, NULL, &pers_hud.pv.rectangle);
  SDL_RenderCopy(rendu, pers_hud.nom.img, NULL, &pers_hud.nom.rectangle);
  SDL_RenderCopy(rendu, images[coeur].img, NULL, &images[coeur].rectangle);

  images[coeur].rectangle.x = WIN_WIDTH * 0.81;
  images[coeur].rectangle.y = WIN_HEIGHT * 0.02;

  SDL_RenderCopy(rendu, ennemi_hud.pv.img, NULL, &ennemi_hud.pv.rectangle);
  SDL_RenderCopy(rendu, ennemi_hud.nom.img, NULL, &ennemi_hud.nom.rectangle);
  SDL_RenderCopy(rendu, images[coeur].img, NULL, &images[coeur].rectangle);

  if(action.existe){
  	SDL_RenderCopy(rendu, images[gui_bar].img, NULL, &images[gui_bar].rectangle);
 	SDL_RenderCopy(rendu, action.texte.img, NULL, &action.texte.rectangle);
  }

  /*Mise en place des cartes */
  SDL_RenderCopy(rendu, images[carte1].img, NULL, &images[carte1].rectangle);

  SDL_RenderCopy(rendu, images[carte2].img, NULL, &images[carte2].rectangle);

  SDL_RenderCopy(rendu, images[carte3].img, NULL, &images[carte3].rectangle);

  SDL_RenderCopy(rendu, images[carte4].img, NULL, &images[carte4].rectangle);
  /*afficher le rectangle*/
  SDL_SetRenderDrawColor(rendu, 255,255,255,255);
  SDL_RenderDrawRect(rendu, rect_sel);
  /*Texte Défausse et fuir*/
  SDL_RenderCopy(rendu, def.img, NULL, &def.rectangle);
  SDL_RenderCopy(rendu, fuir.img, NULL, &fuir.rectangle);

  /*Mise en place du personnage*/
  int w=pers->sprites[idle_droite].rectangle.w;
  int h=pers->sprites[idle_droite].rectangle.h;
  int x=pers->sprites[idle_droite].rectangle.x;
  int y=pers->sprites[idle_droite].rectangle.y;
  pers->sprites[idle_droite].rectangle.w *= 1.5;
  pers->sprites[idle_droite].rectangle.h *= 1.5;
  pers->sprites[idle_droite].rectangle.x = 150;
  pers->sprites[idle_droite].rectangle.y = 342;
  pers->sprites[courant] = pers->sprites[idle_droite];
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);

  /*Afficher l'ennemi*/
  int xe=ennemi->sprites.rectangle.x;
  int ye=ennemi->sprites.rectangle.y;
  int he=ennemi->sprites.rectangle.h;
  int we=ennemi->sprites.rectangle.w;
  int hauteur=405;
  ennemi->sprite_courant.x = 0;
  ennemi->sprite_courant.y = ennemi->sprite_courant.h;
  ennemi->sprites.rectangle.x = 750;
  ennemi->sprites.rectangle.w *= 1.5;
  ennemi->sprites.rectangle.h *= 1.5;
	ennemi->sprites.rectangle.y = hauteur-(ennemi->sprites.rectangle.h);
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

  images[gui_bar].rectangle.w = w5;
}



/**
*\fn void charge_textures_combat(image_t images[], SDL_Renderer *rendu, carte_t *cartes[])

*\param images[], le tableau contenant les images
*\param *rendu, le renderer sur lequel on dessine
*\param *cartes[], tableau de pointeur sur des cartes, contient les cartes utilisées pendant le combat

*\brief Charge dans le tableau images les visuels pour les fonds et les cartes afin de pouvoir les afficher
*/
void charge_textures_combat(image_t images[], SDL_Renderer *rendu, carte_t *cartes[]){

	charge_image(FOND_COMBAT_PATH,&images[fond2], rendu);
	charge_image(COMBAT_PATH,&images[fond], rendu);
	charge_image(GUI_COMBAT_PATH,&images[gui_bar], rendu);
	charge_image(cartes[0]->path,&images[carte1], rendu);
	charge_image(cartes[1]->path,&images[carte2], rendu);
	charge_image(cartes[2]->path,&images[carte3], rendu);
	charge_image(cartes[3]->path,&images[carte4], rendu);
	charge_image(HEART_PATH,&images[coeur], rendu);
}


/**
*\fn void donne_valeur_rect_images(image_t images[])

*\param images[], le tableau contenant les images

*\brief Donne les coordonnées et ajuste les tailles des images des cartes et des fonds pour l'écran de combat
*/
void donne_valeur_rect_images(image_t images[]){

	images[fond2].rectangle.x= 0;
	images[fond2].rectangle.y= 70;
	images[fond2].rectangle.w *= 1;
	images[fond2].rectangle.h *= 1;

 	images[fond].rectangle.x=0;
	images[fond].rectangle.y= 450;
  	images[fond].rectangle.w *= 1;
  	images[fond].rectangle.w *= 1;
  	images[fond].rectangle.w *= 4;

  	images[gui_bar].rectangle.x = WIN_WIDTH / 2 - images[gui_bar].rectangle.w / 2;
  	images[gui_bar].rectangle.y = WIN_HEIGHT * 0.15;

  	images[carte1].rectangle.x=50;
  	images[carte1].rectangle.y= 450;

	images[carte2].rectangle.x=250;
  	images[carte2].rectangle.y= 450;

 	images[carte3].rectangle.x=450;
  	images[carte3].rectangle.y= 450;

  	images[carte4].rectangle.x=650;
  	images[carte4].rectangle.y= 450;
}


/**
*\fn void free_image(image_t images[])

*\param images[], le tableau contenant les images

*\brief Supprime les images des cartes et des fonds utilisées pour le combat
*/
void free_image(image_t images[]){

	for(int i = 0; i< NB_TEXTURES_COMBAT; i++)
		libere_texture(&images[i].img);
}


/**
*\fn void tour_joueur(perso_t *pers, ennemi_t *ennemi, carte_t carte)

*\param *pers, la structure du personnage
*\param *ennemi, l'ennemi que le joueur affronte
*\param carte, la carte que le joueur joue

*\brief permet d'effectuer l'action sélectionnée par le joueur
*/
void tour_joueur(perso_t *pers, ennemi_t *ennemi, carte_t *carte){

	if(carte->type == ATTAQUE){
		if(carte->consommable > 0){
			carte->consommable -= 1;
		}
		ennemi->pv -= carte->valeur;
	}
	else{

		if(carte->consommable > 0){
			carte->consommable -= 1;
		}

		if(pers->pv + carte->valeur <= PV_DEPART_PERSONNAGE)
			pers->pv += carte->valeur;
		else
			pers->pv = PV_DEPART_PERSONNAGE;
	}
}


/**
*\fn void tour_ennemi(perso_t *pers, ennemi_t *ennemi)

*\param *pers, la structure du personnage
*\param *ennemi, l'ennemi que le joueur affronte

*\brief permet de faire jouer l'ennemi, actions effectuées selon la situation
*/
void tour_ennemi(perso_t *pers, ennemi_t *ennemi){

	pers->pv -= ennemi->attaque;
}


/**
*\fn void creer_texte_combat(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu, TTF_Font *font)

*\param *txt, le texte que l'on souhaite afficher à l'écran,
*\param *image, la structure qui contiendra le texte
*\param x, la position en x où sera placée l'image
*\param y, la position en y où sera placée l'image
*\param *rendu, le renderer sur lequel on dessine
*\param *font, la police utilisée pour écrire le texte

*\brief Permet de donner à une structure image, un texte et les positions où l'afficher à l'écran
*/
void creer_texte_combat(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu, TTF_Font *font){

	image->rectangle.x = x;
	image->rectangle.y = y;

	get_text_and_rect(rendu,image->rectangle.x, image->rectangle.y, txt, font, &image->img, &image->rectangle);
}


/**
*\fn void create_hud(hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, ennemi_t ennemi, perso_t pers, SDL_Renderer *rendu, TTF_Font *font)

*\param
*\param *rendu, le renderer sur lequel on dessine
*\param *font, la police utilisée pour écrire le texte

*\brief Créer un HUD pour le perso et l'ennemi s'il n'existe pas, sinon détruit les textures précédentes pour mettre à jour
*/
void create_hud(hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, ennemi_t ennemi, perso_t pers, SDL_Renderer *rendu, TTF_Font *font){

	char pv_pers[20], pv_ennemi[20], nom_pers[] = "Joueur";

	sprintf(pv_pers, "PV  %d / %d", pers.pv, PV_DEPART_PERSONNAGE);
	sprintf(pv_ennemi, "PV  %d / %d", ennemi.pv, ennemi.pv_max);

	if(hud_ennemi->existe == 0 || hud_pers->existe == 0){

		hud_ennemi->existe = 1;

		hud_pers->existe = 1;
	}
	else{
		libere_texture(&hud_pers->pv.img);
		libere_texture(&hud_pers->nom.img);
		libere_texture(&hud_ennemi->nom.img);
		libere_texture(&hud_ennemi->pv.img);
	}

	creer_texte_combat(nom_pers, &hud_pers->nom, WIN_WIDTH * 0.02, WIN_HEIGHT *0.02, rendu, font);
	creer_texte_combat(pv_pers, &hud_pers->pv, hud_pers->nom.rectangle.x + hud_pers->nom.rectangle.w + 50, WIN_HEIGHT *0.02, rendu, font);

	creer_texte_combat(ennemi.nom, &hud_ennemi->nom, WIN_WIDTH * 0.65, WIN_HEIGHT *0.02, rendu, font);
	creer_texte_combat(pv_ennemi, &hud_ennemi->pv, WIN_WIDTH * 0.85, WIN_HEIGHT *0.02, rendu, font);
}

/**
*\fn void init_hud_action(hud_combat_t *action)

*\param *action, le hud qui affichera l'action effectuée par le joueur ou l'ennemi

*\brief initialise certaines valeurs du hud action
*/
void init_hud_action(hud_combat_t *action){

	action->existe = 0;
}



/**
*\fn void actualisation_apres_tour(perso_t *pers, ennemi_t *ennemi, carte_t carte, hud_combat_t *action, hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, SDL_Renderer *rendu, TTF_Font *font, int  tour)

*\param *action, le hud qui affichera l'action effectuée par le joueur ou l'ennemi
*\param *pers, la structure du personnage
*\param *ennemi, la structure de l'ennemi
*\param carte, la carte utilisée par le joueur lors de ce tour
*\param *hud_pers, le hud du personnage
*\param *hud_ennemi, le hud de l'ennemi
*\param *rendu, le renderer sur lequel on dessine
*\param *font, la police utilisée pour écrire le texte

*\brief Actualise les huds des perso et ennemi, prépare le texte a affichant indiquant l'action effectuée
*/
void actualisation_apres_tour(perso_t *pers, ennemi_t *ennemi, carte_t carte, hud_combat_t *action, hud_combat_t *hud_pers, hud_combat_t *hud_ennemi, SDL_Renderer *rendu, TTF_Font *font, int  tour){

	char joueur[80];
	int x, y;

	if(action->existe)
		libere_texture(&action->texte.img);

	if(tour){

		create_hud(hud_pers, hud_ennemi, *ennemi, *pers, rendu, font); //actualisation des pdv dans le hud

		if(carte.type == ATTAQUE)
			sprintf(joueur, "Vous utilisez %s, %s perd %d points de vie", carte.nom, ennemi->nom, carte.valeur);
		else
			sprintf(joueur, "Vous utilisez %s, Vous recuperez %d points de vie", carte.nom, carte.valeur);
	}
	else{

		create_hud(hud_pers, hud_ennemi, *ennemi, *pers, rendu, font); //actualisation des pdv dans le hud

		if(ennemi->pv != ennemi->pv_old)
			sprintf(joueur, "%s se soigne de %d points de vie", ennemi->nom, ennemi->defense);
		else
			sprintf(joueur, "%s attaque ! Vous perdez %d points de vie", ennemi->nom, ennemi->attaque);
	}

	action->existe = 1;

	creer_texte_combat(joueur, &action->texte, 0, 0, rendu, font);

	x = WIN_WIDTH / 2 - action->texte.rectangle.w /2;
	y = WIN_HEIGHT * 0.15;
	action->texte.rectangle.x = x + 20;
	action->texte.rectangle.y = y + 20;

	ennemi->pv_old = ennemi->pv;
}


/**
*\fn void detruire_action_temp(hud_combat_t *action)

*\param *action, la zone de texte détaillant les coups échangés entre le joueur et l'ennemi

*\brief permet de détruire l'image présente dans le champs texte de action
*/
void detruire_action_temp(hud_combat_t *action){

	if(action->existe){
		action->existe = 0;
		libere_texture(&action->texte.img);
	}
}


/**
*\fn void range_carte_deck(carte_t *cartes[])

\param *cartes[], tableau de pointeurs sur cartes, contient les cartes utilisées pendant le combat

*\brief Range les cartes encore valide dans le deck, détruit les cartes barrées
*/
void range_carte_deck(carte_t *cartes[]){

	choix_liste(DECK);

	en_queue();

	for(int i = 0; i < NB_CARTES_COMBAT; i++){

		if(cartes[i]->type != NO_CARTE){

			ajout_droit(cartes[i]);
		}
		else{ // fake carte (carte barrée)
			detruire_carte(&cartes[i]);
		}
	}
}


void consommable_epuise(carte_t *cartes[], int indice, image_t images[], SDL_Renderer *rendu){

	int x = images[carte1 + indice].rectangle.x, y = images[carte1 + indice].rectangle.y;

	if(cartes[indice]->type != NO_CARTE){

		if(cartes[indice]->consommable == 0){

			detruire_carte(&cartes[indice]);

			tire_carte_deck(cartes, indice);

			charge_image(cartes[indice]->path,&images[carte1 + indice], rendu);

			images[carte1 + indice].rectangle.y = y;
			images[carte1 + indice].rectangle.x = x;
		}
	}
}

/**
*\fn void combat(perso_t * perso, ennemi_t * ennemi, SDL_Renderer *rendu)
*\param *perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param *ennemi Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\param *rendu, le renderer sur lequel on dessine

*\brief Fonction qui permet de gérer les choix de l'utilisateur via la SDL sur le combat
*/
void combat_t_p_t(perso_t * perso, ennemi_t * ennemi,SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC])
{
////////////////Déclaration variables

	carte_t *cartes[NB_CARTES_COMBAT];

	image_t images[NB_TEXTURES_COMBAT];

	SDL_Event event;

	SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

  	image_t def, fui;

  	hud_combat_t hud_pers, hud_ennemi, action;

  	int choix=0, i,fuite=1, alea = rand()%2, wait = 600, pv_ennemi = ennemi->pv;

  	TTF_Font * police = NULL;

  	police=TTF_OpenFont(FONT_PATH, 35);

//////////////Intialisation, chargement, allocation

  	hud_ennemi.existe = 0;
  	hud_pers.existe = 0;

  	for(int j = 0; j < NB_CARTES_COMBAT; j++)
		tire_carte_deck(cartes, j);

	charge_textures_combat(images, rendu, cartes);

	init_hud_action(&action);

	create_hud(&hud_pers, &hud_ennemi, *ennemi, *perso, rendu, police);

	donne_valeur_rect_images(images);

	creer_texte_combat("Defausse", &def, 875, 475, rendu, police);
	creer_texte_combat("Fuir", &fui, 875, 550, rendu, police);

	/*Mise en place du rectangle de selection*/
  	rectangle_selection->x = (def.rectangle).x - RECT_SELECT_X_DIFF;
	rectangle_selection->y = (def.rectangle).y - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = (def.rectangle).w +100;
	rectangle_selection->h = (def.rectangle).h +30;

////////////////boucle combat

	Mix_VolumeMusic(80);
	Mix_PlayMusic(musics[fight], -1);

  	while((ennemi->pv > 0 && perso->pv > 0) && fuite==1 ){

  		//affichage de l'écran et déplacement de rectangle de sélection
  		affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);

  		choix = deplacement_rectangle_selection_combat(def.rectangle, fui.rectangle, images, &rectangle_selection, sounds, musics);


  		if(choix == -1){//le joueur fuit le combat
  			perso->fuite = 1;
  			ennemi->pv = pv_ennemi;
  			fuite = 0;
  		}
  		else if(choix == -2){//défausse de carte(s)

  		}
  		else if(choix < NB_CARTES_COMBAT && cartes[choix]->type != NO_CARTE){//le joueur a selectionné une carte

  			if(alea){//le joueur commence

  				tour_joueur(perso, ennemi, cartes[choix]);
  				actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea);
  				affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
  				SDL_Delay(wait* 2);

  				if(ennemi->pv > 0){
	  				tour_ennemi(perso, ennemi);
	  				actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea-1);
	  				affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
	  				SDL_Delay(wait);
	  			}
  			}
  			else{//l'ennemi commence

  				tour_ennemi(perso, ennemi);
  				actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea);
  				affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
  				SDL_Delay(wait* 2);

  				if(perso->pv > 0){
	  				tour_joueur(perso, ennemi, cartes[choix]);
	  				actualisation_apres_tour(perso, ennemi, *cartes[choix], &action, &hud_pers, &hud_ennemi, rendu, police, alea + 1);
	  				affichage_combat_personnage(rendu, perso, ennemi, def, fui, rectangle_selection, images, hud_ennemi, hud_pers, action);
	  				SDL_Delay(wait);
	  			}
  			}
  			consommable_epuise(cartes, choix, images, rendu);
  		}
  		detruire_action_temp(&action);
  		while(SDL_PollEvent(&event));
	}
	if(ennemi->pv<=0){
		perso->pv=50;
	}
	Mix_HaltMusic();
  	TTF_CloseFont(police);


  	range_carte_deck(cartes);

  	libere_texture(&def.img);
	libere_texture(&fui.img);
	libere_texture(&hud_ennemi.pv.img);
	libere_texture(&hud_ennemi.nom.img);
	libere_texture(&hud_pers.pv.img);
	libere_texture(&hud_pers.nom.img);

  	detruire_action_temp(&action);

	free_image(images);

	if(rectangle_selection != NULL){
		free(rectangle_selection);
		rectangle_selection=NULL;
	}
}
