#pragma once

namespace ui {
    class Driver {
        private:
            void (*login_cb)(void);
            void (*signup_cb)(void);
            void (*sendmoney_cb)(void);
            void (*withdrawlmoney_cb)(void);
            void (*editinfo_cb)(void);
            void (*exit_cb)(void);
        public:
            Driver(void (*login_cb)(void),
                   void (*signup_cb)(void),
                   void (*sendmoney_cb)(void),
                   void (*withdrawlmoney_cb)(void),
                   void (*editinfo_cb)(void),
                   void (*exit_cb)(void));
            ~Driver();
            void start();
    };
}
