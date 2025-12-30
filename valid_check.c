#include <stdio.h>

#include "valid_check.h"

/**
valid_check.c contains all functions that are related to checking the validity of
a move, chosen tile etc.
*/

int are_coordinates_valid(GameState *g, int x, int y) {
if(g->type==0)
{
    if (x < 0 || x>=g->columns || y < 0 || y >= g->rows) {
        return 0;
    }
    if (g->grid[x][y].is_penguin == 1 || g->grid[x][y].is_sea == 1) {
        return 0;
    }
    return 1;
}
else
{
    if (x < 0 || x>=g->rows || y < 0 || y >= g->columns) {
        return 0;
    }
    if (g->grid[x][y].is_penguin == 1 || g->grid[x][y].is_sea == 1) {
        return 0;
    }
    return 1;
}
}

int can_make_a_move(GameState *g, Tile t) {
    if (are_coordinates_valid(g, t.x + 1, t.y) || are_coordinates_valid(g, t.x - 1, t.y) ||
        are_coordinates_valid(g, t.x, t.y + 1) || are_coordinates_valid(g, t.x, t.y - 1)) {
        return 1;
    }
    return 0;
}

int is_chosen_penguin_valid(GameState *g, int x, int y) {
    if (x >= g->columns || y >= g->rows || y < 0 || x < 0) {
        printf("\033[0;31m""out of bounds\033[0;0m\n");
        return 0;
    }
    if (g->grid[x][y].is_penguin && g->grid[x][y].player_id == g->current_player) {
        if (can_make_a_move(g, g->grid[x][y])) {
            return 1;
        }
        printf("\033[0;31m""penguin can't make a move\033[0;0m\n");
        return 0;
    }
    if (g->grid[x][y].is_penguin && g->grid[x][y].player_id != g->current_player) {
        printf("\033[0;31m""not your penguin\033[0;0m\n");
        return 0;
    }
    printf("\033[0;31m""not a penguin\033[0;0m\n");
    return 0;
}

int can_given_player_make_a_move(GameState *g, int player) {
    for (int i = 0; i < g->columns; i++) {
        for (int j = 0; j < g->rows; j++) {
            if (g->grid[i][j].player_id == player) {
                if (can_make_a_move(g, g->grid[i][j])) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int can_any_player_make_a_move(GameState *g) {
    for (int pl = 0; pl < g->players_nr; pl++) {
        if (can_given_player_make_a_move(g, pl+1)) {
            return 1;
        }
    }
    return 0;
}

int is_move_valid(GameState *g, int x1, int y1, int x2, int y2) {
    if (x1 != x2 && y1 != y2) {
        printf("\033[0;31m""move invalid\033[0;0m\n");
        return 0;
    }
    if (!are_coordinates_valid(g, x2, y2)) {
        printf("\033[0;31m""move invalid\033[0;0m\n");
        return 0;
    }
    if (x1 != x2 && x1 < x2) {
        for(int i = x1 + 1; i < x2; i++) {
            if(g->grid[i][y1].is_penguin || g->grid[i][y1].is_sea) {
                printf("\033[0;31m""move invalid\033[0;0m\n");
              return 0;
            }
        }
    }
    if (x1 != x2 && x1 > x2) {
        for (int i = x1 - 1; i > x2; i--) {
            if (g->grid[i][y1].is_penguin || g->grid[i][y1].is_sea) {
                printf("\033[0;31m""move invalid\033[0;0m\n");
                return 0;
            }
        }
    }
    if (y1 != y2 && y1 < y2) {
        for (int i = y1 + 1; i < y2; i++) {
            if (g->grid[x1][i].is_penguin || g->grid[x1][i].is_sea) {
                printf("\033[0;31m""move invalid\033[0;0m\n");
              return 0;
            }
        }
    }
    if (y1 != y2 && y1 > y2) {
        for (int i = y1 - 1; i > y2; i--) {
            if (g->grid[x1][i].is_penguin || g->grid[x1][i].is_sea) {
                printf("\033[0;31m""move invalid\033[0;0m\n");
                return 0;
            }
        }
    }
    return 1;
}