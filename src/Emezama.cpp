#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "Emezama.h"
#include "Maze.h"
#include "Window.h"
#include "Player.h"
#include <cstdlib>
#include "debug.h"


// Constructors
Emezama::Emezama() {
    // Initialize the screen
    initscr();
    if (has_colors() == false) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    noecho(); // Don't echo key presses
    cbreak(); // Capture all input
    nodelay(stdscr, true);
    curs_set(0); // Don't show the curser
    // Start color mode and initialize our color pairs
    start_color();
    // COLOR_NORM is used for everything not in the maze
    // COLOR_WALL is used for the maze walls
    // COLOR_PATH is used for the maze path
    init_pair(COLOR_NORM, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_WALL, COLOR_BLACK, COLOR_RED);
    init_pair(COLOR_PATH, COLOR_RED, COLOR_WHITE);
    init_pair(COLOR_TRAVEL, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(COLOR_BACKTRACK, COLOR_GREEN, COLOR_GREEN);

    setScreenWidth(COLS);
    setScreenHeight(LINES);
#ifdef _DEBUG // Use a constant seed if in debug mode
    gameMaze = new Maze((getScreenWidth() / 2) - 2, (getScreenHeight() / 2) - 2, DEBUG_START_X, DEBUG_START_Y,  DEBUG_SEED);
#else
    gameMaze = new Maze((getScreenWidth() / 2) - 2, (getScreenHeight() / 2) - 2);
#endif

    gameMaze->drawMaze();
    gamePlayer = new Player('A');
    gamePlayer->enter(gameMaze);

    gameDestination = new Player(gameMaze->getWidth() / 2, gameMaze->getHeight() / 2, 'E');
    gameDestination->enter2(gameMaze);


}


// Deconstructor
Emezama::~Emezama() {
    if (gameMaze) delete gameMaze;
    if (gamePlayer) delete gamePlayer;
    if (gameDestination) delete gameDestination;
}

void Emezama::restart() {
    //if (gameMaze) delete gameMaze;
    if (gamePlayer) delete gamePlayer;
    //if (gameDestination) delete gameDestination;

    // Initialize the screen
    initscr();
    if (has_colors() == false) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    noecho(); // Don't echo key presses
    cbreak(); // Capture all input
    nodelay(stdscr, true);
    curs_set(0); // Don't show the curser
    // Start color mode and initialize our color pairs
    start_color();
    // COLOR_NORM is used for everything not in the maze
    // COLOR_WALL is used for the maze walls
    // COLOR_PATH is used for the maze path
    init_pair(COLOR_NORM, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_WALL, COLOR_BLACK, COLOR_RED);
    init_pair(COLOR_PATH, COLOR_RED, COLOR_WHITE);
    init_pair(COLOR_TRAVEL, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(COLOR_BACKTRACK, COLOR_GREEN, COLOR_GREEN);

    setScreenWidth(COLS);
    setScreenHeight(LINES);
#ifdef _DEBUG // Use a constant seed if in debug mode
    gameMaze = new Maze((getScreenWidth() / 2) - 2, (getScreenHeight() / 2) - 2, DEBUG_START_X, DEBUG_START_Y,  DEBUG_SEED);
#else
    //gameMaze = new Maze((getScreenWidth() / 2) - 2, (getScreenHeight() / 2) - 2);
#endif

    gameMaze->drawMaze();
    gamePlayer = new Player('A');
    gamePlayer->enter(gameMaze);

    //gameDestination = new Player(rand()%(gameMaze->getWidth()/2) + gameMaze->getWidth(), rand()%(gameMaze->getHeight()/2) + gameMaze->getHeight(), 'E');
    //gameDestination->enter2(gameMaze);
}

// Private Setters
void Emezama::setScreenWidth(int w) {
    screen.width = w;
}

void Emezama::setScreenHeight(int h) {
    screen.height = h;
}

// Getters
int Emezama::getScreenWidth() {
    return screen.width;
}

int Emezama::getScreenHeight() {
    return screen.height;
}

// Other Methods
void Emezama::resize() { // Re generate the maze
    setScreenWidth(COLS);
    setScreenHeight(LINES);

    if (gameMaze) delete gameMaze;

    clear();

#ifdef _DEBUG // Use a constant seed if in debug mode
    gameMaze = new Maze((getScreenWidth() / 2) - 2, (getScreenHeight() / 2) - 2, DEBUG_START_X, DEBUG_START_Y,  DEBUG_SEED);
#else
    gameMaze = new Maze((getScreenWidth() / 2) - 2, (getScreenHeight() / 2) - 2);
#endif

    gameMaze->drawMaze();
    gamePlayer->enter(gameMaze);
    gamePlayer->draw(gameMaze);

    gameDestination->enter2(gameMaze);
    gameDestination->draw(gameMaze);
}

// This method displays the title screen
void Emezama::title() {
    Window *title = new Window();
    //gameMaze->drawMaze();
    //title->clear();
    title->draw();
    title->print("Hello!!\nWelcome to Emezama!!\n\n A simple maze game.");
    getch();
    delete title;
}


// This is the main game loop, it reads input and moves the player
void Emezama::run() {

    while (true) {
        std::cout << "Select an option(1-5):\n";
        std::cout << "1) DFS\n";
        std::cout << "2) BFS\n";
        std::cout << "3) AStar\n";
        std::cout << "4) Best First\n";
        std::cout << "5) Exit\n";
        std::cout << "Type:";

        int x = getchar() - '0';
        gamePlayer->draw(gameMaze);
        gameDestination->draw(gameMaze);
        refresh();
        int nodesN;
        switch (x) {
            case 1:
                nodesN = searchingAlgorithms.DFS(*gameMaze, *gamePlayer, *gameDestination);

                break;
            case 2:
                nodesN = searchingAlgorithms.BFS(*gameMaze, *gamePlayer, *gameDestination);

                break;
            case 3:
                nodesN = searchingAlgorithms.AStar(*gameMaze, *gamePlayer, *gameDestination);
                break;
            case 4:
                nodesN = searchingAlgorithms.BestFirst(*gameMaze, *gamePlayer, *gameDestination);
                break;
            case 5:
                return;
            default:
                break;
        }


        endwin();

        for (int i = 0; i < 100; i++)
            std::cout << "\n";
        std::cout << "Nodes Visited: " << nodesN << "\n\n\n\n";

        restart();
    }

}

void Emezama::quit() {
    endwin();
}
