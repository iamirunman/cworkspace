/* prog2TypeKeys.c
 
    Gather statistics to see if Qwerty or Dvorak keyboard layout is the best in terms of how far
    a person's fingers have to travel.

    Author: Pablo Escarcega
 
 
If we use the following file for input (copy and paste it so you don't get "smart" quotes):
     fast "sad--had,"
     
        MLS alaska oil line.
 
then running the program looks like:
 
     Author: Pablo Escarcega
     Program: #2, TypeKeys
 
     First two lines of the input file are:
     fast "sad--had,"
     
     
                    Total words:       6
     Total non-blank characters:      32
     
                                       Qwerty    Dvorak
     % All Characters on home row:        66        66
          % All Words on home row:        17        17
        % Words typed on one hand:        33        17
        Distance travelled(miles):         0.000     0.000
     
     ------ For debugging: ------      Qwerty    Dvorak
     Total characters on home row:        21        21
          Total words on home row:         1         1
    Total words typed on one hand:         2         1
       Distance travelled(inches):        10.75     11.50
 
 Using PuddnheadWilsonByMarkTwain.txt as a data file gives these results:
 
     Author: Pablo Escarcega
     Program: #2, TypeKeys
 
     First two lines of the input file are:
     THE TRAGEDY OF PUDD'NHEAD WILSON
     by Mark Twain
     
                    Total words:   53096
     Total non-blank characters:  237683
     
                                        Qwerty    Dvorak
      % All Characters on home row:        35        69
           % All Words on home row:         5        35
         % Words typed on one hand:        17         6
         Distance travelled(miles):         2.203     1.243
     
     ------ For debugging: ------       Qwerty    Dvorak
      Total characters on home row:     83326    163286
           Total words on home row:      2441     18543
     Total words typed on one hand:      8884      2941
        Distance travelled(inches):    139581.00  78747.50
 
 
 Using 2000LeaguesUnderTheSeaJulesVerne.txt as a data file gives these results:
 
     Author: Pablo Escarcega
     Program: #2, TypeKeys
 
     First two lines of the input file are:
     TWENTY THOUSAND LEAGUES UNDER THE SEA
     by JULES VERNE
     
                    Total words:  102944
     Total non-blank characters:  480295
     
                                        Qwerty    Dvorak
      % All Characters on home row:        33        68
           % All Words on home row:         4        34
         % Words typed on one hand:        17         5
         Distance travelled(miles):         4.503     2.505
     
     ------ For debugging: ------       Qwerty    Dvorak
      Total characters on home row:    159427    328988
           Total words on home row:      3835     34541
     Total words typed on one hand:     17074      5304
        Distance travelled(inches):    285305.75 158702.75
 
 */
#include <stdio.h>
#include <stdlib.h>      // For file input and output
#include <string.h>      // For string functions
#include <assert.h>      // For sanity check assertions
#include <ctype.h>       // For character type checking

// Global constants
const int MAX_LENGTH = 81;   // global constant for max input line length
//const char FILE_NAME[] = "20000LeaguesUnderTheSeaJulesVerne.txt";
//const char FILE_NAME[] = "PuddnheadWilsonByMarkTwain.txt";
const char FILE_NAME[] = "words.txt";

// The following constants help define the number cells in the following table, stored in two arrays:
//                         | Qwerty | Dvorak |
//          HOME_ROW_CHARS |        |        |
//          HOME_ROW_WORDS |        |        |
//          ONE_HAND_WORDS |        |        |
//        INCHES_TRAVELLED |        |        |
//
const int NUMBER_OF_ROWS = 4;      // Total number of table rows in the above table
const int HOME_ROW_CHARS = 0;      // Top row, counting % All Letters on home row
const int HOME_ROW_WORDS = 1;      // Second row, counting % All Words on home row
const int ONE_HAND_WORDS = 2;      // Third row, counting % Words typed on one hand
const int INCHES_TRAVELLED = 3;    // Fourth row, counting total inches travelled


