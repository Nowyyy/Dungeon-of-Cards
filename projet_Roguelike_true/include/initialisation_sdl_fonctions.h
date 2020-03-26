//fonctions de la sdl pour son initialisation, fichier .h


int initialisation_sdl(SDL_Window **window, SDL_Renderer **rendu);
void quit_sdl(SDL_Renderer **rendu, SDL_Window **window);
int init_or_quit_ttf(int action);
extern void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);
int charge_image(char *path_img, image_t *struct_image, SDL_Renderer *rendu);
void init_son(Mix_Chunk* sounds[NB_SON]);
void init_music(Mix_Music* musics[NB_MUSIC]);
void free_mixer(Mix_Music* musics[NB_MUSIC], Mix_Chunk* sounds[NB_SON]);
void choix_musique(Mix_Music* musics[NB_MUSIC], perso_t *pers);
void libere_texture(SDL_Texture **texture);