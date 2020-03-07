int indice_salle(int salle_actuelle, int porte_salle_actuelle, int taille);
int tirage_au_sort_porte_a_creer(int indice, int taille, salle_t salles[]);
void creation_labyrinthe(salle_t salles[], int taille, int nb_salles_a_creer);
void charge_toutes_textures(image_t images[], perso_t *pers, SDL_Renderer *rendu);
void affichage_salle_personnage(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[], ennemi_t monstre, ennemi_t boss);
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu, Mix_Chunk *change_salle, Mix_Chunk *footsteps, Mix_Music *gameOverMusic, Mix_Chunk *gameOverFrame, perso_t *pers, carte_t *cartes, TTF_Font *police);
void cree_liaison(salle_t tab[], int salle1, int salle2, int porteS1);
void initialise_salles(salle_t tab[], int taille);
void mort(int *etat, perso_t *pers, SDL_Renderer *rendu, Mix_Music *gameOverMusic, Mix_Chunk *gameOverFrame, image_t images[], TTF_Font *police, SDL_Texture *cmpPartie_texture);
