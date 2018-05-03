//
// Created by Rimza Afzal
//

#include <string>

using namespace std;

#define DEPOSIT     1
#define WITHDRAW    2

class log{
public:
    static bool createFile(string user, string password);
    static void writeFile(string user, string password, long balance, long amount, int flag);
    static long getBalance(string user, string password);
    static string getPassword(string user, string password);
    static void openLog(string user, string password);
};
