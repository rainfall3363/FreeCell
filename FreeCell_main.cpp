#include "FreeCell_Main.h"

const int BOARD_WIDTH = 33;
const int BOARD_HEIGHT = 20;
const int FREECELL_SIZE = 4;
const int HOMECELL_SIZE = 4;  
const vector<int> CASCADE_INITIAL_LENGTH = {7, 7, 7, 7, 6, 6, 6, 6};
const vector<string> CARD_SUIT = {"♠", "◇", "♣", "♡"};
const vector<string> CARD_NUMBER = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

int main() {
    // 게임 생성 파트
    Game original;
    Game ongoing = original;
    Shell shell;
    string status = "d";

    while (true) {
        system("clear");        // system("cls");
        cout << "FreeCell by H.J.Choo\n\n";
        // 게임 출력 파트
        ongoing.showGame();
        shell.printMessage(status);
        // 명령어 입력, 분석 파트
        shell.enterCommand();
        shell.processCommand(status);

        // 명령어 처리 파트
        if (!status.compare("m")) {
            if (ongoing.canMoveCards(shell.getMoveInfo())) {
                ongoing.moveCards(shell.getMoveInfo());
            }
            else {
                status = "um";
            }
        }
        else if (!status.compare("ud")) {
            if (ongoing.canUndoMove()) {
                ongoing.undoMove();
            }
            else {
                status = "nm";
            }
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
        
        // isAllOrder 될때까지 automove하다가 되면 autocompletion 발동하는 구조
        // 게임 결과 처리 파트
        if (ongoing.isWin()) {
            status = "v";
        }
        if (ongoing.canAutoComplete()) {
            ongoing.autoComplete();
        }
        if (ongoing.canAutoMove()) {
            // 한 번 할때마다 canAutoComplete() 확인 해야하나?
            ongoing.autoMove();
        }
    }
    
    return 0;
}