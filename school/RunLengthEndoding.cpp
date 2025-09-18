#include<iostream>
#include<vector>
#include<string>
using namespace std;

void compress(vector<int>& A, vector<int>& B){
    fill(B.begin(),B.end(),0);
    for(int x: A){
        B[x]++;
    }
}
void decompress(vector<int>& A1, vector<int>& B){
    A1.clear();
    for(int i = 1;i < (int)B.size();i++ ){
        for (int j = 0; j < B[i]; j++){
            A1.push_back(i);
        }
    };
    cout << "mang A sau khi giai nen:"<< endl;
    for ( int x : A1){
        cout << x << " ";
    }
    cout << endl;
}
int main(){
    vector <int> A ={2,3,4,1,2,53,24,43,53,1,24,35,56,34,1,2,4,35,36,57,78};
    vector <int> B(101);   
    compress(A,B);
    
    for(int i = 1; i <= (int)B.size(); i++){
        if (B[i] != 0){
            cout << i <<" appears " << B[i] << " times"<< endl;
        }
    }
    vector <int> A1;
    decompress(A1,B);
    return 0;
}
