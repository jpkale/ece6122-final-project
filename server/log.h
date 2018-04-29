//
// Created by Rimza Afzal
//

#include <string>

using namespace std;

class log{
public:
    static void createFile(string user, string password);
    static void write(string user, string password, int balance, int amount, int flag);
    static int getBalance(string user, string password);
    static string getPassword(string user, string password);
};