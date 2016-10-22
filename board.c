#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "othello.h"

typedef struct Board{
  int cell[ROW][COL];
}Board;

static void *errorchecked_malloc(unsigned int);
static void init_board(Board *board);
Point get_move();
bool put_piece(Board *board, Piece piece, Point move);

void *create_board()
{
  Board *board = errorchecked_malloc(sizeof(Board));
  init_board(board);

  return board;
}

void init_board(Board *board)
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

  board->cell[3][3] =BLACK;
  board->cell[3][4] =WHITE;
  board->cell[4][3] =WHITE;
  board->cell[4][4] =BLACK;
}

void render(Board *board)
{
  int y;
  int x;


  for(y = 0; y < ROW; y++)
  {
    for(x = 0; x < COL; x++)
    {
      printf("%d", board->cell[y][x]);
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




static void *errorchecked_malloc(unsigned int size)
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
