/**
*\file animation.c
*\author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
*\date 18/02/2020
*\version 0.1

*\brief Gère les différentes animations de combat, de chargement et de mort
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/personnage.h"
#include "../include/sauvegardefonc.h"
#include "../include/fonctions.h"

/**
*\fn void animation_niveau(perso_t *perso, SDL_Renderer *rendu)
*\param *perso, la structure du personnage
*\param *rendu, le renderer sur lequel on dessine
*\brief Fonction qui anime le lancement d'une partie avec un chargement
*/
void animation_niveau(perso_t *perso, SDL_Renderer *rendu){

  //initialisation des variables
  image_t texte_etage, texte_charg, p1, p2, p3;
  char etage[15], charg[15]="chargement", cp1[10]=".", cp2[10]=".", cp3[10]=".";
  TTF_Font *police = NULL;
  int x_etage = 480, y_etage = 250, x_charg = 450, y_charg = 350;
  int p1_x = 2000, p1_y = 350, p2_x = 2000, p2_y = 350, p3_x = 2000, p3_y = 350;
  int char_alea = rand()%(9-4)+4;
  int cmp = 0, cmp2=0;
  police = TTF_OpenFont(FONT_PATH, 30);
  SDL_Rect rect;
 	rect.w = 1080;
 	rect.h = 620;

  sprintf(etage, "Etage %d", perso->etage);
  get_text_and_rect(rendu, x_etage, y_etage, etage, police, &texte_etage.img, &texte_etage.rectangle);
  get_text_and_rect(rendu, x_charg, y_charg, charg, police, &texte_charg.img, &texte_charg.rectangle);
  get_text_and_rect(rendu, p1_x, p1_y, cp1, police, &p1.img, &p1.rectangle);
  get_text_and_rect(rendu, p2_x, p2_y, cp2, police, &p2.img, &p2.rectangle);
  get_text_and_rect(rendu, p3_x, p3_y, cp3, police, &p3.img, &p3.rectangle);

  //Animation
  SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
  SDL_RenderClear(rendu);
  SDL_RenderFillRect(rendu, &rect);
  SDL_RenderPresent(rendu);

  SDL_Delay(100);

  SDL_RenderClear(rendu);
  SDL_RenderCopy(rendu, texte_etage.img, NULL, &texte_etage.rectangle);
  SDL_RenderCopy(rendu, texte_charg.img, NULL, &texte_charg.rectangle);

  SDL_RenderPresent(rendu);

  //Faire clignoter les points
  while(cmp != char_alea){
    if(cmp2==0){
      p1.rectangle.x = 2000;

      p2.rectangle.x = 2000;

      p3.rectangle.x = 2000;
    }
    else if(cmp2==1){
      p1.rectangle.x = 580;
    }

    else if(cmp2==2){
      p2.rectangle.x = 585;
    }

    else if(cmp2==3){
      p3.rectangle.x = 590;
      cmp2=-1;

    }

    SDL_RenderClear(rendu);
    SDL_RenderCopy(rendu, texte_etage.img, NULL, &texte_etage.rectangle);
    SDL_RenderCopy(rendu, texte_charg.img, NULL, &texte_charg.rectangle);
    SDL_RenderCopy(rendu, p1.img, NULL, &p1.rectangle);
    SDL_RenderCopy(rendu, p2.img, NULL, &p2.rectangle);
    SDL_RenderCopy(rendu, p3.img, NULL, &p3.rectangle);
    SDL_RenderPresent(rendu);


    cmp++;
    cmp2++;
    SDL_Delay(500);
  }

	TTF_CloseFont(police); //on libère la police

  if(texte_etage.img != NULL){
    SDL_DestroyTexture(texte_etage.img);
    texte_etage.img=NULL;
  }

  if(texte_charg.img!=NULL){
    SDL_DestroyTexture(texte_charg.img);
    texte_charg.img=NULL;
  }

  if(p1.img!=NULL){
    SDL_DestroyTexture(p1.img);
    p1.img=NULL;
  }

  if(p2.img!=NULL){
    SDL_DestroyTexture(p2.img);
    p2.img=NULL;
  }

  if(p3.img!=NULL){
    SDL_DestroyTexture(p3.img);
    p3.img=NULL;
  }
}


