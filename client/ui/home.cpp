#include <curses.h>
#include <form.h>

#include "home.h"

using namespace ui;

#define W_WIDTH         40
#define W_HEIGHT        10

#define SUB_M_WIDTH     20
#define SUB_M_HEIGHT    3

#define TEXT_LENGTH     20

Request::Request(unsigned int account_number, unsigned int amount) {
    this->account_number = account_number;
    this->amount = amount;
}

HomePage::HomePage() {
    ITEM* items[3];
    items[0] = new_item("Withdrawl", "");
    items[1] = new_item("Deposit", "");
    items[2] = new_item("", "");
    this->withdrawl_deposit_menu = new_menu(items);

    this->withdrawl_deposit_window = derwin(this->enclosing_window,
            W_HEIGHT, W_WIDTH,
            (this->height - W_HEIGHT) / 2,
            (this->width - W_WIDTH) / 2);
    keypad(this->withdrawl_deposit_window, true);
    box(this->withdrawl_deposit_window, 0, 0);

    set_menu_win(this->withdrawl_deposit_menu, this->withdrawl_deposit_window);
    set_menu_sub(this->withdrawl_deposit_menu,
            derwin(this->withdrawl_deposit_window, SUB_M_HEIGHT, SUB_M_WIDTH,
            (W_HEIGHT - SUB_M_HEIGHT), (W_WIDTH - SUB_M_WIDTH) / 2));
    set_menu_format(this->withdrawl_deposit_menu, 1, 2);
    set_menu_mark(this->withdrawl_deposit_menu, "");
    post_menu(this->withdrawl_deposit_menu);

    FIELD* field[3];
    field[0] = new_field(1, 10, 0, 0, 0, 0);    // Amount label
    field_opts_off(field[0], O_ACTIVE);
    set_field_buffer(field[0], 0, "Amount: ");

    field[1] = new_field(1, TEXT_LENGTH, 0, 10, 0, 0);   // Amount entry
    set_field_back(field[1], A_UNDERLINE);
    field_opts_off(field[1], O_AUTOSKIP);

    field[2] = NULL;
    this->amount_form = new_form(field);
    int form_w, form_h;
    scale_form(this->amount_form, &form_h, &form_w);
    set_form_win(this->amount_form, this->withdrawl_deposit_window);
    set_form_sub(this->amount_form, derwin(this->withdrawl_deposit_window,
        3, TEXT_LENGTH + 10,
        2, (W_WIDTH - (TEXT_LENGTH + 10)) / 2));

    post_form(this->amount_form);

    wrefresh(this->withdrawl_deposit_window);
}

HomeResult* HomePage::wait_for_result() {
    wgetch(this->withdrawl_deposit_window);
    return 0;
}
