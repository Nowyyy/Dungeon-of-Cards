/**
 *\file salle.c
 *\brief Programme qui créé une salle et l'affiche.
 *\author {Axel Jourry, Aurélien Tudoret}
 *\version 0.1
 *\date 30 Janvier 2020
 */

#include "../include/constantes.h"
#include "../include/labyrinthe.h"
#include "../include/fonctions.h"
#include "../include/salle.h"


//Ecrit par Axel Jourry
/**
 *\fn void init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE])
 *\param salle[TAILLE_SALLE][TAILLE_SALLE] est le tableau de TAILLE_SALLE qui comprend la salle
 *\brief fonction qui génère une salle en un tableau
 */
void init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE]){

  for(int i = 0; i<TAILLE_SALLE; i++){
    for(int j=0; j<TAILLE_SALLE; j++){

      if(j == 0){
        salle[i][j]=mur;
      }
      else if(i == 0){
        salle[i][j]=mur;
      }
      else if(i == TAILLE_SALLE-1){
        salle[i][j]=mur;
      }
      else if(j == TAILLE_SALLE-1){
        salle[i][j]=mur;
      }
      else{
        salle[i][j]=sol;

      }

    }
  }
}


//Ecrit par Axel Jourry
/**
 *\fn void ajout_porte_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], int direction)
 *\param salle[TAILLE_SALLE][TAILLE_SALLE] est le tableau de TAILLE_SALLE qui comprend la salle
 *\param direction correspond à un nombre entre 0 et 3 indiquant quel mur est seléctionné.
 *\brief fonction qui ajoute une porte à un côté du carré

 */
void ajout_porte_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], int direction){

  int millieu = TAILLE_SALLE / 2;

  for(int i = 0; i<TAILLE_SALLE; i++){
    for(int j=0; j<TAILLE_SALLE; j++){

      //Nord
      if(direction == 0){
        if(i == 0){
          if(j == millieu-1 || j == millieu){
            salle[i][j]=porte;
          }
        }
      }
      //Ouest
      if(direction == 3){
        if(j == 0){
          if(i == millieu-1 || i == millieu){
            salle[i][j]=porte;
          }
        }
      }

      //Sud
      if(direction == 2){
        if(i == TAILLE_SALLE-1){
          if(j == millieu-1 || j == millieu){
            salle[i][j]=porte;
          }
        }
      }

      //Est
      if(direction == 1){
        if(j == TAILLE_SALLE-1){
          if(i == millieu-1 || i == millieu){
            salle[i][j]=porte;
          }
        }
      }
    }
  }
}


//Ecrit par Axel Jourry
/**
 *\fn void afficher_salle(salle_t *salle, SDL_Renderer *rendu, image_t texture[])

 *\param *salle est une salle comportant le tableau a afficher
 *\param *rendu, le renderer sur lequel on dessine
 *\param texture[], contient toutes les images utilisées sauf celle du personnage

 *\brief fonction qui génère une salle en un tableau

 */
void afficher_salle(salle_t *salle, SDL_Renderer *rendu, image_t texture[]){

  int coorX = EMPLACEMENT_DEPART_DESSIN_SALLE_X, coorY = EMPLACEMENT_DEPART_DESSIN_SALLE_Y;

  for(int i = 0; i<TAILLE_SALLE; i++){

    for(int j=0; j<TAILLE_SALLE; j++){

      texture[salle->salle[i][j]].rectangle.x = coorX;
      texture[salle->salle[i][j]].rectangle.y = coorY;

      SDL_RenderCopy(rendu, texture[salle->salle[i][j]].img, NULL, &texture[salle->salle[i][j]].rectangle);

      coorX += TAILLE_IMAGE;
    }
    coorX = EMPLACEMENT_DEPART_DESSIN_SALLE_X;
    coorY += TAILLE_IMAGE;
  }
}