/**
*\fn void anim1(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON])
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_MUSIC], le tableau contenant les sons

*\brief Affiche l'animation 1 de début de combat
*/
void anim1(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]){
	SDL_Rect rect;
	int sens = 0;

	rect.x = 200;
 	rect.y = 0;
 	rect.w = 270;
 	rect.h = 155;
  Mix_PlayChannel(0, sounds[enterFight], 0);
	while(rect.x < WIN_WIDTH-540 && rect.y < WIN_HEIGHT){

    //De gauche à droite
		if(sens == 0){
			rect.x += 20;
			if(rect.x >= WIN_WIDTH-540){
				rect.y += 155;
				sens = 1;
			}
		}

    //De droite à gauche
		if(sens == 1){
			rect.x -= 20;
			if(rect.x <= 200){
				rect.y += 155;
				sens = 0;
			}
		}
		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		SDL_RenderFillRect(rendu, &rect);
		SDL_RenderPresent(rendu);
		SDL_Delay(20);

	}
	SDL_Delay(200);

}


/**
*\fn void anim2(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON])
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_MUSIC], le tableau contenant les sons

*\brief Affiche l'animation 2 de début de combat
*/
void anim2(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]){

  //Initialisation des valeurs
	SDL_Rect rect;
	int sens = 0;
	int tour = 0;

	rect.x = 200;
	rect.y = 0;
	rect.w = 270;
	rect.h = 155;

	int xmax = WIN_WIDTH-560;
	int ymax = WIN_HEIGHT-200;
	int xmin = 200;
	int ymin = 0;

  Mix_PlayChannel(0, sounds[enterFight], 0);

	while(tour < 6){
    //De gauche à droite
		if(sens == 0){
			rect.x += 20;
			if(rect.x >= xmax ){
				tour++;
				sens = 1;
			}
		}

    //De haut en bas
		if(sens == 1){
			rect.y += 20;
			if(rect.y >= ymax){
				tour++;
				sens = 2;
			}
		}

    //De droite à gauche
		if(sens == 2){
			rect.x -= 20;
			if(rect.x <= xmin){
				ymin+=130;
				xmin+=200;
				tour++;
				sens = 3;
			}
		}

    //De bas en haut
		if(sens == 3){
			rect.y -= 20;
			if(rect.y <= ymin){
				xmax-=250;
				ymax-=125;
				tour++;

				sens = 0;
			}
		}
		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		SDL_RenderFillRect(rendu, &rect);
		SDL_RenderPresent(rendu);
		SDL_Delay(20);
	}

	SDL_Delay(200);

}


/**
*\fn void anim3(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON])
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_MUSIC], le tableau contenant les sons

*\brief Affiche l'animation 3 de début de combat
*/
void anim3(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]){

  //Initialisation des variables
	SDL_Rect rect1, rect2;
	int sens = 0;

	rect2.x = WIN_WIDTH-560;
 	rect2.y = WIN_HEIGHT;
 	rect2.w = 270;
 	rect2.h = 155;

	rect1.x = 200;
 	rect1.y = 0;
 	rect1.w = 270;
 	rect1.h = 155;

  Mix_PlayChannel(0, sounds[enterFight], 0);

	while(sens<2){
    //rect1 descend et rect2 monte
		if(sens == 0){
			if(rect1.y < WIN_HEIGHT){
				rect1.y +=20;
			}
			if(rect2.y > 0){
				rect2.y -=20;
			}

      //Décallage des rectangles et inversement du sens
			if(rect1.y >= WIN_HEIGHT && rect2.y <=0){
				rect1.x+=270;
				rect2.x-=270;
				sens+=1;
			}
		}

    //rect1 monte et rect2 descend
		if(sens == 1){
			if(rect1.y > 0){
				rect1.y -=20;
			}
			if(rect2.y < WIN_HEIGHT){
				rect2.y +=20;
			}
      //Sortie de boucle
			if(rect1.y <= 0 && rect2.y >=WIN_HEIGHT){
				sens+=1;
			}
		}
		SDL_SetRenderDrawColor(rendu, 0, 0, 0, 255);
		SDL_RenderFillRect(rendu, &rect1);
		SDL_RenderFillRect(rendu, &rect2);
		SDL_RenderPresent(rendu);
		SDL_Delay(35);
	}
	SDL_Delay(100);

}

