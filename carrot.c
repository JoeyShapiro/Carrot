#ifdef _WIN32
    #include <pdcurses.h>
#else
    #include <ncurses.h>
    #include <sys/time.h>
#endif

#include <time.h>
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
    int x = 5, y = 0;
    int WIDTH = 80, HEIGHT = 24;
    int direction[] = { 1, 1 };
    int msg_width = 0, msg_height = 0;

    printf("%s\n", argv[1]);
    

	initscr();			/* Start curses mode 		  */
    printf("x: %d, y: %d", getmaxx(stdscr), getmaxy(stdscr));
    curs_set(0);
    getmaxyx(stdscr, HEIGHT, WIDTH);
    start_color();
    assume_default_colors(curColor,COLOR_BLACK);

    char msg[HEIGHT][WIDTH];
    for (size_t i = 0; i < HEIGHT; i++)
    {
        memset(msg[i], 0, WIDTH);
    }

    size_t row = 0;
    size_t col = 0;
    for (size_t i = 0; i < strlen(argv[1]); i++)
    {
        // if an escape character
        if (argv[1][i] == '\\') {
            char escape_char = argv[1][i+1];

            if (escape_char == 'n') {
                if (strlen(msg[row]) > msg_width)// this should work here
                    msg_width = strlen(msg[row]);

                msg[row++][col] = '\0'; //TODO might not need to zero out with this
                i++; // skip the type character
                col = 0;
            } else if (escape_char == 'a') {

            } else if (escape_char == 'b') {
                
            } else if (escape_char == 'f') {
                
            } else if (escape_char == 'r') {
                
            } else if (escape_char == 't') {
                
            } else if (escape_char == 'v') {
                
            } else if (escape_char == '\\') {
                
            } else if (escape_char == '\'') { //TODO does this work
                
            } else if (escape_char == '"') {
                
            } else if (escape_char == '?') { //TODO what?
                
            } else if (escape_char == 'o') {
                
            } else if (escape_char == 'x') {
                
            } else if (escape_char == '0') {
                
            }
        } else {
            msg[row][col++] = argv[1][i];
        }
    }
    // check if the last row is largest
    if (strlen(msg[row]) > msg_width)
        msg_width = strlen(msg[row]);
    // get height
    msg_height = row+1;

    // for (size_t i = 0; i < HEIGHT; i++)
    // {
    //     printf("\"%s\" %lu\n", msg[i], strlen(msg[i]));
    // }

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
            // mvaddstr(y, x, msg);
            for (size_t i = 0; i < msg_height; i++)
            {
                for (size_t j = 0; j < msg_width; j++)
                {
                    // if the string is done and shorter than the max string, stop printing
                    if (msg[i][j] == '\0')
                        break;
                    mvaddch(y+i, x+j, msg[i][j]);
                }
            }
            
            refresh();			/* Print it on to the real screen */
            x += direction[0];
            y += direction[1];
            if (x == WIDTH-msg_width) { direction[0] = -1; changeColor(); } else if (x == 0) { direction[0] = 1; changeColor(); }
            if (y == HEIGHT-msg_height) { direction[1] = -1; changeColor(); } else if (y == 0) { direction[1] = 1; changeColor(); }
        }
    }
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */


	return 0;
}