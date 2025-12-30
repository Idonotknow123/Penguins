#ifndef GRID_H
#define GRID_H

#include "structures.h"

/**
 * "grid.h" has declaration of functions that are related to making changes
 * inside the tile (like changing an ice floe tile to a sea tile, placing a penguin on a tile
 * (changing the is_penguin value)
 * And also a function that is responsible for printing a specific tile (considering all the
 * information that it has)
 */

 /**
 * @brief prints the specific tile
 *
 * This function prints the current state of a tile with use of colors and different symbols.
 * If on a specific tile there's a penguin of a specific player, it prints in yellow color ID of that player on the tile
 * If there isn't any penguin and the tile is an ice floe, it prints in white the number of fish on it
 * If the tile is sea, it prints "_ "
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile
 */
void draw_tile(GameState *g, Tile t);

 /**
 * @brief places the penguin on a tile
 *
 * This function places a penguin of current player on a chosen tile.
 * It changes is_penguin to 1, and writes down the ID of current player.
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile
 */
void place_penguin(GameState *g, Tile t);

 /**
 * @brief changes ice floe to sea
 *
 * This function "removes the tile", i.e. changes an ice floe tile to a sea tile, so that
 * it's not considered a valid move anymore, and no player can place a penguin there
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile
 */
void remove_tile(GameState *g, Tile t);

 /**
 * @brief moves penguin
 *
 * This function moves penguin using place_penguin and remove_time functions.
 * it moves penguin to a new tile and changes the previous one to a sea tile.
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile on which the penguin is standing
 * @param t_move A specific tile to which the penguins are moved
 */
void move_penguin(GameState *g, Tile t, Tile t_move);

#endif //GRID_H