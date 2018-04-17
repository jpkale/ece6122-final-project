#include "page.h"

#include <curses.h>
#include <menu.h>

#include <cstdlib>

using namespace ui;
using namespace std;

#define HELP_W_WIDTH    11
#define HELP_W_HEIGHT   3 

Page::Page() {
    initscr();
    cbreak();
	noecho();

    if (has_colors()) {
        start_color();
    }

    getmaxyx(stdscr, this->height, this->width);
    // FIXME: Add check for dimensions

    this->enclosing_window = newwin(this->height, this->width, 0, 0);

    ITEM** items = (ITEM**) calloc(3, sizeof(ITEM*));
    items[0] = new_item("Help", "");
    items[1] = new_item("Exit", "");
    items[2] = new_item("", "");
    this->help_menu = new_menu(items);

    this->help_window = derwin(this->enclosing_window,
            HELP_W_HEIGHT, HELP_W_WIDTH,
            (this->height - HELP_W_HEIGHT),
            (this->width - HELP_W_WIDTH) / 2);
    keypad(this->help_window, true);
    box(this->help_window, 0, 0);

    set_menu_win(this->help_menu, this->help_window);
    set_menu_sub(this->help_menu, derwin(this->help_window,
                HELP_W_HEIGHT - 1,
                HELP_W_WIDTH - 1, 1, 1));
    set_menu_format(this->help_menu, 1, 2);
    set_menu_mark(this->help_menu, "");

    // Refresh before returning
    post_menu(this->help_menu);
    wrefresh(this->help_window);
    wrefresh(this->enclosing_window);
}

Page::~Page() {
    // FIXME free a bunch of other shit
    free_menu(this->help_menu);
    endwin();
}
