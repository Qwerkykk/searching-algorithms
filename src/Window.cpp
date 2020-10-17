#include <ncurses.h>
#include <string>
#include "Window.h"

// COnstructors
Window::Window() {
  win.height = LINES / 2;
  win.width  = COLS  / 2;
  win.starty = (LINES - win.height)/2;
  win.startx = (COLS - win.width)/2;

  init();
}
Window::Window(int h, int w) {
  win.height = h;
  win.width  = w;
  win.starty = (LINES - win.height)/2;
  win.startx = (COLS - win.width)/2;

  init();
}
Window::Window(int h, int w, int x, int y) {
  win.height = h;
  win.width  = w;
  win.starty = y;
  win.startx = x;

  init();
}

// Getters
int Window::getCursorX() {
  return win.cursor.x;
}
int Window::getCursorY() {
  return win.cursor.y;
}
int Window::getRelativeCursorX() {
  return getCursorX() + getPosX();
}
int Window::getRelativeCursorY() {
  return getCursorY() + getPosY();
}
int Window::getHeight() {
  return win.height;
}
int Window::getWidth() {
  return win.width;
}
int Window::getPosX() {
  return win.startx;
}
int Window::getPosY() {
  return win.starty;
}

// Setters
void Window::setCursor(int x, int y) {
  setCursorX(x);
  setCursorY(y);
}
void Window::setCursorX(int x) {
  win.cursor.x = x;
}
void Window::setCursorY(int y) {
  win.cursor.y = y;
}

// Other methods
void Window::init() {
  win.cursor.x = 1;
  win.cursor.y = 1;
  win.border.ls = '|';
  win.border.rs = '|';
  win.border.ts = '-';
  win.border.bs = '-';
  win.border.tl = '+';
  win.border.tr = '+';
  win.border.bl = '+';
  win.border.br = '+';
}

bool Window::advanceCursor(char c) {
  if ( ( getCursorX() + 1 ) == getWidth() || c == '\n' ) { // At window EOL
    if ( ( getCursorY() + 1 ) == getHeight() ) { // At bottom of window
      return false;
    } else {
      setCursorX(1);
      setCursorY(getCursorY() + 1);
      return true;
    }
  } else {
    setCursorX(getCursorX() + 1);
    return true;
  }
}

void Window::print(std::string s) {
  for ( unsigned int i = 0; i < s.length(); i++) {
    if ( s[i] != '\n' ) {
      mvprintw(getRelativeCursorY(), getRelativeCursorX(), "%c", s[i]);
    }
    if(!advanceCursor(s[i])) break;
  }
  refresh();
}

void Window::print(int x, int y, std::string s) {
  setCursor(x, y);
  print(s);
}

void Window::draw() {
  createBox(true);
}

void Window::clear() {
  createBox(false);
}

void Window::createBox(bool flag) {
  int i, j;
  int x, y, w, h;

  x = win.startx;
  y = win.starty;
  w = win.width;
  h = win.height;

  if ( flag == true ) {
    mvaddch(y, x, win.border.tl);
    mvaddch(y, x + w, win.border.tr);
    mvaddch(y + h, x, win.border.bl);
    mvaddch(y + h, x + w, win.border.br);
    mvhline(y, x + 1, win.border.ts, w - 1);
    mvhline(y + h, x + 1, win.border.bs, w - 1);
    mvvline(y + 1, x, win.border.ls, h - 1);
    mvvline(y + 1, x + w, win.border.rs, h - 1);
  } else {
    for ( j = y; j <= y + h; ++j ) {
      for ( i = x; x <= x + w; ++i ) {
        mvaddch(j, i, ' ');
      }
    }
  }
  refresh();
}
