#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "othello.h"



static const Point dir[] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, 
                           {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
static const char ordinate[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

void *create_board()
{
  Board *board = ec_malloc(sizeof(Board));
  init_board(board);
  return board;
}

static void init_board(Board *board)
{
  int x, y;

  for( y = 0; y < ROW; y++)
  {
    for( x = 0; x < COL; x++)
    {
      board->cell[y][x] = EMPTY;
    }
  }

  board->cell[3][3] = BLACK;
  board->cell[3][4] = WHITE;
  board->cell[4][3] = WHITE;
  board->cell[4][4] = BLACK;
  board->turn = BLACK;
}

bool get_pussible_points(Board *board)
{
  int x, y;
  int count;
  int current_index = 0;
  Point point;
  
  sweep_pussible(board);

  for( y = 0; y < ROW; y++)
  {
    for( x = 0; x < COL; x++)
    {
      if(board->cell[y][x] != EMPTY)
        continue;
      point.x = x;
      point.y = y;
      if(isPussible(board, point))
      {
        board->pussible_points[current_index] = point;
        board->pcells_num = current_index + 1;
        current_index++;
      }
    }
  }
  return (current_index != 0);
}

static bool isPussible(Board *board, Point point)
{
  int i;
  int x,y;
  int count;
  const Piece own_piece = board->turn;
  const Piece opponent_piece = get_opponent_piece(own_piece); 
  Point check_point;

  for(i = 0; i < 8; i++)
  {
    check_point.x = point.x + dir[i].x;
    check_point.y = point.y + dir[i].y;
    count = 0;
    if(!is_on_board(check_point))
      continue;
   while(is_on_board(check_point))
   {
   if(board->cell[check_point.y][check_point.x] == opponent_piece)
     {
      count++;
     }
     else if(board->cell[check_point.y][check_point.x] == own_piece &&
             count != 0)
     {
       return true;
     }
     else
       break;
     check_point.x += dir[i].x;
     check_point.y += dir[i].y;
     }
  }
  return false;
}

static void sweep_pussible(Board *board)
{
  int x, y;

  for( y = 0; y < ROW; y++)
  {
    for( x = 0; x < COL; x++)
    {
      if(board->cell[y][x] == PUSSIBLE)
        board->cell[y][x] = EMPTY;
    }
  }
} 

Piece get_opponent_piece(Piece piece)
{
  return (piece == BLACK) ? WHITE : BLACK;
}

bool is_on_board(Point point)
{
  return (0 <= point.x && point.x < COL) || (0 <= point.y  && point.y < ROW);
}

void update_board(Board *board)
{
  int i;
  int x, y;
  Point pussible_point;

  for(i = 0; i < board->pcells_num; i++)
  {
    pussible_point = board->pussible_points[i];
    x = pussible_point.x;
    y = pussible_point.y;
    
    board->cell[y][x] = PUSSIBLE;
  }
}

void change_turn(Board *board)
{
  Piece next_turn = get_opponent_piece(board->turn);
  board->turn = next_turn;
}

void render(Board *board)
{
  int x, y;

  for(y = 0; y < ROW; y++)
    printf(" %d", y);
  puts("");
  for(y = 0; y < ROW; y++)
  {
    printf("%c", ordinate[y]);
    for(x = 0; x < COL; x++)
    {
      switch(board->cell[y][x])
      {
        case BLACK:
          printf("○ ");
          break;
        case WHITE:
          printf("● ");
          break;
        case EMPTY:
          printf("□ ");
          break;
        case PUSSIBLE:
          printf("× ");
      }
    }
    puts("");
  }
}

/*
Point get_move()
{
  int x;
  int y;
}
*/


bool put_piece(Board *board, Piece piece, Point move)
{
  if(is_on_board(move) || (board->cell[move.y][move.x] == PUSSIBLE) )
  {
    board->cell[move.y][move.x] = piece;
    return true;
  }
  else
  {
    printf("The cell is impossible to put the piece\n");
    return false;
  }
}

static void *ec_malloc(unsigned int size)
{
  void *ptr;
  ptr = malloc(size);
  if(ptr == NULL)
  {
    fprintf(stderr, "Error: failed memory allocate");
    exit(-1);
  }
  return ptr;
}

int main(void)
{
  OBoard board;
  board = create_board();
  get_pussible_points(board);
  update_board(board);
  render(board);
  return 0;
}
