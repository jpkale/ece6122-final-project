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
    LandingPage page = LandingPage();
	LandingResult result = page.waitForResult();

	switch (result.type) {
		case LOGIN:
			// Do something
			break;
		case CREATE:
			// Do something
			break;
	}
}
