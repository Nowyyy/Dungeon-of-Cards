void init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE]);
void ajout_porte_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], int direction);
int aleatoire_porte(salle_t *salle, int porte_arrivee, int max_porte);
void afficher_salle(salle_t *salle, SDL_Renderer *rendu, image_t texture[]);
void rempli_tableau_murs_portes(salle_t *salle);
