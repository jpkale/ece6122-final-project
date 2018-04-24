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
            MENU* withdrawl_deposit_menu;
            WINDOW* withdrawl_deposit_window;
            FORM* amount_form;
        public:
            HomeResult* wait_for_result();
            HomePage();
            ~HomePage();
    };
}
