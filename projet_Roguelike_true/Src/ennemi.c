/**
*\file ennemi.c
*\author Tudoret Aurélien
*\version 0.
*\date 12/03/2020

*\brief Permet de gérer les déplacements et animations des ennemis dans le labyrinthe et en combat
*/

#include "../include/constantes.h"

void change_anim_ligne(ennemi_t *ennemi, int nouvelle_anim){

	ennemi->sprite_courant.y = 0;
	ennemi->sprite_courant.x = 0;
	ennemi->anim_courante = nouvelle_anim;
	ennemi->id_col = 0;
}



void animation_ennemi(ennemi_t *ennemi){

	if(ennemi->last + DELAIS_ANIMATIONS_ENNEMIS <= SDL_GetTicks()){

		if((ennemi->anim_courante == idle_droite_ennemi || ennemi->anim_courante == idle_gauche_ennemi) 
			&& ennemi->id_col < ennemi->nb_sprites_idle - 1){
			
			ennemi->sprite_courant.x += ennemi->sprite_courant.w;
			ennemi->id_col ++;
		}
		else{

			if(ennemi->anim_courante == idle_droite_ennemi){

				change_anim_ligne(ennemi, idle_gauche_ennemi);
				ennemi->sprite_courant.y = ennemi->sprite_courant.h;
			}
			if(ennemi->anim_courante == idle_gauche_ennemi){

				change_anim_ligne(ennemi, idle_droite_ennemi);
			}
		}

		ennemi->last = SDL_GetTicks();
	}
}