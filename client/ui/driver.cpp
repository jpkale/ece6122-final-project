#include "driver.h"
#include "page.h"
#include "landing.h"

#include <thread>

using namespace ui;
using namespace std; 
Driver::Driver(void (*login_cb)(void), void (*signup_cb)(void), void (*sendmoney_cb)(void),
        void (*withdrawlmoney_cb)(void), void (*editinfo_cb)(void), void (*exit_cb)(void)) {
    this->login_cb = login_cb;
    this->signup_cb = signup_cb;
    this->sendmoney_cb = sendmoney_cb;
    this->withdrawlmoney_cb = withdrawlmoney_cb;
    this->editinfo_cb = editinfo_cb;
    this->exit_cb = exit_cb;
}

Driver::~Driver() {}

void Driver::start() {
    LandingPage* page = new LandingPage();
	LandingResult* result = page->wait_for_result();

	switch (result->type) {
		case LOGIN:
			printf("Login: %s:%s", result->cred->username, result->cred->password);
			break;
		case CREATE:
			printf("create: %s:%s", result->cred->username, result->cred->password);
			break;
	}
    
    delete result;
    delete page;
}
