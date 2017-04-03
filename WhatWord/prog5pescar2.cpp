/* prog5Boggle.cpp
 Play the word-guess game of Boggle.
 
 Running the program looks like the following:
 
     Author: Pablo Escarcega
     Program: #5, Boggle
     
     Welcome to the game of Boggle, where you play against the clock
     to see how many words you can find using adjacent letters on the
     board.  Each letter can be used only once for a given word.
     
     When prompted to provide input you may also:
          Enter 'r' to reset the board to user-defined values.
          Enter 's' to solve the board and display all possible words.
          Enter 't' to toggle the timer on/off.
          Enter 'x' to exit the program.
     
     The dictionary total number of words is: 263533
     Number of words of the right length is:  259709
     
       60 seconds remaining
     a c r l
     n e a p
     p u i m
     s a a n
        Score: 0
     1. Enter a word: near
        Worth 2 points.
     Words so far are: near
     
       44 seconds remaining
     a c r l
     n e a p
     p u i m
     s a a n
        Score: 2
     2. Enter a word: reap
        Worth 2 points.
     Words so far are: near reap
     
       38 seconds remaining
     a c r l
     n e a p
     p u i m
     s a a n
        Score: 4
     3. Enter a word: map
        Worth 1 points.
     Words so far are: map near reap
     
       31 seconds remaining
     a c r l
     n e a p
     p u i m
     s a a n
        Score: 5
     4. Enter a word: s
     Enter min and max word lengths to display: 6 7
     Words between 6 and 7 are:
     animal apneal arcane caiman capias encamp imparl lamias lamina launce maniac manias
     pareus paunce pauper placer camaieu campier praunce
     Exiting the program.
*/
#include <iostream>     // for input and output
#include <fstream>      // for file input and output
#include <ctime>        // timer functions
#include <cctype>       // tolower()
#include <stdio.h>      // printf, NULL
#include <cassert>      // for the assert statement
#include <stdlib.h>     // srand, rand
#include <string.h>     // strlen, strcpy


// Global constants
const int dictionarySize = 263533;  // Number of dictionary words
const int boardSize = 16;
const int MAX_SIZE = 81;            // Max user input length

const char DictionaryFileName[] = "dictionary.txt";

const int MinWordLength = 3;         // Minimum dictionary word size to be stored
const int MaxWordLength = 16;	     // Max word size.  Add 1 for null
const int BoardArraySide = 6;        // Number of elements per side on board array
const int NumberOfLetters = 26;      // Letters in the alphabet
const int Offsets[] = {-1,-7,-6,-5,1,7,6,5};  // offsets for neighbor squares, given an index
const int NumberOfNeighbors = 8;     // Number of elements in above array
const int TotalSecondsToPlay = 60;   // Total number of seconds to play per board

using namespace std;

//==============================================================================
/*prints information*/
void printHeader(){
    printf("\n");
    printf("Author: Pablo Escarcega    \n");
    printf("Program: #5, Boggle        \n");
    printf("\n");
}//end of printHeader()


//==============================================================================
/*prints instructions on how to play*/
void printInstructions(){
    printf("Welcome to the game of Boggle, where you play against the clock\n");  
    printf("to see how many words you can find using adjacent letters on the\n"); 
    printf("board. Each letter can be used only once for a given word.\n\n");      
  
    printf("When prompted to provide input you may also:\n");                      
    printf("    Enter 'r' to reset the board to user-defined values.\n");    
    printf("    Enter 's' to solve the board and display all possible words.\n");
    printf("    Enter 't' to toggle the timer on/off.\n");                     
    printf("    Enter 'x' to exit the program.\n\n");
    
}//end of printInstructions()


//==============================================================================
/*displays total words*/
void displayWordCount(int possibleWords){
    cout << "The dictionary total number of words is: "<< dictionarySize << endl
         << "Number of words of the right length is: " << possibleWords  << endl;

}//end of displayWordCount()


//==============================================================================
/*Read in dictionary by first dynamically allocate space for the dictionary. 
  Then read in words from file. CODE FROM PAST PROGRAM
  */
