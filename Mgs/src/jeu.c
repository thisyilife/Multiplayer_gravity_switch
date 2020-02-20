/**
jeu.c
------------------
*@Author : CHOU Antoine
*@Creation date  : 14/03/2019
*@Last modification : 06/05/2019
**/

#include "../include/jeu.h"


/* Model function , Game * initGame() is a better option */
Game *initGame()
{
    Game *game = (Game *) malloc(sizeof(Game));
    SDL_Init(SDL_INIT_VIDEO);
    game->mainWindow = SDL_CreateWindow("Multiplayer gravity switch", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_FENETRE,HAUTEUR_FENETRE, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    game->renderer = SDL_CreateRenderer(game->mainWindow, 0, SDL_RENDERER_ACCELERATED);
    game->nbBlock = 0;
    game->nbPlat = 0;
    if ( game->mainWindow == NULL || game->renderer == NULL )
    {
        return NULL;
    }
    return game;
}

/* Model function */
int detectCollision(Character *player, Game *g){
    /* Récupérer les éléments pouvant cogner le joueurs*/
    /* Check si cela percute le personnage */
    /* Ou tout check */
    int i,j;
    for(i = 0; i < g->nbBlock ; i++){
        if ( SDL_HasIntersection(&player->hitbox.All,&g->tabBlock[i].pos) == SDL_TRUE )
            return 1;
    }
    for(j = 0; j < g->nbPlat ; j++){
        if ( SDL_HasIntersection(&player->hitbox.All,&g->tabPlat[j].pos) == SDL_TRUE )
            return 1;
    }
    return 0;
}

/* Model function */
int solidSurface(Character *player, Game *g)
{
    int i,j;
    if ( player->gravity == 1)
    {
        for(i = 0; i < g->nbBlock ; i++)
        {
            if ( SDL_HasIntersection(&player->hitbox.Low,&g->tabBlock[i].pos) == SDL_TRUE )
                return 1;
        }
        for(j = 0; j < g->nbPlat ; j++)
        {
            if ( SDL_HasIntersection(&player->hitbox.Low,&g->tabPlat[j].pos) == SDL_TRUE )
                return 1;
        }
    }
    else if ( player->gravity == -1)
    {
            for(i = 0; i < g->nbBlock ; i++)
            {
                if ( SDL_HasIntersection(&player->hitbox.High,&g->tabBlock[i].pos) == SDL_TRUE )
                    return 1;
            }
            for(j = 0; j < g->nbPlat ; j++)
            {
                if ( SDL_HasIntersection(&player->hitbox.High,&g->tabPlat[j].pos) == SDL_TRUE )
                    return 1;
            }
        }
    return 0;
}


/* Model function */
void gravityFalls(Character *character, Game *game)
{
    if(!solidSurface(character,game)){
           character->hitbox.All.y += (character->gravity) * 15;
    }
}



/* Model function*/
void freeGame(Game *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->mainWindow);
    SDL_Quit();
    free(game);
    game = NULL;
}

/* Model function */
void Running(Character *player, Game *g){
    if ( detectCollision(player,g)){
        player->hitbox.All.x -= SCROLL_SPEED;
        } else {
        player->hitbox.All.x += RUN_SPEED;
    }
}

/* model function */
int canSwitchGravity(Character *player, Game *g){
    if( solidSurface(player,g)){
        return 0;
    }
    return -1;
}

/* Model function */
void UpdateHitbox(Character *player){
    SDL_Rect rect = player->hitbox.All;
    SDL_Rect lowRect = { rect.x , rect.y + rect.h/2 , rect.w/4 , rect.h - 3 };
    player->hitbox.Low = lowRect;
    SDL_Rect highRect = { rect.x , rect.y - 15, rect.w/4 , rect.h};
    player->hitbox.High = highRect;
}

/* Model function */
void Endgame(Game *game, Character *player)
{
    if ( (DOWN_LIMIT < player->hitbox.All.y) || (player->hitbox.All.y < UP_LIMIT ) || ( player->hitbox.All.x < LEFT_LIMIT)){
        player->alive = 0;
        player->gravity = 1; // Reset gravity when players dies
    }
    if (player->IA){
        Respawn(game,player);
    }
}

/* Model function */
void Respawn(Game *game, Character *player){
    if(!player->alive){
        player->alive = 1;
        player->hitbox.All.x = RESPAWN_POSX;
        player->hitbox.All.y = RESPAWN_POSY;
    }
}


