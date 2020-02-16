/**
 * \file salle.c
 * \brief Programme qui créé une salle et l'affiche.
 * \author Axel Jourry
 * \version 0.1
 * \date 30 Janvier 2020
 */

#include "constantes.h"
#include "labyrinthe.h"

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

      coorX += TAILLE_IMAGE;
    }
    coorX = 256;
    coorY += TAILLE_IMAGE;
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
 */
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
}



/**
* \fn inverse_porte

* \param porte, la porte que l'on souhaite inverser

* \return l'inverse de la porte passée en paramètre

* \brief Renvoie l'opposée de la porte passée en paramètre
*/
int inverse_porte(int porte){

  if(porte == 0)
    return 2;
  if(porte == 1)
    return 3;
  if(porte == 2)
    return 0;
  if(porte == 3)
    return 1;
}


/**
* \fn ferme_porte_inutile

* \param salles[], le tableau contenant les salles du labyrinthe
* \param indice, l'indice de la salle pour laquelle on veut faire une modification

* \brief Ferme une porte dans la salle, pour laquelle on n'a pu effectuer de liaison vers une autre
*/
void ferme_porte_inutile(salle_t salles[], int indice){

  int i, millieu = TAILLE_SALLE / 2;

  if(salles[indice].haut == 1 || salles[indice].s_h == -1){

    salles[indice].haut = 0;
    salles[indice].salle[0][millieu] = mur;
    salles[indice].salle[0][millieu-1] = mur;
  }

  if(salles[indice].droite == 1 || salles[indice].s_d == -1){

    salles[indice].droite = 0;
    salles[indice].salle[millieu][TAILLE_SALLE-1] = mur;
    salles[indice].salle[millieu-1][TAILLE_SALLE-1] = mur;
  }

  if(salles[indice].bas == 1 || salles[indice].s_b == -1){

    salles[indice].bas = 0;
    salles[indice].salle[TAILLE_SALLE-1][millieu] = mur;
    salles[indice].salle[TAILLE_SALLE-1][millieu-1] = mur;
  }

  if(salles[indice].gauche == 1 || salles[indice].s_g == -1){

    salles[indice].gauche = 0;
    salles[indice].salle[millieu][0] = mur;
    salles[indice].salle[millieu-1][0] = mur;
  }
}



/**
* \fn porte_libre_existe

* \param salles[], le tableau contenant les salles du labyrinthe
* \param porte_libre, la porte pour laquelle on veut savoir si elle est sans liaison

* \return 1 si la porte est libre, 0 sinon

* \brief Regarde si la porte passée en paramètre est disponible pour effectuer une liaison
*/
int porte_libre_existe(salle_t salle, int porte_libre){

  if(porte_libre == 0 && salle.haut == 1)
    return TRUE;
  else if(porte_libre == 1 && salle.droite == 1)
    return TRUE;
  else if(porte_libre == 2 && salle.bas == 1)
    return TRUE;
  else if(porte_libre == 3 && salle.gauche == 1)
    return TRUE;
  else
    return FALSE;
}



/**
* \fn verifie_porte_ouverte

* \param salles[], le tableau contenant les salles du labyrinthe
* \param indice, l'indice de la salle pour laquelle on veut faire une modification
* \param taille, la taille du tableau de salle

* \brief Ouvre une porte si la liaison existe mais pas sa représentation physique
*/
void verifie_porte_ouverte(salle_t salles[], int indice, int taille){

  int s_h = salles[indice].s_h, s_d = salles[indice].s_d, s_g = salles[indice].s_g, s_b = salles[indice].s_b, millieu = TAILLE_SALLE / 2;

  if(salles[indice].s_h == inverse_porte(salles[s_h].s_b)){
    salles[indice].salle[0][millieu] = porte;
    salles[indice].salle[0][millieu-1] = porte;
  }

  else if(salles[indice].s_d == inverse_porte(salles[s_d].s_g)){
    salles[indice].salle[millieu][TAILLE_SALLE-1] = porte;
    salles[indice].salle[millieu-1][TAILLE_SALLE-1] = porte;
  }

  else if(salles[indice].s_b == inverse_porte(salles[s_b].s_h)){
    salles[indice].salle[TAILLE_SALLE-1][millieu] = porte;
    salles[indice].salle[TAILLE_SALLE-1][millieu-1] = porte;
  }

  else if(salles[indice].s_g == inverse_porte(salles[s_g].s_d)){
    salles[indice].salle[millieu][0] = porte;
    salles[indice].salle[millieu-1][0] = porte;
  }
}


/**
* \fn porte_disponible

* \param salles[], le tableau contenant les salles du labyrinthe
* \param indice, l'indice de la salle pour laquelle on veut faire une modification
* \param porte_possible, la porte pour laquelle on cherche un double éventuel

* \return Return vrai si la salle possède déjà une connexion vers la salle passée en paramètre, faux sinon

* \brief Return vrai si la salle possède déjà une connexion vers la salle passée en paramètre, faux sinon
*/
int porte_disponible(salle_t salles[], int indice, int porte_possible){

  if(salles[indice].s_h == porte_possible || salles[indice].s_b == porte_possible || 
    salles[indice].s_g == porte_possible || salles[indice].s_d == porte_possible)

    return FALSE;
  else
    return TRUE;
}


/**
* \fn rajoute_salle_ou_ferme_porte

* \param salles[], le tableau contenant les salles du labyrinthe
* \param deb, l'indice de la salle pour laquelle on veut chercher une porte à raccorder
* \param fin, l'indice de fin du tableau actuel
* \param porte, la porte pour laquelle on cherche une correspondance
* \param taille_max, la taille maximale que peut prendre le tableau

* \return la nouvelle taille du tableau

* \brief Ajoute une salle a laquelle raccorder la salle courante, ou ferme la porte concernée si l'on n'as plus la place pour créer d'autres salles
*/
int rajoute_salle_ou_ferme_porte(salle_t salles[], int deb, int fin, int porte, int taille_max){

  int porte2;

  if(fin < taille_max){

    aleatoire_porte(&salles[fin], inverse_porte(porte), fin);
    porte2 = porte_non_connectee(salles[fin]);

    if(porte_libre_existe(salles[fin],inverse_porte(porte))){
      cree_liaison(salles, deb, fin, porte);
      fin++;
    }
  }
  else{
    ferme_porte_inutile(salles, deb);
  }

  return fin;
}