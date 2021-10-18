#include "FreeCell_game.h"

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

}
Card Board::takeCard(int from) {
    Card tmp = cascade

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
bool Game::isMovable(vector<string> moveInfo) {
    // 1. 현재 움직일 수 있는 카드의 수 확인
    // 4. from의 전체 카드 수 > 옮길 카드 수
    // 5. to + 옮길 카드 수 <= BOARD_HEIGHT
    // 2. 옮기려는 카드의 연속성
    // 3. to의 suit, numstr과 옮기려는 카드의 suit, numStr
    bool movable = true;
    int movableCardNum = 0;
    






    return movable;
}
void Game::moveCards(vector<string> moveInfo) {
    
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


Shell::Shell() {
    this->command = "";
    moveInfo = vector<int>();
}
void Shell::enterCommand() {
    cout << ">> ";
    getline(cin, this->command);
}
string Shell::processCommand(string mode) {
	// command tokenize 커맨드를 띄어쓰기 기준으로 찢음
    stringstream ss(command);
    vector<string> commandTokens;
    string token;
    while (getline(ss, token, ' ')) {
		commandTokens.push_back(token);
	}
    /////////////////////////////////////////
    // command를 쪼개서 현재 mode에 따라서 다음 mode를 정의함
    if (commandTokens.size() == 0) {
        ;
    }
    else if (commandTokens.size() == 1) {
        // new, restart, exit, undo 확인
        // 확인되면 맞는 mode 적용 we, wr, we, wu
        if (mode[0] == 'w') {
            if (!(commandTokens[0].compare("Y")) || !(commandTokens[0].compare("y"))) {
                // w 만 뗌
                mode = mode.substr(1, 1);
            }
            else if (!(commandTokens[0].compare("N")) || !(commandTokens[0].compare("n"))) {
                mode = "d";
            }
            else {
                mode = "uc";
            }
        }
        else {
            if (!(commandTokens[0].compare("new"))) {
                mode = "wn";
            }
            else if (!(commandTokens[0].compare("restart"))) {
                mode = "wr";
            }
            else if (!(commandTokens[0].compare("undo"))) {
                mode = "wu";
            }
            else if (!(commandTokens[0].compare("exit"))) {
                mode = "we";
            }
            else {
                mode = "uc";
            }
        }
    }
    else if (commandTokens.size() == 2) {
        // from, to 유효성 확인
        // 숫자만 있다면 amount 1 자동 적용
        // from:    commandTokens[0] - 1~8 / f1~f4
        // to:      commandTokens[1] - 1~8 / f1~f4 / h1~h4 
        // amount:  commandTokens[2] - 1 직접 더하기
        



    }
    else if (commandTokens.size() == 3) {
        // from, to, amount 유효성 확인
        // from:    commandTokens[0] - 1~8 / f1~f4
        // to:      commandTokens[1] - 1~8 / f1~f4 / h1~h4 
        // amount:  commandTokens[2] - 1 ~ BOARD_HEIGHT / f, h rk 가 있을 때 1 이외의 숫자면 x

        

    }
    else {
        mode = "uc";
    }

    
    
}
void Shell::printMessage(string mode) {
    vector<string> ordinal = {"1st line", "2nd line", "3rd line", "4th line", "5th line", "6th line", "7th line", "8th line", "FreeCell", "HomeCell"};
    if (!mode.compare("d")) {
            cout << "Make your move\n";
    }
    else if (!mode.compare("wn")) {
        cout << "Do you want to start new game? (Y/N)\n";    
    }
    else if (!mode.compare("wr")) {
        cout << "Do you want to restart the game? (Y/N)\n";    
    }
    else if (!mode.compare("wa")) {
        cout << "Automatic completion is available. Do you want to activate it? (Y/N)\n"; 
    }
    else if (!mode.compare("we")) {
        cout << "Do you want to quit the game? (Y/N)\n";    
    }
    else if (!mode.compare("m")) {
        
        cout << moveInfo[0] << " cards moved from " << ordinal[moveInfo[1] - 1] << " to " << ordinal[moveInfo[2] - 1] << "\n"; 
    }
    else if (!mode.compare("ud")) {
        cout << "Undo completed\n"; 
    }
    else if (!mode.compare("um")) {
        cout << "※※※ Can't move that way! ※※※\n"; 
    }
    else if (!mode.compare("uc")) {
        cout << "※※※ Unvalid command! ※※※\n";
    }
    else if (!mode.compare("v")) {
        cout << "VICTORY!!!\n";    
    }
}

vector<string> Shell::getMoveInfo() {

}