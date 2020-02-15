void charge_toutes_textures(image_t images[], perso_t *pers, SDL_Renderer *rendu);
void affichage_salle_personnage(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[]);
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu);
int generation_labyrinthe(salle_t salles[], int taille, int max_salles, int taille_max);
void cree_liaison(salle_t tab[], int salle1, int salle2, int porteS1);
int cherche_porte_libre(salle_t salles[], int indice, int taille, int position);
int porte_non_connectee(salle_t salle);
void initialise_salles(salle_t tab[], int taille);
