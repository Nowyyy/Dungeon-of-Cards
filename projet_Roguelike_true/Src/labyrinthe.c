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
* \fn detruire_salles

*\bief détruit toues les salles créées dynamiquement par appel récusif

* \param *salle, la salle a détruire
*/
void detruire_salles(salle_t *salle[], int taille){

	for(int i = 0; i < taille; i++)
		free(salle[i]);

	free(salle);
}

/**
* \fn liaison_entre_salles

* \param *src, la salle source que l'on cherche a connecter
* \param *dest, la salle que l'on connecte à la salle source
* \param max_salles, le nombre maximun de salles que l'on souhaite créer

* \brief effectue la liaison entre deux salles et créée la porte correspondante dans la salle dest
*/
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


/**
*\fn creer_salles

* \param *salles[], le tableau de pointeur sur les salles du labyrinthe
* \param taille, la taille du tableau

* \brief créé les salles dynamiqueùent, mets les pointeurs à NULL, initialise l'intérieur des salles

*/
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


/**
* \fn cherche_portes_non_connectees

* \param *salles[], le tableau de pointeur sur les salles du labyrinthe
* \param taille, la taille du tableau
* \param indice, le premier indice à partir duquel chercher dans le tableau
* \param position, la position de la porte pour laquelle on cherche une liaison

* \return -1 si pas de porte trouvée, sinon l'indice du tableau correspondant

* \brief cherche et retourne les portes non connectées correspondant à la recherche en cours
*/
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

/**
* \fn porte_non_connectee

* \param *salle, la salle dans laquelle on cherche

* \return -1 si toutes les portes sont connectées, sinon l'identifiant de la porte non connectée

* \brief renvoi l'identifiant d'une porte si elle est non connectée sinon -1

*/
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


/**
* \fn cree_liaisons

* \param *s1, la première salle pour laquelle on effectue les liaisons
* \param *s2, la seconde salle pour laquelle on effectue les liaisons
* \param porteS1, la porte de la première salle à laquelle on va rattacher la seconde

* \brief Créée les liaisons entre deux salles enfonction de la porte libre sur la première
*/
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


/**
* \fn cree_salle_copine_et_lie

* \param *s1, la première salle pour laquelle on effectue les liaisons
* \param *s2, la seconde salle pour laquelle on effectue les liaisons
* \param porteS1, la porte de la première salle à laquelle on va rattacher la seconde

* \brief Créée les liaisons entre deux salles, et créé la porte dans la seconde en fonction de la porte libre sur la première
*/
void cree_salle_copine_et_lie(salle_t *s1, salle_t **s2, int porteS1){

	switch(porteS1){

	case 0 : s1->salle_haut = (*s2); 
			 (*s2)->salle_bas = s1;

			 aleatoire_porte((*s2), 2, 0);
			 break;
	case 1 : s1->salle_droite = (*s2); 
			 (*s2)->salle_gauche = s1;
			 s1->droite = 0;
			 aleatoire_porte((*s2), 3, 0);
			 break;
	case 2 : s1->salle_bas = (*s2); 
			 (*s2)->salle_haut = s1;
			 s1->bas = 0;
			 aleatoire_porte((*s2), 0, 0);
			 break;
	case 3 : s1->salle_gauche = (*s2); 
			 (*s2)->salle_droite = s1;
			 s1->gauche = 0;
			 aleatoire_porte((*s2), 1, 0);
			 break;
	}

	(*s2)->bas = 0;
	(*s2)->droite = 0;
	(*s2)->gauche = 0;
	(*s2)->haut = 0;
}


/**

* \fn connecte_salles_restantes

* \param *salles[], le tableau de pointeur sur les salles du labyrinthe
* \param taille, la taille du tableau
* \param memoire_en_plus, l'espace mémoire supplémentaire alloué en cas de besoin, afin de créer des salles supplémentaires

* \return la nouvelle taille du tableau en fonction des besoins suppélementaires ou non de mémoire

* \brief connecte les salles restantes dont certaines portes sont sans liaisons. Connecte uniquement entres elles des portes opposées.
*/
int connecte_salles_restantes(salle_t *salles[], int taille, int memoire_en_plus){

	int i = 0, porte, salle_copine;

	while(i < taille || i < memoire_en_plus){
		porte =  porte_non_connectee(salles[i]);

		if(porte >= 0){
			salle_copine = cherche_portes_non_connectees(salles, taille, i+1, porte);
			if(salle_copine != -1)
				cree_liaisons(salles[i], salles[salle_copine], porte);
			else{
				taille++;
				cree_salle_copine_et_lie(salles[i], &salles[taille], porte);
				i++;
			}
		}
		else{
			i++;
		}
	}

	return taille;
}


/**
* \fn generer_labyrinthe_aleatoire

* \param *salle[], le tableau de pointeur sur les salles du labyrinthe
* \param taille, la taille du tableau

* \return la nouvelle taille du tableau en fonction des besoins suppélementaires ou non de mémoire

* \brief Génère aléatoirement un labyrinthe
*/
int generer_labyrinthe_aleatoire(salle_t *salles[], int taille){

	int max_salles = taille - 1, indice = 0, fin = taille -1, taille_provisoire = taille * 4;
	srand(time(NULL));

	creer_salles(salles, taille_provisoire);

	while(max_salles > 0 || indice < taille && indice != fin){

		salles[indice]->nb_portes = aleatoire_porte(salles[indice], -1, max_salles);

		max_salles -= salles[indice]->nb_portes;

		for(int j = 0; j < salles[indice]->nb_portes; j++, fin--){
			liaison_entre_salles(salles[indice], salles[fin], max_salles);
		}
		indice++;
	}

	taille = connecte_salles_restantes(salles, taille, taille_provisoire);
	for(int i = 0; i < taille; i++){
		rempli_tableau_murs_portes(salles[i]);
	}

	for(int i = taille_provisoire; i > taille; i--)
		free(salles[i]);

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

	taille = generer_labyrinthe_aleatoire(salles, taille);

	charge_toutes_textures(images, &pers, rendu);

	salle_depart = salles[0];

	salle_courante = salle_depart;
	
	while(*etat == labyrinthe && *continuer){

		affichage_salle_personnage(pers, salle_courante, rendu, images);

		deplacement_personnage(&pers, *salle_courante, continuer);

		salle_courante = changement_de_salle(&pers, salle_courante);
	}

	detruire_salles(salles, taille);

	//on libère tous les emplacements mémoires utilisés par les images
	SDL_DestroyTexture(images[instructions].img);
	SDL_DestroyTexture(images[commandes].img);
	SDL_DestroyTexture(pers.sprites[0].img);
	SDL_DestroyTexture(images[sol].img);
	SDL_DestroyTexture(images[mur].img);
	SDL_DestroyTexture(images[porte].img);	
}