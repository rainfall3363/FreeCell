#include "FreeCell_Component.h"

Card::Card() {
    this->numStr = "-";
    this->suit = "-";
    this->value = 0;
}
Card::Card(int numIdx, int suitIdx) {
    this->numStr = CARD_NUMBER[numIdx];
    this->suit = CARD_SUIT[suitIdx];
    this->value = find(CARD_NUMBER.begin(), CARD_NUMBER.end(), numStr) - CARD_NUMBER.begin() + 1;
}
Card::Card(const Card& original) {
    this->numStr = original.numStr;
    this->suit = original.suit;
    this->value = original.value;
}
Card& Card::operator=(const Card& ref) {
    this->numStr = ref.numStr;
    this->suit = ref.suit;
    this->value = ref.value;
    return *this;
}

Cell::Cell() {
    this->cell_cards = vector<Card>(); 
}
Cell::Cell(int cell_size) {
    if (cell_size == 0) {
        this->cell_cards = vector<Card>();
    }
    else {
        this->cell_cards = vector<Card>(cell_size);
    }
}
Cell::Cell(const Cell& original) {
    if (original.cell_cards.size() == 0) {
        this->cell_cards = vector<Card>();
    }
    else {
        this->cell_cards = vector<Card>(original.cell_cards.size());
        copy(original.cell_cards.begin(), original.cell_cards.end(), this->cell_cards.begin());
    }
}
void Cell::putCell(int cellNum, Card card) {
    cell_cards[cellNum - 1] = card;    
}
Card Cell::getCell(int cellNum) {
    return cell_cards[cellNum - 1];
}
Card Cell::takeCell(int cellNum) {
    Card tmp = cell_cards[cellNum - 1];
    cell_cards[cellNum - 1] = Card();
    return tmp;
}
void Cell::showCell() {
    for (int i = 0; i < cell_cards.size(); i++) {
        if (cell_cards[i].value == 10) {
            cout << cell_cards[i].numStr << cell_cards[i].suit << " ";
        }
        else {
            cout << " " << cell_cards[i].numStr << cell_cards[i].suit << " ";
        }
    }
}
bool Cell::isWin() {
    for (int i = 0; i < cell_cards.size(); i++) {
        if (cell_cards[i].value != 13) {
            return false;
        }
    }
    return true;
}
Cell& Cell::operator=(const Cell& ref) {
    if (ref.cell_cards.size() == 0) {
        this->cell_cards = vector<Card>();}
    else {
        this->cell_cards = vector<Card>(ref.cell_cards.size());
        copy(ref.cell_cards.begin(), ref.cell_cards.end(), this->cell_cards.begin());
    }
    return *this;
}

Cascade::Cascade() {
    this->cascade = vector<Card>(BOARD_HEIGHT);
    this->occupied = 0;
}
Cascade::Cascade(const Cascade& original) {
    this->cascade = vector<Card>(BOARD_HEIGHT);
    copy(original.cascade.begin(), original.cascade.end(), this->cascade.begin());
    this->occupied = original.occupied;
}
bool Cascade::checkOrder() {
    for (int i = 0; i < cascade.size() - 1; i++) {
        int idx1 = find(CARD_SUIT.begin(), CARD_SUIT.end(), cascade[i].suit) - CARD_SUIT.begin();
        int idx2 = find(CARD_SUIT.begin(), CARD_SUIT.end(), cascade[i + 1].suit) - CARD_SUIT.begin();
        if ((idx1 % 2 == idx2 % 2) || (cascade[i].value - cascade[i + 1].value != 1)) {
            return false;
        }
    }
    return true;
}
bool Cascade::checkOrder(int amount) {
    // 1장 일때는 할 필요가 읎다
    for (int i = cascade.size() - amount; i < cascade.size() - 1; i++) {
        int idx1 = find(CARD_SUIT.begin(), CARD_SUIT.end(), cascade[i].suit) - CARD_SUIT.begin();
        int idx2 = find(CARD_SUIT.begin(), CARD_SUIT.end(), cascade[i + 1].suit) - CARD_SUIT.begin();
        if ((idx1 % 2 == idx2 % 2) || (cascade[i].value - cascade[i + 1].value != 1)) {
            return false;
        }
    }
    return true;
}
Cascade& Cascade::operator=(const Cascade& ref) {
    copy(ref.cascade.begin(), ref.cascade.end(), this->cascade.begin());
    this->occupied = ref.occupied;
    return *this;
}

