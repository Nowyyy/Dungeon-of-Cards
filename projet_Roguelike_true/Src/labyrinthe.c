/**

*\file labyrinthe.c

*\author {Tudoret Aurélien, Jourry Axel, Marin Timothée, Malabry Thomas}

*\date 04/02/2020

*\version 0.1

*\brief contient et fait appel a toutes fonctions nécessaires pour la  gestion du labyrinthe
*/

#include "../include/constantes.h"
#include "../include/salle.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/personnage.h"
#include "../include/fonctions.h"
#include "../include/sauvegardefonc.h"
#include "../include/clavier.h"
#include "../include/ennemi.h"
#include "../include/coffre.h"
#include "../include/combat_tour_par_tour.h"

/**
*\fn void charge_toutes_textures(image_t images[], perso_t *pers, SDL_Renderer *rendu)

*\param images[], contient toutes les images utilisées sauf celle du personnage
*\param *pers, pointeur sur la structure contenant le personnage
*\param *rendu, le renderer sur lequel on dessine

*\brief Permet de charger toutes les images et de les ranger dans les structures correspondantes

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
	charge_image(HEART_PATH, &images[heart], rendu);
	charge_image(TRAPDOOR_PATH, &images[trapdoor], rendu);
	charge_image(TRAPDOOR_PATH, &images[trapdoor2], rendu);

	creer_texture_depuis_char(&images[pv], &images[etage], *pers, rendu);

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
	images[heart].rectangle.x = 25;
	images[heart].rectangle.y = WIN_HEIGHT * 0.10;
	images[trapdoor].rectangle.x = 0;
	images[trapdoor].rectangle.y = WIN_HEIGHT * 0.02;
	images[trapdoor2].rectangle.x = 610;
	images[trapdoor2].rectangle.y = 110;

	//on place le personnage dans la premiere salle, au centre
	pers->sprites[courant].rectangle.x = pers->x;
	pers->sprites[courant].rectangle.y = pers->y;
}


/**
*\fn void affichage_salle_personnage(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[], ennemi_t monstre, ennemi_t boss)

*\param images[], contient toutes les images utilisées sauf celle du personnage
*\param pers, la structure contenant le personnage
*\param *rendu, le renderer sur lequel on dessine

*\brief Permet d'afficher une salle, le personnage et si on est dans la premiere salle, les instructions et commandes du jeu

*/
void affichage_salle_personnage(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[], mini_map_t map){

	SDL_Rect rect;
	rect = map.map[0];
	rect.x -= 5;
	rect.y -= 5;
	rect.h = (map.taille / TAILLE_LABY) * TAILLE_RECT_MINI_MAP_H + 15;
	rect.w = (map.taille / TAILLE_LABY) * TAILLE_RECT_MINI_MAP_W + 15;

	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

///////////COMMANDES ET INSTRUCTIONS
	if(salle->depart ==TRUE && salle->prems == 0){//affichage des commandes et rêgles du jeu si on est dans la première salle
		SDL_RenderCopy(rendu, images[commandes].img, NULL, &images[commandes].rectangle);
		SDL_RenderCopy(rendu, images[instructions].img, NULL, &images[instructions].rectangle);
	}
	else{
///////////MINI MAP
		SDL_SetRenderDrawColor(rendu,169,169,169,255);//gris
		SDL_RenderDrawRect(rendu, &rect); // rectangle qui sert de cadre à la mini map

		for(int i = 0; i < map.taille; i++){

			if(map.salles_decouvertes[i] == TRUE && i == salle->id){
				//salle dans laquelle se situe le joueur
				SDL_SetRenderDrawColor(rendu,255,0,0,255);//rouge
				SDL_RenderFillRect(rendu, &map.map[i]);
			}
			else if(map.salles_decouvertes[i] == TRUE){
				SDL_SetRenderDrawColor(rendu,255,255,255,255);//blanc
				SDL_RenderFillRect(rendu, &map.map[i]);
			}
			else{
				SDL_SetRenderDrawColor(rendu,0,0,0,255);
				SDL_RenderFillRect(rendu, &map.map[i]);
			}
		}
	}

///////////SALLE
	afficher_salle(salle, rendu, images);

///////////PERSONNAGE
	SDL_RenderCopy(rendu, pers.sprites[courant].img, NULL, &pers.sprites[courant].rectangle);

///////////HUD
	SDL_RenderCopy(rendu, images[pv].img, NULL, &images[pv].rectangle);
	SDL_RenderCopy(rendu, images[etage].img, NULL, &images[etage].rectangle);
	SDL_RenderCopy(rendu, images[heart].img, NULL, &images[heart].rectangle);
	SDL_RenderCopy(rendu, images[trapdoor].img, NULL, &images[trapdoor].rectangle);

///////////SPRITES MONSTRES
	if(salle->ennemi_present || salle->boss){
		if(salle->ennemi->pv <= 0 && salle->boss){
			SDL_RenderCopy(rendu, images[trapdoor2].img, NULL, &images[trapdoor2].rectangle);
		}

		SDL_RenderCopy(rendu, salle->ennemi->sprites.img, &salle->ennemi->sprite_courant, &salle->ennemi->sprites.rectangle);

		if(salle->nb_ennemi == 2){

			SDL_RenderCopy(rendu, salle->ennemi2->sprites.img, &salle->ennemi2->sprite_courant, &salle->ennemi2->sprites.rectangle);
		}
	}
	else if(salle->coffre){
		SDL_RenderCopy(rendu, salle->coffre_salle.sprite.img, &salle->coffre_salle.sprite_courant, &salle->coffre_salle.sprite.rectangle);
	}

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}



