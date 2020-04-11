/**
*\file constantes.h
*\author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
*\date 30/01/2020
*\version 0.1

*\brief Constantes et structures du projet Roguelike
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

#define SOL_TEST_PATH "../Images/truc.png"
#define SOL_TEST_2_PATH "../Images/truc2.png"
#define SOL_TEST_3_PATH "../Images/truc3.png"

#define SOL1_PATH "../Images/dalle3.png"
#define SOL1_2_PATH "../Images/dalle3_2.png"
#define SOL1_3_PATH "../Images/dalle_3.png"

#define MUR1_PATH "../Images/mur.png"
#define MUR1_2_PATH "../Images/mur_2.png"
#define MUR1_3_PATH "../Images/mur_3.png"

#define MUR2_PATH "../Images/mur_feu.png"
#define MUR2_2_PATH "../Images/mur_feu_2.png"
#define MUR2_3_PATH "../Images/mur_feu_3.png"

#define SOL2_PATH "../Images/dalle_cailloux.png"
#define SOL2_2_PATH "../Images/dalle_cailloux_2.png"
#define SOL2_3_PATH "../Images/dalle_cailloux_3.png"

#define SOL3_PATH "../Images/dalle_eau.png"
#define SOL3_2_PATH "../Images/dalle_eau_2.png"
#define SOL3_3_PATH "../Images/dalle_3_eau.png"

#define PORTE_PATH "../Images/dalle3.png"
#define PORTE_2_PATH "../Images/dalle3_2.png"
#define PORTE_3_PATH "../Images/dalle_3.png"

#define COMMANDES_PATH "../Images/commandes.png"
#define INSTRUCTIONS_PATH "../Images/instructions.png"
#define GAMEOVER_PATH "../Images/gameover.png"
#define DEATHLIGHT_PATH "../Images/deathlight.png"
#define HEART_PATH "../Images/heart.png"
#define TRAPDOOR_PATH "../Images/trapdoor2.png"
#define MOBCOUNTER_PATH "../Images/mob_counter.png"

#define COFFRE_PATH "../Images/coffre_sprites.png"

#define SPRITE1_PATH "../Images/Animations_personnage/idle_droite.png"
#define SPRITE2_PATH "../Images/Animations_personnage/idle_gauche.png"
#define SPRITE3_PATH "../Images/Animations_personnage/droite1.png"
#define SPRITE4_PATH "../Images/Animations_personnage/droite2.png"
#define SPRITE5_PATH "../Images/Animations_personnage/gauche2.png"
#define SPRITE6_PATH "../Images/Animations_personnage/gauche1.png"
#define SPRITE8_PATH "../Images/Animations_personnage/gauche3.png"
#define SPRITE9_PATH "../Images/Animations_personnage/droite3.png"
#define SPRITE7_PATH "../Images/Animations_personnage/dead.png"

#define SQUELETTE_PATH "../Images/sprites_mobs/squelette_sprites.png"
#define CYCLOPE_PATH "../Images/sprites_mobs/cyclo_sprites.png"
#define VOLANT_PATH "../Images/sprites_mobs/volant_sprites.png"
#define MINOTAURE_PATH "../Images/sprites_mobs/mino_sprites.png"
#define BLOB_PATH "../Images/sprites_mobs/blob_sprite.png"
#define IMP_PATH "../Images/sprites_mobs/imp_sprites.png"
#define SORCERER_PATH "../Images/sprites_mobs/sorcerer_sprites.png"
#define WIZARD_PATH "../Images/sprites_mobs/wizard_sprite2.png"
#define WITCH_PATH "../Images/sprites_mobs/witch_sprites.png"

#define COMBAT_PATH "../Images/combat1.png"
#define FOND_COMBAT_PATH "../Images/combat2.png"
#define GUI_COMBAT_PATH "../Images/GUI_bar.png"

#define CARTE_GUERISON_PATH "../Images/Cartes/guerison.png"
#define CARTE_SOIN_PATH "../Images/Cartes/soin.png"
#define CARTE_EPEE_I_PATH "../Images/Cartes/epee_1.png"
#define CARTE_POTION_I_PATH "../Images/Cartes/potion_1.png"
#define CARTE_POING_PATH "../Images/Cartes/poing.png"
#define CARTE_PIERRE_PATH "../Images/Cartes/pierre.png"
#define CARTE_B_DE_FEU_PATH "../Images/Cartes/boule_de_feu.png"
#define CARTE_POISON_PATH "../Images/Cartes/poison.png"
#define CARTE_BARRIERE_PATH "../Images/Cartes/barriere.png"

#define CARTE_NO_CARTE_PATH "../Images/Cartes/no_carte.png"

#define SAVE_PERSO_PATH "../Sauvegarde/personnage.txt"
#define SAVE_CARTES_DECK_PATH "../Sauvegarde/cartes_deck.txt"
#define SAVE_CARTES_COLLEC_PATH "../Sauvegarde/cartes_collec.txt"
#define SAVE_CARTES_CATALOGUE_PATH "../Sauvegarde/cartes_catalogue"
#define SAVE_CARTES_NEW_GAME_PATH "../Sauvegarde/cartes_nouvelle_partie.txt"

#define NB_TEXTURES_LABY 15
#define NB_TEXTURES_COMBAT 10

#define TRUE 1
#define FALSE 0

#define DECK 1
#define COLLEC 0

#define TAILLE_SALLE 8 //Taille de la matrice d'un salle

#define TAILLE_IMAGE 64 //taille du coté d'une image

#define TAILLE_LABY 8

#define TAILLE 20 //Taille des chaînes de caractères

#define TAILLE_ETAGE_FINAL 2 //Taille du dernier étage
#define TAILLE_DECK 5

#define DUREE_AFFICHAGE_CARTE_LOOT 5000

#define NB_SPRITES_PERSONNAGE 10

#define NB_CARTES_COMBAT 4
#define NB_CARTES 4

#define EMPLACEMENT_DEPART_DESSIN_SALLE_X 256
#define EMPLACEMENT_DEPART_DESSIN_SALLE_Y 40

#define EMPLACEMENT_DEFAUSSE_Y 475
#define EMPLACEMENT_DEFAUSSE_X 875
#define EMPLACEMENT_FUITE_Y 550

#define VITESSE_PERSO 1

#define RECT_SELECT_Y_DIFF 25
#define RECT_SELECT_X_DIFF 50

#define NB_TOUCHES_UTILISEES 6

#define DELAIS_ANIMATIONS 100

#define PV_DEPART_PERSONNAGE 50

#define TAILLE_RECT_MINI_MAP_H 20
#define TAILLE_RECT_MINI_MAP_W 30

#define NB_SALLES_LEVEL_1 10
#define NB_SALLES_LEVEL_2 15
#define NB_SALLES_LEVEL_3 20
#define NB_SALLES_LEVEL_4 25

#define NB_SON 17
#define NB_MUSIC 9

/**
*\enum t_sprites_perso

*\brief les types de sprites pour les animations du personnage
*/

