/**
*\file fonctions.c
*\brief fichier qui permet de référencé tous les fonctions du système de combat.
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 13/02/2020
*/


#include "constantes.h"
#include "initialisation_sdl_fonctions.h"

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
}

/**
*\fn void suivant()
*\brief Fonction qui permet d'avancer dans la liste
*/
void suivant(){
	if (!hors_liste())
		ec = ec->succ;
}
/**
*\fn void valeur_elt(carte_t * t)
*\brief Fonction qui permet de prendre une valeur de la liste
*\param t un pointeur qui permet de prendre une valeur dans la liste
*/
void valeur_elt(carte_t * t){
	if (!hors_liste())
		*t = *ec->carte;
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
void oter_elt(carte_t t){
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
carte_t * creer_carte(char * nom, type_carte type, int valeur, int consommable)
{
  carte_t * carte = NULL ;
  static unsigned long int cpt = 0 ;

  carte = malloc(sizeof(carte_t));

  carte->nom = malloc(sizeof(char)*TAILLE);
  strcpy(carte->nom , nom);
  carte->valeur = valeur;
  carte->cible = NULL;
  carte->type = type;
  carte->consommable = consommable;
  return(carte);
}
/**
*\fn perso_t * creer_perso()
*\brief permet de créer un personnage selon différentes caractéristiques
*\return un pointeur sur une variable structure perso_t
*/
perso_t * creer_perso()
{
  perso_t * perso = NULL ;
  static unsigned long int cpt = 0 ;

  perso = malloc(sizeof(perso_t));

  perso->pv = 20;
  perso->vitesse = 10;
  perso->attaque = 10;
  perso->defense = 10;
  perso->x = 0;
  perso->y = 0;
  return(perso);
}
/**
*\fn ennemi_t * creer_ennemi(char * nom)
*\brief permet de créer un ennemi selon plusieurs caractéristiques
*\param nom pour le nom d'un ennemi
*\return un pointeur sur une variable structure ennemi_t
*/
ennemi_t * creer_ennemi(char * nom, int pv, int vitesse, int attaque, int defense, int type, SDL_Renderer *rendu)
{
  ennemi_t * ennemi = NULL ;
  static unsigned long int cpt = 0 ;

  ennemi = malloc(sizeof(ennemi_t));

  ennemi->nom = malloc(sizeof(char)*TAILLE);
  strcpy(ennemi->nom , nom);

  ennemi->pv = pv;
  ennemi->vitesse = vitesse;
  ennemi->attaque = attaque;
  ennemi->defense = defense;

  if(type == squelette){
    charge_image(SQUELETTE_IDLE_PATH, &ennemi->sprites[0], rendu);
  }
  else if(type == minautore){
    //do stuff ...
  }
  else if(type == cyclope){
    //do other stuff
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
}


/**
*\fn void detruire_ennemi(ennemi_t ** ennemi)
*\brief Fonction qui permet de détruire un ennemi
*\param perso Un pointeur de pointeur de ennemi qui permet de détruire le pointeur qui pointe sur la structure ennemi
*/
void detruire_ennemi(ennemi_t ** ennemi)
{
  free((*ennemi)->nom);
  SDL_DestroyTexture((*ennemi)->sprites[0].img);
  free(*ennemi);
}

/**
*\fn int initiative (perso_t * perso,ennemi_t * ennemi)
*\brief Fonction qui permet savoir si c'est l'ennemi ou le personnage qui combat en premier
*\param perso Un pointeur sur la structure perso_t qui permet de prendre la vitesse pour la comparé à l'ennemi
*\param perso Un pointeur sur la structure ennemi_t qui permet de prendre la vitesse pour la comparé au personnage
*/
int initiative (perso_t * perso,ennemi_t * ennemi)
{
  if(perso->vitesse>ennemi->vitesse){
    return 1;
  }
  else if(ennemi->vitesse>perso->vitesse){
    return 0;
  }
  else if(ennemi->vitesse==perso->vitesse){
    return rand()%2;
  }
}

/**
*\fn void tour_ennemi(perso_t * perso,ennemi_t * ennemi)
*\brief Fonction qui permet à l'ennemi d'effectuer une action
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action de l'ennemi
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action de l'ennemi
*/
void tour_ennemi(perso_t * perso,ennemi_t * ennemi)
{
  int i;
  if(ennemi->pv > perso->attaque){
        printf("Le %s attaque \n", ennemi->nom);
        perso->pv += ennemi->attaque;
      }
  else if (ennemi->pv < perso->attaque){
        printf("Le %s se soigne \n", ennemi->nom);
        ennemi->pv += 5;
      }
  else{
    printf("Le %s tacle \n", ennemi->nom);
    perso->vitesse += -1;
  }
}

/**
*\fn int tour_perso(int choix,perso_t *perso,ennemi_t * ennemi, carte_t ** deck)
*\brief Fonction qui permet au personnage d'effectuer une action
*\param choix Entier qui va permettre au personnage un choix selon les instructions de l'utilisateur
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\param deck Pointeur sur un pointeur de fonction qui permet de connaître le deck du personnage
*/
int tour_perso(int choix,perso_t * perso,ennemi_t * ennemi)
{
  en_tete();
  choix--;
  int i;
  for(i=0;i<choix && !hors_liste();i++,suivant());
  printf("Vous avez choisi %s\n", ec->carte->nom);
  *(ec->carte->cible) += ec->carte->valeur * ec->carte->type;

}

/**
*\fn void combat(perso_t * perso, ennemi_t * ennemi, carte_t ** deck)
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques du personnage qui vont être modifié par l'action du personnage
*\param perso Pointeur sur une structure qui permet de prendre les caractéristiques de l'ennemi qui vont être modifié par l'action du personnage
*\*\param deck Pointeur sur un pointeur de fonction qui permet de connaître le deck du personnage
*/
void combat(perso_t * perso, ennemi_t * ennemi)
{
  int choix, i, vitesse;
  vitesse = perso->vitesse;
  while(ennemi->pv > 0 && perso->pv > 0){
    printf("Vous avez %d pv et le %s a %d pv\n",perso->pv, ennemi->nom, ennemi->pv);
    printf("Vous avez %d de vitesse et le %s a %d de vitesse\n",perso->vitesse,ennemi->nom, ennemi->vitesse);
    for(i=0, en_tete() ; !hors_liste() ; i++, suivant()){
      printf("[%d] : %s\n", i+1, ec->carte->nom);
    }
    scanf("%d",&choix);
    if (initiative(perso, ennemi)){
      tour_perso(choix, perso, ennemi);
      if(ennemi->pv)
        tour_ennemi(perso, ennemi);
    }
    else{
      tour_ennemi(perso, ennemi);
      if(perso->pv)
        tour_perso(choix, perso, ennemi);
    }
  }
  if(!ennemi->pv){
    printf("Vous avez vaincu le %s\n", ennemi->nom);
  }
  else{
    printf("Vous avez été vaincu par le %s\n", ennemi->nom);
  }
  perso->vitesse = vitesse;
}
