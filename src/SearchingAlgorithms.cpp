#include <ncurses.h>
#include <thread>
#include <cmath>
#include <chrono>

#include "Player.h"
#include "SearchingAlgorithms.h"
#include "PriorityQueue.h"
#include "Queue.h"

int SearchingAlgorithms::DFS(Maze& maze, Player& player, Player& destination) {
    Stack<struct CellPath> fringe;
    List<struct CellPath> visitedCells;
    List<struct CellPath> successorCells;

    fringe.Push(CellPath(maze.getXPos(), maze.getYPos(), Move::NONE));

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // For "Animation"

        if (fringe.Empty()) {
            std::cout << "Fringe is empty\n";
            exit(1);
        }

        CellPath cell = fringe.Top();
        fringe.Pop();
        visitedCells.PushFront(cell);


        DrawStep(maze, cell, player, COLOR_TRAVEL);


        if (IsGoalState(maze)) {
            DrawPathToGoal(maze, player, visitedCells, destination);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return visitedCells.Size();
        }

        AddSuccessorCells(successorCells, maze);

        for (auto& successorCell: successorCells) {
            if (fringe.Contains(successorCell) || IsVisited(visitedCells, successorCell))
                continue;

            fringe.Push(successorCell);
        }
        successorCells.Clear();
    }

}


