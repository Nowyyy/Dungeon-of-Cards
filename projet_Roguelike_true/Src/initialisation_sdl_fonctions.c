/**
*\file initialisation_sdl_fonctions.c
*\author {Jourry Axel, Tudoret Aurélien, Malabry Thomas, Marin Timothée}
*\date 30/01/2020
*\version 0.1
*\brief fonctions de la sdl pour son initialisation, fichier .c
*/
#include "../include/constantes.h"

/**
*\fn int initialisation_sdl(SDL_Window **window, SDL_Renderer **rendu)

*\param **window contiendra la fenetre du jeu
*\param **rendu est le rendu dans la fenetre sur lequel on dessinera par la suite

*\return 0 si tout c'est bien passé, 1 si une erreur est apparue 

*\brief Initialise et créé fenetre et rendu par leur pointeur, si une initialisation échoue, on détruit tout et on retourne 1 pour signifier une erreur
*/
int initialisation_sdl(SDL_Window **window, SDL_Renderer **rendu){
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return 1;

	*window = SDL_CreateWindow("Dungeon Of Cards", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL)
		return 1;

	*rendu = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

	if(rendu == NULL){
		SDL_DestroyWindow(*window);
		return 1;
	}

	return 0;
}


/**
*\fn void quit_sdl(SDL_Renderer **rendu, SDL_Window **window)

*\param **window contient la fenetre du jeu que l'on veut détruire
*\param **rendu est le rendu dans la fenetre que l'on veut détruire

*\return 0 si tout c'est bien passé, 1 si une erreur est apparue 

*\brief détruit les renderer et window passés en paramètre
*/
void quit_sdl(SDL_Renderer **rendu, SDL_Window **window){
	SDL_DestroyRenderer(*rendu);
	SDL_DestroyWindow(*window);
}




/** 
*\fn int init_or_quit_ttf(int action)

*\param action, permet de définir si l'on souhaite initialiser ttf ou le fermer

*\return 0 si tout c'est bien passé, 1 si une erreur est apparue 

*\brief Initialise la librairie ttf
*/
int init_or_quit_ttf(int action){

	if(action){
		if(TTF_Init() != 0)
			return 1;
		else
			return 0;
	}
	else
		TTF_Quit();
		return 0;
}




/** 
*\fn extern void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect)

*\param renderer, le rendu sur lequel on va dessiner le texte
*\param x, la position x a laquelle sera le texte
*\param y, la position y a laquelle sera le texte
*\param *text, le texte que l'on souhaite dessiner à l'écran
*\param *font, la police utilisée pour écrire
*\param **texture, la texture qui contiendra le texte
*\param *rect, le rectangle qui contiendra la texture

*\brief Modifie une texture et un rect afin d'afficher le texte aux coordonnées données sur le renderer avec la police
*/
extern void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect){

    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);

    text_width = surface->w;
    text_height = surface->h;

    SDL_FreeSurface(surface);

    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


/**
*\fn int charge_image(char *path_img, image_t *struct_image, SDL_Renderer *rendu)

*\param *path_img contient le chemin et nom de l'image que l'on souhaite charger
*\param *struct_image est une structure contenant les  champs nécessaires pour afficher l'image
*\param *rendu est le rendu sur lequel on souhaite dessiner

*\brief charge une image dans une structure pouvant la contenir

*\return 1 si echec, 0 si réussite
*/
int charge_image(char *path_img, image_t *struct_image, SDL_Renderer *rendu){

	SDL_Surface *image = IMG_Load(path_img);

	if(!image){
		printf("Erreur chargement image %s\n", SDL_GetError());
		return 1;
	}

	struct_image->img = SDL_CreateTextureFromSurface(rendu, image);

	struct_image->rectangle.w = image->w;
	struct_image->rectangle.h = image->h;

	SDL_FreeSurface(image);

	return 0;
}
