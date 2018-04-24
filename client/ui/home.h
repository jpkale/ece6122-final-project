#pragma once

#include "page.h"

namespace ui {
    class Request {
        public:
            unsigned int account_number;
            unsigned int amount;
            Request(unsigned int account_number, unsigned int ammount);
    };

    enum HomeRequestType {
        DEPOSIT,
        WITHDRAWL,
    };

    class HomeResult {
        public:
            Request* request;
            HomeRequestType type;
            HomeResult(Request* req, HomeRequestType type);
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
