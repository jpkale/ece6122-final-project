#include "page.h"

#include <curses.h>
#include <menu.h>
#include <stdarg.h>

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

    // Refresh before returning
    wrefresh(this->help_window);
    wrefresh(this->enclosing_window);
}

Page::~Page() {
    delwin(this->help_window);
    delwin(this->enclosing_window);
    endwin();
}

void Page::handle_exit() {
    // Insert logout call?
    endwin();
    std::exit(0);
}

void Page::show_help() {
    this->popup("HELP\n - Use LEFT and RIGHT arrows to navigate.\n - Press enter to select a button\n - Use TAB to navigate fields\n - Press F2 to exit\n");
}

void Page::popup(string format, ...) {
    WINDOW* window = newwin(8, 60, (this->height - 8) / 2, (this->width - 60) / 2);
    keypad(window, true);
    box(window, 0, 0);

    va_list args;
    va_start(args, format);

    size_t pos = 0, count = 0;;
    std::string token;
    while ((pos = format.find("\n")) != std::string::npos && count < 5) {
        token = format.substr(0, pos);
        wmove(window, count + 1, 1);
        vwprintw(window, token.c_str(), args);
        format.erase(0, pos + 1);
        count ++;
    }

    mvwprintw(window, 6, 1, "Press any key to continue.");
    wrefresh(window);
    wgetch(window);
    wclear(window);
    wrefresh(window);
    delwin(window);
    touchwin(this->enclosing_window);
    wrefresh(this->enclosing_window);

    va_end(args);
}

void Page::handle_help_exit() {
    ITEM** items = menu_items(this->help_menu);
    int c = item_count(this->help_menu);

    if (current_item(this->help_menu) == items[0]) {
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
    } else {
        // Insert logout call?
        endwin();
        std::exit(0);
    }
}
