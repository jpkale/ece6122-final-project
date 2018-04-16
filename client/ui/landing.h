#pragma once

#include "page.h"

#include <curses.h>
#include <form.h>
#include <menu.h>
#include <string>

using namespace std;

namespace ui {

    typedef struct LandingCredential {
        string username;
        string password; 
    } LandingCredentials;

    enum LandingSubmitType {
		LOGIN,
		CREATE,       
    };

	typedef struct LandingResult {
		LandingCredentials creds;
		LandingSubmitType type;
	} LandingResult;

    class LandingPage : public Page {
        private:
            FIELD* username_field;
            FIELD* password_field;
            MENU* create_login_menu;
            WINDOW* menu_window;
        public:
            LandingPage();
            ~LandingPage();
			LandingResult waitForResult();
    };
}
