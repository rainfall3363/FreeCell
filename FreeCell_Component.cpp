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
bool Card::canMoveCard(Card card) {
    int num1 = find(CARD_SUIT.begin(), CARD_SUIT.end(), this->suit) - CARD_SUIT.begin();
    int num2 = find(CARD_SUIT.begin(), CARD_SUIT.end(), card.suit) - CARD_SUIT.begin();
    if ((num1 % 2 == num2 % 2) || this->value - card.value != 1) {
        return false;
    }
    return true;
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
    this->cell_cards[cellNum - 1] = card;    
}
Card Cell::getCell(int cellNum) {
    return this->cell_cards[cellNum - 1];
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
bool Cascade::isOrdered(int amount) {
    if (amount == 0) {
        amount = occupied;
    }
    if (occupied < amount) {
        return false;
    }
    for (int i = occupied - amount; i < occupied - 1; i++) {
        int num1 = find(CARD_SUIT.begin(), CARD_SUIT.end(), cascade[i].suit) - CARD_SUIT.begin();
        int num2 = find(CARD_SUIT.begin(), CARD_SUIT.end(), cascade[i + 1].suit) - CARD_SUIT.begin();
        if ((num1 % 2 == num2 % 2) || (cascade[i].value - cascade[i + 1].value != 1)) {
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
    vector<Card> cards_list(card_amount);
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
    this->cascades = vector<Cascade>(CASCADE_INITIAL_LENGTH.size());
    for (int i = 0; i < cascades.size(); i++) {
        this->cascades[i] = Cascade(original.cascades[i]);
    }    
}
int Board::getOccupied(int cascadeNum) {
    return cascades[cascadeNum - 1].occupied;
}
void Board::putCard(int to, Card card) {
    int toIdx = to - 1;
    cascades[toIdx].cascade[cascades[toIdx].occupied++] = card;
}
Card Board::getCard(int cascadeNum, int reverseIdx) {
    if (reverseIdx == -1) {
        reverseIdx = cascades[cascadeNum - 1].occupied - 1;
    }
    else {
        reverseIdx = cascades[cascadeNum - 1].occupied - reverseIdx;
    }
    return cascades[cascadeNum - 1].cascade[reverseIdx];
}
Card Board::takeCard(int from) {
    int fromIdx = from - 1;
    Card tmp = cascades[fromIdx].cascade[--cascades[fromIdx].occupied];
    cascades[fromIdx].cascade[cascades[fromIdx].occupied] = Card();
    return tmp;
}
void Board::moveCards(int from, int to, int amount) {
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
        if (i + 1 < 10) {
            cout << " " << i + 1;
        }
        else {
            cout << i + 1;
        }
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
        cout << "|";
        if (i + 1 < 10) {
            cout << " " << i + 1 << "    ";
            if (i == 0) {

            }
            else if (i == 1) {
                cout << "# Please adjust window size to fit the game";
            }
            else if (i == 2) {
                cout << "# There are games that cannot be won";
            }
            else if (i == 3) {
                cout << "# Automatic completion is not available yet";
            }
            else if (i == 4) {
                cout << "# Bug report to rainfall3363@gmail.com";
            }
            else if (i == 5) {

            }
            else if (i == 6) {
            }
            else if (i == 7) {
                cout << "*** Command List ***";
            }
            else if (i == 8) {
                cout << "1. \"new\"";
            }
            cout << '\n';
        }
        else {
            cout << i + 1 << "    ";
            if (i == 9) {
                cout << "   - Generate new game";
            }
            else if (i == 10) {
                cout << "2. \"restart\"";
            }
            else if (i == 11) {
                cout << "   - Restart present game from beginning";
            }
            else if (i == 12) {
                cout << "3. \"exit\"";
            }
            else if (i == 13) {
                cout << "   - Exit program";
            }
            else if (i == 14) {
                cout << "4. \"undo\"";
            }
            else if (i == 15) {
                cout << "   - Undo last move";
            }
            else if (i == 16) {
                cout << "5. \"From To\", \"From To Amount\"";
            } 
            else if (i == 17) {
                cout << "   - Move cards";
            } 
            else if (i == 18) {
                cout << "   - If skip enter amount, automatically set as 1";
            }
            else if (i == 19) {
                cout << "   e.g. 1 8 3 / f3 h1 / f1 4 / 3 h4 / f1 h3";
            }
            cout << '\n';
        }
        // 여기에 붙여서 
        // if (i == 3) { ~ }
        // if (i == 4) { ~ }
        // 도움말 작성하기
    }
}
bool Board::isOrdered(int cascadeNum, int amount) {
    return cascades[cascadeNum - 1].isOrdered(amount);
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
    this->moveLog = vector<vector<int>>(original.moveLog.size(), vector<int>());
    for (int i = 0; i < original.moveLog.size(); i++) {
        this->moveLog[i] = original.moveLog[i];
    }
}
void Game::showGame() {
    cout << "   ";
    for (int i = 0; i < FREECELL_SIZE; i++) {
        cout << " f" << i + 1 << " ";
    }
    cout << " ";
    for (int i = 0; i < HOMECELL_SIZE; i++) {
        cout << " h" << i + 1 << " ";
    }
    cout << "       How to play\n   ";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "-";
    }
    cout << "       :Raise all of the cascade's cards to the top\n  |";
    this->freeCell.showCell();
    cout << "|";
    this->homeCell.showCell();
    cout << "|       home cell by using four free cells\n  |";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "-";
    }
    cout << "|\n";
    board.showBoard();
    cout << "   ";
    for (int i = 0; i < BOARD_WIDTH; i++) {
        cout << "-";
    }
    cout << "\n   ";
    for (int i = 1; i <= 4; i++) {
        cout << "  " << i << " ";
    }
    cout << " ";
    for (int i = 5; i <= 8; i++) {
        cout << "  " << i << " ";
    }
    cout << "\n\n";
}
bool Game::canMoveCards(vector<int> moveInfo) {
    // moveInfo의 입력 값에 따라 경우의 수를 나눔
    // 카드의 갯수 부터 비교 후, 유효성 판단 순으로 진행 (단순 -> 복잡)

    
    // to의 suit, numstr과 옮기려는 카드의 suit, numStr
    // 카드 갯수 비교 옮기는 수, from to
    bool result = true;
    int movableCard = 0;
    
    if (moveInfo[0] == moveInfo[1]) {
        result = false;
    }
    // from Board
    else if (moveInfo[0] > 0 && moveInfo[0] < 9) {
        // To Board
        if (moveInfo[1] > 0 && moveInfo[1] < 9) { 
            if (board.getOccupied(moveInfo[0]) < moveInfo[2]) {
                result = false;
            }
            else if (board.getOccupied(moveInfo[1]) + moveInfo[2] > BOARD_HEIGHT) {
                result = false;
            }
            else if (!board.isOrdered(moveInfo[0], moveInfo[2])) {
                result = false;
            }
            else if (board.getCard(moveInfo[1]).value != 0 && !(board.getCard(moveInfo[1]).canMoveCard(board.getCard(moveInfo[0], moveInfo[2])))) {
                // 빈 줄에는 걍 올릴 수 있음
                result = false;
            }
            // movableCard 갯수 공식 사용해야함
        }
        // To FreeCell
        else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
            
        }
        // To HomeCell
        else if (moveInfo[1] > 20 && moveInfo[1] < 25) {
            
        }
    }
    // From FreeCell
    else if (moveInfo[0] > 10 && moveInfo[0] < 15) {
        // To Board
        if (moveInfo[1] > 0 && moveInfo[1] < 9) {
              
        }
        // To FreeCell
        else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
            
        }
        // To HomeCell
        else if (moveInfo[1] > 20 && moveInfo[1] < 25) {
            
        }
    }
    
    







    





    return result;
}
void Game::moveCards(vector<int> moveInfo, bool isUndo) {
    // From Board
    if (moveInfo[0] > 0 && moveInfo[0] < 9) {
        // To Board
        if (moveInfo[1] > 0 && moveInfo[1] < 9) {
            board.moveCards(moveInfo[0], moveInfo[1], moveInfo[2]);
        }
        // To FreeCell
        else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
            freeCell.putCell(moveInfo[1] - 10, board.takeCard(moveInfo[0]));
        }
        // To HomeCell
        else if (moveInfo[1] > 20 && moveInfo[1] < 25) {
            homeCell.putCell(moveInfo[1] - 20, board.takeCard(moveInfo[0]));
        }
    }
    // From FreeCell
    else if (moveInfo[0] > 10 && moveInfo[0] < 15) {
        // To Board
        if (moveInfo[1] > 0 && moveInfo[1] < 9) {
            board.putCard(moveInfo[1], freeCell.takeCell(moveInfo[0] - 10));    
        }
        // To FreeCell
        else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
            freeCell.putCell(moveInfo[1] - 10, freeCell.takeCell(moveInfo[0] - 10));
        }
        // To HomeCell
        else if (moveInfo[1] > 20 && moveInfo[1] < 25) {
            homeCell.putCell(moveInfo[1] - 20, freeCell.takeCell(moveInfo[0] - 10));
        }
    }
    // From HomeCell - for undo
    else if (moveInfo[0] > 20 && moveInfo[0] < 25) {
        // To Board
        if (moveInfo[1] > 0 && moveInfo[1] < 9) {
            board.putCard(moveInfo[1], homeCell.takeCell(moveInfo[0] - 20));
        }
        // To FreeCell
        else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
            board.putCard(moveInfo[1], freeCell.takeCell(moveInfo[0] - 10));
        }
    }
    if (!isUndo) {
        moveLog.push_back(moveInfo);
    }
}
bool Game::canUndoMove() {
    if (moveLog.size() == 0) {
        return false;
    }
    return true;
}
void Game::undoMove() {
    vector<int> reversedMove(3, 0);
    reversedMove[0] = moveLog.back()[1];
    reversedMove[1] = moveLog.back()[0];
    reversedMove[2] = moveLog.back()[2];
    
    moveCards(reversedMove, true);
    moveLog.pop_back();
}
bool Game::canAutoMove() {
    return false;
}
void Game::autoMove() {

}
bool Game::canAutoComplete() {
    for (int i = 0; i < CASCADE_INITIAL_LENGTH.size(); i++) {
        if (!board.isOrdered(i + 1)) {
            return false;
        }
    }
    return true;
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
    this->moveLog = vector<vector<int>>(ref.moveLog.size(), vector<int>());
    for (int i = 0; i < ref.moveLog.size(); i++) {
        this->moveLog[i] = ref.moveLog[i];
    }
    return *this;
}

