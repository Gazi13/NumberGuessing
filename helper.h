#ifndef HELPER_H_
#define HELPER_H_

#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

extern vector<vector<int>> combinations; //Master set of combinations 1111 to 6666
extern vector<vector<int>> candidateSolutions;
extern vector<vector<int>> nextGuesses;
extern vector<int> comp_code;
extern vector<int> code;
extern vector<int> currentGuess;
extern vector<int> user_guess;
extern string comp_respond;
extern string user_hint;
extern bool win;
extern int turn;

void makeSet();
void removeCode(vector<vector<int>> &set, vector<int> code);
void pruneCodes(vector<vector<int>> &set, vector<int> code, string currentResponse);

vector<int> getRandomCode();
vector<int> getUserGuess();
vector<vector<int>> minmax(int turn);
vector<int> getNextGuess(vector<vector<int>> nextGuesses);

int getMaxScore(map<string, int> inputMap);
int getMinScore(map<vector<int>, int> inputMap);

string getHintFromUser();
string checkCode(vector<int> guess, vector<int> code);

#endif