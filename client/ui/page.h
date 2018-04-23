#pragma once

#include <curses.h>
#include <menu.h>

#define FOCUSED     1
#define UNFOCUSED   2

namespace ui {
    class Page {
        public:
            Page(); 
            ~Page(); 
            void handle_help_exit();
        protected:
            MENU* help_menu;
            WINDOW *help_window;
            WINDOW *enclosing_window;
            int width;
            int height;
    };
}
