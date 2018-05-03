#include <curses.h>
#include <form.h>
#include <stdlib.h>

#include "home.h"

using namespace ui; 
#define W_WIDTH         40
#define W_HEIGHT        10

#define SUB_M_WIDTH     20
#define SUB_M_HEIGHT    3
#define TEXT_LENGTH     20

#define EMPTY_FIELD     "                     0.00"

HomeResult::HomeResult(long amount, HomeRequestType type) {
    this->amount = amount;
    this->type = type;
}

HomePage::HomePage() {
    this->withdrawal_deposit_menu_items = (ITEM**) calloc(3, sizeof(ITEM*));
    this->withdrawal_deposit_menu_items[0] = new_item("Withdrawl", "");
    this->withdrawal_deposit_menu_items[1] = new_item("Deposit", "");
    this->withdrawal_deposit_menu_items[2] = new_item("", "");
    this->withdrawal_deposit_menu = new_menu(this->withdrawal_deposit_menu_items);

    this->withdrawal_deposit_window = derwin(this->enclosing_window,
            W_HEIGHT, W_WIDTH,
            (this->height - W_HEIGHT) / 2,
            (this->width - W_WIDTH) / 2);
    keypad(this->withdrawal_deposit_window, true);
    box(this->withdrawal_deposit_window, 0, 0);

    set_menu_win(this->withdrawal_deposit_menu, this->withdrawal_deposit_window);
    set_menu_sub(this->withdrawal_deposit_menu,
            derwin(this->withdrawal_deposit_window, SUB_M_HEIGHT, SUB_M_WIDTH,
            (W_HEIGHT - SUB_M_HEIGHT), (W_WIDTH - SUB_M_WIDTH) / 2));
    set_menu_format(this->withdrawal_deposit_menu, 1, 2);
    set_menu_mark(this->withdrawal_deposit_menu, "");
    post_menu(this->withdrawal_deposit_menu);

    this->amount_form_fields = (FIELD**) calloc(3, sizeof(FIELD*));
    this->amount_form_fields[0] = new_field(1, 10, 0, 0, 0, 0);    // Amount label
    field_opts_off(this->amount_form_fields[0], O_ACTIVE);
    set_field_buffer(this->amount_form_fields[0], 0, "Amount: ");

    this->amount_form_fields[1] = new_field(1, TEXT_LENGTH, 0, 10, 0, 0);   // Amount entry
    set_field_back(this->amount_form_fields[1], A_UNDERLINE);
    field_opts_off(this->amount_form_fields[1], O_AUTOSKIP);

    this->amount_form_fields[2] = NULL;
    this->amount_form = new_form(this->amount_form_fields);
    int form_w, form_h;
    scale_form(this->amount_form, &form_h, &form_w);
    set_form_win(this->amount_form, this->withdrawal_deposit_window);
    set_form_sub(this->amount_form, derwin(this->withdrawal_deposit_window,
        3, TEXT_LENGTH + 10,
        2, (W_WIDTH - (TEXT_LENGTH + 10)) / 2));

    post_form(this->amount_form);

    wrefresh(this->withdrawal_deposit_window);
}

HomePage::~HomePage() {
    unsigned int count;

    count = 0;
    unpost_form(this->amount_form);
    free_form(this->amount_form);
    while (this->amount_form_fields[count] != NULL) {
        free_field(this->amount_form_fields[count]);
        count ++;
    }
    free(this->amount_form_fields);

    count = 0;
    unpost_menu(this->withdrawal_deposit_menu);
    free_menu(this->withdrawal_deposit_menu);
    while (this->withdrawal_deposit_menu_items[count] != NULL) {
        free_item(this->withdrawal_deposit_menu_items[count]);
        count ++;
    }
    free(this->withdrawal_deposit_menu_items);
}

HomeResult* HomePage::wait_for_result() {
    char buf[TEXT_LENGTH];
    unsigned int count = 0;

    while (true) {
        int c = wgetch(this->withdrawal_deposit_window);
        switch (c) {
            case KEY_RIGHT:
                menu_driver(this->withdrawal_deposit_menu, REQ_RIGHT_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(this->withdrawal_deposit_menu, REQ_LEFT_ITEM);
                break;
            case KEY_ENTER: case '\n':
                if (current_item(this->withdrawal_deposit_menu) ==
                        this->withdrawal_deposit_menu_items[0])
                    return new HomeResult(strtod(buf, NULL), WITHDRAWL);
                else
                    return new HomeResult(strtod(buf, NULL), DEPOSIT);
                break;
            case KEY_F(1):
                this->show_help();
                break;
            case KEY_F(2):
                this->handle_exit();
                break;
            case KEY_F(3):
                form_driver(this->amount_form, REQ_CLR_FIELD);
                break;
            default:
                if (count < TEXT_LENGTH - 1  && (('0' <= c && c <= '9'))) {
                    form_driver(this->amount_form, REQ_CLR_FIELD);
                    buf[count] = c;
                    count ++;

                    if (count >= 3) {
                        for (int i = 0; i < (TEXT_LENGTH - 1) - count; i ++) {
                            form_driver(this->amount_form, ' ');
                        }
                        for (int i = (TEXT_LENGTH - 1) - count; i < (TEXT_LENGTH) - 3; i ++) {
                            form_driver(this->amount_form, buf[i - (TEXT_LENGTH - 1) + count]);
                        }
                        form_driver(this->amount_form, '.');
                        form_driver(this->amount_form, buf[count - 2]);
                        form_driver(this->amount_form, buf[count - 1]); 
                    } else if (count == 2) {
                        for (int i = 0; i < TEXT_LENGTH - 3; i++) {
                            form_driver(this->amount_form, ' ');
                        } 
                        form_driver(this->amount_form, '.');
                        form_driver(this->amount_form, buf[count - 2]);
                        form_driver(this->amount_form, buf[count - 1]); 
                    } else if (count == 1) {
                        for (int i = 0; i < TEXT_LENGTH - 3; i++) {
                            form_driver(this->amount_form, ' ');
                        } 
                        form_driver(this->amount_form, '.');
                        form_driver(this->amount_form, '0');
                        form_driver(this->amount_form, buf[0]); 
                    }
                }
                break;
        }
    }
    return 0;
}