//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    printf("\n");
    printf("Author: Pablo Escarcega    \n");
    printf("Program: #2, TypeKeys      \n");
    printf("\n");
}//end displayIdentifyingInformation()


//----------------------------------------------------------------------------------
// Open the text file.  Since the file pointer is already of type "FILE *", when we make
// it a reference parameter we add a second star, making it of type "FILE **"
void openTextFile( FILE **pInputFile)
{
    // Associate the file pointer with the actual file name and try to open it
    *pInputFile = fopen( FILE_NAME, "r");   // open with "r" for "read" access
    // verify that file open worked
    if (*pInputFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", FILE_NAME);
        exit(-1);
    }
}
    
    

//----------------------------------------------------------------------------------
// Parse allWords to find the next word, updating the current index in allWords
// and returning the new word in the newWord array.
void extractNextWordFromLine(
             char allWords[],    // The line of all words
             int *wordsIndex,    // The current index postion in allWords, with changes reflected back
             char newWord[])     // The new word is placed in this array, to be returned and used
{
    int j = 0;     // Set the index within the newWord array to start at the beginning
    char c='\0';   // Temporary storage for each character as we read it
    
    // Initialize c to be the first character, if there is one
    if( allWords[ *wordsIndex] != '\0') {
        c = allWords[ *wordsIndex];     // Get first character
        (*wordsIndex)++;                // Advance index to the next character
    }
    
    // Skip leading spaces if there are any
    while( c==' ') {
        c = allWords[ *wordsIndex];   // advance to the next character
        (*wordsIndex)++;              // Advance index to the next character
    }

    // Copy characters into the word until we hit a space or null
    while( c!=' ' && c!='\0') {
        newWord[ j++] = c;
        // Get the next character
        c = allWords[ *wordsIndex];
        // advance to the next character if we're not at the end of the list
        if( c!='\0') {
            (*wordsIndex)++;          // Advance index to the next character
        }
    }//end while(...
    
    // NULL terminate the word so that we can use string functions
    newWord[ j] = '\0';
}//end extractNextWordFromLine()


//----------------------------------------------------------------------------------
// Count and return the number of non-white-space characters on the input line.
int countCharacters( char inputLine[])
{
    int numberOfCharacters = 0;
    
    int i;
    for( i=0; i<strlen(inputLine); i++){
        char c=inputLine[ i];
        if( c!=' ' && c!='\t' && c!= '\n') {
            numberOfCharacters++;
        }
    }
    
    return numberOfCharacters;
}//end countCharacters()


//----------------------------------------------------------------------------------
// count the number of times char c is found in theString
int countCharFoundInString( char c, char theString[])
{
    int count = 0;
    int i;
    for( i=0; i<strlen( theString); i++) {
        if( c == theString[ i]) {
            count++;
        }
    }
    
    // Sanity check for this program: count should never be > 1
    assert( count <= 1);
    
    return count;
}


//----------------------------------------------------------------------------------
// Return 1 if theWord can be formed using only the letters in theString, else return 0.
int countWordMadeOnlyOfCharsInString( char theWord[], char theString[])
{
    int allLettersFound = 1;   // Assume all letters can be found.  Reset if not.
    
    int i;
    for( i=0; i<strlen(theWord); i++) {
        char c = theWord[ i];
        if( countCharFoundInString( c, theString) != 1) {
            // character was not found, so word cannot be formed from letters in theString
            allLettersFound = 0;
            break;      // No need to keep checking
        }
    }
    
    return allLettersFound;
}


