#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Maze.h"

#define CENTER 4


class Player {
    std::string name;
    struct position {
      int x;
      int y;
      int cell; // 0=N, 1=E, 2=S, 3=W, 4=C
    } pos;
    char body;
  public:
    // Constructors
    Player();
    Player(char b);
    Player(int x, int y);
    Player(int x, int y, char b);

    // Getters
    int getPosX();
    int getPosY();
    int getPosCell();
    std::string getName();

    // Setters
    void setPosX(int x);
    void setPosY(int y);
    void setPosCell(int c);
    void setBody(char c);
    void setName(std::string n);

    // Other
    bool goNorth(Maze* m);
    bool goEast(Maze* m);
    bool goSouth(Maze* m);
    bool goWest(Maze* m);
    void enter(Maze* m);
    void enter2(Maze* m);
    void erase(Maze* m);
    void draw(Maze* m,int color);
    void draw(Maze* m);
    #ifdef _DEBUG
    void printPosition();
    #endif

};

#endif
