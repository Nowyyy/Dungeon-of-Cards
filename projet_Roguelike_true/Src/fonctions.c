/**
*\file fonctions.c
*\brief fichier qui permet de référencé tous les fonctions du système de combat.
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 13/02/2020
*/


#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
// Mise en oeuvre dynamique d'une liste de cartes


// Primitives de manipulation de la liste


/**
*\fn void init_liste()
*\brief Fonction d'initialiser une liste
*/
void init_liste(){
	drapeau = malloc(sizeof(element_t));
	drapeau->pred = drapeau;
	drapeau->succ = drapeau;
	ec = drapeau;
}

/**
*\fn int liste_vide()
*\brief Fonction qui permet de vérifier si une liste est vide
*\return 1 si la liste est vide, 0 si la liste est pas vide
*/
int liste_vide(){
	return drapeau->pred==drapeau;
}
/**
*\fn int hors_liste()
*\brief Fonction qui permet de vérifier si on est pas hors liste
*\return 1 si on est dans la liste, 0 si on est hors liste
*/
int hors_liste(){
	return ec==drapeau;
}

/**
*\fn void en_tete()
*\brief Fonction qui permet de se mettre au début de la liste
*/
void en_tete(){
	if (!liste_vide())
		ec = drapeau->succ;
}

/**
*\fn void en_queue()
*\brief Fonction qui permet de se mettre en fin de la liste
*/
void en_queue(){
	if (!liste_vide())
		ec = drapeau->pred;
}

/**
*\fn void precedent()
*\brief Fonction qui permet de reculer dans la liste
*/
void precedent(){
	if (!hors_liste())
		ec = ec->pred;
  else
    ec = ec->pred;
}

/**
*\fn void suivant()
*\brief Fonction qui permet d'avancer dans la liste
*/
void suivant(){
	if (!hors_liste())
		ec = ec->succ;
  else
    ec = ec->succ;
}
/**
*\fn void valeur_elt(carte_t * t)
*\brief Fonction qui permet de prendre une valeur de la liste
*\param t un pointeur qui permet de prendre une valeur dans la liste
*/
void valeur_elt(carte_t ** t){
	if (!hors_liste())
		*t = ec->carte;
}

/**
*\fn void modif_elt(carte_t t)
*\brief Fonction qui permet de modifier une valeur dans une liste
*\param t une variable qui permet de modifier une valeur dans la liste
*/
void modif_elt(carte_t t){
	if (!hors_liste())
		*ec->carte = t;
}

/**
*\fn void oter_elt(carte_t t)
*\brief Fonction qui permet de supprimer une valeur de la liste
*\param t une variable qui va être supprimer de la liste
*/
void oter_elt(){
	element_t * temp;

	if (!hors_liste()){
		(ec->succ)->pred = ec->pred;
		(ec->pred)->succ = ec->succ;
		temp = ec;
		ec = ec->pred;
		free(temp);
		}
}

/**
*\fn void ajout_droit(carte_t * t)
*\brief Fonction qui permet d'ajouter un objet après l'objet sur lequel l'utilisteur se trouve
*\param t un pointeur qui va contenir une valeur qui va être rajouté
*/
void ajout_droit(carte_t * t){
	element_t* nouv;

	if (liste_vide() || !hors_liste()){
		nouv = malloc(sizeof(element_t));
		nouv->carte = t;
		nouv->pred = ec;
		nouv->succ = ec->succ;
		(ec->succ)->pred = nouv;
		ec->succ = nouv;
		ec = nouv;
	}
}

/**
*\fn void ajout_gauche(carte_t * t)
*\brief Fonction qui permet d'ajouter un objet avant l'objet sur lequel l'utilisteur se trouve
*\param t un pointeur qui va contenir une valeur qui va être rajouté
*/
void ajout_gauche(carte_t * t){
	element_t* nouv;

	if (liste_vide() || !hors_liste()){
		nouv = malloc(sizeof(element_t));
		nouv->carte = t;
		nouv->succ = ec;
		nouv->pred = ec->pred;
		(ec->pred)->succ = nouv;
		ec->pred = nouv;
		ec = nouv;
	}
}

/**
*\fn carte_t * creer_carte(char * nom, type_carte type, int * cible, int valeur)
*\brief permet de créer une carte selon différentes caractéristiques donnés
*\param nom pour le nom de la carte
*\param type pour le type de la carte
*\param cible pour la cible de la carte
*\param valeur pour la valeur de la force de la carte
*\return un pointeur sur une variable structure carte_t
*/
carte_t * creer_carte(char * nom, type_carte type, int valeur, int consommable, char *path)
{
  carte_t * carte = NULL ;
  static unsigned long int cpt = 0 ;
  
  carte = malloc(sizeof(carte_t));

  carte->nom = malloc(sizeof(char)*TAILLE);
  strcpy(carte->path, path);
  strcpy(carte->nom , nom);
  carte->valeur = valeur;
  carte->cible = NULL;
  carte->type = type;
  carte->consommable = consommable;
  return(carte);
}