Board::Board() { 
    int idx = 0;    // 인덱스로 활용하기 위한 변수
    int card_amount = CARD_NUMBER.size() * CARD_SUIT.size();
    // 52장의 카드 리스트 생성
    cards_list = vector<Card>(card_amount);
    for (int i = 0; i < CARD_SUIT.size(); i++) {
        for (int j = 0; j < CARD_NUMBER.size(); j++) {
            cards_list[idx++] = Card(j, i);
        }
    }
    // 0 ~ 51을 랜덤한 순서로 나열한 벡터 생성
    idx = 0;
    int randomNum;  // 랜덤 숫자 변수
    vector<int> cardOrder(card_amount, 0);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, card_amount); 
    while (idx < 52) {
        randomNum = dis(gen);
        if (find(cardOrder.begin(), cardOrder.end(), randomNum) == cardOrder.end()) {
            cardOrder[idx++] = randomNum;
        }
    }
    // 위에서 생성한 벡터를 바탕으로 그 벡터의 원소에 해당하는 cardOrder의 카드를 cascade에 배치함
    idx = 0;
    cascades = vector<Cascade>(CASCADE_INITIAL_LENGTH.size());
    for (int i = 0; i < cascades.size(); i++) { 
        cascades[i].occupied = CASCADE_INITIAL_LENGTH[i]; 
        for (int j = 0; j < CASCADE_INITIAL_LENGTH[i]; j++) { 
            cascades[i].cascade[j] = cards_list[cardOrder[idx++] - 1];
        }
    }
}
Board::Board(const Board& original) { 
    this->cards_list = vector<Card>(CARD_SUIT.size() * CARD_NUMBER.size());
    copy(original.cards_list.begin(), original.cards_list.end(), this->cards_list.begin());
    this->cascades = vector<Cascade>(CASCADE_INITIAL_LENGTH.size());
    for (int i = 0; i < cascades.size(); i++) {
        this->cascades[i] = Cascade(original.cascades[i]);
    }    
}
void Board::putCard(int to, Card card) {
    int toIdx = to - 1;
    this->cascades[toIdx].cascade.push_back(card);
    this->cascades[toIdx].occupied++;
}
Card Board::takeCard(int from) {
    int fromIdx = from - 1;
    Card tmp = cascades[fromIdx].cascade.back();
    cascades[fromIdx].cascade.pop_back();
    cascades[fromIdx].occupied--;
    return tmp;
}
void Board::moveCards(int amount, int from, int to) {
    int fromIdx = from - 1;
    int toIdx = to - 1;
    
    copy(cascades[fromIdx].cascade.begin() + (cascades[fromIdx].occupied - amount), cascades[fromIdx].cascade.begin() + cascades[fromIdx].occupied, cascades[toIdx].cascade.begin() + cascades[toIdx].occupied);
    
    for (int i = cascades[fromIdx].occupied - amount; i < cascades[fromIdx].occupied; i++) {
        cascades[fromIdx].cascade[i] = Card();
    }
    cascades[fromIdx].occupied -= amount;
    cascades[toIdx].occupied += amount;
}
void Board::showBoard() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        cout << "|";
        for (int j = 0; j < cascades.size(); j++) {
            if (j == 4) { 
                cout << " ";
            }
            if (cascades[j].cascade[i].value == 10) {
                cout << cascades[j].cascade[i].numStr << cascades[j].cascade[i].suit << " ";
            }
            else {
                cout << " " << cascades[j].cascade[i].numStr << cascades[j].cascade[i].suit << " ";
            }
        }
        cout << "| \n";
    }
}
bool Board::isAllOrdered() {
    for (int i = 0; i < cascades.size(); i++) {
        if (!cascades[i].checkOrder()) {
            return false;
        }
    }
    return true;
}
Board& Board::operator=(const Board& ref) {
    for (int i = 0; i < cascades.size(); i++) {
        this->cascades[i] = Cascade(ref.cascades[i]);
    }    
    return *this;
}

Game::Game() {
    this->freeCell = Cell(FREECELL_SIZE);
    this->homeCell = Cell(HOMECELL_SIZE);
    this->board = Board();
}
Game::Game(const Game& original) {
    this->freeCell = original.freeCell;
    this->homeCell = original.homeCell;
    this->board = original.board;
    }
void Game::putCell(char ch, int cellNum, Card card) {
    if (ch == 'f' && freeCell.getCell(cellNum).value == 0) {
        freeCell.putCell(cellNum, card);
    }
    else if (ch == 'h') {
        homeCell.putCell(cellNum, card);
    }
}
Card Game::getCell(char ch, int cellNum) {
    if (ch == 'f') {
        return freeCell.getCell(cellNum);
    }
    else if (ch == 'h') {
        return homeCell.getCell(cellNum);
    }
    return Card();
}
Card Game::takeCell(char ch, int cellNum) {
    if (ch == 'f') {
        return freeCell.takeCell(cellNum);
    }
    else if (ch == 'h') {
        return homeCell.takeCell(cellNum);
    }
    return Card();
}
void Game::showGame() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "-";
    }
    cout << "\n|";
    this->freeCell.showCell();
    cout << "|";
    this->homeCell.showCell();
    cout << "|\n";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "-";
    }
    cout << "\n";
    board.showBoard();
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "-";
    }
    cout << "\n";
}
bool Game::isMovable(vector<int> moveInfo) {
    // 1. 현재 움직일 수 있는 카드의 수 확인
    // 4. from의 전체 카드 수 > 옮길 카드 수
    // 5. to + 옮길 카드 수 <= BOARD_HEIGHT
    // 2. 옮기려는 카드의 연속성
    // 3. to의 suit, numstr과 옮기려는 카드의 suit, numStr
    bool movable = true;
    int movableCardNum = 0;
    






    return movable;
}
void Game::moveCards(vector<int> moveInfo) {
    
}
void Game::undoMove() {

}
bool Game::isAllOrdered() {
    return board.isAllOrdered();
}
void Game::autoMove() {

}
void Game::autoComplete() {

}
bool Game::isWin() {
    return homeCell.isWin();
}
Game& Game::operator=(const Game& ref) {
    this->freeCell = ref.freeCell;
    this->homeCell = ref.homeCell;
    this->board = ref.board;
    return *this;
}

