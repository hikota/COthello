#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "othello.h"

typedef struct Board{
  Piece cell[ROW][COL];
  Turn turn;
}Board;

static void *ec_malloc(unsigned int);
static void init_board(Board *board);
Point get_move();
bool put_piece(Board *board, Piece piece, Point move);

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
  int y;
  int x;

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
  board->turn = FIRST;
}

void sweep_pussible(Board *board)
{
  int y;
  int x;

  for( y = 0; y < ROW; y++)
  {
    for( x = 0; x < COL; x++)
    {
      if(board->cell[y][x] == PUSSIBLE)
        board->cell[y][x] = EMPTY;
    }
  }
} 

void change_turn(Board *board)
{
  Turn next_turn = (board->turn == FIRST) ? SECOND : FIRST;
  board->turn = next_turn;
}

void update_board(Board *board, Turn turn)
{
  int y;
  int x;
  const Piece attacker_piece = (turn == FIRST) ? FIRST : SECOND;
  
  sweep_pussible(board);

  for( y = 0; y < ROW; y++)
  {
    for( x = 0; x < COL; x++)
    {
      if(board->cell[y][x] == attacker_piece)
      {

      }
    }
  }
}

void render(Board *board)
{
  int y;
  int x;

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
  if( (0 <= move.x && move.x < COL) || (0 <= move.y  && move.y < ROW) 
      || (board->cell[move.y][move.x] == PUSSIBLE) )
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
  render(board);
  return 0;
}
