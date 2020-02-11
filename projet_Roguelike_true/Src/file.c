/** 
* \file file.c
* \author Tudoret Aurélien
* \date 8/02/2020
* \version 0.1

* \brief contient les appels a la pile et a la file pour la création de labyrinthe aléatoire

*/

#include "constantes.h"

#define MAX 1000

int tete, queue;
salle_t *salles_a_creer[MAX];


/**
* \fn init_file()

* \brief Initialise la file

*/
void init_file(){
	tete = 0;
	queue = 0;
}


/**
* \fn file_vide()

* \return retourne un si la file est vide, 0 sinon

*/
int file_vide(){
	return (tete == queue);
}


/**
* \fn ajoute_file()

* \param salle_t *salle la salle que l'on souhaite ajouter a la file

* \brief ajoute une salle a la file

*/
void ajoute_file(salle_t *salle){

	if(queue < MAX && tete -1 != queue){
		salles_a_creer[queue++] = salle;
	}
	else if(queue == MAX - 1 && tete > 0) {
		queue = 0;
		salles_a_creer[queue] = salle;
	}
}


/**
* \fn retire_file()

* \param salle_t *salle la salle que l'on souhaite retirer de la file

* \brief retire une salle a la file

*/
void retire_file(salle_t **salle){

	if(!file_vide()){
		*salle = salles_a_creer[tete++];
		if(tete == MAX -1 && !file_vide())
			tete = 0;
	}
}