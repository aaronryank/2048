#ifndef __2048_H
#define __2048_H

/* every file needs this */
#include <curses.h>

/* game defs */
enum { QUIT, STUCK, BORK };

/* functions */
/* interface.c */
void signalexit();
void init_interface();
void shutdown_interface();

/* board.c */
void spawn_tile();
int new_tile();
void init_board();
void display_board();
int has_empty();
int highest_tile();

/* move.c */
int movedown(), moveup(), moveleft(), moveright();
int keymove(int);

/* main.c */
int game_over();
void endgame(int);
void display_score();

/* game variables */
extern int score, recent_score;

/* board variables */
extern int board[];
extern int num_neighbors[];
extern int neighbors[16][4];

/* ease-of-access to board<row,column> */
#define BOARD_RC(r, c) board[(c) + (r)*4]

/* board.c needs this */
#ifndef max
#define max(a,b) (a) > (b) ? (a) : (b)
#endif

#endif //__2048_H
