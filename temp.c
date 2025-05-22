#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>

#include "tetris.h"

int main(int argc, char *argv[]) {
    int delay = 1000;
    if (argc == 2) {
        delay = atoi(argv[1]);
    }
    int pts = 0;
    char board[22][23];
    strcpy(board[0], "######################");
    strcpy(board[21], "######################");
    for (int i = 1; i < 21; i++) {
        strcpy(board[i], "#                    #");
    }
    int ini_tetris[7][4][2] = {{{1, 10}, {1, 11}, {2, 10}, {2, 11}}, 
                            {{1, 9} , {1, 10}, {1, 11}, {1, 12}}, 
                            {{1, 11}, {1, 10}, {2, 10}, {3, 10}}, 
                            {{1, 10}, {1, 11}, {2, 11}, {3, 11}}, 
                            {{1, 11}, {2, 11}, {2, 10}, {3, 10}}, 
                            {{1, 10}, {2, 10}, {2, 11}, {3, 11}}, 
                            {{2, 11}, {1, 10}, {2, 10}, {3, 10}}}; 
    srand(time(NULL));
    int randomNum = rand() % 7;
    int holder[4][2];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            holder[i][j] = ini_tetris[randomNum][i][j];
        }
    }
    initialise_tetris(board, holder);
    int ch;
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    nodelay(stdscr, TRUE);
    noecho();
    print_board(board, 22, pts);
    napms(delay);
    while (1) {
        // thread 1
        ch = getch();
        if (ch == 'r' || ch == KEY_UP) {
            rotate_tetris(board, holder);
        }
        else if (ch == 'a' || ch == KEY_LEFT) {
            shift_tetris_left(board, holder);
        }
        else if (ch == 'd' || ch == KEY_RIGHT) {
            shift_tetris_right(board, holder);
        }
        else if (ch == 's' || ch == KEY_DOWN) {
            update_tetris(board, holder);
        }
        else if (ch == ' ') {
            nodelay(stdscr, FALSE);
            getch();
            nodelay(stdscr, TRUE);
        }
        
        // thread 2
        int a = update_tetris(board, holder);
        clear();
        print_board(board, 22, pts);
        if (a == 0) {
            if (point_increase(board) == 1) {
                pts++;
            }
            randomNum = rand() % 7;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 2; j++) {
                    holder[i][j] = ini_tetris[randomNum][i][j];
                }
            }
            napms(delay / 2);
            initialise_tetris(board, holder);
            clear();
            print_board(board, 22, pts);
        }
        napms(delay);
    }
    return 0;
}