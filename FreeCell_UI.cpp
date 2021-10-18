#include "FreeCell_UI.h"

Shell::Shell() {
    this->command = "";
    moveInfo = vector<int>(3, 0);
}
void Shell::enterCommand() {
    cout << ">> ";
    getline(cin, this->command);
}
void Shell::processCommand(string& status) {
    stringstream ss(command);
    vector<string> commandTokens;
    string token;
    while (getline(ss, token, ' ')) {
		commandTokens.push_back(token);
	}
    
    if (commandTokens.size() == 0) {
        ;   // 빈 명령어 무시
    }
    else if (commandTokens.size() == 1) {
        //////////////// 개발자 도구 /////////////////
        if (!commandTokens[0].compare("getMode")) {
            cout << status << endl;
            sleep(5);
            return;
        }
        else if (!commandTokens[0].compare("setMode")) {
            cin >> status;
            return;
        }
        ///////////////////////////////////////////
        if (status[0] == 'w') {
            if (!(commandTokens[0].compare("Y")) || !(commandTokens[0].compare("y")) || !(commandTokens[0].compare("yes"))) {
                // w 만 뗌
                status = status.substr(1, 1);
            }
            else if (!(commandTokens[0].compare("N")) || !(commandTokens[0].compare("n")) || !(commandTokens[0].compare("no"))) {
                status = "d";
            }
            else {
                status = "uc";
            }
        }
        else {
            if (!(commandTokens[0].compare("new"))) {
                status = "wn";
            }
            else if (!(commandTokens[0].compare("restart"))) {
                status = "wr";
            }
            else if (!(commandTokens[0].compare("undo"))) {
                status = "wu";
            }
            else if (!(commandTokens[0].compare("exit"))) {
                status = "we";
            }
            else {
                status = "uc";
            }
        }
    }
    else if (commandTokens.size() == 2) {
        // from, to 유효성 확인
        // 숫자만 있다면 amount 1 자동 적용
        // from:    commandTokens[0] - 1~8 / f1~f4
        // to:      commandTokens[1] - 1~8 / f1~f4 / h1~h4 
        // amount:  commandTokens[2] - 1 직접 더하기
        



    }
    else if (commandTokens.size() == 3) {
        // from, to, amount 유효성 확인
        // from:    commandTokens[0] - 1~8 / f1~f4
        // to:      commandTokens[1] - 1~8 / f1~f4 / h1~h4 
        // amount:  commandTokens[2] - 1 ~ BOARD_HEIGHT / f, h rk 가 있을 때 1 이외의 숫자면 x

        

    }
    else {
        status = "uc";
    }
}
void Shell::printMessage(string status) {
    vector<string> ordinal = {"1st line", "2nd line", "3rd line", "4th line", "5th line", "6th line", "7th line", "8th line", "FreeCell", "HomeCell"};
    int from = moveInfo[0] - 1;
    int to = moveInfo[1] - 1;
    int amount = moveInfo[2];
    if (from >= 20) {
        from = 9;
    }
    else if (from >= 10) {
        from = 8;
    }
    if (to >= 20) {
        to = 9;
    }
    else if (to >= 10) {
        to = 8;
    }

    if (!status.compare("d")) {
        cout << "Make your move\n";
    }
    else if (!status.compare("m")) {
        if (amount > 1) {
            cout << amount << " cards moved from " << ordinal[from] << " to " << ordinal[to] << "\n"; 
        }
        else {
            cout << amount << " card moved from " << ordinal[from] << " to " << ordinal[to] << "\n"; 
        }
    }
    else if (!status.compare("ud")) {
        cout << "Undo completed\n"; 
    }
    else if (!status.compare("um")) {
        cout << "※※※ Can't move that way! ※※※\n"; 
    }
    else if (!status.compare("uc")) {
        cout << "※※※ Unvalid command! ※※※\n";
    }
    else if (!status.compare("wr")) {
        cout << "Do you want to restart the game? (Y/N)\n";    
    }
    else if (!status.compare("r")) {
        cout << "Game restarted\n";
    }
    else if (!status.compare("wn")) {
        cout << "Do you want to start new game? (Y/N)\n";    
    }
    else if (!status.compare("n")) {
        cout << "New game loading complete\n";
    }
    else if (!status.compare("we")) {
        cout << "Do you want to quit the game? (Y/N)\n";    
    }
    else if (!status.compare("wa")) {
        cout << "Automatic completion is available. Do you want to activate it? (Y/N)\n"; 
    }
    else if (!status.compare("v")) {
        cout << "VICTORY!!!\n";    
    }
}
vector<int> Shell::getMoveInfo() {  
    return moveInfo;
}