/*  Name: Cell.cpp
 *
 *  Description: 
 *    This class represents one cell in a maze. Four booleans represent each
 *    wall of the cell, and one boolean represeents whether or not the cell
 *    has been visited.
 */

#include "Cell.h"
#include "debug.h"

// Constructors
Cell::Cell() {
  northWall = true;
  eastWall  = true;
  southWall = true;
  westWall  = true;
  beenVisited = false;
}
Cell::Cell(Cell* oldCell) {
  northWall = oldCell->north();
  eastWall  = oldCell->east();
  southWall = oldCell->south();
  westWall  = oldCell->west();
  beenVisited = oldCell->visited();
}

// Deconstructor
Cell::~Cell() {
}

// Getters
bool Cell::north() {
  return northWall;
}
bool Cell::east() {
  return eastWall;
}
bool Cell::south() {
  return southWall;
}
bool Cell::west() {
  return westWall;
}
bool Cell::visited() {
  return beenVisited;
}

// Setters
void Cell::setNorth(bool u) {
  northWall = u;
}
void Cell::setEast(bool u) {
  eastWall = u;
}
void Cell::setSouth(bool u) {
  southWall = u;
}
void Cell::setWest(bool u) {
  westWall = u;
}
void Cell::setVisited() {
  setVisited(true);
}
void Cell::setVisited(bool v) {
  beenVisited = v;
}
