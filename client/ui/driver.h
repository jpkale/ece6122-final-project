#pragma once

#include "landing.h"
#include "home.h"

namespace ui {
    class Driver {
        private:
            bool (*login_cb)(Credential*);
            bool (*signup_cb)(Credential*);
            bool (*deposit_cb)(Request*);
            bool (*withdrawl_cb)(Request*);
        public:
            Driver(
                bool (*login_cb)(Credential*),
                bool (*signup_cb)(Credential*),
                bool (*deposit_cb)(Request*),
                bool (*withdrawl_cb)(Request*)
            );
            ~Driver();
            void start();
    };
}
