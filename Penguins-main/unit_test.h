#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include "structures.h"

 /**
 * @brief checks if the function "are_coordinates_valid" functions well
 *
 * This function checks whether "are_coordinates_valid" function
 * works well. We assign some specific cases in this test function
 * to check some border cases. It will stop the program if it finds a problem.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 */
void test_are_coordinates_valid(GameState *g);

 /**
 * @brief checks if the function "is_chosen_penguin_valid" functions well
 *
 * This function checks whether "is_chosen_penguin_valid" function
 * works well. We assign some specific cases in this test function
 * to check some border cases. It will stop the program if it finds a problem.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 */
void test_is_chosen_penguin_valid(GameState *g);

 /**
 * @brief checks if the function "can_make_a_move" functions well
 *
 * This function checks whether "can_make_a_move" function
 * works well. We check for two penguins that are placed in
 * the test GameState. It will stop the program if it finds a problem.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 */
void test_can_make_a_move(GameState *g);

 /**
 * @brief checks if the function "can_given_player_make_a_move" functions well
 *
 * This function checks whether "can_given_player_make_a_move" function
 * works well. We check for two players, 1st can't make a move, 2nd can.
 * It will stop the program if it finds a problem.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 */
void test_can_given_player_make_a_move(GameState *g);

 /**
 * @brief checks if the function "can_any_player_make_a_move" functions well
 *
 * This function checks whether "can_any_player_make_a_move" function
 * works well. We check for two players, one can't and one can make a move.
 * It will stop the program if it finds a problem.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 */
void test_can_any_player_make_a_move(GameState *g);

 /**
 * @brief checks if the function "is_move_valid" functions well
 *
 * This function checks whether "is_move_valid" function
 * works well. We check various cases for two penguins, one cant make a move at all.
 * For the second one we check various cases (make sure that it can't move diagonally,
 * that it doesn't jump over the sea, that it can't be placed at the same place it is standing on etc.)
 * It will stop the program if it finds a problem.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 */
void test_is_move_valid(GameState *g);

 /**
 * @brief checks if the function "count_available_moves" functions well
 *
 * This function checks whether "count_available_moves" function
 * works well. We check various cases for two penguins, one cant make a move at all.
 * Second one can make some moves.
 * It will stop the program if it finds a problem.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 */
void test_count_available_moves(GameState *g);

 /**
 * @brief generates a fixed board solely for testing
 *
 * This function generates a fixed board, just for testing.
 * 3 rows and 3 columns, ice and sea tiles in some specific places,
 * also places 2 penguins.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 *
 */
void test_generate(GameState *g);

 /**
 * @brief this function performs the tests of different functions in our code
 *
 * This function performs tests of various functions in our code,
 * ensuring that they work correctly and writing the results of the tests
 * in a file "test_results.txt".
 * It will print "....passed" if the test was passed.
 *
 * @param g Is a pointer to the state of the game (that for tests we
 * generate a fixed board (the fish aren't generated randomly)
 *
 */
void test(GameState *g);

#endif //UNIT_TEST_H