typedef enum{courant, idle_droite, droite1, droite2, droite3, idle_gauche, gauche2, gauche1, gauche3, dead}t_sprites_perso;

/**
*\enum t_ligne_sprites_ennemi

*\brief les types de sprites pour les animations des ennemis
*/

typedef enum{idle_droite_ennemi, idle_gauche_ennemi, walk_droite, walk_gauche, ennemi_dead}t_ligne_sprites_ennemi;

/**
*\enum t_types_textures

*\brief les types de textures sur lequel le perso peut tomber
*/
typedef enum{sol =0, mur, porte, sol2, commandes, instructions, sol3, mur2, heart, trapdoor, trapdoor2, pv, etage,mobcounter,countertxt}t_types_textures;

/**
*\enum t_textures_combat

*\brief les types de textures pour les combats
*/
typedef enum{fond,fond2,coeur,gui_bar,carte1,carte2,carte3,carte4, gameover, deathlight,}t_textures_combat;


/**
*\enum t_types_ennemis

*\brief les types d'ennemis existants
*/
typedef enum{squelette, blob, imp, volant, minotaure, cyclope, wizard, witch, sorcerer}t_type_ennemis;


/**
*\enum t_etat

*\brief les états que peut prendre le jeu afin de naviguer entre les menus
*/

typedef enum{mainMenu = 0, labyrinthe, tourParTour, pauseScreen, charger_partie, confirmer_nouveau}t_etat;

/**
*\enum type_carte

*\brief Les différents types de cartes
*/

typedef enum {ATTAQUE = -1, DEFENSE = 1, NO_CARTE = 0} type_carte ;


/**
*\enum t_touches_clavier

*\brief Les différents types de touches utilisées
*/
typedef enum{up, down, right, left, entree, escape}t_touches_clavier;

/**
*\enum t_direction

*\brief Les différents types de touches utilisées
*/
typedef enum{haut, droite, bas, gauche}t_direction;


