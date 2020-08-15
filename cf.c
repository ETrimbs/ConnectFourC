#include <stdio.h>
#include <stdlib.h>

void initializeBoard(char board[6][7]){
  for(int i=0; i<6; i++){
    for(int j=0;j<7;j++){
      board[i][j] = '.';
    }
  }
}

void toString(char board[6][7]){

  printf("\n   A B C D E F G");
    
  for(int i=0; i<6; i++){
    printf("\n%i  ", 6-i);
      for(int j=0;j<7;j++){
        printf( "%c ", board[i][j] );
      }
  }

  printf("\n");

}

void printMoves(char moves[42], int turns){
  for(int i=0; i<turns; i++){
    printf("%c", moves[i]);
  }
  printf("\n");
}

int charToCol(char character){
  switch(character){
    case('A'):
      return 0; 
    case('B'):
      return 1;
    case('C'):
      return 2;
    case('D'):
      return 3;
    case('E'):
      return 4;
    case('F'):
      return 5;
    case('G'):
      return 6;
  }
  return -1;
}

char colToChar(int col){
  switch(col){
    case(0):
      return 'A';
    case(1):
      return 'B'; 
    case(2):
      return 'C';
    case(3):
      return 'D';
    case(4):
      return 'E';
    case(5):
      return 'F';
    case(6):
      return 'G';
  }
  return 'Z';
}

//done
//board, valid column (0-6), piece ('X' or 'O')
//returns false if piece cannot be added
_Bool addPiece(char board[6][7], int col, char piece){
  if(col == -1){
    return 0;
  }

  int i = 5;

  while(i >= 0 && board[i][col] != '.'){
    i--;
  }
  
  if(i < 0){
    return 0;
  }

  board[i][col] = piece;
  return 1;
}

int push(char array[8], char c){
  int i = 0;
  while(array[i] != '\0'){
    ++i;
  }
  if(i < 7){
    array[i] = c;
    array[i+1] = '\0';
  }
  return i;
}

int analyse(char surroundings[8]){
  int counter = 0;
  int max = 0;

  for(int i = 0; i < 7; i++){
    counter = 0;

    if(surroundings[i] == 'X'){

      for(int j = i; j < 7; ++j, ++i){

        if(j != 3){
          if(surroundings[j] == 'X'){
            counter++;
          }
          else{
            --i;
            break;
          }
        }
      }

      if(counter >= 3) return 300;
      else if(counter == 2 && (i > 2 && i <= 5)) max = counter;
      else if(max < 1 && counter == 1 && (i == 1 || i == 3)) max = counter;
    }
    

    else if(surroundings[i] == 'O'){

      for(int j = i; j < 7; ++j, ++i){

        if(j != 3){
          if(surroundings[j] == 'O'){
            counter++;
          }
          else{
            --i;
            break;
          }
        }
      }

      if(counter >= 3) return 300;
      else if(counter == 2 && (i > 2 && i <= 5)) max = counter;
      else if(max < 1 && counter == 1 && (i == 1 || i == 3)) max = counter;
    }
  }

  return max;
}

