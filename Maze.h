#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "Cell.h"

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define COLOR_NORM 1
#define COLOR_WALL 2
#define COLOR_PATH 3
#define COLOR_TRAVEL 4
#define COLOR_BACKTRACK 5

class Maze {
    int width;
    int height;
    int cells;
    struct position {
      int x;
      int y;
    } pos;
    struct position pos2;
    std::vector<position> pos_history;
    std::vector< std::vector<Cell*> > grid;
    #ifdef _DEBUG
    std::vector< std::vector<bool> > screen;
    #endif
    bool initialized;
    bool seeded;
  public:
    // Constructors
    Maze(int x, int y);
    Maze(int x, int y, int s);
    Maze(int x, int y, int s_x, int s_y);
    Maze(int x, int y, int s_x, int s_y, int s);

    // Deconstructor
    ~Maze();
    
    // Getters
    Cell getCell(int x, int y);
    int getWidth();
    int getHeight();
    int getCellCount();
    bool isInitialized();
    bool isVisited(int x, int y);
    int getXPos();
    int getYPos();
    int getXPos2();
    int getYPos2();

    // Setters
    void setPosX(int x);
    void setPosY(int y);
    void setPosX2(int x);
    void setPosY2(int y);
    void setPos(int x, int y);
    void setPos2(int x , int y);
    void setWidth(int w);
    void setHeight(int h);
    void setVisited(int x, int y);

    // Methods that traverse the maze
    bool goNorth();
    bool goEast();
    bool goSouth();
    bool goWest();
    void goBack();
    void goBack(int s);
    bool breakNorth();
    bool breakEast();
    bool breakSouth();
    bool breakWest();
    int testNorth();
    int testEast();
    int testSouth();
    int testWest();
    void pushPosition();
    void popPosition();

    // Other Methods
    void initialize();
    void initialize(int x, int y);
    #ifndef _DEBUG
    void drawCell(int x, int y);
    #else
    void renderCell(int x, int y);
    #endif
    void drawBackground();
    void drawBorder();
    void drawMaze();
    #ifdef _DEBUG
    void renderMaze();
    #endif
    void printMaze();
    void printPosStack();
    void seed();
    void seed(int s);
    int transX(int x);
    int transY(int y);
    void reset();
};

#endif
