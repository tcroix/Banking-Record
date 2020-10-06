//
//  Banking Record System.cpp
//  Banking Account
//
//  Created by Taylor Croix on 9/27/20.
//  Copyright © 2020 Taylor Croix. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<cstdlib>
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::iostream;
class account {
private:
    char accountNum[20];
    char firstName[10];
    char lastName[10];
    float totalBal;
public:
    void readD();
    void showD();
    void searchR();
    void addR();
    void readR();
};
void account::readD() {
    cout<<"Enter Account Number: ";
    cin>>accountNum;
    cout<<"Enter First Name: ";
    cin>>firstName;
    cout<<"Enter Last Name: ";
    cin>>lastName;
    cout<<"Enter Balance: ";
    cin>>totalBal;
    cout<<endl;
}
void account::showD() {
    cout<<"Account Number: "<<accountNum<<endl;
    cout<<"First Name: "<<firstName<<endl;
    cout<<"Last Name: "<<lastName<<endl;
    cout<<"Current Balance: "<<totalBal<<endl;
}
void account::searchR() {
    int n;
    ifstream infile;
    infile.open("recordbank");
    if(!infile) {
        cout<<"Error: File not found"<<endl;
        return;
    }
    infile.seekg(0,infile.end);
    int size = sizeof(*this);
    cout<<"Enter Record Number: \n";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));
    infile.read(reinterpret_cast<char*>(this), size);
    showD();
    infile.close();
}
void account::addR() {
    int size = sizeof(*this);
    ofstream outfile;
    outfile.open("recordbank");
    readD();
    outfile.write(reinterpret_cast<char *>(this), size);
    outfile.close();
}
void account::readR() {
    int size = sizeof(*this);
    ifstream infile;
    infile.open("recordbank");
    if(!infile) {
        cout<<"Error: File not found"<<endl;
        return;
    }
    while(!infile.eof()){
        if(infile.read(reinterpret_cast<char*>(this), size)) {
            showD();
        }
    }
    infile.close();
}
int main() {
    account A;
    bool menu = true;
    int choice;
    while(menu != false) {
        cout<<"Select one option below ";
        cout<<"1 - Show Record \n";
        cout<<"2 - Search Record \n";
        cout<<"3 - Add Record \n";
        cout<<"4 - Quit \n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice) {
        case 1:
            A.readR();
            break;
        case 2:
            A.searchR();
            break;
        case 3:
            A.addR();
            break;
        case 4:
            menu = false;
            break;
        default:
            cout<<"Not a valid choice, try again";
            cin >> choice;
            break;
        }
    }
    return 0;
}
