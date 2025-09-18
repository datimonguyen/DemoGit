#include<iostream>
#include<fstream>
#include<conio.h>
#include<windows.h> 
#include<cctype> 
#include<iomanip>
#include<vector>
#include<stack>
using namespace std;

stack<vector<string>> history;

vector<string> ReadAll(const string &filename){
    string line;
    vector<string> lines;
    ifstream file(filename);
    while(getline(file, line)){
        lines.push_back(line);
    }
    file.close();
    return lines;
}

void writeAll(const string &filename, const vector<string>& lines){
    ofstream file(filename, ios::trunc);
    for(auto &line : lines){
        file << line << endl;
    }
    file.close();
}

void saveState(const string &filename){
    history.push(ReadAll(filename));
}

void undo(const string &filename){
    if (history.empty()){
        cout << " There is nothing to undo !!!"<< endl;
        return;
    }
    vector<string> prev = history.top();
    history.pop();
    writeAll(filename, prev);
    cout <<"Undo successfully !!! "<<endl;
}   
// ghi lại nội dung trong file
void wfile(const string& filename, string id, string name , string score){
    ofstream file(filename, ios::app);
    if (!file.is_open()){
        cout<< "file is not open";
    }
    file << left << setw(10) << id
         << setw(25) << name
         << setw(15) << score
         << endl;
    file.close();
}
//mở file để đọc
void readfile(const string& filename){
    string line;
    ifstream file(filename);
    while (getline(file, line)){
        cout << line<<endl;
    }
    file.close();
}
// chương trình chon nội dung bằng phím
int menu(){
    string option[]{
        "1. Adding new student",
        "2. Viewing the list",
        "3. Remove a student by ID",
        "4. Undo",
        "5. Exit"
    };
    int choice = 0;
    while(true){
        system("cls");
        cout << " ----- MENU -----"<<endl;
        for ( int i = 0; i < 5 ; i++){
            if(i  == choice ){
                cout << " >> " << option[i] << " << " << endl;
            }
            else{
                cout << "    " << option[i] << "    " << endl;
            }
        } 
        int key = _getch();
        if ( key == 224){
            key = _getch();
            if (key == 72){ // up
                choice = (choice -1 + 5 ) % 5;
            }
            else if (key == 80){ // down
                choice = (choice + 1 ) % 5;
            }
        }
        else if (key == 13 ){
            return choice;
        }
    }
}

// kiểm tra tên có phù hợp không
bool checkname (string &input){
    if (input.empty()){
        cout << "The name is invalid!!! " << endl;
        return false;
    }
    if (isspace(input.front()) || isspace(input.back())) {
        return false;
    }

    for (int i = 0 ; i < input.size(); i++ ){
        if (!isalpha(input[i]) && !isspace(input[i])){
            return false;
        }
        if (isspace(input[i]) && i > 0 && isspace(input[i-1])){
            return false;
        }
    }
    input[0] = toupper(input[0]);
    for (int i = 1 ; i < input.size(); i++ ){
        if(isspace(input[i-1])){
            input[i] = toupper(input[i]);

        }
    }
    return true;
}

// kiểm tra id có phù hợp không
bool checkid(string input){
    if (input.empty()){
        cout << "Id is invalid"<< endl;
        return false;
    }

    for (char ch : input){
        if(!isdigit(ch)){
            return false;
        }
    }
    return true;
}

//kiểm tra điểm có phù hợp không
bool checkscore(string input){
    if (input.empty()){
        cout << "Id is invalid"<< endl;
        return false;
    }
    for (char ch : input){
        if(!isdigit(ch) && ch != '.'){
            return false;
        }
    }
    if(input.front()=='.' || input.back()=='.'){
        return false;
    }
    return true;
}


// loại bỏ sinh viên bằng id
void RemoveById(const string &filename, string &id){
    ifstream  infile(filename);
    if(!infile.is_open()){
        cout << "file is not open!!! "<<endl;
    }
    
    bool remove = false;
    vector<string> lines;
string line;
    while (getline(infile,line)){
        if(line.find(id) == 0) {
            remove = true;
            continue;
        }
        lines.push_back(line);
    }
    infile.close();
    if(!remove){
        cout << " There is no one with this ID "<< endl;
    }else{
        cout << " A student has been removed" <<endl;
    }

    ofstream outfile(filename, ios::trunc);
    for (string each: lines){
        outfile << each << endl;
    }
    outfile.close();

}

int main(){
    // mở file để ghi tựa đề 
    ofstream file("test.txt");
    file << "THE STUDENT LIST OF CLASS E24CQCE01"<<endl;
    file << left << setw(10) << "ID"          
     << setw(25) << "FULL NAME"
     << setw(15) << "ENGLISH SCORE"        
     << endl;
    file.close();

    // lựa chọn !!!!
    while (true){
        int tem = menu();
        if ( tem == 0){
            string id;
            string name;
            string score;
            while (true){
                cout << " - Enter your ID: "; cin >> id ;
                    if (checkid(id)){
                        int n = stoi(id);
                        if (n > 0){
                            break;
                        }
                        else{
                        cout<< " The ID is invalid!!! " << endl;
                        }
                    }
                    else {
                        cout<< " The ID is invalid!!! " << endl;
                    }
            }
            while (true){
                cin.ignore();
                cout<< " - Enter your name: ";
                getline(cin,name);
                if (checkname(name)){
                    break;
                }
                else{
                    cout<< " The name is invalid!!!";
                }
            }

            while(true){
                cout << " - Enter your English score: "; cin >> score;
                if(checkscore(score)){
                    break;
                }
                else{
                    cout<< " Invalid score !!!"<< endl;
                }
            }
            saveState("test.txt");
            wfile("test.txt",id,name,score);
            system("pause");
        }
        else if( tem == 1){
            readfile("test.txt");
            system("pause");
        }
        else if( tem == 2 ){   
            string id;
            while (true){
                cout << " - Enter the ID to remove: "; cin >> id ;
                    if (checkid(id)){
                        int n = stoi(id);
                        if (n > 0){
                            break;
                        }
                        else{
                        cout<< " the ID is invalid!!! " << endl;
                        }
                    }
                    else {
                        cout<< " the ID is invalid!!! " << endl;
                    }
                }
            saveState("test.txt");
            RemoveById("test.txt",id);
            system("pause");

        }
        else if( tem == 3 ){
            undo("test.txt");
            system("pause");
        }
        else if( tem == 4 ){
            cout<< "GOOOBYE !!!"<< endl;
        }
    }
}