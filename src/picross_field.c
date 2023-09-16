#include "picross_field.h"

void picross_field_load(picross_field* pf, FILE* f){
    fseek(f, 0, SEEK_SET);
    for (uint8_t y = 0; y < PICROSS_GRID_SIZE; y++){
        for (uint8_t x = 0; x < PICROSS_GRID_SIZE; x++){
            if (fgetc(f) == ' ') pf->solution[x][y] = SS_MARKED_EMPTY;
            else pf->solution[x][y] = SS_MARKED_FILLED;
        }
        if (y != PICROSS_GRID_SIZE - 1)
            fgetc(f);
    }

    _picross_field_getLabels(pf);
}

void picross_field_init(picross_field* pf){
    pf->life = 3;
    pf->isRunning = true;

    _picross_field_getLabels(pf);
    for (uint8_t y = 0; y < PICROSS_GRID_SIZE; y++)
        for (uint8_t x = 0; x < PICROSS_GRID_SIZE; x++){
            pf->board[x][y] = SS_UNKNOWN;
            pf->xLabels[x % (PICROSS_GRID_SIZE / 2)][y] = 0;
            pf->yLabels[x % (PICROSS_GRID_SIZE / 2)][y] = 0;
        }
}

uint8_t picross_field_make_move(picross_field* pf, uint8_t x, uint8_t y, uint8_t state){
    pf->board[x][y] = state;
    return pf->solution[x][y] == state;
}

void _picross_field_getLabels(picross_field* pf){
    // xLabels
    bool inRow = false;
    uint8_t size = 0;
    uint8_t index = 0;

    pf->max_nb_label_x = 0;
    pf->max_nb_label_y = 0;

    for (uint8_t x = 0; x < PICROSS_GRID_SIZE; x++){
        memset(pf->xLabels[x], 0, PICROSS_GRID_SIZE / 2);
        inRow = false;
        size = 0;
        index = 0;
        for (uint8_t y = 0; y < PICROSS_GRID_SIZE; y++){
            if (inRow){
                if (pf->solution[x][y] == SS_MARKED_FILLED) size++;
                else {pf->xLabels[x][index] = size; index++; inRow = false;}
            }
            else if (pf->solution[x][y] == SS_MARKED_FILLED) {size = 1; inRow = true;}
        }
        pf->max_nb_label_x = MAX(pf->max_nb_label_x, index);
    }

    for (uint8_t y = 0; y < PICROSS_GRID_SIZE; y++){
        memset(pf->xLabels[y], 0, PICROSS_GRID_SIZE / 2);
        inRow = false;
        size = 0;
        index = 0;
        for (uint8_t x = 0; x < PICROSS_GRID_SIZE; x++){
            if (inRow){
                if (pf->solution[x][y] == SS_MARKED_FILLED) size++;
                else {pf->yLabels[y][index] = size; index++; inRow = false;}
            }
            else if (pf->solution[x][y] == SS_MARKED_FILLED) {size = 1; inRow = true;}
        }
        pf->max_nb_label_y = MAX(pf->max_nb_label_y, index);
    }
}

void picross_field_print_ascii(picross_field* pf){
    printf("%d, %d\n", pf->max_nb_label_x, pf->max_nb_label_y);
    // x labels
    for (uint32_t i = 0; i < pf->max_nb_label_x; i++){
        for (uint32_t x = 0; x < PICROSS_GRID_SIZE; x++){
            printf("│");
            if (pf->xLabels[x][pf->max_nb_label_x - i - 1] == 0)
                printf("   ");
            else
                printf("%3d", (int)pf->xLabels[x][pf->max_nb_label_x - i - 1] );
        }
            printf("│\n");
    }

    // actual grid
    for (uint32_t i = 0; i < PICROSS_GRID_SIZE; i++)
        printf("┼───");
    printf("┤\n");
    
    for (uint8_t y = 0; y < PICROSS_GRID_SIZE; y++){
        for (uint8_t x = 0; x < PICROSS_GRID_SIZE; x++){
            printf("│");
            switch (pf->solution[x][y]){

            case SS_MARKED_EMPTY:
                printf(" ✖ ");
                break;
            
            case SS_MARKED_FILLED:
                printf("███");
                break;

            case SS_UNKNOWN:
                printf("   ");
                break;

            default:
                printf("[!] Error printing field !!");
                exit(1);
                break;
            }
        }
        printf("│\n");
        if (y != PICROSS_GRID_SIZE - 1){
            for (uint32_t i = 0; i < PICROSS_GRID_SIZE ; i++)
                printf("┼───");
            printf("┤\n");
        }
    }
    printf("┴");
    for (uint32_t i = 0; i < PICROSS_GRID_SIZE - 1; i++)
        printf("───┴");
    printf("───┘\n");
}