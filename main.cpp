#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <chrono>

#include "helper.h"

using namespace std;
using namespace std::chrono;


int main() {

    turn = 1;
    win = false;
    int who = 0;
    current_guess = {1, 3, 5, 7};
    cout << "Think a 4 digit number \nIf your ready";


    // Yazilim icin rasgele sayi uret
    computer_code = getRandomCode();
    // Muhtemel butun 4 basamaklı sayıların listesini olustur.
    makeSet();
    // Bu listeyi eleme yapacagimiz candidate listesine kopyala
    candidate_solution.insert(candidate_solution.end(), combinations.begin(), combinations.end());


    // Main loop
    while (!win) {
        cout << "\n------- Turn: " << turn <<" -------"<< endl;
        // ------------------------------ Kullanici Tahmini ------------------------------
        who = 0;
        cout << "guess my number : ";

        //Kullanicinin girdisini alıp kontrol et ve daha sonra ipucuyu olustur.
        user_guess = getUserGuess();
        computer_respond = checkCode(user_guess, computer_code);
        cout << computer_respond << endl;

        //Eger butun degerler dogru ise oyunu kazanir
        win = checkResult(computer_respond,who);
        if (win)
            break;


        // ------------------------------ Yazilim Tahmini ------------------------------       
        who = 1;
        
        // Tekrar ayni sayi girmemek icin bir kere kullandigimiz sayiyi listeden cikariyoruz
        removeCode(combinations, current_guess);
        removeCode(candidate_solution, current_guess);

        // Yazilim tahminini ekrana basar ve kullanicidan ipucu bekler
        cout << "Your Number : ";
        for (int i = 0; i < current_guess.size(); ++i) {
            cout << current_guess[i] << " ";
        }
        cout <<"? "<<endl;
        cout << "Enter hint: ";

        // Ipucunu alır ve formata kontrolu yapar. 
        user_hint = getHintFromUser();        
        // Butun degerler dogruysa yazilim kazanir.
        win = checkResult(user_hint,who);

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