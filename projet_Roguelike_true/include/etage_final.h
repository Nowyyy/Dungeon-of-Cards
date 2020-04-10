void charge_textures_etage_final(image_t images[], perso_t *pers, SDL_Renderer *rendu);
void affichage_salle_personnage_etage_final(perso_t pers, salle_t *salle, SDL_Renderer *rendu, image_t images[]);
void etage_final(SDL_Renderer *rendu, int *continuer, int *etat, Mix_Chunk *sounds[NB_SON], Mix_Music *musics[NB_MUSIC], perso_t *pers, TTF_Font *police);
void creation_salles_dernier_etage(salle_t salles[], int taille, SDL_Renderer *rendu);