/**

*\fn void initialise_salles(salle_t tab[], int taille)


*\brief remplit les tableaux des salles, initialise les variables

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
		tab[i].boss = FALSE;
		tab[i].ennemi_present = FALSE;
		tab[i].nb_ennemi = 0;
		tab[i].depart = FALSE;
		tab[i].decouverte = FALSE;
		tab[i].salle_existe = FALSE;
	}
}



/**
*\fn void cree_liaison(salle_t tab[], int salle1, int salle2, int porteS1)

*\param *s1, la première salle pour laquelle on effectue les liaisons
*\param *s2, la seconde salle pour laquelle on effectue les liaisons
*\param porteS1, la porte de la première salle à laquelle on va rattacher la seconde

*\brief Créée les liaisons entre deux salles enfonction de la porte libre sur la première
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
*\fn void mort(int *etat, perso_t *pers, SDL_Renderer *rendu, Mix_Music *gameOverMusic, Mix_Chunk *sounds[NB_SON], image_t images[], TTF_Font *police, SDL_Texture *cmpPartie_texture)

*\param *etat, variable contenant le mode de jeu actuel
*\param *pers, contient le personnage afin de le sauvegarder
*\param *rendu, le renderer sur lequel on dessine
*\param *musics[NB_MUSIC], tableau contenant les musiques
*\param *sounds[NB_SON], tableau contenant les sons
*\param images[], contient toutes les images du jeu sauf celles du personnage

*\brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...

*/

