/**
jeu.h
------------------
*@Author : CHOU Antoine
*@Creation date  : 14/03/2019
*@Last modification : 06/05/2019

*@brief
File containing the functions to describe the game's rules

*@details
The file contains every function to run properly the game. Assets credit goes to @Jsf23Art.
*/


#ifndef JEU_H
#define JEU_H


#include <stdio.h>
#include <time.h>

#include "constantes.h"
#include "personnage.h"

/**
*@struct Block
*@brief struct to create Block with its position and texture.
**/
typedef struct
{
    SDL_Rect pos;
}Block;

/**
*@struct Plateform
*@brief struct same as Block but for platform
**/
typedef struct
{
    SDL_Rect pos;
}Plateform;


/**
*@struct Game
*@brief contains the graphic detail to generate the game window and the map
*/
typedef struct
{
    SDL_Window *mainWindow;
    SDL_Renderer *renderer;
    Plateform tabPlat[MAX_PLATFORM];
    Block tabBlock[MAX_BLOCK];
    int nbBlock;
    int nbPlat;
}Game;


/**
*@fn void Running(Character *character, Game *gamemap)
*@brief Constantly running if no collision
*@param  Character to edit position and the game map to check collision
*@return
*/
void Running(Character *character, Game *gamemap);


/**
*@fn int detectCollision(Character *c, Game *g)
*@brief detect if there is a collision between the character and objects
*@param SDL_Rect ( either *character) is the character's hitbox, checking the surrounding for elements.
*@return 0 if no collision, 1 otherwise.
*/
int detectCollision(Character *Character, Game *gamemap);


/**
*@fn int gravityFalls(Character *character,Game *game);
*@brief Constantly falling due to gravity depending of character's gravity value.
*@param  Character only needed.
*@return 0 if gravity applies to character, -1 otherwise.
*/
void gravityFalls(Character *player,Game *game);

/**
*@fn initGame(Game *game)
*@brief Init SDL window and renderer for the game
*@param Game containing the renderer and the window
*@return the initialized game struct.
**/
Game *initGame();


/**
*@fn freeGame(Game *game)
*@brief Free SDL window and renderer created for the game
*@param Game containing the renderer and the window
*@return
**/
void freeGame(Game *game);

/**
*@fn int canSwitchGravity(Character *character, Game *gamemap)
*@brief Check if there is solid surface beneath the character.
*@param  Character to retrieve position and the game map to check collision
*@return return 0 if he can switch gravity, -1 otherwise.
*/
int canSwitchGravity(Character *character, Game *jeu);


/**
*@fn void Endgame(Game *game, Character *character)
*@brief End the game if the character is dead.
*@param Character to check if he is alive, game to be stopped.
*@return
**/
void Endgame(Game *game, Character *character);



/**
*@fn int solidSurface(Character *player, Game *g)
*@brief Detect if the player is on a solid surface
*@param The character with its hitbox and the game containing the map
*@ return 1 if there is a solid surface, 0 otherwise;
**/
int solidSurface(Character *player, Game *g);

/**
*@fn void UpdateHitbox(Character *player)
*@brief Update the low hitbox and high hitbox positions
*@param Character containing hitbox
*@return void
*/
void UpdateHitbox(Character *player);

/**
*@fn void Respawn(Game *game, Character *player){
*@brief If the player is dead, Respawn it
*@param Dead player and map where it will be respawned
*@return void
*/
void Respawn(Game *game, Character *player);



#endif // JEU_H


