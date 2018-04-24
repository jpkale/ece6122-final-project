#pragma once

#include "landing.h"
#include "home.h"

namespace ui {
    class Driver {
        private:
            bool (*login_cb)(Credential*);
            bool (*signup_cb)(Credential*);
            bool (*deposit_cb)(double);
            bool (*withdrawl_cb)(double);
        public:
            Driver(
                bool (*login_cb)(Credential*),
                bool (*signup_cb)(Credential*),
                bool (*deposit_cb)(double),
                bool (*withdrawl_cb)(double)
            );
            ~Driver();
            void start();
    };
}
