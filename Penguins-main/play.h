#ifndef PLAY_H
#define PLAY_H

#include "structures.h"

/**
* play.h contains declarations of functions that are related to the game phases
* i.e. playing the manual/autonomous mode of the game. Playing the placement/movement phase
* etc.
*/
/**
* @brief plays the manual version of the game
*
* This function plays the manual version of the game (player vs player).
* Asks for the dimensions to generate board, for the number of players, penguins per player.
*
* @param g Pointer to the structure that saves the state of the Game
*/
void play_manual(GameState *g);

/**
* @brief prints the board
*
* This function prints the current state of the board with use of colors
* columns are marked as letters A, B, C etc.
* rows are marked as numbers 1, 2 ,3 etc.
*
* @param g Pointer to the structure that saves the state of the Game
*/
void show_board(GameState *g);

/**
* @brief generates the board
*
* This function generates the board. Assigns to our two-dimensional table grid
* of a tile type some specific values, that are later used (for example the
* information if the specific tile is a sea tile or an ice floe, if it
* has a penguin placed on it and which player's it would be, the amount of fish
* on the tile)
*
* @param g Pointer to the structure that saves the state of the Game
*/
void generate_board(GameState *g);

/**
* @brief plays the placement phase of the game
*
* This function plays the placement phase of the game. It makes player enter parameters to
* place his penguins (by typing a tile's parameters, for example A2, B4 etc.)
* on the board while there are still penguins left to place (while the number of placed penguins is lower
* than the full number of penguins).
* It checks if the chosen tile is already taken by another penguin or whether it's a sea tile or not.
*
* @param g Pointer to the structure that saves the state of the Game
*/
void play_placement(GameState *g);

/**
* @brief plays the movement phase of the game
*
* This function plays the movement phase of the game. It's playing for as long as any player
* can still make a valid move. It lets a specific player choose a penguin of theirs and if it's a
* valid choice, then it lets the player choose a tile to move the penguin to, and checks if it's a
* valid choice.
* If no player can make a move, the movement phase stops.
* if a specific player can't make any valid move, then he's skipped by the program
* (he can't choose or move any penguin anymore, he's not given a choice)
*
* @param g Pointer to the structure that saves the state of the Game
*/
void play_movement(GameState *g);

 /**
 * @brief Change the current player
 *
 * This function simply changes the current player to the next one, if it gets to the
 * last player, it then changes again to the first one.
 *
 * @param g Pointer to the structure that saves the state of the Game
 */
void change_current_player(GameState *g);

 /**
 * @brief Announce the score after the game ends
 *
 * This function announces the final scores after the game ends.
 * Also announces who's the winner or if there's a tie.
 *
 * @param g Pointer to the structure that saves the state of the Game
 */
void announce_score(GameState *g);

#endif //PLAY_H