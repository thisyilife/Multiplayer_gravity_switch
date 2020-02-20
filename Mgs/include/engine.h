/**
engine.h
------------------
*@Author : CHOU Antoine
*@Creation date  : 30/03/2019
*@Last modification : 14/05/2019

*@brief
File containing the functions to update the game.

*@details
This file contains every function to update the game's elements without displaying it to the user.
Elements from game.h and environnement.h are needed.
*/

#ifndef ENGINE_H
#define ENGINE_H



#include "jeu.h"
#include "environnement.h"




/**
*@fn int loadAssets(mapElement *mE,Game *jeu)
*@brief load every assets needed to play
*@param mapElement to store the loaded assets and *Game to provide the renderer.
*@return 0 if every assets were loaded, -1 otherwise
*/
int loadAssets(mapElement *elements, Game *jeu);

/**
*@fn int generatePlayer(Character *character, SDL_Rect pos);
*@brief generate the player in a given position.
*@param  The player to be generated, its avatar and the position. 0 if it's a player, 1 if its an IA.
*@return  0 if correctly generated, -1 otherwise
*/
int generatePlayer(Character *character, SDL_Rect pos);

/**
*@fn void mapScrolling(Game *gameMap);
*@brief Create an illusion of map scrolling
*@param We need to retrieve the current element and push each one to the left.
*@return
*/
void mapScrolling(Game *gameMap);

/**
*@fn void generatePlatforme(Game* jeu, mapElement *m)
*@brief generate the platform on the map
*@param Game where it need to be generated, mapElement containing the view
*@return void
*/
void generatePlateforme(Game* jeu,mapElement *mE);


/**
*@fn void generateBlock(Game* jeu, mapElement *m)
*@brief generate the block on the map
*@param Game where it need to be generated, mapElement containing the view
*@return void
*/
void generateBlock(Game* jeu, mapElement *mE);


/**
*@fn int loadBackground(Game *jeu, mapElement *mE);
*@brief load the background and sheer it
*@param Game contains the targetted renderer and mapelement the background
*@return 1 on success, -1 otherwise;
*/
int loadBackground(mapElement *mapp, Game* Jeu);

/**
*@fn Button *createButton(char *file,SDL_Rect Pos,Game *jeu)
*@brief Create a button ;
*@param file containing the button's picture, Pos where it needs to be created and Game containing the targeted renderer.
*@return Return 1 on success, 0 otherwise.
*/
int createButton(char *file,SDL_Rect Pos,Game *jeu);

/**
*@fn void mainMenu(Game *jeu)
*@brief Create the main menu renderer
*@param Game contains the targeted renderer;
*@return
*/
void mainMenu(Game *jeu);


/**
*@fn void playerMenu(Game *jeu)
*@brief Generate the menu to choose the number of player
*@param Game containing the targeted renderer;
*@return
*/
void playerMenu(Game *jeu);

/**
*@fn void IA(Game *jeu, Character *player)
*@brief A player is controlled by an AI
*@param player to be controlled and game containing the environnement
*@return
*/
void IA(Game *jeu, Character *player);


#endif // ENGINE_H






