void init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE]);
void ajout_porte_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], int direction);
void aleatoire_porte(salle_t *salle, int porte_arrivee);
int afficher_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], SDL_Renderer *rendu, t_image texture[], SDL_Rect murs[]);
