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
void charge_toutes_textures(image_t images[], perso_t *pers, SDL_Renderer *rendu){

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
void affichage_salle_personnage(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[]){

	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	if(salle->salle_prec == NULL){//affichage des commandes et rêgles du jeu si on est dans la première salle
		SDL_RenderCopy(rendu, images[commandes].img, NULL, &images[commandes].rectangle);
		SDL_RenderCopy(rendu, images[instructions].img, NULL, &images[instructions].rectangle);
	}

	afficher_salle(salle, rendu, images);

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

			rempli_tableau_murs_portes(dest);

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

	nb_salles_a_creer -= aleatoire_porte(salle, rand()%4, nb_salles_a_creer); 

	rempli_tableau_murs_portes(salle);

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

























void liaison_entre_salles(salle_t *src, salle_t *dest, int max_salles){

	if(src->haut == 1){
		src->haut = 0;
		src->salle_haut = dest;
		dest->salle_bas = src;
		dest->nb_portes = aleatoire_porte(dest, 0, max_salles);
	}
	else if(src->droite == 1){
		src->droite = 0;
		src->salle_droite = dest;
		dest->salle_gauche = src;
		dest->nb_portes = aleatoire_porte(dest, 1, max_salles);
	}
	else if(src->bas == 1){
		src->bas = 0;
		src->salle_bas = dest;
		dest->salle_haut = src;
		dest->nb_portes = aleatoire_porte(dest, 2, max_salles);
	}
	else if(src->gauche == 1){
		src->gauche = 0;
		src->salle_gauche = dest;
		dest->salle_droite = src;
		dest->nb_portes = aleatoire_porte(dest, 3, max_salles);
	}
}



//créé les salles par malloc, mets les pointeurs à NULL, initialise l'intérieur des salles
void creer_salles(salle_t *salles[], int taille){

	int i;

	for(i = 0; i < taille; i++){
		salles[i] = malloc(sizeof(salle_t));
		if(!salles[i])
			printf("Erreur création salles malloc\n");
		else{
			salles[i]->salle_haut = NULL;
			salles[i]->salle_bas = NULL;
			salles[i]->salle_droite = NULL;
			salles[i]->salle_gauche = NULL;
			salles[i]->salle_prec = NULL;
			salles[i]->haut = 0;
			salles[i]->bas = 0;
			salles[i]->gauche = 0;
			salles[i]->droite = 0;
		}
	}

	for(i = 0; i < taille; i++){
		init_salle(salles[i]->salle);
	}
}


int cherche_portes_non_connectees(salle_t *salles[], int taille, int indice, int position){

	int i = indice, position_salle;

	switch(position){
		case 0 : position_salle = 2; break;
		case 1 : position_salle = 3; break;
		case 2 : position_salle = 0; break;
		case 3 : position_salle = 1; break;
	}

	while(i < taille){
		if(salles[i]->bas && position_salle == 2){
			return i;
		}
		else if(salles[i]->haut && position_salle == 0){
			return i;
		}
		else if(salles[i]->droite && position_salle == 1){
			return i;
		}
		else if (salles[i]->gauche && position_salle == 3){
			return i;
		}
		i++;
	}
	return -1;
}

int porte_non_connectee(salle_t *salle){

	if(salle->bas)
		return 2;
	if(salle->haut)
		return 0;
	if(salle->droite)
		return 1;
	if(salle->gauche)
		return 3;

	return -1;
}


void cree_liaisons(salle_t *s1, salle_t *s2, int porteS1){

	switch(porteS1){

		case 0 : s1->salle_haut = s2; 
				 s2->salle_bas = s1;
				 s1->haut = 0;
				 s2->bas = 0;
				 break;
		case 1 : s1->salle_droite = s2; 
				 s2->salle_gauche = s1;
				 s1->droite = 0;
				 s2->gauche = 0;
				 break;
		case 2 : s1->salle_bas = s2; 
				 s2->salle_haut = s1;
				 s1->bas = 0;
				 s2->haut = 0;
				 break;
		case 3 : s1->salle_gauche = s2; 
				 s2->salle_droite = s1;
				 s1->gauche = 0;
				 s2->droite = 0;
				 break;
	}
}


void cree_salle_copine_et_lie(salle_t *s1, salle_t **s2, int porteS1){

	(*s2) = malloc(sizeof(salle_t));
	init_salle((*s2)->salle);

	if(!(*s2))
		printf("Erreur création salle copine\n");
	else{

		switch(porteS1){

		case 0 : s1->salle_haut = (*s2); 
				 (*s2)->salle_bas = s1;
				 (*s2)->haut = 0;
				 (*s2)->salle_haut = NULL;
				 (*s2)->salle_droite = NULL;
				 (*s2)->salle_gauche = NULL;
				 aleatoire_porte((*s2), 2, 0);
				 break;
		case 1 : s1->salle_droite = (*s2); 
				 (*s2)->salle_gauche = s1;
				 s1->droite = 0;
				 (*s2)->salle_haut = NULL;
				 (*s2)->salle_droite = NULL;
				 (*s2)->salle_bas = NULL; 
				 aleatoire_porte((*s2), 3, 0);
				 break;
		case 2 : s1->salle_bas = (*s2); 
				 (*s2)->salle_haut = s1;
				 s1->bas = 0;
				 (*s2)->salle_bas = NULL;
				 (*s2)->salle_droite = NULL;
				 (*s2)->salle_gauche = NULL;
				 aleatoire_porte((*s2), 0, 0);
				 break;
		case 3 : s1->salle_gauche = (*s2); 
				 (*s2)->salle_droite = s1;
				 s1->gauche = 0;
				 (*s2)->salle_haut = NULL;
				 (*s2)->salle_gauche = NULL;
				 (*s2)->salle_bas = NULL;
				 aleatoire_porte((*s2), 1, 0);
				 break;
		}

		(*s2)->bas = 0;
		(*s2)->droite = 0;
		(*s2)->gauche = 0;
		(*s2)->haut = 0;
	}

}


int connecte_salles_restantes(salle_t *salles[], int taille){

	int i = 0, porte, salle_copine;

	while(i < taille){
		porte =  porte_non_connectee(salles[i]);

		if(porte >= 0){
			salle_copine = cherche_portes_non_connectees(salles, taille, i+1, porte);
			if(salle_copine != -1)
				cree_liaisons(salles[i], salles[salle_copine], porte);
			else{
				salles = realloc(salles, sizeof(salle_t)*(taille+1));
				taille++;
				cree_salle_copine_et_lie(salles[i], &salles[taille-1], porte);
			}
		}
		else{
			i++;
		}
	}

	return taille;
}


int generer_labyrinthe_aleatoire(salle_t *salles[], int taille){

	int max_salles = taille - 1, indice = 0, fin = taille -1;
	srand(time(NULL));

	creer_salles(salles, taille);

	while(max_salles > 0 || indice < taille && indice != fin){

		salles[indice]->nb_portes = aleatoire_porte(salles[indice], -1, max_salles);

		max_salles -= salles[indice]->nb_portes;

		for(int j = 0; j < salles[indice]->nb_portes; j++, fin--){
			liaison_entre_salles(salles[indice], salles[fin], max_salles);
		}
		indice++;
	}

	taille = connecte_salles_restantes(salles, taille);

	for(int i = 0; i < taille; i++){
		rempli_tableau_murs_portes(salles[i]);
	}

	return taille;
}

/**
* \fn boucle_labyrinthe

* \param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
* \param *etat, pointeur sur variable permettant de connaître l'écran dans lequel on est 
* \param *rendu, le renderer sur lequel on dessine

* \brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...

*/
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu){


	image_t images[5];

	perso_t pers;

	pers.x = WIN_WIDTH / 2;
	pers.y = WIN_HEIGHT / 2;

	int taille = 15;

	salle_t **salles = malloc(sizeof(salle_t)*taille);
	
	salle_t *salle_depart, *salle_courante;

	//creer_premiere_salle(salle_depart, nb_salles_a_creer);
	taille = generer_labyrinthe_aleatoire(salles, taille);

	charge_toutes_textures(images, &pers, rendu);

	salle_depart = salles[0];

	salle_courante = salle_depart;
	
	while(*etat == labyrinthe && *continuer){

		affichage_salle_personnage(pers, salle_courante, rendu, images);

		deplacement_personnage(&pers, *salle_courante, continuer);
	}

	//detruire_salles(salle_depart);

	//on libère tous les emplacements mémoires utilisés par les images
	SDL_DestroyTexture(images[instructions].img);
	SDL_DestroyTexture(images[commandes].img);
	SDL_DestroyTexture(pers.sprites[0].img);
	SDL_DestroyTexture(images[sol].img);
	SDL_DestroyTexture(images[mur].img);
	SDL_DestroyTexture(images[porte].img);	
}