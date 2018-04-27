#pragma once

#include <string>

#include <curses.h>
#include <menu.h>

using namespace std;

namespace ui {
    class Page {
        public:
            Page(); 
            ~Page(); 
            void show_help();
            void handle_exit();
            void popup(string format, ...);
        protected:
            WINDOW *help_window;
            WINDOW *enclosing_window;
            int width;
            int height;
    };
}
