/**
* \file personnage.c
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 04/02/2020
* \version 0.1

* \brief Gère toute la partie concernant le personnage

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"
#include "clavier.h"



/**

* \fn charge_sprites_personnage

* \param sprites[], tableau qui contiendra tous les sprites du personnage
* \param *rendu, le rendu sur lequel on dessinera le personnage

*\brief fonction qui charge tous les sprites du personnage
*/
void charge_sprites_personnage(image_t sprites[], SDL_Renderer *rendu){

	charge_image(SPRITE1_PATH, &sprites[idle_droite], rendu);
	charge_image(SPRITE2_PATH, &sprites[idle_gauche], rendu);
	charge_image(SPRITE3_PATH, &sprites[droite1], rendu);
	charge_image(SPRITE4_PATH, &sprites[droite2], rendu);
	charge_image(SPRITE5_PATH, &sprites[gauche2], rendu);
	charge_image(SPRITE6_PATH, &sprites[gauche1], rendu);
	charge_image(SPRITE7_PATH, &sprites[dead], rendu);
	charge_image(SPRITE8_PATH, &sprites[gauche3], rendu);
	charge_image(SPRITE9_PATH, &sprites[droite3], rendu);

	charge_image(SPRITE2_PATH, &sprites[courant], rendu);
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
			pers.sprites[courant].rectangle.y -= 1;
		else if(direction == 1) //droite
			pers.sprites[courant].rectangle.x += 1;
		else if(direction == 2) //bas
			pers.sprites[courant].rectangle.y += 1;
		else //gauche
			pers.sprites[courant].rectangle.x -= 1;

		if(SDL_HasIntersection(&salle.murs[i], &pers.sprites[courant].rectangle)){
			return 1;
		}

		//printf("x perso %d, y perso %d, x mur +tailleimage %d, y mur, %d\n", pers.sprites[0].rectangle.x, pers.sprites[0].rectangle.y, salle.murs[i].x + TAILLE_IMAGE, salle.murs[i].y);
	}
	return 0;
}


/**

* \fn init_animations

* \param *anim, la structure qui gère les animations

* \brief Initialise la structure d'animations

*/
void init_animations(animation_t *anim){

	anim->actuel = courant;
	anim->last_use = SDL_GetTicks() - DELAIS_ANIMATIONS;
}



/**
* \fn change_animation

* \param sprites[], le tableau de sprites du personnage
* \param *anim, la structure qui gère les animations
* \param nouvelle_animation, l'indice du tableau ou se trouve la nouvelle animation a utiliser

* \brief permet de changer d'animation selon la nouvelle passée en paramètre

*/
void change_animation(animation_t *anim, image_t sprites[], int nouvelle_animation){

	sprites[courant] = sprites[nouvelle_animation];
	anim->actuel = nouvelle_animation;
	anim->last_use = SDL_GetTicks();
}



