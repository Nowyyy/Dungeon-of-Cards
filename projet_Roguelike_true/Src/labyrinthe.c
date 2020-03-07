/**

* \file labyrinthe.c

* \author {Tudoret Aurélien, Jourry Axel, Marin Timothée, Malabry Thomas}

* \date 04/02/2020

* \version 0.1

* \brief contient et fait appel a toutes fonctions nécessaires pour la  gestion du labyrinthe
*/

#include "../include/constantes.h"
#include "../include/salle.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/personnage.h"
#include "../include/fonctions.h"
#include "../include/sauvegardefonc.h"

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
	charge_image(MUR2_PATH,&images[mur2], rendu);
	charge_image(PORTE_PATH,&images[porte], rendu);
	charge_image(SOL2_PATH,&images[sol2], rendu);
	charge_image(SOL3_PATH,&images[sol3], rendu);
	charge_image(COMMANDES_PATH, &images[commandes], rendu);
	charge_image(INSTRUCTIONS_PATH, &images[instructions], rendu);
	charge_image(GAMEOVER_PATH, &images[gameover], rendu);
	charge_image(DEATHLIGHT_PATH, &images[deathlight], rendu);

	charge_sprites_personnage(pers->sprites, rendu);

	//on donne les coordonnées pour placer les images des commandes et des instructions
	images[commandes].rectangle.x = 0;
	images[commandes].rectangle.y = WIN_HEIGHT/4;
	images[instructions].rectangle.x = 800;
	images[instructions].rectangle.y = WIN_HEIGHT/30;
	images[gameover].rectangle.x = 135;
	images[gameover].rectangle.y = -100;
	images[deathlight].rectangle.x = pers->x-100;
	images[deathlight].rectangle.y = pers->y-65;

	//on place le personnage dans la premiere salle, au centre
	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;
}


/**
* \fn affichage_salle_personnage

* \param images[], contient toutes les images utilisées sauf celle du personnage
* \param pers, la structure contenant le personnage
* \param *rendu, le renderer sur lequel on dessine

* \brief Permet d'afficher une salle, le personnage et si on est dans la premiere salle, les instructions et commandes du jeu

*/
void affichage_salle_personnage(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[], ennemi_t monstre, ennemi_t boss){

	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

	if(salle->id == 0){//affichage des commandes et rêgles du jeu si on est dans la première salle
		SDL_RenderCopy(rendu, images[commandes].img, NULL, &images[commandes].rectangle);
		SDL_RenderCopy(rendu, images[instructions].img, NULL, &images[instructions].rectangle);
	}

	afficher_salle(salle, rendu, images);

	SDL_RenderCopy(rendu, pers.sprites[courant].img, NULL, &pers.sprites[courant].rectangle);

	if(salle->ennemi_present){

		monstre.sprites[courant].rectangle.x = (salle->x_ennemi1 * TAILLE_IMAGE) + EMPLACEMENT_DEPART_DESSIN_SALLE_X;
		monstre.sprites[courant].rectangle.y = (salle->y_ennemi1 * TAILLE_IMAGE) + EMPLACEMENT_DEPART_DESSIN_SALLE_Y;
		
		if(salle->pv1)
			SDL_RenderCopy(rendu, monstre.sprites[courant].img, NULL, &monstre.sprites[courant].rectangle);
		else
			SDL_RenderCopy(rendu, monstre.sprites[courant+1].img, NULL, &monstre.sprites[courant].rectangle);

		if(salle->nb_ennemi == 2){
			monstre.sprites[courant].rectangle.x = (salle->x_ennemi2 * TAILLE_IMAGE) + EMPLACEMENT_DEPART_DESSIN_SALLE_X;
			monstre.sprites[courant].rectangle.y = (salle->y_ennemi2 * TAILLE_IMAGE) + EMPLACEMENT_DEPART_DESSIN_SALLE_Y;

			if(salle->pv2)
				SDL_RenderCopy(rendu, monstre.sprites[courant].img, NULL, &monstre.sprites[courant].rectangle);
			else
				SDL_RenderCopy(rendu, monstre.sprites[courant+1].img, NULL, &monstre.sprites[courant].rectangle);
		}
	}

	if(salle->boss){
		SDL_RenderCopy(rendu, boss.sprites[courant].img, NULL, &boss.sprites[courant].rectangle);
	}

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}



