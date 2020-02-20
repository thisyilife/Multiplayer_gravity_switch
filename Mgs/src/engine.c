/**
engine.c
------------------
*@Author : CHOU Antoine
*@Creation date  : 24/03/2019
*@Last modification : 15/05/2019

**/

#include "../include/engine.h"



/* Model function*/
int loadAssets(mapElement *elements, Game *jeu){
    /*      Checking if it's loaded properly            */
    loadBackground(elements,jeu);
    if ((elements->block = loadImage("Assets/Block.png",jeu->renderer)) == NULL )
        {
            return -1;
        }
        /*      Checking if it's loaded properly            */
    if ((elements->platform = loadImage("Assets/Plateforme.png",jeu->renderer)) == NULL)
        {
            return -1;
        }
    jeu->nbPlat = jeu->nbBlock = 0;
    return 0;
}

/* Model function */
int loadBackground(mapElement *elements, Game *jeu){
    if((elements->background = loadImage("Assets/Background/plx-5.png",jeu->renderer)) == NULL){
        return -1;
    }
    SDL_SetTextureAlphaMod(elements->background, ALPHA_VALUE);
    return 0;
}

/* Model function*/
int generatePlayer(Character *character, SDL_Rect pos)
{
    int width = 0,
        height = 0;

    if (SDL_QueryTexture(character->apparence,NULL,NULL,&width,&height) != 0)
    {
        return -1; // NULL and NULL as we don't need access and format atm.
    }
    SDL_Rect rect = {pos.x, pos.y, width + 10, height};
    // + 10 is an arbitrary value to create a bigger hitbox than the texture
    pos.h = height + 10;
    pos.w = width + 10;
    character->alive = 1;
    /* Hitbox initialisation */
    character->hitbox.All = rect;
    UpdateHitbox(character);

    return 0;
}



/* Model function */
void generateBlock(Game *jeu,mapElement *mE)
{
    int i,width,height;
    /* Pos chosen randomly, possible to change value to test */
    SDL_QueryTexture(mE->block,NULL,NULL,&width,&height);
    SDL_Rect pos = { 680, 50, width,height};
    Block bloc;
    /* Generate 5 blocs on pos and next to pos */
    for ( i = 0; i < 5; i++)
    {
        bloc.pos = pos;
        pos.x += pos.w;
        jeu->tabBlock[i] = bloc;
        if(jeu->nbBlock < MAX_BLOCK)
        jeu->nbBlock++;
    }
    /* Generate blocs on the ground, pos can be changed */
   for ( i = 5; i < MAX_BLOCK ; i++){
        pos.y = 550;
        bloc.pos = pos;
        bloc.pos.x += pos.w*(i+1);
        jeu->tabBlock[i] = bloc;
        if(jeu->nbBlock < MAX_BLOCK)
        jeu->nbBlock++;

    }

}

/* Model function */
void generatePlateforme(Game *jeu,mapElement *mE){
    int i,width,height;
    /* Used random value to generate */
    SDL_QueryTexture(mE->platform,NULL,NULL,&width,&height);
    SDL_Rect pos = { 0,350, width,height};

    Plateform plat;
/** Creating 3 different levels of platform **/
    for ( i = 0; i < 3 ; i++)
    {
        plat.pos = pos;
        pos.x += pos.w;
        jeu->tabPlat[i] = plat;
        if ( jeu->nbPlat < MAX_PLATFORM )
        jeu->nbPlat++;
    }
    pos.x = 150;
    for ( i =  3; i < 9 ; i++){
        plat.pos = pos;
        plat.pos.y = 600;
        plat.pos.x += pos.w*(i);
        jeu->tabPlat[i] = plat;
        if ( jeu->nbPlat < MAX_PLATFORM )
            jeu->nbPlat++;
    }
    for ( i =  9; i < MAX_PLATFORM ; i++){
        plat.pos = pos;
        plat.pos.y = 30;
        plat.pos.x += pos.w*(i);
        jeu->tabPlat[i] = plat;
        if ( jeu->nbPlat < MAX_PLATFORM )
            jeu->nbPlat++;
    }
}

