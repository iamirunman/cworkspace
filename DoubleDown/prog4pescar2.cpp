/* prog4DoubleDown.cpp
      Play a game similar to Quarto, except we only have 2 different types of pieces.
 
 Author: Pablo Escarcega

 Running the program (for a couple of moves only) looks like the following:
 
     Author: Pablo Escarcega
     Program: #4, DoubleDown
     
     Welcome to the game of DoubleDown, where you try to complete a set
     of four pieces that are alike.  Players take turns making moves.
     On each move your OPPONENT chooses the piece, then YOU get to
     place it on the board.  If you create a set of four alike when
     you place your piece, then you win! A set of four alike can be
     completed by using four upper case characters, four lower-case
     characters, four vowels (a,e,i,o,u) or four consonants.
     
     The game level determines which positions can be used in completing
     four alike pieces.  Level one checks for four alike in every row,
     column, and diagonal.  Level two additionally checks for the pieces
     in the four corners as well as each cluster of four in each corner.
     
     When prompted for piece to use you may also:
     Enter 's' to change program level.
     Enter 'x' to exit the program.
     
     
     
     |---------|   Square #
     | . . . . |  1  2  3  4
     | . . . . |  5  6  7  8
     | . . . . |  9 10 11 12
     | . . . . | 13 14 15 16
     |---------|
     Pieces: AEIO aeio BCDF bcdf
     
     1. Player 2 enter piece, and Player 1 enter destination: E 6
     
     
     |---------|   Square #
     | . . . . |  1  2  3  4
     | . E . . |  5  6  7  8
     | . . . . |  9 10 11 12
     | . . . . | 13 14 15 16
     |---------|
     Pieces: A IO aeio BCDF bcdf
     
     2. Player 1 enter piece, and Player 2 enter destination: a 2
     
     
     |---------|   Square #
     | . a . . |  1  2  3  4
     | . E . . |  5  6  7  8
     | . . . . |  9 10 11 12
     | . . . . | 13 14 15 16
     |---------|
     Pieces: A IO  eio BCDF bcdf
     
     3. Player 2 enter piece, and Player 1 enter destination:
 
    .
    .
    .
 */
#include <iostream>
#include <cstring>
#include <ctype.h>
#include <stdio.h>

// Global constants
const int Board_Size = 16;

using namespace std;

//==============================================================================
/*prints information*/
void PrintHeader(){
    printf("\n");
    printf("Author: Pablo Escarcega      \n");
    printf("Program: #4, DoubleDown      \n");
    printf("\n");
}//end of PrintHeader()


//==============================================================================
// prints instructions on how to play
void PrintInstructions(){
    printf("Welcome to the game of DoubleDown, where you try to complete a set\n"); 
    printf("of four pieces that are alike.  Players take turns making moves.\n");  
    printf("On each move your OPPONENT chooses the piece, then YOU get to\n");    
    printf("place it on the board.  If you create a set of four alike when\n");    
    printf("you place your piece, then you win! A set of four alike can be\n");   
    printf("completed by using four upper case characters, four lower-case\n");    
    printf("characters, four vowels (a,e,i,o,u) or four consonants.\n\n");           
   
    printf("The game level determines which positions can be used in completing\n"); 
    printf("four alike pieces.  Level one checks for four alike in every row,\n");   
    printf("column, and diagonal.  Level two additionally checks for the pieces\n"); 
    printf("in the four corners as well as each cluster of four in each corner.\n\n"); 
  
    printf("When prompted for piece to use you may also:\n");                        
    printf("\tEnter 's' to change program level.\n");                             
    printf("\tEnter 'x' to exit the program. \n");
}//end of PrintInstructions()


//==============================================================================
// Returns true if the character is a '.' , returns false otherwise
bool isPeriod(char a){
     bool flag = false;
     
     if(a == '.'){
         flag = true;
     }
     
     return flag;
}//end of isPeriod()


//==============================================================================
// Return true if the letter passed is a vowel, return false otherwise
bool isVowel(char a){
    bool flag = false;
    
    a = toupper(a); // Make a uppercase for easier comparing
    
    if (a == 'A' || a == 'E' || a == 'I' || a == 'O') { //Check whether a is a vowel
        flag = true;
    }
    
    return flag;
}// end isVowel


