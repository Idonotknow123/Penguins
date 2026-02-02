#ifndef AUTONOMOUS_H
#define AUTONOMOUS_H

#include "structures.h"

/**
 * @brief Extracts the program name from its file path.
 *
 * This function parses the file path of the program and extracts the program's name
 * without the file extension. It supports paths using both forward (/) and backward (\) slashes.
 *
 * @param programPath The full path to the program executable.
 * @return A dynamically allocated string containing the program name without extension.
 *         The caller is responsible for freeing the allocated memory.
 * @note If the program path does not include an extension or slashes, the entire string is returned.
 */
char* printProgramName(const char *programPath);

/**
 * @brief Loads the state of a game from a specified file.
 *
 * This function reads the game state from a text file and initializes the `GameState` structure.
 * The file should contain the grid dimensions, grid data, and player information in the following format:
 * - First line: Number of rows and columns.
 * - Following lines: Grid data (fish count and player ID for each cell, encoded as `fish_nr * 10 + player_id`).
 * - Remaining lines: Player information (name, ID, and total fish count for each player).
 *
 * @param filename A string representing the name of the file containing the saved game state.
 * @param game A pointer to the `GameState` structure to initialize with the loaded data.
 *
 * @note The function will terminate the program with an exit code of 2 if any errors occur (file issues, 
 * memory allocation failures, or invalid file format).
 * @warning Ensure the file exists and is formatted correctly, and check for potential memory leaks when reallocating 
 * or initializing the game grid. (solved later in free function)
 *
 * Errors handled:
 * - Failure to open the file.
 * - Invalid or incomplete grid dimensions or data.
 * - Memory allocation failures.
 * - Exceeding the maximum number of players.
 */
void load_game_state_from_file(const char* filename, GameState* game);

/**
 * @brief Writes the state of a game to a specified file.
 *
 * This function saves the current game state, including the grid dimensions,
 * grid details, and player information, to a text file. The format of the file is:
 * - First line: Number of rows and columns.
 * - Following lines: Grid information (number of fish and player ID for each cell).
 * - Last section: Player information (name, ID, and total fish count for each player).
 *
 * @param filename A string representing the name of the file to save the game state to.
 * @param game A pointer to the `GameState` structure containing the game's state.
 *
 * @note The function terminates the program with an exit code of 2 if the file cannot be opened.
 * @warning Ensure that the `filename` is valid and writable.
 */
void put_to_file(const char* filename, GameState* game);

/**
 * @brief Checks if a player exists in the game state and performs necessary updates or validations.
 *
 * This function verifies whether a player with the specified name exists in the game state. If the player
 * is not found and the phase is "placement", a new player is added to the game. If the phase is "movement"
 * and the player is not found, the program exits with an error. The function also checks for duplicate
 * player names or IDs in the game state.
 *
 * @param g Pointer to the current game state.
 * @param name_of_program The name of the program or player to check.
 * @param ph The phase of the game ("placement" or "movement").
 *
 * @note The function assumes a maximum of 10 players in the game. If this limit is exceeded, the program exits.
 *
 * @warning If duplicate player names or IDs are detected, the program will terminate.
 * @warning If no valid ID can be assigned to a new player, the program will terminate.
 */
void check_for_player(GameState *g, const char *name_of_program, char *ph);

#endif //AUTONOMOUS_H