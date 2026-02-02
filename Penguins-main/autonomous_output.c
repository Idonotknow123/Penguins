#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "autonomous_mode.h"
#include "autonomous_output.h"
#include "algorithm.h"

int play_autonomous(int argc, char* argv[], GameState* game) {
    // set type to autonomous
    game->type = 1;
    // initialize a few things
    char phase[50] = {0};
    int penguins = 0;
    char input_file[100] = {0};
    char output_file[100] = {0};
    int is_name_present = 0;
    // treatment of command line parameters
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "phase=", 6) == 0) {
            strncpy(phase, argv[i] + 6, sizeof(phase) - 1);
        } else if (strncmp(argv[i], "penguins=", 9) == 0) {
            penguins = atoi(argv[i] + 9);
        } else if (strcmp(argv[i], "name") == 0) {
            is_name_present = 1;
        } else if (i == 2 || i == 3 || i == 4) {
            if (strlen(input_file) == 0) {
                strncpy(input_file, argv[i], sizeof(input_file) - 1);
            } else if (strlen(output_file) == 0) {
                strncpy(output_file, argv[i], sizeof(output_file) - 1);
            }
        }
    }
    // searching for our program's name
    char* name_of_program = printProgramName(argv[0]);
    if (is_name_present) {
        printf("%s", name_of_program);
        return 0;
    }
    load_game_state_from_file(input_file, game);
    check_for_player(game, name_of_program, phase);
    //
    int p = 0;
    for (int i = 1; i < game->rows; i++) {
        for (int j = 1; j < game->columns; j++) {
            if (game->current_player == game->grid[i][j].player_id) {
                p++;
            }
        }
    }
    if ((p >= penguins && strcmp(phase, "placement")==0) || (count_available_penguins(game) == 0) && strcmp(phase, "movement")==0) { 
    printf("Error, too many penguins or unable to move\n");
        return 1;
    }
    // treatment of various phases
    if (strcmp(phase, "placement") == 0) {
        if (penguins <= 0 || strlen(input_file) == 0 || strlen(output_file) == 0) {
            printf("-> %d %llu %llu\n", penguins, strlen(input_file), strlen(output_file));
            printf("Error: incorrect arguments for phase=placement.\n");
            // return 2;
        }
        // program makes a placement
        make_a_placement(game);
    } else if (strcmp(phase, "movement") == 0) {
        if (penguins != 0 || strlen(input_file) == 0 || strlen(output_file) == 0) {
            printf("Error: incorrect arguments for phase=movement.\n");
            // return 2;
        }
        // program makes a move
        make_a_move(game);
    } else {
        printf("Error: unknown argument for phase.\n");
        // return 2;
    }
    /*for (int i = 0; i < game->players_nr; i++) {
        printf("%s %d %d\n", game->players[i].name, game->players[i].id, game->players[i].fish_nr);
    }*/
    put_to_file(output_file, game);
    return 0;
}