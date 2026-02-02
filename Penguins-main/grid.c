#include <stdio.h>

#include "grid.h"

void draw_tile(GameState *g, Tile t) {
    if (!g->grid[t.x][t.y].is_sea) {
        if (g->grid[t.x][t.y].is_penguin) {
            if (!g->grid[t.x][t.y].is_selected) {
                printf("\033[0;33m%i \033[0;0m", g->grid[t.x][t.y].player_id);
            } else {
                printf("\033[0;32m%i \033[0;0m", g->grid[t.x][t.y].player_id);
            }
        } else {
            printf("%i ", g->grid[t.x][t.y].fish_nr);
        }
    } else {
        printf("_ ");
    }
}

void place_penguin(GameState *g, Tile t) {
    g->grid[t.x][t.y].is_penguin = 1;
    g->grid[t.x][t.y].player_id = g->current_player;
    if (g->type == 0) {
        g->players[g->current_player-1].fish_nr += g->grid[t.x][t.y].fish_nr;
    }
    g->grid[t.x][t.y].fish_nr = 0;
}

void remove_tile(GameState *g, Tile t) {
    g->grid[t.x][t.y].is_penguin = 0;
    g->grid[t.x][t.y].is_sea = 1;
    g->grid[t.x][t.y].fish_nr = 0;
    if (g->type == 0) {
        g->grid[t.x][t.y].player_id = -1;
    } else {
        g->grid[t.x][t.y].player_id = 0;
    }
}

void move_penguin(GameState *g, Tile t, Tile t_move) {
    place_penguin(g, t_move);
    remove_tile(g, t);
}