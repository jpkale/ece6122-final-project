#include <thread>

#include "ui/driver.h"
#include "ui/landing.h"

using namespace ui;
using namespace std;

bool mock_success_login(Credential* cred) { return true; }
bool mock_failure_login(Credential* cred) { return false; }
bool mock_success_signup(Credential* cred) { return true; }
bool mock_failure_signup(Credential* cred) { return false; }
bool mock_success_withdrawl(Request* req) { return true; }
bool mock_failure_widthrawl(Request* req) { return true; }
bool mock_success_deposit(Request* req) { return true; }
bool mock_failure_deposit(Request* req) { return true; }

int main(int argc, char* argv[]) {
    Driver *ui_driver = new Driver(
        mock_success_login,
        mock_success_signup,
        mock_success_withdrawl,
        mock_success_deposit
    );
    ui_driver->start();
}
