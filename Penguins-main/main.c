#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "autonomous_output.h"
#include "play.h"
#include "structures.h"
// #include "unit_test.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // unit test
    /*
    GameState* testgame = malloc(sizeof(GameState) + 10 * sizeof(Player));
    if (testgame == NULL){
        printf("Memory allocation failed for testgame\n");
        exit(1);
    }
    test_generate(testgame);
    test(testgame);
    for (int i = 0; i < testgame->rows; i++){
        free(testgame->grid[i]);
    }
    free(testgame->grid);
    free(testgame);
	*/
    // end of unit test

    GameState *game = malloc(sizeof(GameState) + 10 * sizeof(Player)); // assuming players_nr <= 10
    if (argc == 1) {
        play_manual(game);
    } else {
        return play_autonomous(argc, argv, game);
    }
    free(game);
    return 0;
}