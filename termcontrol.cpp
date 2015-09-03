#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>

WINDOW *win1;

void paint_window(void){
    int x, y;

    refresh();

    clear();
    refresh();

    getmaxyx(stdscr, y, x);

    bkgd(COLOR_PAIR(1));
    refresh();

    win1 = newwin(3, x - 4, 1, 2);
    box(win1, 0, 0);
    wbkgd(win1, COLOR_PAIR(2));

    wattron(win1, COLOR_PAIR(3));
    mvwprintw(win1, 1, 1, "MAX X: %d, MAX Y: %d. Press 'q' to exit.", x, y);
    wattroff(win1, COLOR_PAIR(3));

    wrefresh(win1);
}

void sig_handler(int sig_num){
    delwin(win1);
    endwin();
    paint_window();
}

int main(void) {
    int ch;

    initscr();

    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_WHITE, COLOR_RED);

    paint_window();

    signal(SIGWINCH, sig_handler);

    while(1){
        ch = getch();

        if(ch == 'q' || ch == 'Q'){
            delwin(win1);
            endwin();
            exit(EXIT_SUCCESS);
        }
    }

    return 0;
}