void readInDictionary(
          char ** &dictionary,                      // dictionary words
          long int &possibleWords)                  // number of words stored
{
    // Allocate space for large array of C-style strings
    dictionary = new char*[ dictionarySize];
    
    // For each array entry, allocate space for the word (C-string) to be stored there
    for(int i = 0; i < dictionarySize; i++) {
        dictionary[i] = new char[ MaxWordLength + 1];
        // just to be safe, initialize C-strings to all null characters
        for (int j = 0; j < MaxWordLength; j++) {
            dictionary[i][j] = '\0';
        }//end for (int j=0...
    }//end for (int i...
    
    // Now read in the words from the file
    ifstream inStream;                   // declare an input stream for my use
    possibleWords = 0;                   // Row for the current word
    inStream.open( DictionaryFileName);
    assert( ! inStream.fail() );         // make sure file open was OK
    
    // Keep repeating while input from the file yields a word
    char theWord[ 81];    // declare input space to be clearly larger than largest word
    while( inStream >> theWord) {
        int wordLength = (int)strlen( theWord);
        if( wordLength >= MinWordLength && wordLength <= MaxWordLength) {
            strcpy( dictionary[ possibleWords], theWord);
            // increment number of words
            possibleWords++;
        }
    }//end while( inStream...
    
    //display the word counts
    displayWordCount(possibleWords);
    
    // close the file
    inStream.close();
}//end readInDictionary()


//==============================================================================
/*Uses binary seach to search the dictionary array, returns the index of the 
  position found in the dicitonary. Otherwise, it returns -1 if not found. 
  CODE FROM PAST PROGRAM
  */
int binarySearch( const char searchWord[ MaxWordLength+1],  // word to be looked up
                  char **dictionary)                        // the dictionary of words
{
    int low, mid, high;     // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = dictionarySize - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // searchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = strcmp( searchWord, dictionary[ mid]);
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located prior to mid location
        }
        else  {
            low = mid + 1; // word should be located after mid location
        }
    }
    
    // Word was not found
    return -1;
}//end binarySearch()


//==============================================================================
/*calculate the number of points that each word will represent
  point table for reference
    Letters  Points
      <3        0
       3        1
       4        2
       5        4
       6+    #letters
*/
int calculatePoints(int wordLength){
    int points = 0;
    
    switch( wordLength) {
        case 0:
        case 1:
        case 2: points = 0; break;
        case 3: points = 1; break;
        case 4: points = 2; break;
        case 5: points = 4; break;
        default: points = wordLength; break;
    }
    
    return points;
}//end of calculatePoints()


//==============================================================================
/*Get random character
  Find random character using a table of letter frequency counts.
  Iterate through the array and find the first position where the random number is
  less than the value stored.  The resulting index position corresponds to the
  letter to be generated (0='a', 1='b', etc.)
  */
char generateRandomChar()
{
    // The following table of values came from the frequency distribution of letters in the dictionary
    float letterPercentTotals[ NumberOfLetters] = {
                0.07680,  //  a
                0.09485,  //  b
                0.13527,  //  c
                0.16824,  //  d
                0.28129,  //  e
                0.29299,  //  f
                0.32033,  //  g
                0.34499,  //  h
                0.43625,  //  i
                0.43783,  //  j
                0.44627,  //  k
                0.49865,  //  l
                0.52743,  //  m
                0.59567,  //  n
                0.66222,  //  o
                0.69246,  //  p
                0.69246,  //  q
                0.76380,  //  r
                0.86042,  //  s
                0.92666,  //  t
                0.95963,  //  u
                0.96892,  //  v
                0.97616,  //  w
                0.97892,  //  x
                0.99510,  //  y
                1.00000}; //  z
    
    // generate a random number between 0..1
    // Multiply by 1.0 otherwise integer division truncates remainders
    float randomNumber = 1.0 * rand() / RAND_MAX;
    
    // Find the first position where our random number is less than the
    // value stored.  The index corresponds to the letter to be returned,
    // where 'a' is 0, 'b' is 1, and so on.
    for(int i = 0; i < NumberOfLetters; i++) {
        if(randomNumber < letterPercentTotals[ i]) {
            // we found the spot.  Return the corresponding letter
            return (char) 'a' + i;
        }
    }
    
    // Sanity check
    cout << "No alphabetic character generated.  This should not have happened. Exiting program.\n";
    exit( -1);
    return ' ';   // should never get this
}//end generateRandomChar()


