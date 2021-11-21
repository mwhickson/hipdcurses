#include <stdlib.h>
#include "pdcurses/curses.h"

/* gcc -o hi.exe hi.c -Wall -lpdcurses -mwindows */

short THEME_PRIMARY_ID = 1;
short THEME_PRIMARY_BG = COLOR_BLUE;
short THEME_PRIMARY_FG = COLOR_WHITE;

short THEME_SECONDARY_ID = 2;
short THEME_SECONDARY_BG = COLOR_RED;
short THEME_SECONDARY_FG = COLOR_WHITE;

short THEME_PRIMARY_INVERSE_ID = 3;
short THEME_PRIMARY_INVERSE_BG = COLOR_WHITE;
short THEME_PRIMARY_INVERSE_FG = COLOR_BLUE;

short THEME_SECONDARY_INVERSE_ID = 4;
short THEME_SECONDARY_INVERSE_BG = COLOR_WHITE;
short THEME_SECONDARY_INVERSE_FG = COLOR_RED;

int SCREEN_HEIGHT = 25;
int SCREEN_WIDTH = 80;

WINDOW* MENU_WINDOW = NULL;
WINDOW* STATUS_WINDOW = NULL;
WINDOW* BODY_WINDOW = NULL;

void initializeApplication(void);
void finalizeApplication(void);
void clearScreen(void);
void drawMenuBar(void);
void drawBodyWindow(void);
void drawStatusBar(void);

int main (int argc, char* argv[]) {

  initscr();

  if (has_colors())
  {
    start_color();

    init_pair(THEME_PRIMARY_ID, THEME_PRIMARY_FG, THEME_PRIMARY_BG);
    init_pair(THEME_SECONDARY_ID, THEME_SECONDARY_FG, THEME_SECONDARY_BG);
    init_pair(THEME_PRIMARY_INVERSE_ID, THEME_PRIMARY_INVERSE_FG, THEME_PRIMARY_INVERSE_BG);
    init_pair(THEME_SECONDARY_INVERSE_ID, THEME_SECONDARY_INVERSE_FG, THEME_SECONDARY_INVERSE_BG);
  }

  initializeApplication();

  // do stuff

  // wait around so we can see things
  getch();

  finalizeApplication();

  endwin();

  return EXIT_SUCCESS;

}

void initializeApplication() {
  PDC_set_title("Hello");

  SCREEN_HEIGHT = getmaxy(stdscr);
  SCREEN_WIDTH = getmaxx(stdscr);

  MENU_WINDOW = newwin(1, SCREEN_WIDTH, 0, 0);
  STATUS_WINDOW = newwin(1, SCREEN_WIDTH, (SCREEN_HEIGHT - 1), 0);
  BODY_WINDOW = newwin((SCREEN_HEIGHT - 2), SCREEN_WIDTH, 1, 0);

  clearScreen();

  drawMenuBar();
  drawStatusBar();

  drawBodyWindow();
}

void finalizeApplication() {
  delwin(BODY_WINDOW);
  delwin(STATUS_WINDOW);
  delwin(MENU_WINDOW);
}

void clearScreen() {
  if (has_colors())
  {
    bkgd(COLOR_PAIR(THEME_PRIMARY_ID));
  }

  clear();
  refresh();
}

void drawMenuBar() {
  if (has_colors())
  {
    wbkgd(MENU_WINDOW, COLOR_PAIR(THEME_PRIMARY_INVERSE_ID));
  }

  wclear(MENU_WINDOW);

  wprintw(MENU_WINDOW, "Hi! version 0.01");

  wrefresh(MENU_WINDOW);
}

void drawBodyWindow() {
  if (has_colors())
  {
    wbkgd(BODY_WINDOW, COLOR_PAIR(THEME_PRIMARY_ID));
  }

  wclear(BODY_WINDOW);

  wprintw(BODY_WINDOW, "...");

  wrefresh(BODY_WINDOW);
}

void drawStatusBar() {
  if (has_colors())
  {
    wbkgd(STATUS_WINDOW, COLOR_PAIR(THEME_PRIMARY_INVERSE_ID));
  }

  wclear(STATUS_WINDOW);

  wprintw(STATUS_WINDOW, "ready...");

  wrefresh(STATUS_WINDOW);
}