#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <string>

typedef struct _WIN_border_struct {
  chtype  ls, rs, ts, bs,
          tl, tr, bl, br;
}WIN_BORDER;

typedef struct _WIN_cursor {
  int x, y;
}WIN_CURSOR;

typedef struct _WIN_struct {
  int startx, starty;
  int height, width;
  WIN_BORDER border;
  WIN_CURSOR cursor;
}WIN;

class Window {
    WIN win;
  public:
    // Constructors
    Window();
    Window(int h, int w);
    Window(int x, int y, int h, int w);

    // Getters
    int getCursorX();
    int getCursorY();
    int getRelativeCursorX();
    int getRelativeCursorY();
    int getHeight();
    int getWidth();
    int getPosX();
    int getPosY();

    // Setters
    void setCursor(int x, int y);
    void setCursorX(int x);
    void setCursorY(int y);

    // Other methods
    void init();
    bool advanceCursor(char c);
    void print(std::string s);
    void print(int x, int y, std::string s);
    void draw();
    void clear();
    void createBox(bool flag);

};

#endif
