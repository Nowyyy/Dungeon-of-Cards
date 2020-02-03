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


#define WIN_HEIGHT 620
#define WIN_WIDTH 1080

#define FONT_PATH "../Font/BebasNeue.ttf"

#define TRUE 1
#define FALSE 0

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
