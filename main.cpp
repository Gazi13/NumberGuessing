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

    // Yazilim icin rasgele sayi uret
    computer_code = getRandomCode();

    //-------------------------------------
    /*cout << "\nCode: ";
    for (int i = 0; i < computer_code.size(); ++i) {
        cout << computer_code[i] << " ";
    }
    cout << endl;*/
    //-------------------------------------


    // Yazilimin baslangic tahmini 
    current_guess = {1, 3, 5, 7}; //1122

    cout << "Think a 4 digit number \nIf your ready";

    // Muhtemel butun 4 basamaklı sayıların listesini olustur.
    // Daha sonra bu liste uzerınde elemeler yaparak sonuca ulasacagiz
    makeSet();

    // Bu listeyi eleme yapacagimiz candidate listesine kopyala
    candidate_solution.insert(candidate_solution.end(), combinations.begin(), combinations.end());

    // Main loop
    while (!win) {

        cout << "\n------- Turn: " << turn <<" -------"<< endl;

        // ------------------------- Kullanici Tahmini -------------------------
        cout << "guess my number : ";

        //Kullanicinin girdisini alıp kontrol et ve daha sonra ipucuyu olustur.
        user_guess = getUserGuess();
        computer_respond = checkCode(user_guess, computer_code);
        cout << computer_respond << endl;

        //Eger butun degerler dogru ise oyunu kazanir
        if (computer_respond == "+4-0") {
            win = true;
            cout << "You Win!" << endl;
            break;
        }

        // ------------------------- Yazilim Tahmini -------------------------       
        // Tekrar ayni sayi girmemek icin bir kere kullandigimiz sayiyi listeden cikariyoruz
        removeCode(combinations, current_guess);
        removeCode(candidate_solution, current_guess);

        // Yazilim tahminini ekrana basar ve kullanicidan ipucu bekler
        cout << "Your Number : ";
        for (int i = 0; i < current_guess.size(); ++i) {
            cout << current_guess[i] << " ";
        }
        cout<<"? \nEnter hint: ";
        
        // Ipucuyu alır ve formata uygun mu kontrol eder. 
        // Butun degerler dogruysa yazilim kazanir.
        user_hint = getHintFromUser();

        if (user_hint == "+4-0") {
            win = true;
            cout << "Computer Win!" << endl;
            break;
        }

        // candidate_solution icerisinde ayni karsiligi vermeyenleri listeden siler
        pruneCodes(candidate_solution, current_guess, user_hint);

        //Minmax skorları hesaplar
        next_guesses = minmax(turn);

        // Bir sonraki tahmini belirler
        current_guess = getNextGuess(next_guesses);

        turn++;
    }//End while

    return 0;
}