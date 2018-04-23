#pragma once

#include "page.h"

#include <curses.h>
#include <form.h>
#include <menu.h>
#include <string>

using namespace std;

namespace ui {

    class LandingCredential {
        public:
            char* username;
            char* password;
            LandingCredential();
            ~LandingCredential();
    };

    enum LandingSubmitType {
		LOGIN,
		CREATE,       
    };

    class LandingResult {
        public:
            LandingCredential* cred;
            LandingSubmitType type;
            LandingResult(LandingCredential* cred, LandingSubmitType type);
            ~LandingResult();
    };

    class LandingPage : public Page {
        private:
            FORM* credentials_form;
            MENU* create_login_menu;
            WINDOW* create_login_window;
        public:
            LandingPage();
            ~LandingPage();
			LandingResult* wait_for_result();
    };
}
