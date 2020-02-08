/**

* \file labyrinthe.c

* \author {Tudoret Aurélien, Jourry Axel, Marin Timothée, Malabry Thomas}

* \date 04/02/2020

* \version 0.1

* \brief contient et fait appel a toutes fonctions nécessaires pour la  gestion du labyrinthe
*/

#include "constantes.h"
#include "salle.h"
#include "initialisation_sdl_fonctions.h"
#include "personnage.h"
#include "file.h"



/**
* \fn charge_toutes_textures

* \param images[], contient toutes les images utilisées sauf celle du personnage
* \param *pers, pointeur sur la structure contenant le personnage
* \param *rendu, le renderer sur lequel on dessine

* \brief Permet de charger toutes les images et de les ranger dans les structures correspondantes

*/
void charge_toutes_textures(t_image images[], t_perso *pers, SDL_Renderer *rendu){

	charge_image(SOL1_PATH,&images[sol], rendu);
	charge_image(MUR1_PATH,&images[mur], rendu);
	charge_image(SOL2_PATH,&images[porte], rendu);
	charge_image(COMMANDES_PATH, &images[commandes], rendu);
	charge_image(INSTRUCTIONS_PATH, &images[instructions], rendu);

	charge_sprites_personnage(pers->sprites, rendu);

	//on donne les coordonnées pour placer les images des commandes et des instructions
	images[commandes].rectangle.x=0;
	images[commandes].rectangle.y=WIN_HEIGHT/4;
	images[instructions].rectangle.x=800;
	images[instructions].rectangle.y=WIN_HEIGHT/30;

	//on place le personnage dans la premiere salle, au centre
	pers->sprites[0].rectangle.x = pers->x;
	pers->sprites[0].rectangle.y = pers->y;
}


/**
* \fn affichage_salle_personnage

* \param images[], contient toutes les images utilisées sauf celle du personnage
* \param pers, la structure contenant le personnage
* \param *rendu, le renderer sur lequel on dessine

* \brief Permet d'afficher une salle, le personnage et si on est dans la premiere salle, les instructions et commandes du jeu

*/
void affichage_salle_personnage(t_perso pers, salle_t *salle, SDL_Renderer *rendu, t_image images[]){

	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	if(salle->salle_id == 0){//affichage des commandes et rêgles du jeu si on est dans la première salle
		SDL_RenderCopy(rendu, images[commandes].img, NULL, &images[commandes].rectangle);
		SDL_RenderCopy(rendu, images[instructions].img, NULL, &images[instructions].rectangle);
	}

	salle->nb_murs = afficher_salle(salle->salle, rendu, images, salle->murs);

	SDL_RenderCopy(rendu, pers.sprites[0].img, NULL, &pers.sprites[0].rectangle);

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}



/**
* \fn boucle_labyrinthe

* \param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
* \param *etat, pointeur sur variable permettant de connaître l'écran dans lequel on est 
* \param *rendu, le renderer sur lequel on dessine

* \brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...

*/
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu){


	t_image images[5];

	t_perso pers;

	pers.x = WIN_WIDTH / 2;
	pers.y = WIN_HEIGHT / 2;

	salle_t salle;
	salle.salle_prec = NULL;
	salle.salle_id = 0;//première salle

	//init la salle et créé les portes
	init_salle(salle.salle);
	aleatoire_porte(&salle, 3); //on indique -1 pour préciser qu'il n'y a pas besoin de génerer 
	//de porte d'arrivée car c'est la première salle

	charge_toutes_textures(images, &pers, rendu);

	
	while(*etat == labyrinthe && *continuer){

		affichage_salle_personnage(pers, &salle, rendu, images);

		deplacement_personnage(&pers, salle, continuer);
	}

	//on libère tous les emplacements mémoires utilisés par les images
	SDL_DestroyTexture(images[instructions].img);
	SDL_DestroyTexture(images[commandes].img);
	SDL_DestroyTexture(pers.sprites[0].img);
	SDL_DestroyTexture(images[sol].img);
	SDL_DestroyTexture(images[mur].img);
	SDL_DestroyTexture(images[porte].img);	
}
/*

void generation_laby_alea(salle_t *salle, int nb_salle, int porte_arrivee){

	if(!file_vide() && nb_salle != 0){
		salle_t *salle_cree = malloc(sizeof(salle_cree));
		int nb_portes;

		if(salle_cree == NULL){
			printf("Error création salle\n");
		}

		link_salle(salle_cree, salle, porte_arrivee);

		nb_salle -= aleatoire_porte(salle_cree, porte_arrivee);

		if(salle_cree->salle_haut != NULL && salle_cree->salle_haut != salle){
			generation_laby_alea()
		}
	}
}

*/
/**
* \fn link_salle()

* \param *dest, la salle de destination, celle ou l'on arrive
* \param *src, la salle d'ou l'on vient
* \param porte_arrivee, la porte par laquelle on arrive

* \brief Permet de lier la porte d'arrivée dans la salle destination à la salle de départ

*/
/*
void link_salle(salle_t *dest, salle_t *src, int porte_arrivee){

	switch(porte_arrivee){
		case -1 : dest->salle_prec = NULL; break;
		case 0 : dest->salle_haut = src; src->salle_bas = dest; break;
		case 1 : dest->salle_droite = src; src->salle_gauche = dest;break;
		case 2 : dest->salle_bas = src; src->salle_haut = dest; break;
		case 3 : dest->salle_gauche = src; src->salle_droite = dest; break;
	}
	if(dest->salle_prec != NULL)
		dest->salle_prec = src;
}
*/