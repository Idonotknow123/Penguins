#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "valid_check.h"
#include "print.h"
#include "play.h"
#include "grid.h"
// #include "unit_test.h"

void play_manual(GameState *g) {
    // set type to manual
    g->type = 0;
    // scan parameters
    int temp[4];
    printf("\033[0;32mENTER GAME PARAMETERS\033[0;0m\n");
    printf("columns: ");
    scanf("%d", &temp[0]);
    printf("rows: ");
    scanf("%d", &temp[1]);
    printf("players: ");
    scanf("%d", &temp[2]);
    printf("penguins per player: ");
    scanf("%d", &temp[3]);
    // initialize game
    g->columns = temp[0];
    g->rows = temp[1];
    g->players_nr = temp[2];
    g->penguins_per_player = temp[3];
    g->penguins_nr = 0;
    // allocate memory
    g->grid = malloc(g->rows * g->columns * sizeof(Tile));
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->columns; j++) {
            g->grid[i] = malloc(g->columns * sizeof(Tile));
        }
    };
    // initialize grid
    for (int i = 0; i < g->columns; i++) {
        for (int j = 0; j < g->rows; j++) {
            g->grid[i][j] = (Tile) {
                .x = i,
                .y = j,
                .is_penguin = 0,
                .player_id = 0,
                .is_sea = 0,
                .fish_nr = 0
            };
        }
    }
    // initialize players
    for (int i = 0; i < g->players_nr; i++) {
        g->players[i] = (Player) {
            .id = i + 1,
            .fish_nr = 0,
            .penguins_nr = 0
        };
    }
    // set current player
    g->current_player = g->players[0].id;
    // play
    generate_board(g);
    play_placement(g);
    play_movement(g);
    announce_score(g);
    // free memory
    for (int i = 0; i < g->rows; i++) {
        free(g->grid[i]);
    };
    free(g->grid);
};

void show_board(GameState *g) {
    // calculating number of spaces given the row number (prevents offset)
    const int space = floor(log10(g->rows + 1)) + 1;
    for (int s = 0; s < space + 1; s ++) {
        printf(" ");
    }
    for (int i = 0; i < g->columns; i ++) {
        printf("\033[0;31m%c \033[0;0m", i + 'A');
    }
    printf("\n");
    for (int i = 0; i < g->rows; i ++) {
        printf("\033[0;31m%i \033[0;0m", i + 1);
        for (int s = 0; s < space - log10(floor(i) + 1) - 1; s++) {
            printf(" ");
        }
        for (int j = 0; j < g->columns; j ++) {
            draw_tile(g, g->grid[j][i]);
        }
        printf("\n");
    }
}

void generate_board(GameState *g) {
    int required_ones = g->penguins_per_player * g->players_nr;
    int placed_ones = 0;
    // placing enough 1s
    while (placed_ones < required_ones) {
        int x=rand() % g->columns;
        int y=rand() % g->rows;
        if (g->grid[x][y].fish_nr != 1) {
            g->grid[x][y] = (Tile) {
                .x=x,
                .y=y,
                .is_penguin=0,
                .player_id=0,
                .is_sea=0,
                .fish_nr=1
            };
          placed_ones++;
          }
    }
    for (int i = 0; i < g->columns; i++) {
        for (int j = 0; j < g->rows; j++) {
            if (g->grid[i][j].fish_nr != 1) {
                g->grid[i][j] = (Tile)
                {
                    .x = i,
                    .y = j,
                    .is_penguin = 0,
                    .player_id = 0,
                    .is_sea = rand() % 2,
                    .fish_nr = rand() % 3 + 1
                };
            }
        }
    }
    printf("\033[0;32mBOARD GENERATED\033[0;0m\n");
}

void play_placement(GameState *g) {
    int x = 0, y = 0;
    for (int i = 0; i < g->penguins_per_player * g->players_nr; i++) {
        show_board(g);
        printf("\033[0;32mPLAYER %d\033[0;0m (place your penguin)\n", g->current_player);
        input:
        enter_values(&x, &y);
        if (are_coordinates_valid(g, x, y) && g->grid[x][y].fish_nr == 1) {
            place_penguin(g, g->grid[x][y]);
            change_current_player(g);
        } else {
            printf("\033[0;31mYou can't place there, choose different tile\033[0;0m\n");
            goto input;
        }
    }
}

void play_movement(GameState *g) {
    int x = 0, y = 0, x2 = 0, y2 = 0;
    while (can_any_player_make_a_move(g)) {
        if (can_given_player_make_a_move(g, g->current_player)) {
            show_board(g);
            printf("\033[0;32mPLAYER %d\033[0;0m (penguin to move)\n", g->current_player);
            do {
                enter_values(&x, &y);
            } while (!is_chosen_penguin_valid(g, x, y) && x!=-1);
            g->grid[x][y].is_selected = 1;
            show_board(g);
            printf("\033[0;32mPLAYER %d\033[0;0m (tile to move to)\n", g->current_player);
            do {
                enter_values(&x2, &y2);
            } while (!is_move_valid(g, x, y, x2, y2));
            g->grid[x][y].is_selected = 0;
            move_penguin(g, g->grid[x][y], g->grid[x2][y2]);
        }
        change_current_player(g);
    }
    show_board(g);
    printf("\033[0;32m""GAME FINISHED\033[0;0m\n");
}

void change_current_player(GameState *g) {
    g->current_player = g->current_player % g->players_nr + 1;
}

void announce_score(GameState *g) {
    int max = 0;
    int winner = 0;
    for (int i = 0; i < g->players_nr; i++) {
        printf("PLAYER %d's score: %d\n", g->players[i].id, g->players[i].fish_nr);
        if (max < g->players[i].fish_nr) {
            max = g->players[i].fish_nr;
            winner = g->players[i].id;
        }
    }
    int tie = 0;
    for (int i = 0; i<g->players_nr; i++) {
        if (g->players[i].id != winner && g->players[i].fish_nr == max) {
            printf("\033[0;33mTIE\033[0;0m\n");
            tie = 1;
        }
    }
    if (tie == 0) {
        printf("\033[0;32mWINNER: PLAYER %d\033[0;0m\n", winner);
    }
}