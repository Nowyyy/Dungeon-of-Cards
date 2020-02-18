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
	charge_image(PORTE_PATH,&images[porte], rendu);
	charge_image(SOL2_PATH,&images[sol2], rendu);
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

	if(salle->id == 0){//affichage des commandes et rêgles du jeu si on est dans la première salle
		SDL_RenderCopy(rendu, images[commandes].img, NULL, &images[commandes].rectangle);
		SDL_RenderCopy(rendu, images[instructions].img, NULL, &images[instructions].rectangle);
	}

	afficher_salle(salle, rendu, images);

	SDL_RenderCopy(rendu, pers.sprites[0].img, NULL, &pers.sprites[0].rectangle);

	SDL_RenderPresent(rendu);//applique les modifs précédentes
}



/**

* \fn initisalise_salles


* \brief remplit les tableaux des salles, initialise les variables

*/
void initialise_salles(salle_t tab[], int taille){

	int i;

	for(i = 0; i < taille; i++){

		init_salle(tab[i].salle);

		tab[i].s_b = -1;
		tab[i].s_h = -1;
		tab[i].s_g = -1;
		tab[i].s_d = -1;
		tab[i].nb_murs = 0;
		tab[i].nb_portes = 0;
		tab[i].id = i;
		tab[i].haut = 0;
		tab[i].bas = 0;
		tab[i].droite = 0;
		tab[i].gauche = 0;
	}
}


/**
* \fn porte_non_connectee

* \param salle, la salle dans laquelle on cherche

* \return -1 si toutes les portes sont connectées, sinon l'identifiant de la porte non connectée

* \brief renvoi l'identifiant d'une porte si elle est non connectée sinon -1

*/
int porte_non_connectee(salle_t salle){

	if(salle.bas == 1)
		return 2;
	if(salle.haut == 1)
		return 0;
	if(salle.droite == 1)
		return 1;
	if(salle.gauche == 1)
		return 3;

	return -1;
}



/**
* \fn cherche_portes_non_connectees

* \param *salles[], le tableau de pointeur sur les salles du labyrinthe
* \param taille, la taille du tableau
* \param indice, le premier indice à partir duquel chercher dans le tableau
* \param position, la position de la porte pour laquelle on cherche une liaison

* \return -1 si pas de porte trouvée, sinon l'indice du tableau correspondant

* \brief cherche et retourne les portes non connectées correspondant à la recherche en cours
*/
int cherche_porte_libre(salle_t salles[], int indice, int taille, int position){

	int i = taille - 1, position_salle;

	position_salle = inverse_porte(position);

	while(i >= 0){
		if(salles[i].bas == 1 && position_salle == 2 && i != indice){
			return i;
		}
		else if(salles[i].haut == 1 && position_salle == 0 && i != indice){
			return i;
		}
		else if(salles[i].droite == 1 && position_salle == 1 && i != indice){
			return i;
		}
		else if (salles[i].gauche == 1 && position_salle == 3 && i != indice){
			return i;
		}
		i--;
	}
	return -1;
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
				 tab[salle1].haut = 0;
				 tab[salle2].bas = 0;
				 break;
		case 1 : tab[salle1].s_d = salle2;
				 tab[salle2].s_g = salle1;
				 tab[salle1].droite = 0;
				 tab[salle2].gauche = 0;
				 break;
		case 2 : tab[salle1].s_b = salle2;
				 tab[salle2].s_h = salle1;
				 tab[salle1].bas = 0;
				 tab[salle2].haut = 0;
				 break;
		case 3 : tab[salle1].s_g = salle2;
				 tab[salle2].s_d = salle1;
				 tab[salle1].gauche = 0;
				 tab[salle2].droite = 0;
				 break;
	}
}



/**
* \fn generer_labyrinthe

* \param salle[], le tableau de salles du labyrinthe
* \param taille, la taille du tableau
* \param max_salles, le nombre maximal de salle que l'on veut créer
* \param taille_max, la taille maximale que peu prendre le tableau de salles

* \return la nouvelle taille du tableau en fonction des besoins suppélementaires ou non de mémoire

* \brief Génère aléatoirement un labyrinthe
*/
int generation_labyrinthe(salle_t salles[], int taille, int max_salles, int taille_max){

	srand(time(NULL));

	int deb = 0, fin = taille, salle_compatible, porte, porte2;

	while(deb < taille){

			aleatoire_porte(&salles[deb], rand()%4, taille);
			deb++;
	}

	deb = 0;

	while(deb < fin ){

		porte = porte_non_connectee(salles[deb]);

		if(porte > -1){//porte sans liaison détectée

			salle_compatible = cherche_porte_libre(salles, deb, fin, porte);

			if(salle_compatible > -1){//il y a une salle comportant une porte pouvant être réliée à celle-ci

				if(porte_disponible(salles, deb, salle_compatible)){
					cree_liaison(salles, deb, salle_compatible, porte);
				}
				else{
					do{
						salle_compatible = cherche_porte_libre(salles, deb, salle_compatible, porte);
					}while(!porte_disponible(salles, deb, salle_compatible) && salle_compatible != -1);

					if(salle_compatible != -1){
						cree_liaison(salles, deb, salle_compatible, porte);
					}
					else{
						fin = rajoute_salle_ou_ferme_porte(salles, deb, fin, porte, taille_max);
					}
				}
			}
			else{

				fin = rajoute_salle_ou_ferme_porte(salles, deb, fin, porte, taille_max);
			}
		}
		else{//toutes les portes ont une liaison vers une autre salle
			deb++;
		}
	}

	deb = 0;

	while(deb < fin){
		
		ferme_porte_inutile(salles, deb);
		verifie_porte_ouverte(salles, deb, fin);
		deb++;
	}

	for(int i = 0; i < fin; i++){
		rempli_tableau_murs_portes(salles, i);
	}

	return fin;
}


/**
* \fn boucle_labyrinthe

* \param *continuer, pointeur sur variable permettant de savoir si le joueur souhaite quitter le programme
* \param *etat, pointeur sur variable permettant de connaître l'écran dans lequel on est
* \param *rendu, le renderer sur lequel on dessine

* \brief Permet de gèrer toutes la partie labyrinthe, création, destruction, deplacement personnage...

*/
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu){


	image_t images[NB_TEXTURES];

	perso_t pers;

	pers.x = WIN_WIDTH / 2;
	pers.y = WIN_HEIGHT / 2;

	int taille = 10, taille_max = taille *2, salle_courante;

	salle_t salles[taille_max];

	charge_toutes_textures(images, &pers, rendu);

	initialise_salles(salles, taille_max);

	taille = generation_labyrinthe(salles, taille, taille, taille_max);

	salle_courante = 0;

	verifie_salles_accessibles(salles, taille);

	for(int i = 0; i < taille; i++)
		ferme_porte_inutile(salles, i);

	textures_aleatoires(salles, taille);

	while(*etat == labyrinthe && *continuer){

		affichage_salle_personnage(pers, &salles[salle_courante], rendu, images);

		deplacement_personnage(&pers, salles[salle_courante], continuer);

		salle_courante = changement_de_salle(&pers, salles[salle_courante], salle_courante);
	}

	//on libère tous les emplacements mémoires utilisés par les images
	SDL_DestroyTexture(images[instructions].img);
	SDL_DestroyTexture(images[commandes].img);
	SDL_DestroyTexture(pers.sprites[0].img);
	SDL_DestroyTexture(images[sol].img);
	SDL_DestroyTexture(images[mur].img);
	SDL_DestroyTexture(images[porte].img);
}