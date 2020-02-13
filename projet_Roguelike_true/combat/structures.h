/**
* \file structures.h
* \author {Jourry Axel, Tudoret Aurélien, Marin Timothée, Malabry Thomas}
* \date 13/02/2020
* \version 0.1
* \brief Différentes structures qui correspond à la partie du combat
*/
#include <stdlib.h>

#define TAILLE 20
#define TAILLE_DECK 5
/**
*/
typedef enum {ATTAQUE = -1, DEFENSE = 1} type_carte ;

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
} perso_t

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
} ennemi_t

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
