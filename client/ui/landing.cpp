#include "page.h"
#include "landing.h"

#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <regex>

using namespace ui;

#define W_WIDTH         40
#define W_HEIGHT        10

#define SUB_M_WIDTH     20
#define SUB_M_HEIGHT    3

#define TEXT_LENGTH     20

#define KEY_DEL         127

LandingPage::LandingPage() : Page() {
    this->create_login_menu_items = (ITEM**) calloc(3, sizeof(ITEM*));
    this->create_login_menu_items[0] = new_item("Create Account", "");
    this->create_login_menu_items[1] = new_item("Login", "");
    this->create_login_menu_items[2] = new_item("", "");
    this->create_login_menu = new_menu(this->create_login_menu_items);

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

    this->credential_form_fields = (FIELD**) calloc(5, sizeof(FIELD*));
    this->credential_form_fields[0] = new_field(1, 10, 0, 0, 0, 0);    // username label
    field_opts_off(this->credential_form_fields[0], O_ACTIVE);
    set_field_buffer(this->credential_form_fields[0], 0, "Username: ");

    this->credential_form_fields[1] = new_field(1, TEXT_LENGTH, 0, 10, 0, 0);   // username entry
    set_field_back(this->credential_form_fields[1], A_UNDERLINE);
    field_opts_off(this->credential_form_fields[1], O_AUTOSKIP);

    this->credential_form_fields[2] = new_field(1, 10, 2, 0, 0, 0);    // password label
    field_opts_off(this->credential_form_fields[2], O_ACTIVE);
    set_field_buffer(this->credential_form_fields[2], 0, "Password: ");

    this->credential_form_fields[3] = new_field(1, TEXT_LENGTH, 2, 10, 0, 0);   // password entry
    set_field_back(this->credential_form_fields[3], A_UNDERLINE);
    field_opts_off(this->credential_form_fields[3], O_AUTOSKIP);

    this->credential_form_fields[4] = NULL;
    this->credential_form = new_form(this->credential_form_fields);
    int form_w, form_h;
    scale_form(this->credential_form, &form_h, &form_w);
    set_form_win(this->credential_form, this->create_login_window);
    set_form_sub(this->credential_form, derwin(this->create_login_window,
                3, TEXT_LENGTH + 10,
                2, (W_WIDTH - (TEXT_LENGTH + 10)) / 2));

    post_form(this->credential_form);

    wrefresh(this->create_login_window);
}

LandingPage::~LandingPage() { 
    unsigned int count;

    count = 0;
    unpost_form(this->credential_form);
    free_form(this->credential_form);
    while (this->credential_form_fields[count] != NULL) {
        free_field(this->credential_form_fields[count]);
        count ++;
    }
    free(this->credential_form_fields);

    count = 0;
    unpost_menu(this->create_login_menu);
    free_menu(this->create_login_menu);
    while (this->create_login_menu_items[count] != NULL) {
        free_item(this->create_login_menu_items[count]);
        count ++;
    }
    free(this->create_login_menu_items);
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

    while (true) {
        int c = wgetch(this->create_login_window);
        if (vertical_level == USERNAME_FIELD) {
            count = &uname_char_count;
        } else {
            count = &pword_char_count;
        }

        switch (c) {
            case KEY_STAB: case KEY_CTAB: case '\t':
                if (vertical_level == USERNAME_FIELD) {
                    form_driver(this->credential_form, REQ_DOWN_FIELD);
                    vertical_level = PASSWORD_FIELD;
                } else {
                    form_driver(this->credential_form, REQ_UP_FIELD);
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
                    form_driver(this->credential_form, REQ_DEL_PREV);
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
                cred->username = regex_replace(
                        string(field_buffer(this->credential_form_fields[1], 0)),
                        regex(" +$"),
                        "");
                cred->password = regex_replace(
                        string(field_buffer(this->credential_form_fields[3], 0)),
                        regex(" +$"),
                        "");
                if (current_item(this->create_login_menu) == items[0])
                    return new LandingResult(cred, CREATE);
                else
                    return new LandingResult(cred, LOGIN);
                break;
            default:
                if (32 < c && c < 127 && *count < TEXT_LENGTH - 1) {
                    if (vertical_level == USERNAME_FIELD)
                        form_driver(this->credential_form, c);
                    else
                        form_driver(this->credential_form, '*');
                    (*count)++;
                }
                break;
        }
        wrefresh(this->create_login_window);
    }
}

Credential::Credential() {
    this->username = std::string('\0', TEXT_LENGTH);
    this->password = std::string('\0', TEXT_LENGTH);

}

Credential::~Credential() {}

LandingResult::LandingResult(Credential* cred, LandingSubmitType type) {
    this->cred = cred;
    this->type = type;
}

LandingResult::~LandingResult() {
    delete this->cred;
}
