#ifndef VALID_CHECK_H
#define VALID_CHECK_H

#include "structures.h"

 /**
 *valid_check.h contains declarations of all functions related to
 *checking the validity of the move, chosen tile etc.
 *
 */

 /**
 * @brief checks if coordinates are valid
 *
 * This function checks given coordinates if they're inside the boundaries and
 * if they're ice floe tiles
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param x X coordinate of the tile
 * @param y Y coordinate of the tile
 *
 * @return Returns 1 if coordinates are valid, 0 if they're not
 */
int are_coordinates_valid(GameState *g, int x, int y);

 /**
 * @brief check if penguin can make a move
 *
 * This function checks if penguin can make a move using are_coordinates_valid
 * function for checking surrounding tiles if at least one is an ice floe
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param t A specific tile
 *
 * @return Returns 1 if penguin can make a move, and 0 if it cannot
 */
int can_make_a_move(GameState *g, Tile t);

 /**
 * @brief checks if the chosen penguin is valid
 *
 * This function checks if the chosen penguin is of the player that's currently choosin*g,
 * if the penguin is able to make any move, if the chosen tile is inside the bounds,
 * and if the chosen tile is even a penguin
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param x X parameter of the tile of chosen penguin
 * @param y Y parameter of the tile of chosen penguin
 *
 * @return Returns 1 if the penguin is valid, and 0 if it's not
 */
int is_chosen_penguin_valid(GameState *g, int x, int y);

 /**
 * @brief Check if this player can make any move
 *
 * This function checks if current player is able to make any move, i.e. if the player
 * has any penguins on the board that have at least 1 ice floe tile next to them
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param player ID of a player
 *
 * @return Returns 1 if the player can make a move, 0 if they can't
 */
int can_given_player_make_a_move(GameState *g, int player);

 /**
 * @brief Checks if any player can make a move
 *
 * This function checks if any player is able to make any move, i.e. if there's
 * any penguin on the board that can make a valid move
 *
 * @param g Pointer to the structure that saves the state of the Game
 *
 * @return Returns 1 if there's a player that can make a valid move, 0 if there's
 * no such player
 */
int can_any_player_make_a_move(GameState *g);

 /**
 * @brief Checks if chosen move is valid
 *
 * This functions checks if a specific penguin can move to the chosen tile.
 * It checks if it's not a diagonal move (only straight line movement is allowed),
 * if the penguin would move over a sea tile or another penguin to get to the chosen tile.
 *
 * @param g Pointer to the structure that saves the state of the Game
 * @param x1 X coordinate of chosen penguin
 * @param y1 Y coordinate of chosen penguin
 * @param x2 X coordinate of chosen tile to move to
 * @param y2 Y coordinate of chosen tile to move to
 * @return Returns 0 if the conditions are not satisfied (i.e. move not valid), and
 * 1 if they're satisfied (valid move)
 */
int is_move_valid(GameState *g, int x1, int y1, int x2, int y2);

#endif //VALID_CHECK_H