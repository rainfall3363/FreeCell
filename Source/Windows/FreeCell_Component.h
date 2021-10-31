#ifndef FREECELL_COMPONENT_H
#define FREECELL_COMPONENT_H

#include "FreeCell_Main.h"

class Card {
public:
	int numIdx;
	int suitIdx;
	int color;

	Card();
	Card(int numIdx, int suitIdx);
	Card(const Card& original);
	bool canMoveCard(Card card);
	Card& operator=(const Card& ref);
	bool operator==(const Card& ref);
};

class Cell {
private:
	vector<Card> cell_cards;
public:
	Cell();
	Cell(int cellSize);
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
	int getOccupied(int cascadeNum);
	void putCard(int to, Card card);
	Card getCard(int cascadeNum, int fromBack = 1);
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
	vector<int> moveInfo;
	vector<vector<int>> moveLog;
public:
	Game();
	Game(const Game& original);
	vector<int> getMoveInfo();
	void showGame();
	bool canMoveCards(vector<int> moveInput, string& status);
	void moveCards(bool isUndo = false);
	bool canUndoMove();
	void undoMove();
	bool canAutoMove();
	bool canAutoComplete();
	void autoMove(string status);
	bool isWin();
	Game& operator=(const Game& ref);
};


#endif
