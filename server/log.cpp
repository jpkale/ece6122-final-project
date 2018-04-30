// All the functions for logging the data
// Created by Rimza Afzal.


#include "log.h"
#include "encryption.h"
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
 *                      password - write the password to associate with the user
 * Hard coded: and initial account balance of 0
 **************************************************************************************/
void log::createFile(string user, string password){
  string name;
  int balance = 0;
  name.append(user);
  name.append(".cvs");
  person.open(name, ios::app);
  person << encryption::encrypt("Password: ", password) << " " << encryption::encrypt(password, password) << endl;
  person << encryption::encrypt("Balance: ", password) << " " << encryption::encrypt(to_string(balance), password) << endl;
  person.close();
}

/********************************************************************************
 * Adds the data to the already created log file (updating the balance)
 * Variables to take in: user - to grab the file by user name
 *                       password - to use when encrypting information to file
 *                       balance - the new balance in the account
 *                       amount - the user ammount that was withdrawn/deposited
 *                       flag - 1: deposit 2: withdrawal
 ********************************************************************************/
void log::write(string user, string password, int balance, int amount, int flag){
  string name;
  name.append(user);
  name.append(".cvs");
  person.open(name, ios::app);
  switch(flag) {
    case 1:  //money is being deposited
      if (person.is_open()) {       //checks to make sure file is open
        person << encryption::encrypt("User deposited: ", password) << " " << encryption::encrypt(to_string(amount),password) << endl;
        person << encryption::encrypt("Balance: " , password)<< " " << encryption::encrypt(to_string(balance),password) << endl;
      } else {
        cout << "Unable to open file";
      }
          person.close();
          break;
    case 2:  //money is being withdrawn
      if (person.is_open()) {       //checks to make sure file is open
        person << encryption::encrypt("User withdrew: ", password) << " " << encryption::encrypt(to_string(amount),password) << endl;
        person << encryption::encrypt("Balance: " , password) << " " << encryption::encrypt(to_string(balance),password) << endl;
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
 *                       password - to decrypt information from file
 *******************************************************************/
int log::getBalance(string user, string password)
{
  string line, part1, part2, d1, d2;
  string name;
  int part = 5;
  name.append(user);
  name.append(".cvs");
  data.open(name);
  if(data.is_open()){     //checks to make sure file is open
    while (data >> ws && getline(data, line)) // skip empty lines
      data >> part1 >> part2;
      d1 = encryption::decrypt(part1, password);
      d2 = encryption::decrypt(part2, password);
      part = stoi(d2);
  }
  else {
    cout << "Unable to open file";
  }
  data.close();
  return part;
}

/**************************************************************************
 * Sends the password to the server (can be used for verification)
 * Variables to take in: user - to grab the file by user name
 **************************************************************************/
string log::getPassword(string user, string password)
{
  string name, part1, part2, d1, d2;
  name.append(user);
  name.append(".cvs");
  data.open(name);
  if(data.is_open()){     //checks to make sure file is open
    data >> part1 >> part2;
    d1 = encryption::decrypt(part1, password);
    d2 = encryption::decrypt(part2, password);
  }
  else {
    cout << "Unable to open file" << endl;
  }
  data.close();
  return d2;
}


/*******************************************************************
 * Creates new file of log with all data decrypted
 * Variables to take in: user - to grab the file by user name
 *                       password - to decrypt information from file
 *******************************************************************/
void log::openLog(string user, string password){
    string line, part1, part2, d1, d2;
    string name, newFile;
    name.append(user);
    name.append(".cvs");
    data.open(name);

    newFile.append(user);
    newFile.append("_decrypted.cvs");
    person.open(newFile, ios::trunc);

    while (data){
        data >> part1 >> part2;
        d1 = encryption::decrypt(part1, password);
        d2 = encryption::decrypt(part2, password);
        if(data){person << d1 << d2 << endl;}
    }

    data.close();
    person.close();
}
