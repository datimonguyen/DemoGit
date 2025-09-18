#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
using namespace std;

int letter[26];

void showletter(){
    for (char let = 'A'; let <= 'Z'; let++){
        cout << let <<": "<< letter[let - 'A'] << endl;    
    }
}
void readfile(const string& filename){
    ifstream file(filename);
    
    if (!file.is_open()){
        cout << "file này không mở được !!!" <<endl;
    }
    string line;
    while (getline(file, line)){
        for ( int i = 0; i < line.length(); i++){
            if (isalpha(line[i])){
               char room = toupper(line[i]);
               letter[room - 'A']++;
            }
    }
}
    file.close();
}

int main(){
    for (int i = 0; i < 26; i++){
        letter[i] = 0;
    }    
    readfile("NumberOfLetter.txt");
    showletter();
}