/**
*\fn void rempli_tableau_murs_portes(salle_t salle[], int indiceT)

*\param salle[], la salle pour laquelle on va completer les tableaux
*\param indiceT, indice du tableau

*\brief rempli les tableaux des murs et des portes de la salle afin de pouvoir gérer les collisions plus tard
*/
void rempli_tableau_murs_portes(salle_t salle[], int indiceT){

  int indice = 0, indice_porte = 0;
  int coorX = EMPLACEMENT_DEPART_DESSIN_SALLE_X, coorY = EMPLACEMENT_DEPART_DESSIN_SALLE_Y;

  for(int i = 0; i<TAILLE_SALLE; i++){

    for(int j=0; j<TAILLE_SALLE; j++){

      if(salle[indiceT].salle[i][j] == mur){
        salle[indiceT].murs[indice].x = coorX;
        salle[indiceT].murs[indice].y = coorY;
        salle[indiceT].murs[indice].w = TAILLE_IMAGE;
        salle[indiceT].murs[indice++].h = TAILLE_IMAGE;
      }
      else if(salle[indiceT].salle[i][j] == porte){
        salle[indiceT].portes[indice_porte].x = coorX;
        salle[indiceT].portes[indice_porte].y = coorY;
        salle[indiceT].portes[indice_porte].w = TAILLE_IMAGE;
        salle[indiceT].portes[indice_porte++].h = TAILLE_IMAGE;
      }
      coorX += TAILLE_IMAGE;
    }
    coorX = 256;
    coorY += TAILLE_IMAGE;
  }

  salle[indiceT].nb_murs = indice;
  salle[indiceT].nb_portes = indice_porte;
}



/**
*\fn int inverse_porte(int porte)

*\param porte, la porte que l'on souhaite inverser

*\return l'inverse de la porte passée en paramètre

*\brief Renvoie l'opposée de la porte passée en paramètre
*/
int inverse_porte(int porte){

  if(porte == 0){
    return 2;
  }
  if(porte == 1){
    return 3;
  }
  if(porte == 2){
    return 0;
  }
  return 1;
}



/**
*\fn void textures_aleatoires(salle_t salles[], int taille)

*\param salles[], le tableau contenant les salles du labyrinthe
*\param taille, la taille de la salle

*\brief Permet de placer des textures différentes afin de varier le visuel des salles
*/
void textures_aleatoires(salle_t salles[], int taille){

  int i, j, k, alea;

  for(i = 0; i < taille; i++){

    for(j = 0; j < TAILLE_SALLE; j++){

      for(k = 0; k < TAILLE_SALLE; k++){

        if(salles[i].salle[j][k] == sol){
          alea = rand()%13+1;

          if(alea >= 6 && alea <= 8)
            salles[i].salle[j][k] = sol2;
          else if(alea > 12)
            salles[i].salle[j][k] = sol3;
        }

        else if(salles[i].salle[j][k] == mur){
          alea = rand()%10;

          if(alea >=8)
            salles[i].salle[j][k] = mur2;
        }
      }
    }
  }
}



/**
*\fn void place_monstre_coffre_boss(salle_t tab[], int taille, int type_ennemi, SDL_Renderer *rendu, int *ennemi_max)

*\param tab[], tableau contenant les salles du labyrinthe
*\param taille, taille du tableau
*\param type_ennemi, type de l'ennemi
*\param *rendu, le renderer sur lequel on dessine
*\param *ennemi_max, est le nombre d'ennemi max.

*\brief rempli les salles de monstres, de coffre
*/
void place_monstre_coffre_boss(salle_t tab[], int taille, int type_ennemi, SDL_Renderer *rendu, int *ennemi_max){

  int alea;

  for(int i = 0; i < taille - 1; i++){

    //choix de monstres ou coffre dans les autres salles que celle du début et celle du boss
    if(tab[i].depart == TRUE){
      tab[i].ennemi_present = 0;
      tab[i].nb_ennemi = 0;
      tab[i].coffre = 0;
      tab[i].prems = 0;
      tab[i].ennemi2 = NULL;
      tab[i].ennemi = NULL;

    }
    else if (tab[i].salle_existe && tab[i].boss == FALSE){
      alea = rand()%10;

      //choix pour un monbre ou un coffre dans la salle
      if(alea <= 8){
        tab[i].coffre = 0;
        tab[i].ennemi_present = 1;

        alea = rand()%8;

        if(alea <= 4){
          tab[i].nb_ennemi = 1;
          *(ennemi_max)+=1;
        }
        //il y aura deux ennemis
        else{

          tab[i].nb_ennemi = 2;
          *(ennemi_max)+=2;
        }
        tab[i].coffre = 0;
      }
      //pas d'ennemi dans la salle
      else{
        tab[i].coffre = 1;
        tab[i].nb_ennemi = 0;
        tab[i].ennemi_present = 0;
        tab[i].ennemi2 = NULL;
        tab[i].ennemi = NULL;
      }
    }
  }
}



