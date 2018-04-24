#pragma once

#include <string>

#include <curses.h>
#include <menu.h>

#define FOCUSED     1
#define UNFOCUSED   2

namespace ui {
    class Page {
        public:
            Page(); 
            ~Page(); 
            void show_help();
            void handle_exit();
            void popup(std::string message);
        protected:
            MENU* help_menu;
            WINDOW *help_window;
            WINDOW *enclosing_window;
            int width;
            int height;
    };
}
