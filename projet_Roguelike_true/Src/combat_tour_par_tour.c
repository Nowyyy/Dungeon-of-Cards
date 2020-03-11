#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"
void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers){
  //écran noir puis nettoie l'écran
  SDL_SetRenderDrawColor(rendu,0,0,0,255);
  SDL_RenderClear(rendu);
  pers->sprites[idle_droite].rectangle.x = pers->x;
  pers->sprites[idle_droite].rectangle.y = pers->y;
  pers->sprites[courant] = pers->sprites[idle_droite];
  SDL_RenderCopy(rendu, pers->sprites[courant].img, NULL, &pers->sprites[0].rectangle);

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
  affichage_combat_personnage(rendu,perso);
  return 0;
  /*
  int choix, i, vitesse;
  vitesse = perso->vitesse;
  while(ennemi->pv > 0 && perso->pv > 0){
    affichage_combat_personnage(rendu,perso);
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
  */
}
