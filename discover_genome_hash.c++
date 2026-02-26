#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
#define a 257
#define M 1000003

void Open_File(string& name){
    ifstream file("genome.txt");
    if(!file){
        cerr << "cannot open" << endl;
        exit(1);
    }
    file >> name;
    file.close();
}
double calculater(int i,string mine, string name){
    long long hash_name = 0;
    for(i; i < mine.size(); i++){
        hash_name +=((name[i]%M)*(int)pow(a,M-1-i)%M)%M;
    }
    return hash_name;
}

void Comparator(int i,string name, string mine, vector<bool>& board){
    int count = 0;
    for(i; i < name.size(); i++){
        if(name[i]==mine[0]){
            count=0;
            for(int j = 0; j < mine.size(); j++){
                if(name[j+i]==mine[j]){
                    count++;
                    if(count==mine.size())board[i]=true;
                }
            }
        }
    }
}

int main(void){
    string mine;
    cin >> mine;
    long long hash_mine=0;
    cout << hash_mine;
    for(int i = 0; i < mine.size(); i++){
        hash_mine += ((mine[i]%M)*(int)pow(a,M-1-i)%M)%M;
    }
    string name;
    Open_File(name);
    vector<bool> board(name.size(),false);
    for(int i = 0; i < name.size(); i++){
        if(calculater(i,mine,name)==hash_mine){
            cout << "a" << endl;
            Comparator(i,name,mine,board);
        }
    }
    for(int i = 0; i < name.size(); i++){
        if(board[i]==true) cout << i << endl;
    }
    return 0;
}