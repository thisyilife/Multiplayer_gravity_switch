#include <stdio.h>
#include <stdlib.h>

#include "../include/personnage.h"

/*//Version 2?
int calculScore(Character *character){

}
*/

/* Model function */
Character *initCharacter(){
    Character *player = (Character *) malloc(sizeof(Character));
    if(player == NULL)
        return NULL;
    player->alive = 1;
    player->gravity = 1;
    player->IA = 0;
    return player;
}




