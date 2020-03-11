#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"

void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi){
  //écran noir puis nettoie l'écran
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  image_t images[NB_TEXTURES];
  charge_image(FOND_COMBAT_PATH,&images[fond2], rendu);
  charge_image(COMBAT_PATH,&images[fond], rendu);
  /*Mise en place du personnage*/
  pers->sprites[idle_droite].rectangle.x = 200;
  pers->sprites[idle_droite].rectangle.y = 300;
  pers->sprites[courant] = pers->sprites[idle_droite];
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);
  /*
  ennemi->sprites[idle_gauche].rectangle.x = 600;
  ennemi->sprites[idle_gauche].rectangle.y = 300;
  ennemi->sprites[courant] = ennemi->sprites[idle_gauche];
  SDL_RenderCopy(rendu, ennemi->sprites[courant].img, NULL, &ennemi->sprites[0].rectangle);
  */
  SDL_RenderPresent(rendu);
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
  ajout_droit(creer_carte("épée", ATTAQUE, 10, 0));
  ajout_droit(creer_carte("épée", ATTAQUE,10, 0));
  ajout_droit(creer_carte("boule de feu", ATTAQUE, 20, 0));
  int choix, i, vitesse;
  vitesse = perso->vitesse;
  while(ennemi->pv > 0 && perso->pv > 0){
    affichage_combat_personnage(rendu,perso,ennemi);
    printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);

    for(i=0, en_tete() ; !hors_liste() ; i++, suivant()){
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
