#include <stdlib.h>
#include "pdcurses/curses.h"

/* gcc -o hi.exe hi.c -Wall -lpdcurses -mwindows */

short G_THEME_PRIMARY_ID = 1;
short G_THEME_PRIMARY_BG = COLOR_BLUE;
short G_THEME_PRIMARY_FG = COLOR_WHITE;

short G_THEME_SECONDARY_ID = 2;
short G_THEME_SECONDARY_BG = COLOR_RED;
short G_THEME_SECONDARY_FG = COLOR_WHITE;

short G_THEME_PRIMARY_INVERSE_ID = 3;
short G_THEME_PRIMARY_INVERSE_BG = COLOR_WHITE;
short G_THEME_PRIMARY_INVERSE_FG = COLOR_BLUE;

short G_THEME_SECONDARY_INVERSE_ID = 4;
short G_THEME_SECONDARY_INVERSE_BG = COLOR_WHITE;
short G_THEME_SECONDARY_INVERSE_FG = COLOR_RED;

const int KEY_ESC = 27;
int G_SCREEN_HEIGHT = 25;
int G_SCREEN_WIDTH = 80;

WINDOW* G_MENU_WINDOW = NULL;
WINDOW* G_STATUS_WINDOW = NULL;
WINDOW* G_BODY_WINDOW = NULL;

void initializeApplication(void);
void finalizeApplication(void);
void clearScreen(void);
void initializeMenuBar(void);
void initializeBodyWindow(void);
void initializeStatusBar(void);
void doMainLoop(void);

int main (int argc, char* argv[]) {

  initializeApplication();
  doMainLoop();
  finalizeApplication();

  return EXIT_SUCCESS;

}

void initializeApplication() {
  PDC_set_title("Hello");

  initscr();

  if (has_colors())
  {
    start_color();

    init_pair(G_THEME_PRIMARY_ID, G_THEME_PRIMARY_FG, G_THEME_PRIMARY_BG);
    init_pair(G_THEME_SECONDARY_ID, G_THEME_SECONDARY_FG, G_THEME_SECONDARY_BG);
    init_pair(G_THEME_PRIMARY_INVERSE_ID, G_THEME_PRIMARY_INVERSE_FG, G_THEME_PRIMARY_INVERSE_BG);
    init_pair(G_THEME_SECONDARY_INVERSE_ID, G_THEME_SECONDARY_INVERSE_FG, G_THEME_SECONDARY_INVERSE_BG);
  }

  G_SCREEN_HEIGHT = getmaxy(stdscr);
  G_SCREEN_WIDTH = getmaxx(stdscr);

  G_MENU_WINDOW = newwin(1, G_SCREEN_WIDTH, 0, 0);
  G_STATUS_WINDOW = newwin(1, G_SCREEN_WIDTH, (G_SCREEN_HEIGHT - 1), 0);
  G_BODY_WINDOW = newwin((G_SCREEN_HEIGHT - 2), G_SCREEN_WIDTH, 1, 0);

  curs_set(0);

  clearScreen();

  initializeMenuBar();
  initializeBodyWindow();
  initializeStatusBar();

  curs_set(1);
}

void finalizeApplication() {
  delwin(G_BODY_WINDOW);
  delwin(G_STATUS_WINDOW);
  delwin(G_MENU_WINDOW);

  curs_set(1);

  endwin();
}

void clearScreen() {
  if (has_colors())
  {
    bkgd(COLOR_PAIR(G_THEME_PRIMARY_ID));
  }

  clear();
  refresh();
}

void initializeMenuBar() {
  if (has_colors())
  {
    wbkgd(G_MENU_WINDOW, COLOR_PAIR(G_THEME_PRIMARY_INVERSE_ID));
  }

  wclear(G_MENU_WINDOW);

  wprintw(G_MENU_WINDOW, "Hi! version 0.01 \t File \t Edit \t Help");

  wrefresh(G_MENU_WINDOW);
}

void initializeBodyWindow() {
  if (has_colors())
  {
    wbkgd(G_BODY_WINDOW, COLOR_PAIR(G_THEME_PRIMARY_ID));
  }

  wsetscrreg(G_BODY_WINDOW, 1, (G_SCREEN_HEIGHT - 2));
  scrollok(G_BODY_WINDOW, TRUE);

  wclear(G_BODY_WINDOW);

  wmove(G_BODY_WINDOW, 0, 0);

  wrefresh(G_BODY_WINDOW);
}

void initializeStatusBar() {
  if (has_colors())
  {
    wbkgd(G_STATUS_WINDOW, COLOR_PAIR(G_THEME_PRIMARY_INVERSE_ID));
  }

  wclear(G_STATUS_WINDOW);

  wprintw(G_STATUS_WINDOW, "ready...");

  wrefresh(G_STATUS_WINDOW);
}

void doMainLoop() {
  int ch = wgetch(G_BODY_WINDOW);
  while (ch != KEY_ESC) {
    ch = wgetch(G_BODY_WINDOW);
  }  
}
