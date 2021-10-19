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
    void processCommand(string& status);
    void printMessage(string status);
    vector<int> getMoveInfo();
};

// 추후 menu 화면 추가

#endif