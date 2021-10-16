#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<bits/stdc++.h>

using namespace std;

void getText();
void leftrotate(string &s, int d)
{
    reverse(s.begin(), s.begin()+d);
    reverse(s.begin()+d, s.end());
    reverse(s.begin(), s.end());
}
void rightrotate(string &s, int d)
{
   leftrotate(s, s.length()-d);
}
string permute(string k, int* arr, int n){

    string temp = "";
    for(int i =0; i < n; i++){
        temp += k[arr[i]-1];
    }
    return temp;
}
void permuteP(int* pinverse, int* p, int n){
    for(int i = 0; i < n; i++){
        pinverse[p[i]-1]=i+1;
    }
}


void processkey(string key, string &a, string &b){
    string k = key;
    //divide into two 5 bits
    string k5a, k5b;
    k5a = k.substr(0,5);
    k5b = k.substr(5,5);

    //left rotate 1bit;
    leftrotate(k5a, 1);
    leftrotate(k5b, 1);
    //store the rotated 2 5bit keys
    a = k5a;
    b = k5b;

};
string xorFunct(string a, string b){
    string temp = "";
    for(int i =0; i<a.size(); i++){
        if(a[i] != b[i]){
            temp += '1';
        } else{
            temp += '0';
        }
    }
    return temp;
}
string szero(string a){
    int s[4][4] = { {1,0,3,2},
                     {3,2,1,0},
                     {0,2,1,3},
                     {3,1,3,2} };
    //get row and column in binary
    string row ="";
    row += a[0];
    row += a[3];

    string col ="";
    col += a[1];
    col += a[2];

    //get row and col from binary to decimal
    unsigned long long int rowI, colI;
    rowI=bitset<64>(row).to_ullong();
    colI=bitset<64>(col).to_ullong();

    //get the decimal of [row][col] then change to binary string and return it
    cout << rowI << " " << colI << endl;
    int o = s[rowI][colI];
    string result = bitset<2>(o).to_string();
    return result;
}
string sone(string a){
    int s[4][4] = { {0,1,2,3},
                     {2,0,1,3},
                     {3,0,1,0},
                     {2,1,0,3} };
    //get row and column in binary
    string row ="";
    row += a[0];
    row += a[3];

    string col ="";
    col += a[1];
    col += a[2];

    //get row and col from binary to decimal
    unsigned long long int rowI, colI;
    rowI=bitset<64>(row).to_ullong();
    colI=bitset<64>(col).to_ullong();

    //get the decimal of [row][col] then change to binary string and return it
    cout << rowI << " " << colI << endl;
    int o = s[rowI][colI];
    string result = bitset<2>(o).to_string();
    return result;
}

