#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <fstream>
#include <string>

void playerActions(int* teamOne, int* teamTwo, int goal);
void teamPlacement(int* teamOne, int* teamTwo);
void teamTransition(int* teamPos);
void gameScore(int *teamOne, int *teamTwo);
void replacementOfPlayers(int* team, int* substitute, int* volleyballPlayer);
void logsOfFile(std::string action);
void result(int* counterOne, int* counterTwo);
bool checkingNumbers(int* team, int* substitute);
int randomNumber(int min, int max);

int main() {
    int teamOne[6]{ 1, 5, 23, 7, 21, 8 };
    int teamTwo[6]{ 12, 4, 11, 99, 26, 5 };
    teamPlacement(teamOne, teamTwo);
    gameScore(teamOne, teamTwo);
}

void gameScore(int *teamOne, int *teamTwo) {
    std::string action;
    int counter = 0; 
    int counterTeamOne = 0; 
    int counterTeamTwo = 0;
    int goal;
    int SUB;
    do{
    int teamOneScore = 0;
    int teamTwoScore = 0;
    SUB = 33;
        do {
            
            goal = randomNumber(0,1);
            if (goal == 0) teamOneScore++;
            else if (goal == 1) teamTwoScore++;
            action = std::to_string(counterTeamOne) + " (" + std::to_string(teamOneScore) + ") - "
                + std::to_string(counterTeamTwo) + " (" + std::to_string(teamTwoScore) + ")";
            std::cout << "\t\t\t\t" << action << '\t';
            logsOfFile(action);
            playerActions(teamOne, teamTwo, goal);

            if (teamOneScore >= 5 && (teamOneScore - teamTwoScore >= 2)) {
                counterTeamOne++;
                break;
            }
            else if (teamTwoScore >= 5 && (teamTwoScore - teamOneScore >= 2)) {
                counterTeamTwo++;
                break;
            }
            if (goal == 0 && SUB != goal && SUB != 33) {
                teamTransition(teamOne);
                teamPlacement(teamOne, teamTwo);
                SUB = 33;
            }
            else if (goal == 1 && SUB != goal && SUB != 33) {
                teamTransition(teamTwo);
                teamPlacement(teamOne, teamTwo);
                SUB = 33;
            }

            else SUB = goal;
        } while (true);
        if (counter == 3 || counterTeamOne == 2 || counterTeamTwo == 2) break; 
        counter++;
    } while (true);
    std::cout << counterTeamOne << " - " << counterTeamTwo;
    result(&counterTeamOne, &counterTeamTwo);
}
void teamPlacement(int* teamOne, int* teamTwo) {
    for (int i = 0; i < 6; i++) {
        if(i == 3) std::cout << '\t';
        if (i >= 3) printf("%3d", teamTwo[i - 3]);
        else printf("%3d", teamOne[i]);
    }
    std::cout << '\n';

    for (int i = 5; i >= 0; i--) {
        if (i == 2) std::cout << '\t';
        if(i > 2) printf("%3d", teamOne[i]);
        else printf("%3d", teamTwo[i + 3]);
    }
    std::cout << '\n' << '\n';
}
void teamTransition(int* teamPos) {
    int unitPosition;

    unitPosition = teamPos[5];
    for (int i = 5; i >= 0; i--) {
        teamPos[i] = teamPos[i - 1];
        if (i == 0) teamPos[0] = unitPosition;
    }
}
int randomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
void playerActions(int* teamOne, int* teamTwo, int goal) {
    int action = randomNumber(1, 5);
    std::string step;
    int volleyballPlayer, substitute;
    if (action == 1) {
        if (goal == 1) {
            step = "2 - A - ";
            step += std::to_string(teamTwo[randomNumber(0, 5)]);
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
        else {
            step = "1 - A - ";
            step += std::to_string(teamOne[randomNumber(0, 5)]);
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
    }
    else if (action == 2) {
        if (goal == 1) {
            step = "2 - B - ";
            step += std::to_string(teamTwo[randomNumber(0, 5)]);
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
        else {
            step = "1 - B - ";
            step += std::to_string(teamOne[randomNumber(0, 5)]);
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
    }
    else if (action == 3) {
        if (goal == 1) {
            step = "2 - S - ";
            step += std::to_string(teamTwo[randomNumber(0, 5)]);
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
        else {
            step = "1 - S - ";
            step += std::to_string(teamOne[randomNumber(0, 5)]);
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
    }
    else if (action == 4) {
        if (goal == 1) {
            step = "2 - F";
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
        else {
            step = "1 - F";
            std::cout << step << '\n' << '\n';
            logsOfFile(step);
        }
    }
    else if (action == 5) {
        if (randomNumber(1, 2) == 1) {
            do {
                volleyballPlayer = teamOne[randomNumber(0, 5)];
                substitute = randomNumber(1, 99);
                if (checkingNumbers(teamOne, &substitute) == true) {
                    replacementOfPlayers(teamOne, &substitute, &volleyballPlayer);
                    step = "1 - R(";
                    step += (std::to_string(substitute) + (char)26);
                    step += (std::to_string(volleyballPlayer) + ")");
                    std::cout <<step << '\n' << '\n';
                    logsOfFile(step);
                    teamPlacement(teamOne, teamTwo);
                    break;
                }
            } while (true);
        }
        else if (randomNumber(1, 2) == 2) {
            do {
                volleyballPlayer = teamTwo[randomNumber(0, 5)];
                substitute = randomNumber(1, 99);
                if (checkingNumbers(teamTwo, &substitute) == true) {
                    replacementOfPlayers(teamTwo, &substitute, &volleyballPlayer);
                    step = "2 - R(";
                    step += (std::to_string(substitute) + (char)26);
                    step += (std::to_string(volleyballPlayer) + ")");
                    std::cout << step << '\n' << '\n';
                    logsOfFile(step);
                    teamPlacement(teamOne, teamTwo);
                    break;
                }
            } while (true); 
        }
    }
}
bool checkingNumbers(int* team, int* substitute) {
    int counter = 0;
    for (int i = 0; i <= 5; i++) {
        if (team[i] == *substitute) counter++;
    }
    if (counter == 0) return true;
    else return false;
}
void replacementOfPlayers(int* team, int* substitute, int* volleyballPlayer) {
    for (int i = 0; i < 6; i++) {
        if (team[i] == *volleyballPlayer) team[i] = *substitute;
    }
}
void logsOfFile(std::string action) {
    std::ofstream logs;
    
    try { 
       logs.open("logs.txt", std::ofstream::app);
       logs << action << "\n\n";
       logs.close();
    }
    catch(std::string error) {
        std::cerr << "Critical ERROR!";
    }
}
void result(int* counterOne, int* counterTwo) {
    std::ofstream db;

    try {
        db.open("db.txt", std::ofstream::app);
        db << *counterOne << " - " << *counterTwo << "\n\n";
        db.close();
    }
    catch (std::string error) {
        std::cerr << "Critical ERROR!";
    }
}