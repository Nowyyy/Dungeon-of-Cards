/**
*\file coffre.c
*\author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
*\date 14/03/2020
*\version 0.1

*\brief permet de gérer animation et drop d'objets des coffres
*/


#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"


/**
*\fn void animation_coffre(perso_t *pers, salle_t *salle, Mix_Chunk *sounds[NB_SON])

*\param *pers, la structure du personnage
*\param *salle, la salle dans laquelle se trouve le personnage
*\param *sounds[NB_SON], tableau contenant les sons

*\brief Permet d'effectuer l'animation du coffre s'il est en contact avec le joueur
*/
void animation_coffre(perso_t *pers, salle_t *salle, Mix_Chunk *sounds[NB_SON]){

	if(salle->coffre_salle.ouvert == 0 && (salle->coffre && (SDL_HasIntersection(&pers->sprites[courant].rectangle, &salle->coffre_salle.sprite.rectangle) || salle->coffre_salle.courant > 0))){
		//on est dans une salle avec un coffre et il n'a pas été ouvert

		if(salle->coffre_salle.courant < salle->coffre_salle.nb_sprites -1 && salle->coffre_salle.last + DELAIS_ANIMATIONS + 5 <= SDL_GetTicks()){

			salle->coffre_salle.sprite_courant.x += salle->coffre_salle.sprite_courant.w + salle->coffre_salle.gap;
			salle->coffre_salle.courant ++;
			salle->coffre_salle.last = SDL_GetTicks();

			if(salle->coffre_salle.son == 0){
				Mix_PlayChannel(2, sounds[chest], 0);
				salle->coffre_salle.son = 1;
			}


		}
		else if (salle->coffre_salle.courant == salle->coffre_salle.nb_sprites -1){
			salle->coffre_salle.ouvert = 1;
		}

	}

}


/**
*\fn void creer_coffre(coffre_t *coffre, SDL_Renderer *rendu, int coffre_existe)

*\param *coffre, le coffre pour lequel on assigne une image et une animation
*\param *rendu, le renderer sur lequel on dessine
*\param *salle, la salle courante, permet de vérifier les valeurs

*\brief Créer un coffre dans les salles dédiées
*/
void creer_coffre(coffre_t *coffre, SDL_Renderer *rendu, salle_t *salle){

	if(salle->coffre && !salle->boss && !salle->depart && !salle->ennemi_present){

		charge_image(COFFRE_PATH, &coffre->sprite, rendu);

		coffre->ouvert = 0;
		coffre->nb_sprites = 5;
		coffre->courant = 0;
		coffre->gap = 68;
		coffre->son = 0;
		coffre->vide = 0;

		coffre->last = SDL_GetTicks();

		coffre->sprite_courant.x = 0;
		coffre->sprite_courant.y = 0;
		coffre->sprite_courant.w = 39;
		coffre->sprite_courant.h = 50;

		coffre->sprite.rectangle.w = coffre->sprite_courant.w * 1.3;
		coffre->sprite.rectangle.h = coffre->sprite_courant.h * 1.3;
		coffre->sprite.rectangle.x = WIN_WIDTH / 2 - coffre->sprite.rectangle.w / 2;
		coffre->sprite.rectangle.y = WIN_HEIGHT / 2 - coffre->sprite.rectangle.h / 2;
	}
	else{
		coffre->sprite.img = NULL;
	}
}



/**
*\fn void destruction_des_coffres(salle_t salles[], int taille)

*\param salles[], le tableau contenant toutes les salles du labyrinthe
*\param taille, la taille du tableau de salles

*\brief Libère tous les emplacements mémoires attribués aux coffres
*/
void destruction_des_coffres(salle_t salles[], int taille){

	int i;

	for(i = 0; i < taille * taille; i++){

		if(salles[i].coffre && !salles[i].boss && !salles[i].depart && !salles[i].ennemi_present)
			libere_texture(&salles[i].coffre_salle.sprite.img);
	}
}


