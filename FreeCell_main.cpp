#include "FreeCell_Main.h"

const int BOARD_WIDTH = 33;
const int BOARD_HEIGHT = 20;
const int FREECELL_SIZE = 4;
const int HOMECELL_SIZE = 4;  
const vector<int> CASCADE_INITIAL_LENGTH = {7, 7, 7, 7, 6, 6, 6, 6};
const vector<string> CARD_SUIT = {"♠", "◇", "♣", "♡"};
const vector<string> CARD_NUMBER = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

int main() {
    Game original;
    Game ongoing = original;
    Shell shell;
    string status = "d";

    while (true) {
        system("clear");        // system("cls");
        cout << "FreeCell by H.J.Choo\n\n";
        ongoing.showGame();
        shell.printMessage(status);
        shell.enterCommand();
        shell.processCommand(status);

        if (!status.compare("m")) {
            if (ongoing.isMovable(shell.getMoveInfo())) {
                ongoing.moveCards(shell.getMoveInfo());
            }
        }
        else if (!status.compare("ud")) {
            ongoing.undoMove();
        }
        else if (!status.compare("r")) {
            ongoing = original;
        }
        else if (!status.compare("n")) {
            original = Game();
            ongoing = original;
        }
        else if (!status.compare("e")) {
            system("clear");
            cout << "Thank you for playing FreeCell by rainfall3363\n\n";
            break;
        }
        else if (!status.compare("a")) {
            ongoing.autoComplete();
        }
        
        if (ongoing.isWin()) {
            status = "v";
        }
        //else if (ongoing.isAllOrdered()) {
        //    status = "wa";
        //}
        // 자동 이동 확인

    }
    
    return 0;
}