/**
*\fn void creation_mini_map(int taille, int indice, mini_map_t *map)

*\param taille, la taille d'un côté du labyrinthe
*\param *map, un pointeur sur la minimap que l'on rempli

*\brief Créée et initialise la mini map avec toutes les salles considerées comme non-découvertes
*/
void creation_mini_map(int taille, mini_map_t *map){

  map->taille = taille * taille;

  int coorX = WIN_WIDTH * 0.74;
  int prevX = coorX;
  int coorY = 0, prevY = 10;

  for(int i = 0; i < map->taille; i++){

    map->salles_decouvertes[i] = FALSE;
    map->map[i].w = TAILLE_RECT_MINI_MAP_W;
    map->map[i].h = TAILLE_RECT_MINI_MAP_H;

    map->map[i].x = prevX;
    map->map[i].y = prevY;

    if((i + 1) % taille == 0){//fin de ligne
      prevY += TAILLE_RECT_MINI_MAP_H + 1;
      prevX = coorX;
    }
    else {
      prevX += TAILLE_RECT_MINI_MAP_W + 1;
    }
  }
}



/**
*\fn void ajoute_salle_decouverte(mini_map_t *map, salle_t salles[], int indice, int *salle_pred)

*\param *map, un pointeur sur la minimap que l'on modifie
*\param salles[], le tableau des salles du labyrinthe
*\param indice, la salle actuelle dans le tableau de salles
*\param *salle_pred, pointeur sur un entier stockant l'indice de la salle précédente

*\bief Ajoute la salle où se situe le joueur dans le tableau de salles découvertes
*/
void ajoute_salle_decouverte(mini_map_t *map, salle_t salles[], int indice, int *salle_pred){

  if(indice != *salle_pred){

    salles[indice].decouverte = TRUE;
    salles[indice].prems = 1;
    *salle_pred = indice;
    map->salles_decouvertes[indice] = TRUE;
  }
}



/**
*\fn void ajoute_ennemi(ennemi_t **ennemi, int type, SDL_Renderer *rendu, int etage)

*\param **ennemi, pointeur sur pointeur de type ennemi_t, l'ennemi que l'on va créer
*\param type, le type d'ennemi que l'en veut créer.
*\param *rendu, le renderer sur lequel on dessine
*\param etage, l'étage où se situe le joueur

*\brief créer un ennemi à partir d'un type donné
*/
void ajoute_ennemi(ennemi_t **ennemi, int type, SDL_Renderer *rendu, int etage){

  ennemi_t ennemi_tmp;

  ennemi_selon_etage(etage, 0, &ennemi_tmp);

  *ennemi = creer_ennemi(ennemi_tmp.pv, ennemi_tmp.attaque, ennemi_tmp.attaque, ennemi_tmp.attaque, type, rendu);

  (*ennemi)->last = SDL_GetTicks();
}



/**
*\fn void placer_monstre(ennemi_t *ennemi)

*\param *ennemi, l'ennemi à modifier

*\brief place l'ennemi de façon à ne pas bloquer les portes
*/
void placer_monstre(ennemi_t *ennemi){


  int x = 0, y = 0, milieu = TAILLE_SALLE /2, milieu1 = TAILLE_SALLE / 2 -1;

  do{
    x = rand()%TAILLE_SALLE;
    y = rand()%TAILLE_SALLE;

  }while(x == 0 || y == 0 || y == TAILLE_SALLE - 1 || x == TAILLE_SALLE -1 || y == milieu1 || y == milieu || x == milieu || x == milieu1);

  ennemi->sprites.rectangle.y = y * TAILLE_IMAGE + EMPLACEMENT_DEPART_DESSIN_SALLE_Y;
  ennemi->sprites.rectangle.x = x * TAILLE_IMAGE + EMPLACEMENT_DEPART_DESSIN_SALLE_X;
}



