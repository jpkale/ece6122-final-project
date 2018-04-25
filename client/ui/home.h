#pragma once

#include "page.h"

namespace ui {

    enum HomeRequestType {
        DEPOSIT,
        WITHDRAWL,
    };

    class HomeResult {
        public:
            double amount;
            HomeRequestType type;
            HomeResult(double amount, HomeRequestType type);
            ~HomeResult();
    };

    class HomePage : public Page {
        private:
            FORM* amount_form;
            FIELD** amount_form_fields;
            MENU* withdrawl_deposit_menu;
            ITEM** withdrawl_deposit_menu_items;
            WINDOW* withdrawl_deposit_window;
        public:
            HomeResult* wait_for_result();
            HomePage();
            ~HomePage();
    };
}
