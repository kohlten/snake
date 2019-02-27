/**
 * @defgroup Game
 * @{
 */

#include "game.h"
#include <stdio.h>

// http://lazyfoo.net/tutorials/SDL/
// https://wiki.libsdl.org/CategoryAPI
// https://cabochongames.itch.io/volcano-world-tiles
// https://chipmunk-physics.net/release/ChipmunkLatest-Docs/
// https://forums.libsdl.org/viewtopic.php?p=38717

// For windows, SDL2 creates a main (WHY?????)
#undef main

/**
 * Entry point of the program. Will create a new game, then it will initialize the game.
 * Then it will run the game. When the game is complete, it will free the game.
 * @return
 */
int main()
{
    t_game *game;

    if (!(game = create_game()))
    {
        printf("Failed to create game!\n");
        return -1;
    }
    if (init_objects(game) == -1)
        return -1;
    run(game);
    clean_game(game);
    return 0;
}

/**
 * @}
 */