/**
*\fn creer_ennemi_pointeur(ennemi_t **ennemi, ennemi_t **ennemi2, int nb_ennemi, int type, SDL_Renderer *rendu, int etage)

*\param **ennemi, pointeur sur pointeur de type ennemi_t, l'ennemi que l'on va peut-être créer
*\param **ennemi2, pointeur sur pointeur de type ennemi_t, l'ennemi que l'on va peut-être créer
*\param nb_ennemi, peremet de savoir combien d'ennemis sont à créer
*\param type, le type d'ennemi que l'en veut créer.
*\param *rendu, le renderer sur lequel on dessine
*\param etage, l'étage où se situe le joueur

*\brief créer un/des ennemi à partir d'un type donné
*/
void creer_ennemi_pointeur(ennemi_t **ennemi, ennemi_t **ennemi2, int nb_ennemi, int type, SDL_Renderer *rendu, int etage){

  if(nb_ennemi > 0){

    ajoute_ennemi(ennemi, type, rendu, etage);
    placer_monstre(*ennemi);
    *ennemi2 = NULL;
  }

  if (nb_ennemi == 2){

    ajoute_ennemi(ennemi2, type, rendu, etage);

    do{
      placer_monstre(*ennemi2);

    }while(SDL_HasIntersection(&(*ennemi)->sprites.rectangle, &(*ennemi2)->sprites.rectangle));
    (*ennemi2)->anim_courante = idle_gauche_ennemi;
    (*ennemi2)->sprite_courant.y = (*ennemi2)->sprite_courant.h;
  }
}



/**
*\fn void affiche_mini_map(mini_map_t map, salle_t salle, SDL_Renderer *rendu)

*\param map, la structure contenant la minimap
*\param salle, la salle dans laquelle se situe le joueur
*\param *rendu, le renderer sur lequel on dessine

*\brief effectue l'affichage à l'écran de la minimap
*/
void affiche_mini_map(mini_map_t map, salle_t salle, SDL_Renderer *rendu){

  SDL_Rect rect;
  rect = map.map[0];
  rect.x = 794;
  rect.y = 5;
  rect.h = 175;
  rect.w = 255;

  SDL_SetRenderDrawColor(rendu,169,169,169,255);//gris
  SDL_RenderDrawRect(rendu, &rect); // rectangle qui sert de cadre à la mini map

  for(int i = 0; i < 64; i++){

    if(map.salles_decouvertes[i] == TRUE && i == salle.id){
      //salle dans laquelle se situe le joueur
      SDL_SetRenderDrawColor(rendu,255,0,0,255);//rouge
      SDL_RenderFillRect(rendu, &map.map[i]);
    }
    else if(map.salles_decouvertes[i] == TRUE){
      SDL_SetRenderDrawColor(rendu,255,255,255,255);//blanc
      SDL_RenderFillRect(rendu, &map.map[i]);
    }
    else{
      SDL_SetRenderDrawColor(rendu,0,0,0,255);
      SDL_RenderFillRect(rendu, &map.map[i]);
    }
  }
}



/**
*\fn ennemi_selon_etage

*\param etage, l'étage où se situe le joueur
*\param boss, si l'ennemi que l'on conçoit est un boss ou non
*\param *ennemi, l'ennemi pour lequel on donne les valeurs

*\brief Donne des points de vie et dommages différents selon l'étage et le style d'ennemi
*/
void ennemi_selon_etage(int etage, int boss, ennemi_t *ennemi){

  if(boss){
    switch(etage){
      case 1 : ennemi->pv = 65; ennemi->attaque = 18; break;
      case 2 : ennemi->pv = 80; ennemi->attaque = 23; break;
      case 3 : ennemi->pv = 95; ennemi->attaque =  28; break;
      case 4 : ennemi->pv = 110; ennemi->attaque = 33; break;
      default : ennemi->pv = 125; ennemi->attaque = 40; break;
    }
  }
  else{
    switch(etage){
      case 1 : ennemi->pv = 50; ennemi->attaque = 10; break;
      case 2 : ennemi->pv = 65; ennemi->attaque = 15; break;
      case 3 : ennemi->pv = 80; ennemi->attaque = 20; break;
      default : ennemi->pv = 95; ennemi->attaque = 25; break;
    }
  }
}
