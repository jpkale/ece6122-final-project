#pragma once

#include <curses.h>
#include <menu.h>

namespace ui {
    class Page {
        public:
            Page(); 
            ~Page(); 
        protected:
            MENU* help_menu;
            WINDOW *help_window;
            WINDOW *enclosing_window;
            int width;
            int height;
    };
}