void mort(int *etat, perso_t *pers, SDL_Renderer *rendu, Mix_Music *musics[NB_MUSIC], Mix_Chunk *sounds[NB_SON], image_t images[], TTF_Font *police, SDL_Texture *cmpPartie_texture){
	int mort_tmp;

	int x_cmpPartie = WIN_WIDTH / 2-90;
	int y_cmpPartie = WIN_HEIGHT * 0.8;

	//textes
	SDL_Rect cmpPartie_text, rect;

	char cmpPartie[20];

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
 	while(rect.w < WIN_WIDTH){
 		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		Mix_PlayChannel(0, sounds[gameOverFrame], 0);
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

	//Fond noir et logo game over
	SDL_RenderClear(rendu);
	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderCopy(rendu, images[gameover].img, NULL, &images[gameover].rectangle);
	//Musique
	Mix_VolumeMusic(64);
	Mix_PlayMusic(musics[gameOverMusic], 1);


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

 	SDL_DestroyTexture(cmpPartie_texture);
}


/**
*\fn int tirage_au_sort_porte_a_creer(int indice, int taille, salle_t salles[])

*\param salles[], tableau des salles du labyrinthe
*\param taille, la taille d'une ligne ou d'une colonne du tableau
*\param indice, l'indice de la salle courante
*\param tentatives, le nombres d'essais pour trouver une liaison avec le jeu de données actuelles

*\return la direction valide dans laquelle créée une porte selon l'emplacement de la salle actuelle

*\brief Permet de renvoyer la direction vers laquelle on peut tenter de créer une liaison avec une autre salle

*/
int tirage_au_sort_porte_a_creer(int indice, int taille, salle_t salles[], int tentatives){

	int alea = rand()%4;

	if(indice == 0 && (alea == haut || alea == gauche)) //première case du tableau
	//on ne peut créer de liaison vers le haut ou la gauche
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);

	else if(indice == taille - 1 && (alea == haut || alea == droite))//case en bas à droite du tableau
	//on ne peut créer de liaison vers le haut ou la droite
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);

	else if(indice == taille * taille -1 && (alea == bas || alea == droite))//derniere case du tableau
	//on ne peut créer de liaison vers le bas ou la droite
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);

	else if(indice == (taille * taille - taille) && (alea == bas || alea == gauche))//première case de la dernière ligne du tableau
	//on ne peut créer de liaison vers le bas ou la gauche
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);

	else if(indice % taille == 0 && alea == gauche)//colonnes toutes a droite du tableau
	//on ne peut créer de liaison vers la gauche
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);

	else if((indice + 1) % taille == 0 && alea == droite)//colonnes toutes a gauche du tableau
	//on ne peut créer de liaison vers la droite
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);

	else if(indice < taille && alea == haut)//lignes toutes en haut du tableau
	//on ne peut créer de liaison vers le haut
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);

	else if(indice > (taille * taille - taille) && alea == bas)//lignes toutes en bas du tableau
	//on ne peut créer de liaison vers le bas
		return tirage_au_sort_porte_a_creer(indice, taille, salles, tentatives++);


	else if(alea == haut && salles[indice].s_h == -1 && salles[alea].s_b == -1)
		return alea;
	else if(alea == bas && salles[indice].s_b == -1 && salles[alea].s_h == -1)
		return alea;
	else if(alea == droite && salles[indice].s_b == -1 && salles[alea].s_g == -1)
		return alea;
	else if(alea == gauche && salles[indice].s_g == -1 && salles[alea].s_d == -1)
		return alea;
	else{
		if(tentatives >= taille){
			return -1;
		}
		else{
			return tirage_au_sort_porte_a_creer(indice, taille, salles, ++tentatives);
		}
	}
}



/**
*\fn int indice_salle(int salle_actuelle, int porte_salle_actuelle, int taille)

*\param salle_actuelle, l'indice de la salle ou l'on se trouve actuellement
*\param porte_salle_actuelle, la porte par laquelle on passe pour rejoindre une autre salle
*\param taille, la taille d'une ligne ou d'une colonne du tableau

*\return l'indice de la salle à lier avec la salle courante

*\brief Renvoie l'indice d'une salle correspondant à la direction dans laquelle on crée la porte
*/
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



