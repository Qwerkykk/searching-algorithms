#ifndef MAZE_GAME_H
#define MAZE_GAME_H

#include "Maze.h"
#include "Player.h"
#include "SearchingAlgorithms.h"

#define MY_KEY_UP    65
#define MY_KEY_DOWN  66
#define MY_KEY_LEFT  68
#define MY_KEY_RIGHT 67

class Emezama {
    // Stores the size of the screen
    struct {
      int width;
      int height; 
    } screen;
    Maze* gameMaze;
    Player* gamePlayer;
    Player* gameDestination;
    SearchingAlgorithms searchingAlgorithms;

    // Private setters
    void setScreenWidth(int w);
    void setScreenHeight(int h);
  public:
    // Constructors
    Emezama();
    // Deconstructor
    ~Emezama();
    
    // Getters
    int getScreenWidth();
    int getScreenHeight();

    // Other functions
    void restart();
    void resize();
    void title();
    void run();
    void quit();
};

#endif
