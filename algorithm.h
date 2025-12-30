#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "structures.h"

/**
 * @brief performs placement
 *
 * This function performs a placement. It searches for a tile with the greatest potential
 * and places a penguin on that tile.
 *
 * @param g Pointer to the structure that saves the state of the Game
 */
void make_a_placement(GameState *g);

/**
 * @brief performs a move
 *
 * This function performs a move (moves a penguin) to a specific tile that is chosen by
 * the program using potential() function. It calculates which tile has the
 * greatest potential and then places a penguin on that tile.
 *
 * @param g Pointer to the structure that saves the state of the Game
 */
void make_a_move(GameState *g);

/**
 * @brief calculates potential
 *
 * This function calculates the potential of the tiles that a specific penguin can
 * make a move to.
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile
 * @param depth Sets how many times the function will go into recursion
 *
 * @return Returns the potential of a specific tile
 */
int potential(GameState *g, Tile t, int depth);

 /**
 * @brief counts the number of available moves
 *
 * This function counts the number of available moves that a chosen penguin can perform.
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile
 *
 * @return Returns the number of available moves
 *
 */
int count_available_moves(GameState *g, Tile t);

 /**
 * @brief saves Tiles available for movement
 *
 * This function saves the parameters of Tiles on the board that a specific penguin
 * can make a move to.
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile
 *
 * @return Returns a pointer to the available Tile
 */
Tile * available_moves(GameState *g, Tile t);

 /**
 * @brief counts available penguins
 *
 * This function counts the amount of available penguins, of a current player, that can
 * make a move.
 *
 * @param g Pointer to the structure that saves the state of the Game
 *
 * @return Returns a number of penguins
 */
int count_available_penguins(GameState *g);

 /**
 * @brief saves tiles of available penguins
 *
 * This function saves the parameters of tiles of penguins, of a player, that can make a move
 *
 * @param g Pointer to the structure that saves the state of the Game
 *
 * @return Returns a pointer to the tile of the available penguin
 */
Tile *available_penguins(GameState *g);

#endif //ALGORITHM_H