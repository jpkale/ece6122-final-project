#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

ofstream person;   //writing to
ifstream data;     //reading from

/**************************************************************************************
 * Creates the initial log file
 * Variables to take in: user - to name the file
 *                      accNum - write the account number to associate with the user
 * Hard coded: and initial account balance of 0
 **************************************************************************************/
void createFile(string user, int accNum){
    string name;
    int balance = 0;
    name.append(user);
    name.append(".cvs");
    person.open(name, ios::app);
    person << "Account number: " << accNum << endl;
    person << "Balance: " << balance << endl;
    person.close();
};

/********************************************************************************
 * Adds the data to the already created log file (updating the balance)
 * Variables to take in: user - to grab the file by user name
 *                       balance - the new balance in the account
 *                       amount - the user ammount that was withdrawn/deposited
 *                       flag - 1: deposit 2: withdrawal
 ********************************************************************************/
void log(string user, int balance, int amount, int flag){
    string name;
    name.append(user);
    name.append(".cvs");
    person.open(name, ios::app);
    switch(flag) {
        case 1:  //money is being deposited
            if (person.is_open()) {       //checks to make sure file is open
                person << "User deposited: " << amount << endl;
                person << "Balance: " << balance << endl;
            } else {
                cout << "Unable to open file";
            }
            person.close();
            break;
        case 2:  //money is being withdrawn
            if (person.is_open()) {       //checks to make sure file is open
                person << "User withdrew: " << amount << endl;
                person << "Balance: " << balance << endl;
            } else {
                cout << "Unable to open file";
            }
            person.close();
            break;
        default:
            cout << "flag was not set correct" << endl;
            break;
    }
}

/*******************************************************************
 * Sends the last line balance to the user
 * Variables to take in: user - to grab the file by user name
 *******************************************************************/
int getBalance(string user)
{
    string line, part1;
    string name;
    int part2 = 5;
    name.append(user);
    name.append(".cvs");
    data.open(name);
    if(data.is_open()){     //checks to make sure file is open
        while (data >> ws && getline(data, line)) // skip empty lines
            data >> part1 >> part2;
    }
    else {
        cout << "Unable to open file";
    }
    data.close();
    return part2;
}

/**************************************************************************
 * Sends the account number to the user 9can be used for verification)
 * Variables to take in: user - to grab the file by user name
 **************************************************************************/
int getAcctNum(string user)
{
    string name, part1, part2;
    int part3 = 0;
    name.append(user);
    name.append(".cvs");
    data.open(name);
    if(data.is_open()){     //checks to make sure file is open
        data >> part1 >> part2 >> part3;
    }
    else {
        cout << "Unable to open file" << endl;
    }
    data.close();
    return part3;
}

int main() {
    string userNam , Dline;
    int option, accunt, balance, newbalance, Uservalue;

    cout << "1) New user 2) Check Balance (Read Data)  3) Add money (Write Data) 4) Withdraw money 5) Accnt Num" << endl;
    cin >> option;

    cout << "Name:" << endl;
    cin >> userNam;

    //Checking all my functions work
    switch(option){
        case 1:
            cout << "Account number:" << endl;
            cin >> accunt;
            createFile(userNam, accunt);
            break;
        case 2:
            balance = getBalance(userNam);
            cout << "Balance = " << balance << endl;
            break;
        case 3:
            cout << "Money to add:" << endl;
            cin >> Uservalue;
            balance = getBalance(userNam);
            newbalance = balance + Uservalue;
            log(userNam, newbalance, Uservalue, 1);
            break;
        case 4:
            cout << "Money to withdraw:" << endl;
            cin >> Uservalue;
            balance = getBalance(userNam);
            newbalance = balance - Uservalue;
            log(userNam, newbalance, Uservalue, 2);
            break;
        case 5:
            accunt = getAcctNum(userNam);
            cout << "Account number is: " << accunt << endl;
            break;
        default:
            cout << "Did not choose an option" << endl;
            break;
    }

    return 0;
}


