/**
 * \file salle.c
 * \brief Programme qui créé une salle et l'affiche.
 * \author {Axel Jourry, Aurélien Tudoret}
 * \version 0.1
 * \date 30 Janvier 2020
 */

#include "../include/constantes.h"
#include "../include/labyrinthe.h"

/**
 * \fn init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE])
 * \brief fonction qui génère une salle en un tableau
 * \param salle[TAILLE_SALLE][TAILLE_SALLE] est le tableau de TAILLE_SALLE qui comprend la salle
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


/**
 * \fn afficher_salle(int salle[TAILLE_SALLE][TAILLE_SALLE])

 * \brief fonction qui génère une salle en un tableau

 * \param *salle est une salle comportant le tableau a afficher
 * \param *rendu, le renderer sur lequel on dessine
 * \param texture[], contient toutes les images utilisées sauf celle du personnage

 */
void afficher_salle(salle_t *salle, SDL_Renderer *rendu, image_t texture[]){

  int coorX = EMPLACEMENT_DEPART_DESSIN_SALLE_X, coorY = EMPLACEMENT_DEPART_DESSIN_SALLE_Y;

  for(int i = 0; i<TAILLE_SALLE; i++){

    for(int j=0; j<TAILLE_SALLE; j++){

      texture[salle->salle[i][j]].rectangle.x = coorX;
      texture[salle->salle[i][j]].rectangle.y = coorY;

      SDL_RenderCopy(rendu, texture[salle->salle[i][j]].img, NULL, &texture[salle->salle[i][j]].rectangle);

      coorX += TAILLE_IMAGE-1;
    }
    coorX = EMPLACEMENT_DEPART_DESSIN_SALLE_X;
    coorY += TAILLE_IMAGE - 1;
  }
}



/**
* \fn rempli_tableau_salle_murs_portes

* \param *salle la salle pour laquelle on va completer les tableaux

* \brief rempli les tableaux des murs et des portes de la salle afin de pouvoir gérer les collisions plus tard
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
 * \fn aleatoire_salle(salle_t *salle)
 * \brief fonction qui créer aléatoirement des portes dans une salle, version 2 pour les salles mallocs
 * \param salle_t *salle est la structure représentant une salle
 * \param porte_arrivee, permet d'indiquer si on vient d'une autre salle afin de générer une porte à l'endroit auquel le joueur arrive
 * \param max_porte, le nombre max de porte que l'on souhaite créer

 * \return le nombre de portes créées
 *//*
int aleatoire_porte(salle_t *salle, int porte_arrivee, int max_porte){

  int alea;
  int cmp = 0;

  //Nord
  alea = rand()%9;
  if(alea > 5 && max_porte > 0){
    ajout_porte_salle(salle->salle, 0);
    cmp++;
    salle->haut = 1;
  }
  else if(porte_arrivee == 0){
    ajout_porte_salle(salle->salle, 0);
    salle->haut = 1;
    cmp++;
  }

  //Est
  alea = rand()%9;
  if(alea > 5&& max_porte -cmp > 0){
    ajout_porte_salle(salle->salle, 1);
    cmp++;
    salle->droite = 1;
  }
  else if(porte_arrivee == 1){
    ajout_porte_salle(salle->salle, 1);
    salle->droite = 1;
    cmp++;
  }

  //Sud
  alea = rand()%9;
  if(alea > 5 && max_porte -cmp > 0){
    ajout_porte_salle(salle->salle, 2);
    cmp++;
    salle->bas = 1;
  }
  else if(porte_arrivee == 2){
    ajout_porte_salle(salle->salle, 2);
    salle->bas = 1;
    cmp++;
  }

  //Ouest
  alea = rand()%9;
  if(alea > 5 && max_porte - cmp > 0){
    ajout_porte_salle(salle->salle, 3);
    cmp++;
    salle->gauche = 1;
  }
  else if(porte_arrivee == 3){
    ajout_porte_salle(salle->salle, 3);
    salle->gauche = 1;
    cmp++;
  }

  if(cmp == 0 && max_porte > 0){

    alea = rand()%4;

    switch(alea){
      case 0: salle->haut = 1; ajout_porte_salle(salle->salle, 0); break;
      case 1: salle->droite = 1; ajout_porte_salle(salle->salle, 1); break;
      case 2: salle->bas = 1; ajout_porte_salle(salle->salle, 2); break;
      case 3: salle->gauche = 1; ajout_porte_salle(salle->salle, 3); break;
    }
    cmp++;
  }

  return cmp;
}*/



/**
* \fn inverse_porte

* \param porte, la porte que l'on souhaite inverser

* \return l'inverse de la porte passée en paramètre

* \brief Renvoie l'opposée de la porte passée en paramètre
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
* \fn textures_aleatoires

* \param salles[], le tableau contenant les salles du labyrinthe
* \param taille, la taille de la salle

* \brief Permet de placer des textures différentes afin de varier le visuel des salles
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
* \fn place_monstre_coffre_boss

* \param tab[], tableau contenant les salles du labyrinthe
* \param taille, taille du tableau

* \brief rempli les salles de monstres, de coffre ou place un boss

*/
void place_monstre_coffre_boss(salle_t tab[], int taille){

  int alea;

  for(int i = 0; i < taille - 1; i++){

    //choix de monstres ou coffre dans les autres salles que celle du début et celle du boss
    if(i == 0){
      tab[i].ennemi_present = 0;

    }
    else if (tab[i].salle_existe && tab[i].boss == FALSE){
      alea = rand()%10;
      tab[i].pv1 = 1;
      tab[i].pv2 = 1;

      //choix pour un monbre ou un coffre dans la salle
      if(alea <= 7){
        tab[i].ennemi_present = 1;

        alea = rand()%8;

        tab[i].x_ennemi1 = rand()%TAILLE_SALLE;
        tab[i].y_ennemi1 = rand()%TAILLE_SALLE;

        //on place l'ennemi dans la salle avec ses coordonnées
        if(tab[i].x_ennemi1 == 0)
          tab[i].x_ennemi1 += 1;
        else if(tab[i].x_ennemi1 == TAILLE_SALLE - 1)
          tab[i].x_ennemi1 -= 1;

        if(tab[i].y_ennemi1 == 0)
          tab[i].y_ennemi1 += 1;
        else if(tab[i].y_ennemi1 ==  TAILLE_SALLE - 1)
          tab[i].y_ennemi1 -= 1;

        if(alea <= 4){
          tab[i].nb_ennemi = 1;
        }
        //il y aura deux ennemis
        else{
          tab[i].x_ennemi2 = rand()%TAILLE_SALLE;
          tab[i].y_ennemi2 = rand()%TAILLE_SALLE;

          if(tab[i].x_ennemi2 == 0)
            tab[i].x_ennemi2 += 1;
          else if(tab[i].x_ennemi2 == TAILLE_SALLE - 1)
            tab[i].x_ennemi2 -= 1;

          if(tab[i].y_ennemi2 == 0)
            tab[i].y_ennemi2 += 1;
          else if(tab[i].y_ennemi2 ==  TAILLE_SALLE - 1)
            tab[i].y_ennemi2 -= 1;

          tab[i].nb_ennemi = 2;
        }
        tab[i].coffre = 0;
      }
      //pas d'ennemi dans la salle
      else{
        tab[i].ennemi_present = 0;
        tab[i].coffre = 1;
      }
    }
  }
}
