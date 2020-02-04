#include <stdlib.h>

#define TAILLE 20
#define TAILLE_DECK 5

typedef enum {ATTAQUE = -1, DEFENSE = 1} type_carte ;


typedef struct perso_s {
  int pv;
  int vitesse;
  int attaque;
  int defense;
  int x;
  int y;
} perso_t;

typedef struct ennemi_s {
  int pv;
  int vitesse;
  int attaque;
  int defense;
  char* nom;
} ennemi_t;

typedef struct carte_s {
  char * nom ;
  type_carte type;
  int * cible;
  int valeur;
} carte_t ;