/**

* \fn initisalise_salles


* \brief remplit les tableaux des salles, initialise les variables

*/
void initialise_salles(salle_t tab[], int taille){

	int i, alea;

	for(i = 0; i < taille; i++){

		init_salle(tab[i].salle);

		tab[i].s_b = -1;
		tab[i].s_h = -1;
		tab[i].s_g = -1;
		tab[i].s_d = -1;
		tab[i].nb_murs = 0;
		tab[i].nb_portes = 0;
		tab[i].id = i;
		tab[i].salle_existe = FALSE;
	}
}



/**
* \fn cree_liaison

* \param *s1, la première salle pour laquelle on effectue les liaisons
* \param *s2, la seconde salle pour laquelle on effectue les liaisons
* \param porteS1, la porte de la première salle à laquelle on va rattacher la seconde

* \brief Créée les liaisons entre deux salles enfonction de la porte libre sur la première
*/
void cree_liaison(salle_t tab[], int salle1, int salle2, int porteS1){

	switch(porteS1){

		case 0 : tab[salle1].s_h = salle2;
				 tab[salle2].s_b = salle1;
				 break;
		case 1 : tab[salle1].s_d = salle2;
				 tab[salle2].s_g = salle1;
				 break;
		case 2 : tab[salle1].s_b = salle2;
				 tab[salle2].s_h = salle1;
				 break;
		case 3 : tab[salle1].s_g = salle2;
				 tab[salle2].s_d = salle1;
				 break;
	}
}


/**
* \fn mort

* \param *etat, variable contenant le mode de jeu actuel
* \param *pers, contient le personnage afin de le sauvegarder
* \param *rendu, le renderer sur lequel on dessine
* \param gameOverMusic, musique de mort du joueur
* \param gameOverFrame, bruit de mort du joueur
* \param images[], contient toutes les images du jeu sauf celles du personnage

* \param pers
* \param cartes

* \brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...

*/

void mort(int *etat, perso_t *pers, SDL_Renderer *rendu, Mix_Music *gameOverMusic, Mix_Chunk *gameOverFrame, image_t images[], TTF_Font *police, SDL_Texture *cmpPartie_texture){
	int mort_tmp;

	int x_cmpPartie = WIN_WIDTH / 2-90;
	int y_cmpPartie = WIN_HEIGHT * 0.8;

	//textes
	SDL_Rect cmpPartie_text, rect;

	char cmpPartie[20];

	Mix_HaltMusic();

	//Reinitialisation de la sauvegarde et compteur de mort
	mort_tmp = pers->cmpMort;

	initialise_personnage(pers);

	pers->cmpMort = mort_tmp+1;

  	saveperso(pers);

	//Apparition du rectangle de mort

 	rect.x = 405;
 	rect.y = 231;
 	rect.w = 270;
 	rect.h = 155;

 	//aggrandissement progressif du rectangle
 	while(rect.w <= WIN_WIDTH){
 		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		Mix_PlayChannel(0, gameOverFrame, 0);
  	SDL_RenderFillRect(rendu, &rect);
  	SDL_RenderPresent(rendu);
		SDL_Delay(500);

		rect.x -= 135;
		rect.y -= 77;
		rect.w += 270;
		rect.h += 155;
 	}

	if(pers->cmpMort ==1){
		sprintf(cmpPartie, "%dere mort", pers->cmpMort);
	}
	else{
		sprintf(cmpPartie, "%d morts", pers->cmpMort);
	}

	//Ecran de game over
		//Musique
		Mix_VolumeMusic(64);
		Mix_PlayMusic(gameOverMusic, 1);

		//Fond noir et logo game over
		SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir
		SDL_RenderClear(rendu);
		SDL_RenderCopy(rendu, images[gameover].img, NULL, &images[gameover].rectangle);

		//halo lumineux
		SDL_RenderCopy(rendu, images[deathlight].img, NULL, &images[deathlight].rectangle);

		//Sprite perso mort
		pers->sprites[dead].rectangle.x = pers->x-50;
		pers->sprites[dead].rectangle.y = pers->y;
		pers->sprites[courant] = pers->sprites[dead];
		SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);


	get_text_and_rect(rendu, x_cmpPartie, y_cmpPartie, cmpPartie, police, &cmpPartie_texture, &cmpPartie_text);
	SDL_RenderCopy(rendu, cmpPartie_texture, NULL, &cmpPartie_text);

	SDL_RenderPresent(rendu);

	//Des que la musique s'arrête, on revient au menu principal
 	while(Mix_PlayingMusic() == 1);

 	*etat = mainMenu;
}


