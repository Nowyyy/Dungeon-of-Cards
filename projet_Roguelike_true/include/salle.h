void init_salle(int salle[TAILLE_SALLE][TAILLE_SALLE]);
void ajout_porte_salle(int salle[TAILLE_SALLE][TAILLE_SALLE], int direction);
void afficher_salle(salle_t *salle, SDL_Renderer *rendu, image_t texture[]);
void rempli_tableau_murs_portes(salle_t salle[], int indiceT);
int inverse_porte(int porte);
void textures_aleatoires(salle_t salles[], int taille);
void place_monstre_coffre_boss(salle_t salles[], int taille);