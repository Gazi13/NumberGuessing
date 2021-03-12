#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "helper.h"


vector<vector<int>> combinations;
vector<vector<int>> candidate_solution;
vector<vector<int>> next_guesses;
vector<int> computer_code;
vector<int> code;
vector<int> current_guess;
vector<int> user_guess;
string computer_respond;
string user_hint;
bool win;
int turn;


string testCode(vector<int> guess){

    vector<vector<int>> test_code 
    { 
        {2, 3, 9, 7},
        {4, 1, 0, 3},
        {7, 8, 9, 0},
        {1, 2, 3, 5}

    };

    string test_hint = checkCode(guess, test_code[3]);

    return test_hint;

}

bool checkResult(string respond,int who){
    
    if (respond == "+4-0") {
        win = true;
        if (who == 0)
            cout << "You Win!" << endl;
        else
            cout << "Computer Win!" << endl;
    }
    return win;
}

vector<int> getRandomCode() {
   /**
   * Rakamlari farkli 4 basamakli sayi olusturur.
   * 
   */

    vector<int> code;
    int max = 9;
    int min = 1;
    int random;
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
   /**
   * Kullanicinin girdigi tahmini alir.
   * Uygun olup olmadigini kontrol eder
   * Uzunluk - Harf - Farkli sayilardan olusma
   */

    bool input_check = true;
    bool valid = false;
    vector<int> userCode;

    while (input_check){
        input_check = false;

        string s_userGuess;
        cin >> s_userGuess;
        
        // Uzunluk kontrolu
        if (s_userGuess.size() != 4){
            cout << "Enter 4-digit number" << endl;
            cout << "guess my number: ";
            input_check = true;
            continue;
        }

        // Harf kontrolu
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
        
        // Farklı rakamlardan olusma kontrolu
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


        // Once int cevrilir
        // Daha sonra vector<int> olarak return edilir.
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
   /**
   * Kullanicinin girdigi ipucunu alir.
   * Uygun olup olmadigini kontrol eder
   * Uzunluk - Format - Toplam
   */

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
    /**
    * Rakamlari farkli 4 basamakli olan bütün sayilarin listesini olusturur
    * Bu listeden her tahmin sonrasi elemeler yapilarak sonuca ulasmaya calisilir.
    * 
    */

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
    /**
    * Kullanicinin tahmini ile yazilimin sayisini karsilastirir
    * ve uygun olan ipucuyu return eder
    * 
    */
    string result;
    int correct_place = 0;
    int wrong_place = 0;

    //Dogru yerdeki sayilar kontrol edilir
    result.append("+");
    for (int i = 0; i < 4; ++i) {

        if (guess[i] == code[i]) {
            correct_place++;
            guess[i] *= -1;
            code[i] *= -1;
        }
    }
    result.append(to_string(correct_place));

    // Yanlis yerdeki sayılar kontrol edilir.
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
    /**
    * Bir kere kullanılan sayiyi tekrar kullanmamak için
    * listeden o tahmini siler.
    */
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
   /**
   * candidate listesindeki dogru sayinin olusturacagi ipucu ile
   * kullanicinin verdigi ipucu aynı olacaktır. 
   * Bu yüzden listede ayni ipucu sonucunu vermeyen degeler elenir.
   */
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
    /**
    * Bir sonraki tahmin icin candidate listesinden en cok eleme yapacak sayi secilmelidir.
    * Bunun icin muhtemel inputlar teker teker denenip minimum eleme sayilari bulunur.
    * Daha sonra bunlar icerisinde maximum eleme yapan deger secilir.
    */

    map<string, int> scoreCount;
    map<vector<int>, int> score;
    vector<vector<int>> next_guesses;
    int max, min;

    for (int i = 0; i < combinations.size(); ++i) {
        if (turn == 1 && i>100){
            break;
        }
        for (int j = 0; j < candidate_solution.size(); ++j) {

            string pegScore = checkCode(combinations[i], candidate_solution[j]);
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
            next_guesses.push_back(elem.first);
        }
    }

    return next_guesses;
}

int getMaxScore(map<string, int> inputMap) {
    /**
    * map icindeki maximum degeri bulur
    */

    int max = 0;
    for (auto elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int getMinScore(map<vector<int>, int> inputMap) {
    /**
    * map icindeki minimum degeri bulur
    */

    int min = numeric_limits<int>::max();
    for (auto elem : inputMap) {
        if (elem.second < min) {
            min = elem.second;
        }
    }

    return min;
}

vector<int> getNextGuess(vector<vector<int>> next_guesses) {
    /**
    * Bir sonraki tahmin icin secilmis degerler arasında oncelikle candidate listesinde bulunanlar alinir
    * Yoksa butun ihtimallarin icinde oldugu tekrar kontrol edilerek ilk olan secilir.
    */

    vector<int> nextGuess;

    for (int i = 0; i < next_guesses.size(); ++i) {
        if (find(candidate_solution.begin(), candidate_solution.end(), next_guesses[i]) != candidate_solution.end()) {
            return next_guesses[i];
        }
    }
    for (int j = 0; j < next_guesses.size(); ++j) {
        if (find(combinations.begin(), combinations.end(), next_guesses[j]) != combinations.end()) {
            return next_guesses[j];
        }
    }

    return nextGuess;
}