//==============================================================================
/*function that populates the board with random letters
  For reference, the board index positions are:
   8  9 10 11
  14 15 16 17
  20 21 22 23
  26 27 28 29 
  */
void populateBoard(char board[]){
    for(int row = 1; row < 5; row++){
        for(int col = 1; col < 5; col++){
            // calculate actual board position
            int index = row * BoardArraySide + col;
            // store a random character at that position
            board[index] = generateRandomChar();
        }
    }
    
}//end of populateBoard()


//==============================================================================
/*Given a board and index starting position for a row, and userInput along
  with an index starting point there, store the next four userInput values
  into the designated board row.
  */
void setFour(char board[], int boardIndex, char userInput[], int userInputIndex){
    for( int i = 0; i < 4; i++) {
        board[ boardIndex + i] = userInput[ userInputIndex + i];
    }
}//end of setFour()


//==============================================================================
/*function that resets the board to user-defined values
  For reference, the board index positions are:
   8  9 10 11
  14 15 16 17
  20 21 22 23
  26 27 28 29 
*/
void resetBoard(char board[]){
    cout << "Enter 16 characters to be used to set the board: ";
    char userInput[16 + 1];  // Extra character is for the NULL
    cin >> userInput;
    
    // Set the board characters in groups of 4, one group per line
    setFour(board,  7, userInput, 0); // first row
    setFour(board, 13, userInput, 4); // second row
    setFour(board, 19, userInput, 8); // third row
    setFour(board, 25, userInput, 12);// fourth row
}//end of resetBoard()


//==============================================================================
// Recursively see if the next character in the word is also on the board.
bool nextCharacterFound(
         char theWord[],       // the word to be found on board
         int lengthOfWord,     // length of word
         int wordLetterIndex,  // index of letter in word to be found this time
         char board[],         // the board
         int boardPosition)    // position on board of previous letter examined
{
    // Set the return value to default of false.  If any of the possible adjacent
    // positions on the board find it, then it will be set to true, indicating that
    // the current letter being searched for was found.
    bool wordWasFound = false;
    
    // Extract the character to be found now on this turn
    char c = theWord[ wordLetterIndex];
    
    // Iterate through each adjacent board neighbor of the current letter
    for( int i=0; i<NumberOfNeighbors; i++) {
        // Get the index of the neighbor
        int neighborIndex = boardPosition + Offsets[ i];
        
        // See if neighbor matches the word character we're looking for
        if( board[ neighborIndex] == c) {
            // The adjacent letter matches.  See if there are still word letters left to check
            if( wordLetterIndex + 1 < lengthOfWord) {
                // First blank out current character, which will be restored
                // after we return back to this function coming out of the recursion.
                board[ neighborIndex] = '*';
                
                // Here is the recursive call, looking for the next index position letter in theWord
                wordWasFound = nextCharacterFound( theWord, lengthOfWord, wordLetterIndex + 1,
                                                  board, neighborIndex);
                
                // Restore the character when we return from the recursion, so we can
                // go on and try a different neighbor as the next letter instead.
                board[ neighborIndex] = c;
            }
            else {
                // all word letters checked, so word was found
                wordWasFound = true;
            }
        }//end if( board[ neighborIndex....
        
        // Stop searching if word was found, otherwise after a word is found, a subsequent
        // partial word match can reset the result to false.
        if( wordWasFound) {
            break;
        }
    }//end for( int i...
    
    return wordWasFound;     // true or false
}// end ...CharacterFound()


