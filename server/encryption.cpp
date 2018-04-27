// This module encrypts data using a key
// Created by Terrence Thurk on 4/17/18.

#include <iostream>
#include <string>
#include "encryption.h"
using namespace std;

//This function performs XOR encryption on the data
string XOREncryption(string data, string key) {
    //Variable to store the encrypted string
    string encrypted = data;
    //Make a dataSize variable so data.size() does not have to run in the for loop
    unsigned long dataSize = data.size();
    //Integer to prevent overflow outside of the bounds of the key
    const unsigned long bound = key.length();

    //for loop to encrypt the data using XOR encryption
    for (unsigned long i = 0; i < dataSize; ++i) {
        encrypted[i] = data[i] ^ key[i % bound];
    }
    return encrypted;
}

//This function performs a Cesar Shift Cipher to scramble the data
string CShift(string data, string key, bool encrypt) {
    string cipher = data;
    //Store length of key so key.length() does not have to run in the for loop
    const unsigned long keyLength = key.length();

    //for loop to perform Cesar Shift
    for (unsigned long i = data.length(); i > 0; --i) {
        //Handle letters in data
        if (isalpha(data[i])) {
            //Assume character is uppercase letter (lower case letter handled later)
            //ASCII 65 = 'A' so we will need to offset by this when we do letter shifting
            unsigned int offset = 65;

            if (islower(data[i])) {
                //Now we handle cases where the character is lowercase
                //ASCII 97 = 'a' so we will need to offset by this when we do letter shifting
                offset = 97;
            }

            //if encrypt is true then program shifts to encrypt.
            if (encrypt == true) {
                //Shifting algorithm. There exists 26 letters in the English alphabet.
                //The first % 26 modulus operator converts the key to a shift patter between 0 and 25
                //The second % 26 operator ensures we loop back to the character 'a' after 'z' is reached
                unsigned int cipherChar = (((unsigned int) data[i] - offset
                                            + ((unsigned int) key[i % keyLength]) % 26) % 26) + offset;
                cipher[i] = (char) cipherChar;
            }

                //otherwise we assume decryption and program shifts to decrypt.
            else {
                unsigned int cipherChar = (((unsigned int) data[i] - offset
                                            + (26 - ((unsigned int) key[i % keyLength]) % 26)) % 26) + offset;
                cipher[i] = (char) cipherChar;
            }
        }
        //handle numbers in data
        if (isdigit(data[i])) {

            //ASCII 48 = '0' so we will need to offset by this when we do shifting
            unsigned int offset = 48;

            //if encrypt is true then program shifts to encrypt
            if (encrypt) {
                //Shifting algorithm. There exists 10 numbers in the English alphabet.
                //The first % 10 modulus operator converts the key to a shift patter between 0 and 25
                //The second % 10 operator ensures we loop back to the character 'a' after 'z' is reached
                //the % keyLength is to make sure that the index does not go out of bounds of the key
                unsigned int cipherDigit = (((unsigned int) data[i] - offset
                                             + ((unsigned int) key[i % keyLength]) % 10) % 10) + offset;
                cipher[i] = (char) cipherDigit;
            }

                //otherwise we assume decryption and program shifts to decrypt
            else {
                unsigned int cipherDigit = (((unsigned int) data[i] - offset
                                             + (10 - ((unsigned int) key[i % keyLength] % 10))) % 10) + offset;
                cipher[i] = (char) cipherDigit;
            }
        }

        //handle special characters ranging from ! to / located between 33 and 47 of the ASCII table
        if (data[i] > 32 && data[i] < 48) {
            unsigned int offset = 33;
            //if encrypt is true then program shifts to encrypt
            if (encrypt) {
                //Shifting algorithm. There exists 15 special letters in the range of 33 and 47 on the ASCII table
                //The first % 15 modulus operator converts the key to a shift patter between 0 and 25
                //The second % 15 operator ensures we loop back to the character 'a' after 'z' is reached
                //the % keyLength is to make sure that the index does not go out of bounds of the key
                unsigned int cipherSChar = (((unsigned int) data[i] - offset
                                             + ((unsigned int) key[i % keyLength]) % 15) % 15) + offset;
                cipher[i] = (char) cipherSChar;
            }

                //otherwise we assume decryption and program shifts to decrypt
            else {
                unsigned int cipherSChar = (((unsigned int) data[i] - offset
                                             + (15 - ((unsigned int) key[i % keyLength] % 15))) % 15) + offset;
                cipher[i] = (char) cipherSChar;
            }

        }
    }

    return cipher;
}

string ASCIIShift(const string data, const string key, bool encrypt){
    string cipher = data;
    //store lengths here so .length() does not have to run in the for loop
    const unsigned long keyLength = key.length();
    const unsigned long dataLength = data.length();
    //ASCIIcode ranges from 0 to 255, but CLion IDE wants to store it in an int.
    int ASCIIcode;

    //for loop to perform ASCII Shift
    for (unsigned long i = 0; i < dataLength; ++i) {
        //if encrypt is true then the program shifts to encrypt
        //the % keyLength is to make sure that the index does not go out of bounds of the key
        if (encrypt) {
            ASCIIcode = (data[i] + key[i % keyLength]) % 255;
            cipher[i] = (char)ASCIIcode;
        }
            //if encrypt is false then the program shifts to decrypt
        else {
            ASCIIcode = (data[i] - key[i %keyLength]) % 255;
            cipher[i] = (char)ASCIIcode;
        }
    }
    return cipher;
}

//encrypt function to chain together XOR, ASCII, and Cesar Shifts
string encryption::encrypt(const string data, const string key){
    return XOREncryption(ASCIIShift(CShift(data, key, true), key, true), key);
}

//decrypt function to chain together Cesar Shift, ASCII, and XOR
string encryption::decrypt(const string encryptedData, const string key){
    return CShift(ASCIIShift(XOREncryption(encryptedData, key), key, false), key, false);
}
