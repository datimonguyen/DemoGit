#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <vector>
#include "InputUtils.h"

using namespace std;

void wfile(const string& filename, string id, string name , string score) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout<< "file is not open";
    }
    file << left << setw(10) << id
         << setw(25) << name
         << setw(15) << score
         << endl;
    file.close();
}

void readfile(const string& filename) {
    string line;
    ifstream file(filename);
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int menu() {
    string option[] {
        "1. Adding new student",
        "2. Viewing the list",
        "3. Remove a student by ID",
        "4. Exit"
    };
    int choice = 0;
    while(true) {
        system("cls");
        cout << " ----- MENU -----"<<endl;
        for ( int i = 0; i < 4 ; i++) {
            if(i == choice ){
                cout << " >> " << option[i] << " << " << endl;
            }
            else{
                cout << "    " << option[i] << "    " << endl;
            }
        } 
        int key = _getch();
        if ( key == 224) {
            key = _getch();
            if (key == 72) choice = (choice -1 + 4 ) % 4;
            else if (key == 80) choice = (choice + 1 ) % 4;
        }
        else if (key == 13 ) {
            return choice;
        }
    }
}

void RemoveById(const string &filename, string &id) {
    ifstream  infile(filename);
    if(!infile.is_open()) {
        cout << "file is not open!!! "<<endl;
    }
    
    bool remove = false;
    vector<string> lines;
    string line;
    while (getline(infile,line)) {
        if(line.find(id) == 0) {
            remove = true;
            continue;
        }
        lines.push_back(line);
    }
    infile.close();

    if(!remove) {
        cout << " There is no one with this ID "<< endl;
    } else {
        cout << " A student has been removed" <<endl;
    }

    ofstream outfile(filename, ios::trunc);
    for (string each: lines) {
        outfile << each << endl;
    }
    outfile.close();
}

int main() {
    ofstream file("test.txt");
    file << "THE STUDENT LIST OF CLASS E24CQCE01"<<endl;
    file << left << setw(10) << "ID"          
         << setw(25) << "FULL NAME"
         << setw(15) << "ENGLISH SCORE"        
         << endl;
    file.close();

    while (true) {
        int tem = menu();
        if ( tem == 0) {
            cout << " you choose add student " << endl;
            string id = inputId();
            string name = inputName();
            string score = inputScore();
            wfile("test.txt", id, name, score);
            system("pause");
        }
        else if( tem == 1) {
            cout << " you choose view list "<< endl;
            readfile("test.txt");
            system("pause");
        }
        else if( tem == 2 ) {   
            string id = inputId();
            cout << " you choose remove " << endl;
            RemoveById("test.txt", id);
            system("pause");
        }
        else if( tem == 3 ) {
            cout << " you choose exit"<< endl;
            break;
        }
    }
}
