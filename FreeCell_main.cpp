#include "FreeCell_main.h"

const int BOARD_WIDTH = 35;
const int BOARD_HEIGHT = 17;
const int FREECELL_SIZE = 4;
const int HOMECELL_SIZE = 4;  
const vector<int> CASCADE_INITIAL_LENGTH = {7, 7, 7, 7, 6, 6, 6, 6};
const vector<string> CARD_SUIT = {"♠", "◇", "♣", "♡"};
const vector<string> CARD_NUMBER = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

int main() {
    // Menu 출력
    // 1. new game / 2. load game / 3. help / 4. exit
    Game original;
    Game ongoing = original;
    Shell shell;
    string mode = "d";
    
    while (true) {
        system("clear");        // system("cls");
        cout << "FreeCell by rainfall3363\n";
        ongoing.showGame();
        shell.enterCommand();
        mode = shell.processCommand(mode); // mode를 리턴, move 명령을 저장
        shell.printMessage(mode); 

    }
    
    return 0;
}