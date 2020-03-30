void animation_coffre(perso_t *pers, salle_t *salle, Mix_Chunk *sounds[NB_SON]);
void creer_coffre(coffre_t *coffre, SDL_Renderer *rendu, salle_t *salle);
void destruction_des_coffres(salle_t salles[], int taille);
void creer_texte_coffre(char *txt, image_t *image, int x, int y, SDL_Renderer *rendu);
void loot_de_carte(loot_carte_t *loot, SDL_Renderer *rendu, coffre_t *coffre, int etage);
void detruire_loot(loot_carte_t **loot);
void afficher_loot(loot_carte_t loot, SDL_Renderer *rendu);
void loot_affichage_fini(loot_carte_t *loot);