#ifndef CELL_H
#define CELL_H

class Cell {
    bool northWall;
    bool eastWall;
    bool southWall;
    bool westWall;
    bool beenVisited;
  public:
    // Constructors
    Cell();
    Cell(Cell* oldCell);

    // Deconstructor
    ~Cell();

    // Getters
    bool north();
    bool east();
    bool south();
    bool west();
    bool visited();

    // Setters
    void setNorth(bool u);
    void setEast(bool u);
    void setSouth(bool u);
    void setWest(bool u);
    void setVisited();
    void setVisited(bool v);
};

#endif
