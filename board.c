#pragma ide diagnostic ignored "cert-msc30-c"
#include "2048.h"
#include <time.h>
#include <stdlib.h>

int board[] = {0, 0, 0, 0,
               0, 0, 0, 0,
               0, 0, 0, 0,
               0, 0, 0, 0};

/* board indices
 * 0  1  2  3
 * 4  5  6  7
 * 8  9  10 11
 * 12 13 14 15 */

int num_neighbors[] = {2, 3, 3, 2, 3, 4, 4, 3, 3, 4, 4, 3, 2, 3, 3, 2};
int neighbors[16][4] = {{1, 4}, {0, 5, 2}, {1, 6, 3}, {2, 7}, {0, 5, 8}, {1, 4, 6, 9}, {2, 5, 7, 10},
                        {3, 6, 11}, {4, 9, 12}, {5, 8, 10, 13}, {6, 9, 14, 11}, {7, 10, 15}, {8, 13}, {9, 12, 14},
                        {10, 13, 15}, {11, 14}};

const int spawns[] = {2, 2, 2, 4}; /* tile spawning array with proper probability */

void spawn_tile() {
    int idx;
    for (idx = rand() % 16; board[idx]; idx = rand() % 16)
        /* make sure we're not spawning tiles somewhere there's already a tile */;

    board[idx] = new_tile();
}

int new_tile() {
    return spawns[rand() % 4];
}

void init_board() {
    board[8] = new_tile();
    board[12] = new_tile();
    board[13] = new_tile();

    time_t t;
    time(&t);
    srand(t % RAND_MAX);
}

void display_board() {
    int i;
    for (i = 0; i < 16; i++) {
        if (board[i])
            printw("|%4d", board[i]);
        else
            printw("|    ");
        if (i == 3 || i == 7 || i == 11 || i == 15)
            printw("|\n");
    }
}

int has_empty() {
    int i;
    for (i = 0; i < 16; i++)
        if (!board[i])
            return 1;

    return 0;
}

int highest_tile() {
    int i, m = 0;
    for (i = 0; i < 16; i++)
        m = max(m, board[i]);
    return m;
}
