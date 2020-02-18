void menu_charger_partie(int *continuer, int *etat, SDL_Renderer *rendu, TTF_Font *police);
int deplacement_rectangle_selection_charger(int *etat, SDL_Rect charger_rect, SDL_Rect retour_rect, SDL_Rect **rect_sel);
void afficher_chagrer_partie(SDL_Renderer *rendu, SDL_Rect rect_sel, SDL_Texture *charger_texture, SDL_Rect charger_rect, SDL_Texture *retour_texture, SDL_Rect retour_rect);