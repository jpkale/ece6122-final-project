#include "page.h"
#include "landing.h"

#include <curses.h>

using namespace ui;

#define W_WIDTH         40
#define W_HEIGHT        15

#define SUB_M_WIDTH     20
#define SUB_M_HEIGHT    3

LandingPage::LandingPage() : Page() {
    ITEM** items = (ITEM**) calloc(3, sizeof(ITEM *));
    items[0] = new_item("Create Account", "");
    items[1] = new_item("Login", "");
    items[2] = new_item("", "");
    this->create_login_menu = new_menu(items);

    this->menu_window = derwin(this->enclosing_window,
            W_HEIGHT, W_WIDTH,
            (this->height - W_HEIGHT) / 2,
            (this->width - W_WIDTH) / 2);
    box(this->menu_window, 0, 0);

    set_menu_win(this->create_login_menu, this->menu_window);
    set_menu_sub(this->create_login_menu,
            derwin(this->menu_window, SUB_M_HEIGHT, SUB_M_WIDTH,
            (W_HEIGHT - SUB_M_HEIGHT), (W_WIDTH - SUB_M_WIDTH) / 2));
    set_menu_format(this->create_login_menu, 1, 2);
    set_menu_mark(this->create_login_menu, "");
    post_menu(this->create_login_menu);

    wrefresh(this->menu_window);
}

LandingPage::~LandingPage() { 
    // FIXME: Free shit
}

LandingResult LandingPage::waitForResult() {
	noecho();
	while (true) {
		int c = wgetch(this->help_window);
		switch (c) {
			case KEY_RIGHT:
				menu_driver(this->help_menu, REQ_RIGHT_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(this->help_menu, REQ_LEFT_ITEM);
				break;
			default:
				mvwprintw(this->enclosing_window, "WTF\n");
		}
		wrefresh(this->help_window);
	}

	LandingCredential creds = LandingCredential {
		"myusername",
		"mypassword",
	};
	LandingResult result = LandingResult {
		creds,
		LOGIN,	
	};
	
	return result;
}
