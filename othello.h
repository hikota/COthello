#define COL 8
#define ROW 8

typedef struct Board* OBoard;

typedef enum Piece{
  BLACK,
  WHITE,
  EMPTY,
  PUSSIBLE
}Piece;

typedef struct Point{
  int x;
  int y;
}Point;

typedef struct Board{
  Piece cell[ROW][COL];
  Point pussible_points[40];
  int pcells_num;
  Piece turn;
}Board;

void *create_board();
static void init_board(Board *board);
bool get_pussible_points(Board *board);
static bool isPussible(Board *board, Point point);
static void sweep_pussible(Board *board);
Piece get_opponent_piece(Piece piece);
void update_board(Board *board);
bool is_on_board(Point point);
void change_turn(Board *board);
void render(Board *board);
bool put_piece(Board *board, Piece piece, Point move);
static void *ec_malloc(unsigned int);
