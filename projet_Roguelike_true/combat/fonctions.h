carte_t * creer_carte(char *, type_carte, int *, int);

perso_t * creer_perso();

ennemi_t * creer_ennemi(char *);

void detruire_carte(carte_t **);

void detruire_perso(perso_t **);

void detruire_ennemi(ennemi_t **);

int initiative (perso_t *, ennemi_t *);

void tour_ennemi(perso_t *, ennemi_t *);

int tour_perso(int, perso_t *, ennemi_t *, carte_t **);

void combat(perso_t *, ennemi_t *, carte_t **);
