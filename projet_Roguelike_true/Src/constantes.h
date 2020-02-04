/**
* \file constantes.h
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 30/01/2020
* \version 0.1

* \brief Constantes et structures du projet Casse-brique
*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>


#define WIN_HEIGHT 620
#define WIN_WIDTH 1080

#define FONT_PATH "../Font/BebasNeue.ttf"

#define TRUE 1
#define FALSE 0

#define TAILLE_SALLE 9 //Taille de la matrice d'un salle

#define TAILLE_IMAGE 64 //taille du coté d'une image


/**
* \enum t_etat

* \brief les états que peut prendre le jeu afin de naviguer entre les menus
*/

typedef enum{mainMenu = 0, labyrinthe, tourParTour, pauseScreen}t_etat;



/**
* \struct t_image

* \brief contient les éléments necéssaires au stockage d'une image
*/
typedef struct{

	SDL_Texture *img;
	SDL_Rect rectangle;
}t_image;

/**
\struct salle_t
\brief Représente une salle et ses liaisons aux autres salles
*/
typedef struct salle_s{
  int salle[TAILLE_SALLE][TAILLE_SALLE], salle_id;
  struct salle_s *salle_bas, *salle_haut, *salle_gauche, *salle_droite, *salle_prec;
}salle_t;
