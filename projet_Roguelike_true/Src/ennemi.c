/**
*\file ennemi.c
*\author Tudoret Aurélien
*\version 0.
*\date 12/03/2020

*\brief Permet de gérer les déplacements et animations des ennemis dans le labyrinthe et en combat
*/

#include "../include/constantes.h"
#include "../include/fonctions.h"

/**
*\fn void change_anim_ligne(ennemi_t *ennemi, int nouvelle_anim)

*\param *ennemi, l'ennemi pour lequel on change l'animation
*\param nouvelle_anim, la nouvelle animation que doit effectuer l'ennemi

*\brief Permet de donner à l'ennemi l'animation qu'il devra effectuer par la suite
*/
void change_anim_ligne(ennemi_t *ennemi, int nouvelle_anim){

	ennemi->sprite_courant.y = 0;
	ennemi->sprite_courant.x = 0;
	ennemi->anim_courante = nouvelle_anim;
	ennemi->id_col = 0;
}


/**
*\fn void animation_ennemi(ennemi_t *ennemi)

*\param *ennemi, l'ennemi pour lequel on veut effectuer une animation

*\brief Permet de passer d'animations en animations pour un ennemi
*/
void animation_ennemi(ennemi_t *ennemi){

	if(ennemi->last + DELAIS_ANIMATIONS*1.25  <= SDL_GetTicks()){

		if((ennemi->anim_courante == idle_droite_ennemi || ennemi->anim_courante == idle_gauche_ennemi) 
			&& ennemi->id_col < ennemi->nb_sprites_idle - 1){
			
			ennemi->sprite_courant.x += ennemi->sprite_courant.w + ennemi->gap;
			ennemi->id_col ++;
		}
		else{

			if(ennemi->anim_courante == idle_droite_ennemi){

				change_anim_ligne(ennemi, idle_gauche_ennemi);

				ennemi->sprite_courant.y = ennemi->sprite_courant.h;
			}
			else if(ennemi->anim_courante == idle_gauche_ennemi){

				change_anim_ligne(ennemi, idle_droite_ennemi);
			}
		}

		ennemi->last = SDL_GetTicks();
	}
}



/**
*\fn void destruction_tous_ennemis(salle_t salles[], int taille)

*\param salles[], le tableau contenant toutes les salles du labyrinthe
*\param taille, la taille du tableau de salles

*\brief Libère tous les emplacements mémoires attribués aux ennemis
*/
void destruction_tous_ennemis(salle_t salles[], int taille){

	int i;

	for(i = 0; i < taille * taille; i++){

		if(salles[i].ennemi_present > 0 || salles[i].boss)
			detruire_ennemi(&salles[i].ennemi);
		if(salles[i].nb_ennemi == 2)
			detruire_ennemi(&salles[i].ennemi2);
	}
}