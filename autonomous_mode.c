#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "structures.h"

char *printProgramName(const char *programPath) {
    char *result = malloc((strlen(programPath) + 1) * sizeof(char));
    const char *programName = strrchr(programPath, '/');
    if (programName == NULL) {
        programName = strrchr(programPath, '\\');
    }
    if (programName == NULL) {
        programName = programPath;
    } else {
        programName++;
    }
	for (int i = 0; i < strlen(programName); i++) {
		if (programName[i] == '.')  {
		break;
		}
    	result[i] = programName[i];
	}
    result[strlen(programName)] = '\0';
	return result;
}

void load_game_state_from_file(const char* filename, GameState* game) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(2);
    }
    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        fprintf(stderr, "Error reading grid dimensions\n");
        fclose(file);
        exit(2);
    }
    game->grid = malloc(rows * sizeof(Tile*));
    if (!game->grid) {
        perror("Memory allocation failed");
        fclose(file);
        exit(2);
    }
    for (int i = 0; i < rows; ++i) {
        game->grid[i] = malloc(cols * sizeof(Tile));
        if (!game->grid[i]) {
            perror("Memory allocation failed");
            fclose(file);
            exit(2);
        }
    }
    game->rows = rows;
    game->columns = cols;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
        int value;
            if (fscanf(file, "%d", &value) != 1) {
                fprintf(stderr, "Error reading grid data\n");
                fclose(file);
                exit(2);
            }
            game->grid[i][j].x = i;
            game->grid[i][j].y = j;
            if (value % 10 != 0 && value / 10 != 0) {
                printf("Something's wrong. Fish and penguin on the same tile [%d][%d]\n", i, j);
                exit(2);
                // game->grid[i][j].fish_nr = 0;
            }
            game->grid[i][j].fish_nr = value / 10;
            game->grid[i][j].player_id = value % 10;
            game->grid[i][j].is_penguin = game->grid[i][j].player_id != 0;
            game->grid[i][j].is_sea = game->grid[i][j].fish_nr == 0;
            game->grid[i][j].is_selected = 0;
        }
    }
    game->players_nr = 0;
    while (fscanf(file, "%s %d %d", game->players[game->players_nr].name, &game->players[game->players_nr].id, &game->players[game->players_nr].fish_nr) == 3) {
        if (game->players_nr >= 10) {
            fprintf(stderr, "Maximum number of players exceeded\n");
            fclose(file);
            exit(2);
        }
    game->players[game->players_nr].penguins_nr = 0;
    game->players_nr++;
    }
    fclose(file);
}

void put_to_file(const char* filename, GameState* game) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        exit(2);
    }
    fprintf(file, "%d %d\n", game->rows, game->columns);
    for (int i = 0; i < game->rows; ++i) {
        for (int j = 0; j < game->columns; ++j) {
            fprintf(file, "%d%d ", game->grid[i][j].fish_nr, game->grid[i][j].player_id);
        }
        fprintf(file, "\n");
    }
    for (int i=0; i<game->players_nr; i++) {
        fprintf(file, "%s %d %d\n", game->players[i].name, game->players[i].id, game->players[i].fish_nr);
    }
    fclose(file);
}

void check_for_player(GameState *g, const char *name_of_program, char *ph) {
    bool our_player_found = false;
    for (int i = 0; i < g->players_nr; i++) {
        if (strcmp(g->players[i].name, name_of_program) == 0) {
        our_player_found = true;
            //printf("%d %s\n", i, g->players[i].name); <- to można zakomentować
            g->current_player = g->players[i].id;
        }
    }
    if (!our_player_found && strcmp(ph, "placement")==0) {
        int tab[10];
        int found_id = 0;
        for (int i = 0; i < g->players_nr; i++) {
            tab[g->players[i].id] = 1;
        }
        for (int i = 10; i > 0; i--) {
            if (tab[i] != 1) {
                found_id = i;
            }
        }
        if (found_id == 0) {
            printf("Could not assign id for a new player\n");
            exit(2);
        }
        g->current_player = found_id;
        g->players[g->players_nr].id = found_id;
        g->players[g->players_nr].fish_nr = 0;
        g->players[g->players_nr].penguins_nr = 0;
        strcpy(g->players[g->players_nr].name, name_of_program);
        g->players_nr++;
        if (g->players_nr >= 10) {
            printf("Maximum number of players exceeded\n");
            exit(2);
        }
    }
    else if (!our_player_found && strcmp(ph, "movement") == 0)
    {
        printf("Couldn't find our player\n");
        exit(2);
    }
    for (int i = 0; i < g->players_nr; i++) {
        for (int j = 0; j < i; j++) {
            if (strcmp(g->players[i].name, g->players[j].name) == 0) {
                printf("Repeating names of players!\n");
                exit(2);
            }
            if (g->players[i].id == g->players[j].id) {
                printf("Repeating ids of players!\n");
                exit(2);
            }
        }
    }
}