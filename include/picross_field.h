#pragma once

#include "stdinc.h"

#define PICROSS_TILE_SIZE      5
#define PICROSS_NB_TILE        3
#define PICROSS_GRID_SIZE      (PICROSS_TILE_SIZE * PICROSS_NB_TILE)

enum squareState{SS_UNKNOWN, SS_MARKED_FILLED, SS_MARKED_EMPTY};


typedef struct {
    uint8_t board[PICROSS_GRID_SIZE][PICROSS_GRID_SIZE];
    uint8_t solution[PICROSS_GRID_SIZE][PICROSS_GRID_SIZE];

    uint8_t xLabels[PICROSS_GRID_SIZE][PICROSS_GRID_SIZE / 2]; // divided by two cuz on a 15 by 15 grid;
    uint8_t yLabels[PICROSS_GRID_SIZE][PICROSS_GRID_SIZE / 2]; // the max amount of label is 1, 1, 1, ... 1, 15 / 2 times 
    uint8_t max_nb_label_x;
    uint8_t max_nb_label_y;
    
    uint8_t life;
    bool isRunning;
} picross_field;

void _picross_field_getLabels(picross_field* pf);

void picross_field_load(picross_field* pf, FILE* f);
void picross_field_init(picross_field* pf);
uint8_t picross_field_make_move(picross_field* pf, uint8_t x, uint8_t y, uint8_t state);
void picross_field_print_ascii(picross_field* pf);