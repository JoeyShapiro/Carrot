#ifdef _WIN32
    #include <pdcurses.h>
#else
    #include <ncurses.h>
#endif

#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

int curColor = 3;

void changeColor() {
    assume_default_colors(++curColor,COLOR_BLACK);

    if (curColor >= 7)
        curColor = 1;
}

int main(int argc, char **argv)
{	
    struct timeval now, then;
    gettimeofday(&now, NULL);
    gettimeofday(&then, NULL);
    int x = 0, y = 0;
    int WIDTH, HEIGHT;
    int direction[] = {1, 1};
    int length = strlen(argv[1]);

    char msg[100];

	initscr();			/* Start curses mode 		  */
    printf("x: %d, y: %d", getmaxx(stdscr), getmaxy(stdscr));
    curs_set(0);
    getmaxyx(stdscr, HEIGHT, WIDTH);
    start_color();
    assume_default_colors(curColor,COLOR_BLACK);

    // init_pair(1, COLOR_BLACK, COLOR_YELLOW);
    // init_pair(2, COLOR_BLACK, COLOR_BLUE);
    // init_pair(3, COLOR_BLACK, COLOR_CYAN);
    // init_pair(4, COLOR_BLACK, COLOR_GREEN);
    // init_pair(5, COLOR_BLACK, COLOR_MAGENTA);
    // init_pair(6, COLOR_BLACK, COLOR_RED);
    // init_pair(7, COLOR_BLACK, COLOR_WHITE);

    // init_pair(1, COLOR_YELLOW, COLOR_YELLOW);


    while (true) {
        gettimeofday( &now, NULL);
        long delta_us = (now.tv_sec * 1000000 + now.tv_usec) - (then.tv_sec * 1000000 + then.tv_usec);

        if (delta_us > 100000) {
            clear();
            gettimeofday(&then, NULL);
            
            // attron(1);
            mvaddstr(y, x, argv[1]);
            refresh();			/* Print it on to the real screen */
            x += direction[0];
            y += direction[1];
            if (x == WIDTH-1-length) { direction[0] = -1; changeColor(); } else if (x == 0) { direction[0] = 1; changeColor(); }
            if (y == HEIGHT-1) { direction[1] = -1; changeColor(); } else if (y == 0) { direction[1] = 1; changeColor(); }
        }
    }
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */


	return 0;
}