#include "page.h"

#include <curses.h>
#include <menu.h>

#include <cstdlib>
#include <string>

using namespace ui;
using namespace std;

#define HELP_W_WIDTH    23
#define HELP_W_HEIGHT   3 

Page::Page() {
    initscr();
    cbreak();
	noecho();

    if (has_colors()) {
        start_color();
        init_pair(FOCUSED, COLOR_BLACK, COLOR_WHITE);
        init_pair(UNFOCUSED, COLOR_WHITE, COLOR_BLACK);
    }

    getmaxyx(stdscr, this->height, this->width);
    // FIXME: Add check for dimensions

    this->enclosing_window = newwin(this->height, this->width, 0, 0);

    this->help_window = derwin(this->enclosing_window,
            HELP_W_HEIGHT, HELP_W_WIDTH,
            (this->height - HELP_W_HEIGHT),
            (this->width - HELP_W_WIDTH) / 2);
    box(this->help_window, 0, 0);
    mvwprintw(this->help_window, 1, 1, "(F1) Help | (F2) Exit");

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

void Page::handle_exit() {
    // Insert logout call?
    endwin();
    std::exit(0);
}

void Page::show_help() {
    WINDOW* window = newwin(6, 48, (this->height - 6) / 2, (this->width - 48) / 2);
    box(window, 0, 0);
    keypad(window, true);
    mvwprintw(window, 1, 1, "Help:");
    mvwprintw(window, 2, 1, " - Use arrows to navigate.");
    mvwprintw(window, 3, 1, " - Press enter to select a button");
    mvwprintw(window, 4, 1, " - Press any key to return to previous window");
    wrefresh(window);
    wgetch(window);
    wclear(window);
    wrefresh(window);
    delwin(window);
    touchwin(this->enclosing_window);
    wrefresh(this->enclosing_window);
}

void Page::popup(string message) {
    WINDOW* window = newwin(6, 48, (this->height - 6) / 2, (this->width - 48) / 2);
    box(window, 0, 0);
    keypad(window, true);
    mvwprintw(window, 2, 1, message.c_str());
    mvwprintw(window, 3, 1, "Press any key to continue");
    wrefresh(window);
    wgetch(window);
    wclear(window);
    wrefresh(window);
    delwin(window);
    touchwin(this->enclosing_window);
    wrefresh(this->enclosing_window);
}