//----------------------------------------------------------------------------------
// Distances travelled depend on fingers moving from middle row to number, upper and lower rows.
// In addition there are a few characters that add some distance.
// This function is not completely accurate, as the upper-right keys should technically
// have greater distances, as would fingers to the right of the right-hand pinky home position.
//
// While this function is almost identical to countDvorakIncehsTravelled (which follows), I left them
// separate because of the need for separate special case characters.  Combining the two
// functions together would have made it more difficult to understand that portion of the code.
double countQwertyInchesTravelled(
        char theWord[],
        char numberRowChars[],
        char upperRowChars[],
        char homeRowChars[],
        char lowerRowChars[])
{
    double inchesTravelled = 0;
    
    // Accumulate distance travelled counts for each character in the word for Qwerty
    int i;
    for( i=0; i<strlen(theWord); i++) {
        char c = toupper( theWord[i]);   // Character is converted to upper case if it is lower case
        
        // handle the QWERTY special cases first
        switch( c) {
            case 'G':
            case 'H': inchesTravelled += 0.75;
                      break;
            case 'T':
            case 'Y': inchesTravelled += 1.0;
                      break;
            case 'B': inchesTravelled += 1.25;
                      break;
            case '6':
            case '^': inchesTravelled += 1.75;
                      break;
            // Handle the default, which will be most cases
            default:
                    if( countCharFoundInString( c, numberRowChars) == 1) {
                        inchesTravelled += 1.5;
                    }
                    else if( countCharFoundInString( c, upperRowChars) == 1) {
                        inchesTravelled += 0.75;
                    }
                    else if( countCharFoundInString( c, lowerRowChars) == 1) {
                        inchesTravelled += 0.75;
                    }
                    else if( countCharFoundInString( c, homeRowChars) == 1) {
                        inchesTravelled += 0.0;
                    }
                    else {
                        // Sanity check
                        printf("\nCharacter %c was not found in any of the sets.  Aborting...\n", c);
                        //exit( -1);
                    }
                    break;
        }//end switch( c)
        
    }//end for( i...

    return inchesTravelled;
}//end countQwertyInchesTravelled()


//----------------------------------------------------------------------------------
// This is identical to the above function, with the difference being the characters
// used for the special cases.
double countDvorakInchesTravelled(
          char theWord[],
          char numberRowChars[],
          char upperRowChars[],
          char homeRowChars[],
          char lowerRowChars[])
{
    double inchesTravelled = 0;
    
    // Accumulate distance travelled counts for each character in the word for Qwerty
    int i;
    for( i=0; i<strlen(theWord); i++) {
        char c = toupper( theWord[i]);   // Character is converted to upper case if it is lower case
        
        // handle the DVORAK special cases first
        switch( c) {
            case 'I':
            case 'D': inchesTravelled += 0.75;
                break;
            case 'Y':
            case 'F': inchesTravelled += 1.0;
                break;
            case 'X': inchesTravelled += 1.25;
                break;
            case '6':
            case '^': inchesTravelled += 1.75;
                break;
                // Handle the default, which will be most cases
            default:
                if( countCharFoundInString( c, numberRowChars) == 1) {
                    inchesTravelled += 1.5;
                }
                else if( countCharFoundInString( c, upperRowChars) == 1) {
                    inchesTravelled += 0.75;
                }
                else if( countCharFoundInString( c, lowerRowChars) == 1) {
                    inchesTravelled += 0.75;
                }
                else if( countCharFoundInString( c, homeRowChars) == 1) {
                    inchesTravelled += 0.0;
                }
                else {
                    // Sanity check, should trigger the same as the function above.
                    //printf("Character %c was not found in any of the sets. Aborting...\n", c);
                    //exit( -1);
                }
                break;
        }//end switch( c)
        
    }//end for( i...
    
    return inchesTravelled;
}//end countDvorakInchesTravelled()


