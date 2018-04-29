#include <iostream>
#include <iomanip>
#include <string>

#include "log.h"

using namespace std;

int main() {
    string userNam , Dline, password, passCheck;
    int option, balance, newbalance, Uservalue;

    cout << "1) New user 2) Check Balance (Read Data)  3) Add money (Write Data) 4) Withdraw money 5) Check Password" << endl;
    cin >> option;

    cout << "Name:" << endl;
    cin >> userNam;

    cout << "Password:" << endl;
    cin >> password;

    //Checking all my functions work
    switch(option){
        case 1: //creating a new user file
            log::createFile(userNam,password);
            break;
        case 2: //checking your balance
            passCheck = log::getPassword(userNam, password);
            if(passCheck == password) {
                balance = log::getBalance(userNam, password);
                cout << "Balance = " << balance << endl;
            }
            else{
                cout << "Incorrect username or password" << endl;
            }
            break;
        case 3:  //Adding money to account
            passCheck = log::getPassword(userNam, password);
            if(passCheck == password) {
                cout << "Money to add:" << endl;
                cin >> Uservalue;
                balance = log::getBalance(userNam, password);
                newbalance = balance + Uservalue;
                log::write(userNam, password, newbalance, Uservalue, 1);
            }
            else{
                cout << "Incorrect username or password" << endl;
            }
            break;
        case 4:  //Taking money from account
            passCheck = log::getPassword(userNam, password);
            if(passCheck == password) {
                cout << "Money to withdraw:" << endl;
                cin >> Uservalue;
                balance = log::getBalance(userNam, password);
                newbalance = balance - Uservalue;
                log::write(userNam, password, newbalance, Uservalue, 2);
            }
            else{
                cout << "Incorrect username or password" << endl;
            }
            break;
        case 5:  //checking to see if I can get the password out from file
            passCheck = log::getPassword(userNam, password);
            if(passCheck == password){
                cout << "Correct" << endl;
            }
            else{
                cout << "Incorrect" << endl;
            }
            break;
        default:
            cout << "Did not choose an option" << endl;
            break;
    }

    return 0;
}


