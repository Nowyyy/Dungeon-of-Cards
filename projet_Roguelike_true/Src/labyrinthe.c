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
#include <time.h>


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

	if(salle->salle_prec == NULL){//affichage des commandes et rêgles du jeu si on est dans la première salle
		SDL_RenderCopy(rendu, images[commandes].img, NULL, &images[commandes].rectangle);
		SDL_RenderCopy(rendu, images[instructions].img, NULL, &images[instructions].rectangle);
	}

	salle->nb_murs = afficher_salle(salle->salle, rendu, images, salle->murs);

	SDL_RenderCopy(rendu, pers.sprites[0].img, NULL, &pers.sprites[0].rectangle);

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}


/**

* \fn generation_laby_alea

* \param nb_salle, le nombre de salles restantes a créer

* \brief genere un labyrinthe aléatoire par appel récursif
*/
void generation_laby_alea(int nb_salle){

	salle_t *src, *dest = malloc(sizeof(salle_t));

	dest->salle_haut = NULL;
	dest->salle_bas = NULL;
	dest->salle_gauche = NULL;
	dest->salle_droite = NULL;
	dest->salle_prec = NULL;
	int nb = nb_salle, test = 0, porte_arrivee;

	if(!file_vide() || nb_salle != 0){

		retire_file(&src);

		//lie les salles entre elles
		if(src->haut == 1){
			src->salle_bas = dest;
			dest->salle_haut = src;
			src->haut = 0;
			test ++;
			porte_arrivee = 0;
		}
		else if(src->droite == 1){
			src->salle_gauche = dest;
			dest->salle_droite = src;
			src->droite = 0;
			test++;
			porte_arrivee = 1;
		}
		else if(src->bas == 1){
			src->salle_haut = dest;
			dest->salle_bas = src;
			src->bas = 0;
			test++;
			porte_arrivee = 2;
		}
		else if(src->gauche){
			src->salle_droite = dest;
			dest->salle_gauche = src;
			src->gauche = 0;
			test++;
			porte_arrivee = 3;
		}

		//remplit la salle et continue la generation alétoire
		if(test){
			init_salle(dest->salle);

			nb -= aleatoire_porte(dest, porte_arrivee, nb_salle);

			generation_laby_alea(nb);
		}
		else{
			//toutes les portes ont été pourvues en salle
			ajoute_file(src);
			free(dest);
			generation_laby_alea(nb_salle);
		}
	}
}


/**
*\fn creer_premiere_salle

*\brief permet la création de la premiere salle du labyrinthe puis d'appeler la génération du laby

* \param *salle, la salle que l'on créé
* \param nb_salles_a_creer, le nombre de salles dans la laby final
*/
void creer_premiere_salle(salle_t *salle, int nb_salles_a_creer){

	srand(time(NULL));

	salle->salle_prec = NULL;
	salle->salle_bas = NULL;
 	salle->salle_haut = NULL;
 	salle->salle_gauche = NULL;
 	salle->salle_droite = NULL;

	//initialise la salle et créé les portes dans la matrice
	init_salle(salle->salle);

	nb_salles_a_creer -= aleatoire_porte(salle, rand()%4, nb_salles_a_creer); //on indique -1 pour préciser qu'il n'y a pas besoin de génerer 
	//de porte d'arrivée car c'est la première salle

	generation_laby_alea(nb_salles_a_creer);
}


/**
* \fn detruire_salles

*\bief détruit toues les salles créées dynamiquement par appel récusif

* \param *salle, la salle a détruire
*/
void detruire_salles(salle_t *salle){

	salle_t *s_haut = NULL, *s_bas = NULL, *s_droite = NULL, *s_gauche = NULL;

	if(salle->salle_droite != NULL){
		s_droite = salle->salle_droite;
		salle->salle_droite->salle_gauche = NULL;
	}
	if(salle->salle_gauche != NULL){
		s_gauche = salle->salle_gauche;
	}
	if(salle->salle_bas != NULL){
		s_bas = salle->salle_bas;
		salle->salle_bas->salle_haut = NULL;
	}
	if(salle->salle_haut != NULL){
		s_haut = salle->salle_haut;
		salle->salle_haut->salle_bas = NULL;
	}	
	
	free(salle);

	if(s_haut != NULL)
		detruire_salles(s_haut);
	if(s_bas != NULL)
		detruire_salles(s_bas);
	if(s_gauche != NULL)
		detruire_salles(s_gauche);
	if(s_droite != NULL)
		detruire_salles(s_droite);
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

	int nb_salles_a_creer = 15;

	init_file();
	
	salle_t *salle_depart = malloc(sizeof(salle_t));
	salle_t *salle_courante;

	if(salle_depart == NULL)
		printf("Erreur création salle départ\n");

	creer_premiere_salle(salle_depart, nb_salles_a_creer);

	charge_toutes_textures(images, &pers, rendu);

	salle_courante = salle_depart;
	
	while(*etat == labyrinthe && *continuer){

		affichage_salle_personnage(pers, salle_courante, rendu, images);

		deplacement_personnage(&pers, *salle_courante, continuer);
	}

	detruire_salles(salle_depart);

	//on libère tous les emplacements mémoires utilisés par les images
	SDL_DestroyTexture(images[instructions].img);
	SDL_DestroyTexture(images[commandes].img);
	SDL_DestroyTexture(pers.sprites[0].img);
	SDL_DestroyTexture(images[sol].img);
	SDL_DestroyTexture(images[mur].img);
	SDL_DestroyTexture(images[porte].img);	
}