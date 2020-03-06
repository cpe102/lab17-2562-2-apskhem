#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

int FindSumScore(string t);
string ToUpperCase(string t);
string GetStringBefore(string t, char split);
string GetStringAfter(string t, char split);
void FindName(string);
bool IsNumber(char c);
string FindGrade(int score);

int main()
{
    ifstream file("name_score.txt");
    
    vector<string> name;
    vector<string> grade;
    
    string line;
    while(getline(file, line)) {
    	name.push_back(GetStringBefore(line, ':'));
    	grade.push_back(FindGrade(FindSumScore(line)));
    }
    
    string frontCommand;
    string queryCommand;
    
    do {
    	string command;
    	cout << "Please input your command: ";
		getline(cin, command);
		
		frontCommand = GetStringBefore(command, ' ');
		queryCommand = GetStringAfter(command, ' ');
		
		if (ToUpperCase(frontCommand) == "GRADE") {
			for (unsigned short i = 0; i < grade.size(); i++) {
				if (ToUpperCase(grade[i]) == ToUpperCase(queryCommand)) {
					cout << name[i] << endl;
				}
			}
			cout << "----------------------------------" << endl;
		}
		else if (ToUpperCase(frontCommand) == "NAME") {
			bool isFound = false;
			for (unsigned short i = 0; i < name.size(); i++) {
				if (ToUpperCase(name[i]) == ToUpperCase(queryCommand)) {
					cout << name[i] << "'s grade = " << grade[i] << endl;
					isFound = true;
				}
			}
			
			if (!isFound)
				cout << "Connot found." << endl;
				
			cout << "----------------------------------" << endl;
		}
		else {
			cout << "Invalid Command" << endl;
		}
		
		
	}
	while (ToUpperCase(frontCommand) != "EXIT");

    return 0;
}

string ToUpperCase(string t) {
	for (unsigned short i = 0; i < t.size(); i++) {
		if (t[i] >= 97 && t[i] <= 122)
			t[i] -= 32;
	}
	
	return t;
}

int FindSumScore(string t) {
	bool isRead = false;
	bool isContinueNum = false;
	int sum = 0;
	string collectNum = "";
	for (unsigned short i = 0; i < t.size(); i++) {
        if (t[i] == ':') {
        	isRead = true;
            i++;
        }
        
        if (isRead && IsNumber(t[i])) {
        	collectNum += t[i];
		}
		else {
			sum += atoi(collectNum.c_str());
			collectNum = "";
		}
		
		if (t.size() - 1 == i) {
			sum += atoi(collectNum.c_str());
			collectNum = "";
		}
    }
    
    return sum;
}

string GetStringBefore(string t, char split) {
    string temp = "";
    for (unsigned short i = 0; i < t.size(); i++) {
        if (t[i] == split) {
            return temp;
        }
        temp += t[i];
    }
    
    return temp;
}

string GetStringAfter(string t, char split) {
	string temp = "";
	bool isContinue = false;
    for (unsigned short i = 0; i < t.size(); i++) {
    	if (isContinue) {
        	temp += t[i];
		}
    	
        if (t[i] == split) {
        	isContinue = true;
        }
    }
    
    return temp;
}

bool IsNumber(char c) {
	if (c >= 48 && c <= 58) return true;
	else return false;
}

string FindGrade(int score) {
    if (score >= 80) return "A";
    else if (score >= 70) return "B";
    else if (score >= 60) return "C";
    else if (score >= 50) return "D";
    else return "F";
}
