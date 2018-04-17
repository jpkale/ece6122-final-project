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
            FORM* credentials_form;
            MENU* create_login_menu;
            WINDOW* create_login_window;
        public:
            LandingPage();
            ~LandingPage();
			LandingResult waitForResult();
    };
}
