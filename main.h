
typedef enum { ROW, COLUMN, BLOCK } GroupType;

const int BOARD_SIZE = 9;
const int BLOCK_SIZE = sqrt(BOARD_SIZE);

void read_board(int (&board)[BOARD_SIZE*BOARD_SIZE]);
void load_group(GroupType t, int group, int* c_num[BOARD_SIZE], int (&board)[BOARD_SIZE*BOARD_SIZE],
										int* c_p_val[BOARD_SIZE], int (&p_val)[BOARD_SIZE*BOARD_SIZE]);
int scan_group(int* c_num[BOARD_SIZE], int* c_p_val[BOARD_SIZE]);
void print_board(int (&board)[BOARD_SIZE*BOARD_SIZE]);
void insert_values(int (&board)[BOARD_SIZE*BOARD_SIZE], int (&p_val)[BOARD_SIZE*BOARD_SIZE]);
