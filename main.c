#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "2048.h"

int score = 0, recent_score = 0;

#pragma clang diagnostic ignored "-Wmissing-noreturn"

int main() {
    init_interface();
    init_board();

    gamestart:

        clear();
        display_score();
        display_board();
        refresh();

        if (game_over())
            endgame(STUCK);

        recent_score = 0;

        int c = getch();
        if (c == 'q') {
            endgame(QUIT);
        } else {
            if (keymove(c))
                spawn_tile();   /* we only want to spawn tiles if we actually moved something */
        }

        score += recent_score;

    goto gamestart;
}

void display_score() {
    printw("\tScore: %d", score, recent_score);
    if (recent_score)
        printw(" (+%d)", recent_score);
    printw("\n");
}

int game_over() {
    if (has_empty())
        return 0;

    int i, j;
    for (i = 0; i < 16; i++)
        for (j = 0; j < num_neighbors[i]; j++)
            if (board[i] == board[neighbors[i][j]])
                return 0;

    return 1;
}

const char *deathcauses[] = {"quit", "ran out of moves", "borked"};

void endgame(int cause) {
    sleep(1);

    shutdown_interface();

    printf("You %s!\n", deathcauses[cause]);
    printf("Highest tile: %d\n", highest_tile());
    printf("Score: %d\n", score);

    exit(cause == BORK ? EXIT_FAILURE : EXIT_SUCCESS);
}
