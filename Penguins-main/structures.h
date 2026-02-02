#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdbool.h>

typedef struct Tile {
    int x, y; // coordinates
    bool is_sea; // is there an ice floe?
    bool is_penguin; // is penguin on the ice floe? (applicable if is_sea == False)
    int fish_nr; // how many fish are there (applicable if is_sea == False)
    int player_id; // player's id (applicable if is_penguin == True)
    bool is_selected; // is tile selected? (feature in manual game: movement phase)
} Tile;

typedef struct Player {
    int id; // player's id
    int penguins_nr; // number of player's penguins
    int fish_nr; // number of fish eaten by player's penguins
    char name[107]; // player's name
} Player;

typedef struct GameState{
    int type; // 0 for manual, 1 for autonomous
    int columns, rows; // dimensions
    int penguins_nr; // number of penguins on the board
    int current_player; // player to make a move/placement
    int players_nr; // total number of players
    int penguins_per_player; // number of penguins each player has control of
    Tile **grid; // two-dimensional array of tiles
    Player players[]; // array of players playing the game
} GameState;

#endif //STRUCTURES_H