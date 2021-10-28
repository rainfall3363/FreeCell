#include "FreeCell_UI.h"

Shell::Shell() {
    this->command = "";
    moveInput = vector<int>(4, 0);
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
        if (!commandTokens[0].compare("forceMove")) {
            status = "fm";
            enterCommand();
            processCommand(status);
            return;
        }
        else if (!commandTokens[0].compare("getMode")) {
            cout << status << '\n';
            sleep(3);
            status = "d";
            return;
        }
        else if (!commandTokens[0].compare("setMode")) {
            cin >> status;
            return;
        }
        else if (!commandTokens[0].compare("getCard")) {
            status = "gc";
            cin >> moveInput[3];
            return;
        }
        ///////////////////////////////////////////
        if (status[0] == 'q') {
            if (!(commandTokens[0].compare("Y")) || !(commandTokens[0].compare("y")) || !(commandTokens[0].compare("yes"))) {
                // q 만 뗌
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
                    status = "qn";
                }
            }
            else if (!(commandTokens[0].compare("restart"))) {
                if (!status.compare("v")) {
                    status = "r";
                }
                else {
                    status = "qr";
                }
            }
            else if (!(commandTokens[0].compare("undo")) && status.compare("v")) {
                status = "ud";
            }
            else if (!(commandTokens[0].compare("exit"))) {
                if (!status.compare("v")) {
                    status = "x";
                }
                else {
                    status = "qx";
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
                moveInput[0] = (int)commandTokens[0][0] - 48;
                moveInput[1] = (int)commandTokens[1][0] - 48;
                if (status.compare("fm")) {
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 1 && commandTokens[1].size() == 2) { 
            if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9' && (commandTokens[1][0] == 'h' || commandTokens[1][0] == 'f') && commandTokens[1][1] < '5' && commandTokens[1][1] > '0') {
                moveInput[0] = (int)commandTokens[0][0] - 48;
                if (commandTokens[1][0] == 'f') {
                    moveInput[1] = 10 + (int)commandTokens[1][1] - 48;
                }
                else if (commandTokens[1][0] == 'h') {
                    moveInput[1] = 20 + (int)commandTokens[1][1] - 48;
                }
                if (status.compare("fm")) {
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 1) {
            if ((commandTokens[0][0] == 'f' || commandTokens[0][0] == 'h') && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && commandTokens[1][0] < '9' && commandTokens[1][0] > '0') {
                if (commandTokens[0][0] == 'f') {
                    moveInput[0] = 10 + (int)commandTokens[0][1] - 48;
                }
                else if (commandTokens[0][0] == 'h') {
                    moveInput[0] = 20 + (int)commandTokens[0][1] - 48;
                }
                moveInput[1] = (int)commandTokens[1][0] - 48;
                if (status.compare("fm")) {
                    status = "m";
                }
            }
            else {
                status = "uc";
            }
        }
        else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 2) {
            if ((commandTokens[0][0] == 'f' || commandTokens[0][0] == 'h') && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && (commandTokens[1][0] == 'f' || commandTokens[1][0] == 'h') && commandTokens[1][1] > '0' && commandTokens[1][1] < '5') {
                if (commandTokens[0][0] == 'f') {
                    moveInput[0] = 10 + (int)commandTokens[0][1] - 48;
                }
                else if (commandTokens[0][0] == 'h') {
                    moveInput[0] = 20 + (int)commandTokens[0][1] - 48;
                }
                if (commandTokens[1][0] == 'f') {
                    moveInput[1] = 10 + (int)commandTokens[1][1] - 48;
                }
                else if (commandTokens[1][0] == 'h') {
                    moveInput[1] = 20 + (int)commandTokens[1][1] - 48;
                }
                if (status.compare("fm")) {
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

        if (moveInput[0] < 9 && moveInput[0] > 0 && moveInput[1] < 9 && moveInput[1] > 0 && status.compare("fm")) {
            moveInput[2] = -1;
        }
        else {
            moveInput[2] = 1;
        }
    }
    else if (commandTokens.size() == 3 && status.compare("v")) {
        if (commandTokens[2].size() == 1 && commandTokens[2][0] > '0' && commandTokens[2][0] <= '9') {
            amount = (int)commandTokens[2][0] - 48;
            if (status.compare("fm")) {
                status = "m";    
            }
        }
        else if (commandTokens[2].size() == 2 && commandTokens[2][0] == '1' && commandTokens[2][1] >= '0' && commandTokens[2][1] <= '9') {
            amount = ((int)commandTokens[2][0] - 48) * 10 + (int)commandTokens[2][1] - 48;
            if (status.compare("fm")) {
                status = "m";    
            }
        }
        else {
            status = "uc";
        }

        if (status.compare("uc")) {
            if (commandTokens[0].size() == 1 && commandTokens[1].size() == 1) {
                if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9' && commandTokens[1][0] > '0' && commandTokens[1][0] < '9') {
                    if (amount < 1 || amount > BOARD_HEIGHT) {
                        status = "uc";
                    }
                    else {
                        moveInput[0] = (int)commandTokens[0][0] - 48;
                        moveInput[1] = (int)commandTokens[1][0] - 48;
                        if (status.compare("fm")) {
                            status = "m";    
                        }
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
                        moveInput[0] = (int)commandTokens[0][0] - 48;
                        if (commandTokens[1][0] == 'f') {
                            moveInput[1] = 10 + (int)commandTokens[1][1] - 48;
                        }
                        else if (commandTokens[1][0] == 'h') {
                            moveInput[1] = 20 + (int)commandTokens[1][1] - 48;
                        }
                        if (status.compare("fm")) {
                            status = "m";    
                        }
                    }
                }
                else {
                    status = "uc";
                }
            }
            else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 1) {
                if ((commandTokens[0][0] == 'f' || commandTokens[0][0] == 'h') && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && commandTokens[1][0] < '9' && commandTokens[1][0] > '0') {
                    if (amount != 1) {
                        status = "uc";
                    }
                    else {
                        if (commandTokens[0][0] == 'f') {
                            moveInput[0] = 10 + (int)commandTokens[0][1] - 48;
                        }
                        else if (commandTokens[0][0] == 'h') {
                            moveInput[0] = 20 + (int)commandTokens[0][1] - 48;
                        }
                        moveInput[1] = (int)commandTokens[1][0] - 48;
                        if (status.compare("fm")) {
                            status = "m";    
                        }
                    }
                }
                else {
                    status = "uc";
                }
            }
            else if (commandTokens[0].size() == 2 && commandTokens[1].size() == 2) {
                if ((commandTokens[0][0] == 'f' || commandTokens[0][0] == 'h') && commandTokens[0][1] < '5' && commandTokens[0][1] > '0' && (commandTokens[1][0] == 'f' || commandTokens[1][0] == 'h') && commandTokens[1][1] > '0' && commandTokens[1][1] < '5') {
                    if (amount != 1) {
                        status = "uc";
                    }
                    else {
                        if (commandTokens[0][0] == 'f') {
                            moveInput[0] = 10 + (int)commandTokens[0][1] - 48;
                        }
                        else if (commandTokens[0][0] == 'h') {
                            moveInput[0] = 20 + (int)commandTokens[0][1] - 48;
                        }
                        if (commandTokens[1][0] == 'f') {
                            moveInput[1] = 10 + (int)commandTokens[1][1] - 48;
                        }
                        else if (commandTokens[1][0] == 'h') {
                            moveInput[1] = 20 + (int)commandTokens[1][1] - 48;
                        }
                        if (status.compare("fm")) {
                            status = "m";    
                        }
                    }
                }
                else {
                    status = "uc";
                }
            }
            else {
                status = "uc";
            }
            moveInput[2] = amount;
        }
    }
    else if (!status.compare("v")) {
        ;
    }
    else {
        status = "uc";
    }

    if (!status.compare("uc")) {
        moveInput = vector<int>(4, 0);
    }
}
void Shell::printMessage(string status, vector<int> moveInfo) {
    vector<string> ordinal = {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "f1", "f2", "f3", "f4", "h1", "h2", "h3", "h4"};
    int from = moveInfo[0] - 1;
    int to = moveInfo[1] - 1;
    int amount = moveInfo[2];
    if (from >= 20) {
        from -= 8;
    }
    else if (from >= 10) {
        from -= 2;
    }
    if (to >= 20) {
        to -= 8;
    }
    else if (to >= 10) {
        to -= 2;
    }

    if (!status.compare("d")) {
        cout << "Make your move\n";
    }
    else if (!status.compare("m")) {
        if (amount > 1) {
            cout << "[Move] " << ordinal[from] << " -> " << ordinal[to] << " / " << amount << " cards moved\n"; 
        }
        else {
            cout << "[Move] " << ordinal[from] << " -> " << ordinal[to] << " / " << amount << " card moved\n";
        }
    }
    else if (!status.compare("ud")) {
        cout << "[Move] Undo completed\n"; 
    }
    else if (!status.compare("qr")) {
        cout << "[Game] Restart the game? (Y/N)\n";    
    }
    else if (!status.compare("r")) {
        cout << "[Game] Game restarted\n";
    }
    else if (!status.compare("qn")) {
        cout << "[Game] Start the new game? (Y/N)\n";    
    }
    else if (!status.compare("n")) {
        cout << "[Game] New game load completed\n";
    }
    else if (!status.compare("qx")) {
        cout << "[Game] Quit the game? (Y/N)\n";    
    }
    else if (!status.compare("v")) {
        cout << "VICTORY!!!\n";    
    }
    else if (!status.compare("eud")) {
        cout << "[Error] No moves left\n";
    }
    else if (!status.compare("ewm")) {
        cout << "[Error] Wrong move\n"; 
    }
    else if (!status.compare("uc")) {
        cout << "[Error] Unvalid command\n";
    }
    else if (!status.compare("ems")) {
        cout << "[Error] Can't move to self\n";
    }
    else if (!status.compare("eec")) {
        cout << "[Error] Not enough cards to move\n";
    }
    else if (!status.compare("eef")) {
        if (moveInfo[3] == 1) {
            cout << "[Error] Can move " << moveInfo[3] << " card at once\n";
        }
        else {
            cout << "[Error] Can move " << moveInfo[3] << " cards at once\n";
        }
    }
    else if (!status.compare("eno")) {
        cout << "[Error] Cards not in order\n";
    }
    else if (!status.compare("ene")) {
        cout << "[Error] Cell is not empty\n";
    }
    else if (!status.compare("ehm")) {
        cout << "[Error] Can't move HomeCell's card\n";
    }
    else {
        cout << "[Error] Unvalid status\n";
    }
}
vector<int> Shell::getMoveInput() {
    return moveInput;
}