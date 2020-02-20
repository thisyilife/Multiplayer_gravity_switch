/**
environnement.h
------------------
*@Author : CHOU Antoine
*@Creation date  : 24/03/2019
*@Last modification : 30/04/2019

*@brief
File containing the map and function to display the game.

*@details
This file contains every needed function to display each elements of the game such as the background, the map and the character(s).
**/

#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include "constantes.h"
#include "jeu.h"



/**
*@struct mapElement
*@brief struct to save map's elements like block or platform in arrays.
**/
typedef struct
{
    SDL_Texture *block;
    SDL_Texture *platform;
    SDL_Texture *background;
} mapElement;






/**
*@fn SDL_texture* loadImage(char *file, SDL_Renderer *renderer)
*@brief load an image and convert it to a texture
*@param file contains the path to the image and store it in texture. A renderer is needed in order to blit the texture on it.
*@return 0 if it has been loaded and saved, -1 otherwise
**/

SDL_Texture* loadImage(char *file, SDL_Renderer *renderer);

/**
*@fn void DisplayMap(Game* environ, mapElement *mE);
*@brief Display every element of the map;
*@param Display the map according to environ and the stage
*@return
*/
void DisplayMap(Game* environ, mapElement *mE);

/**
*@fn void DisplayPlayer(Character* character, Game *environ);
*@brief Display the character.
*@param Display the character on the map with position already set.
*@return
*/
void DisplayPlayer(Character *hero,Game *mapp);





#endif  // ENVIRONNEMENT_H
