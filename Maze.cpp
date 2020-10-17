/* Name: Maze.cpp
 * 
 * Description:
 *   This class represents a Maze object. The Cell class is utilized in this
 *   class. This class is used in the Ezemama game class.
 */

#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "Maze.h"
#include "debug.h"

// Constructors
Maze::Maze(int x, int y) {
  setWidth(x);
  setHeight(y);
  seed();
  initialize(0, 0);
}
Maze::Maze(int x, int y, int s) {
  setWidth(x);
  setHeight(y);
  seed(s);
  initialize(0, 0);
}
Maze::Maze(int x, int y, int s_x, int s_y) {
  setWidth(x);
  setHeight(y);
  seed();
  initialize(s_x, s_y);
}
Maze::Maze(int x, int y, int s_x, int s_y, int s) {
  setWidth(x);
  setHeight(y);
  seed(s);
  initialize(s_x, s_y);
}
Maze::~Maze() {
  for ( int i = 0; i < width; i++ ) {
    for ( int j = 0; j < height; j++ ) {
      if ( grid[i][j] ) delete grid[i][j];
    }
  }
}

// Getters
Cell Maze::getCell(int x, int y) {
  Cell* myCell;
  myCell = new Cell(grid[x][y]);
  return myCell;
}
int Maze::getWidth() {
  return width;
}
int Maze::getHeight() {
  return height;
}
int Maze::getCellCount() {
  return height * width;
}
bool Maze::isInitialized() {
  return initialized;
}
bool Maze::isVisited(int x, int y) {
  bool v = grid[x][y]->visited();
  return v;
}
int Maze::getXPos() {
  return pos.x;
}
int Maze::getYPos() {
  return pos.y;
}

int Maze::getXPos2(){
  return pos2.x;
}

int Maze::getYPos2(){
  return pos2.y;
}



// Setters
void Maze::setPosX(int x) {
  pos.x = x;
}
void Maze::setPosY(int y) {
  pos.y = y;
}

void Maze::setPosX2(int x){
  pos2.x = x;
}

void Maze::setPosY2(int y){
  pos2.y = y;
}

void Maze::setPos2(int x , int y){
  setPosX2(x);
  setPosY2(y);
}


void Maze::setPos(int x, int y) {
  setPosX(x);
  setPosY(y);
}
void Maze::setWidth(int w) {
  width = w;
}
void Maze::setHeight(int h) {
  height = h;
}
void Maze::setVisited(int x, int y) {
  grid[x][y]->setVisited();
}

