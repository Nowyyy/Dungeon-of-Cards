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
#define SOL1_PATH "../Images/herbe2.png"
#define MUR1_PATH "../Images/mur.png"
#define SOL2_PATH "../Images/herbe1.png"
#define SPRITE_PATH "../Images/sprite2.png"
#define COMMANDES_PATH "../Images/commandes.png"
#define INSTRUCTIONS_PATH "../Images/instructions.png"

#define TRUE 1
#define FALSE 0

#define TAILLE_SALLE 8 //Taille de la matrice d'un salle

#define TAILLE_IMAGE 64 //taille du coté d'une image

#define NB_SPRITES_PERSONNAGE 12

#define EMPLACEMENT_DEPART_DESSIN_SALLE_X 256
#define EMPLACEMENT_DEPART_DESSIN_SALLE_Y 20

#define VITESSE_PERSO 5

/**
* \enum t_types_textures

* \brief les types de textures sur lequel le perso peut tomber
*/
typedef enum{sol =0, mur, porte, commandes, instructions}t_types_textures;


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

  SDL_Rect murs[TAILLE_SALLE*TAILLE_SALLE];
  int nb_murs;

}salle_t;


/**
\struct t_perso
\brief Représente un personnage, ses sprites et ses coordonnées
*/
typedef struct{

	int x, y;
	t_image sprites[NB_SPRITES_PERSONNAGE];
}t_perso;
