/**
*\file animation.c
*\author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
*\date 18/02/2020
*\version 0.1

*\brief Gère l'animation de chargement de niveau
*/

#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include <time.h>

/**
*\fn void animation_niveau()
*\param perso, la structure du personnaeg
*\param *rendu, le renderer sur lequel on dessine
*\brief Fonction qui anime le lancement d'une partie avec un chargement
*/
void animation_niveau(perso_t *perso, SDL_Renderer *rendu){

  //initialisation des variables
  srand(time(NULL));
  image_t texte_etage, texte_charg, p1, p2, p3;
  char etage[15], charg[15]="chargement", cp1[10]=".", cp2[10]=".", cp3[10]=".";
  TTF_Font *police = NULL;
  int x_etage = 480, y_etage = 250, x_charg = 450, y_charg = 350;
  int p1_x = 2000, p1_y = 350, p2_x = 2000, p2_y = 350, p3_x = 2000, p3_y = 350;
  int char_alea = rand()%(9-4)+4;
  int cmp = 0, cmp2=0;
  police = TTF_OpenFont(FONT_PATH, 30);
  malloc_cpt++;
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
  malloc_cpt--;
  SDL_DestroyTexture(texte_etage.img);
  SDL_DestroyTexture(texte_charg.img);
  SDL_DestroyTexture(p1.img);
  SDL_DestroyTexture(p2.img);
  SDL_DestroyTexture(p3.img);
  malloc_cpt-=5;


}
