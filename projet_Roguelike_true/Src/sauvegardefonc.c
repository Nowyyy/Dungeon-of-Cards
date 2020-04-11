/**
*\file sauvegardefonc.c
*\brief Fichier qui référence les différentes fonctions de sauvegarde
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 14/02/2020
*/

#include "../include/constantes.h"
#include "../include/fonctions.h"




/**
*\fn int save_existe()

*\return Retourne 1 si une sauvegarde existe, 0 sinon

*\brief Regarde si une sauvegarde existe
*/
int save_existe(){

  FILE *f;

  f = fopen(SAVE_CARTES_COLLEC_PATH, "r");

  if(!f)
    return 0;

  fclose(f);

  return 1;
}

/**
*\fn void savecarte (carte_t* carte2)
*\brief Fonction qui permet de sauvegarde toutes les données d'une carte
*\param carte2 Permet de sauvegarder les cartes d'un deck
*/
void savecarte (char *path, int liste){

  FILE *fichier=NULL;

  carte_t* carte2;

  fichier=fopen(path,"w");
  choix_liste(liste);
  en_tete();

  if (fichier != NULL)
   {
      while(!hors_liste() && !liste_vide()){
        valeur_elt(&carte2);
        fprintf(fichier,"%d %d %d %s %s\n",carte2->type,carte2->valeur,carte2->consommable,carte2->path,carte2->nom);
        suivant();
      }
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier %s", path);
   }
   fclose(fichier);
}

/**
*\fn void readcarte(carte_t* carte2)
*\brief Fonction qui permet de lire une carte
*\param carte2 Permet de lire les cartes d'un deck
*/
void readcarte(char *path_file, int liste){

  FILE *fichier=NULL;

  fichier=fopen(path_file,"r");

  char nom[20], path[100];/** Nom d'une carte */
  type_carte type;/** Type d'une carte */
  int valeur, consommable;

  if (fichier != NULL)
    {
      fscanf(fichier,"%d%d%d%s %[^\n]",&type,&valeur,&consommable,path,nom);

      choix_liste(liste);
      en_tete();

        while(!feof(fichier)){

          ajout_droit(creer_carte(nom,type,valeur,consommable,path));
          fscanf(fichier,"%d%d%d%s %[^\n]",&type,&valeur,&consommable,path,nom);
        }
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s", path_file);
    }
    fclose(fichier);
}



/**
*\fn void saveperso (perso_t *perso)
*\brief Fonction qui permet de sauvegarder les données du personnage
*\param perso Pour savoir les données du perso à sauvegarder
*/
void saveperso (perso_t *perso){

  FILE *fichier=NULL;

  char *nom_fichier = malloc(sizeof(char)* 100);

  strcpy(nom_fichier, SAVE_PERSO_PATH);

  fichier=fopen(nom_fichier,"w+");

  if (fichier != NULL)
   {
       fprintf(fichier,"%d %d %d %d %d %d\n",perso->pv,perso->x,perso->y, perso->etage, perso->cmpMort, perso->pv_max);
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier personnage.txt");
   }
   fclose(fichier);
   if(nom_fichier != NULL){
     free(nom_fichier);
     nom_fichier=NULL;
   }
}



/**
*\fn void readperso(perso_t*perso)
*\brief Fonction qui permet de lire les données du personnage
*\param perso Pour savoir les données du perso à sauvegarder
*/
void readperso(perso_t*perso){

  FILE *fichier=NULL;

  char *nom_fichier = malloc(sizeof(char)* 100);

  strcpy(nom_fichier, SAVE_PERSO_PATH);

  fichier=fopen(nom_fichier,"r");

  if (fichier != NULL)
   {
       fscanf(fichier,"%d %d %d %d %d %d\n",&perso->pv,&perso->x,&perso->y,&perso->etage, &perso->cmpMort, &perso->pv_max);
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier personnage.txt");
   }
   fclose(fichier);
   if(nom_fichier != NULL){
     free(nom_fichier);
     nom_fichier=NULL;
   }
}