/**
* \fn boucle_labyrinthe

* \param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
* \param *etat, pointeur sur variable permettant de connaître l'écran dans lequel on est
* \param *rendu, le renderer sur lequel on dessine
* \param *change_salle, le son de changement de salle
* \param *footsteps, les bruits de pas du personnage
* \param *gameOverMusic, la musique de mort
* \param *gameOverFrame, les bruits de mort
* \param *pers, le renderer sur lequel on dessine
* \param cartes

* \brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...

*/
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu, Mix_Chunk *change_salle, Mix_Chunk *footsteps, Mix_Music *gameOverMusic, Mix_Chunk *gameOverFrame, perso_t *pers, carte_t *cartes, TTF_Font *police){


/////////////////////////// Déclarations variables ////////////////////////////////////////////
	image_t images[NB_TEXTURES];

	int taille = 5, nb_salles_a_creer = 10, salle_courante = 0;

	salle_t salles[taille*taille];

	SDL_Texture *cmpPartie_texture;

	animation_t anim;

	ennemi_t *ennemi = creer_ennemi("Squelette", 10, 10, 10, 10, squelette, rendu);
	ennemi_t *boss = creer_ennemi("Minotaure", 10, 10, 10, 10, minotaure, rendu);

	printf("\nLet's go ! \n\n");

/////////////////////////// Génération aléatoire ////////////////////////////////////////////

	creation_labyrinthe(salles, taille, nb_salles_a_creer);
/////////////////////////// Textures ///////////////////////////////////////////////////////

	init_animations(&anim);

	charge_toutes_textures(images, pers, rendu);

	textures_aleatoires(salles, taille*taille);

	place_monstre_coffre_boss(salles, taille*taille);

/////////////////////////// boucle du labyrinthe / explo / combat ///////////////////////////
	while(*etat == labyrinthe && *continuer){

		affichage_salle_personnage(*pers, &salles[salle_courante], rendu, images, *ennemi, *boss);

		deplacement_personnage(pers, salles[salle_courante], continuer, &anim, footsteps);

		//Si le joueur meurt
		if(pers->pv <= 0){
			mort(etat, pers, rendu, gameOverMusic, gameOverFrame, images, police, cmpPartie_texture);
		}

		salle_courante = changement_de_salle(pers, salles[salle_courante], salle_courante, change_salle);

		//Tester animation de mort
		//pers->pv -= 1;

		//collision avec un ennemi
		if(salle_courante == taille - 1 && combat_declenche(salles[salle_courante], *pers, *boss)){
			//combat_t_p_t(pers, boss, cartes);
			if(boss->pv == 0){
				//etage suivant
			}
		}
		if(combat_declenche(salles[salle_courante], *pers, *ennemi) == 1){
			//salles[salle_courante].pv1 = combat_t_p_t(pers, ennemi, cartes);
		}
		else if(combat_declenche(salles[salle_courante], *pers, *ennemi) == 2){
			//salles[salle_courante].pv2 = combat_t_p_t(pers, ennemi, cartes);
		}
	}

//////////////////////// On libère tous les emplacements mémoires utilisés par les images ////
	for(int i = 0; i < NB_SPRITES_PERSONNAGE; i++)
		SDL_DestroyTexture(pers->sprites[i].img);

	for(int i = sol; i <= NB_TEXTURES-1; i++)
		SDL_DestroyTexture(images[i].img);

	detruire_ennemi(&ennemi);
	detruire_ennemi(&boss);

	SDL_DestroyTexture(cmpPartie_texture);
}