/**
*\fn void anim_combat(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON])
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_MUSIC], le tableau contenant les sons

*\brief Permet de choisir quelle animation de début de combat exécuter
*/
void anim_combat(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]){
	srand(time(NULL));
	int choix = rand()%3;

	if(choix==0){
		anim1(rendu, sounds);
	}
	else if(choix==1){
		anim2(rendu, sounds);
	}
	else{
		anim3(rendu, sounds);
	}

}


/**
*\fn void mort(int *etat, perso_t *pers, SDL_Renderer *rendu, Mix_Music *musics[NB_MUSIC], Mix_Chunk *sounds[NB_SON], image_t images[], TTF_Font *police)

*\param *etat, variable contenant le mode de jeu actuel
*\param *perso, la structure du personnage
*\param *rendu, le renderer sur lequel on dessine
*\param *musics[NB_MUSIC], tableau contenant les musiques
*\param *sounds[NB_SON], tableau contenant les sons
*\param images[], le tableau contenant toutes les images du jeu sauf celles du personnage
*\param *police, contient la police d'écriture

*\brief Exécute l'animation de mort du joueur
*/

void mort(int *etat, perso_t *pers, SDL_Renderer *rendu, Mix_Music *musics[NB_MUSIC], Mix_Chunk *sounds[NB_SON], image_t images[], TTF_Font *police){
	int mort_tmp;

  SDL_Texture *cmpPartie_texture;
  int x_cmpPartie;
  if(pers->cmpMort == 1){
    x_cmpPartie = WIN_WIDTH / 2-60;
  }
  else{
    x_cmpPartie = WIN_WIDTH / 2-47;

  }
	int y_cmpPartie = WIN_HEIGHT * 0.8;

	//textes
	SDL_Rect cmpPartie_text, rect;

	char cmpPartie[20];

  int gap = 38;

  int id_col = 0;

//Charge les sprites
  image_t spritesMort[7];

  charge_image("../Images/Mort/sprite_mort1.png", &spritesMort[0], rendu);
  charge_image("../Images/Mort/sprite_mort2.png", &spritesMort[1], rendu);
  charge_image("../Images/Mort/sprite_mort3.png", &spritesMort[2], rendu);
  charge_image("../Images/Mort/sprite_mort4.png", &spritesMort[3], rendu);
  charge_image("../Images/Mort/sprite_mort5.png", &spritesMort[4], rendu);
  charge_image("../Images/Mort/sprite_mort6.png", &spritesMort[5], rendu);
  charge_image("../Images/Mort/sprite_mort7.png", &spritesMort[6], rendu);


	//Reinitialisation de la sauvegarde et compteur de mort
	mort_tmp = pers->cmpMort;

	initialise_personnage(pers);

	pers->cmpMort = mort_tmp+1;

  saveperso(pers);//on sauvegarde le personnage et le deck afin de les préserver
  savecarte(SAVE_CARTES_COLLEC_PATH, COLLEC);

  //on détruit les listes, afin d'éviter les conflits entre les sauvegardes et la duplication
  //de cartes
  detruire_liste(DECK);
  detruire_liste(COLLEC);
  init_liste();

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


  //Animation de mort du personnage et halo
  for(int i = 0; i<7; i++){
    SDL_RenderClear(rendu);
    Mix_PlayChannel(0, sounds[animDeath], 0);
    pers->sprites[courant] = spritesMort[i];
    pers->sprites[courant].rectangle.x = pers->x-40;
    pers->sprites[courant].rectangle.y = pers->y;

    if(i==2){
      pers->sprites[courant].rectangle.y = pers->y-15;

    }
    if(i==3){
      pers->sprites[courant].rectangle.y = pers->y-5;
    }
    if(i < 2){
      pers->sprites[courant].rectangle.y = pers->y-10;
    }
    SDL_RenderCopy(rendu, images[deathlight].img, NULL, &images[deathlight].rectangle);
    SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);
    SDL_RenderPresent(rendu);

    SDL_Delay(500);
  }

