#ifndef FREECELL_COMPONENT_H
#define FREECELL_COMPONENT_H

#include "FreeCell_Main.h"

extern const int BOARD_WIDTH;
extern const int BOARD_HEIGHT;
extern const int FREECELL_SIZE;
extern const int HOMECELL_SIZE;  
extern const vector<int> CASCADE_INITIAL_LENGTH ;
extern const vector<string> CARD_SUIT;
extern const vector<string> CARD_NUMBER;

class Card {
public:
    string numStr;
    string suit;
    int value;
    
    Card();
    Card(int numIdx, int suitIdx);
    Card(const Card& original);
    bool canMoveCard(Card card);
    Card& operator=(const Card& ref);
};

class Cell {
private:
    vector<Card> cell_cards;
public:
    Cell();
    Cell(int cell_size);
    Cell(const Cell& original);
    void putCell(int cellNum, Card card);    
    Card getCell(int cellNum);
    Card takeCell(int cellNum);
    void showCell();
    bool isWin();
    Cell& operator=(const Cell& ref);
};

class Cascade {
private:
    vector<Card> cascade;
    int occupied;
    friend class Board;
public:
    Cascade();
    Cascade(const Cascade& original);
    bool isOrdered(int amount = 0);
    Cascade& operator=(const Cascade& ref);
};

class Board {
private:
    vector<Cascade> cascades;
public:
    Board();
    Board(const Board& original);
    int getOccupied(int cascadeNum);    // 이동 명령 유효성 판단 위해 필요
    void putCard(int to, Card card);
    Card getCard(int cascadeNum, int reverseIdx = -1);
    Card takeCard(int from);
    void moveCards(int from, int to, int amount);
    void showBoard();
    bool isOrdered(int cascadeNum, int amount = 0);
    Board& operator=(const Board& ref);
};

class Game {
private:
    Cell freeCell;
    Cell homeCell;
    Board board;
    vector<vector<int>> moveLog;
public:
    Game();
    Game(const Game& original);
    void showGame();
    bool canMoveCards(vector<int> moveInfo);
    void moveCards(vector<int> moveInfo, bool isUndo = false);
    bool canUndoMove();
    void undoMove();
    bool canAutoMove();
    void autoMove();
    bool canAutoComplete();
    void autoComplete();
    bool isWin();
    Game& operator=(const Game& ref);
};


#endif