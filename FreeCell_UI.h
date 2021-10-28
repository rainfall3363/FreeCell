#ifndef FREECELL_UI_H
#define FREECELL_UI_H

#include "FreeCell_Main.h"

class Shell {
private:
    string command;
    vector<int> moveInput;
public:
    Shell();    
    void enterCommand();
    void processCommand(string& status); // 뱉기만 하면 됨
    void printMessage(string status, vector<int> moveInfo);   // 받아야됌
    vector<int> getMoveInput();
};

// 추후 menu 화면 추가
/*
class Menu {
private:
    int menu;
public:
    void displayMenu();
    void newGame();
    void loadGame();
    void helpGame();
    void exitGame();
}
*/
#endif