/**
*\file sauvegarde
*\brief Permet de faire une sauvegarde d'une carte
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TAILLE 20 //Taille des chaînes de caractères
#define TAILLE_DECK 5

typedef enum {ATTAQUE = -1, DEFENSE = 1}type_carte;

/**
\struct carte_t
\brief Représente une carte
*/

typedef struct carte_s {
  char * nom ;/** Nom d'une carte */
  type_carte type;/** Type d'une carte */
  int valeur;/** Valeur d'une carte */
} carte_t ;

carte_t * creer_carte(char *nom,type_carte type, int valeur)
{
  carte_t * carte = NULL ;

  carte = malloc(sizeof(carte_t));

  carte->nom = malloc(sizeof(char)*TAILLE);
  strcpy(carte->nom , nom);
  carte->valeur = valeur;
  carte->type = type;

  return(carte);
}

void detruire_carte(carte_t ** carte)
{
  free((*carte)->nom);
  free(*carte);
}

int main(){
  /*Initialisation */
  FILE* fichier=NULL;
  int i;
  carte_t * deck[TAILLE_DECK];
  deck[0] = creer_carte("soin", DEFENSE, 10);
  deck[1] = creer_carte("épée", ATTAQUE, 10);
  deck[2] = creer_carte("épée", ATTAQUE, 10);
  deck[3] = creer_carte("épée", ATTAQUE, 10);
  deck[4] = creer_carte("boule de feu", ATTAQUE, 20);
  fichier=fopen("sauvegarde.txt","w");
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
   for(i=0;i<5;i++){
    detruire_carte(&(deck[i]));
  }


  carte_t *deck2[TAILLE_DECK];
  deck2[0] = creer_carte("r", 0, 0);
  deck2[1] = creer_carte("r", 0, 0);
  deck2[2] = creer_carte("r", 0, 0);
  deck2[3] = creer_carte("r", 0, 0);
  deck2[4] = creer_carte("r", 0, 0);
  fichier=fopen("sauvegarde.txt","r");
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
   for(i=0;i<5;i++){
     printf("%s %d %d \n",deck2[i]->nom,deck2[i]->type,deck2[i]->valeur);
   }
   for(i=0;i<5;i++){
    detruire_carte(&(deck2[i]));
  }
}
