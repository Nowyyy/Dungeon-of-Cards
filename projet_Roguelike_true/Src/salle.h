void init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE]);
void ajout_porte_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], int direction);
int aleatoire_porte(salle_t *salle, int porte_arrivee, int max_porte);
int afficher_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], SDL_Renderer *rendu, t_image texture[], SDL_Rect murs[]);
int aleatoire_porte2(salle_t *salle, int porte_arrivee, int max_porte);