/**
* \fn animations_personnage

* \param sprites[], le tableau de sprites du personnage
* \param timer, le temps d'execution du jeu
* \param clavier, la structure de touches du clavier
* \param *anim, la structure qui gère les animations
* \param *footsteps, les sons de pas du personnage

* \brief permet de changer d'animation selon le déplacement du personnage

*/
void animations_personnage(image_t sprites[], unsigned int timer, touches_t clavier, animation_t *anim, Mix_Chunk *footsteps){

	int i;

	for(i = 0; i <= left && clavier.tab[i] != 1; i++);//recherche d'une touche pressée

	if(i <= left){

		if(anim->last_use + DELAIS_ANIMATIONS <= timer){

			//animation du personnage vers la droite
			if(i == right && sprites[courant].img == sprites[droite3].img){
				change_animation(anim, sprites, droite2);

			}
			else if (i == right && sprites[courant].img == sprites[droite2].img){
				change_animation(anim, sprites, droite1);
				Mix_PlayChannel(0, footsteps, 0);

			}
			else if (i == right || (i == right && sprites[courant].img == sprites[droite1].img)){
				change_animation(anim, sprites, droite3);

			}

			//animation du personnage vers la gauche
			if(i == left && sprites[courant].img == sprites[gauche1].img){
				change_animation(anim, sprites, gauche2);
			}
			else if (i== left && sprites[courant].img == sprites[gauche2].img){
				change_animation(anim, sprites, gauche3);
			}
			else if (i == left || (i == left && sprites[courant].img == sprites[gauche3].img)){
				change_animation(anim, sprites, gauche1);
				Mix_PlayChannel(0, footsteps, 0);

			}

			//animation du personnage vers le haut
			if(i == up){
				//on garde le personnage orienté dans sa direction d'origine
				if(anim->actuel >= idle_droite && anim->actuel <= droite3){
					if(sprites[courant].img == sprites[droite3].img){
						change_animation(anim, sprites, droite2);
					}
					else if(sprites[courant].img == sprites[droite2].img){
						change_animation(anim, sprites, droite1);
						Mix_PlayChannel(0, footsteps, 0);

					}
					else{
						change_animation(anim, sprites, droite3);
					}
				}
				else{
					if(sprites[courant].img == sprites[gauche1].img){
						change_animation(anim, sprites, gauche2);
					}
					else if(sprites[courant].img == sprites[gauche2].img){
						change_animation(anim, sprites, gauche3);
					}
					else{
						change_animation(anim, sprites, gauche1);
						Mix_PlayChannel(0, footsteps, 0);

					}
				}
			}
			else //animation du personnage vers le bas
			if(i == down){
				//on garde le personnage orienté dans sa direction d'origine
				if(anim->actuel >= idle_droite && anim->actuel <= droite3){
					if(sprites[courant].img == sprites[droite3].img){
						change_animation(anim, sprites, droite2);
					}
					else if(sprites[courant].img == sprites[droite2].img){
						change_animation(anim, sprites, droite1);
						Mix_PlayChannel(0, footsteps, 0);

					}
					else{
						change_animation(anim, sprites, droite3);
					}
				}
				else{
					if(sprites[courant].img == sprites[gauche1].img){
						change_animation(anim, sprites, gauche2);
					}
					else if(sprites[courant].img == sprites[gauche2].img){
						change_animation(anim, sprites, gauche3);
					}
					else{
						change_animation(anim, sprites, gauche1);
						Mix_PlayChannel(0, footsteps, 0);

					}
				}
			}
		}
	}
	else{

		//aucune touche enfoncée, on revient a un état idle
		if(sprites[courant].img == sprites[gauche3].img || sprites[courant].img == sprites[gauche2].img || sprites[courant].img == sprites[gauche1].img){
			change_animation(anim, sprites, idle_gauche);
		}
		else{
			change_animation(anim, sprites, idle_droite);
		}

		anim->last_use -= DELAIS_ANIMATIONS;
	}
}


/**

* \fn deplacement_personnage

* \param pers, la structure du pêrsonnage que l'on souhaite déplacer
* \param salle, la salle dans laquelle le personnage se déplace
* \param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
* \param *footsteps, les sons de pas du personnage


* \brief Gère les déplacement du personnage dans une salle
*/
void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer, animation_t *anim, Mix_Chunk *footsteps){

	SDL_Event event;

	unsigned int temps = SDL_GetTicks();

	touches_t clavier;

	init_tab_clavier(clavier.tab);

	while(SDL_PollEvent(&event)){ //On attend un évènement au clavier

		event_clavier(&clavier, event);

		if(clavier.tab[down] == 1){ //touche du bas

			if(!test_collision(salle,*pers, 2)){
				pers->y += VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim, footsteps);
			}
		}
		else if(clavier.tab[right] == 1){ //touche droite

			if(!test_collision(salle,*pers, 1)){
				pers->x += VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim, footsteps);
			}
		}
		else if(clavier.tab[left] == 1){ //touche gauche

			if(!test_collision(salle,*pers, 3)){
				pers->x -= VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim, footsteps);
			}
		}
		else if(clavier.tab[up] == 1){ //touche haut

			if(!test_collision(salle,*pers, 0)){
				pers->y -= VITESSE_PERSO;
				animations_personnage(pers->sprites, temps, clavier, anim, footsteps);
			}
		}

	if(event.type == SDL_QUIT)//croix de la fenetre
		*continuer = FALSE;

	animations_personnage(pers->sprites, temps, clavier, anim, footsteps);
	//permet au personnage de revenir à l'état idle quand aucune touche n'est enfoncée
	}

	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;
}



