#include <iostream>
using namespace std;

const int BOARD_SIZE;
void read_board(int& board[BOARD_SIZE]);

int main() 
{
  int board[BOARD_SIZE];
  read_board(board); 
}

void read_board(int& board[BOARD_SIZE])
{
  FILE * f = fopen("puzzle.txt", "r");
  
  int count = 0;
  while ( !feof(f) ) {
    c = getc(f);
    
    if ( c > 47 && c < 58 ) {
     board[count++] = c - 48; 
    }
    if (count >= BOARD_SIZE * BOARD_SIZE) {
      break;
    }
  }
  fclose(f);
}
