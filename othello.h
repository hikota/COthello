#define COL 8
#define ROW 8

typedef struct Board* OBoard;

typedef enum Piece{
  BLACK,
  WHITE,
  EMPTY,
  PUSSIBLE
}Piece;

typedef enum Turn{
  FIRST,
  SECOND
}Turn;

typedef struct Point{
  int x;
  int y;
}Point;

typedef struct{
  Point start_point;
  Point end_point;
  Point dir;
}reverse_line;

void *create_board();
void render(OBoard);
void input(OBoard, Point *move_point);
bool put_check(Point *move_point);
void reverse_check( Point *move_point);
void move( Point *move_point);
void reverse(reverse_line line);
bool board_check(void);
void check_winner(void);