// Methods that traverse the maze
bool Maze::goNorth() {
  // Check if possible
  if (    (pos.y + 1) == height // Already at the top
       || grid[pos.x][pos.y]->north() // north wall of our cell not open
       || grid[pos.x][pos.y+1]->south() ) { // South wall of northern cell closed
    return false;
  }
  // Save the current position
  pushPosition();
  // Move North
  pos.y++;
  return true;
}
bool Maze::goEast() {
  if (    (pos.x + 1) == width // Already farthest east
       || grid[pos.x][pos.y]->east() // east wall of our cell not open
       || grid[pos.x+1][pos.y]->west() ) { // West wall of eastern cell closed
    return false;
  }
  // Save the current position
  pushPosition();
  // Move East
  pos.x++;
  return true;
}
bool Maze::goSouth() {
  if (    pos.y == 0 // Already at bottom
       || grid[pos.x][pos.y]->south() // south wall of our cell is closed
       || grid[pos.x][pos.y-1]->north() ) {// North wall of sothern cell closed
    return false;
  }
  // Save the current position
  pushPosition();
  // Move south
  pos.y--;
  return true;
}
bool Maze::goWest() {
  if (    pos.x == 0 // Already far west
       || grid[pos.x][pos.y]->west() // west wall of our cell not open
       || grid[pos.x-1][pos.y]->east() ) { // East wall of wester cell closed
    return false;
  }
  // Save the current position
  pushPosition();
  // Move West
  pos.x--;
  return true;
}
void Maze::goBack() {
  popPosition();
}
void Maze::goBack(int s) {
  for ( int i =0; i < s; i++ ) {
    if ( pos_history.empty() ) {
      break;
    } else {
      popPosition();
    }
  }
}
bool Maze::breakNorth(){
  if ( (pos.y + 1) == height ) {
    return false; // Can't go north past the top
  }
  // Save the current location
  pushPosition();
  // Break the northern wall
  grid[pos.x][pos.y]->setNorth(false);
  #ifdef _DEBUG
  renderCell(pos.x, pos.y);
  #endif
  // Move to now cell
  pos.y++;
  // Break the new cell's southern wall
  grid[pos.x][pos.y]->setSouth(false);
  return true;
}
bool Maze::breakEast(){
  if ( (pos.x + 1) == width ) {
    return false; // Can't go off screen
  }
  // Save position
  pushPosition();
  // Break eastern wall
  grid[pos.x][pos.y]->setEast(false);
  #ifdef _DEBUG
  renderCell(pos.x, pos.y);
  #endif
  // Move east
  pos.x++;
  // Break the new cell's western wall
  grid[pos.x][pos.y]->setWest(false);
  return true;
}
bool Maze::breakSouth(){
  if ( pos.y == 0 ) {
    return false; // Can't go off screen
  }
  // Save position
  pushPosition();
  // Break Southern Wall
  grid[pos.x][pos.y]->setSouth(false);
  #ifdef _DEBUG
  renderCell(pos.x, pos.y);
  #endif
  // Move south
  pos.y--;
  // Break the new cell's northern wall
  grid[pos.x][pos.y]->setNorth(false);
  return true;
}
bool Maze::breakWest(){
  if ( pos.x == 0 ) {
    return false; // Can't go off screen
  }
  // Save position
  pushPosition();
  // Break the western wall
  grid[pos.x][pos.y]->setWest(false);
  #ifdef _DEBUG
  renderCell(pos.x, pos.y);
  #endif
  // Move west
  pos.x--;
  // Break the new cell's eastern wall
  grid[pos.x][pos.y]->setEast(false);
  return true;
}
int Maze::testNorth() {
  int total = 0;
  int i = 1;
  if ( (pos.y + 1) == height || isVisited(pos.x, pos.y + 1) ) {
    return 0;
  }
  while ( ((pos.y + i) < height) && !isVisited(pos.x, pos.y + i) ) {
    i++;
    total++;
  }
  return total;
}
int Maze::testEast() {
  int total = 0;
  int i = 1;
  if ( (pos.x + 1) == width || isVisited(pos.x + 1, pos.y) ) {
    return 0;
  }
  while ( ((pos.x + i) < width) && !isVisited(pos.x + i, pos.y) ) {
    i++;
    total++;
  }
  return total;
}
int Maze::testSouth() {
  int total = 0;
  int i = 1;
  if ( pos.y == 0 || isVisited(pos.x, pos.y - 1) ) {
    return 0;
  }
  while ( ((pos.y - i) >= 0) && !isVisited(pos.x, pos.y - i) ) {
    i++;
    total++;
  }
  return total;
}
int Maze::testWest() {
  int total = 0;
  int i = 1;
  if ( pos.x == 0 || isVisited(pos.x - 1, pos.y) ) {
    return 0;
  }
  while ( ((pos.x - i) >= 0) && !isVisited(pos.x - i, pos.y) ) {
    i++;
    total++;
  }
  return total;
}

void Maze::pushPosition() {
  pos_history.push_back(pos);
}
void Maze::popPosition() {
  pos = pos_history.back();
  pos_history.pop_back();
}

