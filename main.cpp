#include <stdlib.h>
#include <ncurses.h>
#include <signal.h>
#include "Emezama.h"
#include "debug.h"
#include <iostream>
#include <queue>
Emezama *game;

int main(int argc, char *argv[]) {

    game = new Emezama();
    game->run();
    game->quit();
    delete game;

    return 0;

}
