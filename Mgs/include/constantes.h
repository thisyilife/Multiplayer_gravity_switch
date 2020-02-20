/**
constantes.h
------------------
*@Author : CHOU Antoine
*@Creation date  : 14/03/2019
*@Last modification : 14/05/2019
*@brief
File with every defined useful constant for the game.
*@details
This file contains every constant such as the height and width of the game. It's been fixed to make the code easier to write together.
*/

#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_mixer.h>

#define HAUTEUR_FENETRE 680
#define LARGEUR_FENETRE 1280

#define ALPHA_VALUE 80

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 100

#define RESPAWN_POSX 250
#define RESPAWN_POSY 200

#define MAX_BLOCK 15
#define MAX_PLATFORM 20
#define MAXPLAYERS 4

#define DOWN_LIMIT 700
#define UP_LIMIT -100

#define LEFT_LIMIT -20
#define SCROLL_SPEED 46 * .5 // 46 which is the width of a BLOCK
#define RUN_SPEED 1 // Value between 1-5
#define PLAY_SPEED 20 // A good range would be between 20 - 400

extern int NBplayer;

#endif // CONSTANTES_H
