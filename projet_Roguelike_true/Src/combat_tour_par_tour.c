#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"

void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi){
  //écran noir puis nettoie l'écran
  TTF_Font * police = NULL;
  police=TTF_OpenFont(FONT_PATH,40);
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  image_t images[NB_TEXTURES];
<<<<<<< HEAD
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
  char * defausse=malloc(sizeof(char));
  char * fuir=malloc(sizeof(char));
  strcpy(defausse,"Defausse");
  strcpy(fuir,"Fuir");
  image_t texte;
  image_t texte2;
  texte.rectangle.x=875;
  texte.rectangle.y=475;
  get_text_and_rect(rendu,texte.rectangle.x, texte.rectangle.y, defausse,police, &texte.img, &texte.rectangle);
  SDL_RenderCopy(rendu, texte.img, NULL, &texte.rectangle);

  texte2.rectangle.x=875;
  texte2.rectangle.y=550;
  get_text_and_rect(rendu,texte2.rectangle.x, texte2.rectangle.y, fuir,police, &texte2.img, &texte2.rectangle);
  SDL_RenderCopy(rendu, texte2.img, NULL, &texte2.rectangle);

  /*Mise en place du personnage*/
  int w=pers->sprites[idle_droite].rectangle.w;
  int h=pers->sprites[idle_droite].rectangle.h;
  int x=pers->sprites[idle_droite].rectangle.x;
  int y=pers->sprites[idle_droite].rectangle.y;
  pers->sprites[idle_droite].rectangle.w *=3;
  pers->sprites[idle_droite].rectangle.h *=3;
  pers->sprites[idle_droite].rectangle.x = 150;
  pers->sprites[idle_droite].rectangle.y = 250;
=======
  charge_image(FOND_COMBAT_PATH,&images[fond2], rendu);
  charge_image(COMBAT_PATH,&images[fond], rendu);
  /*Mise en place du personnage*/
  pers->sprites[idle_droite].rectangle.x = 200;
  pers->sprites[idle_droite].rectangle.y = 300;
>>>>>>> thomas_work
  pers->sprites[courant] = pers->sprites[idle_droite];
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);
  /*
  ennemi->sprites[idle_gauche].rectangle.x = 600;
  ennemi->sprites[idle_gauche].rectangle.y = 300;
  ennemi->sprites[courant] = ennemi->sprites[idle_gauche];
  SDL_RenderCopy(rendu, ennemi->sprites[courant].img, NULL, &ennemi->sprites[0].rectangle);
  */
  SDL_RenderPresent(rendu);
  pers->sprites[idle_droite].rectangle.w = w;
  pers->sprites[idle_droite].rectangle.h = h;
  pers->sprites[idle_droite].rectangle.x = x;
  pers->sprites[idle_droite].rectangle.y = y;
  TTF_CloseFont(police);
  SDL_DestroyTexture(texte.img);
}
/**
*\fn void combat(perso_t * perso, ennemi_t * ennemi, carte_t ** deck)
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\*\param deck Pointeur sur un pointeur de fonction qui permet de connaître le deck du personnage
*/
int combat_t_p_t(perso_t * perso, ennemi_t * ennemi,SDL_Renderer *rendu)
{
  affichage_combat_personnage(rendu,perso,ennemi);
  init_liste();
  ajout_droit(creer_carte("soin", DEFENSE, 5, 0));
  ajout_droit(creer_carte("potion", DEFENSE, 20, 1));
<<<<<<< HEAD
=======
  ajout_droit(creer_carte("épée", ATTAQUE, 10, 0));
>>>>>>> thomas_work
  ajout_droit(creer_carte("épée", ATTAQUE,10, 0));
  ajout_droit(creer_carte("boule de feu", ATTAQUE, 20, 0));
  int choix, i, vitesse;
  vitesse = perso->vitesse;
  while(ennemi->pv > 0 && perso->pv > 0){
    affichage_combat_personnage(rendu,perso,ennemi);
    printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);

    for(i=0, en_tete() ; i<4 ; i++, suivant()){
      printf("[%d] : %s\n", i+1, ec->carte->nom);
    }
    scanf("%d",&choix);
    if (initiative(perso, ennemi)){
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
  else{
    printf("Vous avez été vaincu par le %s\n", ennemi->nom);
  }
  perso->vitesse = vitesse;
  return ennemi->pv;
}