//Affichage du texte
	if(pers->cmpMort ==1){
		sprintf(cmpPartie, "%dere mort", pers->cmpMort);
	}
	else{
		sprintf(cmpPartie, "%d morts", pers->cmpMort);
	}

	//Ecran de game over
  SDL_RenderClear(rendu);
  SDL_RenderCopy(rendu, images[deathlight].img, NULL, &images[deathlight].rectangle);
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);

	//Fond noir et logo game over
	//SDL_RenderClear(rendu);
	SDL_SetRenderDrawColor(rendu,0,0,0,255);//on met un fond noir

	SDL_RenderCopy(rendu, images[gameover].img, NULL, &images[gameover].rectangle);


	//Musique
	Mix_VolumeMusic(16);
	Mix_PlayMusic(musics[gameOverMusic], 1);

	get_text_and_rect(rendu, x_cmpPartie, y_cmpPartie, cmpPartie, police, &cmpPartie_texture, &cmpPartie_text);

	SDL_RenderCopy(rendu, cmpPartie_texture, NULL, &cmpPartie_text);

	SDL_RenderPresent(rendu);

	//Des que la musique s'arrête, on revient au menu principal
 	while(Mix_PlayingMusic() == 1);

 	*etat = mainMenu;

	if(cmpPartie_texture!=NULL){
		SDL_DestroyTexture(cmpPartie_texture);
		cmpPartie_texture=NULL;
	}

  for(int i = 0; i < 7; i++)
		libere_texture(&spritesMort[i].img);

	//Charge à nouveau les cartes de la collec précédement sauvegardées
  readcarte(SAVE_CARTES_COLLEC_PATH, COLLEC);

	transfert_mort();//on prend des cartes de la collec pour les mettre dans le deck

  savecarte(SAVE_CARTES_DECK_PATH, DECK);//on sauvegarde le deck remplit de nouvelles cartes
}


/**
*\fn void anim_combat_perso_attaque(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON])

*\param *pers, contient le personnage afin de le sauvegarder
*\param cartes, la carte jouée par le joueur
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons

*\brief Permet de gèrer les animations de combat liées à l'attaque du personnage

*/
void anim_combat_perso_attaque(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]){
  int i = 0;

//Faire avancer le personnage
  while(i < 75){
    SDL_Delay(25);
    pers->sprites[courant].rectangle.x +=i;

    SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);
    SDL_RenderPresent(rendu);

    i+=15;
  }

  //Jouer le son correspondant et faire le flash
  SDL_Delay(50);
  SDL_RenderClear(rendu);
  if(!strcmp(carte->nom, "poing I") || !strcmp(carte->nom, "poing II") || !strcmp(carte->nom, "poing X")){
    Mix_PlayChannel(0, sounds[punch], 0);
  }
  else if(!strcmp(carte->nom,"epee I") || !strcmp(carte->nom,"epee II") || !strcmp(carte->nom,"epee X")){
    Mix_PlayChannel(0, sounds[sword], 0);
  }
  else if(!strcmp(carte->nom, "pierre I") || !strcmp(carte->nom, "pierre II") || !strcmp(carte->nom, "pierre X")){
    Mix_PlayChannel(0, sounds[rock], 0);
  }

  //Faire revenir le perso a sa place
  while(i>15){
    SDL_Delay(25);
    pers->sprites[courant].rectangle.x -=i;

    SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);
    SDL_RenderPresent(rendu);
    i-=15;
  }

  pers->sprites[courant].rectangle.x =215;
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);
  SDL_RenderPresent(rendu);

 SDL_RenderClear(rendu);

}


