#include "2048.h"

int movetilesdown() {
    int row, column, moved, rmoved = 0;
    do {
        moved = 0;
        for (column = 0; column < 4; column++) {
            for (row = 3; row >= 0; row--) {
                if (!BOARD_RC(row, column) && row && BOARD_RC(row - 1, column)) {
                    BOARD_RC(row, column) = BOARD_RC(row - 1, column);
                    BOARD_RC(row - 1, column) = 0;
                    moved++;
                }
            }
        }
        rmoved += moved;
    } while (moved);
    return rmoved;
}

int movetilesup() {
    int row, column, moved, rmoved = 0;
    do {
        moved = 0;
        for (column = 0; column < 4; column++) {
            for (row = 0; row < 4; row++) {
                if (!BOARD_RC(row, column) && row < 3 && BOARD_RC(row + 1, column)) {
                    BOARD_RC(row, column) = BOARD_RC(row + 1, column);
                    BOARD_RC(row + 1, column) = 0;
                    moved++;
                }
            }
        }
        rmoved += moved;
    } while (moved);
    return rmoved;
}

int movetilesright() {
    int row, column, moved, rmoved = 0;
    do {
        moved = 0;
        for (row = 0; row < 4; row++) {
            for (column = 3; column >= 0; column--) {
                if (!BOARD_RC(row, column) && column && BOARD_RC(row, column - 1)) {
                    BOARD_RC(row, column) = BOARD_RC(row, column - 1);
                    BOARD_RC(row, column - 1) = 0;
                    moved++;
                }
            }
        }
        rmoved += moved;
    } while (moved);
    return rmoved;
}

int movetilesleft() {
    int row, column, moved, rmoved = 0;
    do {
        moved = 0;
        for (row = 0; row < 4; row++) {
            for (column = 0; column < 4; column++) {
                if (!BOARD_RC(row, column) && column < 3 && BOARD_RC(row, column + 1)) {
                    BOARD_RC(row, column) = BOARD_RC(row, column + 1);
                    BOARD_RC(row, column + 1) = 0;
                    moved++;
                }
            }
        }
        rmoved += moved;
    } while (moved);
    return rmoved;
}

int combinetilesdown() {
    int row, column, combined = 0;
    for (column = 0; column < 4; column++) {
        for (row = 3; row > 0; row--) {
            if (BOARD_RC(row, column) && BOARD_RC(row, column) == BOARD_RC(row - 1, column)) {
                BOARD_RC(row, column) += BOARD_RC(row - 1, column);
                BOARD_RC(row - 1, column) = 0;
                recent_score += BOARD_RC(row, column);
                row--; /* make sure we don't do double-combines on the same tile */
                combined++;
            }
        }
    }
    return combined;
}

int combinetilesup() {
    int row, column, combined = 0;
    for (column = 0; column < 4; column++) {
        for (row = 0; row < 3; row++) {
            if (BOARD_RC(row, column) && BOARD_RC(row, column) == BOARD_RC(row + 1, column)) {
                BOARD_RC(row, column) += BOARD_RC(row + 1, column);
                BOARD_RC(row + 1, column) = 0;
                recent_score += BOARD_RC(row, column);
                row++; /* make sure we don't do double-combines on the same tile */
                combined++;
            }
        }
    }
    return combined;
}

int combinetilesright() {
    int row, column, combined = 0;
    for (row = 0; row < 4; row++) {
        for (column = 3; column > 0; column--) {
            if (BOARD_RC(row, column) && BOARD_RC(row, column) == BOARD_RC(row, column - 1)) {
                BOARD_RC(row, column) += BOARD_RC(row, column - 1);
                BOARD_RC(row, column - 1) = 0;
                recent_score += BOARD_RC(row, column);
                column--; /* make sure we don't do double-combines on the same tile */
                combined++;
            }
        }
    }
    return combined;
}

int combinetilesleft() {
    int row, column, combined = 0;
    for (row = 0; row < 4; row++) {
        for (column = 0; column < 3; column++) {
            if (BOARD_RC(row, column) && BOARD_RC(row, column) == BOARD_RC(row, column + 1)) {
                BOARD_RC(row, column) += BOARD_RC(row, column + 1);
                BOARD_RC(row, column + 1) = 0;
                recent_score += BOARD_RC(row, column);
                column++; /* make sure we don't do double-combines on the same tile */
                combined++;
            }
        }
    }
    return combined;
}

int moveup() {
    return movetilesup() + combinetilesup() + movetilesup();
}

int movedown() {
    return movetilesdown() + combinetilesdown() + movetilesdown();
}

int moveright() {
    return movetilesright() + combinetilesright() + movetilesright();
}

int moveleft() {
    return movetilesleft() + combinetilesleft() + movetilesleft();
}

// I needed this at one point
// KEY_DOWN  v 258
// KEY_UP    ^ 259
// KEY_LEFT  < 260
// KEY_RIGHT > 261

#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
int keymove(int direction) {
    switch (direction) {
        case KEY_DOWN:  return movedown();
        case KEY_UP:    return moveup();
        case KEY_LEFT:  return moveleft();
        case KEY_RIGHT: return moveright();
        default:        return 0;
    }
}