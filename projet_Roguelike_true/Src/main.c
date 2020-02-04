/**
* \file main.c
* \date 30/01/2020
* \author {Tudoret Aurélien, Jourry Axel, Malabry Thomas, Marin Timothée}
* \version 0.1
* \brief Le projet de deuxième année de licence, un roguelike/rpg

*/

#include "constantes.h"
#include "initialisation_sdl_fonctions.h"
#include "main_menu_screen.h"
#include "salle.h"
#include "personnage.h"


int main(void){

//************************* DECLARATION VARIABLES************************************************************

	SDL_Window *window;
	SDL_Renderer *rendu;

	TTF_Font *police = NULL;

	int continuer = 1, etat = labyrinthe;

	t_image images[3];
	t_image commandes;
	t_image instructions;

	salle_t salle;
	salle.salle_prec = NULL;
	salle.salle_id = 0;//première salle

	t_perso pers;

	pers.x = WIN_WIDTH / 2;
	pers.y = WIN_HEIGHT / 2;

//************************* INITIALISATION SDL + TTF ********************************************************

	if(initialisation_sdl(&window, &rendu)){
		printf("Erreur création fenetre ou rendu\n");
	}
	else{

		if(init_or_quit_ttf(1))//initialise TTF (permet s d'écrire sur l'écran)
			printf("Erreur init TTF\n");
		else{

			if((IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG){
				printf("Erreur init sdl_image\n");
			}
			else{

				police = TTF_OpenFont(FONT_PATH, 50);//charge la police pour écrire a l'ecran

				if(!police)
					printf("Erreur police\n");
				else{
					charge_image(SOL1_PATH,&images[0], rendu);
					charge_image(MUR1_PATH,&images[1], rendu);
					charge_image(SOL2_PATH,&images[2], rendu);
					charge_sprites_personnage(pers.sprites, rendu);
					charge_image("../Images/commandes.png", &commandes, rendu);
					charge_image("../Images/instructions.png", &instructions, rendu);

					//init la salle et créé les portes
					init_salle(salle.salle);
					aleatoire_porte(&salle);

					//on place le personnage dans la salle
					pers.sprites[0].rectangle.x = pers.x;
					pers.sprites[0].rectangle.y = pers.y;

					//on donne les coordonnées pour placer l'image des commandes et des instructions
					commandes.rectangle.x=0;
					commandes.rectangle.y=WIN_HEIGHT/4;
					instructions.rectangle.x=800;
					instructions.rectangle.y=WIN_HEIGHT/30;
	//************************* BOUCLE DE JEU ********************************************************************

					while(continuer){

						if(etat == mainMenu){

							main_menu(&continuer, &etat, rendu, police);

						}
						else if (etat == labyrinthe){
							//tout ce qui sera relatif à l'explo dans le laby

							SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

							SDL_RenderClear(rendu);//nettoie l'écran pour supprimer tout ce qui est dessus

							if(salle.salle_id == 0){//affichage des commandes et rêgles du jeu si on est dans la première salle
								SDL_RenderCopy(rendu, commandes.img, NULL, &commandes.rectangle);
								SDL_RenderCopy(rendu, instructions.img, NULL, &instructions.rectangle);
							}

							afficher_salle(salle.salle, rendu, images);
							SDL_RenderCopy(rendu, pers.sprites[0].img, NULL, &pers.sprites[0].rectangle);

							SDL_RenderPresent(rendu);//applique les modifs précédentes

							deplacement_personnage(&pers, salle, &continuer);
						}
						else if(etat == tourParTour){
							//le combat tour par tour, le fait de le séparer fera une pause automatique dans
							//toutes les actions qui pourraient se passer dans le laby pendant le combat
						}
						else if(etat == pauseScreen){

							//ecran de pause en jeu tpt ou laby
						}
					}
				}
			}
		}
	}

	SDL_DestroyTexture(instructions.img);
	SDL_DestroyTexture(commandes.img);
	SDL_DestroyTexture(pers.sprites[0].img);
	SDL_DestroyTexture(images[0].img);
	SDL_DestroyTexture(images[1].img);
	SDL_DestroyTexture(images[2].img);

//************************* FERMETURES ***********************************************************************
	IMG_Quit();
	TTF_CloseFont(police); //on libère la police
	quit_sdl(&rendu, &window);
	SDL_Quit();
	init_or_quit_ttf(0);//quitte TTF

	printf("Tout est fermé\n");//affiche dans la console

	return 0;
}
