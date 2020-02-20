#include <stdio.h>
#include <stdlib.h>
#include "../include/jeu.h"
#include "../include/environnement.h"
#include "../include/engine.h"
#include "../include/event.h"
#include "../include/personnage.h"

/* mainIA to test IA */
void mainIA();
/* main2 to test the current game */
int main2();

int main(int argc, char **argv){
/*
	 SDL_Init(SDL_INIT_AUDIO);

     Mix_OpenAudio(22500, MIX_DEFAULT_FORMAT, 2, 2048);

     Mix_Music *backgroundsound = Mix_LoadMUS("Assets/Music/Pacman_background.wav");
     fprintf(stderr,"Error ? : %s",SDL_GetError());
     Mix_PlayMusic(backgroundsound, 2);

    //mainIA();

    main2();
    */


	/* Unit test */
    main_mocka1();
    main_mocka2();
    main_mocka3();

    return 0;
}

int main2(int argc, char **argv){
    /** GAME INITIALISATION **/
        int i, CurrentPlayer;
        NBplayer = 0;
        MGS_event *MGSevent = initEvent();
        SDL_Event SDLevent;
        Game *jeu = NULL;
        mapElement *mapl =  (mapElement *) malloc(sizeof(mapElement));
        jeu = initGame();
    /** Player and position generation **/
        Character *player = initCharacter(),
                  *player2 = initCharacter(),
                  *player3 = initCharacter(),
                  *player4 = initCharacter();

        Character *playerArray[4] = {player, player2, player3, player4};

        SDL_Rect beginningPos = { 0, 80, 0, 0 },
                 beginningPos1 = { 0, 130, 0, 0 },
                 beginningPos2 = { 0, 180, 0, 0 },
                 beginningPos3 = { 0, 230, 0, 0 };

        SDL_Rect ArrayPos[4] = {beginningPos, beginningPos1,beginningPos2, beginningPos3};

        for ( i = 0 ; i < MAXPLAYERS ; i++){
            if((playerArray[i]->apparence = loadImage("Assets/idle.gif",jeu->renderer)) == NULL){
                fprintf(stderr,"Failed to load character's asset \n");
        }
    }

    /** Loading world elements **/
        if ( loadAssets(mapl,jeu) == -1 ) {
                fprintf(stderr,"Erreur de chargement des éléments de la map \n");
        }

    /** Main Menu **/
    MGSevent->main_menu = 1;
        while(!MGSevent->Quit){
            if( MGSevent->main_menu || MGSevent->playerSelectionMenu){
                WaitMenuEvent(MGSevent,SDLevent,jeu);
                SDL_Delay(500);
                LoadMenu(MGSevent,jeu);
            }

            if( MGSevent->playerSelectionMenu && NBplayer > 0){
        /** Generating the world and the correct player numbers**/
                    generatePlateforme(jeu,mapl);
                    generateBlock(jeu,mapl);
                    /** If only one player and init an IA **/
                    if( NBplayer == 1){
                        generatePlayer(playerArray[0],ArrayPos[0]);
                    } else if ( NBplayer > 1 ){
                       for( i = 0 ; i < NBplayer ; i++){
                            generatePlayer(playerArray[i],ArrayPos[i]);
                        }
                    }

                    loadBackground(mapl,jeu);

                    MGSevent->playerSelectionMenu = 0;
                    MGSevent->play = 1;
                    CurrentPlayer = NBplayer;

                } else if(MGSevent->play){
                /* Play function */
                DisplayMap(jeu,mapl);

                CurrentPlayer = 0;
                for( i = 0 ; i < NBplayer ; i++){
                    UpdateHitbox(playerArray[i]);
                    Running(playerArray[i],jeu);
                    gravityFalls(playerArray[i],jeu);
                    DisplayPlayer(playerArray[i],jeu);
                    Endgame(jeu,playerArray[i]);
                    CurrentPlayer += playerArray[i]->alive;
                }
                if(CurrentPlayer == 0){
                    MGSevent->play = 0;
                    SDL_Delay(500);
                    MGSevent->main_menu = 1;
                    NBplayer = 0;
                }


                    WaitEvent(MGSevent,SDLevent);
                    gravitySwitch(MGSevent,playerArray,jeu);
                    mapScrolling(jeu);
            }
        }
        /** FREE MEMORY **/
        free(MGSevent);
        MGSevent = NULL;

        free(mapl);
        mapl = NULL;

        free(player);
        free(player2);
        free(player3);
        free(player4);
        player = player2 = player3 = player4 = NULL;

        freeGame(jeu);
        jeu = NULL;

        return 0;

}

void mainIA(){
        Game *jeu = NULL;
        mapElement *mapl =  (mapElement *) malloc(sizeof(mapElement));
        jeu = initGame();
        MGS_event *MGSevent = initEvent();
        SDL_Event SDLevent;
        Character *player = initCharacter();


        loadAssets(mapl,jeu);
        SDL_Rect beginningPos = { 0, 80, 0, 0 };
        generateBlock(jeu,mapl);
        generatePlateforme(jeu,mapl);

        player->apparence = loadImage("Assets/idle.gif",jeu->renderer);
        generatePlayer(player,beginningPos);
        player->IA = 1;
        while(!MGSevent->Quit){
                    IA(jeu,player);
                    DisplayMap(jeu,mapl);
                    DisplayPlayer(player,jeu);
                    WaitEvent(MGSevent,SDLevent);
                    mapScrolling(jeu);
                    Endgame(jeu,player);
        }
}