/**
*\fn void anim_combat_ennemi_attaque(ennemi_t *ennemi, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], perso_t *pers)

*\param *ennemi, l'ennemi contre lequel le joueur va combattre
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons
*\param *perso, la structure du personnage

*\brief Permet de gèrer les animations de combat liées à l'attaque de l'ennemi

*/
void anim_combat_ennemi_attaque(ennemi_t *ennemi, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], perso_t *pers){
  int i = 0;

  int xe=ennemi->sprites.rectangle.x;
  int ye=ennemi->sprites.rectangle.y;
  int he=ennemi->sprites.rectangle.h;
  int we=ennemi->sprites.rectangle.w;

  ennemi->sprites.rectangle.y = 375-(ennemi->sprites.rectangle.h);
  ennemi->sprites.rectangle.x = 830;
  ennemi->sprites.rectangle.w *= 1.5;
  ennemi->sprites.rectangle.h *= 1.5;


//Faire avancer le personnage
  while(i < 75){
    SDL_Delay(25);
    ennemi->sprites.rectangle.x -= i;

    SDL_RenderCopy(rendu, ennemi->sprites.img, &ennemi->sprite_courant, &ennemi->sprites.rectangle);
    SDL_RenderPresent(rendu);

    i+=15;
  }

  //Jouer le son correspondant et faire le flash
  SDL_Delay(50);
  SDL_RenderClear(rendu);
  Mix_PlayChannel(0, sounds[punch], 0);

  //Faire revenir le perso a sa place
  while(i>15){
    SDL_Delay(25);
    ennemi->sprites.rectangle.x +=i;

    SDL_RenderCopy(rendu, ennemi->sprites.img, &ennemi->sprite_courant, &ennemi->sprites.rectangle);
    SDL_RenderPresent(rendu);

    i-=15;
  }

  ennemi->sprites.rectangle.x = 830;
  SDL_RenderCopy(rendu, ennemi->sprites.img, &ennemi->sprite_courant, &ennemi->sprites.rectangle);
  SDL_RenderPresent(rendu);

  ennemi->sprites.rectangle.w = we;
  ennemi->sprites.rectangle.h = he;
  ennemi->sprites.rectangle.x = xe;
  ennemi->sprites.rectangle.y = ye;

  SDL_RenderClear(rendu);


}


