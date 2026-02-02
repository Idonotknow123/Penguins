#ifndef PLAY_AUTONOMOUS_H
#define PLAY_AUTONOMOUS_H
#include "structures.h"

/**
 * @brief Executes the game logic based on the provided arguments and game state.
 *
 * This function processes command-line arguments, sets up the game state, and handles
 * different phases of the game (e.g., "placement" or "movement"). It reads input files,
 * processes player information, and outputs results to the console and/or specified files.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @param game A pointer to the current game state structure.
 *
 * Command-line arguments:
 * - `phase=`: Specifies the phase of the game ("placement" or "movement").
 * - `penguins=`: Number of penguins to place (used in "placement" phase).
 * - `name`: Prints the program name and exits.
 * - Input and output file paths: The 2nd, 3rd, or 4th argument is treated as input/output files.
 *
 * Functionality:
 * - Parses the command-line arguments and initializes the game settings.
 * - Reads player information from the input file.
 * - Prints player details, game grid, and other settings to the console.
 * - Handles the "placement" and "movement" phases of the game.
 * - Writes the updated game state to the specified output file.
 *
 * Error handling:
 * - Validates the correctness of arguments based on the specified phase.
 * - Prints error messages for incorrect arguments or unknown phases.
 *
 * Example usage:
 * ```
 * ./game phase=placement penguins=5 input.txt output.txt
 * ```
 *
 * Dependencies:
 * - Requires `printProgramName`, `process_file`, `assign_programm_variables`, and `write_to_file` functions.
 */
int play_autonomous(int argc, char* argv[], GameState* game);

#endif //PLAY_AUTONOMOUS_H