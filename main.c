#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

// Only 3*3 and higher
#define WIDTH 20
#define HEIGHT 20

#define DEAD "#"
#define ALIVE "@"

typedef struct Cell {
  size_t x;
  size_t y;
  bool alive;
  unsigned char neighboors;
} Cell;


Cell map[WIDTH][HEIGHT] = { };

unsigned char checkNeighboors(size_t cx, size_t cy) {
  unsigned char neighboors = 0;

  size_t xlimit = cx + 2;
  size_t ylimit = cy + 2;

  int cell_x = cx;
  int cell_y = cy;

  if(cx == (WIDTH-1))
    xlimit--;
  else if (cx == 0)
    cx++;

  if(cy == (HEIGHT-1))
    ylimit--;
  else if(cy == 0)
    cy++;

  for(size_t y = cy-1; y < ylimit; y++) {
    for(size_t x = cx-1; x < xlimit; x++) {
      if(x == (size_t) cell_x && y == (size_t) cell_y)
        continue;
      if(map[x][y].alive)
        neighboors++;
    }
  }
  return neighboors;
}

void setNeighboors() {
  for(size_t y = 0; y < HEIGHT; y++) {
    for(size_t x = 0; x < WIDTH; x++) {
      Cell cell = map[x][y];
      map[x][y].neighboors = checkNeighboors(cell.x, cell.y);
    }
  }

}

void initRandomSet(void) {
  for(size_t y = 0; y < HEIGHT; y++) {
    for(size_t x = 0; x < WIDTH; x++) {
      Cell cell = {x, y, rand()%2, 0};
      map[x][y] = cell;
    }
  }
}

void printState(void) {
  for(size_t y = 0; y < HEIGHT; y++) {
    for(size_t x = 0; x < WIDTH; x++) {
      if(map[x][y].alive)
        printf("%s ", ALIVE);
      else
        printf("%s ", DEAD);
    }
    printf("\n");
  }
}

void printNeighboors(void) {
  for(size_t y = 0; y < HEIGHT; y++) {
    for(size_t x = 0; x < WIDTH; x++) {
        printf("%d ", map[x][y].neighboors);
    }
    printf("\n");
  }
}


int main(void) {
  srand(time(NULL));
  initRandomSet();
  setNeighboors();
  printState();
  printf("\n");
  printNeighboors();

  return 0;
}
