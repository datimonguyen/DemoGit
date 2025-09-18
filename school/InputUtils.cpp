#include "InputUtils.h"
#include <iostream>
#include <cctype>

using namespace std;

bool checkName(string &input) {
    if (input.empty()) {
        cout << "The name is invalid!!!" << endl;
        return false;
    }
    if (isspace(input.front()) || isspace(input.back())) {
        return false;
    }

    for (int i = 0; i < input.size(); i++) {
        if (!isalpha(input[i]) && !isspace(input[i])) {
            return false;
        }
        if (isspace(input[i]) && i > 0 && isspace(input[i - 1])) {
            return false;
        }
    }

    // Viết hoa chữ cái đầu mỗi từ
    input[0] = toupper(input[0]);
    for (int i = 1; i < input.size(); i++) {
        if (isspace(input[i - 1])) {
            input[i] = toupper(input[i]);
        }
    }
    return true;
}

bool checkId(const string &input) {
    if (input.empty()) {
        cout << "ID is invalid!" << endl;
        return false;
    }
    for (char ch : input) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool checkScore(const string &input) {
    if (input.empty()) {
        cout << "Score is invalid!" << endl;
        return false;
    }
    for (char ch : input) {
        if (!isdigit(ch) && ch != '.') {
            return false;
        }
    }
    if (input.front() == '.' || input.back() == '.') {
        return false;
    }
    return true;
}

// Hàm nhập ID có kiểm tra
string inputId() {
    string id;
    while (true) {
        cout << " - Enter your ID: ";
        cin >> id;
        if (checkId(id)) {
            int n = stoi(id);
            if (n > 0) break;
        }
        cout << "The ID is invalid!!!" << endl;
    }
    return id;
}

// Hàm nhập tên có kiểm tra
string inputName() {
    string name;
    cin.ignore();
    while (true) {
        cout << " - Enter your name: ";
        getline(cin, name);
        if (checkName(name)) break;
        cout << "The name is invalid!!!" << endl;
    }
    return name;
}

// Hàm nhập điểm có kiểm tra
string inputScore() {
    string score;
    while (true) {
        cout << " - Enter your English score: ";
        cin >> score;
        if (checkScore(score)) break;
        cout << "Invalid score!!!" << endl;
    }
    return score;
}
