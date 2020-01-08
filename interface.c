#include "2048.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void signalexit() {
    endgame(BORK);
}

void ctrlcexit() {
    endgame(QUIT);
}

void init_interface() {
    /* curses stuff, borrowed from the curses manpage */
    initscr();
    cbreak();
    noecho();
    nonl();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    /* signal stuff, borrowed from Omega-RPG */
#ifdef SIGINT
    signal(SIGINT, (void*) ctrlcexit);
#endif
#ifdef SIGHUP
    signal(SIGHUP,(void*) signalexit);
#endif
#ifdef SIGQUIT
    signal(SIGQUIT, (void*) signalexit);
#endif
#ifdef SIGILL
    signal(SIGILL, (void*) signalexit);
#endif
#ifdef SIGTRAP
    signal(SIGTRAP, (void*) signalexit);
#endif
#ifdef SIGFPE
    signal(SIGFPE, (void*) signalexit);
#endif
#ifdef SIGSEGV
    signal(SIGSEGV, (void*) signalexit);
#endif
#ifdef SIGIOT
    signal(SIGIOT,(void*) signalexit);
#endif
#ifdef SIGABRT
    signal(SIGABRT, (void*) signalexit);
#endif
#ifdef SIGEMT
    signal(SIGEMT,(void*) signalexit);
#endif
#ifdef SIGBUS
    signal(SIGBUS,(void*) signalexit);
#endif
#ifdef SIGSYS
    signal(SIGSYS,(void*) signalexit);
#endif
}

void shutdown_interface() {
    endwin();
}