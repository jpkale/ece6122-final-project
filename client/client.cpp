#include <thread>

#include "ui/driver.h"

using namespace ui;
using namespace std;

int main(int argc, char* argv[]) {
    Driver *ui_driver = new Driver(NULL, NULL, NULL, NULL, NULL, NULL);
    ui_driver->start();
}
