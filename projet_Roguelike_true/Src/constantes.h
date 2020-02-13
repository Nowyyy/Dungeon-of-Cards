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

#define TAILLE 20 //Taille des chaînes de caractères
#define TAILLE_DECK 5

#define NB_SPRITES_PERSONNAGE 12

#define EMPLACEMENT_DEPART_DESSIN_SALLE_X 256
#define EMPLACEMENT_DEPART_DESSIN_SALLE_Y 40

#define VITESSE_PERSO 5

#define RECT_SELECT_Y_DIFF 25
#define RECT_SELECT_X_DIFF 50

/**
* \enum t_types_textures

* \brief les types de textures sur lequel le perso peut tomber
*/
typedef enum{sol =0, mur, porte, commandes, instructions}t_types_textures;


/**
* \enum t_etat

* \brief les états que peut prendre le jeu afin de naviguer entre les menus
*/

typedef enum{mainMenu = 0, labyrinthe, tourParTour, pauseScreen, charger_partie}t_etat;

/**
* \enum type_carte

* \brief Les différents types de cartes
*/

typedef enum {ATTAQUE = -1, DEFENSE = 1} type_carte ;

/**
* \struct t_image

* \brief contient les éléments necéssaires au stockage d'une image
*/
typedef struct{

	SDL_Texture *img;
	SDL_Rect rectangle;
}image_t;

/**
\struct salle_t
\brief Représente une salle et ses liaisons aux autres salles
*/
typedef struct salle_s{

  int salle[TAILLE_SALLE][TAILLE_SALLE];

  struct salle_s *salle_bas, *salle_haut, *salle_gauche, *salle_droite, *salle_prec;

  SDL_Rect murs[TAILLE_SALLE*TAILLE_SALLE];
  SDL_Rect portes[TAILLE_SALLE];
  
  int nb_murs, haut, bas, gauche, droite, nb_portes;

}salle_t;


/**
*\struct perso_t
*\Permet de définir un personnage
*/
typedef struct perso_s {
  int pv;/**Point de vie d'un personnage*/
  int vitesse;/**Vitesse d'un personnage*/
  int attaque;/**Attaque d'un personnage*/
  int defense;/**Défense d'un personnage*/
  int x;/**Placement sur l'axe des abscisses d'un personnage*/
  int y;/**Placement sur l'axe des ordonnés d'un personnage*/
  image_t sprites[NB_SPRITES_PERSONNAGE];
} perso_t;

/**
*\struct ennemi_t
*\Permet de définir un ennemi
*/
typedef struct ennemi_s {
  int pv;/**Point de vie d'un ennemi*/
  int vitesse;/**Vitesse d'un ennemi*/
  int attaque;/**Attaque d'un ennemi*/
  int defense;/**Défense d'un ennemi*/
  char* nom;/** Nom de l'ennemi*/
} ennemi_t;

/**
\struct carte_t
\brief Représente une carte
*/

typedef struct carte_s {
  char * nom ;/** Nom d'une carte */
  type_carte type;/** Type d'une carte */
  int * cible;/** Cible d'une carte */
  int valeur;/** Valeur d'une carte */
} carte_t ;
