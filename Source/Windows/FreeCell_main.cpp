#include "FreeCell_Main.h"

int main() {
	// ���� ���� ��Ʈ
	Game original;
	Game ongoing = original;
	Shell shell;
	string status = "d";

	while (true) {
		// ���� ��� ��Ʈ
		system("cls");
		cout << "FreeCell by H.J.Choo\n\n";
		ongoing.showGame();
		shell.setStatus(status);    // shell�� status ����
		shell.printMessage(ongoing.getMoveInfo());
		// ��ɾ� �Է�, �м� ��Ʈ
		shell.enterCommand();
		shell.processCommand();

		// ��ɾ� ó�� ��Ʈ
		status = shell.getStatus();     // shell���� ����� status �ҷ���
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
			system("cls");
			cout << "Thank you for playing FreeCell by H.J Choo\n\n";
			cout << "You can check the full code at the address below\n";
			cout << "https://github.com/rainfall3363/FreeCell\n\n";
			Sleep(1000);
			break;
		}

		// �ڵ� �̵� Ȯ�� ��Ʈ
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

		// ���� �¸� �Ǻ� ��Ʈ
		if (ongoing.isWin()) {
			status = "v";
		}
	}

	return 0;
}