//==============================================================================
// Return true if the letter passed is a vowel, return false otherwise
bool isConsonant(char a){
    bool flag = false;
    
    a = toupper(a);
    
    if(a == 'B' || a == 'C' || a == 'D' || a == 'F' ){
        flag = true;
    }
    
    return flag;
}//end of isConsonant()


//==============================================================================
// Return true if the letter passed is uppercase and not a '.', return false otherwise
bool isUppercase(char a){
    bool flag = false;
    
    if(isupper(a)){
        flag = true;
    }
    
    return flag;
}//end of isUppercase(){
    

//-------------------------------------------------------------------------------
// Return true if the letter passed is lowercase and not a '.', return false otherwise
bool isLowercase(char a){
    bool flag = false;
    
    if(islower(a)){
        flag = true;
    }
    
    return flag;
}//end of isLowercase



//-------------------------------------------------------------------------------
// returns true if the char was used, false otherwise
bool used(char board[], char userInput){
    for(int i = 0; i < Board_Size; i++){
        if(board[i] == userInput){
            return true;
        }
    }
    
    return false;
}//end of used()


//-------------------------------------------------------------------------------
//returns true if the location has not been used, false otherwise
bool locationValid(char board[], int moveLocation){
    if(board[moveLocation - 1] == '.')
        return true;
    else
        return false;
}//end of locationValid()


//-------------------------------------------------------------------------------
//error checking for a character
bool charValid(char board[], int moveLocation, char userInput){
    if( board[moveLocation - 1] == userInput || used(board, userInput) ){
           return false;
    }
    else{
        return true; 
    }

}//end of charValid()


//-------------------------------------------------------------------------------
//updates the letters still available to use
void updateAvailablePieces(char availablePieces[], char userInput){
    for(int i = 0; i < 19; i++){
        if(availablePieces[i] == userInput){
            availablePieces[i] = ' ';
        }
    }
}//end of updateAvailablePieces()


//-------------------------------------------------------------------------------
//Return true if postitions passed are all uppercase and none are periods, return false otherwise
bool allFourAreUppercase(char board[], int pos1, int pos2, int pos3, int pos4){
    if( isPeriod(board[pos1]) || isPeriod(board[pos2]) || isPeriod(board[pos3]) || isPeriod(board[pos4]) ){
        return false;
    }
    
    if( isUppercase(board[pos1]) && isUppercase(board[pos2]) && 
        isUppercase(board[pos3]) && isUppercase(board[pos4]) ){
        return true;        
    }
}//end of allFourAreUppercase()


//-------------------------------------------------------------------------------
//Return true if postitions passed are all lowercase, return false otherwise
bool allFourAreLowercase(char board[], int pos1, int pos2, int pos3, int pos4){
   if( isPeriod(board[pos1]) || isPeriod(board[pos2]) || isPeriod(board[pos3]) || isPeriod(board[pos4]) ){
        return false;
    }
    
    if( isLowercase(board[pos1]) && isLowercase(board[pos2]) && 
        isLowercase(board[pos3]) && isLowercase(board[pos4]) ){
        return true;        
    }
    
}//end of allFourAreLowercase()


//-------------------------------------------------------------------------------
//Return true if postitions passed are all vowels, return false otherwise
bool allFourAreVowels(char board[], int pos1, int pos2, int pos3, int pos4){
    if( isPeriod(board[pos1]) || isPeriod(board[pos2]) || isPeriod(board[pos3]) || isPeriod(board[pos4]) ){
        return false;
    }
    
    if( isVowel(board[pos1]) && isVowel(board[pos2]) && 
        isVowel(board[pos3]) && isVowel(board[pos4]) ){
        return true;        
    }
    
}//end of allFourAreVowels()


