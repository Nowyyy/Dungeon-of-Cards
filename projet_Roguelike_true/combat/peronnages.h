typedef struct perso_s {
  int pv;
  int vitesse;
  int attaque;
  int defense;
  int x;
  int y;
} perso_t

typedef struct ennemi_s {
  int pv;
  int vitesse;
  int attaque;
  int defense;
  char* nom;
} ennemi_t
