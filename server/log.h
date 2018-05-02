//
// Created by Rimza Afzal
//

#include <string>

using namespace std;

#define DEPOSIT     1
#define WITHDRAW    2

class log{
public:
    static void createFile(string user, string password);
    static void writeFile(string user, string password, double balance, double amount, int flag);
    static float getBalance(string user, string password);
    static string getPassword(string user, string password);
    static void openLog(string user, string password);
};
