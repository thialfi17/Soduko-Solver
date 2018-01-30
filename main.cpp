// SudokuTest.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <iostream>
#include <math.h>
#include "main.h"

using namespace std;

int main()
{
	int board[BOARD_SIZE * BOARD_SIZE];  //Board.
	int * current_numbers[BOARD_SIZE];   //The current values of the numbers stored in the group we are looking at.
	int p_values[BOARD_SIZE*BOARD_SIZE]; //Possible values for the cells on the board.
	int * current_p_values[BOARD_SIZE];
	int mask_sum = 0, prev_mask_sum = 0;

	for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
		p_values[i] = 0;
	}

	read_board(board);

	print_board(board);

	/*load_group(BLOCK, 8, current_numbers, board, current_p_values, p_values);
	mask_sum += scan_group(c_numbers, current_p_values);
	*current_numbers[2] = 8;
	load_group(ROW, 3, current_numbers, board, current_p_values, p_values);
	*current_numbers[2] = 3;
	load_group(COLUMN, 2, current_numbers, board, current_p_values, p_values);
	*current_numbers[2] = 3;*/

	while (mask_sum < 3 * (pow(2, BOARD_SIZE) - 1) * BOARD_SIZE)
	{
		prev_mask_sum = mask_sum;
		mask_sum = 0;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			load_group(BLOCK, i, current_numbers, board, current_p_values, p_values);
			mask_sum += scan_group(current_numbers, current_p_values);

			load_group(ROW, i, current_numbers, board, current_p_values, p_values);
			mask_sum += scan_group(current_numbers, current_p_values);

			load_group(COLUMN, i, current_numbers, board, current_p_values, p_values);
			mask_sum += scan_group(current_numbers, current_p_values);
		}

		insert_values(board, p_values);

		if (mask_sum == prev_mask_sum)
		{
			cout << "Puzzle unsolvable!" << endl;
			print_board(board);
			return 0;
		}
	}

	cout << "Puzzle solved! :)" << endl;
	print_board(board);
}

int scan_group(int* c_num[BOARD_SIZE], int* c_p_val[BOARD_SIZE]) {
	int temp_mask = 0;
	//Find the numbers missing in the group
	for (int i = 0; i < BOARD_SIZE; i++)	//Finding missing numbers, updating possibilities mask.
	{					//Using mask, if value is 0, that number is possible.
		if (*c_num[i] == 0) {
			continue;
		}
		int bit = 1 << (*c_num[i] - 1);

		if (temp_mask & bit) {
			cout << "The number: " << *c_num[i] << " has occurred before in this group!" << endl;
		}
		temp_mask |= bit;
	}
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (*c_num[i] == 0)
		{
			*c_p_val[i] |= temp_mask;
		}
	}
	return temp_mask;
}

void load_group(GroupType t, int group, int* c_num[BOARD_SIZE], int(&board)[BOARD_SIZE*BOARD_SIZE],
	int* c_p_val[BOARD_SIZE], int(&p_val)[BOARD_SIZE*BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		if (t == ROW) {
			c_num[i] = &board[i + group*BOARD_SIZE];
			c_p_val[i] = &p_val[i + group*BOARD_SIZE];
		}
		else if (t == COLUMN) {
			c_num[i] = &board[group + i * BOARD_SIZE];
			c_p_val[i] = &p_val[group + i * BOARD_SIZE];
		}
		else if (t == BLOCK) {
			c_num[i] = &board[(group % BLOCK_SIZE) * BLOCK_SIZE + 				// Calculates the initial horizontal position of the group
				((group / BLOCK_SIZE) * BLOCK_SIZE * BOARD_SIZE) +  // Calculates the initial vertical position of the group
				(i / BLOCK_SIZE * BOARD_SIZE) + 					// Calculates the vertical position within the group
				(i % BLOCK_SIZE)];								// Calculates the horizontal position within the group
			c_p_val[i] = &p_val[(group % BLOCK_SIZE) * BLOCK_SIZE + 				// Calculates the initial horizontal position of the group
				((group / BLOCK_SIZE) * BLOCK_SIZE * BOARD_SIZE) +  // Calculates the initial vertical position of the group
				(i / BLOCK_SIZE * BOARD_SIZE) + 					// Calculates the vertical position within the group
				(i % BLOCK_SIZE)];								// Calculates the horizontal position within the group
		}
	}
}

void read_board(int(&board)[BOARD_SIZE*BOARD_SIZE])
{
	FILE * f = fopen("puzzle.txt", "r");

	int count = 0;
	while (!feof(f)) {
		char c = getc(f);

		if (c > 47 && c < 58) {
			board[count++] = c - 48;
		}
		if (count >= BOARD_SIZE * BOARD_SIZE) {
			break;
		}
	}
	fclose(f);
}

void print_board(int(&board)[BOARD_SIZE*BOARD_SIZE]) {
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

void insert_values(int(&board)[BOARD_SIZE*BOARD_SIZE], int(&p_val)[BOARD_SIZE*BOARD_SIZE])
{
	for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++) {

			int temp = ~p_val[i] & MASK;

			if (temp == pow(2, j)) {
				board[i] = j + 1;
			}
		}
	}
}