//-------------------------------------------------------------------------------
//Return true if postitions passed are all consonants, return false otherwise
bool allFourAreConsonants(char board[], int pos1, int pos2, int pos3, int pos4){
    if( isPeriod(board[pos1]) || isPeriod(board[pos2]) || isPeriod(board[pos3]) || isPeriod(board[pos4]) ){
        return false;
    }
    
    if( isConsonant(board[pos1]) && isConsonant(board[pos2]) && 
        isConsonant(board[pos3]) && isConsonant(board[pos4]) ){
        return true;        
    }
    
}//end of allFourAreConsonants()


//-------------------------------------------------------------------------------
bool checkAllPossiblilities(char board[], int pos1, int pos2, int pos3, int pos4){
    if(allFourAreConsonants(board, pos1, pos2, pos3, pos4))
        return true;
    if(allFourAreVowels(board, pos1, pos2, pos3, pos4))
        return true;
    if(allFourAreUppercase(board, pos1, pos2, pos3, pos4))
        return true;
    if(allFourAreLowercase(board, pos1, pos2, pos3, pos4))
        return true;
        
    return false; //no matches for a win in this combination of positions
    
}//end of checkAllPossiblilities()


//-------------------------------------------------------------------------------
//displays the board
void displayTheBoard( char board[], char availablePieces[], int moveNumber)
{
    printf("\n");
    printf("|---------|       Square # \n");
    printf("| %c %c %c %c |     1  2  3  4   \n", board[ 0], board[ 1], board[ 2], board[ 3]);
    printf("| %c %c %c %c |     5  6  7  8   \n", board[ 4], board[ 5], board[ 6], board[ 7]);
    printf("| %c %c %c %c |     9  10 11 12  \n", board[ 8], board[ 9], board[10], board[11]);
    printf("| %c %c %c %c |     13 14 15 16  \n", board[12], board[13], board[14], board[15]);
    printf("|---------|                  \n");
    
    printf("\t  Pieces: %s\n\n", availablePieces);
    
    if(moveNumber % 2 == 0){
        printf("%d. Player %d enter piece, and Player %d enter destination: ", 
            moveNumber, 1, 2);
    }
    else {
        printf("%d. Player %d enter piece, and Player %d enter destination: ", 
            moveNumber, 2, 1);
    }
    return;
}//end displayBoard()


//-------------------------------------------------------------------------------
//updates the board if the move is valid
void makeMove(char board[], int moveLocation, int &moveNumber, char userInput, char availablePieces[])  
{
    if(charValid(board, moveLocation, userInput)){
        if(locationValid(board, moveLocation)){
            board[moveLocation - 1] = userInput; 
            updateAvailablePieces(availablePieces, userInput);
        }
        else{
            printf("*** Board square %d is not empty.\n", moveLocation);
            printf("Please retry move.\n");
        }
    }
    else{
        printf("*** %c is an invalid piece selection.\n", userInput);
        printf("Please retry move.\n");
    }
    
    
    moveNumber++;
}//end of makeMove()


//-------------------------------------------------------------------------------
// Check to see if there was a win.  There is a win when there are 4 in a row in
// a row, column, or diagonal that are the same, and are not all '.' characters.
// For reference, the board index positions are:
//    0  1  2  3
//    4  5  6  7
//    8  9  10 11
//    12 13 14 15
bool thereIsAWinLevel1(char board[])   
{
    return checkAllPossiblilities(board, 0, 1, 2, 3)    || //1st row
           checkAllPossiblilities(board, 4, 5, 6, 7)    || //2nd row
           checkAllPossiblilities(board, 8, 9, 10, 11)  || //3rd row
           checkAllPossiblilities(board, 12, 13, 14, 15)|| //4th row
           
           checkAllPossiblilities(board, 0, 4, 8, 12)   || //1st col
           checkAllPossiblilities(board, 1, 5 ,9 , 13)  || //2nd col
           checkAllPossiblilities(board, 2, 6, 10, 14)  || //3rd col
           checkAllPossiblilities(board, 3, 7, 11 ,15)  || //4th col
           
           checkAllPossiblilities(board, 0, 5, 10, 15)  || //L to R diag
           checkAllPossiblilities(board, 3, 6 , 9, 12);    //R to L diag

}//end thereIsAWinLevel1()


