/**

*\file combat_tour_par_tour.c

*\author {Tudoret Aurélien, Jourry Axel, Marin Timothée, Malabry Thomas}

*\date 14/03/2020

*\version 0.1

*\brief contient et fait appel a toutes fonctions nécessaires pour le combat
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"
#include "../include/clavier.h"


/**
*\fn int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir,SDL_Rect carte1,SDL_Rect carte2,SDL_Rect carte3,SDL_Rect carte4, SDL_Rect **rect_sel)

*\param defausse, Correspond aux coordonnées du texte défausse
*\param fuir, Correspond aux coordonnées du texte fuir
*\param carte1, Correspond aux coordonnées de la carte 1
*\param carte2, Correspond aux coordonnées de la carte 2
*\param carte3, Correspond aux coordonnées de la carte 3
*\param carte4, Correspond aux coordonnées de la carte 4
*\param **rect_sel Correspond aux coordonnées du rectangle de sélection

*\brief Permet de déplacer le rectangle de selection

*/
int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir,SDL_Rect carte1,SDL_Rect carte2,SDL_Rect carte3,SDL_Rect carte4, SDL_Rect **rect_sel){

	SDL_Event event;
  int choix=0;

	while(SDL_PollEvent(&event) && choix==0){ //On attend un évènement au clavier
		if(event.type == SDL_KEYDOWN){	//touche enfoncée
			if(event.key.keysym.sym == SDLK_RIGHT){
				if((*rect_sel)->y != fuir.y){//on n'est pas sur la dernière option, on peut descendre
					if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = fuir.y - RECT_SELECT_Y_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte4.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						(*rect_sel)->x = defausse.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte3.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte4.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte2.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte3.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte1.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte2.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_LEFT){
				if((*rect_sel)->y != defausse.y){//on n'est pas sur la premiere option, on peut monter
					if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->y = defausse.y - RECT_SELECT_Y_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
						(*rect_sel)->x = carte4.x - RECT_SELECT_X_DIFF;
						(*rect_sel)->y = carte4.y - RECT_SELECT_Y_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte4.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte3.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte3.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte2.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
					else if((*rect_sel)->x == carte2.x - RECT_SELECT_X_DIFF){
						(*rect_sel)->x = carte1.x - RECT_SELECT_X_DIFF;
						/*Mix_PlayChannel(0, move, 0);*/
					}
				}
			}
			else if(event.key.keysym.sym == SDLK_RETURN){//touche entrée
				if((*rect_sel)->y == defausse.y - RECT_SELECT_Y_DIFF){
					return 9;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				else if((*rect_sel)->y == fuir.y - RECT_SELECT_Y_DIFF){
					return 10;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				/*SOIN*/
				else if((*rect_sel)->x == carte1.x - RECT_SELECT_X_DIFF){
					return 2;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				else if((*rect_sel)->x == carte2.x - RECT_SELECT_X_DIFF){
					return 3;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				else if((*rect_sel)->x == carte3.x - RECT_SELECT_X_DIFF){
					return 4;
					/*Mix_PlayChannel(1, select, 0);*/
				}
				/*BOUE*/
				else if((*rect_sel)->x == carte4.x - RECT_SELECT_X_DIFF){
					return 5;
					/*Mix_PlayChannel(1, select, 0);*/
				}
			}
		}

		if(event.type == SDL_QUIT)//croix de la fenetre
			return FALSE;
	}
	return TRUE;
}





/**
*\fnvoid affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi,SDL_Texture *defausse_texture ,SDL_Texture *fuir_texture,SDL_Rect defausse_rect ,SDL_Rect fuir_rect,SDL_Rect *rect_sel,image_t images[NB_TEXTURES])

*\param *rendu, le renderer sur lequel on dessine
*\param *ennemi, la structure contenant tous les ennemis
*\param pers, la structure contenant le personnage
*\param *defausse_texture, Les textures du texte defausse
*\param *fuir_texture, Les textures du texte fuir
*\param defausse_rect, les coordonnées du texte defausse
*\param fuir_rect, les coordonnées du texte fuir
*\param *rect_sel, Les coordonnées et taille du rectangle de selection
*\param images[NB_TEXTURES], Un tableau contenant les cartes

*\brief Permet d'afficher toutes la partie combat

*/
void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi,SDL_Texture *defausse_texture ,SDL_Texture *fuir_texture,SDL_Rect defausse_rect ,SDL_Rect fuir_rect,SDL_Rect *rect_sel,image_t images[NB_TEXTURES]){
  //écran noir puis nettoie l'écran
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  /*Mise en place des fonds*/
  SDL_RenderCopy(rendu, images[fond2].img, NULL, &images[fond2].rectangle);

  SDL_RenderCopy(rendu, images[fond].img, NULL, &images[fond].rectangle);

  /*Mise en place des cartes */
  SDL_RenderCopy(rendu, images[carte1].img, NULL, &images[carte1].rectangle);

  SDL_RenderCopy(rendu, images[carte2].img, NULL, &images[carte2].rectangle);

  SDL_RenderCopy(rendu, images[carte3].img, NULL, &images[carte3].rectangle);

  SDL_RenderCopy(rendu, images[carte4].img, NULL, &images[carte4].rectangle);
  /*afficher le rectangle*/
  SDL_SetRenderDrawColor(rendu, 255,255,255,255);
  SDL_RenderDrawRect(rendu, rect_sel);
  /*Texte Défausse et fuir*/
  SDL_RenderCopy(rendu, defausse_texture, NULL, &defausse_rect);
  SDL_RenderCopy(rendu, fuir_texture, NULL, &fuir_rect);

  /*Mise en place du personnage*/
  int w=pers->sprites[idle_droite].rectangle.w;
  int h=pers->sprites[idle_droite].rectangle.h;
  int x=pers->sprites[idle_droite].rectangle.x;
  int y=pers->sprites[idle_droite].rectangle.y;
  pers->sprites[idle_droite].rectangle.w *=3;
  pers->sprites[idle_droite].rectangle.h *=3;
  pers->sprites[idle_droite].rectangle.x = 150;
  pers->sprites[idle_droite].rectangle.y = 250;
  pers->sprites[courant] = pers->sprites[idle_droite];
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);

  /*Afficher l'ennemi*/
  int xe=ennemi->sprites.rectangle.x;
  int ye=ennemi->sprites.rectangle.y;
  int he=ennemi->sprites.rectangle.h;
  int we=ennemi->sprites.rectangle.w;
  ennemi->sprites.rectangle.x = 750;
  ennemi->sprites.rectangle.y = 240;
  ennemi->sprites.rectangle.w *= 3;
  ennemi->sprites.rectangle.h *= 3;
  ennemi->sprites = ennemi->sprites;
  SDL_RenderCopy(rendu, ennemi->sprites.img, &ennemi->sprite_courant, &ennemi->sprites.rectangle);

  SDL_RenderPresent(rendu);
	/*Reinitialise les coordonnées du perso et des ennemis*/
  pers->sprites[idle_droite].rectangle.w = w;
  pers->sprites[idle_droite].rectangle.h = h;
  pers->sprites[idle_droite].rectangle.x = x+40;
  pers->sprites[idle_droite].rectangle.y = y+40;
  ennemi->sprites.rectangle.w = we;
  ennemi->sprites.rectangle.h = he;
  ennemi->sprites.rectangle.x = xe-50;
  ennemi->sprites.rectangle.y = ye+50;
}



void charge_textures_combat(image_t images[], SDL_Renderer *rendu){

	charge_image(FOND_COMBAT_PATH,&images[fond2], rendu);
	charge_image(COMBAT_PATH,&images[fond], rendu);
	charge_image(CARTE1_PATH,&images[carte1], rendu);
	charge_image(CARTE2_PATH,&images[carte2], rendu);
	charge_image(CARTE3_PATH,&images[carte3], rendu);
	charge_image(CARTE4_PATH,&images[carte4], rendu);
}


void donne_valeur_rect_images(image_t images[]){

	images[fond2].rectangle.x= -50;
	images[fond2].rectangle.y= -415;
	images[fond2].rectangle.w *= 2;
	images[fond2].rectangle.h *= 2;

 	images[fond].rectangle.x=0;
	images[fond].rectangle.y= 450;
  	images[fond].rectangle.w *= 4;
	
  	images[carte1].rectangle.x=50;
  	images[carte1].rectangle.y= 450;
  	images[carte1].rectangle.w /=8;
  	images[carte1].rectangle.h /=8;

	images[carte2].rectangle.x=250;
  	images[carte2].rectangle.y= 450;
  	images[carte2].rectangle.w /=2;
  	images[carte2].rectangle.h /=2;

 	images[carte3].rectangle.x=450;
  	images[carte3].rectangle.y= 450;
  	images[carte3].rectangle.w /=2;
  	images[carte3].rectangle.h /=2;
	
  	images[carte4].rectangle.x=650;
  	images[carte4].rectangle.y= 450;
  	images[carte4].rectangle.w /=2;
  	images[carte4].rectangle.h /=2;
}



void free_image(image_t images[]){

	for(int i = fond2; i< carte4; i++){
		SDL_DestroyTexture(images[i].img);
	}
}

/**
*\fn void combat(perso_t * perso, ennemi_t * ennemi, SDL_Renderer *rendu)
*\param *perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param *ennemi Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\param *rendu, le renderer sur lequel on dessine

*\brief Fonction qui permet de gérer les choix de l'utilisateur via la SDL sur le combat
*/
int combat_t_p_t(perso_t * perso, ennemi_t * ennemi,SDL_Renderer *rendu)
{
	/*Déclaration et configuration des cartes*/
	image_t images[NB_TEXTURES];

	charge_textures_combat(images, rendu);

	donne_valeur_rect_images(images);


/*Decalaration des différentes variable*/
  SDL_Rect *rectangle_selection = malloc(sizeof(SDL_Rect));

  int choix=0, i, vitesse,fuire=1;
  
  TTF_Font * police = NULL;
  police=TTF_OpenFont(FONT_PATH,40);
  char * defausse=malloc(sizeof(char));
  char * fuir=malloc(sizeof(char));
  strcpy(defausse,"Defausse");
  strcpy(fuir,"Fuir");
  image_t def;
  image_t fui;
  /*Mise en place du texte defausse*/
  def.rectangle.x=875;
  def.rectangle.y=475;
  get_text_and_rect(rendu,def.rectangle.x, def.rectangle.y, defausse,police, &def.img, &def.rectangle);
  /*Mise en place du texte fuir*/
  fui.rectangle.x=875;
  fui.rectangle.y=550;
  get_text_and_rect(rendu,fui.rectangle.x, fui.rectangle.y, fuir,police, &fui.img, &fui.rectangle);
	/*Mise en place du rectangle de selection*/
  rectangle_selection->x = (def.rectangle).x - RECT_SELECT_X_DIFF;
	rectangle_selection->y = (def.rectangle).y - RECT_SELECT_Y_DIFF;
	rectangle_selection->w = (def.rectangle).w +100;
	rectangle_selection->h = (def.rectangle).h +30;
  /*Ajout des cartes en dur pour le moment*/
  init_liste();
  ajout_droit(creer_carte("soin", DEFENSE, 5, 0));
  ajout_droit(creer_carte("potion", DEFENSE, 20, 1));
  ajout_droit(creer_carte("épée", ATTAQUE,10, 0));
  ajout_droit(creer_carte("boule de feu", ATTAQUE, 20, 0));
	/*Déclaration et début du combat*/
  
  vitesse = perso->vitesse;
	printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
	printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);
  while((ennemi->pv > 0 && perso->pv > 0) && fuire==1 ){
		/*Affichage de la salle et du rectangle de selection*/
    affichage_combat_personnage(rendu,perso,ennemi,def.img,fui.img,def.rectangle,fui.rectangle,rectangle_selection,images);
    choix=deplacement_rectangle_selection_combat(def.rectangle,fui.rectangle,images[carte1].rectangle,images[carte2].rectangle,images[carte3].rectangle,images[carte4].rectangle,&rectangle_selection);
    if (choix!=0 && choix !=1){
    	for(i=1, en_tete() ; i<5 ; i++, suivant()){
      	printf("[%d] : %s\n", i+1, ec->carte->nom);
    	}
	  }
    if (choix!=0 && choix !=1){

			printf("%d \n",choix);
    }
		/*Action du personnage selon son choix*/
    if(choix == 10){
      fuire=0;
    }
    else if (choix == 9){
      printf("Vous avez défaussé une carte \n");
    }
		/*Soin*/
		else if (choix == 2){
			choix=1;
			if (initiative(perso, ennemi)){
	      tour_perso(choix, perso, ennemi);
	      if(ennemi->pv){
	        tour_ennemi(perso, ennemi);}
	    }
	    else {
	      tour_ennemi(perso, ennemi);
	      if(perso->pv){
	        tour_perso(choix, perso, ennemi);}
	    }
    }
		/*Epee*/
		else if (choix == 3){
			choix=2;
			if (initiative(perso, ennemi)){
	      tour_perso(choix, perso, ennemi);
	      if(ennemi->pv){
	        tour_ennemi(perso, ennemi);}
	    }
	    else {
	      tour_ennemi(perso, ennemi);
	      if(perso->pv){
	        tour_perso(choix, perso, ennemi);}
	    }
			printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    	printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);
    }
		/*Epee*/
		else if (choix == 4){
			choix=3;
			if (initiative(perso, ennemi)){
	      tour_perso(choix, perso, ennemi);
	      if(ennemi->pv){
	        tour_ennemi(perso, ennemi);}
	    }
	    else {
	      tour_ennemi(perso, ennemi);
	      if(perso->pv){
	        tour_perso(choix, perso, ennemi);}
	    }
			printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    	printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);
    }
		else if(choix==5){
			choix=4;
			if (initiative(perso, ennemi)){
	      tour_perso(choix, perso, ennemi);
	      if(ennemi->pv){
	        tour_ennemi(perso, ennemi);}
	    }
	    else {
	      tour_ennemi(perso, ennemi);
	      if(perso->pv){
	        tour_perso(choix, perso, ennemi);}
	    }
			printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    	printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);
		}
	 }
  /*Fin du combat*/
  if(!ennemi->pv){
    printf("Vous avez vaincu le %s\n", ennemi->nom);
  }
  else if (!perso->pv){
    printf("Vous avez été vaincu par le %s\n", ennemi->nom);
  }
  else if (choix==10) {
    printf("Vous avez fuit le combat\n");
  }
  perso->vitesse = vitesse;

  TTF_CloseFont(police);
  SDL_DestroyTexture(def.img);

  free_image(images);
}
