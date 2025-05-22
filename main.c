#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include <pthread.h>  // Add pthread library

#include "tetris.h"

// Define a structure to share data between threads
typedef struct {
    char board[22][23];
    int holder[4][2];
    int delay;
    int pts;
    int gameOver;
    pthread_mutex_t mutex;
    int ini_tetris[7][4][2];
} GameData;

// Function for keyboard input thread
void* keyboard_thread(void* arg) {
    GameData* game = (GameData*)arg;
    int ch;
    
    while (!game->gameOver) {
        ch = getch();
        if (ch == ERR) {
            continue;  // No input available
        }
        
        pthread_mutex_lock(&game->mutex);
        
        if (ch == 'r') {
            rotate_tetris(game->board, game->holder);
        }
        else if (ch == 'a') {
            shift_tetris_left(game->board, game->holder);
        }
        else if (ch == 'd') {
            shift_tetris_right(game->board, game->holder);
        }
        else if (ch == 's') {
            update_tetris(game->board, game->holder);
        }
        else if (ch == 'q') {
            game->gameOver = 1;  // Quit the game
        }
        clear();
        print_board(game->board, 22, game->pts);
        pthread_mutex_unlock(&game->mutex);
        napms(50);  // Small delay to prevent CPU hogging
    }
    
    return NULL;
}

// Function for game update thread
void* update_thread(void* arg) {
    GameData* game = (GameData*)arg;
    int randomNum;
    
    while (!game->gameOver) {
        pthread_mutex_lock(&game->mutex);
        
        int a = update_tetris(game->board, game->holder);
        clear();
        print_board(game->board, 22, game->pts);
        
        if (a == 0) {
            if (point_increase(game->board) == 1) {
                game->pts++;
            }
            randomNum = rand() % 7;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 2; j++) {
                    game->holder[i][j] = game->ini_tetris[randomNum][i][j];
                }
            }
            napms(game->delay / 2);
            initialise_tetris(game->board, game->holder);
            clear();
            print_board(game->board, 22, game->pts);
        }
        
        pthread_mutex_unlock(&game->mutex);
        napms(game->delay);  // Control game speed
    }
    
    return NULL;
}

int main(int argc, char *argv[]) {
    // Initialize game data
    GameData game;
    game.delay = 700;
    game.pts = 0;
    game.gameOver = 0;
    
    if (argc == 2) {
        game.delay = atoi(argv[1]);
    }
    
    // Initialize board
    strcpy(game.board[0], "######################");
    strcpy(game.board[21], "######################");
    for (int i = 1; i < 21; i++) {
        strcpy(game.board[i], "#                    #");
    }
    
    // Define tetromino shapes
    int shapes[7][4][2] = {{{1, 10}, {1, 11}, {2, 10}, {2, 11}}, 
                        {{1, 9}, {1, 10}, {1, 11}, {1, 12}}, 
                        {{1, 11}, {1, 10}, {2, 10}, {3, 10}}, 
                        {{1, 10}, {1, 11}, {2, 11}, {3, 11}}, 
                        {{1, 11}, {2, 11}, {2, 10}, {3, 10}}, 
                        {{1, 10}, {2, 10}, {2, 11}, {3, 11}}, 
                        {{1, 10}, {2, 10}, {3, 10}, {2, 11}}};
    
    // Copy shapes to game data
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 4; j++) {
            game.ini_tetris[i][j][0] = shapes[i][j][0];
            game.ini_tetris[i][j][1] = shapes[i][j][1];
        }
    }
    
    // Initialize random number generator
    srand(time(NULL));
    int randomNum = rand() % 7;
    
    // Set initial tetromino
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            game.holder[i][j] = shapes[randomNum][i][j];
        }
    }
    
    // Initialize mutex
    pthread_mutex_init(&game.mutex, NULL);
    
    // Initialize ncurses
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    cbreak();
    noecho();
    
    // Initialize the game
    initialise_tetris(game.board, game.holder);
    print_board(game.board, 22, game.pts);
    
    // Create threads
    pthread_t input_thread, game_thread;
    pthread_create(&input_thread, NULL, keyboard_thread, (void*)&game);
    pthread_create(&game_thread, NULL, update_thread, (void*)&game);
    
    // Wait for threads to finish
    pthread_join(input_thread, NULL);
    pthread_join(game_thread, NULL);
    
    // Clean up
    pthread_mutex_destroy(&game.mutex);
    endwin();  // End ncurses
    
    return 0;
}