/**
*\fn void creer_texte_coffre(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu)

*\param *txt, le texte que l'on va afficher
*\param *image, la structure qui contiendra le texte
*\param x, la position x à l'écran du texte
*\param y, la position y à l'écran du texte
*\param *rendu, le renderer sur lequel on dessinee

*\brief Créer le texte qui servira a afficher le contenu du coffre
*/
void creer_texte_coffre(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu){

	TTF_Font *font;

	font = TTF_OpenFont(FONT_PATH, 30);

	image->rectangle.x = x;
	image->rectangle.y = y;

	get_text_and_rect(rendu,image->rectangle.x, image->rectangle.y, txt, font, &image->img, &image->rectangle);

	TTF_CloseFont(font);
}



/**
*\fn void loot_de_carte(loot_carte_t *loot, SDL_Renderer *rendu, coffre_t *coffre, int etage)

*\param *loot, la structure contenant la carte obtenue par le joueur
*\param *rendu, le renderer sur lequel on dessine
*\param *coffre, Etat du coffre (ouvert ou non)
*\param etage, l'étage où se situe le joueur

*\brief initialise la structure de loot, generer une carte qui est envoyée dans les listes
*/

void loot_de_carte(loot_carte_t *loot, SDL_Renderer *rendu, coffre_t *coffre, int etage){

	if(coffre->ouvert && loot->existe == 0 && coffre->vide == 0){

		coffre->vide = 1;

		loot->existe = 1;

		loot->carte = generer_carte(etage);

		ajout_carte_deck(loot->carte);
		ajout_carte_collec(loot->carte);

		charge_image(loot->carte->path, &loot->image, rendu);

		loot->image.rectangle.x = WIN_WIDTH * 0.05;
		loot->image.rectangle.y = WIN_HEIGHT * 0.45;

		loot->delai = DUREE_AFFICHAGE_CARTE_LOOT;

		loot->debut = SDL_GetTicks();

		creer_texte_coffre("Vous avez trouve :", &loot->texte, WIN_WIDTH * 0.03, WIN_HEIGHT *0.40, rendu);
	}
}



/**
*\fn void detruire_loot(loot_carte_t **loot)

*\param **loot, la structure contenant la carte obtenue par le joueur
*\param *rendu, le renderer sur lequel on dessinee

*\brief Détruit toutes les allocations dynamiques effectuées pour la structure loot
*/
void afficher_loot(loot_carte_t loot, SDL_Renderer *rendu){

	if(loot.existe){

		SDL_RenderCopy(rendu, loot.texte.img, NULL, &loot.texte.rectangle);
		SDL_RenderCopy(rendu, loot.image.img, NULL, &loot.image.rectangle);
	}
}


/**
*\fn void detruire_loot(loot_carte_t **loot)

*\param **loot, la structure contenant la carte obtenue par le joueur

*\brief Détruit toutes les allocations dynamiques effectuées pour cette structure
*/
void detruire_loot(loot_carte_t **loot){

	if((*loot)->existe){
		detruire_carte(&(*loot)->carte);
		(*loot)->carte = NULL;
		libere_texture(&(*loot)->texte.img);
		(*loot)->texte.img = NULL;
		libere_texture(&(*loot)->image.img);
		(*loot)->image.img = NULL;
	}
	free(*loot);

	*loot = NULL;
}


/**
*\fn void loot_affichage_fini(loot_carte_t *loot)

*\param *loot, la structure contenant la carte obtenue par le joueur

*\brief Contrôle si la durée d'affichage du loot est dépassée ou non, si oui elle détruit les éléments dans la structure
*/
void loot_affichage_fini(loot_carte_t *loot){

	if(loot->existe){
		if(loot->delai + loot->debut <= SDL_GetTicks()){
			detruire_carte(&loot->carte);
			libere_texture(&loot->texte.img);
			libere_texture(&loot->image.img);
			loot->image.img = NULL;
			loot->texte.img = NULL;
			loot->carte = NULL;

			loot->existe = 0;
		}
	}
}