//----------------------------------------------------------------------------------
// Return the word in place with the leading and trailing punctuation removed.
void removeLeadingAndTrailingPunctuation( char theWord[])
{
    // Make a copy of the word
    char wordCopy[ MAX_LENGTH];
    int i;
    for( i=0; i<strlen(theWord); i++) {
        wordCopy[ i] = theWord[ i];
    }
    
    // Find first non punctuation character
    i=0;
    while( ispunct( wordCopy[ i])) {
        i++;
    }
    // Copy over the rest of the word
    int j=0;  // Set the destination index to start at the beginning of the word
    for( ; i<strlen( theWord); i++) {
        theWord[ j] = wordCopy[ i];
        j++;
    }
    // null terminate the word
    theWord[ j] = '\0';
    
    // Repeatedly overwrite trailing punctuation characters with nulls
    // Cast into (int) to avoid warning of "implicit loss of precision"
    i = (int)strlen( theWord) - 1;   // Set index to the last character in the word
    while( i>=0 && ispunct(theWord[ i])) {
        theWord[ i] = '\0';
        i--;
    }
}


//----------------------------------------------------------------------------------
// Do the various counts for this word.
// The following constants help define the number cells in the following table, stored in two arrays:
//                         | Qwerty | Dvorak |
//          HOME_ROW_CHARS |        |        |
//          HOME_ROW_WORDS |        |        |
//          ONE_HAND_WORDS |        |        |
//        INCHES_TRAVELLED |        |        |
void doWordCounts(
      char theWord[],           // The word being analyzed
      double qwertyCounts[],    // Array to store the Qwerty counts
      double dvorakCounts[])    // Array to store the Dvorak counts
{
    // Declare the sets to be used to find if an individual character is in a set.
    
    // Home Row sets.  Leave space for the double-quote character, which must be manually added
    char qwertyHomeRowChars[] = " asdfghjkl;'ASDFGHJKL:";   // leave the first char blank, to store "
    qwertyHomeRowChars[ 0] = '"';   // store the double-quote character
    char dvorakHomeRowChars[] = "aAoOeEuUiIdDhHtTnNsS-_";

    // Single hand sets.  The backslash '\' character is added by using two adjacent backslashes
    char qwertyLeftHandChars[] = "~!@#$%`12345qwertQWERTasdfgASDFGzxcvbZXCVB";
    char qwertyRightHandChars[] = " ^&*()_+67890-=yuiop[]\\YUIOP{}|hjkl;'HJKL:nm,./NM<>?";  // "\\" gives '\'
    qwertyRightHandChars[ 0] = '"';  // store the double-quote character
    char dvorakLeftHandChars[] = " ~`!1@2#3$4%5'<,>.PpYyAaOoEeUuIi:;QqJjKkXx";
    dvorakLeftHandChars[ 0] = '"';   // store the double-quote character
    char dvorakRightHandChars[] = "^6&7*8(9)0{[}]FfGgCcRrLl?/+=|\\DdHhTtNnSs-_BbMmWwVvZz";  // "\\" gives '\'
    
    // Sets of Number rows characters
    char qwertyNumberRow[] = "~!@#$%^&*()_+`1234567890-=";
    char dvorakNumberRow[] = "~!@#$%^&*(){}`1234567890[]";
    
    // Sets of Upper rows characters.  The backslash '\' character is added by using two adjacent backslashes.
    char qwertyUpperRow[] = "qwertyuiop[]\\QWERTYUIOP{}|";    //  "\\" gives '\'
    char dvorakUpperRow[] = " <<PYFGCRL?+|',.pyfgcrl/=\\";    //  "\\" gives '\'
    dvorakUpperRow[ 0] = '"';  // store the double-quote character
    
    // Sets of Lower rows characters.
    char qwertyLowerRow[] = "zxcvbnm,./ZXCVBNM<>?";
    char dvorakLowerRow[] = ";:qQjJkKxXbBmMwWvVzZ";
    
    // Calculate finger distance travelled in inches.  Do this with the original word, potentially
    // containing leading and trailing punctuation characters, which should all be counted.
    qwertyCounts[ INCHES_TRAVELLED] += countQwertyInchesTravelled( theWord, qwertyNumberRow, qwertyUpperRow,
                                                                  qwertyHomeRowChars, qwertyLowerRow);
    dvorakCounts[ INCHES_TRAVELLED] += countDvorakInchesTravelled( theWord, dvorakNumberRow, dvorakUpperRow,
                                                                  dvorakHomeRowChars, dvorakLowerRow);
    
    // Count letters on home row.
    int i;
    for( i=0; i<strlen(theWord); i++) {
        char c = theWord[ i];
        qwertyCounts[ HOME_ROW_CHARS] += countCharFoundInString( c, qwertyHomeRowChars);
        dvorakCounts[ HOME_ROW_CHARS] += countCharFoundInString( c, dvorakHomeRowChars);
    }
    
    // Now remove leading and trailing punctuation so that word counts for row and hand sets are accurate
    removeLeadingAndTrailingPunctuation( theWord);
    
    // Count if word can be formed by only homerow letters, for both Qwerty and Dvorak
    qwertyCounts[ HOME_ROW_WORDS] += countWordMadeOnlyOfCharsInString( theWord, qwertyHomeRowChars);
    dvorakCounts[ HOME_ROW_WORDS] += countWordMadeOnlyOfCharsInString( theWord, dvorakHomeRowChars);
    
    // Count if word can be formed by only Qwerty letters on left hand, or only Qwerty letters on right hand
    qwertyCounts[ ONE_HAND_WORDS] += countWordMadeOnlyOfCharsInString( theWord, qwertyLeftHandChars);
    qwertyCounts[ ONE_HAND_WORDS] += countWordMadeOnlyOfCharsInString( theWord, qwertyRightHandChars);
    // Now the same thing for both hands for the dvorak keyboard
    dvorakCounts[ ONE_HAND_WORDS] += countWordMadeOnlyOfCharsInString( theWord, dvorakLeftHandChars);
    dvorakCounts[ ONE_HAND_WORDS] += countWordMadeOnlyOfCharsInString( theWord, dvorakRightHandChars);
    
}//end doWordCounts()


