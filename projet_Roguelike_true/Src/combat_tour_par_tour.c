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
#include "../include/main_menu_screen.h"
/**
*\fn void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi)

*\param *ennemi, la structure contenant tous les ennemis
*\param pers, la structure contenant le personnage
*\param *rendu, le renderer sur lequel on dessine

*\brief Permet d'afficher toutes la partie combat

*/
void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi,SDL_Texture defausse_texture ,SDL_Texture fuir_texture,SDL_Rect defausse_rect ,SDL_Rect fuir_rect){
  //écran noir puis nettoie l'écran
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  image_t images[NB_TEXTURES];
  /*Mise en place des fonds*/
  charge_image(FOND_COMBAT_PATH,&images[fond2], rendu);
  images[fond2].rectangle.x= -50;
  images[fond2].rectangle.y= -415;
  images[fond2].rectangle.w *= 2;
  images[fond2].rectangle.h *= 2;
  SDL_RenderCopy(rendu, images[fond2].img, NULL, &images[fond2].rectangle);

  charge_image(COMBAT_PATH,&images[fond], rendu);
  images[fond].rectangle.x=0;
  images[fond].rectangle.y= 450;
  images[fond].rectangle.w *= 4;
  SDL_RenderCopy(rendu, images[fond].img, NULL, &images[fond].rectangle);

  /*Mise en place des cartes */
  charge_image(CARTE1_PATH,&images[carte1], rendu);
  images[carte1].rectangle.x=50;
  images[carte1].rectangle.y= 450;
  images[carte1].rectangle.w /=8;
  images[carte1].rectangle.h /=8;
  SDL_RenderCopy(rendu, images[carte1].img, NULL, &images[carte1].rectangle);

  charge_image(CARTE2_PATH,&images[carte2], rendu);
  images[carte2].rectangle.x=250;
  images[carte2].rectangle.y= 450;
  images[carte2].rectangle.w /=2;
  images[carte2].rectangle.h /=2;
  SDL_RenderCopy(rendu, images[carte2].img, NULL, &images[carte2].rectangle);

  charge_image(CARTE3_PATH,&images[carte3], rendu);
  images[carte3].rectangle.x=450;
  images[carte3].rectangle.y= 450;
  images[carte3].rectangle.w /=2;
  images[carte3].rectangle.h /=2;
  SDL_RenderCopy(rendu, images[carte3].img, NULL, &images[carte3].rectangle);

  charge_image(CARTE4_PATH,&images[carte4], rendu);
  images[carte4].rectangle.x=650;
  images[carte4].rectangle.y= 450;
  images[carte4].rectangle.w /=2;
  images[carte4].rectangle.h /=2;
  SDL_RenderCopy(rendu, images[carte4].img, NULL, &images[carte4].rectangle);

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
  int xe=ennemi->sprites[0].rectangle.x;
  int ye=ennemi->sprites[0].rectangle.y;
  int he=ennemi->sprites[0].rectangle.h;
  int we=ennemi->sprites[0].rectangle.w;
  ennemi->sprites[0].rectangle.x = 750;
  ennemi->sprites[0].rectangle.y = 240;
  ennemi->sprites[0].rectangle.w *= 3;
  ennemi->sprites[0].rectangle.h *= 3;
  ennemi->sprites[0] = ennemi->sprites[0];
  SDL_RenderCopy(rendu, ennemi->sprites[0].img, NULL, &ennemi->sprites[0].rectangle);

  SDL_RenderPresent(rendu);
  pers->sprites[idle_droite].rectangle.w = w;
  pers->sprites[idle_droite].rectangle.h = h;
  pers->sprites[idle_droite].rectangle.x = x+10;
  pers->sprites[idle_droite].rectangle.y = y+10;
  ennemi->sprites[0].rectangle.w = we;
  ennemi->sprites[0].rectangle.h = he;
  ennemi->sprites[0].rectangle.x = xe-50;
  ennemi->sprites[0].rectangle.y = ye+50;
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
  TTF_Font * police = NULL;
  police=TTF_OpenFont(FONT_PATH,40);
  char * defausse=malloc(sizeof(char));
  char * fuir=malloc(sizeof(char));
  strcpy(defausse,"Defausse");
  strcpy(fuir,"Fuir");
  image_t def;
  image_t fui;
  /*DEFAUSSE*/
  def.rectangle.x=875;
  def.rectangle.y=475;
  get_text_and_rect(rendu,def.rectangle.x, def.rectangle.y, defausse,police, &def.img, &def.rectangle);
  /*FUIR*/
  fui.rectangle.x=875;
  fui.rectangle.y=550;
  get_text_and_rect(rendu,fui.rectangle.x, fui.rectangle.y, fuir,police, &fui.img, &fui.rectangle);
  init_liste();
  ajout_droit(creer_carte("soin", DEFENSE, 5, 0));
  ajout_droit(creer_carte("potion", DEFENSE, 20, 1));
  ajout_droit(creer_carte("épée", ATTAQUE,10, 0));
  ajout_droit(creer_carte("boule de feu", ATTAQUE, 20, 0));
  int choix, i, vitesse,fuire=1;
  vitesse = perso->vitesse;
  while((ennemi->pv > 0 && perso->pv > 0) && fuire==1 ){
    affichage_combat_personnage(rendu,perso,ennemi,def.img,fui.img,def.rectangle,fui.rectangle);
    printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);

    for(i=0, en_tete() ; i<4 ; i++, suivant()){
      printf("[%d] : %s\n", i+1, ec->carte->nom);
    }
    printf("[6] : Fuir\n");
    scanf("%d",&choix);
    if(choix == 6){
      fuire=0;
    }
    else if (initiative(perso, ennemi)){
      tour_perso(choix, perso, ennemi);
      if(ennemi->pv)
        tour_ennemi(perso, ennemi);
    }
    else{
      tour_ennemi(perso, ennemi);
      if(perso->pv)
        tour_perso(choix, perso, ennemi);
    }
  }
  if(!ennemi->pv){
    printf("Vous avez vaincu le %s\n", ennemi->nom);
  }
  else if (!perso->pv){
    printf("Vous avez été vaincu par le %s\n", ennemi->nom);
  }
  else {
    printf("Vous avez fuit le combat\n");
  }
  perso->vitesse = vitesse;
  return ennemi->pv;
  TTF_CloseFont(police);
  SDL_DestroyTexture(def.img);
}
