/**
 * \file labyrinthe.c
 * \brief Programme qui créé une salle et l'affiche.
 * \author Axel Jourry
 * \version 1.0
 * \date 30 Janvier 2020
 */


#include <stdio.h>
#include <stdlib.h>

#define TAILLE_LABY 23


/**
 * \fn init_salle(int salle[TAILLE_LABY][TAILLE_LABY])
 * \brief fonction qui génère une salle en un tableau
 * \param salle[TAILLE_LABY][TAILLE_LABY] est le tableau de TAILLE_LABY qui comprend la salle
 */

void init_salle(int salle[TAILLE_LABY][TAILLE_LABY]){

  for(int i = 0; i<TAILLE_LABY; i++){
    for(int j=0; j<TAILLE_LABY; j++){

      if(j == 0){
        salle[i][j]=1;
      }
      else if(i == 0){
        salle[i][j]=1;
      }
      else if(i == TAILLE_LABY-1){
        salle[i][j]=1;
      }
      else if(j == TAILLE_LABY-1){
        salle[i][j]=1;
      }
      else{
        salle[i][j]=0;

      }

    }
  }
}

void ajout_porte_salle(int salle[TAILLE_LABY][TAILLE_LABY]){
  int millieu = TAILLE_LABY / 2;
  for(int i = 0; i<TAILLE_LABY; i++){
    for(int j=0; j<TAILLE_LABY; j++){
      if(i == 0){
        if(j == millieu-1 || j == millieu || j== millieu+1){
          salle[i][j]=2;
        }
      }
      else if(j == 0){
        if(i == millieu-1 || i == millieu || i== millieu+1){
          salle[i][j]=2;
        }
      }
      else if(j == TAILLE_LABY-1){
        if(i == millieu-1 || i == millieu || i== millieu+1){
          salle[i][j]=2;
        }
      }
      if(i == TAILLE_LABY-1){
        if(j == millieu-1 || j == millieu || j== millieu+1){
          salle[i][j]=2;
        }
      }
    }
  }
}

/**
 * \fn afficher_salle(int salle[TAILLE_LABY][TAILLE_LABY])
 * \brief fonction qui génère une salle en un tableau
 * \param salle[TAILLE_LABY][TAILLE_LABY] est le tableau de TAILLE_LABY qui comprend la salle
 */
void afficher_salle(int salle[TAILLE_LABY][TAILLE_LABY]){
  for(int i = 0; i<TAILLE_LABY; i++){
    for(int j=0; j<TAILLE_LABY; j++){
      if(salle[i][j]==0){
        printf("  ");
      }
      else{
      printf("%d ", salle[i][j]);
      }
    }
    printf("\n");
  }
}

int main(){
  int salle[TAILLE_LABY][TAILLE_LABY];

init_salle(salle);
ajout_porte_salle(salle);

afficher_salle(salle);
}
