#include "FreeCell_UI.h"

Shell::Shell() {
	this->command = "";
	this->status = "";
	moveInput = vector<int>(4, 0);
}
void Shell::enterCommand() {
	if (!status.compare("am")) {
		cout << "|| --- Auto Moving ---\n";
	}
	else if (!status.compare("ac")) {
		cout << "|| <<< Auto Completion >>>\n";
	}
	else {
		cout << ">> ";
		getline(cin, this->command);
	}
}
void Shell::processCommand() {
	bool moveValidity = true;
	stringstream ss(command);
	vector<string> commandTokens;
	string token;

	if (status[0] == 'a') {
		return;
	}
	// 명령어 Tokenize
	while (getline(ss, token, ' ')) {
		commandTokens.push_back(token);
	}
	// 명령어 분석 파트
	// 명령어 토큰이 0개인 경우 (빈 명령어)
	if (commandTokens.size() == 0) {
		if (status.compare("v") && status[0] != 'q') {
			status = "d";
		}
	}
	// 명령어 토큰이 1개인 경우
	else if (commandTokens.size() == 1) {
		//////////////// 개발자 도구 /////////////////
		if (!commandTokens[0].compare("getMode")) {
			cout << status << '\n';
			Sleep(3000);
			status = "d";
			return;
		}
		else if (!commandTokens[0].compare("setMode")) {
			cout << ">> ";
			cin >> status;
			return;
		}
		else if (!commandTokens[0].compare("hi") || !commandTokens[0].compare("hello")) {
			status = "hi";
			return;
		}
		///////////////////////////////////////////
		// 확인 질문의 경우
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
			else if (!(commandTokens[0].compare("exit"))) {
				if (!status.compare("v")) {
					status = "x";
				}
				else {
					status = "qx";
				}
			}
			else if (!(commandTokens[0].compare("undo")) && status.compare("v")) {
				status = "ud";
			}
			else if (!status.compare("v")) {
				;
			}
			else {
				status = "uc";
			}
		}
	}
	// victory 일 때 1개 토큰 명령어 이외는 무시
	else if (!status.compare("v")) {
		;
	}
	// 명령어 토큰이 2개인 경우 (이동 명령)
	else if (commandTokens.size() == 2) {
		// From 토큰
		// 길이가 1인 경우
		if (commandTokens[0].size() == 1) {
			if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9') {
				moveInput[0] = (int)commandTokens[0][0] - 48;
			}
			else {
				moveValidity = false;
			}
		}
		// 길이가 2인 경우
		else if (commandTokens[0].size() == 2) {
			if (commandTokens[0][0] == 'f' && commandTokens[0][1] > '0' && commandTokens[0][1] < '5') {
				moveInput[0] = 10 + (int)commandTokens[0][1] - 48;
			}
			else {
				moveValidity = false;
			}
		}
		else {
			moveValidity = false;
		}
		// To 토큰
		// 길이가 1인 경우
		if (commandTokens[1].size() == 1) {
			if (commandTokens[1][0] > '0' && commandTokens[1][0] < '9') {
				moveInput[1] = (int)commandTokens[1][0] - 48;
			}
			else if (commandTokens[1][0] == 'f') {
				moveInput[1] = 10;
			}
			else if (commandTokens[1][0] == 'h') {
				moveInput[1] = 20;
			}
			else {
				moveValidity = false;
			}
		}
		else {
			moveValidity = false;
		}
		// Amount 토큰
		if (moveInput[0] < 9 && moveInput[0] > 0 && moveInput[1] < 9 && moveInput[1] > 0) {
			moveInput[2] = -1;  // 보드 간의 이동 시엔 자동 갯수 설정으로 이행
		}
		else {
			moveInput[2] = 1;
		}

		// Move 명령 유효성 판단
		if (moveValidity) {
			status = "m";
		}
		else {
			status = "uc";
		}
	}
	// 명령어 토큰이 3개인 경우 (이동 명령)
	else if (commandTokens.size() == 3) {
		// Amount 토큰
		if (commandTokens[2].size() == 1 && commandTokens[2][0] > '0' && commandTokens[2][0] <= '9') {
			moveInput[2] = (int)commandTokens[2][0] - 48;
		}
		else if (commandTokens[2].size() == 2 && commandTokens[2][0] == '1' && commandTokens[2][1] >= '0' && commandTokens[2][1] <= '9') {
			moveInput[2] = ((int)commandTokens[2][0] - 48) * 10 + (int)commandTokens[2][1] - 48;
		}
		else {
			moveValidity = false;
		}
		// Cascade to Cascade 1가지 경우의 수만 존재함        
		if (moveValidity) {
			if (commandTokens[0].size() == 1 && commandTokens[1].size() == 1) {
				if (commandTokens[0][0] > '0' && commandTokens[0][0] < '9' && commandTokens[1][0] > '0' && commandTokens[1][0] < '9') {
					moveInput[0] = (int)commandTokens[0][0] - 48;
					moveInput[1] = (int)commandTokens[1][0] - 48;
				}
				else {
					moveValidity = false;
				}
			}
			else {
				moveValidity = false;
			}
		}

		// Move 명령 유효성 판단
		if (moveValidity) {
			status = "m";
		}
		else {
			status = "uc";
		}
	}
	// 명령어 토큰이 4개 이상인 경우
	else {
		status = "uc";
	}
}
void Shell::printMessage(vector<int> moveInfo) {
	vector<string> ordinal = { "1", "2", "3", "4", "5", "6", "7", "8", "F1", "F2", "F3", "F4", "H1", "H2", "H3", "H4" };
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
	else if (!status.compare("m") || !status.compare("am") || !status.compare("ac")) {
		if (moveInfo[2] == 1) {
			cout << "[Move] " << ordinal[from] << " -> " << ordinal[to] << " / " << amount << " card moved\n";
		}
		else {
			cout << "[Move] " << ordinal[from] << " -> " << ordinal[to] << " / " << amount << " cards moved\n";
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
	else if (!status.compare("eff")) {
		cout << "[Error] FreeCell is full\n";
	}
	else if (!status.compare("ehm")) {
		cout << "[Error] Can't move HomeCell's card\n";
	}
	else if (!status.compare("hi")) {
		cout << "Hello there!\n";
	}
	else {
		cout << "[Error] Unvalid status\n";
	}
}
vector<int> Shell::getMoveInput() {
	return moveInput;
}
void Shell::setStatus(string status) {
	this->status = status;
}
string Shell::getStatus() {
	return status;
}
/* void Shell::saveLog() {   // Save command & message at log file
;
} */

/* Menu::Menu() {
;
}
void Menu::inputMenu() {
cin >> menuSelection;
}
void Menu::displayMenu() {
}
void Menu::newGame() {
}
void Menu::loadGame() {
}
void Menu::help() {
}
void Menu::exitGame() {
} */