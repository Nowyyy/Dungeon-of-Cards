/**
*\file personnage.h
*\brief Fichier qui intègre des structures à part du programme
*\author Malabry Thomas Tudoret Aurélien Marin Timothée Jourry Axel
*\version 1
*\date 13 février 2020
*/


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