//==============================================================================
/*checks if the word found is actually on the board, if so returns true, 
otherwise it returns false*/
bool foundInBoard(char theWord[],   // the word to be found on board
                  char board[])     // the board
{
    // set the return value to default of false.
    int wordWasFound = false;
    
    // Find first character of word on board
    char c = theWord[ 0];
    // Go through each board character and see if it matches.
    // Skip the surrounding asterisks
    for(int row = 1; row < 5; row++) {
        for( int col = 1; col < 5; col++) {
            // Once the word is found, stop searching. Otherwise once it is found, if the starting
            // letter is found elsewhere on the board, return values from subsequent character
            // search may mark it as not found.
            if( wordWasFound) {
                break;
            }
            // calculate actual board position
            int currentIndex = row * BoardArraySide + col;
            //  find first word character on board
            if( board[ currentIndex] == c) {
                // First character was found.  Blank it out on board so it is not reused.
                // It will be restored below after the next character is checked.
                board[ currentIndex] = '*';
                if( nextCharacterFound( theWord, (int)strlen( theWord),
                                        1, board, currentIndex)) {  // indicate which next letter to check
                    wordWasFound = true;
                }
                // Now restore the character that was previously blanked out
                board[ currentIndex] = c;
            }
        }
    }
    
    return wordWasFound;
    
}//end of foundInBoard()


//==============================================================================
/*displays the score*/
void displayScore(int score){
    cout << "   Score: " << score << endl;
}//end of displayScore()


//==============================================================================
/*displays the point value that the word found represents*/
void displayPointValue(int points){
    cout << "   Worth " << points << " points." << endl;
}//end of displayPointValue()


//==============================================================================
/*displays which words have already been found in order by word length*/
// Display the words found by going through the wordsFound array, and for
// every entry marked true, display the word.  Do this successively by
// word length, so all length 3 words are first displayed in order, then
// all word 4 length words, and so on.
void displayWordsFound(
       char **dictionary,       // 2d array of dictionary words
       long int possibleWords,  // how many words are in the dictionary
       long int wordsFound[],   // boolean array indicating which words were found
       int minimumLength,       // minimum length of words to display
       int maximumLength){      // maximum length of words to display
   
    cout << "Words so far are: ";
    int outputLineLength = 0;   // Used to print carriage-returns once output line length > 70
    
    // Go through entire dictionary multiple times, displaying the words in ascending length order
    for( int length=minimumLength; length<=maximumLength; length++) {
        for( int i=0; i<possibleWords; i++) {
            // display the word if it was found and if it is the current length
            if( wordsFound[ i] && strlen( dictionary[ i]) == length) {
                // display the word
                cout << dictionary[ i] << " ";
                // Accumulate the output line length, to break up the output
                outputLineLength += length;
                if( outputLineLength >= 70) {
                    outputLineLength = 0;   // Reset it
                    cout << "\n";
                }
            }
        }
    }
    
    cout << endl;
}//end displayWordsFound()


//==============================================================================
/*solves the board for the user and displays all possible words in the size 
range of their choice.*/
void solveBoard(char board[], char **dictionary,
                long int possibleWords, long int wordsFound[]){
    // zero out words found array, since it might have values left over from
    // last board checked
    for( int i = 0; i < possibleWords; i++) {
        wordsFound[ i] = 0;
    }
    
    // go through each word of the dictionary and see if it is on the board
    for( int i=0; i< possibleWords; i++) {
        wordsFound[ i] = foundInBoard( dictionary[ i], board);
    }
    
    // Display words on the board that are in the selected length range
    int minimumLength = 0;
    int maximumLength = MaxWordLength;
    cout << "Enter min and max word lengths to display: ";
    cin >> minimumLength >> maximumLength;
    cout << "Words between " << minimumLength << " and " << maximumLength << " are: " << endl;
    
    displayWordsFound( dictionary, possibleWords, wordsFound, minimumLength, maximumLength);

}//end of solveBoard()


//==============================================================================
/*checks the user imput for special characters that perform a certain operation
  on the game.*/
