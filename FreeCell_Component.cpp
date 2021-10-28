#include "FreeCell_Component.h"

const vector<string> CARD_SUIT = {"-", "♠", "♣", "♡", "◇"};
const vector<string> CARD_NUMBER = {"-", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

Card::Card() {
    this->numIdx = 0;
    this->suitIdx = 0;
    this->color = 0;
}
Card::Card(int numIdx, int suitIdx) {
    this->numIdx = numIdx;
    this->suitIdx = suitIdx;
    if (suitIdx > 0 && suitIdx < 3) {
        this->color = BLACK;
    }
    else if (suitIdx > 2 && suitIdx < 5) {
        this->color = RED;
    }
    else {
        this->color = 0;
    }
}
Card::Card(const Card& original) {
    this->numIdx = original.numIdx;
    this->suitIdx = original.suitIdx;
    this->color = original.color;
}
bool Card::canMoveCard(Card card) {
    if (card.numIdx == 0) {
        return false;
    }
    else if (this->numIdx == 0) {
        return true;
    }
    else if (this->numIdx - card.numIdx == 1 && this->color != card.color) {
        return true;
    }
    else {
        return false;
    }
}
Card& Card::operator=(const Card& ref) {
    this->numIdx = ref.numIdx;
    this->suitIdx = ref.suitIdx;
    this->color = ref.color;
    return *this;
}

Cell::Cell() {
    this->cell_cards = vector<Card>();
}
Cell::Cell(int cellSize) {
    if (cellSize == 0) {
        this->cell_cards = vector<Card>();  
    }
    else {
        this->cell_cards = vector<Card>(cellSize);
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
    Card take = cell_cards[cellNum - 1];
    cell_cards[cellNum - 1] = Card();
    return take;
}
void Cell::showCell() {
    for (int i = 0; i < cell_cards.size(); i++) {
        if (cell_cards[i].numIdx == 10) {
            cout << CARD_NUMBER[cell_cards[i].numIdx] << CARD_SUIT[cell_cards[i].suitIdx] << " ";
        }
        else {
            cout << " " << CARD_NUMBER[cell_cards[i].numIdx] << CARD_SUIT[cell_cards[i].suitIdx] << " ";
        }
    }
}
bool Cell::isWin() {
    for (int i = 0; i < cell_cards.size(); i++) {
        if (cell_cards[i].numIdx != 13) {
            return false;
        }
    }
    return true;
}
Cell& Cell::operator=(const Cell& ref) {
    if (ref.cell_cards.size() == 0) {
        this->cell_cards = vector<Card>();
    }
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
    this->cascade = vector<Card>(original.cascade.size());
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
        if (!cascade[i].canMoveCard(cascade[i + 1])) {
            return false;
        }
    }
    return true;
}
Cascade& Cascade::operator=(const Cascade& ref) {
    this->cascade = vector<Card>(ref.cascade.size());
    copy(ref.cascade.begin(), ref.cascade.end(), this->cascade.begin());
    this->occupied = ref.occupied;
    return *this;
}

Board::Board() {
    int cardOrderIdx;
    int randomNum;  // 랜덤 숫자 변수
    int suitIdx;
    int numberIdx;
    vector<int> card_order(CARD_AMOUNT, 0);
    // 랜덤 보드 생성 파트
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, CARD_AMOUNT); 
    
    cardOrderIdx = 0;
    while (cardOrderIdx < 52) {
        randomNum = dis(gen);
        if (find(card_order.begin(), card_order.end(), randomNum) == card_order.end()) {
            card_order[cardOrderIdx++] = randomNum;
        }
    }
    // 위에서 생성한 벡터를 바탕으로 cascade에 card를 생성
    cardOrderIdx = 0;
    vector<int> cascade_length = {7, 7, 7, 7, 6, 6, 6, 6};
    cascades = vector<Cascade>(CASCADES_SIZE);
    for (int i = 0; i < cascades.size(); i++) { 
        cascades[i].occupied = cascade_length[i]; 
        for (int j = 0; j < cascades[i].occupied; j++) {
            numberIdx = card_order[cardOrderIdx] % (CARD_NUMBER.size() - 1);
            suitIdx = card_order[cardOrderIdx] / (CARD_NUMBER.size() - 1) + 1;
            if (numberIdx == 0) {
                cascades[i].cascade[j] = Card(CARD_NUMBER.size() - 1, suitIdx - 1);
            }
            else {
                cascades[i].cascade[j] = Card(numberIdx, suitIdx);    
            }
            cardOrderIdx++;
        }
    }
}
Board::Board(const Board& original) { 
    this->cascades = vector<Cascade>(CASCADES_SIZE);
    copy(original.cascades.begin(), original.cascades.end(), this->cascades.begin());
}
int Board::getOccupied(int cascadeNum) {
    return cascades[cascadeNum - 1].occupied;
}
void Board::putCard(int to, Card card) {
    cascades[to - 1].cascade[cascades[to - 1].occupied++] = card;
}
Card Board::getCard(int cascadeNum, int fromBack) {
    if (cascades[cascadeNum - 1].occupied == 0) {
        return cascades[cascadeNum - 1].cascade[0];
    }
    else {
        return cascades[cascadeNum - 1].cascade[cascades[cascadeNum - 1].occupied - fromBack];
    }
}
Card Board::takeCard(int from) {
    Card take = cascades[from - 1].cascade[--cascades[from - 1].occupied];
    cascades[from - 1].cascade[cascades[from - 1].occupied] = Card();
    return take;
}
void Board::moveCards(int from, int to, int amount) {
    copy(cascades[from - 1].cascade.begin() + (cascades[from - 1].occupied - amount), cascades[from - 1].cascade.begin() + cascades[from - 1].occupied, cascades[to - 1].cascade.begin() + cascades[to - 1].occupied);
    
    for (int i = cascades[from - 1].occupied - amount; i < cascades[from - 1].occupied; i++) {
        cascades[from - 1].cascade[i] = Card();
    }
    cascades[from - 1].occupied -= amount;
    cascades[to - 1].occupied += amount;
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
                cout << " ";    // 프리셀, 홈셀과 맞추기 위해 한칸 공백 삽입
            }
            if (cascades[j].cascade[i].numIdx == 10) {
                cout << CARD_NUMBER[cascades[j].cascade[i].numIdx] << CARD_SUIT[cascades[j].cascade[i].suitIdx] << " ";
            }
            else {
                cout << " " << CARD_NUMBER[cascades[j].cascade[i].numIdx] << CARD_SUIT[cascades[j].cascade[i].suitIdx] << " ";
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
    }
}
bool Board::isOrdered(int cascadeNum, int amount) {
    return cascades[cascadeNum - 1].isOrdered(amount);
}
Board& Board::operator=(const Board& ref) {
    this->cascades = vector<Cascade>(CASCADES_SIZE);
    copy(ref.cascades.begin(), ref.cascades.end(), this->cascades.begin());
    return *this;
}

