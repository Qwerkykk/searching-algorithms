#ifndef SEARCHING_ALGORITHMS_H
#define SEARCHING_ALGORITHMS_H

#include "Stack.h"
#include "Maze.h"
#include "List.h"
#include "Player.h"


class SearchingAlgorithms {
public:
    enum class Move {
        UP, DOWN, RIGHT, LEFT, NONE
    };

    int DFS(Maze& maze, Player& player, Player& destination);

    int BFS(Maze& maze, Player& player, Player& destination);

    int BestFirst(Maze& maze, Player& player, Player& destination);

    int AStar(Maze& maze, Player& player, Player& destination);


private:
    struct CellPath {
        int x;
        int y;
        Move move;

        CellPath(int x_, int y_, Move move_) {
            x = x_;
            y = y_;
            move = move_;
        }

        bool operator==(const struct CellPath& cell) const{
            return (x == cell.x && y == cell.y);
        }


    };

    void AddSuccessorCells(List<struct CellPath>& successorCells, Maze& maze);

    bool IsVisited(List<struct CellPath>& visitedCells, struct CellPath& cell);

    bool IsGoalState(Maze& maze);

    void DrawPathToGoal(Maze& maze, Player& player, List<struct CellPath>& visitedCells, Player& destination);

    void DrawStep(Maze& maze, struct CellPath& cell, Player& player, int color);

    int ManhattanDistance(Maze& maze, struct CellPath& cell);

};


#endif
