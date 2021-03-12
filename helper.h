#ifndef HELPER_H_
#define HELPER_H_

#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

extern vector<vector<int>> combinations;
extern vector<vector<int>> candidate_solution;
extern vector<vector<int>> next_guesses;
extern vector<int> computer_code;
extern vector<int> code;
extern vector<int> current_guess;
extern vector<int> user_guess;
extern string computer_respond;
extern string user_hint;
extern bool win;
extern int turn;

void makeSet();
void removeCode(vector<vector<int>> &set, vector<int> code);
void pruneCodes(vector<vector<int>> &set, vector<int> code, string currentResponse);

bool checkResult(string user_hint,int who);

vector<int> getRandomCode();
vector<int> getUserGuess();
vector<vector<int>> minmax(int turn);
vector<int> getNextGuess(vector<vector<int>> next_guesses);

int getMaxScore(map<string, int> inputMap);
int getMinScore(map<vector<int>, int> inputMap);


string testCode(vector<int> guess);
string getHintFromUser();
string checkCode(vector<int> guess, vector<int> code);

#endif