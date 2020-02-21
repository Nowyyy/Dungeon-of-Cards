void charge_sprites_personnage(image_t sprites[], SDL_Renderer *rendu);
void init_animations(animation_t *anim);
void animations_personnage(image_t sprites[], unsigned int timer, touches_t clavier, animation_t *anim);
void deplacement_personnage(perso_t *pers, salle_t salle, int *continuer, animation_t *anim);
int test_collision(salle_t salle, perso_t pers, int direction);
int changement_de_salle(perso_t *pers, salle_t salle, int indice, Mix_Chunk *change_salle);