#ifndef PRINT_H
#define PRINT_H

/**
 * @brief Converts a character array of digits into an integer.
 *
 * This function takes a character array that represents a sequence of 
 * numeric digits (e.g., "123") and converts it into its corresponding integer value.
 * It stops processing when a non-digit character is encountered or at the null terminator.
 *
 * @param word Character array containing numeric digits.
 * @return Returns the integer value of the input character array.
 */
int string_to_integer(const char word[]);

/**
 * @brief Finds the position of the first letter in a given word.
 *
 * This function searches through the input character array to find the 
 * position of the first letter (either uppercase or lowercase).
 * The position is stored as a 1-based index.
 *
 * @param word Character array to search for a letter.
 * @return Returns the position (1-based) of the first letter if found, 
 *         or 0 if no letter is found.
 */
int wheres_letter(char word[]);

/**
 * @brief Clears the console screen.
 *
 * This function clears the console screen using the `system("cls")` command.
 * It is platform-dependent and works primarily on Windows, but with small adjustments it can work on another platforms as well
 */
void clear_background();

/**
 * @brief Parses user input to extract tile coordinates.
 *
 * This function reads a string from the user, validates it, and extracts
 * the X and Y coordinates of a tile. It uses other helper functions to find
 * the position of the first letter and convert numeric parts to integers.
 *
 * @param xp Pointer to store the X coordinate of the tile.
 * @param yp Pointer to store the Y coordinate of the tile.
 */
void enter_values(int *xp, int *yp);

#endif //PRINT_H