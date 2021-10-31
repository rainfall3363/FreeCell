#ifndef FREECELL_UI_H
#define FREECELL_UI_H

#include "FreeCell_Main.h"

class Shell {
private:
    string command;
    string status;
    vector<int> moveInput;
public:
    Shell();
    void enterCommand();
    void processCommand();
    void printMessage(vector<int> moveInfo);
    vector<int> getMoveInput();
    void setStatus(string status);
    string getStatus();
    // void saveLog();  // Save command & message at log file
};

/*
class Menu {
public:
    int menuSelection;
    
    int inputMenu();
    void displayMenu();
    void newGame();
    void loadGame();
    void help();
    void exitGame();
}
*/
#endif