int SearchingAlgorithms::BFS(Maze& maze, Player& player, Player& destination) {
    Queue<struct CellPath> fringe;
    List<struct CellPath> visitedCells;
    List<struct CellPath> successorCells;

    fringe.Push(CellPath(maze.getXPos(), maze.getYPos(), Move::NONE));

    while (true) {
        if (fringe.Empty()) {
            std::cout << "Fringe is empty\n";
            exit(1);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        CellPath cell = fringe.Front();
        fringe.Pop();
        visitedCells.PushFront(cell);

        DrawStep(maze, cell, player, COLOR_TRAVEL);


        if (IsGoalState(maze)) {
            DrawPathToGoal(maze, player, visitedCells, destination);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return visitedCells.Size();
        }

        AddSuccessorCells(successorCells, maze);

        for (auto& successorCell: successorCells) {

            if (fringe.Contains(successorCell) || IsVisited(visitedCells, successorCell))
                continue;

            fringe.Push(successorCell);
        }

        successorCells.Clear();
    }
}

int SearchingAlgorithms::AStar(Maze& maze, Player& player, Player& destination) {

    PriorityQueue<struct CellPath> fringe;
    List<struct CellPath> visitedCells;
    List<struct CellPath> successorCells;

    fringe.Push(CellPath(maze.getXPos(), maze.getYPos(), Move::NONE), maze.getXPos2() + maze.getYPos2());


    while (true) {
        if (fringe.Empty()) {
            std::cout << "Fringe is empty\n";
            exit(1);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        CellPath cell = fringe.Top();
        int priority = fringe.TopPriority();
        fringe.Pop();
        visitedCells.PushFront(cell);

        DrawStep(maze, cell, player, COLOR_TRAVEL);


        if (IsGoalState(maze)) {
            DrawPathToGoal(maze, player, visitedCells, destination);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return visitedCells.Size();
        }

        AddSuccessorCells(successorCells, maze);

        int distanceFromStart = priority - ManhattanDistance(maze, cell) + 1;

        for (auto& successorCell: successorCells) {
            if (IsVisited(visitedCells, successorCell))
                continue;

            int heuristicDistance = ManhattanDistance(maze, successorCell);
            if (!fringe.Contains(successorCell)) {
                fringe.Push(successorCell, distanceFromStart + heuristicDistance);
                continue;
            }
            fringe.UpdatePriority(successorCell, distanceFromStart + heuristicDistance);
        }

        successorCells.Clear();
    }

}


int SearchingAlgorithms::BestFirst(Maze& maze, Player& player, Player& destination) {

    PriorityQueue<struct CellPath> fringe;
    List<struct CellPath> visitedCells;
    List<struct CellPath> successorCells;

    fringe.Push(CellPath(maze.getXPos(), maze.getYPos(), Move::NONE), maze.getXPos2() + maze.getYPos2());


    while (true) {
        if (fringe.Empty()) {
            std::cout << "Fringe is empty\n";
            exit(1);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        CellPath cell = fringe.Top();
        fringe.Pop();
        visitedCells.PushFront(cell);

        DrawStep(maze, cell, player, COLOR_TRAVEL);


        if (IsGoalState(maze)) {
            DrawPathToGoal(maze, player, visitedCells, destination);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            return visitedCells.Size();
        }

        AddSuccessorCells(successorCells, maze);



        for (auto& successorCell: successorCells) {
            if (IsVisited(visitedCells, successorCell))
                continue;

            int heuristicDistance = ManhattanDistance(maze, successorCell);
            if (!fringe.Contains(successorCell)) {
                fringe.Push(successorCell,  heuristicDistance);
                continue;
            }
            fringe.UpdatePriority(successorCell, heuristicDistance);
        }

        successorCells.Clear();
    }

}

void SearchingAlgorithms::DrawPathToGoal(Maze& maze, Player& player, List<struct CellPath>& visitedCells,
                                         Player& destination) {
    struct CellPath parentCell = visitedCells.Front();

    for (auto& cell : visitedCells) {

        if (parentCell.x == cell.x && parentCell.y == cell.y) {
            switch (cell.move) {

                case Move::UP:
                    parentCell.y--;
                    break;
                case Move::DOWN:
                    parentCell.y++;
                    break;
                case Move::RIGHT:
                    parentCell.x--;
                    break;
                case Move::LEFT:
                    parentCell.x++;
                    break;
                case Move::NONE:
                    break;
            }


            std::this_thread::sleep_for(std::chrono::milliseconds(10)); //For "Animation
            DrawStep(maze, cell, player, COLOR_BACKTRACK);

            if (cell.x == visitedCells.Front().x && cell.y == visitedCells.Front().y) {
                destination.draw(&maze);
                refresh();
            }
        }
    }

}


bool SearchingAlgorithms::IsVisited(List<struct CellPath>& visitedCells, struct CellPath& cell) {
    for (auto it = visitedCells.begin(); it != visitedCells.end(); it++) {
        if (it->x == cell.x && it->y == cell.y)
            return true;
    }

    return false;
}


bool SearchingAlgorithms::IsGoalState(Maze& maze) {
    if (maze.getXPos() == maze.getXPos2() && maze.getYPos() == maze.getYPos2())
        return true;

    return false;
}

void SearchingAlgorithms::AddSuccessorCells(List<struct CellPath>& successorCells, Maze& maze) {
    int x = maze.getXPos(), y = maze.getYPos();


    if (maze.goEast()) {
        successorCells.PushFront(CellPath(maze.getXPos(), maze.getYPos(), Move::RIGHT));
        maze.setPos(x, y);
    }

    if (maze.goNorth()) {
        successorCells.PushFront(CellPath(maze.getXPos(), maze.getYPos(), Move::UP));
        maze.setPos(x, y);
    }

    if (maze.goWest()) {
        successorCells.PushFront(CellPath(maze.getXPos(), maze.getYPos(), Move::LEFT));
        maze.setPos(x, y);
    }

    if (maze.goSouth()) {
        successorCells.PushFront(CellPath(maze.getXPos(), maze.getYPos(), Move::DOWN));
        maze.setPos(x, y);
    }


}


void SearchingAlgorithms::DrawStep(Maze& maze, struct CellPath& cell, Player& player, int color) {
    player.setPosX(cell.x);
    player.setPosY(cell.y);
    maze.setPos(cell.x, cell.y);
    switch (cell.move) {

        case Move::UP:
            player.setPosCell(SOUTH);
            player.draw(&maze, color);
            player.setPosCell(CENTER);
            player.draw(&maze, color);
            break;
        case Move::DOWN:
            player.setPosCell(NORTH);
            player.draw(&maze, color);
            player.setPosCell(CENTER);
            player.draw(&maze, color);
            break;
        case Move::RIGHT:
            player.setPosCell(WEST);
            player.draw(&maze, color);;
            player.setPosCell(CENTER);
            player.draw(&maze, color);
            break;
        case Move::LEFT:
            player.setPosCell(EAST);
            player.draw(&maze, color);
            player.setPosCell(CENTER);
            player.draw(&maze, color);
            break;
        case Move::NONE:
            break;
    }
    refresh();

}


int SearchingAlgorithms::ManhattanDistance(Maze& maze, SearchingAlgorithms::CellPath& cell) {
    return abs(maze.getXPos2() - cell.x) + abs(maze.getYPos2() - cell.y);
}