// Other methods
void Maze::initialize() {
  // Get the total number of cells and save it
  int total_cells = getCellCount();
  int visited_cells = 0;

  grid.resize(width);
  for ( int i = 0; i < width; i++ ) {
    grid[i].resize(height);
    for ( int j = 0; j < height; j++ ) {
      grid[i][j] = new Cell();
    }
  }

  #ifdef _DEBUG
  screen.resize((width * 2) + 3,  std::vector< bool >((height * 2) + 3, true));
  #endif
  
  // This array, paired with our directions definitions will track our
  // movement options
  int options[4];  
  int numOpts;  

  // use this integer to store random numbers
  int randno;

  int n = 0;
  int e = 0;
  int s = 0;
  int w = 0;
  int p = 0;

  #ifdef _DEBUG
  drawBackground();
  drawBorder();
  for ( int i = 5; i < 15; i++ ) {
    for ( int j = 5; j < 15; j++ ) {
      grid[i][j]->setNorth(false);
      grid[i][j]->setEast(false);
      grid[i][j]->setSouth(false);
      grid[i][j]->setWest(false);
      setVisited(i, j);
      visited_cells++;
    }
  }
  #endif

  // Until we have visited all cells...
  while ( visited_cells < total_cells ) {
    // Check if the current location is marked visited, if not, mark it and
    // increment the visited cell count
    if ( !(isVisited(pos.x, pos.y)) ) {
      setVisited(pos.x, pos.y);
      visited_cells++;
    }
    // Evaluation our options one by one
    options[NORTH] = testNorth();
    options[EAST]  = testEast();
    options[SOUTH] = testSouth();
    options[WEST]  = testWest();

    #ifdef _DEBUG
    renderCell(pos.x, pos.y);
    #endif

    // If we have no options, or one wall left, backtrack
    numOpts = 0;
    if ( options[NORTH] > 0 ) { numOpts++; };
    if ( options[EAST]  > 0 ) { numOpts++; };
    if ( options[SOUTH] > 0 ) { numOpts++; };
    if ( options[WEST]  > 0 ) { numOpts++; };
    if ( numOpts == 0 ) {
      popPosition();
      p++;
      continue;
    } 

    // Randomly select numbers from 0-3 until we get a valid options
    do {
      randno = rand() % 4;
    } while ( options[randno] == 0 );
    switch (randno) {
      case NORTH:
        for ( int i = 0; i < ( rand() % options[NORTH] + 1); i++ ) {
          breakNorth();
          if ( !(isVisited(pos.x, pos.y)) ) {
            setVisited(pos.x, pos.y);
            visited_cells++;
          }
          n++;
        }
        break;
      case EAST:
        for ( int i = 0; i < ( rand() % options[EAST] + 1); i++ ) {
          breakEast();
          if ( !(isVisited(pos.x, pos.y)) ) {
            setVisited(pos.x, pos.y);
            visited_cells++;
          }
          e++;
        }
        break;
      case SOUTH:
        for ( int i = 0; i < ( rand() % options[SOUTH] + 1); i++ ) {
          breakSouth();
          if ( !(isVisited(pos.x, pos.y)) ) {
            setVisited(pos.x, pos.y);
            visited_cells++;
          }
          s++;
        }
        break;
      case WEST:
        for ( int i = 0; i < ( rand() % options[WEST] + 1); i++ ) {
          breakWest();
          if ( !(isVisited(pos.x, pos.y)) ) {
            setVisited(pos.x, pos.y);
            visited_cells++;
          }
          w++;
        }
        break;
    }
    #ifdef _DEBUG
    mvprintw(0, 0, "%i / %i N:%i E:%i S:%i W:%i Rand:%i Pops:%i", visited_cells, total_cells, n, e, s, w, randno, p);
    mvprintw(1, 0, "X:%i Y:%i              ", pos.x, pos.y);
    refresh();
    usleep(SLOMO);
    #endif
    initialized = true;
  }
}
void Maze::initialize(int x, int y) {
  if ( x >= width ) x = width - 1;
  if ( x < 0 ) x = 0;
  if ( y >= height ) y = height - 1;
  if ( y < 0 ) y = 0;
  setPos(x, y);
  initialize();
}
void Maze::drawBackground() {
  attrset(COLOR_PAIR(COLOR_PATH));
  for ( int i = 0; i < ( 2 * width ); i++ ) {
    for ( int j = 0; j < (2 * height ); j++ ) {
      mvprintw((3 + j), (i + 2), " ");
    }
  }
  attrset(COLOR_PAIR(COLOR_NORM));
}
void Maze::drawBorder() {
  attrset(COLOR_PAIR(COLOR_WALL));
  for ( int i = 0; i < ( 2 * width ); i++ ) {
    mvprintw(2, i+2, " ");
    mvprintw( ( 2 * height ) + 2, i+2, " ");
  }
  for ( int i = 0; i < ( 2 * height ); i++ ) {
    mvprintw(i+3, 1, " ");
    mvprintw(i+3, ( 2 * width ) + 1, " ");
  }
  attrset(COLOR_PAIR(COLOR_NORM));

}
#ifndef _DEBUG
void Maze::drawMaze() {
  drawBackground();
#else
void Maze::renderMaze() {
#endif
  for ( int i = 0; i < width; i++ ) {
    for ( int j = 0; j < height; j++ ) {
      #ifndef _DEBUG
      drawCell(i, j);
      #else
      renderCell(i, j);
      #endif
    }
  }
  #ifndef _DEBUG
  drawBorder();
  #endif
}
#ifdef _DEBUG
void Maze::drawMaze() {
  for ( int i = 0; i < (2 * width); i++ ) {
    for ( int j = (2 * height) - 1; j >= 0; j-- ) {
      if ( screen[i][(height * 2) - j] ) {
        attrset(COLOR_PAIR(COLOR_WALL));
      } else {
        attrset(COLOR_PAIR(COLOR_PATH));
      }
      mvprintw(j+2, i+1, " ");
      attrset(COLOR_PAIR(COLOR_NORM));
    }
  }
}
#endif

void Maze::printMaze() {
  for ( int i = 0; i < width; i++ ) {
    for ( int j = 0; j < height; j++ ) {
      printf("(%i,%i) N%d E%d S%d W%d V%d\n", i, j, grid[i][j]->north(), grid[i][j]->east(), grid[i][j]->south(), grid[i][j]->west(), grid[i][j]->visited());
    }
  }
}
#ifndef _DEBUG
void Maze::drawCell(int x, int y) {
#else
void Maze::renderCell(int x, int y) {
#endif
  int pos_x;
  int pos_y;
  pos_x = transX(x);
  pos_y = transY(y);
  if (    !grid[x][y]->north() && !grid[x][y]->east()
       && !grid[x][y]->south() && !grid[x][y]->west()) {
    // If this cell has no walls, dont bother drawing it
    return;
  }
  #ifndef _DEBUG
  attrset(COLOR_PAIR(COLOR_WALL));
  mvprintw(pos_y - 1, pos_x - 1, "   ");
  mvprintw(pos_y, pos_x + 1, " ");
  #else
  //screen[ ( 2 * x ) ][ ( 2 * y ) + 2] = true;
  screen[ ( 2 * x ) + 1 ][ ( 2 * y ) + 1 ] = false;
  //screen[ ( 2 * x ) + 2 ][ ( 2 * y ) + 2 ] = true;
  //screen[ ( 2 * x ) + 2 ][ ( 2 * y ) ] = true;
  #endif
  attrset(COLOR_PAIR(COLOR_NORM));
  if ( !grid[x][y]->north() ) {
    #ifndef _DEBUG
    attrset(COLOR_PAIR(COLOR_PATH));
    mvprintw(pos_y - 1, pos_x, " ");
    #else
    screen[ ( 2 * x ) + 1][ ( 2 * y ) + 2] = false;
    #endif
  }
  if ( !grid[x][y]->east() ) {
    #ifndef _DEBUG
    attrset(COLOR_PAIR(COLOR_PATH));
    mvprintw(pos_y, pos_x + 1, " ");
    #else
    screen[ ( 2 * x ) + 2 ][ ( 2 * y ) + 1] = false;
    #endif
  }
  attrset(COLOR_PAIR(COLOR_NORM));
}
void Maze::seed() {
  srand(time(NULL));
  seeded = true;
}
void Maze::seed(int s) {
  srand(s);
  seeded = true;
}
int Maze::transX(int x) {
  return ( 2 * x ) + 2;
}
int Maze::transY(int y) {
  return ( 2 * ( height - y ) + 1);
}
void Maze::reset() {
  // Loop through all cells and reset their walls and visited boolean
  for ( int i = 0; i < width; i++ ) {
    for ( int j = 0; j < height; j++ ) {
      grid[i][j]->setVisited(false);
      grid[i][j]->setNorth(true);
      grid[i][j]->setEast(true);
      grid[i][j]->setSouth(true);
      grid[i][j]->setWest(true);
    }
  }
}
