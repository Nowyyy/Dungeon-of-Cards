#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/**
*\file sauvegardefonc.c
*\brief Fichier qui référence les différentes fonctions de sauvegarde
*\author {Malabry Thomas Aurélien Tudoret Jourry Axel Marin Timothée}
*\version 1.0
*\date 14/02/2020
*/


/**
*\fn void savecarte (carte_t* deck[])
*\brief Fonction qui permet de sauvegarde toutes les données d'une carte
*\param deck[] Permet de sauvegarder les cartes d'un deck
*/
void savecarte (carte_t* deck[]){
  FILE *fichier=NULL;
  fichier=fopen("sauvegarde.txt","w");
  int i;
  if (fichier != NULL)
   {
       for(i=0;i<5;i++){
         fprintf(fichier,"%d %d %s\n",deck[i]->valeur,deck[i]->type,deck[i]->nom);
       }
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier sauvegarde.txt");
   }
   fclose(fichier);

}
/**
*\fn void readcarte(carte_t* deck2[])
*\brief Fonction qui permet de lire une carte
*\param deck2[] Permet de lire les cartes d'un deck
*/
void readcarte(carte_t* deck2[]){
  FILE *fichier=NULL;
  fichier=fopen("sauvegarde.txt","r");
  int i;
  if (fichier != NULL)
   {
       for(i=0;i<5;i++){
         fscanf(fichier,"%d %d %[^\n]",&deck2[i]->valeur ,&deck2[i]->type,deck2[i]->nom);
       }
   }
   else
   {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier sauvegarde.txt");
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