/**
*\fn void anim_combat_perso_soin(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON])

*\param *perso, la structure du personnage
*\param *carte, la carte jouée par le joueur
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons

*\brief Permet de gèrer les animations de combat liées au soin du personnage

*/
void anim_combat_perso_soin(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]){
  image_t icon[1];


//Si une carte soin est jouée
  if(!strcmp(carte->nom, "soin I") || !strcmp(carte->nom, "soin II") || !strcmp(carte->nom, "soin X")){

  	charge_image("../Images/Combat/soin.png", &icon[0], rendu);

    icon[0].rectangle.x = pers->sprites[courant].rectangle.x + 4;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 60;

    SDL_RenderCopy(rendu, icon[0].img, NULL, &icon[0].rectangle);
    Mix_PlayChannel(0, sounds[heal], 0);
    SDL_RenderPresent(rendu);
  }

//Si une carte potion est jouée
  else if(!strcmp(carte->nom, "potion I") || !strcmp(carte->nom, "potion II") || !strcmp(carte->nom, "potion X")){
    charge_image("../Images/Combat/potion.png", &icon[0], rendu);

    icon[0].rectangle.x = pers->sprites[courant].rectangle.x + 1;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 60;

    SDL_RenderCopy(rendu, icon[0].img, NULL, &icon[0].rectangle);
    Mix_PlayChannel(0, sounds[potion], 0);
    SDL_RenderPresent(rendu);
  }

//Si une carte guerison est jouée
  else if(!strcmp(carte->nom, "guerison I") || !strcmp(carte->nom, "guerison II") || !strcmp(carte->nom, "guerison X")){
    charge_image("../Images/deathlight.png", &icon[0], rendu);

    icon[0].rectangle.x = pers->sprites[courant].rectangle.x - 75;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 70;

    SDL_RenderCopy(rendu, icon[0].img, NULL, &icon[0].rectangle);
    Mix_PlayChannel(0, sounds[divine], 0);
    SDL_RenderPresent(rendu);
  }



  SDL_Delay(1200);

  SDL_RenderClear(rendu);

  if(icon[0].img!=NULL){
		SDL_DestroyTexture(icon[0].img);
		icon[0].img=NULL;
	}

}


/**
*\fn void anim_combat_perso_barriere(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON])

*\param *perso, la structure du personnage
*\param *carte, la carte jouée par le joueur
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons

*\brief Permet de gèrer les animations de combat liées au bouclier du personnage

*/
void anim_combat_perso_barriere(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]){
  image_t icon[1];

  charge_image("../Images/Combat/bouclier.png", &icon[0], rendu);

  icon[0].rectangle.x = WIN_WIDTH/2 - 25;
  icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 40;

  SDL_RenderCopy(rendu, icon[0].img, NULL, &icon[0].rectangle);
  Mix_PlayChannel(0, sounds[bouclier], 0);
  SDL_RenderPresent(rendu);

  SDL_Delay(1200);
  SDL_RenderClear(rendu);

  if(icon[0].img!=NULL){
		SDL_DestroyTexture(icon[0].img);
		icon[0].img=NULL;
	}
}


/**
*\fn void anim_combat_perso_poison(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], ennemi_t *ennemi)

*\param *perso, la structure du personnage
*\param *carte, la carte jouée par le joueur
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons
*\param *ennemi, l'ennemi contre lequel le joueur va combattre

*\brief Permet de gèrer les animations de combat liées à la carte poison du personnage

*/
void anim_combat_perso_poison(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], ennemi_t *ennemi){
  image_t icon[1];

  charge_image("../Images/Combat/poison.png", &icon[0], rendu);

  //Boss
  if(!strcmp(ennemi->nom, "Sorcier")){
    icon[0].rectangle.x = 832;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 140;
  }
  if(!strcmp(ennemi->nom, "Minotaure")){
    icon[0].rectangle.x = 840;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 100;
  }
  if(!strcmp(ennemi->nom, "Cyclope")){
    icon[0].rectangle.x = 845;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 120;
  }
  if(!strcmp(ennemi->nom, "Sorciere")){
    icon[0].rectangle.x = 835;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 80;
  }
  if(!strcmp(ennemi->nom, "Mage")){
    icon[0].rectangle.x = 835;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 120;
  }

  //Ennemis classiques
  if(!strcmp(ennemi->nom, "Squelette")){
    icon[0].rectangle.x = 850;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 67;
  }
  if(!strcmp(ennemi->nom, "Blob")){
    icon[0].rectangle.x = 845;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 90;
  }
  if(!strcmp(ennemi->nom, "Volant")){
    icon[0].rectangle.x = 840;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 60;
  }
  if(!strcmp(ennemi->nom, "Imp")){
    icon[0].rectangle.x = 835;
    icon[0].rectangle.y = pers->sprites[courant].rectangle.y -54;
  }

  SDL_RenderCopy(rendu, icon[0].img, NULL, &icon[0].rectangle);
  Mix_PlayChannel(0, sounds[poison], 0);
  SDL_RenderPresent(rendu);

  SDL_Delay(1200);
  SDL_RenderClear(rendu);

  if(icon[0].img!=NULL){
		SDL_DestroyTexture(icon[0].img);
		icon[0].img=NULL;
	}
}


