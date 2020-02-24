/**
* \file constantes.h
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 30/01/2020
* \version 0.1

* \brief Constantes et structures du projet Roguelike
*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include <string.h>
#include "SDL2/SDL_mixer.h"


#define WIN_HEIGHT 620
#define WIN_WIDTH 1080

#define FONT_PATH "../Font/BebasNeue.ttf"
#define SOL1_PATH "../Images/dalle3.png"
#define MUR1_PATH "../Images/mur.png"
#define MUR2_PATH "../Images/mur_feu.png"
#define SOL2_PATH "../Images/dalle_cailloux.png"
#define SOL3_PATH "../Images/dalle_eau.png"
#define PORTE_PATH "../Images/dalle3.png"
#define COMMANDES_PATH "../Images/commandes.png"
#define INSTRUCTIONS_PATH "../Images/instructions.png"

#define SPRITE1_PATH "../Images/Animations_personnage/idle_droite.png"
#define SPRITE2_PATH "../Images/Animations_personnage/idle_gauche.png"
#define SPRITE3_PATH "../Images/Animations_personnage/droite1.png"
#define SPRITE4_PATH "../Images/Animations_personnage/droite2.png"
#define SPRITE5_PATH "../Images/Animations_personnage/gauche2.png"
#define SPRITE6_PATH "../Images/Animations_personnage/gauche1.png"
#define SPRITE8_PATH "../Images/Animations_personnage/gauche3.png"
#define SPRITE9_PATH "../Images/Animations_personnage/droite3.png"
#define SPRITE7_PATH "../Images/Animations_personnage/dead.png"

#define SAVE_PERSO_PATH "../Sauvegarde/personnage.txt"
#define SAVE_CARTES_PATH "../Sauvegarde/cartes.txt"

#define NB_TEXTURES 8

#define TRUE 1
#define FALSE 0

#define TAILLE_SALLE 8 //Taille de la matrice d'un salle

#define TAILLE_IMAGE 64 //taille du coté d'une image

#define TAILLE 20 //Taille des chaînes de caractères
#define TAILLE_DECK 5

#define NB_SPRITES_PERSONNAGE 10

#define EMPLACEMENT_DEPART_DESSIN_SALLE_X 256
#define EMPLACEMENT_DEPART_DESSIN_SALLE_Y 40

#define VITESSE_PERSO 10

#define RECT_SELECT_Y_DIFF 25
#define RECT_SELECT_X_DIFF 50

#define NB_TOUCHES_UTILISEES 5

#define DELAIS_ANIMATIONS 300

#define PV_DEPART_PERSONNAGE 50
#define VITESSE_DEPART_PERSONNAGE 5
#define ATTAQUE_DEPART_PERSONNAGE 10
#define DEFENSE_DEPART_PERSONNAGE 10


/**
* \enum t_sprites_perso

* \brief les types de sprites pour les animations du personnage
*/

typedef enum{courant, idle_droite, idle_gauche, droite1, droite2, droite3, gauche2, gauche1, gauche3, dead}t_sprites_perso;

/**
* \enum t_types_textures

* \brief les types de textures sur lequel le perso peut tomber
*/
typedef enum{sol =0, mur, porte, sol2, commandes, instructions, sol3, mur2}t_types_textures;


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
* \enum t_touches_clavier

* \brief Les différents types de touches utilisées
*/
typedef enum{up, down, right, left, entree}t_touches_clavier;


/**
* \struct animation_t

* \brief permet de gèrer les animations du personnage
*/
typedef struct{
  
  int actuel;

  unsigned int last_use;

}animation_t;



/**
* \struct touchs_t

* \brief permet de gèrer les touches utilisées
*/
typedef struct{
  
  int tab[NB_TOUCHES_UTILISEES];
}touches_t;

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

  int s_b, s_h, s_g, s_d;

  SDL_Rect murs[TAILLE_SALLE*TAILLE_SALLE];
  SDL_Rect portes[TAILLE_SALLE];

  int nb_murs, haut, bas, gauche, droite, nb_portes, id;

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
  int etage;
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
  int consommable;/** 1 si la carte est à usage unique*/
} carte_t ;

// Definition du type d'un element de liste
typedef struct element {
  carte_t * carte;
  struct element* pred;
  struct element* succ;
} element_t;

// Declaration des listes (drapeau et element courant)
element_t* drapeau;
element_t* ec;
