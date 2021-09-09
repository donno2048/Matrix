#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <locale.h>
#include <curses.h>
typedef struct cmatrix {
    int val;
    bool is_head;
} cmatrix;
cmatrix **matrix = (cmatrix **) NULL;
volatile sig_atomic_t signal_status = 0;
void sighandler(int s) {signal_status = s;}
int main() {
    int i, j, y, z, keypress, count = 0, firstcoldone = 0, update = 4, highnum = 0, mcolor = COLOR_GREEN, randnum = 0, randmin = 0, *length = malloc(COLS * sizeof(int)), *spaces = malloc(COLS * sizeof(int)), *updates = malloc(COLS * sizeof(int));
    char *msg = "";
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    timeout(0);
    curs_set(0);
    signal(SIGINT, sighandler);
    signal(SIGQUIT, sighandler);
    signal(SIGWINCH, sighandler);
    signal(SIGTSTP, sighandler);
    if (has_colors()) {
        start_color();
        init_pair(COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
        init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
        init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
        init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
        init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
        init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
        init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
    }
    randmin = 33;
    highnum = 123;
    randnum = highnum - randmin;
    matrix = malloc(sizeof(cmatrix *) * (LINES + 1));
    matrix[0] = malloc(sizeof(cmatrix) * (LINES + 1) * COLS);
    for (i = 1; i <= LINES; i++)
        matrix[i] = matrix[i - 1] + COLS;
    for (i = 0; i <= LINES; i++)
        for (j = 0; j <= COLS - 1; j += 2)
            matrix[i][j].val = -1;
    for (j = 0; j <= COLS - 1; j += 2) {
        spaces[j] = (int) rand() % LINES + 1;
        length[j] = (int) rand() % (LINES - 3) + 3;
        matrix[1][j].val = ' ';
        updates[j] = (int) rand() % 3 + 1;
    }
    while (signal_status != SIGTSTP && signal_status != SIGINT && signal_status != SIGQUIT) {
        count++;
        if (count > 4)
            count = 1;
        if ((keypress = wgetch(stdscr)) != ERR) {
            switch (keypress) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                update = keypress - 48;
                break;
            case '!':
                mcolor = COLOR_RED;
                break;
            case '@':
                mcolor = COLOR_GREEN;
                break;
            case '#':
                mcolor = COLOR_YELLOW;
                break;
            case '$':
                mcolor = COLOR_BLUE;
                break;
            case '%':
                mcolor = COLOR_MAGENTA;
                break;
            case '^':
                mcolor = COLOR_CYAN;
                break;
            case '&':
                mcolor = COLOR_WHITE;
                break;
            }
        }
        for (j = 0; j <= COLS - 1; j += 2) {
            if (matrix[0][j].val == -1 && matrix[1][j].val == ' ' && spaces[j] > 0)
                spaces[j]--;
            else if (matrix[0][j].val == -1 && matrix[1][j].val == ' ') {
                length[j] = (int) rand() % (LINES - 3) + 3;
                matrix[0][j].val = (int) rand() % randnum + randmin;
                spaces[j] = (int) rand() % LINES + 1;
            }
            i = 0;
            y = 0;
            firstcoldone = 0;
            while (i <= LINES) {
                while (i <= LINES && (matrix[i][j].val == ' ' || matrix[i][j].val == -1))
                    i++;
                if (i > LINES)
                    break;
                z = i;
                y = 0;
                while (i <= LINES && (matrix[i][j].val != ' ' && matrix[i][j].val != -1)) {
                    matrix[i][j].is_head = false;
                    i++;
                    y++;
                }
                if (i > LINES) {
                    matrix[z][j].val = ' ';
                    continue;
                }
                matrix[i][j].val = (int) rand() % randnum + randmin;
                matrix[i][j].is_head = true;
                if (y > length[j] || firstcoldone) {
                    matrix[z][j].val = ' ';
                    matrix[0][j].val = -1;
                }
                firstcoldone = 1;
                i++;
            }
            y = 1;
            z = LINES;
            for (i = y; i <= z; i++) {
                move(i - y, j);
                if (matrix[i][j].val == 0 || matrix[i][j].is_head) {
                    attron(COLOR_PAIR(COLOR_WHITE));
                    if (matrix[i][j].val == 0)
                        addch('&');
                    else if (matrix[i][j].val == -1)
                        addch(' ');
                    else
                        addch(matrix[i][j].val);
                    attroff(COLOR_PAIR(COLOR_WHITE));
                } else {
                    attron(COLOR_PAIR(mcolor));
                    if (matrix[i][j].val == 1)
                        addch('|');
                    else {
                        if (matrix[i][j].val == -1)
                            addch(' ');
                        else
                            addch(matrix[i][j].val);
                    }
                    attroff(COLOR_PAIR(mcolor));
                }
            }
        }
        if (msg[0] != '\0') {
            int msg_x = LINES / 2;
            int msg_y = COLS / 2 - strlen(msg) / 2;
            int i = 0;
            move(msg_x - 1, msg_y - 2);
            for (i = 0; i < (int) strlen(msg) + 4; i++)
                addch(' ');
            move(msg_x, msg_y - 2);
            addch(' ');
            addch(' ');
            addstr(msg);
            addch(' ');
            addch(' ');
            move(msg_x + 1, msg_y - 2);
            for (i = 0; i < (int) strlen(msg) + 4; i++)
                addch(' ');
        }
        napms(update * 10);
    }
    endwin();
	return 0;
}