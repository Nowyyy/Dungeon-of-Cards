/**
*\file fonctions.c
*\brief Fichier référençant toutes les fonctions du système de combat.
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 13/02/2020
*/


#include "../include/constantes.h"
#include "../include/initialisation_sdl_fonctions.h"
#include "../include/fonctions.h"

// Tables de cartes préfaites
char communes[][TAILLE] = {{"soin"},{"poing"},{"pierre"}};
char peu_communes[][TAILLE] = {{"potion"},{"barriere"},{"epee"}};
char rares[][TAILLE] = {{"boule de feu"},{"poison"},{"guerison"}};

/**
*\fn void detruire_carte(carte_t ** carte)
*\brief Fonction qui permet de détruire une carte
*\param carte Un pointeur de pointeur de carte. On détruit libère la zone mémoire située à l'adresse pointée.
*/
void detruire_carte(carte_t ** carte)
{
  if(*carte != NULL){
    if((*carte)->nom != NULL){
      free((*carte)->nom);
      (*carte)->nom = NULL;
    }

    if(*carte != NULL){
      free(*carte);
      *carte = NULL;
    } 
  }
}


/**
*\fn void ajout_carte_collec(carte_t *carte)

*\param carte, la carte pour laquelle on cherche à savoir si elle existe dans la collection du joueur

*\brief ajoute une carte à la collection du joueur s'il ne la possède pas déjà, ou s'il n'en possède aucune
*/
void ajout_carte_collec(carte_t *carte){

  choix_liste(COLLEC);

  carte_t *tmp;

  if(!liste_vide()){
    for(en_tete();!hors_liste() && strcmp(carte->path, ec->carte->path);suivant()){

    }
    if(hors_liste()){
      //carte non possèdée
      tmp = creer_carte(carte->nom, carte->type,  carte->valeur, carte->consommable, carte->path);
      en_queue();
      ajout_droit(tmp);
    }
  }
  else{
      tmp = creer_carte(carte->nom, carte->type,  carte->valeur, carte->consommable, carte->path);
      ajout_droit(tmp);
  }
}



/**
*\fn void ajout_carte_deck(carte_t *tampon)

*\param carte, la carte à ajouter

*\brief ajoute une carte au deck du joueur
*/
void ajout_carte_deck(carte_t *tampon){

  choix_liste(DECK);
  carte_t *tmp;

  if(!liste_vide()){

    for(en_tete();!hors_liste() && strcmp(tampon->nom, ec->carte->nom);suivant()){
  
    }

    if(!hors_liste() && ec->carte->consommable > 0){
      //carte possédée et a usage limité, on up le nb d'usages restants
      ec->carte->consommable += tampon->consommable;
    }
    else if(hors_liste()){
      //carte non présente dans le deck
      en_queue();
      tmp = creer_carte(tampon->nom, tampon->type,  tampon->valeur, tampon->consommable, tampon->path);
      ajout_droit(tmp);
    }
  }
  else{
    //liste de cartes vide
    tmp = creer_carte(tampon->nom, tampon->type,  tampon->valeur, tampon->consommable, tampon->path);
    ajout_droit(tmp);
  }
}




// Mise en oeuvre dynamique d'une liste de cartes


// Primitives de manipulation de la liste
/**
*\fn void choix_liste()
*\param choix 0 = COLLECTION et 1 = DECK. Les valeurs sont définies dans constantes.h
*\brief Selection entre le deck et la collection
*/
void choix_liste(int choix){
	if(choix){
		drapeau = drapeau_deck;
		ec = drapeau_deck;
	}
	else{
		drapeau = drapeau_collec;
		ec = ec_collec;
	}
}

/**
*\fn void init_liste()
*\brief Fonction initialisant les listes. Par défaut, la liste deck est ensuite sélectionner
*/
void init_liste(){
	drapeau_deck = malloc(sizeof(element_t));
	drapeau_deck->pred = drapeau_deck;
	drapeau_deck->succ = drapeau_deck;
	ec_deck = drapeau_deck;

	drapeau_collec = malloc(sizeof(element_t));
	drapeau_collec->pred = drapeau_collec;
	drapeau_collec->succ = drapeau_collec;
	ec_collec = drapeau_collec;

  choix_liste(DECK);
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
    detruire_carte(&temp->carte);
    if(temp != NULL){
      free(temp);
      temp=NULL;
    }
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
*\brief permet de créer une carte selon différentes caractéristiques données
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
  carte->type = type;
  carte->consommable = consommable;
  return(carte);
}