/**
*\fn void init_ennemi_valeurs(ennemi_t *ennemi, char * nom, int w, int h, int nb_sprites, int gap, float w2, float h2, char * path, SDL_Renderer * rendu)

*\param *ennemi, l'ennemi pour lequel on remplit sa structure
*\param *nom, le nom du monstre
*\param w, la taille d'un sprite en largeur
*\param h, la taille d'un sprite en hauteur
*\param nb_sprites, le nombre de sprites par lignes
*\param gap, l'espace entre deux sprites sur l'image globale
*\param w2, la taille en largeur que l'on veut pour le sprite
*\param h2, la taille en hauteur que l'on veut pour le sprite
*\param *path, le chemin vers l'image de l'ennemi
*\param *rendu, le renderer sur lequel on dessine

*\brief donne aux ennemis les valeurs qui les caractèristiques pour leurs sprites
*/
void init_ennemi_valeurs(ennemi_t *ennemi, char * nom, int w, int h, int nb_sprites, int gap, float w2, float h2, char * path, SDL_Renderer * rendu){

  charge_image(path, &ennemi->sprites, rendu);
  ennemi->w = ennemi->sprites.rectangle.w;
  ennemi->h = ennemi->sprites.rectangle.h; 
  ennemi->sprite_courant.h = h;
  ennemi->sprite_courant.w = w;//on prend le idle comme base
  ennemi->nb_sprites_idle = nb_sprites;
  ennemi->gap = gap;
  ennemi->sprites.rectangle.w = ennemi->sprite_courant.w * w2;
  ennemi->sprites.rectangle.h = ennemi->sprite_courant.h * h2;

  strcpy(ennemi->nom, nom);
}

/**
*\fn ennemi_t * creer_ennemi(char * nom)
*\brief permet de créer un ennemi selon plusieurs caractéristiques
*\param nom pour le nom d'un ennemi
*\return un pointeur sur une variable structure ennemi_t
*/
ennemi_t * creer_ennemi(int pv, int vitesse, int attaque, int defense, int type, SDL_Renderer *rendu)
{
  ennemi_t * ennemi = NULL ;
  static unsigned long int cpt = 0 ;

  ennemi = malloc(sizeof(ennemi_t));

  ennemi->nom = malloc(sizeof(char)*TAILLE);

  ennemi->pv = pv;
  ennemi->vitesse = vitesse;
  ennemi->attaque = attaque;
  ennemi->defense = defense;
  ennemi->boss = 0;

  ennemi->sprite_courant.x = 0;
  ennemi->sprite_courant.y = 0;

  ennemi->anim_courante = idle_droite_ennemi;
  ennemi->id_col = 0;

  if(type == squelette){

    init_ennemi_valeurs(ennemi, "Squelette", 46, 60, 11, 0, 1.10, 1.10, SQUELETTE_PATH, rendu);
  }
  else if(type == blob){

    init_ennemi_valeurs(ennemi, "Blob", 76, 80, 6, 88, 0.8, 0.8, BLOB_PATH, rendu);
  }
  else if(type == imp){

    init_ennemi_valeurs(ennemi, "Imp", 35, 30, 7, 25, 1.5, 1.5, IMP_PATH, rendu);    
  }
  else if(type == minotaure){

    init_ennemi_valeurs(ennemi, "Minotaure", 70, 100, 6, 88, 1, 1, MINOTAURE_PATH, rendu);  
  }
  else if(type == cyclope){
    
    init_ennemi_valeurs(ennemi, "Cyclope", 80, 100, 6, 66, 1, 1, CYCLOPE_PATH, rendu);
  }
  else if(type == wizard){

    init_ennemi_valeurs(ennemi, "Sorcier", 26, 46, 10, 35, 1.8, 1.8, WIZARD_PATH, rendu);
  }

  if(type == minotaure || type == wizard || type == cyclope){
    ennemi->boss = 1;
    ennemi->sprites.rectangle.x = WIN_WIDTH / 2 - ennemi->sprites.rectangle.w / 2;
    ennemi->sprites.rectangle.y = WIN_HEIGHT / 2 - ennemi->sprites.rectangle.h / 2;
  }

  return(ennemi);
}
/*
ennemi_t * generer_ennemi(int niveau){
  return ennemis_niveau1[0];
}*/
/**
*\fn void detruire_carte(carte_t ** carte)
*\brief Fonction qui permet de détruire une carte
*\param carte Un pointeur de pointeur de carte qui permet de détruire le pointeur qui pointe sur la structure carte
*/
void detruire_carte(carte_t ** carte)
{
  free((*carte)->nom);
  free(*carte);
  *carte = NULL;
}


/**
*\fn void detruire_ennemi(ennemi_t ** ennemi)
*\brief Fonction qui permet de détruire un ennemi
*\param perso Un pointeur de pointeur de ennemi qui permet de détruire le pointeur qui pointe sur la structure ennemi
*/
void detruire_ennemi(ennemi_t ** ennemi)
{
  free((*ennemi)->nom);
  SDL_DestroyTexture((*ennemi)->sprites.img);
  free(*ennemi);
  *ennemi = NULL;
}


/**
*\fn void tire_carte_deck(carte_t *cartes[])

*\param *cartes[], tableau de pointeurs sur carte_t, contiendra les cartes utilisées pendant le combat

*\brief tire des cartes au hasard dans le deck du joueur afin qu'il puisse les utiliser au combat
*/
void tire_carte_deck(carte_t *cartes[]){

  int nb = NB_CARTES_COMBAT;
  int alea;
  en_tete();

  while(nb != 0){

    alea = rand()%NB_CARTES;

    for(int i = 0; i < alea; i++)
      suivant();
    if(hors_liste())
      suivant();
    valeur_elt(&cartes[nb - 1]);
    nb--;
  }
}