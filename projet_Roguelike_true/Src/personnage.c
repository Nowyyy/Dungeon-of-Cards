/**
* \file personnage.c
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 04/02/2020
* \version 0.1

* \brief Gère toute la partie concernant le personnage

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"



/**

* \fn charge_sprites_personnage

* \param sprites[], tableau qui contiendra tous les sprites du personnage
* \param *rendu, le rendu sur lequel on dessinera le personnage

*\brief fonction qui charge tous les sprites du personnage
*/
void charge_sprites_personnage(image_t sprites[], SDL_Renderer *rendu){

	//for(int i = 0; i < NB_SPRITES_PERSONNAGE; i++){
		charge_image(SPRITE_PATH, &sprites[0], rendu);
	//}
}


/**
* \fn test_collision

* \param salle, la salle pour laquelle on test les collisions
* \param pers, le personnage pour lequel on test les collisions
* \param direction, la direction dans laquelle se rend le personnage

* \brief permet de regarder si le personnage entre en collision avec un des murs de la salle

* \return 1 en cas de collision, 0 si aucune collision
*/
int test_collision(salle_t salle, perso_t pers, int direction){

	int i = 0;

	for( ; i < salle.nb_murs; i++){

		if(direction == 0)//haut
			pers.sprites[0].rectangle.y -= 1;
		else if(direction == 1) //droite
			pers.sprites[0].rectangle.x += 1;
		else if(direction == 2) //bas
			pers.sprites[0].rectangle.y += 1;
		else //gauche
			pers.sprites[0].rectangle.x -= 1;

		if(SDL_HasIntersection(&salle.murs[i], &pers.sprites[0].rectangle)){
			return 1;
		}

		//printf("x perso %d, y perso %d, x mur +tailleimage %d, y mur, %d\n", pers.sprites[0].rectangle.x, pers.sprites[0].rectangle.y, salle.murs[i].x + TAILLE_IMAGE, salle.murs[i].y);
	}
	return 0;
}


/**

* \fn deplacement_personnage

* \param pers, la structure du pêrsonnage que l'on souhaite déplacer
* \param salle, la salle dans laquelle le personnage se déplace
* \param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme

* \brief Gère les déplacement du personnage dans une salle
*/
void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer){

	SDL_Event event;

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		if(event.type == SDL_KEYDOWN){	//touche enfoncée
			if(event.key.keysym.sym == SDLK_DOWN){ //touche du bas
				//if(salle.salle[pers->x - EMPLACEMENT_DEPART_DESSIN_SALLE_X][pers->y - EMPLACEMENT_DEPART_DESSIN_SALLE_Y] != mur){
				if(!test_collision(salle,*pers, 2)){
					pers->y += VITESSE_PERSO;
				}
			}
			else if(event.key.keysym.sym == SDLK_RIGHT){ //touche droite
				//if(salle.salle[pers->x - EMPLACEMENT_DEPART_DESSIN_SALLE_X][pers->y - EMPLACEMENT_DEPART_DESSIN_SALLE_Y] != mur){
				if(!test_collision(salle,*pers, 1)){
					pers->x += VITESSE_PERSO;
				}
			}
			else if(event.key.keysym.sym == SDLK_LEFT){ //touche gauche
				//if(salle.salle[pers->x - EMPLACEMENT_DEPART_DESSIN_SALLE_X][pers->y - EMPLACEMENT_DEPART_DESSIN_SALLE_Y] != mur){
				if(!test_collision(salle,*pers, 3)){
					pers->x -= VITESSE_PERSO;
				}
			}
			else if(event.key.keysym.sym == SDLK_UP){ //touche haut
				//if(salle.salle[pers->x - EMPLACEMENT_DEPART_DESSIN_SALLE_X][pers->y - EMPLACEMENT_DEPART_DESSIN_SALLE_Y] != mur){
				if(!test_collision(salle,*pers, 0)){
					pers->y -= VITESSE_PERSO;
				}
			}
		}
		if(event.type == SDL_QUIT)//croix de la fenetre
			*continuer = FALSE;
	}
	pers->sprites[0].rectangle.x = pers->x;
	pers->sprites[0].rectangle.y = pers->y;
}



/**
* \fn changement_de_salle

* \param *pers, la structure du personnage
* \param *salle, la salle dans laquelle on se trouve
* \param *continuer la variable permettant de quitter le jeu

* \brief permet de téléporter le personnage dans la salle dont il passe la porter

* \return la salle dans laquelle le joueur arrive
*/
int changement_de_salle(perso_t *pers, salle_t salle, int indice, Mix_Chunk *change_salle){

	for(int i = 0; i < salle.nb_portes; i++){

		if(SDL_HasIntersection(&salle.portes[i], &pers->sprites[0].rectangle)){

			if(salle.portes[i].y == EMPLACEMENT_DEPART_DESSIN_SALLE_Y){
			//porte en haut
				pers->x = WIN_WIDTH / 2 - TAILLE_IMAGE;
				pers->y = salle.murs[salle.nb_murs -1].y - TAILLE_IMAGE;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_h;
			}
			else if(salle.portes[i].y == 488){
			//porte en bas
				pers->x = WIN_WIDTH / 2 - TAILLE_IMAGE;

				pers->y = salle.murs[0].y + TAILLE_IMAGE;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_b;
			}
			else if(salle.portes[i].x == EMPLACEMENT_DEPART_DESSIN_SALLE_X){
			//porte à gauche
				pers->x = WIN_WIDTH / 2 + 100;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_g;
			}
			else{
			//porte à droite
				pers->x = salle.murs[0].x + TAILLE_IMAGE;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(0, change_salle, 1);

				return salle.s_d;
			}
		}
	}

	pers->sprites[0].rectangle.x = pers->x;
	pers->sprites[0].rectangle.y = pers->y;

	return indice;
}
