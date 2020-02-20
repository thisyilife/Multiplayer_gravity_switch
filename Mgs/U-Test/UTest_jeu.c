#include "../include/jeu.h"
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>



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


static void test_Running(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    SDL_Rect initPos = {100,100,200,200};
    player->hitbox.All = initPos;
    /*Without obstacle*/
    Running(player,game);
    assert_int_equal(player->hitbox.All.x,initPos.x + RUN_SPEED);

}

static void test_fail_detectCollision(void **state){
    Game *game = (Game*) *state;
    Character *player = initCharacter();
    /*There is no collision */
    assert_int_equal(detectCollision(player,game),0);
}

static void test_detectCollision_Block(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    SDL_Rect InitPos = { 200,200,200,200};
    player->hitbox.All = InitPos;
    /*Create a bloc in front of the player*/
    Block bloc;
    bloc.pos = InitPos;
    bloc.pos.x += 150;
    game->tabBlock[0] = bloc;
    game->nbBlock++;
    assert_int_equal(detectCollision(player,game),1);
    /* Run to check if collision still works */
    Running(player,game);
    assert_int_equal(detectCollision(player,game),1);

    /* Any block under the player ? it should not have anything */
    free(player);

}


static void test_detectCollision_Plat(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    SDL_Rect InitPos = { 200,200,200,200};
    player->hitbox.All = InitPos;
    /*Create one plateform in front of the player and one beneath*/
    Plateform plat1;
    plat1.pos = InitPos;
    plat1.pos.x += 100;
    game->tabPlat[0] = plat1;
    game->nbPlat++;
    /*Is there a collision ? */
    assert_int_equal(detectCollision(player,game),1);
    free(player);
}

static void test_solidSurface_Block(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    SDL_Rect InitPos = {200,200,200,200};
    player->hitbox.All = InitPos;
    UpdateHitbox(player);
    /* test without solid blocs and plateforms*/
    assert_int_equal(solidSurface(player,game),0);
    /* Test with one block */
    Block bloc;
    bloc.pos = InitPos;
    bloc.pos.y += 250;
    game->tabBlock[0] = bloc;
    game->nbBlock++;
    assert_int_equal(solidSurface(player,game),1);
    /* Reversed gravity and update the bloc's pos*/
    player->gravity = -1;
    game->tabBlock[0].pos.y -= 250 + 200;
    assert_int_equal(solidSurface(player,game),1);
    free(player);
}

static void test_solidSurface_Plateform(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    SDL_Rect InitPos = {200,200,200,200};
    player->hitbox.All = InitPos;
    UpdateHitbox(player);
    /* test without solid blocs and plateforms*/
    assert_int_equal(solidSurface(player,game),0);
    /* Test with one plateform */
    Plateform plat;
    plat.pos = InitPos;
    plat.pos.y += 250;
    game->tabPlat[0] = plat;
    game->nbPlat++;
    assert_int_equal(solidSurface(player,game),1);
    /* Reversed gravity and update the plateform's pos*/
    player->gravity = -1;
    game->tabPlat[0].pos.y -= 250 + 200;
    assert_int_equal(solidSurface(player,game),1);
    free(player);
}

static void test_canSwitchGravity(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    SDL_Rect Pos = {200,200,200,200};
    player->hitbox.All = Pos;
    UpdateHitbox(player);
    /* Nothing below the player, cannot switch gravity */
    assert_int_equal(canSwitchGravity(player,game),-1);
    /* Create a plateform under the player */
    Plateform plat;
    plat.pos = Pos;
    plat.pos.y = 250;
    game->tabPlat[0] = plat;
    game->nbPlat += 1;
    /* Should be able to switch gravity now*/
    assert_int_equal(canSwitchGravity(player,game),0);
    /* Erasing the plateform, the player wouldn't be able to switch gravity again */
    game->nbPlat = 0;
    assert_int_equal(canSwitchGravity(player,game),-1);
    free(player);
}

static void test_gravityFalls(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    SDL_Rect Pos = {200,200,200,200};
    player->hitbox.All = Pos;
    UpdateHitbox(player);
    /* Map is empty, the player is falling */
    gravityFalls(player,game);
    UpdateHitbox(player);
    assert_int_not_equal(player->hitbox.All.y, Pos.y);
    SDL_Rect CurrentPos = player->hitbox.All;
    /* Create a solid surface underneath the player */
    Plateform plat;
    plat.pos = Pos;
    plat.pos.y = 250;
    game->tabPlat[0] = plat;
    game->nbPlat += 1;
    /* He should not have fallen, he has the same position than earlier */
    gravityFalls(player,game);
    UpdateHitbox(player);
    assert_int_equal(CurrentPos.x,player->hitbox.All.x);
    assert_int_equal(CurrentPos.y,player->hitbox.All.y);
    free(player);
}

static void test_Endgame(void **state){
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    /* Give the player the X position limit */
    SDL_Rect PosLimit = { LEFT_LIMIT -1 , 200, 200 ,200};
    player->hitbox.All = PosLimit;
    /* The character should have died */
    Endgame(game,player);
    assert_int_equal(player->alive,0);
    /* Testing the Y limit */
    player->alive = 1;
    PosLimit.x = 300;
    PosLimit.y = DOWN_LIMIT + 1 ;
    Endgame(game,player);
    assert_int_equal(player->alive,0);
    /* testing the second Y limit */
    player->alive = 1;
    PosLimit.x = 300;
    PosLimit.y = UP_LIMIT - 1;
    Endgame(game,player);
    assert_int_equal(player->alive,0);
    free(player);
}
static void test_Respawn(void **state){
    /* IA respawning test */
    Game *game = (Game *) *state;
    Character *player = initCharacter();
    player->alive = 0;
    player->IA = 1;
    Endgame(game,player);
    assert_int_equal(player->alive,1);
    assert_int_equal(player->hitbox.All.x,RESPAWN_POSX);
    assert_int_equal(player->hitbox.All.y,RESPAWN_POSY);
    free(player);
}


int main_mocka3(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_Running,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_fail_detectCollision,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_detectCollision_Block,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_detectCollision_Plat,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_solidSurface_Block,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_solidSurface_Plateform,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_canSwitchGravity,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_gravityFalls,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_Endgame,setup_zero,teardown),
        cmocka_unit_test_setup_teardown(test_Respawn,setup_zero,teardown),
    };
    return cmocka_run_group_tests(tests,NULL,NULL);
}

