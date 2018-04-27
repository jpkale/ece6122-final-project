//
// Created by Terrence Thurk on 4/27/2018.
//

#ifndef ENCRYPTION_ENCRYPTION_H
#define ENCRYPTION_ENCRYPTION_H

#endif //ENCRYPTION_ENCRYPTION_H

#include <string>

using namespace std;

class encryption{
public:
    static string encrypt(string data, string key);
    static string decrypt(string encryptedData, string key);
};
