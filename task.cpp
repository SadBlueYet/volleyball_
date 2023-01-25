#include <iostream>
void teamPlacement();
void teamTransition(int* teamOnePos, int* teamTwoPos);
int main(){
    teamPlacement();
}
void teamPlacement() {
    int teamOne[6]{ 1, 5, 23, 7, 21, 8 };
    int teamTwo[6]{ 12, 4, 11, 99, 26, 5 };
    for (int i = 0; i < 12; i++) {
        if ((i >= 3 && i < 6) || (i >= 6 && i < 9) || i >= 9) {
            if (i == 3 || i == 9) std::cout << '\t';
            if (i == 6) std::cout << '\n';
            if (i >= 3 && i < 6) printf("%3d", teamTwo[i - 3]);
            else if (i >= 6 && i < 9) printf("%3d", teamOne[i - 3]);
            else printf("%3d", teamOne[i - 6]);
        }
        else printf("%3d", teamOne[i]);
    }

    teamTransition(teamOne, teamTwo);
}
void teamTransition(int* teamOnePos, int* teamTwoPos) {
    int unitPosition;
    unitPosition = teamOnePos[5];
    for (int i = 5; i >= 0 ; i--) {
        
        teamOnePos[i] = teamOnePos[i - 1];
        
        if (i == 0) teamOnePos[i] = unitPosition;
    }
    for (int i = 0; i < 6; i++) {
        std::cout << teamOnePos[i] << ' ';
        if (i == 3) std::cout << '\n';
    }
}
