#include <string>
#include <ncurses.h>
#include "Player.h"
#include "Maze.h"
#include "debug.h"

// Constructors
Player::Player() {
  setName("Bob");
  setPosX(0);
  setPosY(0);
  setPosCell(CENTER);
  setBody('B');
}
Player::Player(char b) {
  setName("Bob");
  setPosX(0);
  setPosY(0);
  setPosCell(CENTER);
  setBody(b);
}
Player::Player(int x, int y) {
  setName("Bob");
  setPosX(x);
  setPosY(y);
  setPosCell(CENTER);
  setBody('B');
}
Player::Player(int x, int y, char b) {
  setName("Bob");
  setPosX(x);
  setPosY(y);
  setPosCell(CENTER);
  setBody(b);
}

// Getters
int Player::getPosX() {
  return pos.x;
}
int Player::getPosY() {
  return pos.y;
}
int Player::getPosCell() {
  return pos.cell;
}
std::string Player::getName() {
  return name;
}

// Setters
void Player::setPosX(int x) {
  if ( x < 0 ) x = 0;
  pos.x = x;
}
void Player::setPosY(int y) {
  if ( y < 0 ) y = 0;
  pos.y = y;
}
void Player::setPosCell(int c) {
  pos.cell = c;
}
void Player::setName(std::string n) {
  name = n;
}
void Player::setBody(char c) {
  body = c;
}

// Other
bool Player::goNorth(Maze* m) {
  if ( pos.cell == SOUTH ) {
    erase(m);
    pos.cell = CENTER;
    draw(m);
    #ifdef _DEBUG
    printPosition();
    #endif
    return true;
  } else if ( pos.cell == CENTER || pos.cell == NORTH) {
    if (m->goNorth() ) {
      erase(m);
      pos.y++;
      if ( pos.cell == CENTER ) {
        pos.cell = SOUTH;
      } else {
        pos.cell = CENTER;
      }
      draw(m);
      #ifdef _DEBUG
      printPosition();
      #endif
      return true;
    }
  }
  return false;
}
bool Player::goEast(Maze* m) {
  if ( pos.cell == WEST ) {
    erase(m);
    pos.cell = CENTER;
    draw(m);
    #ifdef _DEBUG
    printPosition();
    #endif
    return true;
  } else if ( pos.cell == CENTER || pos.cell == EAST) {
    if ( m->goEast() ) {
      erase(m);
      pos.x++;
      if ( pos.cell == CENTER ) {
        pos.cell = WEST;
      } else {
        pos.cell = CENTER;
      }
      draw(m);
      #ifdef _DEBUG
      printPosition();
      #endif
      return true;
    }
  }
  return false;
}
bool Player::goSouth(Maze* m) {
  if ( pos.cell == NORTH ) {
    erase(m);
    pos.cell = CENTER;
    draw(m);
    #ifdef _DEBUG
    printPosition();
    #endif
    return true;
  } else if ( pos.cell == CENTER || pos.cell == SOUTH ) {
    if ( m->goSouth() ) {
      erase(m);
      pos.y--;
      if ( pos.cell == CENTER ) {
        pos.cell = NORTH;
      } else {
        pos.cell = CENTER;
      }
      draw(m);
      #ifdef _DEBUG
      printPosition();
      #endif
      return true;
    }
  }
  return false;
}
bool Player::goWest(Maze* m) {
  if ( pos.cell == EAST ) {
    erase(m);
    pos.cell = CENTER;
    draw(m);
    #ifdef _DEBUG
    printPosition();
    #endif
    return true;
  } else if ( pos.cell == CENTER || pos.cell == WEST ) {
    if ( m->goWest() ) {
      erase(m);
      pos.x--;
      if ( pos.cell == CENTER ) {
        pos.cell = EAST;
      } else {
        pos.cell = CENTER;
      }
      draw(m);
      #ifdef _DEBUG
      printPosition();
      #endif
      return true;
    }
  }
  return false;
}
void Player::enter(Maze* m) {
  #ifdef _DEBUG
  printPosition();
  #endif
  if ( getPosX() >= m->getWidth() ) {
    setPosX(m->getWidth() - 1);
  }
  if ( getPosY() >= m->getHeight() ) {
    setPosY(m->getHeight() - 1);
  }
  m->setPos(getPosX(), getPosY());
}

void Player::enter2(Maze* m) {
  #ifdef _DEBUG
  printPosition();
  #endif
  if ( getPosX() >= m->getWidth() ) {
    setPosX(m->getWidth() - 1);
  }
  if ( getPosY() >= m->getHeight() ) {
    setPosY(m->getHeight() - 1);
  }
  m->setPos2(getPosX(), getPosY());
}

void Player::erase(Maze* m) {
  attrset(COLOR_PAIR(COLOR_TRAVEL));
  switch (pos.cell) {
    case CENTER:
      mvprintw(m->transY(getPosY()), m->transX(getPosX()), " ");
      break;
    case NORTH:
      mvprintw(m->transY(getPosY()) - 1, m->transX(getPosX()), " ");
      break;
    case EAST:
      mvprintw(m->transY(getPosY()), m->transX(getPosX()) + 1, " ");
      break;
    case SOUTH:
      mvprintw(m->transY(getPosY()) + 1, m->transX(getPosX()), " ");
      break;
    case WEST:
      mvprintw(m->transY(getPosY()), m->transX(getPosX()) - 1, " ");
      break;
  }
  attrset(COLOR_PAIR(COLOR_NORM));
}

void Player::draw(Maze* m,int color) {
    attrset(COLOR_PAIR(color));
    switch (pos.cell) {
        case CENTER:
            mvprintw(m->transY(getPosY()), m->transX(getPosX()), " ");
            break;
        case NORTH:
            mvprintw(m->transY(getPosY()) - 1, m->transX(getPosX()), " ");
            break;
        case EAST:
            mvprintw(m->transY(getPosY()), m->transX(getPosX()) + 1, " ");
            break;
        case SOUTH:
            mvprintw(m->transY(getPosY()) + 1, m->transX(getPosX()), " ");
            break;
        case WEST:
            mvprintw(m->transY(getPosY()), m->transX(getPosX()) - 1, " ");
            break;
    }
    attrset(COLOR_PAIR(COLOR_NORM));
}

void Player::draw(Maze* m) {
    attrset(COLOR_PAIR(COLOR_PATH));
    switch (pos.cell) {
        case CENTER:
            mvprintw(m->transY(getPosY()), m->transX(getPosX()), "%c", body);
            break;
        case NORTH:
            mvprintw(m->transY(getPosY()) - 1, m->transX(getPosX()), "%c", body);
            break;
        case EAST:
            mvprintw(m->transY(getPosY()), m->transX(getPosX()) + 1, "%c", body);
            break;
        case SOUTH:
            mvprintw(m->transY(getPosY()) + 1, m->transX(getPosX()), "%c", body);
            break;
        case WEST:
            mvprintw(m->transY(getPosY()), m->transX(getPosX()) - 1, "%c", body);
            break;
    }
    attrset(COLOR_PAIR(COLOR_NORM));
}
#ifdef _DEBUG
void Player::printPosition() {
  mvprintw(1, 20, "(%2i, %2i) P:%i", getPosX(), getPosY(), pos.cell);
}
#endif
