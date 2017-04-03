/* coinswap.cpp
 
 Sample output:
 
     Author: Pablo Escarcega
     Program: #6, Coin Swap
     
     Welcome to the coin swap puzzle.
     Make moves to solve the puzzle where the objective is to swap the
     place of the pieces on either side of the board.  X can only move
     to the right into an empty square, or can jump to the right over
     an O into an empty square. Conversely O can only move to the left
     into an empty square, or can jump to the left over an X into an
     empty square.
     
     For each move enter the source (1..5) and destination (1..5).
     Enter 0 to exit the program.
     
     1 2 3 4 5
     X X   O O    List: 1
     
     1. Enter source and destination: u
     *** You cannot undo past the beginning of the game.  Please retry.
     
     1 2 3 4 5
     X X   O O    List: 1
     
     1. Enter source and destination: 2 3
     
     1 2 3 4 5
     X   X O O    List: 2->1
     
     2. Enter source and destination: 4 2
     
     1 2 3 4 5
     X O X   O    List: 3->2->1
     
     3. Enter source and destination: u
     * Undoing move *
     
     1 2 3 4 5
     X   X O O    List: 2->1
     
     2. Enter source and destination: u
     * Undoing move *
     
     1 2 3 4 5
     X X   O O    List: 1
     
     1. Enter source and destination:
     .
     .
     .
 
 */
#include <iostream>
using namespace std;

// Global constants
const int BoardSize=5;
struct Node{
    char board[ BoardSize+1];
    int moveNumber;
    Node *pNext;
};

//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    printf("\n");
    printf("Author: Pablo Escarcega    \n");
    printf("Program: #6, Coin Swap     \n");
    printf("\n");
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------
// Display instructions
void displayInstructions()
{
    cout << "Welcome to the coin swap puzzle.                                  \n"
         << "Make moves to solve the puzzle where the objective is to swap the \n"
         << "place of the pieces on either side of the board.  X can only move \n"
         << "to the right into an empty square, or can jump to the right over  \n"
         << "an O into an empty square. Conversely O can only move to the left \n"
         << "into an empty square, or can jump to the left over an X into an   \n"
         << "empty square.  \n"
         << " \n"
         << "For each move enter the source (1..5) and destination (1..5).     \n"
         << "Enter 0 to exit the program. \n";
}//end displayInstructions()


//--------------------------------------------------------------------------------
// See if board pieces have finished being swapped.  This is the case when
// the left-most two pieces are both 'O' and the right-most two pieces are 'X'
bool notDone( char board[])
{
    return board[0]!='O' || board[1]!='O' || board[3]!='X' || board[4]!='X';
}


//--------------------------------------------------------------------------------
// Display the move numbers on the linked list, for debugging
void displayList( Node *pHead)
{
    cout << "   List: ";
    while( pHead != NULL) {
        cout << pHead->moveNumber;
        if( pHead->pNext != NULL)  cout << "->";
        pHead = pHead->pNext;
    }
    cout << endl;
}


//--------------------------------------------------------------------------------
void displayBoardAndList( char board[], Node *pHead)
{
    cout << endl;
    cout << "   1 2 3 4 5\n";
    cout << "   ";
    for( int i=0; i<BoardSize; i++) {
        cout << board[ i] << " ";
    }
    displayList( pHead);
    cout << endl;
}


//--------------------------------------------------------------------------------
// Delete the front node on the list and restore current game values from the
// next node that reflects the previous move.
void deleteNodeFromList(
        Node *&pHead,       // Pointer to the head of the list, which will advance
        char board[],       // Current game board to be restored from list
        int &moveNumber)    // Current move number to be restored from list
{
    // Sanity check: ensure there is at least one node on the list
    if( pHead->pNext == NULL) {
        cout << "*** You cannot undo past the beginning of the game.  Please retry."
             << "\n";
        return;
    }
    
    cout << "* Undoing move * \n";
    // Keep track of old head of the list which will be deleted
    Node *pTemp = pHead;
    
    // Advance the head pointer
    pHead = pHead->pNext;
    
    // Delete the old head of the list
    delete pTemp;
    
    // Restore game values from the new list head
    strcpy( board, pHead->board);
    moveNumber = pHead->moveNumber;
}//end deleteNodeFromList()


