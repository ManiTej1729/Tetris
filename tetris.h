typedef struct availability_board {
    bool avail;
    int *arr;
    int flag;
} availability_board;

void swap(int *ptr1, int *ptr2);
void update_board(char (*board)[23], int start);
int point_increase(char (*board)[23]);
void print_board(char arr[][23], int rows, int pts);
int update_tetris(char (*board)[23], int (*tetris)[2]);
void initialise_tetris(char (*board)[23], int (*tetris)[2]);
void update_simple(char (*board)[23], int (*tetris)[2], char ch);
void print_int_array(int (*tetris)[2]);
void shift_tetris_right(char (*board)[23], int (*tetris)[2]);
void shift_tetris_left(char (*board)[23], int (*tetris)[2]);
void shift_tetris_up(char (*board)[23], int (*tetris)[2]);
void eqaute_arrays(int (*tetris1)[2], int (*tetris2)[2]);
bool shift_left_check (char (*board)[23], int (*tetris)[2]);
bool shift_right_check (char (*board)[23], int (*tetris)[2]);
bool shift_up_check (char (*board)[23], int (*tetris)[2]);
bool shift_down_check (char (*board)[23], int (*tetris)[2]);
availability_board *availability(char (*board)[23], int (*tetris)[2]);
void rotate_tetris_short(char (*board)[23], int (*tetris)[2]);
void rotate_tetris(char (*board)[23], int (*tetris)[2]);