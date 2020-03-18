void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi,SDL_Texture *defausse_texture ,SDL_Texture *fuir_texture,SDL_Rect defausse_rect ,SDL_Rect fuir_rect,SDL_Rect *rect_sel);
int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir, SDL_Rect **rect_sel);
int combat_t_p_t(perso_t * perso, ennemi_t * ennemi,SDL_Renderer *rendu);
