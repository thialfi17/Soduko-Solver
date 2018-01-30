
#include <iostream>
using namespace std;

const int BOARD_SIZE = 9;
void read_board(int (&board)[BOARD_SIZE*BOARD_SIZE]);

int main() 
{
  int board[BOARD_SIZE * BOARD_SIZE];
  read_board(board); 
  
  cout << board[0] << board[10] << board[80] << endl;
  
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