/**
*\fn int salles_compatibles(int salle1, int porte1, int salle2, int porte2, salle_t salles[])

*\param salle1, la première salle qu'on cherche a lier
*\param porte1, la porte de la salle1 pour laquelle on cherche une correspondance dans la salle 2
*\param salle2, la seconde salle qu'on cherche a lier
*\param porte2, la porte de la salle2 pour laquelle on cherche une correspondance dans la salle 1

*\return True si les salles sont compatibles, false sinon

*\brief Permet de savoir si deux salles sont compatibles entre elles
*/
int salles_compatibles(int salle1, int porte1, int salle2, int porte2, salle_t salles[]){

	if(porte1 == droite && salles[salle1].s_d == -1 && porte2 == gauche && salles[salle2].s_g == -1)
		return TRUE;

	else if(porte1 == gauche && salles[salle1].s_g == -1 && porte2 == droite && salles[salle2].s_d == -1)
		return TRUE;

	else if(porte1 == bas && salles[salle1].s_b == -1 && porte2 == haut && salles[salle2].s_h == -1)
		return TRUE;

	else if(porte1 == haut && salles[salle1].s_h == -1 && porte2 == bas && salles[salle2].s_b == -1)
		return TRUE;

	else
		return FALSE;
}



/**
*\fn int creation_labyrinthe(salle_t salles[], int taille, int nb_salles_a_creer)

*\param salles[], le tableau contenant les salles du jeu
*\param taille, la taille d'une ligne ou d'une colonne du tableau
*\param nb_salles_a_creer, le nombre de salles que l'on souhaite pouvoir parcourir dans le donjon

*\brief créer un labyrinthe de salles connectées entres elles, généré aléatoirement

*\return l'indice de la première salle du laby
*/
int creation_labyrinthe(salle_t salles[], int taille, int nb_salles_a_creer){

	int i = 0, porte, nouvelle_salle, porte_nouv_salle, cpt, alea, cpt2, j;
	int salle_crees[nb_salles_a_creer], taille_tab = 0;

	initialise_salles(salles, taille*taille); //initialisation de toutes les salles.

	do{
		if(taille_tab == 0){
			//on ajoute la première salle au tableau
			alea = rand()%(taille*taille);
			salle_crees[taille_tab++] = alea;
			i = alea;
		}
		else{
			//des salles existent déjà
			alea = rand()%taille_tab;
			i = salle_crees[alea];
		}

		cpt = 0;
		cpt2 = 0;

		//on boucle tant qu'aucune salle ne répond aux critères pour faire une liaison
		do{
			//on boucle tant qu'aucune porte possible n'est trouvée
			do{
				porte = tirage_au_sort_porte_a_creer(i, taille, salles, 0);
				cpt2++;

				if(cpt2 > taille){
					//la fonction récursive n'a pas réussie à trouver de liaisons compatibles
					i = salle_crees[rand()%taille_tab];
					cpt2 = 0;
				}
			}while(porte == -1);

			nouvelle_salle = indice_salle(i, porte, taille);
			porte_nouv_salle = inverse_porte(porte);

			if(cpt >= 5){
			//si aucune salle n'est trouvée malgré plusieurs tentatives, on rècupère la salle précédente et on tente avec elle
				i = salle_crees[rand()%taille_tab];
				cpt = 0;
			}
			else
				cpt++;
		}while(salles_compatibles(i, porte, nouvelle_salle, porte_nouv_salle, salles) == FALSE);

		ajout_porte_salle(salles[i].salle, porte);
		ajout_porte_salle(salles[nouvelle_salle].salle, porte_nouv_salle);
		cree_liaison(salles, i, nouvelle_salle, porte);

		salles[nouvelle_salle].salle_existe = TRUE;
		salles[i].boss = FALSE;

		for(j = 0; j < taille_tab && salle_crees[j] != nouvelle_salle; j++);

		if(j >= taille_tab)
			salle_crees[taille_tab++] = nouvelle_salle;
		nb_salles_a_creer --;

	}while(nb_salles_a_creer > 0);

	salles[i].boss = TRUE; // on marque tout de suite la salle du boss
	salles[salle_crees[0]].salle_existe = TRUE;
	salles[salle_crees[0]].depart = TRUE;

	//si le boss a été placé dans la première salle, on le déplace ailleurs aléatoirement
	if(salles[salle_crees[0]].boss == TRUE){
		salles[salle_crees[0]].boss = FALSE;
		alea = rand()%taille_tab + 1;
		if(alea == taille_tab)
			alea--;
		salles[salle_crees[alea]].boss = TRUE;
	}

	//remplissage tableau de collisions pour les murs et les portes
	for(i = 0; i < taille * taille; i++){
		rempli_tableau_murs_portes(salles, i);
	}

	return salle_crees[0];
}


