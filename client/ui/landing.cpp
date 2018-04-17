#include "page.h"
#include "landing.h"

#include <curses.h>

using namespace ui;

#define W_WIDTH         40
#define W_HEIGHT        10

#define SUB_M_WIDTH     20
#define SUB_M_HEIGHT    3

#define TEXT_LENGTH     20

LandingPage::LandingPage() : Page() {
    ITEM* items[3];
    items[0] = new_item("Create Account", "");
    items[1] = new_item("Login", "");
    items[2] = new_item("", "");
    this->create_login_menu = new_menu(items);

    this->create_login_window = derwin(this->enclosing_window,
            W_HEIGHT, W_WIDTH,
            (this->height - W_HEIGHT) / 2,
            (this->width - W_WIDTH) / 2);
    keypad(this->create_login_window, true);
    box(this->create_login_window, 0, 0);

    set_menu_win(this->create_login_menu, this->create_login_window);
    set_menu_sub(this->create_login_menu,
            derwin(this->create_login_window, SUB_M_HEIGHT, SUB_M_WIDTH,
            (W_HEIGHT - SUB_M_HEIGHT), (W_WIDTH - SUB_M_WIDTH) / 2));
    set_menu_format(this->create_login_menu, 1, 2);
    set_menu_mark(this->create_login_menu, "");
    post_menu(this->create_login_menu);

    FIELD* field[5];
    field[0] = new_field(1, 10, 0, 0, 0, 0);    // username label
    field_opts_off(field[0], O_ACTIVE);
    set_field_buffer(field[0], 0, "Username: ");

    field[1] = new_field(1, TEXT_LENGTH, 0, 10, 0, 0);   // username entry
    set_field_back(field[1], A_UNDERLINE);
    field_opts_off(field[1], O_AUTOSKIP);

    field[2] = new_field(1, 10, 2, 0, 0, 0);    // password label
    field_opts_off(field[2], O_ACTIVE);
    set_field_buffer(field[2], 0, "Password: ");

    field[3] = new_field(1, TEXT_LENGTH, 2, 10, 0, 0);   // password entry
    field_opts_off(field[3], O_PUBLIC);
    set_field_back(field[3], A_UNDERLINE);

    field[4] = NULL;
    this->credentials_form = new_form(field);
    int form_w, form_h;
    scale_form(this->credentials_form, &form_h, &form_w);
    set_form_win(this->credentials_form, this->create_login_window);
    set_form_sub(this->credentials_form, derwin(this->create_login_window,
        3, TEXT_LENGTH + 10,
        2, (W_WIDTH - (TEXT_LENGTH + 10)) / 2));

    post_form(this->credentials_form);

    wrefresh(this->create_login_window);
}

LandingPage::~LandingPage() { 
    // FIXME: Free shit
}

LandingResult LandingPage::waitForResult() {
    WINDOW* focused_window = this->create_login_window;
    MENU* focused_menu = this->create_login_menu;
	while (true) {
		int c = wgetch(focused_window);
		switch (c) {
			case KEY_RIGHT:
				menu_driver(focused_menu, REQ_RIGHT_ITEM);
				break;
			case KEY_LEFT:
				menu_driver(focused_menu, REQ_LEFT_ITEM);
				break;
            case KEY_DOWN:
                focused_menu = this->help_menu; 
                focused_window = this->help_window;
                break;
            case KEY_UP:
                focused_menu = this->create_login_menu;
                focused_window = this->create_login_window;
                break;
            case '\n':
                goto construct_result;
                break;
			default:
                break;
		}

        wrefresh(focused_window);
	}

construct_result:
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