/**
*\enum t_sons

*\brief Les différents sons utilisés
*/
typedef enum{move=0, selection, change_salle, footsteps, gameOverFrame, death, collect, chest, enterFight, animDeath, punch, heal, sword, rock, potion, divine, bouclier}t_sons;

/**
*\enum t_musique

*\brief Les différentes musiques utilisées
*/
typedef enum{menu=0, level1, gameOverMusic, fight, boss, level2, level3, level4, level5}t_musique;

/**
*\struct animation_t

*\brief permet de gèrer les animations du personnage
*/
typedef struct{

  int actuel;

  unsigned int last_use;

}animation_t;


/**
*\struct touchs_t

*\brief permet de gèrer les touches utilisées
*/
typedef struct{

  int tab[NB_TOUCHES_UTILISEES];
}touches_t;

/**
*\struct t_image

*\brief contient les éléments necéssaires au stockage d'une image
*/
typedef struct{

	SDL_Texture *img;
	SDL_Rect rectangle;
}image_t;

/**
*\struct ennemi_t
*\Permet de définir un ennemi
*/
typedef struct ennemi_s {
  int pv, pv_max, pv_old;/**Point de vie d'un ennemi*/
  int vitesse;/**Vitesse d'un ennemi*/
  int attaque;/**Attaque d'un ennemi*/
  int defense;/**Défense d'un ennemi*/
  char* nom;/** Nom de l'ennemi*/
  int boss;/** Est un boss ou non*/
  int nb_sprites_idle;
  int gap;
  int w, h;
  unsigned int last;
  int anim_courante;
  int id_col;

  SDL_Rect sprite_courant;

  image_t sprites;
} ennemi_t;

/**
*\struct coffre_t
*\Contient les éléments nécessaires à l'initialisation d'un coffre
*/
typedef struct coffre_s{

  image_t sprite;

  int nb_sprites, courant, gap;

  unsigned int last;

  int ouvert, vide;

  SDL_Rect sprite_courant;

  int son;

  //INSERT HERE CONTENU POTENTIEL
}coffre_t;

/**
*\struct salle_t
*\brief Représente une salle et ses liaisons aux autres salles
*/
typedef struct salle_s{

  int salle[TAILLE_SALLE][TAILLE_SALLE];

  int s_b, s_h, s_g, s_d;

  SDL_Rect murs[TAILLE_SALLE*TAILLE_SALLE];
  SDL_Rect portes[TAILLE_SALLE];

  coffre_t coffre_salle;

  int nb_murs, nb_portes, id, salle_existe, prems;

  int ennemi_present, nb_ennemi, boss, coffre, pv1, pv2, depart, decouverte;

  ennemi_t *ennemi, *ennemi2;

}salle_t;


/**
*\struct mini_map_t
*\brief Structure de la mini map
*/
typedef struct mini_map_s{

  int taille;

  SDL_Rect map[TAILLE_LABY * TAILLE_LABY];

  int salles_decouvertes[TAILLE_LABY * TAILLE_LABY];
}mini_map_t;


/**
*\struct perso_t
*\Permet de définir un personnage
*/
typedef struct perso_s {
  int pv;/**Point de vie d'un personnage*/
  int pv_old;
  int x;/**Placement sur l'axe des abscisses d'un personnage*/
  int y;/**Placement sur l'axe des ordonnés d'un personnage*/
  int etage;
  int fuite;
  int etage_old;
  image_t sprites[NB_SPRITES_PERSONNAGE];
  int cmpMort;
  int pv_max;

} perso_t;

/**
\struct carte_t
\brief Représente une carte
*/

typedef struct carte_s {
  char * nom ;/** Nom d'une carte */
  type_carte type;/** Type d'une carte */
  int valeur;/** Valeur d'une carte */
  int consommable;/** 1 si la carte est à usage unique*/
  char path[50];
} carte_t ;

// Definition du type d'un element de liste
typedef struct element {
  carte_t * carte;
  struct element* pred;
  struct element* succ;
} element_t;


typedef struct hud_combat_s{

  image_t pv, nom, texte;

  int existe, defausse, cartes[NB_CARTES_COMBAT];
}hud_combat_t;


typedef struct loot_carte_s{

  carte_t *carte;

  image_t image;

  unsigned int debut;

  int delai, existe;

  image_t texte;

}loot_carte_t;


// Declaration des listes (drapeau et element courant)
element_t* drapeau;
element_t* drapeau_collec;
element_t* drapeau_deck;
element_t* ec;
element_t* ec_collec;
element_t* ec_deck;
