/**
environnement.c
------------------
*@Author : CHOU Antoine
*@Creation date  : 24/03/2019
*@Last modification : 30/04/2019

**/

#include "../include/environnement.h"

/* Model function*/
SDL_Texture* loadImage(char *file, SDL_Renderer *renderer)
{
    SDL_Surface *image = NULL;  // Creating and loading the image
    SDL_Texture *texture = NULL;
    image = IMG_Load(file);
    if( image == NULL)
        {
            fprintf(stderr,"The file couldn't be loaded \n");
            return NULL;
        }
    texture = SDL_CreateTextureFromSurface(renderer, image);
    // Checking that it has been created
    if (  texture == NULL )
        {
            fprintf(stderr,"The texture wasn't loaded properly \n");
            return NULL;
        }
    // Image is not longer needed, we can free allocated memory.
    SDL_FreeSurface(image);
    return texture;
}

/* View function*/
void DisplayPlayer(Character *character,Game *mapp){
    if(character->gravity == 1){
    SDL_RenderCopy(mapp->renderer, character->apparence, NULL, &(character->hitbox.All));
    } else if (character->gravity == -1){
    SDL_RenderCopyEx(mapp->renderer,character->apparence,NULL,&(character->hitbox.All),0,NULL,SDL_FLIP_VERTICAL);
    }
    SDL_RenderPresent(mapp->renderer);
}

void DisplayMap(Game* jeu,mapElement *mE){
    /* Initialisation */
    Block b;
    Plateform p;
    SDL_Rect BackgroundPos = {0,0,LARGEUR_FENETRE,HAUTEUR_FENETRE};
    int i,j;

    SDL_RenderClear(jeu->renderer);

    SDL_RenderCopy(jeu->renderer,mE->background,NULL,&BackgroundPos);
    for ( i = 0; i < jeu->nbBlock; i++){
    b = jeu->tabBlock[i];

        SDL_RenderCopy(jeu->renderer,mE->block,NULL,&b.pos);

    }
    for( j = 0; j < jeu->nbPlat; j++){
        p = jeu->tabPlat[j];
        SDL_RenderCopy(jeu->renderer,mE->platform,NULL,&p.pos);
    }
     SDL_RenderPresent(jeu->renderer);
}



