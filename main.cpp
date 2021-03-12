#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
#include <string>
#include <chrono>

#include "helper.h"

using namespace std;
using namespace std::chrono;


int main() {

    turn = 1;
    win = false;

    comp_code = getRandomCode();
    //-------------------------------------
    cout << "\nCode: ";
    for (int i = 0; i < comp_code.size(); ++i) {
        cout << comp_code[i] << " ";
    }
    cout << endl;
    //-------------------------------------
    currentGuess = {1, 3, 5, 7}; //1122

    cout << "Think a 4 digit number \nIf your ready";

    //Create the set of 1296 possible codes

    makeSet();
    candidateSolutions.insert(candidateSolutions.end(), combinations.begin(), combinations.end());

    while (!win) {

        cout << "\n------- Turn: " << turn <<" -------"<< endl;

        // ------------------------- User Turn -------------------------
        cout << "guess my number : ";
        user_guess = getUserGuess();
        comp_respond = checkCode(user_guess, comp_code);

        cout << comp_respond << endl;

        //If the response is four colored pegs, the game is win
        if (comp_respond == "+4-0") {
            win = true;
            cout << "You Win!" << endl;
            break;
        }

        // ------------------------- Computer Turn -------------------------       
        //Remove currentGuess from possible solutions
        removeCode(combinations, currentGuess);
        removeCode(candidateSolutions, currentGuess);

        cout << "Your Number : ";
        for (int i = 0; i < currentGuess.size(); ++i) {
            cout << currentGuess[i] << " ";
        }
        cout<<"?"<<endl;

        cout << "Enter hint: ";
        user_hint = getHintFromUser(); // BU EKSİK KALDI
        //cin >> user_hint;

        if (user_hint == "+4-0") {
            win = true;
            cout << "Computer Win!" << endl;
            break;
        }

        //Remove from candidateSolutions,
        //any code that would not give the same response if it were the code
        pruneCodes(candidateSolutions, currentGuess, user_hint);

        //Calculate Minmax scores
        nextGuesses = minmax(turn);

        //Select next guess
        currentGuess = getNextGuess(nextGuesses);

        turn++;
    }//End while

    return 0;
}