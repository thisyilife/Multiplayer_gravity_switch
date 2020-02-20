#include "../include/event.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static int setup_zero(void** state){
    MGS_event *event = initEvent();
    if(event == NULL)
        return EXIT_FAILURE;
     *state =  event;
     return EXIT_SUCCESS;
}

static int teardown(void **state){
    free((MGS_event *) *state);
    return EXIT_SUCCESS;
}

static void test_gravitySwitch(void **state){
    MGS_event *event = *state;
    SDL_Rect InitPos = {100,100,200,200};

    Character *player = initCharacter();
    player->hitbox.All = InitPos;
    UpdateHitbox(player);
     Character *playerArray[1] = {player};
    Game *game = initGame();
    NBplayer = 1;
    /* The player initial gravity's value is 1, to simulate a gravity switch we need to create
     a platform under the player and ask for a gravity switch */
    gravitySwitch(event,playerArray,game);
    /* Cannot change gravity, gravity still equals to 1 */
    assert_int_equal(player->gravity,1);
    /* Create a platform */
    Plateform plat;
    InitPos.y += 100;
    plat.pos = InitPos;
    game->tabPlat[0] = plat;
    game->nbPlat += 1;
    event->gravitySwitch[0] = 1;
    /* Possible to switch gravity by now */
    gravitySwitch(event,playerArray,game);
    assert_int_equal(player->gravity,-1);
    free(player);
    freeGame(game);
}


int main_mocka1(){
    const struct CMUnitTest tests[] =
    {
        cmocka_unit_test_setup_teardown(test_gravitySwitch,setup_zero,teardown),
    };
    return cmocka_run_group_tests(tests,NULL,NULL);
}



