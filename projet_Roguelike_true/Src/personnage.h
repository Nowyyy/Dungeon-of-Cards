void charge_sprites_personnage(image_t sprites[], SDL_Renderer *rendu);
void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer);
int test_collision(salle_t salle, perso_t pers, int direction);
salle_t *changement_de_salle(perso_t *pers, salle_t *salle);