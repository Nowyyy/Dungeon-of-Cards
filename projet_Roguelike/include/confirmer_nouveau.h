void afficher_confirmation(SDL_Renderer *rendu, SDL_Rect rect_sel, SDL_Texture *confirmer_texture, SDL_Rect confirmer_rect, SDL_Texture *retour_texture, SDL_Rect retour_rect, SDL_Texture *message_texture, SDL_Rect message_rect);
int deplacement_rectangle_selection_confirmer(int *etat, SDL_Rect confirmer_rect, SDL_Rect retour_rect, SDL_Rect **rect_sel, Mix_Chunk *sounds[NB_SON], perso_t *pers);
void menu_confirmation(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police, Mix_Chunk *sounds[NB_SON], perso_t *pers);