/**
*\fn void anim_combat_perso_barriere(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON])

*\param *perso, la structure du personnage
*\param *carte, la carte jouée par le joueur
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons

*\brief Permet de gèrer les animations de combat liées à la carte boule de feu du personnage

*/
void anim_combat_perso_bdf(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]){
  image_t icon[1];
  charge_image("../Images/Combat/bdf.png", &icon[0], rendu);

  int i = 0;

  icon[0].rectangle.x = WIN_WIDTH/2 - 25;
  icon[0].rectangle.y = pers->sprites[courant].rectangle.y - 10;

  SDL_RenderCopy(rendu, icon[0].img, NULL, &icon[0].rectangle);
  Mix_PlayChannel(0, sounds[bdf], 0);
  SDL_RenderPresent(rendu);

  SDL_Delay(1200);
  SDL_RenderClear(rendu);

  if(icon[0].img!=NULL){
    SDL_DestroyTexture(icon[0].img);
    icon[0].img=NULL;
  }
}


/**
*\fn void anim_combat_perso(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], ennemi_t *ennemi)

*\param *perso, la structure du personnage
*\param *carte, la carte jouée par le joueur
*\param *rendu, le renderer sur lequel on dessine
*\param *sounds[NB_SON], tableau contenant les sons
*\param *ennemi, l'ennemi contre lequel le joueur va combattre

*\brief Permet de gèrer les animations de combat du personnage

*/
void anim_combat_perso(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON], ennemi_t *ennemi){
  int tmp_x = pers->sprites[courant].rectangle.x;

//Jouer l'animation de combat
  if(!strcmp(carte->nom, "poing I") || !strcmp(carte->nom, "poing II") || !strcmp(carte->nom, "poing X") || !strcmp(carte->nom,"epee I") || !strcmp(carte->nom,"epee II") || !strcmp(carte->nom,"epee X") || !strcmp(carte->nom, "pierre I") || !strcmp(carte->nom, "pierre II") || !strcmp(carte->nom, "pierre X")){
    anim_combat_perso_attaque(pers, carte, rendu, sounds);
  }

//Jouer l'animation de soin
  if(!strcmp(carte->nom, "potion I") || !strcmp(carte->nom, "potion II") || !strcmp(carte->nom, "potion X") || !strcmp(carte->nom, "soin I") || !strcmp(carte->nom, "soin II") || !strcmp(carte->nom, "soin X") || !strcmp(carte->nom, "guerison I") || !strcmp(carte->nom, "guerison II") || !strcmp(carte->nom, "guerison X")){
    anim_combat_perso_soin(pers, carte, rendu, sounds);
  }

//Jouer l'animation de poison
  if(!strcmp(carte->nom, "poison I") || !strcmp(carte->nom, "poison II") || !strcmp(carte->nom, "poison X")){
    anim_combat_perso_poison(pers, carte, rendu, sounds, ennemi);
  }

//Jouer l'animation de barrière
  if(!strcmp(carte->nom, "barriere I") || !strcmp(carte->nom, "barriere II") || !strcmp(carte->nom, "barriere X")){
    anim_combat_perso_barriere(pers, carte, rendu, sounds);
  }

//Jouer l'animation de boule de feu
  if(!strcmp(carte->nom, "boule de feu I") || !strcmp(carte->nom, "boule de feu II") || !strcmp(carte->nom, "boule de feu X")){
    anim_combat_perso_bdf(pers, carte, rendu, sounds);
  }

  pers->sprites[courant].rectangle.x = tmp_x;
}