//get inputs from user, check length and if only 1s and 0s
string getKeyInput(){
    string x;
    int flag = 0;
    cout << "Enter 10 bit binary key\n" << endl;
    cin >> x;
    if (x.length()!= 10){
        cout << "key must be 10 bits\n" << endl;
        x=getKeyInput();
    } else {
        for (int i =0; i<10;i++){
            if(x[i] != '1' && x[i] !='0'){
                cout << "key must only be 1s and 0s" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (flag == 1){
        x = getKeyInput();
    }
    return x;
}
string getPlaintext(){
    string x;
    int flag = 0;
    cout << "Enter 8 bit binary plaintext\n" << endl;
    cin >> x;
    if (x.length()!= 8){
        cout << "plaintext must be 8 bits\n" << endl;
        x=getPlaintext();
    } else {
        for (int i =0; i<8;i++){
            if(x[i] != '1' && x[i] !='0'){
                cout << "plaintext must only be 1s and 0s" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (flag == 1){
        x = getPlaintext();
    }
    return x;
}
string getCipherText(){
    string x;
    int flag = 0;
    cout << "Enter 8 bit binary Ciphertext\n" << endl;
    cin >> x;
    if (x.length()!= 8){
        cout << "Ciphertext must be 8 bits\n" << endl;
        x=getCipherText();
    } else {
        for (int i =0; i<8;i++){
            if(x[i] != '1' && x[i] !='0'){
                cout << "ciphertext must only be 1s and 0s" << endl;
                flag = 1;
                break;
            }
        }
    }
    if (flag == 1){
        x = getCipherText();
    }
    return x;
}


void sdes()
{
    int p10[10] = {3, 5,2,7,4,10,1,9,8,6};
    int p8[8] = {6,3,7,4,8,5,10,9};
    int ip[8] = {2,6,3,1,4,8,5,7};
    int ep[8] = {4,1,2,3,2,3,4,1};
    int p4[4] = {2,4,3,1};


    cout << "Welcome to SDES Encryption" << endl;
    string keyInput = getKeyInput();
    string plaintext = getPlaintext();
    //for key-----------------------------------------------
    //string keyInput = "1100010010";
    cout << "\n----key generation----\n";
    cout << "before permutation key input is " << keyInput << endl;
    keyInput = permute(keyInput,p10,10);
    cout << "after permutation key input is " << keyInput << endl;

    //split keyinput into 2 5bit binary and left rotate 1
    string k5a, k5b;
    processkey(keyInput,k5a, k5b);
    cout << "after left rotate 1 k5a, " << k5a << " k5b, " << k5b << endl;

    //permutation for key
    //add 2 5bit binary together then permute with p8 to get first key
    string key1= "";
    string kten= k5a+k5b;
    key1 = permute(kten,p8,8); //first key
    cout << "after permutation(8) key1 is " << key1 << endl;

    //left rotate the 2 5bit binarys 2 bits
    leftrotate(k5a,2);
    leftrotate(k5b,2);
    cout << "after left rotate 2 k5a, " << k5a << " k5b, " << k5b << endl;

    //to get second key, add the 2 5bit binarys and apply to p8
    kten= k5a+k5b;
    string key2= "";
    key2 = permute(kten,p8,8);
    cout << "after permutation(8) key2 is " << key2 << endl;
    //end key generation----------------------------------------

    ////////////////////////////////////////////////////////////
    //start plaintext to ciphertext-----------------------------
    cout << "\n----plaintext encryption----\n";
    cout << "plaintext: " << plaintext << endl;
    //initial permutation
    //apply 8bit plaintext to ip8
    plaintext = permute(plaintext,ip,8);
    cout << "after permutation(ip) plaintext is " << plaintext << endl;
    //split the permuted plaintext to 2 4bits
    string text4a, text4b;
    text4a = plaintext.substr(0,4);
    text4b = plaintext.substr(4,4);
    cout << "after split, text4a: " << text4a << " and text4b: " << text4b << endl;

    //-----------------first inner encrpyt till SW -----
    //e/p permutation
    //apply text4b to ep8
    string ep1= "";
    ep1 = permute(text4b,ep,8);
    cout << "after expansion permutation: " << ep1 << endl;
    //exlusive or ep1 with key1.
    ep1 = xorFunct(ep1,key1);
    cout << "after XOR with key1: " << ep1 << endl;
    //split into 2 4bits after XOR
    string s10, s11;
    s10 = ep1.substr(0,4);
    s11 = ep1.substr(4,4);
    cout << "after split, s10: " << s10 << " and s11: " << s11 << endl;
    //from 4 bit binary, to 2bit binary and combine
    s10 = szero(s10);
    s11 = sone(s11);
    string sCombined = s10 + s11;
    //p4 permutation and apply scombined to p4, then XOR with ipleft(text4a)
    string pFour = permute(sCombined,p4,4);
    string SWLeft = xorFunct(text4a, pFour);
    //--------------------end first inner encrpyt till SW

    //SW, swap SWLeft and text4b
    string SWRight = "";
    SWRight = SWLeft;
    SWLeft = text4b;
    //end SW

    //-----------start 2nd inner encrypt till ip-1
    //swLeft and SWright
    //apply SWRight to expansion permutation to get 8bit binary
    string ep2 ="";
    ep2 = permute(SWRight,ep,8);
    //XOR key2 with the newly expanded ep2
    ep2 = xorFunct(ep2,key2);
    //split ep2 to 2 4bit binary then turn to 2 bits binary
    string ep2left, ep2right;
    ep2left = ep2.substr(0,4);
    ep2right = ep2.substr(4,4);
    string s20, s21;
    s20 = szero(ep2left);
    s21 = sone(ep2right);
    //combine s20 and s21
    string sCombined2 = s20 + s21;
    string pFour2 = permute(sCombined2,p4,4);
    string ipInverseLeft = xorFunct(SWLeft, pFour2);

    //combine ipinverseLeft with SWRight
    string toIpinverse ="";
    toIpinverse = ipInverseLeft + SWRight;
    //get ip inverse permutation
    int ipinversePermu[8];
    permuteP(ipinversePermu,ip, 8);
    string ciphertext = permute(toIpinverse, ipinversePermu, 8);
    cout << "Ciphertext: " << ciphertext << endl;
    //s1 = sone(ep4b_right);
    //cout << "s0 ands 1 are " << s0 << " " << s1 << endl;

}

void sdesDecrypt(){

    int p10[10] = {3, 5,2,7,4,10,1,9,8,6};
    int p8[8] = {6,3,7,4,8,5,10,9};
    int ip[8] = {2,6,3,1,4,8,5,7};
    int ep[8] = {4,1,2,3,2,3,4,1};
    int p4[4] = {2,4,3,1};


    cout << "Welcome to SDES Decrpytion" << endl;
    string keyInput = getKeyInput();
    string cipherText = getCipherText();
    //for key-----------------------------------------------
    //string keyInput = "1100010010";
    cout << "\n----key generation----\n";
    cout << "before permutation key input is " << keyInput << endl;
    keyInput = permute(keyInput,p10,10);
    cout << "after permutation key input is " << keyInput << endl;

    //split keyinput into 2 5bit binary and left rotate 1
    string k5a, k5b;
    processkey(keyInput,k5a, k5b);
    cout << "after left rotate 1 k5a, " << k5a << " k5b, " << k5b << endl;

    //permutation for key
    //add 2 5bit binary together then permute with p8 to get first key
    string key1= "";
    string kten= k5a+k5b;
    key1 = permute(kten,p8,8); //first key
    cout << "after permutation(8) key1 is " << key1 << endl;

    //left rotate the 2 5bit binarys 2 bits
    leftrotate(k5a,2);
    leftrotate(k5b,2);
    cout << "after left rotate 2 k5a, " << k5a << " k5b, " << k5b << endl;

    //to get second key, add the 2 5bit binarys and apply to p8
    kten= k5a+k5b;
    string key2= "";
    key2 = permute(kten,p8,8);
    cout << "after permutation(8) key2 is " << key2 << endl;
    //end key generation----------------------------------------

    ////////////////////////////////////////////////////////////
    //start ciphertext to ciphertext-----------------------------
    cout << "\n----ciphertext decryption----\n";
    cout << "ciphertext: " << cipherText << endl;
    //initial permutation
    //apply 8bit ciphertext to ip8
    cipherText = permute(cipherText,ip,8);
    cout << "after permutation(ip) ciphertext is " << cipherText << endl;
    //split the permuted ciphertext to 2 4bits
    string text4a, text4b;
    text4a = cipherText.substr(0,4);
    text4b = cipherText.substr(4,4);
    cout << "after split, text4a: " << text4a << " and text4b: " << text4b << endl;

    //-----------------first inner encrpyt till SW -----
    //e/p permutation
    //apply text4b to ep8
    string ep1= "";
    ep1 = permute(text4b,ep,8);
    cout << "after expansion permutation: " << ep1 << endl;
    //exlusive or ep1 with key1.
    ep1 = xorFunct(ep1,key2);
    cout << "after XOR with key2: " << ep1 << endl;
    //split into 2 4bits after XOR
    string s10, s11;
    s10 = ep1.substr(0,4);
    s11 = ep1.substr(4,4);
    cout << "after split, s10: " << s10 << " and s11: " << s11 << endl;
    //from 4 bit binary, to 2bit binary and combine
    s10 = szero(s10);
    s11 = sone(s11);
    string sCombined = s10 + s11;
    //p4 permutation and apply scombined to p4, then XOR with ipleft(text4a)
    string pFour = permute(sCombined,p4,4);
    string SWLeft = xorFunct(text4a, pFour);
    //--------------------end first inner encrpyt till SW

    //SW, swap SWLeft and text4b
    string SWRight = "";
    SWRight = SWLeft;
    SWLeft = text4b;
    //end SW

    //-----------start 2nd inner encrypt till ip-1
    //swLeft and SWright
    //apply SWRight to expansion permutation to get 8bit binary
    string ep2 ="";
    ep2 = permute(SWRight,ep,8);
    //XOR key2 with the newly expanded ep2
    ep2 = xorFunct(ep2,key1);
    //split ep2 to 2 4bit binary then turn to 2 bits binary
    string ep2left, ep2right;
    ep2left = ep2.substr(0,4);
    ep2right = ep2.substr(4,4);
    string s20, s21;
    s20 = szero(ep2left);
    s21 = sone(ep2right);
    //combine s20 and s21
    string sCombined2 = s20 + s21;
    string pFour2 = permute(sCombined2,p4,4);
    string ipInverseLeft = xorFunct(SWLeft, pFour2);

    //combine ipinverseLeft with SWRight
    string toIpinverse ="";
    toIpinverse = ipInverseLeft + SWRight;
    //get ip inverse permutation
    int ipinversePermu[8];
    permuteP(ipinversePermu,ip, 8);
    string plainText = permute(toIpinverse, ipinversePermu, 8);
    cout << "plainText: " << plainText << endl;
    //s1 = sone(ep4b_right);
    //cout << "s0 ands 1 are " << s0 << " " << s1 << endl;

}

//---------------------------------END SDES---------------------
//=================================START RSA======================

int main(){
    int action;

    do
    {
        cout << "\n========Welcome to SDES========\n\n"
             << "Input action to be taken\n"
             << "1: Encrypt\n"
             << "2: Decrypt\n"
             << "0: Quit\n"
             << endl;

        cin.clear();
        cin >> action;
        switch (action) {
            case 0:
                cout << "Exiting SDES..." << endl;
                break;
            case 1:
                cin.ignore();
                sdes();

                break;
            case 2:
                sdesDecrypt();

                break;
            default:
                cout << "Invaild action" << endl;
                break;
        }

    }while (action != 0);
    return 0;

}


