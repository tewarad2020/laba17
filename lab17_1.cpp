#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream source("name_score.txt");
    string text;
    char name[100];  
    char format[] = "%[^:]: %d %d %d";
    int sc[3];
    int j=0;
    
    while (getline(source,text)) {
        sscanf(text.c_str(),format,name,&sc[0],&sc[1],&sc[2]);
        string sN = "";
        while (name[j] != '\0') {
            sN += name[j];
            j++;
        }
        j=0;
        names.push_back(sN);
        scores.push_back(sc[0] + sc[1] + sc[2]);
        grades.push_back(score2grade(sc[0] + sc[1] + sc[2]));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    string text;
    getline(cin,text);
    int z = text.find_first_of(' ');
    command = text.substr(0,z);
    key = text.erase(0,z+1);
}

void searchName(vector<string> names, vector<int> scores, vector<char> grades, string key){
    bool status = false;
    for (unsigned int i=0;i<names.size();i++) {
        if (toUpperStr(names[i]) == key) {
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            cout << "---------------------------------\n";
            status = true;
        }
    }
    if (!status) {
        cout << "---------------------------------\n";
            cout << "Cannot found." << endl;
        cout << "---------------------------------\n";
    }
}

void searchGrade(vector<string> names, vector<int> scores, vector<char> grades, string key){
    cout << "---------------------------------\n";
    for (unsigned int i=0;i<names.size();i++) {
        if (key[0] == grades[i]) 
            cout << names[i] << " (" << scores[i] << ")" << endl;
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