/* Model function */
void mapScrolling(Game *game)
{
    int i,j;
    for ( i = 0 ; i < game->nbBlock ; i++)
    {
        if ( game->tabBlock[i].pos.x < 0)
        {
    /* If the block is too far on the left, we move it to the right side of the screen */
            game->tabBlock[i].pos.x = 1200;
        } else {
    /* Scrolling every block */
            game->tabBlock[i].pos.x -= SCROLL_SPEED;
        }
    }
    /* Same with platform */
        for ( j = 0 ; j < game->nbPlat ; j++)
        {
           if ( game->tabPlat[j].pos.x < -250)
            {
                game->tabPlat[j].pos.x = 1200;
            } else {
                game->tabPlat[j].pos.x -= SCROLL_SPEED;
            }
        }
    SDL_Delay(PLAY_SPEED); // We delay to not make the game too fast
}

void mainMenu(Game *jeu){
        SDL_Rect Pos = { 250,250, BUTTON_WIDTH, BUTTON_HEIGHT};
        createButton("Assets/Button/button_play.png",Pos,jeu);
        Pos.x += 600;
        createButton("Assets/Button/button_quit.png",Pos,jeu);
        SDL_RenderPresent(jeu->renderer); /* A effacer et mettre dans display menu */
}

void playerMenu(Game *jeu)
{
    SDL_Rect Pos = { 100,250, BUTTON_WIDTH, BUTTON_HEIGHT};
    /* Create up to 4 buttons which is the maximum players number */
    createButton("Assets/Button/button_solo.png",Pos,jeu);
    Pos.x += 300;
    createButton("Assets/Button/button_duo.png",Pos,jeu);
    Pos.x += 300;
    createButton("Assets/Button/button_trio.png",Pos,jeu);
    Pos.x += 300;
    createButton("Assets/Button/button_quad.png",Pos,jeu);
    SDL_RenderPresent(jeu->renderer); /* A effacer et mettre dans display menu */
}


/* Model function */
int createButton(char *file,SDL_Rect Pos,Game *jeu){
    /* Init the buttons */
    SDL_Texture *button;
    /* Load the buttons and check if it was done properly */
    if ( (button = loadImage(file,jeu->renderer)) == NULL){
        return 0;
    }
    SDL_RenderCopy(jeu->renderer,button,NULL,&Pos);
    return 1;
}


void IA(Game *jeu, Character *player){

    UpdateHitbox(player);
    gravityFalls(player,jeu);

    Running(player,jeu);
    /* Creating a fake player to check what the IA face */
    Character *mockPlayer = (Character *) malloc(sizeof(Character));
    mockPlayer->hitbox = player->hitbox;
    mockPlayer->gravity = player->gravity;
    mockPlayer->hitbox.All.x += 50;
    if ( player->gravity == 1)
    {
        /* Initialize a "detection zone" to the AI */
        SDL_Rect mockHitbox = { mockPlayer->hitbox.Low.x + 100, mockPlayer->hitbox.Low.y, mockPlayer->hitbox.Low.w += 150, HAUTEUR_FENETRE - mockPlayer->hitbox.Low.y };
        mockPlayer->hitbox.Low =  mockHitbox ;
    }
    else {
        /* Do the same thing than above */
        SDL_Rect mockHitbox = { mockPlayer->hitbox.Low.x + 100, 0 , mockPlayer->hitbox.Low.w += 150, mockPlayer->hitbox.Low.y };
        mockPlayer->hitbox.High = mockHitbox;
    }
    /* Facing a hole ?*/
    if ( !solidSurface(mockPlayer,jeu) && !canSwitchGravity(player,jeu))
    {
        /* Yes, is there any plateforme down or up ? */
        if (!solidSurface(mockPlayer,jeu))
        {
            /* No then switch gravity */
            player->gravity *= -1;
        }
    } else {
          /* Facing a wall ? */
        if ( detectCollision(mockPlayer,jeu) && !canSwitchGravity(player,jeu))
        {
            player->gravity *= -1;
        }
    }
   // Endgame(jeu,player);
}

