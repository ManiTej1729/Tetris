# Tetris Game

A terminal-based implementation of the classic Tetris game using ncurses library for C.

## Overview

This implementation provides a simple yet complete Tetris experience in your terminal, featuring:

- Classic Tetris gameplay with 7 standard tetromino shapes
- Score tracking for completed lines
- Customizable game speed
- Threading for smooth input handling and game updates

## Files

- `main.c`: Contains the game's main logic, threading implementation, and initialization
- `tetris.c`: Implements the core game mechanics and tetromino manipulation
- `tetris.h`: Header file with function declarations and structure definitions
- `Makefile`: Build automation for compiling and running the game

## Requirements

- C compiler (gcc recommended)
- ncurses library
- pthread library

## How to Build and Run

### Basic Usage

To compile and run with the default speed:

```sh
make
```

### Custom Game Speed

To run the game with a custom delay (in milliseconds):

```sh
make delay 500
```

Lower values result in faster gameplay.

### Manual Build

If you prefer not to use the Makefile:

```sh
gcc main.c tetris.c -o tetris -lncurses -lpthread
./tetris [delay]
```

Where `[delay]` is an optional parameter to set the game speed in milliseconds.

## Controls

- `A`: Move tetromino left
- `D`: Move tetromino right
- `S`: Drop tetromino faster
- `R`: Rotate tetromino
- `Q`: Quit the game

## Game Mechanics

- The game uses a 22x23 board with borders represented by '#'
- Active tetromino pieces are represented by '*'
- Placed blocks are represented by 'O'
- Score increases by 1 for each completed line
- Game ends when new tetrominos can't be placed on the board

## Implementation Details

The game uses multi-threading to separate input handling from game logic:

- One thread handles keyboard inputs for smooth and responsive controls
- Another thread manages game state updates and tetromino movement

Tetromino rotation is implemented using matrix transformation around a pivot point.

## Cleanup

To remove compiled files:

```sh
make clean
```