/**
*\fn void modifie_texture_hud(perso_t *pers, image_t *pv, image_t *etage, SDL_Renderer *rendu)

*\param *pers, la structure contenant le personnage
*\param *pv, la structure contenant la texture du HUD représentant les PV du personnage
*\param *etage, la structure contenant la texture du HUD représentant l'étage où se situe le personnage
*\param *rendu, le renderer sur lequel on dessine

*\brief Permet de mettre à jour le HUD selon que les PDV ou l'étage soit différents
*/
void modifie_texture_hud(perso_t *pers, image_t *pv, image_t *etage, SDL_Renderer *rendu){

	if(pers->pv != pers->pv_old || pers->etage != pers->etage_old){
		pers->pv_old = pers->pv;
		pers->etage_old = pers->etage;
		SDL_DestroyTexture(pv->img);
		SDL_DestroyTexture(etage->img);
		creer_texture_depuis_char(pv, etage, *pers, rendu);
	}
}



/**
*\fn int nb_salles_par_etage(int etage)

*\param etage, l'étage où se situe le joueur

*\return le nombres de salles à créer pour cet étage
*\brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...
*/
int nb_salles_par_etage(int etage){

	switch(etage){

		case 1 : return NB_SALLES_LEVEL_1;
		case 2 : return NB_SALLES_LEVEL_2;
		case 3 : return NB_SALLES_LEVEL_3;
		case 4 : return NB_SALLES_LEVEL_4;
		default : return NB_SALLES_LEVEL_1;
	}
}



