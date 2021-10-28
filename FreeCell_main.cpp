#include "FreeCell_Main.h"

int main() {
    // 게임 생성 파트
    Game original;
    Game ongoing = original;
    Shell shell;
    string status = "d";

    while (true) {
        system("clear");
        cout << "FreeCell by H.J.Choo\n\n";
        // 게임 출력 파트
        ongoing.showGame();
        shell.printMessage(status, ongoing.getMoveInfo());
        // 명령어 입력, 분석 파트
        shell.enterCommand();
        shell.processCommand(status);

        // 명령어 처리 파트
        if (!status.compare("m") || !status.compare("fm")) {
            if (ongoing.canMoveCards(shell.getMoveInput(), status)) {
                ongoing.moveCards();
            }
        }
        else if (!status.compare("ud")) {
            if (ongoing.canUndoMove()) {
                ongoing.undoMove();
            }
            else {
                status = "eud";
            }
        }
        else if (!status.compare("r")) {
            ongoing = original;
        }
        else if (!status.compare("n")) {
            original = Game();
            ongoing = original;
        }
        else if (!status.compare("x")) {
            system("clear");
            cout << "Thank you for playing FreeCell by rainfall3363\n\n";
            break;
        }
        else if (!status.compare("gc")) {
            ongoing.showCard(shell.getMoveInput()[3]);
            status = "d";
        }

        // 게임 결과 처리 파트
        while (ongoing.canAutoMove()) {
            ongoing.autoMove();
            if (ongoing.canAutoComplete()) {
                ongoing.autoComplete();
            }
        }
        if (ongoing.isWin()) {
            status = "v";
        }
    }
    
    return 0;
}
