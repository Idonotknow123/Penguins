#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "unit_test.h"
#include "algorithm.h"
#include "play.h"
#include "valid_check.h"

void test_are_coordinates_valid(GameState *g){
    assert(are_coordinates_valid(g, -6, 58759) == 0);
    assert(are_coordinates_valid(g, -6, -58) == 0);
    assert(are_coordinates_valid(g, 97, 6) == 0);
    assert(are_coordinates_valid(g, 22, -67) == 0);

}

void test_is_chosen_penguin_valid(GameState *g){
    assert(is_chosen_penguin_valid(g, -6, 58) == 0);
    assert(is_chosen_penguin_valid(g, 0, 0) == 0);
    assert(is_chosen_penguin_valid(g, 43, -2) == 0);
    assert(is_chosen_penguin_valid(g, -1, -1) == 0);
}

void test_can_make_a_move(GameState *g){
    assert(can_make_a_move(g, g->grid[0][0]) == 0);
    assert(can_make_a_move(g, g->grid[2][2]) == 1);
}

void test_can_given_player_make_a_move(GameState *g){
    assert(can_given_player_make_a_move(g, 1) == 0);
    assert(can_given_player_make_a_move(g, 2) == 1);
}

void test_can_any_player_make_a_move(GameState *g){
    assert(can_any_player_make_a_move(g) == 1);
}

void test_is_move_valid(GameState *g){
    assert(is_move_valid(g, 0, 0, 2, 0) == 0);
    assert(is_move_valid(g, 0, 0, 0, 1) == 0);
    assert(is_move_valid(g, 0, 0, 0, 2) == 0);
    assert(is_move_valid(g, 2, 2, 2, 0) == 1);
    assert(is_move_valid(g, 2, 2, 2, 1) == 1);
    assert(is_move_valid(g, 2, 2, 2, 2) == 0);
    assert(is_move_valid(g, 2, 2, 1, 1) == 0);
    assert(is_move_valid(g, 2, 2, 0, 2) == 0);
    assert(is_move_valid(g, 2, 2, -1, 2) == 0);
    assert(is_move_valid(g, 2, 2, -1, -1) == 0);
    assert(is_move_valid(g, 2, 2, 38, 40) == 0);
}

void test_count_available_moves(GameState *g){
    assert(count_available_moves(g, g->grid[0][0]) == 0);
    assert(count_available_moves(g, g->grid[2][2]) == 2);
}

void test_generate(GameState *g){
    printf("Testing generate\n");
    g->columns=3;
    g->rows=3;
    g->players_nr=2;
    g->penguins_per_player=1;
    g->penguins_nr=2;
    g->grid = malloc(g->rows * sizeof(Tile));
    for (int i = 0; i < g->rows; i++) {
        g->grid[i]=malloc(g->columns * sizeof(Tile));
        for (int j = 0; j < g->columns; j++) {
            g->grid[i][j].x=i;
            g->grid[i][j].y=j;
            g->grid[i][j].is_penguin=0;
            g->grid[i][j].player_id = 0;
            g->grid[i][j].is_sea=0;
            g->grid[i][j].fish_nr=1;
        }
    }
    g->grid[0][0].is_penguin=1;
    g->grid[0][0].player_id=1;
    //
    g->grid[0][1].is_sea=1;
    g->grid[1][0].is_sea=1;
    //
    g->grid[2][2].is_penguin=1;
    g->grid[2][2].player_id=2;
    //
    g->grid[1][2].is_sea=1;
    printf("exiting test_generate");
}

void test(GameState *g){
    printf("entering test\n");
    show_board(g);
    FILE *file = fopen("test_results.txt", "w");
    if (file == NULL){
        fprintf(stderr, "Error opening file test_results.txt\n");
        return;
    }
    printf("File opened successfully\n");
    fflush(file);
    //
    test_is_chosen_penguin_valid(g);
    fprintf(file, "is_chosen_penguin_valid passed\n");
    //
    test_are_coordinates_valid(g);
    fprintf(file, "are_coordinates_valid passed\n");
    //
    test_can_make_a_move(g);
    fprintf(file, "can_make_a_move passed\n");
    //
    test_can_given_player_make_a_move(g);
    fprintf(file, "can_given_player_make_a_move passed\n");
    //
    test_can_any_player_make_a_move(g);
    fprintf(file, "can_any_player_make_a_move passed\n");
    //
    test_is_move_valid(g);
    fprintf(file, "is_move_valid passed\n");
    //
    test_count_available_moves(g);
    fprintf(file, "count_available_moves passed\n");
    //
    fflush(file);
    fclose(file);
    printf("exiting test function\n");
}