//----------------------------------------------------------------------------------
// Return the number of non-blank words found.  As we go also process the counts
// for each word.
int extractAndProcessEachWord(
            char inputLine[],         // The input line
            double qwertyCounts[],    // Array to store the Qwerty counts
            double dvorakCounts[])    // Array to store the Dvorak counts
{
    char aWord[ MAX_LENGTH];        // A single word
    int howManyWordsFound = 0;      // How many words are found on the inputLine
    
    // Extract and accumulate the count of each non-zero length words from the
    // input line, one at a time
    int i=0;
    while( inputLine[ i] != '\0') {
        extractNextWordFromLine( inputLine, &i, aWord);
        // Only count non-zero-length words.  An empty line has a single '\n' on it
        if( aWord[ 0] != '\n' && aWord[ 0] != '\0') {
            howManyWordsFound++;
            
            // Do all the counts for this word
            doWordCounts( aWord, qwertyCounts, dvorakCounts);
        }
    }
    
    return howManyWordsFound;
}//end extractAndProcessEachWord


//----------------------------------------------------------------------------------
// Display tabular results
void displayResults(
            double qwertyCounts[],
            double dvorakCounts[],
            int totalCharacters,
            int totalWords)
{
    // Display the results
    printf("\n");
    printf("               Total words: %7d\n", totalWords);
    printf("Total non-blank characters: %7d\n", totalCharacters);
    printf("\n");
    printf("                                   Qwerty    Dvorak\n");
    printf(" %% All Characters on home row:   %7.0f   %7.0f \n",
                        qwertyCounts[HOME_ROW_CHARS] / totalCharacters * 100,
                        dvorakCounts[HOME_ROW_CHARS] / totalCharacters * 100);
    printf("      %% All Words on home row:   %7.0f   %7.0f \n",
                        qwertyCounts[HOME_ROW_WORDS] / totalWords * 100,
                        dvorakCounts[HOME_ROW_WORDS] / totalWords * 100);
    printf("    %% Words typed on one hand:   %7.0f   %7.0f \n",
                        qwertyCounts[ONE_HAND_WORDS] / totalWords * 100,
                        dvorakCounts[ONE_HAND_WORDS] / totalWords * 100);
    printf("    Distance travelled(miles):       %7.3f   %7.3f \n",
                        qwertyCounts[INCHES_TRAVELLED] / 12 / 5280,  // 12 inches/ft, and
                        dvorakCounts[INCHES_TRAVELLED] / 12 / 5280); //   5280 ft/mile
    printf("\n");
}