Game::Game() {
    this->freeCell = Cell(FREECELL_SIZE);
    this->homeCell = Cell(HOMECELL_SIZE);
    this->board = Board();
    this->moveInfo = vector<int>(4, 0);
}
Game::Game(const Game& original) {
    this->freeCell = original.freeCell;
    this->homeCell = original.homeCell;
    this->board = original.board;
    this->moveInfo = original.moveInfo;
    if (original.moveLog.size() != 0) {
        this->moveLog = vector<vector<int>>(original.moveLog.size(), vector<int>());
        copy(original.moveLog.begin(), original.moveLog.end(), this->moveLog.begin());
    }
}
vector<int> Game::getMoveInfo() {
    return moveInfo;
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
bool Game::canMoveCards(vector<int> moveInput, string& status) {
    bool result = false;
    int repeatCnt = 0;
    int emptyCell = 0;
    int emptyCascade = 0;
    this->moveInfo = moveInput;
    
    for (int i = 0; i < FREECELL_SIZE; i++) {
        if (freeCell.getCell(i + 1).numIdx == 0) {
            emptyCell++;
        }
    }
    for (int i = 0; i < CASCADES_SIZE; i++) {
        if (board.getCard(i + 1).numIdx == 0 && ((i + 1) != moveInfo[1])) {
            emptyCascade++;
        }
    } 
    moveInfo[3] = (emptyCell + 1) * (emptyCascade + 1);

    // 이동 카드 수가 -1 이라면, 자동으로 이동 카드 수 재설정
    if (moveInfo[2] == -1) {
        // 이동 가능한 수 최대 값부터 차례대로 전부 유효성 판단 실행
        moveInfo[2] = board.getOccupied(moveInfo[0]);
        if (moveInfo[2] == 0) {
            status = "eec";
        }
        repeatCnt = moveInfo[2];
    }
    else {
        // 이동 카드 수가 정상적이라면 유효성 판단 한 번만 실행
        repeatCnt = 1;
    }

    while (repeatCnt > 0) {
        if (moveInfo[0] == moveInfo[1]) {
            status = "ems";  // error move to self
        }
        // From Board
        else if (moveInfo[0] > 0 && moveInfo[0] < 9) {
            // To Board
            if (board.getOccupied(moveInfo[0]) < moveInfo[2]) {
                    status = "eec";      // error not enough cards
            }
            else if (moveInfo[1] > 0 && moveInfo[1] < 9) { 
                // From의 카드 수 >= 옮길 카드 수
                if (!status.compare("fm")) {
                    result = true;
                    break;
                }
                // 옮길 수 있는 카드 수 >= 옮길 카드 수
                else if (moveInfo[3] < moveInfo[2]) {
                    status = "eef";     // error not enough freecell
                    if (board.isOrdered(moveInfo[0], moveInfo[2])) {
                        // 자동으로 갯수 설정 시 연속된 카드 나오면 정지
                        break;
                    }
                }
                // 옮기려는 카드의 연속성
                else if (!board.isOrdered(moveInfo[0], moveInfo[2])) {
                    status = "eno";     // error not in order
                }
                // From의 맨 윗장과 To의 맨 아랫장의 연속성 
                else if (!board.getCard(moveInfo[1]).canMoveCard(board.getCard(moveInfo[0], moveInfo[2])) && board.getCard(moveInfo[1]).numIdx != 0) {
                    status = "ewm";
                }
                else {
                    result = true;
                    break;
                }
            }
            // To FreeCell
            else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
                // FreeCell이 비어 있는지 확인
                if (freeCell.getCell(moveInfo[1] - 10).numIdx != 0) {
                    status = "ene";     // error not empty
                }
                else if (board.getCard(moveInfo[0]).numIdx == 0) {
                    status = "eec";
                }
                else {
                    result = true;
                    break;
                }
            }
            // To HomeCell
            else if (moveInfo[1] > 20 && moveInfo[1] < 25) {
                // HomeCell이 비어 있으면 Ace만 이동 가능
                if (homeCell.getCell(moveInfo[1] - 20).numIdx == 0 && board.getCard(moveInfo[0]).numIdx == 1) {
                    result = true;
                    break;
                }
                // 카드의 suit가 일치하고 숫자가 하나 더 큰 숫자가 들어가는지 확인
                else if (homeCell.getCell(moveInfo[1] - 20).numIdx == board.getCard(moveInfo[0]).numIdx - 1 && homeCell.getCell(moveInfo[1] - 20).suitIdx == board.getCard(moveInfo[0]).suitIdx) {
                    result = true;
                    break;
                }
                else if (!status.compare("fm")) {
                    result = true;
                    break;
                }
            }
        }
        // From FreeCell
        else if (moveInfo[0] > 10 && moveInfo[0] < 15) {
            // From FreeCell의 카드 존재 여부
            if (freeCell.getCell(moveInfo[0] - 10).numIdx == 0) {
                status = "eec";
            }
            // To Board
            else if (moveInfo[1] > 0 && moveInfo[1] < 9) {
                // To가 비어 있지 않은데, To에 canCardMove가 false면 불가능 (canMoveCard에서 비어 있는 거 알아서 확인해 줌)
                if (board.getCard(moveInfo[1]).canMoveCard(freeCell.getCell(moveInfo[0] - 10))) {
                    result = true;
                    break;
                }
                else if (!status.compare("fm")) {
                    result = true;
                    break;
                }
            }
            // To FreeCell
            else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
                // To가 비어 있는지
                if (freeCell.getCell(moveInfo[1] - 10).numIdx != 0) {
                    status = "ene";
                }
                else {
                    result = true;
                    break;
                }
            }
            // To HomeCell
            else if (moveInfo[1] > 20 && moveInfo[1] < 25) {
                // HomeCell이 비어 있으면 A 인지
                if (homeCell.getCell(moveInfo[1] - 20).numIdx == 0 && freeCell.getCell(moveInfo[0] - 10).numIdx == 1) {
                    result = true;
                    break;
                }
                // 카드의 suit가 일치하고 숫자가 하나 더 큰 숫자가 들어가는지 확인
                else if (homeCell.getCell(moveInfo[1] - 20).numIdx == freeCell.getCell(moveInfo[0] - 10).numIdx - 1 && homeCell.getCell(moveInfo[1] - 20).suitIdx == freeCell.getCell(moveInfo[0] - 10).suitIdx) {
                    result = true;
                    break;
                }
                else if (!status.compare("fm")) {
                    result = true;
                    break;
                }
            }
        }
        // From HomeCell
        else if (moveInfo[0] > 20 && moveInfo[0] < 25) {
            if (status.compare("fm")) {
                status = "ehm";
            }
            else if (homeCell.getCell(moveInfo[0] - 20).numIdx == 0) {
                status = "eec";
            }
            else {
                result = true;
            }
            break;
        }

        repeatCnt--;
        moveInfo[2]--;
    }

    if (result == false && status[0] != 'e') {
        status = "ewm";
    }
    else if (result == true) {
        status = "m";
    }

    return result;
}
void Game::moveCards(bool isUndo) {
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
    // From HomeCell - for undo, forceMove
    else if (moveInfo[0] > 20 && moveInfo[0] < 25) {
        // To Board
        if (moveInfo[1] > 0 && moveInfo[1] < 9) {
            board.putCard(moveInfo[1], homeCell.takeCell(moveInfo[0] - 20));
        }
        // To FreeCell
        else if (moveInfo[1] > 10 && moveInfo[1] < 15) {
            freeCell.putCell(moveInfo[1] - 10, homeCell.takeCell(moveInfo[0] - 20));
        }
    }
    if (!isUndo) {
        // undo를 실행할 때는 로그에 넣지 않음
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
    Card spaceBehindTheWall;
    moveInfo[0] = moveLog.back()[1];
    moveInfo[1] = moveLog.back()[0];
    moveInfo[2] = moveLog.back()[2];
    // homeCell에서 이동하면 1작은 카드 생성
    if (moveInfo[0] > 20 && moveInfo[0] < 25) {
        if (homeCell.getCell(moveInfo[0] - 20).numIdx != 1) {
            spaceBehindTheWall = Card(homeCell.getCell(moveInfo[0] - 20));
            spaceBehindTheWall.numIdx--;
        }
    }
    moveCards(true);
    moveLog.pop_back();
    homeCell.putCell(moveInfo[0] - 20, spaceBehindTheWall);
}
bool Game::canAutoMove() {
    return false;
}
void Game::autoMove() {

}
bool Game::canAutoComplete() {
    for (int i = 0; i < CASCADES_SIZE; i++) {
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
    this->moveInfo = ref.moveInfo;
    if (ref.moveLog.size() != 0) {
        this->moveLog = vector<vector<int>>(ref.moveLog.size(), vector<int>());
        copy(ref.moveLog.begin(), ref.moveLog.end(), this->moveLog.begin());
    }
    return *this;
}

void Game::showCard(int cascadeNum) {
    cout << cascadeNum << "번 캐스케이드\n";
    cout << "numIdx: " << board.getCard(cascadeNum).numIdx << '\n';
    cout << "suitIdx: " << board.getCard(cascadeNum).suitIdx << '\n';
    cout << "color: " << board.getCard(cascadeNum).color << '\n';
    sleep(3);
}