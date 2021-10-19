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
    int amount = 0;
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
            sleep(4);
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
                if (!status.compare("v")) {
                    status = "n";
                }
                else {
                    status = "wn";
                }
            }
            else if (!(commandTokens[0].compare("restart"))) {
                if (!status.compare("v")) {
                    status = "r";
                }
                else {
                    status = "wr";
                }
            }
            else if (!(commandTokens[0].compare("undo")) && status.compare("v")) {
                status = "ud";
            }
            else if (!(commandTokens[0].compare("exit"))) {
                if (!status.compare("v")) {
                    status = "e";
                }
                else {
                    status = "we";
                }
            }
            else if (!status.compare("v")) {
                ;
            }
            else {
                status = "uc";
            }
        }
    }
    else if (commandTokens.size() == 2 && status.compare("v")) {
        if (commandTokens[0].size() == 1 && commandTokens[1].size() == 1) {
            if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9' && commandTokens[1][0] > '0' && commandTokens[1][0] < '9') {
                if (commandTokens[0][0] == commandTokens[1][0]) {
                    status = "um";
                }
                else {
                    moveInfo[0] = (int)commandTokens[0][0] - 48;
                    moveInfo[1] = (int)commandTokens[1][0] - 48;
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 1 && commandTokens[1].size() == 2) { 
            if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9' && (commandTokens[1][0] == 'h' || commandTokens[1][0] == 'f') && commandTokens[1][1] < '5' && commandTokens[1][1] > '0') {
                moveInfo[0] = (int)commandTokens[0][0] - 48;
                if (commandTokens[1][0] == 'f') {
                    moveInfo[1] = 10 + (int)commandTokens[1][1] - 48;
                }
                else if (commandTokens[1][0] == 'h') {
                    moveInfo[1] = 20 + (int)commandTokens[1][1] - 48;
                }
                status = "m";
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 1) {
            if (commandTokens[0][0] == 'f' && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && commandTokens[1][0] < '9' && commandTokens[1][0] > '0') {
                moveInfo[0] = 10 + (int)commandTokens[0][1] - 48;
                moveInfo[1] = (int)commandTokens[1][0] - 48;
                status = "m";
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 2) {
            if (commandTokens[0][0] == 'f' && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && (commandTokens[1][0] == 'f' || commandTokens[1][0] == 'h') && commandTokens[1][1] > '0' && commandTokens[1][1] < '5') {
                if (commandTokens[0][0] == 'f' && commandTokens[1][0] == 'f' && commandTokens[0][1] == commandTokens[1][1]) {
                    status = "um";
                }
                else {
                    moveInfo[0] = 10 + (int)commandTokens[0][1] - 48;
                    if (commandTokens[1][0] == 'f') {
                        moveInfo[1] = 10 + (int)commandTokens[1][1] - 48;
                    }
                    else if (commandTokens[1][0] == 'h') {
                        moveInfo[1] = 20 + (int)commandTokens[1][1] - 48;
                    }
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else {
            status = "uc";
        }
        this->moveInfo[2] = 1;
    }
    else if (commandTokens.size() == 3 && status.compare("v")) {
        if (commandTokens[2].size() == 1) {
            amount = (int)commandTokens[2][0] - 48;
        }
        else if (commandTokens[2].size() == 2) {
            amount = ((int)commandTokens[2][0] - 48) * 10 + (int)commandTokens[2][1] - 48;
        }
        else {
            amount = 0;
        }
        
        if (commandTokens[0].size() == 1 && commandTokens[1].size() == 1) {
            if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9' && commandTokens[1][0] > '0' && commandTokens[1][0] < '9') {
                if (commandTokens[0][0] == commandTokens[1][0]) {
                    status = "um";
                }
                else if (amount < 1 || amount > BOARD_HEIGHT) {
                    status = "uc";
                }
                else {
                    moveInfo[0] = (int)commandTokens[0][0] - 48;
                    moveInfo[1] = (int)commandTokens[1][0] - 48;
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 1 && commandTokens[1].size() == 2) { 
            if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9' && (commandTokens[1][0] == 'h' || commandTokens[1][0] == 'f') && commandTokens[1][1] < '5' && commandTokens[1][1] > '0') {
                if (amount != 1) {
                    status = "uc";
                }
                else {
                    moveInfo[0] = (int)commandTokens[0][0] - 48;
                    if (commandTokens[1][0] == 'f') {
                        moveInfo[1] = 10 + (int)commandTokens[1][1] - 48;
                    }
                    else if (commandTokens[1][0] == 'h') {
                        moveInfo[1] = 20 + (int)commandTokens[1][1] - 48;
                    }
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 1) {
            if (commandTokens[0][0] == 'f' && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && commandTokens[1][0] < '9' && commandTokens[1][0] > '0') {
                if (amount != 1) {
                    status = "uc";
                }
                else {
                    moveInfo[0] = 10 + (int)commandTokens[0][1] - 48;
                    moveInfo[1] = (int)commandTokens[1][0] - 48;
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 2) {
            if (commandTokens[0][0] == 'f' && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && (commandTokens[1][0] == 'f' || commandTokens[1][0] == 'h') && commandTokens[1][1] > '0' && commandTokens[1][1] < '5') {
                if (commandTokens[0][0] == 'f' && commandTokens[1][0] == 'f' && commandTokens[0][1] == commandTokens[1][1]) {
                    status = "um";
                }
                else if (amount != 1) {
                    status = "uc";
                }
                else {
                    moveInfo[0] = 10 + (int)commandTokens[0][1] - 48;
                    if (commandTokens[1][0] == 'f') {
                        moveInfo[1] = 10 + (int)commandTokens[1][1] - 48;
                    }
                    else if (commandTokens[1][0] == 'h') {
                        moveInfo[1] = 20 + (int)commandTokens[1][1] - 48;
                    }
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else {
            status = "uc";
        }
        this->moveInfo[2] = amount;
    }
    else if (!status.compare("v")) {
        ;
    }
    else {
        status = "uc";
    }

    if (!status.compare("uc") || !status.compare("um")) {
        moveInfo = vector<int>(3, 0);
    }
}
void Shell::printMessage(string status) {
    vector<string> ordinal = {"1stLine", "2ndLine", "3rdLine", "4thLine", "5thLine", "6thLine", "7thLine", "8thLine", "FreeCell", "HomeCell"};
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
            cout << amount << "cards moved from " << ordinal[from] << " to " << ordinal[to] << "\n"; 
        }
        else {
            cout << amount << "card moved from " << ordinal[from] << " to " << ordinal[to] << "\n"; 
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