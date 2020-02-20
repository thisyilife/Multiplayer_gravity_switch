/**
event.h
------------------
*@Author : CHOU Antoine
*@Creation date  : 02/04/2019
*@Last modification : 14/05/2019

*@brief
File containing event management functions.

*@details
This file contains every needed function to manage input from user.
**/

#ifndef EVENT_H
#define EVENT_H

#include "engine.h"
#include "constantes.h"



/**
*@struct MGS_event
*@brief Struct containing event to be pulled.
**/
typedef struct {
    int mouse_x;
    int mouse_y;
    int bonusUse[MAXPLAYERS];
    int gravitySwitch[MAXPLAYERS];
    int main_menu;
    int playerSelectionMenu;
    int play;
    int Quit;
} MGS_event;
// Peut être pas int mais des SDL_Event type, a voir.

/**
*@fn void gravitySwitch(MGS_event *event, Character *character, Game *game)
*@brief If wanted and possible, Switch character's gravity
*@param MGS_event to check if player wants to change gravity, character and map to check if it's possible to change gravity.
*@return
**/
void gravitySwitch(MGS_event *event, Character **character, Game *game);

/**
*@fn void WaitMenuEvent(MGS_event *MGSevent, SDL_Event event, Game *jeu);
*@brief Check for requested action about game's menu.
*@param MGSevent to check status change, SDL_Event to retrieve user's input and Game containing the targeted renderer.
*@return
**/
void WaitMenuEvent(MGS_event *MGSevent, SDL_Event event, Game *jeu);

/**
*@fn void WaitEvent(MGS_event MGSevent, SDL_Event event)
*@brief Check for requested action concerning player's action.
*@param MGSevent to check status change, SDL_Event to retrieve user's input.
*@return
**/
void WaitEvent(MGS_event *MGSevent, SDL_Event event);

/**
*@fn MGS_event initEvent()
*@brief Set every event's value to 0.
*@param MGS_event to be initialized.
*@return
**/
MGS_event * initEvent();

/**
*@fn void LoadMenu(MGS_event *event, Game *jeu);
*@brief Load menu following user's click
*@param MGS_event to found if the user requires a menu selection
*@return
**/
void LoadMenu(MGS_event *event, Game *jeu);

#endif // EVENT_H
