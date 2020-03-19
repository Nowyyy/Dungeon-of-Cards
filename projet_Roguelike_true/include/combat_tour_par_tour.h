void affichage_combat_personnage(SDL_Renderer *rendu,perso_t *pers, ennemi_t * ennemi,SDL_Texture *defausse_texture ,SDL_Texture *fuir_texture,SDL_Rect defausse_rect ,SDL_Rect fuir_rect,SDL_Rect *rect_sel,image_t images);
int deplacement_rectangle_selection_combat(SDL_Rect defausse, SDL_Rect fuir,SDL_Rect carte1,SDL_Rect carte2,SDL_Rect carte3,SDL_Rect carte4, SDL_Rect **rect_sel);
int combat_t_p_t(perso_t * perso, ennemi_t * ennemi,SDL_Renderer *rendu);
