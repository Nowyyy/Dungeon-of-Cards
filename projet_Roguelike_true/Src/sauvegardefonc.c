/**
*\file sauvegardefonc.c
*\brief Fichier qui référence les différentes fonctions de sauvegarde
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 14/02/2020
*/

#include "constantes.h"
#include "fonctions.h"
<<<<<<< HEAD



/**
* \fn save_existe

* \return Retourne 1 si une sauvegarde existe, 0 sinon

* \brief Regarde si une sauvegarde existe
*/
int save_existe(){

  FILE *f;

  f = fopen("sauvegarde.txt", "r");

  if(!f)
    return 0;
  else 
    return 1;
}
=======
>>>>>>> master

/**
*\fn void savecarte (carte_t* carte2)
*\brief Fonction qui permet de sauvegarde toutes les données d'une carte
*\param carte2 Permet de sauvegarder les cartes d'un deck
*/
void savecarte (carte_t* carte2){

  FILE *fichier=NULL;
  fichier=fopen("sauvegarde.txt","w");
  en_tete();

  if (fichier != NULL)
   {
      while(!hors_liste()){
        valeur_elt(carte2);
        fprintf(fichier,"%d %d %d %s\n",carte2->type,carte2->valeur,carte2->consommable,carte2->nom);
        suivant();
      }
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier sauvegarde.txt");
   }
   fclose(fichier);


/**
*\fn void readcarte(carte_t* carte2)
*\brief Fonction qui permet de lire une carte
*\param carte2 Permet de lire les cartes d'un deck
*/
void readcarte(carte_t* carte2){

  FILE *fichier=NULL;
   fichier=fopen("perso1.txt","r");
   en_tete();

   fscanf(fichier,"%d %d %d %[^\n]",&carte2->type,&carte2->valeur,&carte2->consommable,carte2->nom);
   
   if (fichier != NULL)
    {
        while(!feof(fichier)){

          printf("%d %d %d %s\n",carte2->type,carte2->valeur,carte2->consommable,carte2->nom);
          ajout_droit(creer_carte(carte2->nom,carte2->type,carte2->valeur,carte2->consommable));
          fscanf(fichier,"%d %d %d %[^\n]",&carte2->type,&carte2->valeur,&carte2->consommable,carte2->nom);
        }
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }
    fclose(fichier)
}



/**
*\fn void saveperso (perso_t *perso)
*\brief Fonction qui permet de sauvegarder les données du personnage
*\param perso Pour savoir les données du perso à sauvegarder
*/
void saveperso (perso_t *perso){

  FILE *fichier=NULL;
  fichier=fopen("perso.txt","w");

  if (fichier != NULL)
   {
       fprintf(fichier,"%d %d %d %d %d %d\n",perso->pv,perso->vitesse,perso->attaque,perso->defense,perso->x,perso->y);
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier sauvegarde.txt");
   }
   fclose(fichier);
}



/**
*\fn void readperso(perso_t*perso)
*\brief Fonction qui permet de lire les données du personnage
*\param perso Pour savoir les données du perso à sauvegarder
*/
void readperso(perso_t*perso){

  FILE *fichier=NULL;
  fichier=fopen("perso1.txt","r");

  if (fichier != NULL)
   {
       fscanf(fichier,"%d %d %d %d %d %d\n",&perso->pv,&perso->vitesse,&perso->attaque,&perso->defense,&perso->x,&perso->y);
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier sauvegarde.txt");
   }
   fclose(fichier);
}