/**
*\fn void init_ennemi_valeurs(ennemi_t *ennemi, char * nom, int w, int h, int nb_sprites, int gap, float w2, float h2, char * path, SDL_Renderer * rendu)

*\param ennemi, l'ennemi dont on rempli la structure
*\param nom, le nom du monstre
*\param w, la taille du sprite en largeur
*\param h, la taille du sprite en hauteur
*\param nb_sprites, le nombre de sprites par lignes
*\param gap, l'espace entre deux sprites sur l'image globale
*\param w2, la taille en largeur que l'on veut pour le sprite
*\param h2, la taille en hauteur que l'on veut pour le sprite
*\param path, le chemin vers l'image de l'ennemi
*\param rendu, le renderer sur lequel on dessine

*\brief donne à un ennemi les valeurs correspondant à ses sprites
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
  ennemi->pv_old = pv;
  ennemi->pv_max = pv;
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
  else if(type == volant){

    init_ennemi_valeurs(ennemi, "Volant", 76, 58, 4, 85, 0.8, 0.8, VOLANT_PATH, rendu);
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

    init_ennemi_valeurs(ennemi, "Mage", 26, 48, 10, 35, 1.8, 1.8, WIZARD_PATH, rendu);
  }
  else if(type == sorcerer){

    init_ennemi_valeurs(ennemi, "Sorcier", 40, 84, 7, 58, 1.5, 1.5, SORCERER_PATH, rendu);
  }

  if(type == minotaure || type == wizard || type == cyclope || type == sorcerer){
    ennemi->boss = 1;
    ennemi->sprites.rectangle.x = WIN_WIDTH / 2 - ennemi->sprites.rectangle.w / 2;
    ennemi->sprites.rectangle.y = WIN_HEIGHT / 2 - ennemi->sprites.rectangle.h / 2;
  }

  return(ennemi);
}

/**


DOCUMENTATION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


*/
carte_t * generer_carte(int niveau){
	int r, i, puissance;
	char puissances[3][4] = {{" I"},{" II"},{" X"}};
	char nom[TAILLE];
	switch (niveau) {
		case 1:
			puissance = rand()%2 + 1;
			break;
		case 2:
			puissance = rand()%3 + 1;
			break;
		case 3:
			puissance = rand()%4 + 1;
			break;
		case 4:
			puissance = (rand()%5) + 1;
			break;
		case 5:
			puissance = 2;
			break;
	}
	//printf("puissance : %d\n", puissance);
	r = rand()%15;
	//printf("%s\n", puissances[puissance]);
  if (r < 10){
		i = rand()%3;
    switch (i) {
      case 0:
				strcpy(nom, communes[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom, DEFENSE, puissance, -1, CARTE_SOIN_PATH));
        break;
      case 1:
				strcpy(nom, communes[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,ATTAQUE,puissance,-1, CARTE_POING_PATH));
        break;
      case 2:
				strcpy(nom, communes[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,ATTAQUE,puissance,5, CARTE_PIERRE_PATH));
        break;
    }
  }
  else if (r > 9 && r < 14){
    //printf("Peu commune\n");
		i = rand()%3;
    switch (i) {
      case 0:
				strcpy(nom, peu_communes[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,DEFENSE,puissance,3, CARTE_POTION_I_PATH));
        break;
      case 1:
				strcpy(nom, peu_communes[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,DEFENSE,puissance,-1, CARTE_BARRIERE_PATH));
        break;
      case 2:
				strcpy(nom, peu_communes[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,ATTAQUE,puissance,-1, CARTE_EPEE_I_PATH));
        break;
    }
  }
  else{
    //printf("Rare\n");
		i = rand()%3;
    switch (i) {
      case 0:
				strcpy(nom, rares[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,ATTAQUE,puissance,-1, CARTE_B_DE_FEU_PATH));
        break;
      case 1:
				strcpy(nom, rares[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,ATTAQUE,puissance,2, CARTE_POISON_PATH));
        break;
      case 2:
				strcpy(nom, rares[i]);
				strncat(nom, puissances[puissance], 3);
        return(creer_carte(nom,DEFENSE,0,puissance, CARTE_GUERISON_PATH));
        break;
    }
  }
}

void afficher_liste(){

  if(liste_vide())
    printf("\nListe vide.\n\n");
  for(en_tete();!hors_liste();suivant())
    printf("Nom : %s, puissance : %d\n", ec->carte->nom, ec->carte->valeur);
  en_queue();
  printf("\n");
}
/**
*\fn void detruire_ennemi(ennemi_t ** ennemi)
*\brief Fonction qui permet de détruire un ennemi
*\param perso Un pointeur de pointeur d'ennemi qui permet de détruire le pointeur qui pointe sur la structure ennemi
*/
void detruire_ennemi(ennemi_t ** ennemi)
{
  if((*ennemi)->nom != NULL){
    free((*ennemi)->nom);
    (*ennemi)->nom=NULL;
  }

  libere_texture(&(*ennemi)->sprites.img);

  if(*ennemi != NULL){
    free(*ennemi);
    *ennemi = NULL;
  }
}


/**
*\fn void tire_carte_deck(carte_t *cartes[], int indice)

*\param *cartes[], tableau de pointeurs sur carte_t, contiendra les cartes utilisées pendant le combat
*\param indice, l'indice du tableau que l'on souhaite remplir

*\brief tire des cartes au hasard dans le deck du joueur afin qu'il puisse les utiliser au combat
*/
void tire_carte_deck(carte_t *cartes[], int indice){

  int alea = rand()%TAILLE_DECK + 1;

  carte_t *tmp;

  choix_liste(DECK);

  if(liste_vide()){

    cartes[indice] = creer_carte("No carte", NO_CARTE, 0, 0, CARTE_NO_CARTE_PATH);
  }
  else{

    en_tete();

    while(alea > 0){
      suivant();

      if(hors_liste())
        suivant();
      alea--;
    }

    valeur_elt(&tmp);

    cartes[indice] = creer_carte(tmp->nom, tmp->type, tmp->valeur, tmp->consommable, tmp->path);

    oter_elt();
  }
}
