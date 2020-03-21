/**
*\file fonctions.h
*\brief fichier qui permet de référencer tous les prototypes de fonction du système de combat.
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 13/02/2020
*/


/**
*\fn carte_t * creer_carte(char *, type_carte, int *, int)
*\brief permet de créer une carte selon différentes caractéristiques donnés
*\param nom pour le nom de la carte
*\param type pour le type de la carte
*\param cible pour la cible de la carte
*\param valeur pour la valeur de la force de la carte
*/
carte_t * creer_carte(char *, type_carte, int, int, char *);

void init_ennemi_valeurs(ennemi_t *ennemi, char * nom, int w, int h, int nb_sprites, int gap, float w2, float h2, char * path, SDL_Renderer * rendu);


/**
*\fn ennemi_t * creer_ennemi(char *)
*\brief permet de créer un ennemi selon plusieurs caractéristiques
*\param nom pour le nom d'un ennemi
*\return un pointeur sur une variable structure ennemi_t
*/
ennemi_t * creer_ennemi( int, int, int, int, int, SDL_Renderer *);

ennemi_t * generer_ennemi(int);

/**
*\fn void detruire_carte(carte_t **)
*\brief Fonction qui permet de détruire une carte
*\param carte Un pointeur de pointeur de carte qui permet de détruire le pointeur qui pointe sur la structure carte
*/
void detruire_carte(carte_t **);

/**
*\fn void detruire_ennemi(ennemi_t **)
*\brief Fonction qui permet de détruire un ennemi
*\param perso Un pointeur de pointeur de ennemi qui permet de détruire le pointeur qui pointe sur la structure ennemi
*/
void detruire_ennemi(ennemi_t **);

void init_liste();
int liste_vide();
int hors_liste();
void en_tete();
void en_queue();
void precedent();
void suivant();
void valeur_elt(carte_t**);
void modif_elt(carte_t);
void oter_elt();
void ajout_droit(carte_t*);
void ajout_gauche(carte_t*);

void tire_carte_deck(carte_t *cartes[]);