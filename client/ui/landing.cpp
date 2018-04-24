#include "page.h"
#include "landing.h"

#include <curses.h>
#include <string.h>
#include <cstdlib>

using namespace ui;

#define W_WIDTH         40
#define W_HEIGHT        10

#define SUB_M_WIDTH     20
#define SUB_M_HEIGHT    3

#define TEXT_LENGTH     20

#define KEY_DEL         127

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
    set_field_back(field[3], A_UNDERLINE);
    field_opts_off(field[3], O_AUTOSKIP);

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

enum VerticalLevel {
    USERNAME_FIELD,
    PASSWORD_FIELD,
};

LandingResult* LandingPage::wait_for_result() {
    VerticalLevel vertical_level = USERNAME_FIELD;
    unsigned int uname_char_count = 0;
    unsigned int pword_char_count = 0;
    Credential *cred = new Credential();
    ITEM** items = menu_items(this->create_login_menu);
    unsigned int* count;
    char* buf;

    while (true) {
        int c = wgetch(this->create_login_window);
        if (vertical_level == USERNAME_FIELD) {
            count = &uname_char_count;
            buf = cred->username;
        } else {
            count = &pword_char_count;
            buf = cred->password;
        }

        switch (c) {
            case KEY_STAB: case KEY_CTAB: case '\t':
                if (vertical_level == USERNAME_FIELD) {
                    form_driver(this->credentials_form, REQ_DOWN_FIELD);
                    vertical_level = PASSWORD_FIELD;
                } else {
                    form_driver(this->credentials_form, REQ_UP_FIELD);
                    vertical_level = USERNAME_FIELD;
                }
                break;
            case KEY_RIGHT:
                menu_driver(this->create_login_menu, REQ_RIGHT_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(this->create_login_menu, REQ_LEFT_ITEM);
                break;
            case KEY_BACKSPACE: case KEY_DC: case KEY_DEL:
                if (*count != 0) {
                    form_driver(this->credentials_form, REQ_DEL_PREV);
                    buf[*count] = '\0';
                    (*count)--;
                }
                break;
            case KEY_F(1):
                this->show_help();
                break;
            case KEY_F(2):
                this->handle_exit();
                break;
            case KEY_ENTER: case '\n':
                if (current_item(this->create_login_menu) == items[0])
                    return new LandingResult(cred, CREATE);
                else
                    return new LandingResult(cred, LOGIN);
                break;
            default:
                if (32 < c && c < 127 && *count < TEXT_LENGTH - 1) {
                    buf[*count] = c;
                    if (vertical_level == USERNAME_FIELD)
                        form_driver(this->credentials_form, c);
                    else
                        form_driver(this->credentials_form, '*');
                    (*count)++;
                }
                break;
        }
        wrefresh(this->create_login_window);
    }
}

Credential::Credential() {
    this->username = (char*) malloc(TEXT_LENGTH);
    this->password = (char*) malloc(TEXT_LENGTH);
    memset(this->username, '\0', TEXT_LENGTH);
    memset(this->password, '\0', TEXT_LENGTH);
}

Credential::~Credential() {
    free(this->username);
    free(this->password); 
}

LandingResult::LandingResult(Credential* cred, LandingSubmitType type) {
    this->cred = cred;
    this->type = type;
}

LandingResult::~LandingResult() {
    delete this->cred;
}
