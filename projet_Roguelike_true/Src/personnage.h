void charge_sprites_personnage(t_image sprites[], SDL_Renderer *rendu);
void deplacement_personnage(t_perso *pers, salle_t salle, int *continuer);
int test_collision(salle_t salle, t_perso pers, int direction);
