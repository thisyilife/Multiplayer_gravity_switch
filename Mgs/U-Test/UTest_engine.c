#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../include/engine.h"


static int setup_zero(void **state);
static int teardown(void **state);

static int setup_zero(void **state)
{
    Game *game = initGame();
    if ( game == NULL )
        return -1;
    *state = game;
    return 0;
}

static int teardown(void **state)
{
    freeGame((Game *) *state);
    return EXIT_SUCCESS;
}

static void test_loadAssets(void **state){
    Game *game = (Game *) *state;
    mapElement *mE = (mapElement *) malloc(sizeof(mapElement));
    assert_int_equal(loadAssets(mE,game),0);
    free(mE);
}

static void test_failure_loadAssets(void **state){
    Game *game = (Game *) *state;
    game->renderer = NULL;
    mapElement *mE = (mapElement *) malloc(sizeof(mapElement));
    assert_int_equal(loadAssets(mE,game),-1);
    free(mE);
}

static void test_loadBackground(void **state){
    Game *game = (Game *) *state;
    mapElement *mE = (mapElement *) malloc(sizeof(mapElement));
    assert_int_equal(loadBackground(mE,game),0);
    free(mE);
}

static void test_failure_loadBackground(void **state){
     Game *game = (Game *) *state;
    game->renderer = NULL;
    mapElement *mE = (mapElement *) malloc(sizeof(mapElement));
    assert_int_equal(loadBackground(mE,game),-1);
    free(mE);
}

static void test_generatePlayer(void **state){
    Game *game = (Game *) *state;
    Character *player = (Character *) malloc(sizeof(Character));
    player->apparence = loadImage("Assets/idle.gif",game->renderer);
    SDL_Rect Pos = { 0,0,0,0};
    assert_int_equal(generatePlayer(player,Pos),0);
    free(player);
}

static void test_failure_generatePlayer(void **state){
     /* *state unused */
    Character *player = (Character *) malloc(sizeof(Character));
    SDL_Rect Pos = { 0,0,0,-10};
    assert_int_equal(generatePlayer(player,Pos),-1);
    free(player);
}

static void test_generateBlock(void **state){
    Game * game = (Game *) *state;
    mapElement *mE = malloc(sizeof(mapElement));
    loadAssets(mE,game);
    generateBlock(game,mE);
    assert_int_equal(game->nbBlock,MAX_BLOCK);
    free(mE);
}

static void test_generatePlateform(void **state){
    Game * game = (Game *) *state;
    mapElement *mE = malloc(sizeof(mapElement));
    loadAssets(mE,game);
    generatePlateforme(game,mE);
    assert_int_equal(game->nbPlat,MAX_PLATFORM);
    free(mE);
}

static void test_mapScrolling(void **state){
    Game *game = (Game *) *state;
    /* Create a single platform and block to test the scrolling */
    Plateform test_plateform;
    Block test_block;
    SDL_Rect InitialPPos = { 1200,500,200,200};
    SDL_Rect InitialBPos = { 1200,300,200,200};

    test_plateform.pos = InitialPPos;
    test_block.pos = InitialBPos;

    game->tabPlat[0] = test_plateform;
    game->tabBlock[0] = test_block;

    game->nbBlock = 1;
    game->nbPlat = 1;
    /* One scroll */
    mapScrolling(game);
    assert_int_equal(game->tabBlock[0].pos.x,InitialBPos.x - SCROLL_SPEED);
    assert_int_equal(game->tabPlat[0].pos.x,InitialPPos.x - SCROLL_SPEED);
    /* Two scrolls*/
    mapScrolling(game);
    assert_int_equal(game->tabBlock[0].pos.x,InitialBPos.x - 2 * SCROLL_SPEED);
   assert_int_equal(game->tabPlat[0].pos.x,InitialPPos.x - 2 * SCROLL_SPEED);
   /* Move it too far away to the left in order to test respawning functions*/
   game->tabBlock[0].pos.x = -500;
   game->tabPlat[0].pos.x = -500;
   mapScrolling(game);
   assert_int_equal(game->tabBlock[0].pos.x,InitialBPos.x);
   assert_int_equal(game->tabPlat[0].pos.x,InitialPPos.x);


}


static void test_createButton(void **state){
    Game *game = (Game *) *state;
    SDL_Rect ButtonPos = { 200,200,220,220};
    assert_int_equal(1,createButton("Assets/Button/button_play.png",ButtonPos,game));
}

static void test_failure_createButton(void **state){
    Game *game = (Game *) *state;
    SDL_Rect ButtonPos = { 200,200,220,220};
    assert_int_equal(0,createButton("No files",ButtonPos,game));
}
/*
static void test_IA(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    IA(game,player);
}
*/

int main_mocka2(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_loadAssets,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_failure_loadAssets,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_loadBackground,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_failure_loadBackground,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_generatePlayer,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_failure_generatePlayer,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_generateBlock,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_generatePlateform,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_mapScrolling,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_createButton,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_failure_createButton,setup_zero,teardown),
       //cmocka_unit_test_setup_teardown(test_IA,setup_zero,teardown),
    };
    return cmocka_run_group_tests(tests,NULL,NULL);
}

