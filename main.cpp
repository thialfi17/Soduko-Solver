
#include <iostream>
#include <math.h>
using namespace std;

typedef enum { ROW, COLUMN, BLOCK } GroupType;

const int BOARD_SIZE = 9;
const int BLOCK_SIZE = sqrt(BOARD_SIZE);

void read_board(int (&board)[BOARD_SIZE*BOARD_SIZE]);
void load_group(GroupType t, int group, int* c_num[BOARD_SIZE], int (&board)[BOARD_SIZE*BOARD_SIZE],
										int* c_p_val[BOARD_SIZE], int (&c_val)[BOARD_SIZE*BOARD_SIZE]);
void scan_group(int* c_num[BOARD_SIZE], int* c_p_val);
void print_board(int (&board)[BOARD_SIZE*BOARD_SIZE]);

int main() 
{
	int board[BOARD_SIZE * BOARD_SIZE];  //Board.
	int * current_numbers[BOARD_SIZE];   //The current values of the numbers stored in the group we are looking at.
	int p_values[BOARD_SIZE*BOARD_SIZE]; //Possible values for the cells on the board.
	int * current_p_values[BOARD_SIZE];
	
	read_board(board); 
	
	print_board(board);
	
	load_group(BLOCK, 2, current_numbers, board, current_p_values, p_values);
	*current_numbers[2] = 3;
	load_group(ROW, 2, current_numbers, board, current_p_values, p_values);
	*current_numbers[2] = 3;
	load_group(COLUMN, 2, current_numbers, board, current_p_values, p_values);
	*current_numbers[2] = 3;
	
	print_board(board);
}

void scan_group(int* c_num[BOARD_SIZE], int* c_p_val) {
	
}

void load_group(GroupType t, int group, int* c_num[BOARD_SIZE], int (&board)[BOARD_SIZE*BOARD_SIZE],
										int* c_p_val[BOARD_SIZE], int (&c_val)[BOARD_SIZE*BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (t == ROW) {
			c_num[i] = &board[i + group*BOARD_SIZE];
		}
		else if (t == COLUMN) {
			c_num[i] = &board[group + i * BOARD_SIZE];
		}
		else if (t == BLOCK) {
			c_num[i] = &board[group * BLOCK_SIZE + (i / BLOCK_SIZE * BOARD_SIZE + i % BLOCK_SIZE)];
		}
	}
}

void read_board(int (&board)[BOARD_SIZE*BOARD_SIZE])
{
    FILE * f = fopen("puzzle.txt", "r");
   
    int count = 0;
    while ( !feof(f) ) {
        char c = getc(f);
        
        if ( c > 47 && c < 58 ) {
            board[count++] = c - 48; 
        }   
        if (count >= BOARD_SIZE * BOARD_SIZE) {
            break;
        }
    }
    fclose(f);
}

void print_board(int (&board)[BOARD_SIZE*BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
		std::cout << board[i];

		if ((i + 1) % BLOCK_SIZE == 0)
			std::cout << " ";
		if ((i + 1) % BOARD_SIZE == 0) {
			std::cout << std::endl;
			if ((i + 1) % (BOARD_SIZE * BLOCK_SIZE) == 0) {
				std::cout << std::endl;
			}
		}
	}
}
