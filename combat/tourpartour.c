#include "stdlib.h"
#include "stdio.h"
#include "time.h"

typedef struct perso_s{
  int pv;
  int attaque;
  int defense;
  int vitesse;
}perso_t;

/*Fonction qui renvoie 1 si le personnage peut fuir ou peut attaque en premier, 0 si il ne peut pas fuir et qu'il combat en deuxième*/
int fuir_ou_combattre (int vit_ennemi,int vit_perso){
  if(vit_perso>vit_ennemi){
    return 1;
  }
  else if(vit_ennemi>vit_perso){
    return 0;
  }
  else if(vit_ennemi==vit_perso){
    return rand()%2;
  }
}
/*Tour d'un ennemi */
void tour_ennemi(perso_t *ennemi,perso_t *perso){
  int i;
  if(ennemi->pv>perso->attaque){
        printf("Ennemi attaque \n");
        perso->pv-=10;
      }
  else if (ennemi->pv<perso->attaque){
        printf("Ennemi se soigne \n");
        ennemi->pv+=10;
      }
  else{
    printf("Ennemi tacle \n");
    perso->vitesse-=5;
  }
}

/*Tour d'un perso*/
int tour_perso(int carte,perso_t *ennemi,perso_t *perso){
  if(carte==1){
    printf("Perso attaque \n");
    ennemi->pv-=10;
  }
  else if(carte==2){
    printf("Perso se soigne \n");
    perso->pv+=15;
  }
  else if(carte==3){
    perso->defense+=5;
  }
  else if(carte==4){
    perso->vitesse+=5;
  }
}
/*Combat tour par tour*/
void tourpartour(perso_t *ennemi,perso_t *perso){
  int carte;
  while(ennemi->pv>0||perso->pv>0){
    printf("Vous avez %d pv et l'ennemi a %d pv\n",perso->pv,ennemi->pv);
    printf("Vous avez %d de vitesse et l'ennemi a %d de vitesse\n",perso->vitesse,ennemi->vitesse);
    printf("Veuillez choisir une carte [1,2] attaque et 3 defense et 4 vitesse \n");
    scanf("%d",&carte);
    if(fuir_ou_combattre(ennemi->vitesse,perso->vitesse)==0){
      tour_ennemi(ennemi,perso);
      tour_perso(carte,ennemi,perso);
    }
    else if(fuir_ou_combattre(ennemi->vitesse,perso->vitesse)==1){
      tour_perso(carte,ennemi,perso);
      tour_ennemi(ennemi,perso);
    }
  }
}


int main(){
  perso_t *ennemi;
  perso_t *perso;
  perso->pv=50;
  ennemi->pv=50;
  ennemi->vitesse=10;
  perso->vitesse=15;
  perso->attaque=0;
  perso->defense=0;
  tourpartour(ennemi,perso);

  if(ennemi->pv<=0){
    printf("Vous avez gagné\n");
    printf("%d %d \n",perso->attaque,perso->defense);
  }
  else if(perso->pv<=0){
    printf("Vous avez perdu\n");
    printf("%d %d \n",perso->attaque,perso->defense);
  }
}
