URL to video runthrough: https://photos.app.goo.gl/Um6jHu6VUS1v3wLA9

Logic explanation: 

The play() method sets up the initial game state, contains the game loop, 
and also the conclusion to the game. The board is a char[][]. It is initialized to
'.' chars in initializeBoard(board). Moves are stored in a char[] with 42 slots, as the
game board can only fit 42 pieces. The player who goes first is picked by the human player.
Trivial logic aside; a human player inputs their column with validation. Next, the piece is placed
in the first empty slot of the game board counting up from the bottom. This is part of the validation.
Next, their move is recorded in moves[turns]. Next, a didWin() check is performed on the spot the player 
chose to place their piece. 

Using logic borrowed from cpuPlay(), the didWin() checker will return true
if the slot has four in a row of their piece in any direction. I will explain the logic below.

cpuPlay is a more complex version of didWin(), in that cpuPlay rates plays based on how long the
longest single char chain is for each column on the game board using for loops. If there is a three-in-a-row, this slot
will be prioritized as it is either a winning or losing position. If not, a score is given between one and three
for a chain going in each direction, row-wise, column-wise, and diagonal 1 and 2. The sum of these four chains
is the final score for the column. The CPU places a chip on highest-scored column. Each column
is scored before every CPU play.

If didWin returns true, or there have been 42 turns, the game ends, and there is either a tie or a winner chosen based
on who last placed a piece.

