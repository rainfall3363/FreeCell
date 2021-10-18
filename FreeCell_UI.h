#ifndef FREECELL_UI_H
#define FREECELL_UI_H

#include "FreeCell_Main.h"

class Shell {
private:
    string command;
    vector<int> moveInfo;
public:
    Shell();    
    void enterCommand();
    void processCommand(string& status); // status를 리턴, move 명령을 저장
    void printMessage(string status);    // status에 따라 메세지 출력
    vector<int> getMoveInfo();
};

// 추후 menu 화면 추가

#endif