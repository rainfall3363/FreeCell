#include "FreeCell_Main.h"

int main() {
    // 게임 생성 파트
    Game original;
    Game ongoing = original;
    Shell shell;
    string status = "d";

    while (true) {
        // 게임 출력 파트
        system("clear");
        cout << "FreeCell by H.J.Choo\n\n";
        ongoing.showGame();
        shell.setStatus(status);    // shell의 status 세팅
        shell.printMessage(ongoing.getMoveInfo());
        // 명령어 입력, 분석 파트
        shell.enterCommand();
        shell.processCommand();
        
        // 명령어 처리 파트
        status = shell.getStatus();     // shell에서 변경된 status 불러옴
        if (!status.compare("m")) {
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
        else if (!status.compare("am") || !status.compare("ac")) {
            ongoing.autoMove(status);
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
            cout << "Thank you for playing FreeCell by H.J Choo\n\n";
            cout << "You can check the full code at the address below\n";
            cout << "https://github.com/rainfall3363/FreeCell\n\n";
            sleep(2);
            break;
        }

        // 자동 이동 확인 파트
        if (!status.compare("am") || !status.compare("ac") || !status.compare("m")) {
            if (ongoing.canAutoMove()) {
                if (ongoing.canAutoComplete()) {
                   status = "ac";
                }
                else {
                    status = "am";
                }
            }
            else {
                status = "m";
            }
        }

        // 게임 승리 판별 파트
        if (ongoing.isWin()) {
            status = "v";
        }
    }
    
    return 0;
}
