void charge_toutes_textures(t_image images[], t_perso *pers, SDL_Renderer *rendu);
void affichage_salle_personnage(t_perso pers, salle_t *salle, SDL_Renderer *rendu, t_image images[]);
void boucle_labyrinthe(int *continuer, int *etat, SDL_Renderer *rendu);
void generation_laby_alea(int nb_salle);
void creer_premiere_salle(salle_t *salle, int nb_salles_a_creer);
void detruire_salles(salle_t *salle);