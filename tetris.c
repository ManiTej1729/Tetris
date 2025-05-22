#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>

#include "tetris.h"

void swap(int *ptr1, int *ptr2) {
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

void update_board(char (*board)[23], int start) {
    while (start > 1) {
        strcpy(board[start], board[start - 1]);
        start--;
    }
}

int point_increase(char (*board)[23]) {
    for (int i = 1; i < 21; i++) {
        if (strcmp("#OOOOOOOOOOOOOOOOOOOO#", board[i]) == 0) {
            update_board(board, i);
            return 1;
        }
    }
    return 0;
}

void print_board(char arr[][23], int rows, int pts) {
    for (int i = 0; i < rows; i++) {
        printw("%s\n", arr[i]); 
    }
    // Print score and controls
    mvprintw(rows+2, 0, "Score: %d", pts);
    mvprintw(rows+4, 0, "Controls:");
    mvprintw(rows+5, 0, "----------");
    mvprintw(rows+6, 0, "A: Move left/right");
    mvprintw(rows+7, 0, "D: Move left/right");
    mvprintw(rows+8, 0, "R: Rotate");
    mvprintw(rows+9, 0, "S: Drop faster");
    mvprintw(rows+10, 0, "Q: Quit");
    refresh();
}

int update_tetris(char (*board)[23], int (*tetris)[2]) {
    int arr[4];
    for (int i = 0; i < 4; i++) {
        arr[i] = 0;
        if (board[tetris[i][0] + 1][tetris[i][1]] != 'O' && board[tetris[i][0] + 1][tetris[i][1]] != '#') {
            arr[i] = 1;
        }
    }
    if (arr[0] * arr[1] * arr[2] * arr[3] == 1) {
        for (int i = 0; i < 4; i++) {
            board[tetris[i][0]][tetris[i][1]] = ' ';
            tetris[i][0]++;
        }
        for (int i = 0; i < 4; i++) {
            board[tetris[i][0]][tetris[i][1]] = '*';
        }
    }
    else {
        for (int i = 0; i < 4; i++) {
            board[tetris[i][0]][tetris[i][1]] = 'O';
        }
        return 0;
    }
    return 1;
}

void initialise_tetris(char (*board)[23], int (*tetris)[2]) {
    for (int i = 0; i < 4; i++) {
        if (board[tetris[i][0]][tetris[i][1]] == ' ') {
            board[tetris[i][0]][tetris[i][1]] = '*';
        }
        else {
            nodelay(stdscr, FALSE);
            getch();
            endwin();
            exit(0);
        }
    }
}

void update_simple(char (*board)[23], int (*tetris)[2], char ch) {
    for (int i = 0; i < 4; i++) {
        board[tetris[i][0]][tetris[i][1]] = ch;
    }
}

void print_int_array(int (*tetris)[2]) {
    for (int i = 0; i < 4; i++) {
        printf("%d %d\n", tetris[i][0], tetris[i][1]);
    }
}

void shift_tetris_right(char (*board)[23], int (*tetris)[2]) {
    int arr[4];
    for (int i = 0; i < 4; i++) {
        arr[i] = 0;
        if (board[tetris[i][0]][tetris[i][1] + 1] != 'O' && board[tetris[i][0]][tetris[i][1] + 1] != '#') {
            arr[i] = 1;
        }
    }
    if (arr[0] * arr[1] * arr[2] * arr[3] == 1) {
        update_simple(board, tetris, ' ');
        for (int i = 0; i < 4; i++) {
            tetris[i][1]++;
        }
        update_simple(board, tetris, '*');
    }
    else {
        return;
    }
}

void shift_tetris_left(char (*board)[23], int (*tetris)[2]) {
    int arr[4];
    for (int i = 0; i < 4; i++) {
        arr[i] = 0;
        if (board[tetris[i][0]][tetris[i][1] - 1] != 'O' && board[tetris[i][0]][tetris[i][1] - 1] != '#') {
            arr[i] = 1;
        }
    }
    if (arr[0] * arr[1] * arr[2] * arr[3] == 1) {
        update_simple(board, tetris, ' ');
        for (int i = 0; i < 4; i++) {
            tetris[i][1]--;
        }
        update_simple(board, tetris, '*');
    }
    else {
        return;
    }
}

void shift_tetris_up(char (*board)[23], int (*tetris)[2]) {
    update_simple(board, tetris, ' ');
    for (int i = 0; i < 4; i++) {
        tetris[i][0]--;
        tetris[i][1]--;
    }
    update_simple(board, tetris, '*');
}

void eqaute_arrays(int (*tetris1)[2], int (*tetris2)[2]) {
    for (int i = 0; i < 4; i++) {
        tetris1[i][0] = tetris2[i][0];
        tetris1[i][1] = tetris2[i][1];
    }
}

bool shift_left_check (char (*board)[23], int (*tetris)[2]) {
    update_simple(board, tetris, ' ');
    for (int i = 0; i < 4; i++) {
        if (board[tetris[i][0]][tetris[i][1] - 1] != ' ' && board[tetris[i][0]][tetris[i][1] - 1] != '*') {
            update_simple(board, tetris, '*');
            return false;
        }
    }
    update_simple(board, tetris, '*');
    return true;
}

bool shift_right_check (char (*board)[23], int (*tetris)[2]) {
    update_simple(board, tetris, ' ');
    for (int i = 0; i < 4; i++) {
        if (board[tetris[i][0]][tetris[i][1] + 1] != ' ' && board[tetris[i][0]][tetris[i][1] + 1] != '*') {
            update_simple(board, tetris, '*');
            return false;
        }
    }
    update_simple(board, tetris, '*');
    return true;
}

bool shift_up_check (char (*board)[23], int (*tetris)[2]) {
    update_simple(board, tetris, ' ');
    for (int i = 0; i < 4; i++) {
        if (board[tetris[i][0] - 1][tetris[i][1]] != ' ' && board[tetris[i][0] - 1][tetris[i][1]] != '*') {
            update_simple(board, tetris, '*');
            return false;
        }
    }
    update_simple(board, tetris, '*');
    return true;
}

bool shift_down_check (char (*board)[23], int (*tetris)[2]) {
    update_simple(board, tetris, ' ');
    for (int i = 0; i < 4; i++) {
        if (board[tetris[i][0] + 1][tetris[i][1]] != ' ' && board[tetris[i][0] + 1][tetris[i][1]] != '*') {
            update_simple(board, tetris, '*');
            return false;
        }
    }
    update_simple(board, tetris, '*');
    return true;
}

availability_board *availability(char (*board)[23], int (*tetris)[2]) {
    availability_board *state = (availability_board *)malloc(sizeof(availability_board));
    state -> arr = (int *)malloc(2 * sizeof(int));
    state -> flag = 0;
    state -> avail = true;
    for (int i = 0; i < 4; i++) {
        if (board[tetris[i][0]][tetris[i][1]] != ' ' && board[tetris[i][0]][tetris[i][1]] != '*') {
            state -> avail = false;
        }
        if (board[tetris[i][0]][tetris[i][1]] == '#') {
            state -> arr[0] = tetris[i][0];
            state -> arr[1] = tetris[i][1];
            state -> flag = 1;
            if (tetris[i][0] == 0) {
                if (shift_down_check(board, tetris)) {
                    state -> avail = true;
                }
            }
            else if (tetris[i][0] == 21) {
                if (shift_up_check(board, tetris)) {
                    state -> avail = true;
                }
            }
            else if (tetris[i][1] == 0) {
                if (shift_right_check(board, tetris)) {
                    state -> avail = true;
                }
            }
            else { //tetris[i][1] == 21
                if (shift_left_check(board, tetris)) {
                    state -> avail = true;
                }
            }
        }
    }
    return state;
}

void rotate_tetris_short(char (*board)[23], int (*tetris)[2]) {
    int temp[4][2];
    eqaute_arrays(temp, tetris);
    for (int i = 0; i < 4; i++) {
        if (i != 1) {
            temp[i][0] -= temp[1][0];
            temp[i][1] -= temp[1][1];
            swap(&temp[i][0], &temp[i][1]);
            temp[i][1] *= -1;
            temp[i][0] += temp[1][0];
            temp[i][1] += temp[1][1];
        }
    }
    availability_board *state = availability(board, temp);
    if (state -> avail) {
        if (state -> flag == 0) {
            update_simple(board, tetris, ' ');
            eqaute_arrays(tetris, temp);
            update_simple(board, tetris, '*');
        }
        else if (state -> flag == 1) {
            update_simple(board, tetris, ' ');
            eqaute_arrays(tetris, temp);
            if (state -> arr[0] == 0) {
                update_tetris(board, tetris);
            }
            else if (state -> arr[0] == 21) {
                shift_tetris_up(board, tetris);
            }
            else if (state -> arr[1] == 0) {
                shift_tetris_right(board, tetris);
            }
            else {  // state -> arr[1] == 21
                shift_tetris_left(board, tetris);
            }
            board[state -> arr[0]][state -> arr[1]] = '#';
        } 
    }
}

void rotate_tetris(char (*board)[23], int (*tetris)[2]) {
    // ignore if it is a square
    if (tetris[0][0] == tetris[1][0] && tetris[2][0] == tetris[3][0] && tetris[1][0] != tetris[2][0] && tetris[0][1] == tetris[2][1]) {
        return;
    }
    rotate_tetris_short(board, tetris);
}
