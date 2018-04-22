// This module encrypts data using a key
// Created by Terrence Thurk on 4/17/18.
//

#include <iostream>
#include <string>

using namespace std;

//This function performs XOR encryption on the data
string XOREncryption(string data, string key){
    //Variable to store the encrypted string
    string encrypted = data;
    //Integer to prevent overflow outside of the bounds of the key
    const unsigned int bound = (unsigned) key.length();

    //for loop to encrypt the data using XOR encryption
    for (int i=0; i < data.size(); ++i){
        encrypted[i] = data[i] ^ key[i % bound];
    }
    return encrypted;
}

//This function performs a Cesar Shift Cipher to scramble the data
string CShift(string data, string key, bool encrypt){
    unsigned int tempKey = 14; //temporary key in implementation
    string cipherString = data;

    //for loop to perform Cesar Shift
    for (int i = 0; i < data.length(); ++i){
        //Handle letters in data
        if (isalpha(data[i])){
            //Assume character is uppercase letter (lower case letter handled later)
            //ASCII 65 = 'A' so we will need to offset by this when we do letter shifting
            unsigned int offset = 65;

            if (islower(data[i])){
                //Now we handle cases where the character is lowercase
                //ASCII 97 = 'a' so we will need to offset by this when we do letter shifting
                offset = 97;
                }

            //if encrypt is true then program shifts to encrypt.
            if (encrypt == true) {
                //Shifting algorithm. There exists 26 letters in the English alphabet.
                //The % modulus operator ensures we loop back to the character 'a' after ;z; is reached
                unsigned int cipherChar = (((unsigned int) data[i] - offset + tempKey) % 26) + offset;
                cipherString[i] = (char) cipherChar;
            }

            //otherwise we assume decryption and program shifts to decrypt.
            else {
                unsigned int cipherChar = (((unsigned int) data[i] - offset + (26 - tempKey)) % 26) + offset;
                cipherString[i] = (char) cipherChar;
            }
        }
        //handle numbers in data
        if (isdigit(data[i])){

            //ASCII 48 = '0' so we will need to offset by this when we do shifting
            unsigned int offset = 48;

            if (encrypt == true){

                unsigned int cipherDigit = (((unsigned int)data[i] - offset + tempKey) % 10) + offset;
                cipherString[i] = (char) cipherDigit;
            }
            else{
                unsigned int cipherDigit = (((unsigned int)data[i] - offset + (10 - tempKey)) % 10) + offset;
                cipherString[i] = (char) cipherDigit;
            }
        }
    }

    return cipherString;
}

int main(){
    string data = "Terry deposited $300 to Checkings Account 1457";
    string key = "h@x0rs";
//    cout<<"original message:"<<endl;
//    cout<<data<<endl;
//    cout<<"encryped message:"<<endl;
//    string encrypted = XOREncryption(data, key);
//    cout<<encrypted<<endl;
//    cout<<"decrypted message:"<<endl;
//    cout<<XOREncryption(encrypted, key)<<endl;

//    cout<<"original message:"<<endl;
//    cout<<data<<endl;
//    cout<<"encryped message:"<<endl;
//    string encrypted = CShift(data, key, true);
//    cout<<encrypted<<endl;
//    cout<<"decrypted message:"<<endl;
//    cout<< CShift(encrypted, key, false)<<endl;

    cout<<"original message:"<<endl;
    cout<<data<<endl;
    cout<<"encryption begins!!!"<<endl;
    cout<<"scrambled message:"<<endl;
    string shifted = CShift(data, key, true);
    cout<< shifted<<endl;
    cout<<"encrypted scrambled message:"<<endl;
    string encrypted = XOREncryption(shifted, key);
    cout<< encrypted<<endl;
    cout<<"\ndecryption begins!"<<endl;
    cout<<"decrypted scrambled message"<<endl;
    string decryptedShifted = XOREncryption(encrypted, key);
    cout<< decryptedShifted<<endl;
    cout<<"decrypted message:"<<endl;
    cout<< CShift(decryptedShifted, key, false)<<endl;

}