//--------------------------------------------------------------------------------
void promptForAndGetMove(
        Node *&pHead,       // Pointer to the head of the list, which will change
        char board[],       // Current game board to be stored onto the list
        int &moveNumber,    // Current move number to be stored onto the list
        int &source,        // Position to move from to be stored onto the list
        int &destination)   // Position to move to to be stored onto the list
{
    char userInput = ' ';
    
    // Infinite loop to handle possible multiple undo of moves
    while( true) {
        cout << moveNumber << ". Enter source and destination: ";
        cin >> userInput;
        // See if user input of 0 was given to exit the program
        if( userInput == 'x') {
            cout << "\n";
            cout << "Exiting program...\n";
            exit( 0);
        }
        if( userInput == 'u') {
            // Undo move
            deleteNodeFromList( pHead, board, moveNumber);
            displayBoardAndList( board, pHead);
            userInput = ' ';  // reset userInput, so it doesn't trigger undo again
            continue;   // Prompt to retry move
        }
        // Input is likely numeric and is not 'x' or 'u'.  Convert to a number.
        source = userInput - '0';
        
        // Also get destination portion of user input
        cin >> destination;
        
        // Adjust user entry to compensate for 0-based indexing, rather than 1-based
        source--;
        destination--;
        
        // break out of enclosing loop, as we don't need to undo a move
        break;
    }
}//end promptForAndGetMove()


//--------------------------------------------------------------------------------
// Try various move validation conditions and print the corresponding error message
// if any of the error conditions are found.
bool moveNotValid(char board[], int source, int destination)
{
    char sourceCharacter = board[ source];
    char destinationCharacter = board[ destination];
    
    // Ensure source and destination values are within the 0..4 array index range
    if( source<0 || source>4 || destination<0 || destination>4) {
        cout << "*** You can't refer to a position off the board. ";
        return true;
    }
    
    // Ensure X only moves right, and O only moves left
    if( (sourceCharacter=='X' && destination <= source) ||
        (sourceCharacter=='O' && source <= destination)
      ) {
        cout << "*** You can't move that piece that direction. ";
        return true;
    }
    
    // Ensure destination is blank
    if( destinationCharacter != ' ') {
        cout << "*** Destination square is not empty. ";
        return true;
    }
    // Ensure destination is adjacent, or jumps an opponent into the next square
    int offsetDifference = abs( source-destination);  // Find out how far away destination is
    if( offsetDifference > 2) {
        cout << "*** Destination is too far away. ";
        return true;
    }
    
    // When jumping, ensure the jumped piece is the opponent
    if( offsetDifference == 2) {
        // It is a jump
        int indexOfJumpedPiece = source + ((destination-source) / 2);
        char jumpedPiece = board[ indexOfJumpedPiece];
        if( (sourceCharacter == 'X' && jumpedPiece != 'O') ||
            (sourceCharacter == 'O' && jumpedPiece != 'X')
           ) {
            // Jumped piece is not the opponent
            cout << "*** A jumped square must have an opponent. ";
            return true;
        }
    }
    
    // All tests failed, so moveNotValid is false
    return false;
}//end moveNotValid()


//--------------------------------------------------------------------------------
// Create a new node and prepend it to the beginning of the list
void addNodeToList(
        Node *&pHead,       // Pointer to head of list, which will change
        char board[],       // The board, to be added to the list
        int moveNumber)     // The move number, to be added to the list
{
    // Create a new node and store current values into it
    Node *pTemp = new Node;
    strcpy( pTemp->board, board);
    pTemp->moveNumber = moveNumber;
    pTemp->pNext = pHead;
    
    // Prepend it onto the front of the list
    pHead = pTemp;
}


//--------------------------------------------------------------------------------
int main()
{
    char board[ BoardSize + 1] = "XX OO";  // extra character for the NULL
    int moveNumber = 1;
    int source, destination;               // store move information
    
    // Display identifying information, the instructions, and the initial board
    displayIdentifyingInformation();
    displayInstructions();

    Node *pHead = NULL;
    // Add a node onto the list.  The list may grow and shrink, but this first
    // node should always be there.
    addNodeToList( pHead, board, moveNumber);
    displayBoardAndList( board, pHead);
    
    // Game play loop
    while( notDone( board) ) {
        promptForAndGetMove( pHead, board, moveNumber, source, destination);
        
        if( moveNotValid( board, source, destination)) {
            cout << "Invalid move, please retry. \n";
            continue;
        }
        
        // Make move.  Note that no move validation is being done.
        board[ destination] = board[ source];
        board[ source] = ' ';
        moveNumber++;
        
        addNodeToList( pHead, board, moveNumber);
        
        displayBoardAndList( board, pHead);
    }
    
    cout << "Congratulations, you did it! \n"
         << "\n"
         << "Exiting program ...\n";
    return 0;         // return value to keep C++ happy
}//end main()