/**
* \fn changement_de_salle

* \param *pers, la structure du personnage
* \param *salle, la salle dans laquelle on se trouve
* \param *continuer la variable permettant de quitter le jeu
* \param *change_salle, le son de changement de salle

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
				Mix_PlayChannel(0, change_salle, 0);

				return salle.s_h;
			}
			else if(salle.portes[i].y == 488){
			//porte en bas
				pers->x = WIN_WIDTH / 2 - TAILLE_IMAGE;

				pers->y = salle.murs[0].y + TAILLE_IMAGE;
				Mix_PlayChannel(0, change_salle, 0);

				return salle.s_b;
			}
			else if(salle.portes[i].x == EMPLACEMENT_DEPART_DESSIN_SALLE_X){
			//porte à gauche
				pers->x = WIN_WIDTH / 2 + 100;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(0, change_salle, 0);

				return salle.s_g;
			}
			else{
			//porte à droite
				pers->x = salle.murs[0].x + TAILLE_IMAGE;
				pers->y = WIN_HEIGHT / 2 - TAILLE_IMAGE / 2;
				Mix_PlayChannel(0, change_salle, 0);

				return salle.s_d;
			}
		}
	}

	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;

	return indice;
}



/**
* \fn initialise_personnage

* \param *pers, la structure du personnage

* \brief initialise les valeurs de base pour le personnage
*/
void initialise_personnage(perso_t *pers){


	pers->pv = PV_DEPART_PERSONNAGE;
	pers->vitesse = VITESSE_DEPART_PERSONNAGE;
	pers->attaque = ATTAQUE_DEPART_PERSONNAGE;
	pers->defense = DEFENSE_DEPART_PERSONNAGE;

	pers->x = WIN_WIDTH / 2;
	pers->y = WIN_HEIGHT / 2;

	pers->etage = 1;

	pers->cmpMort = 0;
}



/**
* \fn initialise_deck_cartes

* \param *cartes

* \brief Initialise un deck de départ pour le joueur
*/
void initialise_deck_cartes(carte_t *cartes){

	//do nothing pour le moment
}




int collision_perso_ennemi(perso_t pers, ennemi_t ennemi, int x, int y){

	ennemi.sprites[courant].rectangle.x = (x*TAILLE_IMAGE) + EMPLACEMENT_DEPART_DESSIN_SALLE_X;
	ennemi.sprites[courant].rectangle.y = (y*TAILLE_IMAGE) + EMPLACEMENT_DEPART_DESSIN_SALLE_Y;

	return SDL_HasIntersection(&pers.sprites[courant].rectangle, &ennemi.sprites[courant].rectangle);
}


int combat_declenche(salle_t salle, perso_t pers, ennemi_t ennemi){

	if(salle.ennemi_present){
		if(collision_perso_ennemi(pers, ennemi, salle.x_ennemi1, salle.y_ennemi1))
			return TRUE;

		if(salle.nb_ennemi == 2)
			if(collision_perso_ennemi(pers, ennemi, salle.x_ennemi2, salle.y_ennemi2))
				return TRUE;

		return FALSE;
	}
	else
		return FALSE;
}
