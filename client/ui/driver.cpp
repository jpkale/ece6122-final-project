#include "driver.h"
#include "page.h"
#include "landing.h"

#include <thread>

using namespace ui;
using namespace std;

Driver::Driver(
    bool (*login_cb)(Credential*),
    bool (*signup_cb)(Credential*),
    bool (*deposit_cb)(Request*),
    bool (*withdrawl_cb)(Request*)
) {
    this->login_cb = login_cb;
    this->signup_cb = signup_cb;
    this->deposit_cb = deposit_cb;
    this->withdrawl_cb = withdrawl_cb;
}

Driver::~Driver() {}

void Driver::start() {
    LandingPage* lp = new LandingPage();
	LandingResult* lr = lp->wait_for_result();
    bool was_successful;

	switch (lr->type) {
		case LOGIN:
            was_successful = this->login_cb(lr->cred);
            if (was_successful) {
                lp->popup("Successfully logged in");

                HomePage* hp = new HomePage();
                HomeResult* hr = hp->wait_for_result();

            }
            else
                lp->popup("Failed logging in");
			break;
		case CREATE:
            was_successful = this->signup_cb(lr->cred);
            if (was_successful)
                lp->popup("Successfuly created account");
            else
                lp->popup("Failed creating account");
			break;
	}
    
    delete lp, lr;
}