int ratePoint(char board[6][7], int row, int col, char piece){

  char surroundings[8] = {'\0'};
  int rating = 0;

  //row
  for(int i = col - 3; i <= col + 3; ++i){
    if(i >= 0 && i < 7 && i != col ){
      push(surroundings, board[row][i]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);
  surroundings[0] = '\0';


  //column
  for(int i =  row + 3; i >= row - 3; --i){
    if(i >= 0 && i < 6 && i != row ){
      push(surroundings, board[i][col]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);
  surroundings[0] = '\0';


  //diagonal 1
  for(int i = -3; i <= 3; i++){
    if(i != 0 && row - i <= 5 && row - i >= 0 && col + i <= 6 && col + i >= 0){
      push(surroundings, board[row-i][col+i]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);
  surroundings[0] = '\0';


  //diagonal 2
  for(int i = -3; i <= 3; i++){
    if(i != 0 && row + i <= 5 && row + i >= 0 && col + i <= 6 && col + i >= 0){
      push(surroundings, board[row+i][col+i]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);

  return rating;
}

int ratePointForWin(char board[6][7], int row, int col, char piece){

  char surroundings[8] = {'\0'};
  int rating = 0;

  //row
  for(int i = col - 3; i <= col + 3; ++i){
    if(i >= 0 && i < 7 && i != col && board[row][i] == piece){
      push(surroundings, board[row][i]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);
  surroundings[0] = '\0';


  //column
  for(int i =  row + 3; i >= row - 3; --i){
    if(i >= 0 && i < 6 && i != row && board[i][col] == piece){
      push(surroundings, board[i][col]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);
  surroundings[0] = '\0';


  //diagonal 1
  for(int i = -3; i <= 3; i++){
    if(i != 0 && row - i <= 5 && row - i >= 0 && col + i <= 6 && col + i >= 0 && board[row-i][col+i] == piece){
      push(surroundings, board[row-i][col+i]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);
  surroundings[0] = '\0';


  //diagonal 2
  for(int i = -3; i <= 3; i++){
    if(i != 0 && row + i <= 5 && row + i >= 0 && col + i <= 6 && col + i >= 0 && board[row+i][col+i] == piece){
      push(surroundings, board[row+i][col+i]);
    }
    else{
      push(surroundings, '-');
    }
  }

  rating += analyse(surroundings);

  return rating;
}




_Bool didWin(char board[6][7], int col, char piece){
  int j = 5;
    while(j >= 0 && board[j][col] != '.'){
      j--;
    }

  if(ratePointForWin(board, j+1, col, piece) > 20) return 1;
  return 0;
}

int playCPU(char board[6][7], char piece){
  int scores[7] = {0,0,0,0,0,0,0};
  
  for(int i = 0; i < 7; ++i){ //find the empty slot, rate the placement
    int j = 5;
    while(j >= 0 && board[j][i] != '.'){
      j--;
    }

    if(j >= 0){
      scores[i] = ratePoint(board, j, i, piece);
    } else scores[i] = -1;
  }

  int highScore = -1;
  int col = -1;

  for(int i = 0; i < 7; i++){
    if(scores[i] > highScore){
      highScore = scores[i];
      col = i;
    }
  }
  if(highScore == 0){
    addPiece(board, 3, piece);
    return colToChar(3);
  }

  addPiece(board, col, piece);
  return colToChar(col);
}

void play(){
  char board[6][7];
  initializeBoard(board);
  int active;
  char moves[42];
  int turns = 0;

  char character = 'Z';
  int col;

  printf("\nInstructions: \nChoose who will go first. Then, to play a piece, type the letter, 'A' through 'G', corresponding to\nwhich column you would like to place your chip in on your turn.\n\n");

  while(character != 'M' && character != 'C'){
    printf("Who is going first? Type 'M' for me and 'C' for the computer player.\n");
    scanf (" %c", &character);
  }

  active = (character == 'M' ? 0:1);

  toString(board);

  _Bool flag;
  char piece;

  while(turns < 42){

    flag = 0;
    if((active % 2) == 0){ //human //active ++ after every turn even = human odd = cpu

      while(!flag){
        printf("What is your move? (Enter 'A' through 'G' corresponding to the desired column.\n");
        scanf(" %c", &character);
        col = charToCol(character);
        piece = (turns % 2 == 0? 'X': 'O');
        flag = addPiece(board, col, piece);
      }
      moves[turns] = character;
      if(didWin(board, col, piece)) break;
    } 
    else{ //cpu
      piece = turns % 2 == 0? 'X': 'O';
      char move = playCPU(board, piece);
      col = charToCol(move);
      moves[turns] = move;
      printf("Computer player places a chip in column %c.\n", moves[turns]);
      if(didWin(board, col, piece)) break;
    }

    toString(board);
    active++;
    turns++;
  }


  if(turns >= 42){
      printf("Tie; nobody wins! :(\n");
  }
  if((active % 2) == 0){
      printf("Game over; you win!\n");
  } else{
      printf("Game over; computer wins!\n");
  }

  toString(board);

  printf("Move history: \n");
  printMoves(moves, turns);
}


int main(){
  play();
}