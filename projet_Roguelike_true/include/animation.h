void animation_niveau(perso_t *perso, SDL_Renderer *rendu);
void anim_combat(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]);
void anim1(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]);
void anim2(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]);
void anim3(SDL_Renderer *rendu, Mix_Chunk* sounds[NB_SON]);
void mort(int *etat, perso_t *pers, SDL_Renderer *rendu, Mix_Music *musics[NB_MUSIC], Mix_Chunk *sounds[NB_SON], image_t images[], TTF_Font *police);
void anim_combat_perso(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]);
void anim_combat_perso_attaque(perso_t *pers, carte_t *carte, SDL_Renderer *rendu, Mix_Chunk *sounds[NB_SON]);