//-------------------------------------------------------------------------------
// Check to see if there was a win.  There is a win when there are 4 in a row in
// a row, column, diagonal, corner clusters, or corners that are the same, and 
// are not all '.' characters.
// For reference, the board index positions are:
//    0  1  2  3
//    4  5  6  7
//    8  9  10 11
//    12 13 14 15
bool thereIsAWinLevel2(char board[])   
{
    return checkAllPossiblilities(board, 0, 1, 2, 3)    || //1st row
           checkAllPossiblilities(board, 4, 5, 6, 7)    || //2nd row
           checkAllPossiblilities(board, 8, 9, 10, 11)  || //3rd row
           checkAllPossiblilities(board, 12, 13, 14, 15)|| //4th row
           
           checkAllPossiblilities(board, 0, 4, 8, 12)   || //1st col
           checkAllPossiblilities(board, 1, 5 ,9 , 13)  || //2nd col
           checkAllPossiblilities(board, 2, 6, 10, 14)  || //3rd col
           checkAllPossiblilities(board, 3, 7, 11 ,15)  || //4th col
           
           checkAllPossiblilities(board, 0, 5, 10, 15)  || //L to R diag
           checkAllPossiblilities(board, 3, 6 , 9, 12)  || //R to L diag
           
           checkAllPossiblilities(board, 0, 3, 12, 15)  || //corners
           
           checkAllPossiblilities(board, 0, 1, 4, 5)    || //TL cluster of 4
           checkAllPossiblilities(board, 2, 3, 6, 7)    || //TR cluster of 4
           checkAllPossiblilities(board, 8, 9, 12, 13)  || //BL cluster of 4
           checkAllPossiblilities(board, 10, 11, 14, 15);  //BR cluster of 4

}//end thereIsAWinLevel2()


//-------------------------------------------------------------------------------
int main() {
    char board[ ] = "................";  // Initialize board to all periods.
    int moveNumber = 1;
    bool gameNotDone = true;
    int moveLocation = 0;                   //user selected game piece
    int level = 1;                              //game level
    char userInput = '\0';
    
    char availablePieces[] = "AEIO aeio BCDF bcdf";
    
 
    PrintHeader();
    PrintInstructions();
    
    // Play game loop
    while( gameNotDone) {
        displayTheBoard(board, availablePieces, moveNumber);
        
        // Get user input
        scanf(" %c", &userInput);
        
        // See if x was chosen to exit
        if( userInput == 'x') {
            printf("Exiting program... \n");
            break;
        }
        
        // See id s was chosen to change level
        if( userInput == 's'){
            printf("What level of play would you like? 1: Normal, 2: Add corners & groups -->");
            scanf("%d", &level);
            
            if(level == 2){
                if(thereIsAWinLevel2(board)){
                    printf("Sorry, changing level would lead to a pre-existing win.\n" 
                           "Resetting the level to level 1.\n\n");
                    level = 1;
                    displayTheBoard(board, availablePieces, moveNumber);   
                }
            }
            
        }
        
        //Get user location
        scanf(" %d", &moveLocation);
        
        // Make move and increment moveNumber
        makeMove( board, moveLocation, moveNumber, userInput, availablePieces);
        
        
        // Check for win in level 1
        if(level == 1){
            if( thereIsAWinLevel1( board)) {
                int player;
                if(moveNumber % 2 == 0)
                    player = 2;
                else
                    player = 1;
                    
                printf("*** Congratulations! *** Player %d wins the game!\n\n", player);

                displayTheBoard(board, availablePieces, moveNumber);
                
                gameNotDone = false;
                break;
            }
        }
        //check for win in level 2
        if(level == 2){
            if( thereIsAWinLevel2(board)){
                int player;
                if(moveNumber % 2 == 0)
                    player = 2;
                else
                    player = 1;
                    
                printf("*** Congratulations! *** Player %d wins the game!\n\n", player);

                displayTheBoard(board, availablePieces, moveNumber);
                gameNotDone = false;
                break;
            }
        }    
    
        
        // Exit loop if board is full
        if( moveNumber == Board_Size + 1) {
            gameNotDone = false;
            break;
        }
        
        
    }//end while( gameNotDone)

    
    printf("\nDone. \n");
    return 0;
}//end main()
