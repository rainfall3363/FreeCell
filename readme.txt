# Please adjust your terminal or prompt size before start the game.
# Each game is randomly generated, therefore the exact same game might will never be played again.
# If you wins the game, moving card commands will be disabled.
# There may be games that cannot be won.


*** Command List ***
1. "new"
   - Generate new game

2. "restart"
   - Restart present game from beginning

3. "exit"
   - Exit program

4. "undo"
   - Undo last move

5. "From To", "From To Amount"
   - Move cards
   - You can enter amount only when moving cards between cascades
   - If skip enter amount, It will automatically set
   - From: 1~8 f1~f4, To: 1~8 f h, Amount: (blank) 1~20
   - ex) 1 8 3 / 3 f / 2 h / f1 4 / f1 h


How to play
   - The goal of the game is to raise all of the cascade's cards 
     to the top home cell using four free cells.
   - Home cell's foundations are built up by suit. The Foundations 
     begin with Ace and are built up to King.
   - The number of cards that can be moved at once is number of empty cell in free cell + 1,
     and if there is an empty cascade, it can be increased further.
   - Tableaux must be built down by alternating colors.
   - The game is won after all cards are moved to their foundation piles in home cell.

플레이 방법
   - 카드를 놓는 방법
   :카드를 이동 시킬 땐 서로 색이 다른 문양을 가지고 있고, 숫자가 자신보다 딱 하나 더 큰 카드 위에만 놓을 수 있습니다.
   - 연속된 카드
   :위의 방법으로 정렬된 카드는 묶어서 한 번에 이동시킬 수 있습니다.
   - 이동 가능 카드 장 수
   :한 번에 이동시킬 수 있는 카드의 장 수는 프리셀의 빈 칸 + 1장이며, 이동하려는 라인 이외의 빈 라인이
    존재한다면 더 많은 카드를 이동시킬 수 있습니다.
   - 플레이 팁
   :홈셀에 모든 카드를 올리는 것이 목적이기 때문에, 작은 수의 카드부터 찾아야 합니다.
   :연속된 카드 뭉치를 만들고, 필요없는 카드는 프리셀로 올리고 낮은 수의 카드는 홈셀로 올리는 플레이를 반복하면
    승리할 수 있습니다.
   :프리셀로 올리는 카드가 많아질수록 움직일 수 있는 카드의 장 수가 줄어드니 전략을 잘 세워야 합니다.


전체 코드
- https://github.com/rainfall3363/FreeCell

기타 정보
- http://solitairelaboratory.com/fcfaq.html

참고 자료
- https://en.wikipedia.org/wiki/FreeCell
- https://modoocode.com/304
- https://jhnyang.tistory.com/303
