#pragma once

#include "page.h"

#include <curses.h>
#include <form.h>
#include <menu.h>
#include <string>

using namespace std;

namespace ui {

    class Credential {
        public:
            char* username;
            char* password;
            Credential();
            ~Credential();
    };

    enum LandingSubmitType {
		LOGIN,
		CREATE,       
    };

    class LandingResult {
        public:
            Credential* cred;
            LandingSubmitType type;
            LandingResult(Credential* cred, LandingSubmitType type);
            ~LandingResult();
    };

    class LandingPage : public Page {
        private:
            FORM* credential_form;
            FIELD** credential_form_fields;
            MENU* create_login_menu;
            ITEM** create_login_menu_items;
            WINDOW* create_login_window;
        public:
            LandingPage();
            ~LandingPage();
			LandingResult* wait_for_result();
    };
}