void checkSpecialOptions(char userInput[], char board[], bool &userWantsTimerDisabled,
                         char** dictionary, long int possibleWords, long int wordsFound[]){

    if(strlen(userInput) == 1) {
            switch(tolower(userInput[0])) {
                case 'r': resetBoard(board);                      // reset the board
                          break;
                case 't': userWantsTimerDisabled = !userWantsTimerDisabled;       // toggle the timer
                          break;
                case 's': solveBoard(board, dictionary, possibleWords, wordsFound);// solve the board
                case 'x': cout << "Exiting the program." << endl; // quits the game
                          exit(0);
                          break;
        }
    }
}//end of checkSpecialOptions()


//==============================================================================
/*displays the board*/
// For reference, the board index positions are:
//   8  9 10 11
//  14 15 16 17
//  20 21 22 23
//  26 27 28 29
void displayBoard(char board[], int score)
{
    int loopCounter = 1;
    
    for(int i = 0; i < 36; i++){
        cout << board[i] << " ";
        
        if(loopCounter % 6 == 0)
            cout << endl;
            
        loopCounter++;
    }

    //display score
    displayScore(score);
}//end displayBoard()


//==============================================================================
/*main function*/
int main(){
    //board is 1D array with asterisks as a border
    // For reference, the board index positions are:
    //   8  9 10 11
    //  14 15 16 17
    //  20 21 22 23
    //  26 27 28 29 
    char board[] = "*******    **    **    **    *******";  // Initialize board
    char **dictionary;              // 2d array of dictionary words, dynamically allocated
    long int possibleWords;         // how many words actually found
    long int *wordsFound;           // flags index of words found
    int score = 0;                  // score so far
    char userInput[MAX_SIZE];
    bool userWantsTimerDisabled = false;    // Used to toggle the timer
    int turn = 1;                   // Counts and displays moves made
    int elapsedSeconds = 0;         // Loop to play the game while there is still time left
    
    //print information
    printHeader();
    printInstructions();
    
    //read in dictionary & display the words counts
    readInDictionary(dictionary, possibleWords);
    //parallel array with indeces set to 1 if word is found in dictionary, 0 otherwise
    wordsFound = new long int[possibleWords];
    
    //start timer
    srand(time(NULL));
    //eclare a variable to hold a time, and get the current time
    time_t startTime = time( NULL);
    
    // Generate a random board
    populateBoard(board);
    
    //play game loop
    while((elapsedSeconds < TotalSecondsToPlay) || userWantsTimerDisabled){
        cout << endl;
        if(!userWantsTimerDisabled) {
           cout << "  " << TotalSecondsToPlay - elapsedSeconds << " seconds remaining" << endl;
        }
        displayBoard(board, score);
        
        //get user input
        cout << turn << ". Enter a word: ";
        cin >> userInput;
        
        //check for special commands by the user, i.e. 'r' 's' 't' 'x'
        checkSpecialOptions(userInput, board, userWantsTimerDisabled, dictionary, possibleWords, wordsFound);
        
        //check if word has already been used, otherwise check if it is valid
        if(foundInBoard(userInput, board)){
            int indexOfWordInDictionary = binarySearch(userInput, dictionary);
            
            // Ensure words was not previously already guessed and used for points
            if( wordsFound[ indexOfWordInDictionary]) { //if this was already set as found
                cout << "Sorry, that word was already previously found. " << endl;
                displayWordsFound( dictionary, possibleWords, wordsFound, MinWordLength, MaxWordLength+1);
                continue;
            }
            
            // Word was not already previously found
            if( indexOfWordInDictionary != -1) {
                //calculate points
                int points = calculatePoints(strlen( userInput));
                //display point value
                displayPointValue(points);
                //update the score
                score += points;
                //set that the index found to true in parrallel dictionary array
                wordsFound[ indexOfWordInDictionary] = true;
                //update turn
                turn++;
                
                displayWordsFound( dictionary, possibleWords, wordsFound, MinWordLength, MaxWordLength+1);
            }
            else cout << "was not found in the dictionary." << endl;
        }
        else
            cout << "cannot be formed on this board." << endl;
         
        //update the time    
        elapsedSeconds = difftime( time( NULL), startTime);
    }//end while

    printf("\nDone. \n");
    return 0;
}//end of main()


