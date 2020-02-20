/**
personnage.h
------------------
*@Author : Bub Victor
*@Creation date  : ??/??/2019
*@Last modification : 06/05/2019

*@brief
File containing structs and functions related to the character such as bonus, avatar, and the character itself.

*@details
The file contains functions to access character structure and structures related to the character.
*/



#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

#define NUMBER_AVATARS 5 //can be changed

/**
*@fn / @struct / @enum --> prototype de la fonction / nom de la structure / nom de l'énumeration
*@brief --> description rapide de la fonction / structure / enum
*@details --> description detailler n'est pas obligatoire
*@param param_name --> description rapide du paramètre "param_name"
*@return --> description rapide des caleurs de retour de la fonction (si la fonction ne retourne rien, omettez ce champs)
*/

/**
* @enum / @struct mon_enum / ma_struct
*@brief This is an example of an enumeration
*/

/**
*@struct --> Avatar
*@brief --> Helps to define the different avatars
*@details --> consist of name, individual factors for gravity, speed, and the score plus his appearence as an SDL-texture
*@param
*/

typedef struct {
    char name[20]; //name

    double in_grav_fact; //individual gravity factor
    double in_speed_fact; //individual speed factor
    double in_score_fact; //individual score factor
    //SDL_Texture *appearence[NUMBER_AVATARS]; //e.g. image...
} Avatar;



/**
*@struct --> Bonus
*@brief --> contains different characteristics of a Bonus
*@details --> characteristics can be different factors for speed/ gravity.. and his appearence in the game as an SDL_texture
*@param param_name -->
*/

typedef struct{
    double fact_speed; //to change the speed
    double fact_gravity; //to change the intenisty of the gravity
    double fact_score; //maybe 2*the score in that time
    int score_bonus; //maybe score += score_bonus?

    SDL_Texture *bonus_image; //picture of the bonus
}Bonus;

/**
*@struct --> Hitbox
*@brief --> Contains different hero's body part to differentiate them.
*@details --> Part of character's struct, useful to determine where the objects collide with avatar.
*@param param_name -->
*/
typedef struct
{
    SDL_Rect High;
    SDL_Rect All;
    SDL_Rect Low;
} Hitbox;


/**
*@struct --> Character
*@brief --> Top of the hierarchie, contains avatar, position and bonus
*@details --> different characteristics as status of gravity, live, score.... SDL_Rect Hitbox aswell
*@param param_name -->
*/

typedef struct
{
    int gravity;
    int alive;
    int IA;
    SDL_Texture *apparence;
    Hitbox hitbox;
    /* Not used ATM */
    Avatar *avatar;
    Bonus *bonus;
}Character;

//functions:

/**
*@fn --> hasBonus
*@brief --> Tests if player is in posession of bonus
*@details --> returns 0 if player is in posession, -1 if not
*@param param_name --> *character
*@return --> 0 if player is in posession, -1 else
*/

int hasBonus(Character *character);

/**
*@fn --> supprBonus
*@brief --> deletes bonus after beeing used
*@param param_name --> *character
*@return --> nothing
*/

void supprBonus(Character *character);

/**
*@fn --> isDead
*@brief --> test if character is dead
*@details --> returns 0 if character is dead, -1 if he is still alive
*@param param_name --> *character
*@return --> 0 if character is dead, -1 if he is alive
*/

int isDead(Character *character);

/**
*@fn calculScore
*@brief --> calculates the characters score
*@param param_name --> *character
*@return --> score of the character
*/

int calculScore(Character *character);

/**
*@fn getPos
*@brief --> finds position of character
*@details --> returns the hitbox of the character, the hitbox contains the bloc/coordinates of the character
*@param param_name --> *character
*@return --> hitbox
*/

SDL_Rect getPos(Character *character);


/*********** A changer **************/
/**
*@fn int *initCharacter(Character *character)
*@brief initialize character given in parameters.
*@param Character to be initialized
*@ return 1 on success, 0 otherwise.
**/
Character *initCharacter();

#endif // PERSONNAGE_H

