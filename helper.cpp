#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "helper.h"


vector<vector<int>> combinations; //Master set of combinations 1111 to 6666
vector<vector<int>> candidateSolutions;
vector<vector<int>> nextGuesses;
vector<int> comp_code;
vector<int> code;
vector<int> currentGuess;
vector<int> user_guess;
string comp_respond;
string user_hint;
bool win;
int turn;


vector<int> getRandomCode() {

    vector<int> code;
    int max = 9;
    int min = 1;
    int random;
    //Returns the number of seconds since the UNIX epoch for a seed
    srand(time(0));

    while(code.size()<4) {

        random = min + (rand() % (max - min + 1));
        if (find(code.begin(), code.end(), random) == code.end()) {
            code.push_back(random);
        }
    }

    return code;
}
vector<int> getUserGuess(){

    bool input_check = true;
    bool valid = false;
    vector<int> userCode;

    while (input_check){
        input_check = false;

        string s_userGuess;
        cin >> s_userGuess;
        
        // Check size 
        if (s_userGuess.size() != 4){
            cout << "Enter 4-digit number" << endl;
            cout << "guess my number: ";
            input_check = true;
            continue;
        }

        // Check is number or character
        
        for (int i = 0; i < s_userGuess.length(); i++){
            if (isdigit(s_userGuess[i]) == false){
                cout << "Enter numbers, not character"<<endl;
                cout << "guess my number: ";
                input_check = true;
                valid = false;
                break;
            }
            valid = true;
        }
        
        
        //check if there are same numbers in input
        for (int i = 0; i < 4; i++) {
            for (int j = (i + 1); j < 4; j++) {
                if (s_userGuess[i] == s_userGuess[j]) {
                    cout << "Digits should be different" << endl;
                    cout << "guess my number: ";
                    input_check = true;
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }
        if (!valid) continue;



        int userGuess = stoi(s_userGuess);

        while (userGuess > 0)
        {
            int digit = userGuess%10;
            userGuess /= 10;
            userCode.insert(userCode.begin(),digit);
        }
    }

    return userCode;

}

string getHintFromUser(){

    bool format_check = true;
    string user_input;
    while (format_check){
        format_check = false;

        user_input = "";
        cin >> user_input;

        // Check input size
        if (user_input.size() != 4){
            format_check = true;
            cout << "Hint length should be 4"<<endl;
            cout << "Enter hint: ";
            continue;
        }
        
        // Check Input Format
        if (user_input.at(0) != '+' || user_input.at(2) != '-'){
            format_check = true;
            cout << "Hint format should be like that --> +X-Y"<<endl;
            cout << "Enter hint: ";
            continue;
        }
        
        if (!isdigit(user_input.at(1)) || !isdigit(user_input.at(3))){
            format_check = true;
            cout << "Second and third value should be number --> +X-Y"<<endl;
            cout << "Enter hint: ";
            continue;
        }

        // Check sum of numbers 
        if ((user_input[1]-48)+(user_input[3]-48)>4){
            format_check = true;
            cout << "Sum of numbers can not be bigger than 4"<<endl;
            cout << "Enter hint: ";
            continue;
        }

    }
    return user_input;
}


void makeSet(){

    vector<int> current;

    for(int i = 1; i<=9;++i){
        for(int j = 0; j<=9; ++j){
            for(int k = 0; k<=9; ++k){
                for(int l = 0; l<=9; ++l){
                    //cout<<"i: "<<i<<" j: "<<j<<" k: "<<k<<" l: "<<l<<" ... "<<endl;

                    if (i == j || i == k || i == l || j == k || j == l || k == l)
                        continue;

                    current.push_back(i);
                    current.push_back(j);
                    current.push_back(k);
                    current.push_back(l);

                    combinations.push_back(current);
                    

                    /*for (int a=0;a<current.size();a++){
                        cout << current[a];    
                    }
                    cout<<endl;*/
                    current.clear();
                }
            }
        }
    }
}


string checkCode(vector<int> guess, vector<int> code) {

    string result;
    int correct_place = 0;
    int wrong_place = 0;

    //Get black/coloured
    result.append("+");
    for (int i = 0; i < 4; ++i) {

        if (guess[i] == code[i]) {
            correct_place++;
            guess[i] *= -1;
            code[i] *= -1;
        }
    }
    result.append(to_string(correct_place));

    //Get white
    result.append("-");
    for (int i = 0; i < 4; ++i) {

        if (code[i] > 0) {

            vector<int>::iterator it = find(guess.begin(), guess.end(), code[i]);
            int index;
            if (it != guess.end()) {
                wrong_place++;
                index = distance(guess.begin(), it);
                guess[index] *= -1;
            }
        }
    }
    result.append(to_string(wrong_place));

    return result;
}




void removeCode(vector<vector<int>> &set, vector<int> currentCode) {

    int index;
    for (auto it = set.begin(); it != set.end(); it++) {
        index = distance(set.begin(), it);

        if (set[index] == currentCode) {
            set.erase(set.begin() + index);
            break;
        }
    }
}

void pruneCodes(vector<vector<int>> &set, vector<int> currentCode, string currentResponse) {

    int index;
    vector<vector<int>>::iterator it = set.begin();

    while (it != set.end()) {
        index = distance(set.begin(), it);

        if (currentResponse != checkCode(currentCode, set[index])) {
            it = set.erase(set.begin() + index);
        } else {
            it++;
        }
    }
}

vector<vector<int>> minmax(int turn) {

    map<string, int> scoreCount;
    map<vector<int>, int> score;
    vector<vector<int>> nextGuesses;
    int max, min;

    for (int i = 0; i < combinations.size(); ++i) {
        if (turn == 1 && i>100){
            break;
        }
        for (int j = 0; j < candidateSolutions.size(); ++j) {

            string pegScore = checkCode(combinations[i], candidateSolutions[j]);
            if (scoreCount.count(pegScore) > 0) {
                scoreCount.at(pegScore)++;
            } else {
                scoreCount.emplace(pegScore, 1);
            }
        }

        max = getMaxScore(scoreCount);
        score.emplace(combinations[i], max);
        scoreCount.clear();
    }

    min = getMinScore(score);

    for (auto elem : score) {
        if (elem.second == min) {
            nextGuesses.push_back(elem.first);
        }
    }

    return nextGuesses;
}

int getMaxScore(map<string, int> inputMap) {

    int max = 0;
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int getMinScore(map<vector<int>, int> inputMap) {

    int min = numeric_limits<int>::max();
    for (auto elem : inputMap) {
        if (elem.second < min) {
            min = elem.second;
        }
    }

    return min;
}

vector<int> getNextGuess(vector<vector<int>> nextGuesses) {

    vector<int> nextGuess;

    for (int i = 0; i < nextGuesses.size(); ++i) {
        if (find(candidateSolutions.begin(), candidateSolutions.end(), nextGuesses[i]) != candidateSolutions.end()) {
            return nextGuesses[i];
        }
    }
    for (int j = 0; j < nextGuesses.size(); ++j) {
        if (find(combinations.begin(), combinations.end(), nextGuesses[j]) != combinations.end()) {
            return nextGuesses[j];
        }
    }

    return nextGuess;
}