void creation_labyrinthe(salle_t salles[], int taille, int nb_salles_a_creer){


	int i = 0, porte, nouvelle_salle, porte_nouv_salle;

	initialise_salles(salles, taille*taille); //initialisation de toutes les salles.

	salles[i].salle_existe = TRUE;

	while(nb_salles_a_creer > 0){

		printf("Salle %2d ", i);

		porte = tirage_au_sort_porte_a_creer(i, taille, salles);
		printf("Porte %2d ", porte);
		ajout_porte_salle(salles[i].salle, porte);
		nouvelle_salle = indice_salle(i, porte, taille);
		printf("nouvelle_salle %2d ", nouvelle_salle);
		porte_nouv_salle = inverse_porte(porte);
		printf("Porte %2d ", porte_nouv_salle);
		ajout_porte_salle(salles[nouvelle_salle].salle, porte_nouv_salle);
		cree_liaison(salles, i, nouvelle_salle, porte);
		salles[nouvelle_salle].salle_existe = TRUE;
		salles[i].boss = FALSE;

		i = nouvelle_salle;
		nb_salles_a_creer --;
		printf("next\n");
	}

	salles[i].boss = TRUE;

	for(i = 0; i < taille * taille -1; i++){
		if(salles[i].salle_existe)
			rempli_tableau_murs_portes(salles, i);
	}
}



int tirage_au_sort_porte_a_creer(int indice, int taille, salle_t salles[]){

	int alea = rand()%4;

	if(indice == 0 && (alea == haut || alea == gauche)) //première case du tableau
	//on ne peut créer de liaison vers le haut ou la gauche
		return tirage_au_sort_porte_a_creer(indice, taille, salles);

	else if(indice % taille == 0 && alea == gauche)//colonnes toutes a droite du tableau
	//on ne peut créer de liaison vers la gauche
		return tirage_au_sort_porte_a_creer(indice, taille, salles);

	else if(indice + 1 % taille == 0 && alea == droite)//colonnes toutes a gauche du tableau
	//on ne peut créer de liaison vers la droite
		return tirage_au_sort_porte_a_creer(indice, taille, salles);

	else if(indice < taille && alea == haut)//lignes toutes en haut du tableau
	//on ne peut créer de liaison vers le haut
		return tirage_au_sort_porte_a_creer(indice, taille, salles);

	else if(indice > (taille * taille - taille -1) && alea == bas)//lignes toutes en bas du tableau
	//on ne peut créer de liaison vers le bas
		return tirage_au_sort_porte_a_creer(indice, taille, salles);


	else if(alea == haut && salles[indice].s_h == -1)
		return alea;
	else if(alea == bas && salles[indice].s_b == -1)
		return alea;
	else if(alea == droite && salles[indice].s_b == -1)
		return alea;
	else if(alea == gauche && salles[indice].s_g == -1)
		return alea;
	else
		return tirage_au_sort_porte_a_creer(indice, taille, salles);
}


int indice_salle(int salle_actuelle, int porte_salle_actuelle, int taille){

	if(porte_salle_actuelle == bas)
		return salle_actuelle + taille;

	else if(porte_salle_actuelle == gauche)
		return salle_actuelle - 1;

	else if(porte_salle_actuelle == haut)
		return salle_actuelle - taille;

	else //obligatoirement a droite
		return salle_actuelle + 1;
}