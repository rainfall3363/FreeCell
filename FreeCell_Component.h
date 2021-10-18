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
    bool checkOrder();
    bool checkOrder(int amount);
    Cascade& operator=(const Cascade& ref);
};

class Board {
private:
    vector<Cascade> cascades;
    vector<Card> cards_list;
public:
    Board();
    Board(const Board& original);
    void putCard(int to, Card card);
    Card takeCard(int from);
    void moveCards(int from, int to, int amount);
    void showBoard();
    bool isAllOrdered();
    Board& operator=(const Board& ref);
};

class Game {
private:
    Cell freeCell;
    Cell homeCell;
    Board board;
    stack<vector<string>> moveLog;  // 생성자, 연산자 오버로딩에 추가해야함
public:
    Game();
    Game(const Game& original);
    void putCell(char ch, int cellNum, Card card);
    Card getCell(char ch, int cellNum);
    Card takeCell(char ch, int cellNum);
    void showGame();
    bool isMovable(vector<int> moveInfo);
    void moveCards(vector<int> moveInfo);
    void undoMove();
    bool isAllOrdered();
    void autoMove();
    void autoComplete();
    bool isWin();
    Game& operator=(const Game& ref);
};


#endif