/**
*\fn void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], Mix_Music *gameOverMusic, perso_t *pers, carte_t *cartes, TTF_Font *police)

*\param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
*\param *etat, pointeur sur variable permettant de connaître l'écran dans lequel on est
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons
*\param *musics[NB_MUSIC], tableau contenant les musiques
*\param *pers, le renderer sur lequel on dessine
*\param cartes

*\brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...
*/
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], perso_t *pers, TTF_Font *police){


/////////////////////////// Déclarations variables ////////////////////////////////////////////
	image_t images[NB_TEXTURES];

	SDL_Event event;

	int taille = TAILLE_LABY, nb_salles_a_creer = nb_salles_par_etage(pers->etage), salle_courante, salle_pred, salle_0;
	int mob_commun = rand()%minotaure, boss = rand()%minotaure + 3, boss_tuer = 0, trappe=0;

	mini_map_t miniMap;

	creation_mini_map(taille, &miniMap);

	salle_t salles[taille*taille];

	SDL_Texture *cmpPartie_texture;

	animation_t anim;

	touches_t clavier;

/////////////////////////// Génération aléatoire ////////////////////////////////////////////

	salle_courante = creation_labyrinthe(salles, taille, nb_salles_a_creer);
	salle_pred = salle_courante;
	salle_0 = salle_courante;
/////////////////////////// Textures et initialisations///////////////////////////////////////

	init_animations(&anim);

	charge_toutes_textures(images, pers, rendu);

	textures_aleatoires(salles, taille*taille);

	place_monstre_coffre_boss(salles, taille*taille, blob, rendu);

	for(int i = 0; i < taille * taille; i++){
		if(salles[i].boss){
			salles[i].ennemi = creer_ennemi(75, 10, 10, 10, boss, rendu);
		}
		else{
			creer_ennemi_pointeur(&salles[i].ennemi, &salles[i].ennemi2, salles[i].boss, salles[i].nb_ennemi, mob_commun, rendu);
			creer_coffre(&salles[i].coffre_salle, rendu, salles[i].coffre);
		}
	}

	ajoute_salle_decouverte(&miniMap, salle_courante);

	init_tab_clavier(clavier.tab);

/////////////////////////// boucle du labyrinthe / explo / combat ///////////////////////////
	while(*etat == labyrinthe && *continuer && boss_tuer==0){

		if((salles[salle_courante].nb_ennemi > 0 && salles[salle_courante].ennemi->pv > 0) || (salles[salle_courante].boss && salles[salle_courante].ennemi->pv > 0))
			animation_ennemi(salles[salle_courante].ennemi);

		if(salles[salle_courante].nb_ennemi == 2 && salles[salle_courante].ennemi2->pv > 0){
			animation_ennemi(salles[salle_courante].ennemi2);
		}

		if(salles[salle_courante].coffre){
			animation_coffre(pers, &salles[salle_courante], sounds);
		}

		modifie_texture_hud(pers, &images[pv], &images[etage], rendu);

		affichage_salle_personnage(*pers, &salles[salle_courante], rendu, images, miniMap);

		deplacement_personnage(pers, salles[salle_courante], continuer, &anim, sounds, &clavier);

		if(*continuer == TRUE){

			salle_courante = changement_de_salle(pers, salles[salle_courante], salle_courante, sounds);
			SDL_Delay(5);

			//collision avec un ennemi
			if(combat_declenche(salles[salle_courante], *pers) == 1 && salles[salle_courante].ennemi->pv > 0 && *etat == labyrinthe){
				init_tab_clavier(clavier.tab);
				combat_t_p_t(pers, salles[salle_courante].ennemi, rendu, images);
				init_tab_clavier(clavier.tab);
			}
			else if(combat_declenche(salles[salle_courante], *pers) == 2 && salles[salle_courante].ennemi2->pv > 0 && *etat == labyrinthe){
				init_tab_clavier(clavier.tab);
				combat_t_p_t(pers, salles[salle_courante].ennemi2, rendu, images);
				init_tab_clavier(clavier.tab);
			}

			//Si le joueur meurt
			if(pers->pv <= 0){
				Mix_HaltMusic();
				mort(etat, pers, rendu, musics, sounds, images, police, cmpPartie_texture);
			}

			if(pers->fuite){//le joueur à fuit le combat, on le renvoie dans la première salle du niveau
				pers->fuite = 0;
				salle_courante = salle_0;
			}

			if(salle_courante != salle_pred){
				salles[salle_courante].decouverte = TRUE;
				salles[salle_pred].prems = 1;
				salle_pred = salle_courante;
				ajoute_salle_decouverte(&miniMap, salle_courante);
			}

			//On fait apparaitre la trappe quand le boss meurt
			if(salles[salle_courante].boss && salles[salle_courante].ennemi->pv <= 0 && trappe==0){
				trappe = 1;
				pers->x = WIN_WIDTH / 2 - pers->sprites[courant].rectangle.w / 2;
				pers->y = WIN_HEIGHT / 2 - pers->sprites[courant].rectangle.h / 2;
			}

			//Si on passe sur la trappe on accède au niveau suivant
			if(salles[salle_courante].boss && trappe==1){
				if(pers->x > 585 && pers->y < 145){
					boss_tuer = 1;
					pers->etage+=1;
					pers->x = WIN_WIDTH / 2 - pers->sprites[courant].rectangle.w / 2;
					pers->y = WIN_HEIGHT / 2 - pers->sprites[courant].rectangle.h / 2;
				}
			}
		}
	}

	while (SDL_PollEvent (&event));

//////////////////////// On libère tous les emplacements mémoires utilisés par les images ////
	for(int i = 0; i < NB_SPRITES_PERSONNAGE; i++)
		SDL_DestroyTexture(pers->sprites[i].img);

	for(int i = sol; i < fond; i++)
		SDL_DestroyTexture(images[i].img);

	destruction_tous_ennemis(salles, taille);
	destruction_des_coffres(salles, taille);
}
