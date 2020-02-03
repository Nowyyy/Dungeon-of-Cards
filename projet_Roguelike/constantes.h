/*  
* \file constantes.h
* \author Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas
* \date 30/01/2020
* \version 0.1

* \brief Constantes et structures du projet Casse-brique                     
*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>


#define WIN_HEIGHT 620
#define WIN_WIDTH 1080

#define FONT_PATH "font/BebasNeue.ttf"

#define TRUE 1
#define FALSE 0

typedef enum{mainMenu = 0, labyrinthe, tourParTour, pauseScreen}t_etat;
