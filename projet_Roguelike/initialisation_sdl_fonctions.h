//fonctions de la sdl pour son initialisation, fichier .h


int initialisation_sdl(SDL_Window **window, SDL_Renderer **rendu);
void quit_sdl(SDL_Renderer **rendu, SDL_Window **window);
int init_or_quit_ttf(int action);
extern void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect);