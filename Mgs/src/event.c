#include "../include/event.h"

int NBplayer;



/* controller function*/
void WaitEvent(MGS_event *MGSevent, SDL_Event event)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            MGSevent->Quit = 1;
        if(event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_a :
                MGSevent->gravitySwitch[0] = 1; // Any pressed key will change gravity
                break;
            case SDLK_w :
                MGSevent->gravitySwitch[1] = 1;
                break;
            case SDLK_n :
                MGSevent->gravitySwitch[2] = 1;
                break;
            case SDLK_p :
                MGSevent->gravitySwitch[3] = 1;
                break;
            case SDLK_SPACE :
                MGSevent->bonusUse[0] = 1;
                break;
            }
        }
    }
}
/* Controller function */
void WaitMenuEvent(MGS_event *MGSevent, SDL_Event event, Game *jeu)
{
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            MGSevent->Quit = 1;
        if(event.type == SDL_MOUSEBUTTONDOWN )
        {
            SDL_GetMouseState(&MGSevent->mouse_x,&MGSevent->mouse_y);
            if( MGSevent->main_menu == 1 )
            {
                /* Ecrire tous les cas du Menu */
                if( ( ( 250 < MGSevent->mouse_x )&& (MGSevent->mouse_x < 450 )) && (( 250 < MGSevent->mouse_y ) && (MGSevent->mouse_y < 350 )) )
                {
                    MGSevent->playerSelectionMenu = 1;
                    MGSevent->main_menu = 0;
                }
                if( ( ( 850 < MGSevent->mouse_x )&& (MGSevent->mouse_x < 1050 )) && (( 250 < MGSevent->mouse_y ) && (MGSevent->mouse_y < 350 )) )
                {
                    MGSevent->Quit = 1;
                }
            }
            if( MGSevent->playerSelectionMenu == 1 )
            {
                if((( 250 < MGSevent->mouse_y ) && (MGSevent->mouse_y < 350 )) )
                {
                    if(( 100 < MGSevent->mouse_x ) && (MGSevent->mouse_x < 300 ))
                        NBplayer = 1;
                    if((400 < MGSevent->mouse_x )&& (MGSevent->mouse_x < 600 ))
                        NBplayer = 2;
                    if((700 < MGSevent->mouse_x )&& (MGSevent->mouse_x < 900 ))
                        NBplayer = 3;
                    if((1000 < MGSevent->mouse_x )&& (MGSevent->mouse_x < 1200 ))
                        NBplayer = 4;
                }
            }
        }
//        if(NBplayer > 0){
//            MGSevent->play = 1;
//            MGSevent->main_menu =0;
//            MGSevent->playerSelectionMenu =0;
//        }
    }
}


void LoadMenu(MGS_event *event, Game *jeu){
    SDL_RenderClear(jeu->renderer);
    if(event->main_menu){
        mainMenu(jeu);
        event->mouse_x = event->mouse_y = 0;
    }
    if(event->playerSelectionMenu){
        playerMenu(jeu);
        event->mouse_x = event->mouse_y = 0;
    }
}



/* Model function*/
void gravitySwitch(MGS_event *event, Character **character, Game *game)
{
    for( int i = 0 ; i < NBplayer ; i++) {
    if((event->gravitySwitch[i] & !(character[i]->IA)) && !canSwitchGravity(character[i],game))
        {
            character[i]->gravity *= -1;
        }
    event->gravitySwitch[i] = 0;
    }
}

/* Model function*/
MGS_event* initEvent()
{
    MGS_event* MGSevent = (MGS_event *) malloc(sizeof(MGS_event));
    /* Init every MGSevent parameter to 0 */
    MGSevent->playerSelectionMenu = MGSevent->Quit = MGSevent->play = MGSevent->mouse_x = MGSevent->mouse_y = 0;
    for (int i = 0 ; i < MAXPLAYERS ; i++){
       MGSevent->bonusUse[i] =  MGSevent->gravitySwitch[i] = 0;
    }
    MGSevent->main_menu = 1;
    return MGSevent;
}
