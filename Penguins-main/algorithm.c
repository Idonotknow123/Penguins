#include <stdio.h>
#include <stdlib.h>

#include "valid_check.h"
#include "algorithm.h"
#include "grid.h"

void make_a_move(GameState *g) {
    // initializing depth
    int d = 2;
    // performing calculations
    int pc = count_available_penguins(g);
    if (pc != 0) {
        Tile *best_move = NULL;	
        Tile *best_penguin = NULL;
        Tile *penguins = available_penguins(g);
        Tile *penguin = penguins;
        int dominant_val = 0;
        int first_val = 0;
        for (int p = 0; p < pc; p++) {
        //printf("p: %d\n", p);
            int mc = count_available_moves(g, *penguin);
            Tile *moves = available_moves(g, *penguin);
            for (int m = 0; m < mc; m++) {
                int val =  potential(g, moves[m], d);
                if (val > dominant_val) {
                    dominant_val = val;
                    /*if (moves[m].fish_nr > first_val) {
                        first_val = moves[m].fish_nr;
                    }*/
                    best_move = &moves[m];
                    best_penguin = &penguins[p];
                    //best_move = &moves[m];
                }
                //free(moves);
            }
        }
        // adding fish
        for (int i = 0; i < 10; i++) {
            if (g->players[i].id == g->current_player) {
                g->players[i].fish_nr += best_move->fish_nr;
                break;
            }
        }
        // making a move
        move_penguin(g, *best_penguin, *best_move);
        free(penguins);
    }
}

void make_a_placement(GameState *g) {
    int d = 4;
    int dominant_val = 0;
    Tile *best_place = NULL;
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->columns; j++) {
            Tile *sample = &g->grid[i][j];
            if (g->grid[i][j].fish_nr == 1) {
                Tile *moves = available_moves(g, *sample);
                int val = potential(g, *sample, d);
                if (val > dominant_val) {
                    dominant_val = val;
                    best_place = sample;
                }
                free(moves);
            }
        }
    }
    // adding fish
    for (int i = 0; i < 10; i++) {
        if (g->players[i].id == g->current_player) {
            g->players[i].fish_nr += best_place->fish_nr;
            break;
        }
    }
    // making a placement
    place_penguin(g, *best_place);
}

int potential(GameState *g, Tile t, int depth) {
    // initializing raw value for the tile
    int raw_val = t.fish_nr;
    int c = count_available_moves(g, t);
    // check preventing infinite loop
    if (depth == 0 || c == 0) {
        return raw_val;
    }
    Tile *moves = available_moves(g, t);
    int max_val = 0;
    for (int i = 0; i < c; i++) {
        Tile temp = g->grid[moves[i].x][moves[i].y];
        move_penguin(g, t, moves[i]);
        // recursive call
        int val = potential(g, moves[i], depth - 1);
        if (val > max_val) {
            max_val = val;
        }
        // undoing the move (line 59)
        place_penguin(g, t);
        g->grid[moves[i].x][moves[i].y] = temp;
    }
    g->grid[t.x][t.y] = t;
    free(moves);
    return max_val + raw_val;
}

int count_available_moves(GameState *g, Tile t) {
    int count = 0, i = 1;
    // up
    while (are_coordinates_valid(g, t.x + i, t.y)) {
       i++; count++;
    }
    // down
    i = 1;
    while (are_coordinates_valid(g, t.x - i, t.y)) {
        i++; count++;
    }
    // left
    i = 1;
    while (are_coordinates_valid(g, t.x, t.y - i)) {
        i++; count++;
    }
    // right
    i = 1;
    while (are_coordinates_valid(g, t.x, t.y + i)) {
        i++; count++;
    }
    return count;
}

Tile *available_moves(GameState *g, Tile t) {
    int c = count_available_moves(g, t);
    Tile *ret = malloc(sizeof(Tile) * (c));
    if (ret == NULL) {
        return NULL;
    }
    int res = 0;
    // up
    int up = 1;
    while (are_coordinates_valid(g, t.x + up, t.y)) {
        Tile q = g->grid[t.x + up][t.y];
        ret[res++] = q;
        up++;
    }
    // down
    int down = 1;
    while (are_coordinates_valid(g, t.x - down, t.y)) {
        Tile q = g->grid[t.x - down][t.y];
        ret[res++] = q;
        down++;
    }
    // left
    int left = 1;
    while (are_coordinates_valid(g, t.x,t.y - left)) {
        Tile q = g->grid[t.x][t.y - left];
        ret[res++] = q;
        left++;
    }
    // right
    int right = 1;
    while (are_coordinates_valid(g, t.x, t.y + right)) {
        Tile q = g->grid[t.x][t.y + right];
        ret[res++] = q;
        right++;
    }
    return ret;
}

int count_available_penguins(GameState *g) {
    int count = 0;
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->columns; j++) {
            Tile q = g->grid[i][j];
            if (q.player_id == g->current_player && can_make_a_move(g, q)) {
                count++;
            }
        }
    }
    return count;
}

Tile *available_penguins(GameState *g) {
    int c = count_available_penguins(g);
    Tile *ret = malloc(sizeof(Tile) * c);
    if (ret == NULL) {
        return NULL;
    }
    int res = 0;
    for (int i = 0; i < g->rows; i++) {
        for (int j = 0; j < g->columns; j++) {
            Tile q = g->grid[i][j];
            if (q.player_id == g->current_player && can_make_a_move(g, q)) {
                ret[res++] = q;
            }
        }
    }
    return ret;
}