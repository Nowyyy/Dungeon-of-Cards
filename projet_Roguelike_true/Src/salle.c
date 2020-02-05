/**
 * \file salle.c
 * \brief Programme qui créé une salle et l'affiche.
 * \author Axel Jourry
 * \version 1.0
 * \date 30 Janvier 2020
 */

#include "constantes.h"

/**
 * \fn init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE])
 * \brief fonction qui génère une salle en un tableau
 * \param salle[TAILLE_SALLE][TAILLE_SALLE] est le tableau de TAILLE_SALLE qui comprend la salle
 */

void init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE]){

  for(int i = 0; i<TAILLE_SALLE; i++){
    for(int j=0; j<TAILLE_SALLE; j++){

      if(j == 0){
        salle[i][j]=1;
      }
      else if(i == 0){
        salle[i][j]=1;
      }
      else if(i == TAILLE_SALLE-1){
        salle[i][j]=1;
      }
      else if(j == TAILLE_SALLE-1){
        salle[i][j]=1;
      }
      else{
        salle[i][j]=0;

      }

    }
  }
}

/**
 * \fn init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE])
 * \brief fonction qui ajoute une porte à un côté du carré
 * \param salle[TAILLE_SALLE][TAILLE_SALLE] est le tableau de TAILLE_SALLE qui comprend la salle
 * \param direction correspond à un nombre entre 0 et 3 indiquant quel mur est seléctionné.
 */
void ajout_porte_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], int direction){
  int millieu = TAILLE_SALLE / 2;
  for(int i = 0; i<TAILLE_SALLE; i++){
    for(int j=0; j<TAILLE_SALLE; j++){

      //Nord
      if(direction == 0){
        if(i == 0){
          if(j == millieu-1 || j == millieu){
            salle[i][j]=2;
          }
        }
      }
      if(direction == 1){
        if(j == 0){
          if(i == millieu-1 || i == millieu){
            salle[i][j]=2;
          }
        }
      }

      //Sud
      if(direction == 2){
        if(j == TAILLE_SALLE-1){
          if(i == millieu-1 || i == millieu){
            salle[i][j]=2;
          }
        }
      }

      //Est
      if(direction == 3){
        if(i == TAILLE_SALLE-1){
          if(j == millieu-1 || j == millieu){
            salle[i][j]=2;
          }
        }
      }
    }
  }
}


/**
 * \fn aleatoire_salle(salle_t *salle)
 * \brief fonction qui créer aléatoirement des portes dans une salle
 * \param salle_t *salle est la structure représentant une salle
 * \param porte_arrivee, permet d'indiquer si on vient d'une autre salle afin de générer une porte à l'endroit auquel le joueur arrive
 */
void aleatoire_porte(salle_t *salle, int porte_arrivee){
  SDL_Delay(10);
  srand(time(NULL));
  int alea;
  int cmp = 0;

  //Si salle de départ
  if(salle->salle_prec==NULL){

    //Nord
    alea = rand()%9;
    if(alea > 5 || porte_arrivee == 0){
      ajout_porte_salle(salle->salle, 0);
      cmp++;
    }
    //Ouest
    alea = rand()%9;
    if(alea > 5 || porte_arrivee == 1){
      ajout_porte_salle(salle->salle, 1);
      cmp++;

    }
    //Sud
    alea = rand()%9;
    if(alea > 5 || porte_arrivee == 2){
      ajout_porte_salle(salle->salle, 2);
      cmp++;

    }
    //Est
    alea = rand()%9;
    if(alea > 5 || porte_arrivee == 3){
      ajout_porte_salle(salle->salle, 3);
      cmp++;
    }
    else if(cmp==0){
      ajout_porte_salle(salle->salle, rand()%4);
    }
  }

  //Si pas salle de départ
  //A FAIRE CAS OU UNE SALLE PREC EXISTE
  //Link la salle a la porte de départ
}

/**
 * \fn afficher_salle(int salle[TAILLE_SALLE][TAILLE_SALLE])
 * \brief fonction qui génère une salle en un tableau
 * \param salle[TAILLE_SALLE][TAILLE_SALLE] est le tableau de TAILLE_SALLE qui comprend la salle
 * \param *rendu, le renderer sur lequel on dessine
 * \param texture[], contient toutes les images utilisées sauf celle du personnage

 * \return le nombre de murs dans la salle
 */
int afficher_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], SDL_Renderer *rendu, t_image texture[], SDL_Rect murs[]){

  int coorX = EMPLACEMENT_DEPART_DESSIN_SALLE_X, coorY = EMPLACEMENT_DEPART_DESSIN_SALLE_Y;
  int indice = 0;

  for(int i = 0; i<TAILLE_SALLE; i++){

    for(int j=0; j<TAILLE_SALLE; j++){
      texture[salle[i][j]].rectangle.x = coorX;
      texture[salle[i][j]].rectangle.y = coorY;

      if(salle[i][j] == mur){
        murs[indice].x = coorX;
        murs[indice].y = coorY;
        murs[indice].w = TAILLE_IMAGE;
        murs[indice++].h = TAILLE_IMAGE;
      }

      SDL_RenderCopy(rendu, texture[salle[i][j]].img, NULL, &texture[salle[i][j]].rectangle);

      coorX += TAILLE_IMAGE;
    }
    coorX = 256;
    coorY += TAILLE_IMAGE;
  }

  return indice;
}
