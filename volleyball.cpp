#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <random>

void playerActions(int* teamOne, int* teamTwo, int goal);
void teamPlacement(int* teamOne, int* teamTwo);
void teamTransition(int* teamPos);
void gameScore(int *teamOne, int *teamTwo);
int randomNumber(int min, int max);
int main() {
    int teamOne[6]{ 1, 5, 23, 7, 21, 8 };
    int teamTwo[6]{ 12, 4, 11, 99, 26, 5 };
    teamPlacement(teamOne, teamTwo);
    gameScore(teamOne, teamTwo);
}

void gameScore(int *teamOne, int *teamTwo) {
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

            std::cout << "\t\t\t\t" << counterTeamOne << " (" << teamOneScore << ')' << " - " <<
                counterTeamTwo << " (" << teamTwoScore << ')' << '\t';
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
    if (action == 1) {
        if (goal == 1) std::cout << "2" << " - " << "A - " << teamTwo[randomNumber(0, 5)] << '\n';
        else std::cout << "1" << " - " << "A - " << teamOne[randomNumber(0, 5)] << '\n';
    }
    else if (action == 2) {
        if (goal == 1) std::cout << "2" << " - " << "B - " << teamTwo[randomNumber(0, 5)] << '\n';
        else std::cout << "1" << " - " << "B - " << teamOne[randomNumber(0, 5)] << '\n';
    }
    else if (action == 3) {
        if (goal == 1) std::cout  << "2" << " - " << "S - " << teamTwo[randomNumber(0, 5)] << '\n';
        else std::cout << "1" << " - " << "S - " << teamOne[randomNumber(0, 5)] << '\n';
    }
    else if (action == 4) {
        if (goal == 1) std::cout << "2" << " - " << "F" << '\n';
        else std::cout << "1" << " - " << "F" << '\n';
    }
    
}