//----------------------------------------------------------------------------------
// Display debugging version of tabular results, showing the totals
void displayDebuggingResults(
            double qwertyCounts[],
            double dvorakCounts[],
            int totalCharacters,
            int totalWords)
{
    // For debugging, display the Totals
    printf("------ For debugging: ------       Qwerty    Dvorak\n");
    printf(" Total characters on home row:   %7.0f   %7.0f \n",
                        qwertyCounts[HOME_ROW_CHARS], dvorakCounts[HOME_ROW_CHARS]);
    printf("      Total words on home row:   %7.0f   %7.0f \n",
                        qwertyCounts[HOME_ROW_WORDS], dvorakCounts[HOME_ROW_WORDS]);
    printf("Total words typed on one hand:   %7.0f   %7.0f \n",
                        qwertyCounts[ONE_HAND_WORDS], dvorakCounts[ONE_HAND_WORDS]);
    printf("   Distance travelled(inches):   %10.2f%10.2f \n",
                        qwertyCounts[INCHES_TRAVELLED], dvorakCounts[INCHES_TRAVELLED]);
    printf("\n");
}


//----------------------------------------------------------------------------------
int main()
{
    FILE *pInputFile;               // file pointer
    char inputLine[ MAX_LENGTH];    // An input line with some number of words on it
    
    // Create two arrays to store all the following counts:
    //                            | Qwerty | Dvorak |
    //             HOME_ROW_CHARS |        |        |
    //             HOME_ROW_WORDS |        |        |
    //             ONE_HAND_WORDS |        |        |
    //           INCHES_TRAVELLED |        |        |
    double qwertyCounts[ NUMBER_OF_ROWS];
    double dvorakCounts[ NUMBER_OF_ROWS];
    
    int totalCharacters = 0;
    int totalWords = 0;
    int inputLineNumber = 0;
    
    displayIdentifyingInformation();
    
    openTextFile( &pInputFile);
    
    // Blank out the counts arrays
    int i;
    for( i=0; i<NUMBER_OF_ROWS; i++) {
        qwertyCounts[ i] = 0;
        dvorakCounts[ i] = 0;
    }
    
    // Read a line at a time from the file and do the character counts on it.
    // Then reprocess that line to count the number of words and handle them one at a time.
    printf("First two lines of the input file are:\n");
    while( fgets(inputLine, MAX_LENGTH, pInputFile) != NULL) {
        
        // Eliminate the trailing newline character '\n' if there is one on this line.
        // There potentially won't be one on the last line of the file.
        int n = strlen(inputLine);
        if( inputLine[ n-1] == '\n') {
           inputLine[ n - 1] = '\0';
        }
        
        // Display only the first two lines of the input file
        if( inputLineNumber++ < 2) {
            printf("%s\n", inputLine);
        }
        
        // Add to the count of total number of characters
        totalCharacters += countCharacters( inputLine);
        
        // Add to the count of total number of words.  As you go process the Qwerty and
        // Dvorak counts for each word.
        totalWords += extractAndProcessEachWord( inputLine, qwertyCounts, dvorakCounts);
        
    }//end while( fgets...
    
    // Display the table of results
    displayResults( qwertyCounts, dvorakCounts, totalCharacters, totalWords);
    displayDebuggingResults( qwertyCounts, dvorakCounts, totalCharacters, totalWords);
    
    fclose( pInputFile);         // close the input file
    return 0;
}//end main()
