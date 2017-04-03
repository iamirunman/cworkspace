/* prog3IKEAWords.c
      Given a list of IKEA product names, find names in English that are the same or similar.
 
     This is done in stages:
     1. Display all IKEA words that match English dictionary words
     2. Display all words from an input file that exactly match IKEA words (minus leading and
        trailing punctuation)
     3. Display all words from an input file that match IKEA words when:
        a) One character is deleted from the input word
        b) One character is substituted from the input word
        c) One character is inserted into the input word
        d) The input word is a substring of some IKEA word
     4. Same as the previous step, except now up to 3 characters are changed.
     
     Author: Pablo Escarcega
 
 Consider using this inputfile.txt:
    I want to attest that Billy asked Bertha and Dana
    if they were having a "blast" while dining. 
    The menu was a document with a picture of an elephant.
 
 Output from running program is:
 
     Author: Pablo Escarcega
     Program: #3, IKEA Words

     
     There were 40437 words read from dictionary.txt, with max length 21.
     There were 1764 words read from IKEAwords.txt, with max length 14.
     
     1. Ikea words found in the dictionary are:
     1. alex         2. attest       3. barometer    4. billy        5. blast
     6. calypso      7. capita       8. cider        9. citron      10. cylinder
     11. dessert     12. dining      13. dragon      14. format      15. franklin
     16. frost       17. glenn       18. groggy      19. hall        20. harry
     21. heat        22. ideal       23. inner       24. iris        25. kilometer
     26. lack        27. lax         28. lots        29. martin      30. matilda
     31. not         32. pomp        33. portion     34. rand        35. senior
     36. sill        37. skimmer     38. slat        39. smoothie    40. soda
     41. soften      42. stall       43. stave       44. succulent   45. sultan
     46. swedish     47. textiles    48. toga        49. tolerant    50. urban
     51. utter       52. yucca
     
2. Input file words found in the Ikea list are: 
i want to ATTEST that billy asked bertha and dana if they were having a BLAST while dining the menu was a document with a picture of an elephant 

3. Input file words found in the Ikea list after 1 delete, substitute, insert or substring search are: 
AINA want ANGSTOREL ATTEST that BILLY asked BERTA RAND DANKA ANTIFONI they were having ADDE BLAST while DYNING CALATHEA menu SAS ADDE DOKUMENT with ADDE picture DOFTA AGGPLANTA ELEPHANTIPES 

4. Input file words found in the Ikea list after multiple delete, substitute, insert or substring searches are: 
AINA DYNT ANGSTOREL ATTEST HEAT BILLY OSTED BERTA RAND DANKA ANTIFONI AGEN ADDE BARING ADDE BLAST HYLLE DYNING CALATHEA RENS SAS ADDE DOKUMENT DITO ADDE picture DOFTA AGGPLANTA ELEPHANTIPES
 */
#include <stdio.h>
#include <string.h>   // for string length
#include <stdlib.h>   // for exit()
#include <ctype.h>    // for tolower()

#define TRUE 1
#define FALSE 0

const int MaxWordSize = 21 + 1;                      // Maximum size of any word in the dictionary, + 1 for null
const int NumberOfWordsInDictionary = 40437;         // Number of words in the dictionary
const char DictionaryFileName[] = "dictionary.txt";  // File name for where dictionary words are found
const int NumberOfIkeaWords = 1764;                  // Number of IKEA words are in the IKEA file
const char IkeaWordsFileName[] = "IKEAwords.txt";    // File name for the IKEA words
const char InputFileName[] = "inputfile.txt";        // File name for input file of some text


//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    printf("\n");
    printf("Author: Pablo Escarcega      \n");
    printf("Program: #3, IKEA Words      \n");
    printf("\n");
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------------
// Use binary search to look up the word in the dictionary array, returning index if found, -1 otherwise
int binarySearch( const char searchWord[], 				  // word to be looked up
                  const char dictionary[][MaxWordSize],	  // the dictionary of words
                  int numberOfDictionaryWords)		      // number of words in the dictionary
{
    int low, mid, high;     // array indices for binary search
    int searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = numberOfDictionaryWords - 1;
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


//--------------------------------------------------------------------------------------
// Try to open the input file and display an error message if it can't be opened.
void openAndValidateInputFile( const char inputFileName[], FILE **pFilePointer)
{
    // Associate the actual file name with file pointer and try to open it
    *pFilePointer = fopen(inputFileName, "r");
    // verify that file open worked
    if (*pFilePointer == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", inputFileName);
        exit(-1);
    }
}//end openAndValidateInputFile()


//--------------------------------------------------------------------------------------
// Read in the words from the designated file, into the given array
void readWordsFromFile( const char inputFileName[], char wordsArray[ ][ MaxWordSize])
{
    FILE *pInputFile;       // file pointer
    int howManyWords = 0;   // index of word being read
    int maxWordLength = 0;
    
    // Associate the actual file name with file pointer and try to open it
    openAndValidateInputFile( inputFileName, &pInputFile);
    
    // Keep reading words while there are any
    while( fscanf(pInputFile, "%s", wordsArray[ howManyWords]) != EOF) {
        int tempLength = (int)strlen( wordsArray[ howManyWords]);
        if (tempLength > maxWordLength) {
            maxWordLength = tempLength;
        }
        howManyWords++;
    }
    
    printf("There were %d words read from %s, with max length %d. \n", howManyWords, inputFileName, maxWordLength);
    fclose( pInputFile);   // close the file
}//end readWordsFromFile()


//--------------------------------------------------------------------------------------
// Convert the letters in a word to all lower case
char * convertWordToLowerCase( char aWord[ ])
{
    int i;
    for( i=0; i<strlen(aWord); i++) {
        aWord[ i] = tolower( aWord[i]);
    }
    
    return aWord;
}//end convertWordToLowerCase()


//--------------------------------------------------------------------------------------
// Convert the letters in a word to all UPPER case
char * convertWordToUpperCase( char aWord[ ])
{
    int i;
    for( i=0; i<strlen(aWord); i++) {
        aWord[ i] = toupper( aWord[i]);
    }
    
    return aWord;
}//end convertWordToUPPERCase()


//--------------------------------------------------------------------------------------
// Convert the IKEA words to all lower case
void convertAllIKEAWordsToLowerCase( char ikeaWords[ ][ MaxWordSize])
{
    int i;
    for( i=0; i< NumberOfIkeaWords; i++) {
        convertWordToLowerCase( ikeaWords[i]);
    }
}//end convertAllIKEAWordsToLowerCaseI()


//--------------------------------------------------------------------------------------
// For Stage 1: Step through each IKEA word as-is and look it up in the dictionary, printing it out
// if it is found.
void displayIKEAWordsFoundInDictionary(
       char ikeaWords[ ][ MaxWordSize],
       char dictionary[ ][ MaxWordSize])
{
    int ikeaWordsFoundCounter = 0;
    int wordsPerLineCounter = 0;   // Not required to be implemented in program description
    
    for( int i=0; i< NumberOfIkeaWords; i++) {
        if( binarySearch( ikeaWords[ i], dictionary, NumberOfWordsInDictionary) != -1) {
            // Ikea word was found, so display it
            printf("%4d. %-10s", ++ikeaWordsFoundCounter, ikeaWords [i]);
            wordsPerLineCounter++;
            if( wordsPerLineCounter == 5) {
                // print a new line and reset counter
                printf("\n");
                wordsPerLineCounter = 0;
            }
        }
    }//end for( int i...
    
    printf("\n");
}//end displayIKEAWordsFoundInDictionary()


//----------------------------------------------------------------------------------
// Return the word in place with the leading and trailing punctuation removed.
void removeLeadingAndTrailingPunctuation( char theWord[])
{
    // Make a copy of the word
    char wordCopy[ MaxWordSize];
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
}//end removeLeadingAndTrailingPunctuation()


//--------------------------------------------------------------------------------------
// For Stage 2: Compare each input file word against the IKEA list and display if found.
void lookupEachInputFileWordInIkeaWordList( char ikeaWords[ ][ MaxWordSize])
{
    FILE *pInputFile;
    char aWord[ MaxWordSize];
    
    openAndValidateInputFile( InputFileName, &pInputFile);
    
    // Handle each word one at a time, converting to lower case and removing leading and
    // trailing punctuation that would otherwise prevent a word match.
    while( fscanf(pInputFile, "%s", aWord) != EOF) {
        convertWordToLowerCase( aWord);
        removeLeadingAndTrailingPunctuation( aWord);
        
        if( binarySearch( aWord, ikeaWords, NumberOfIkeaWords) != -1) {
            // Input file word was found on IKEA words list
            printf("%s ", convertWordToUpperCase( aWord));
        }
        else {
            printf("%s ", aWord);
        }
    }
}//end lookupEachInputFileWordInIkeaWordList()


//--------------------------------------------------------------------------------------
// For Stage 4, delete a third character and see if that one is found in the words list.
// This is only called for each word after the first two characters have already been deleted.
//
// When we study recursion, we will see that we could have simply called the *original*
// function again, changing only numberOfCharactersToDelete.
//
int deleteAThirdCharacterAndCheckForMatch(
           char aWord[],                    // Original word with first two deletions already made
           char matchingWord[],             // Used to return the matching IKEA word if found
           char wordsList[ ][ MaxWordSize], // All the Ikea words, used for comparisons
           int  numberOfWordsInWordsList,   // How many words there are in the wordsList
           int  numberOfCharactersToDelete) // How many characters to delete.  This is 1 for stage 3
{
    char copyOfWord[ MaxWordSize];
    
    // Delete each character in turn
    for( int i=0; i<strlen( aWord); i++) {
        // Reset the word each time we delete a different character
        strcpy( copyOfWord, aWord);
        // Delete the ith character by copying over the rest of the word (starting from
        // the next character) on top of the character to delete.
        strcpy( &copyOfWord[ i], &aWord[ i+1]);
        
        // Delete the appropriate number of characters, then try and find a match for the word
        if( numberOfCharactersToDelete == 1){
            if( binarySearch( copyOfWord, wordsList, numberOfWordsInWordsList) != -1) {
                // Word with character i deleted does match an IKEA word, so return TRUE
                strcpy( matchingWord, copyOfWord);
                return TRUE;
            }
        } else {
            printf("*** Error, trying to delete too many characters. Exiting program. \n");
            exit( -1);
        }
    }//end for( int i...
    
    return FALSE;
}//end deleteASecondCharacterAndCheckForMatch()


//--------------------------------------------------------------------------------------
// For Stage 4, delete a second character and see if that one is found in the wordsList.
// This is only called for each word after the first character has already been deleted.
//
// When we study recursion, we will see that we could have simply called the *original*
// function again, changing only numberOfCharactersToDelete.
//
int deleteASecondCharacterAndCheckForMatch(
        char aWord[],                    // Original word with first deletion already made
        char matchingWord[],             // Used to return the matching IKEA word if found
        char wordsList[ ][ MaxWordSize], // All the Ikea words, used for comparisons
        int  numberOfWordsInWordsList,   // How many words there are in the wordsList
        int  numberOfCharactersToDelete) // How many characters to delete.  This is 1 for stage 3
{
    char copyOfWord[ MaxWordSize];

    // Delete each character in turn
    for( int i=0; i<strlen( aWord); i++) {
        // Reset the word each time we delete a different character
        strcpy( copyOfWord, aWord);
        // Delete the ith character by copying over the rest of the word (starting from
        // the next character) on top of the character to delete.
        strcpy( &copyOfWord[ i], &aWord[ i+1]);
        
        // Delete the appropriate number of characters, then try and find a match for the word
        if( numberOfCharactersToDelete == 1){
            if( binarySearch( copyOfWord, wordsList, numberOfWordsInWordsList) != -1) {
                // Word with character i deleted does match an IKEA word, so return TRUE
                strcpy( matchingWord, copyOfWord);
                return TRUE;
            }
        } else if( numberOfCharactersToDelete > 1){
            // Delete a third character if we are deleting more than 2, for Stage 4
            if( deleteAThirdCharacterAndCheckForMatch( copyOfWord, matchingWord, wordsList,
                                         numberOfWordsInWordsList,numberOfCharactersToDelete-1)) {
                return TRUE;
            }
        }
    }//end for( int i...
    
    return FALSE;
}//end deleteASecondCharacterAndCheckForMatch()


//--------------------------------------------------------------------------------------
// Delete some number of characters at a time from aWord, looking up each resulting word in a
// list of words.  Return TRUE if the word is found and store it in matchingWord.  If no word
// is found after trying all possible new words after deleting the designated number
// of characters, then return FALSE.
//
int deletingCharactersGivesAMatch(
        char aWord[],                    // Original word
        char matchingWord[],             // Used to return the matching word from wordList if found
        char wordsList[ ][ MaxWordSize], // List of words used for comparisons
        int  numberOfWordsInWordsList,   // How many words there are in the wordsList
        int  numberOfCharactersToDelete) // How many characters to delete.  This is 1 for stage 3
{
    char copyOfWord[ MaxWordSize];
    
    // Ensure length of word is > 1, so there is something to delete
    if( strlen( aWord) == 1) {
        return FALSE;   // Deleting the single character gives empty string, so it isn't in Ikea words
    }
    
    // Delete each character in turn
    for( int i=0; i<strlen( aWord); i++) {
            
        // Reset the word each time we delete a different character
        strcpy( copyOfWord, aWord);
        // Delete the ith character by copying over the rest of the word (starting from
        // the next character) on top of the character to delete.
        strcpy( &copyOfWord[ i], &aWord[ i+1]);

        // Delete the appropriate number of characters, then try and find a match for the word
        if( numberOfCharactersToDelete == 1){
            if( binarySearch( copyOfWord, wordsList, numberOfWordsInWordsList) != -1) {
                // Word with character i deleted does match an IKEA word, so return TRUE
                strcpy( matchingWord, copyOfWord);
                return TRUE;
            }
        } else if( numberOfCharactersToDelete > 1){
            // Delete an second character if we are deleting more than 1, for Stage 4
            if( deleteASecondCharacterAndCheckForMatch( copyOfWord, matchingWord, wordsList,
                                    numberOfWordsInWordsList, numberOfCharactersToDelete-1)) {
                return TRUE;
            }
        }
    }//end for( int i...
    
    // If we got to here it means there was no match
    return FALSE;
}//end deletingCharactersGivesAMatch()


//--------------------------------------------------------------------------------------
// See if substituting a single character in aWord gives a match.  Do this by cycling
// through the Ikea words one at a time and selecting the ones that are the same length
// as aWord.  For each one count how many characters are different between the two
// words.  If the difference is exactly one, then substituting a character does match
// the Ikea word being considered, so store the word into matchingWord and return TRUE.
//
int substitutingACharacterGivesAMatch(
          char aWord[],                             // Original word
          char matchingWord[],                      // Used to return the matching IKEA word if found
          char ikeaWords[ ][ MaxWordSize],          // All the Ikea words, used for comparison
          int  numberOfDifferentCharactersExpected) // How many characters should be different.  This is 1 for stage 3
{
    int numberOfCharactersDifferent = 0;
    
    // Step through each word in the Ikea list
    for( int i=0; i<NumberOfIkeaWords; i++) {
        // Select only the ones that are the same length as aWord
        if( strlen( aWord) == strlen( ikeaWords[ i])) {
            
            numberOfCharactersDifferent = 0;
            // Count how many characters are different between the two words
            for( int j=0; j<strlen( aWord); j++) {
                // Increment a counter if the characters are different at position j
                if( aWord[ j] != ikeaWords[ i][j]) {
                    numberOfCharactersDifferent++;
                }
            }//end for( int j...
            
            // See if this Ikea word is exactly the proscribed number of characters different from aWord
            if( numberOfCharactersDifferent == numberOfDifferentCharactersExpected) {
                // Word with those character differences does match an IKEA word, so return TRUE
                strcpy( matchingWord, ikeaWords[ i]);
                return TRUE;
            }
            
        }//end if( strlen...
    }//end for( int i...
    
    return FALSE;   // There was no match
}//end substitutingACharacterGivesAMatch()


//--------------------------------------------------------------------------------------
// See if inserting a single character in aWord gives a match.  Do this by stepping through
// the Ikea words and selecting the ones that are the designated number of characters longer than aWord.
// Delete one character at a time from the current Ikea word and then see if it matches
// aWord.  If it matches, store it into matchingWord and return TRUE.
//
int insertingACharacterGivesAMatch(
           char aWord[],                    // Original word
           char matchingWord[],             // Used to return the matching IKEA word if found
           char ikeaWords[ ][ MaxWordSize], // All the Ikea words, used for comparison
           int numberOfCharactersToInsert)  // How many characters that can be different
{
    // Make a 2d array with only aWord in it, so we can reuse the delete function, sending this word
    // to match against instead of sending the full list of Ikea words.
    char singleWord2dArray[1][MaxWordSize];
    strcpy( singleWord2dArray[ 0], aWord);   // Make a 2D array with only a single word in it

    // Step through each word in the Ikea list
    for( int i=0; i<NumberOfIkeaWords; i++) {
        
        // Select the ones that are the designated number of characters longer than aWord
        if( strlen( ikeaWords[ i]) == strlen( aWord) + numberOfCharactersToInsert) {

            // Delete some number of characters and check for a match
            if( deletingCharactersGivesAMatch( ikeaWords[ i], matchingWord, singleWord2dArray,
                                               1, numberOfCharactersToInsert)) {
                // delete sets matchingWord to be the word with characters deleted, but since we
                // are using it backwards, here we want to record the original Ikea word with
                // more characters in it.
                strcpy( matchingWord, ikeaWords[ i]);
                return TRUE;
            }
            
        }//end if( strlen...
    }//end for( int i...
    
    return FALSE;   // There was no match
}//end insertingACharacterGivesAMatch()


//--------------------------------------------------------------------------------------
// See if Test word "aWord" is a substring of some IkeaWord.  If it is set the matching
// word into matchingWord and return TRUE.
//
int wordIsASubstring(
         char aWord[],                    // Original word
         char matchingWord[],             // Used to return the matching IKEA word if found
         char ikeaWords[ ][ MaxWordSize]) // All the Ikea words, used for comparison
{
    // Step through each word in the Ikea list
    for( int i=0; i<NumberOfIkeaWords; i++) {
        
        // See if aWord is a substring of some IKEA word
        if( strstr( ikeaWords[i], aWord)) {
            strcpy( matchingWord, ikeaWords[i]);
            return TRUE;
        }
        
    }//end for( int i...
    
    return FALSE;   // There was no match
}//end wordIsASubstring()


//--------------------------------------------------------------------------------------
// For Stage 3: Again take each word to lookup in the IKEA list, but this time do the
// following modifications each time before comparing against the IKEA list:
//   1. Look it up as-is
//   2. Delete one character
//   3. Substitute one character
//   4. Insert a new character
//   5. Match a substring
// Once an IKEA word match is found, no further exploration is done.  In each of the
// functions the word found is stored in array matchingWord, to be used in printing it out.
// Following Fengfeng Fu's idea (CS 141 student), the comparisons are done "backwards".
// Rather than generating all possible strings and looking them up one by one, instead
// we go through IKEA words and see if they might have matched for each condition.
//
void lookupModifiedWordsInIkeaWordList( char ikeaWords[ ][ MaxWordSize], int numberOfCharactersToModify)
{
    FILE *pInputFile;
    char aWord[ MaxWordSize];
    char matchingWord[ MaxWordSize];      // Stores matching IKEA word when found
    int wordWasFoundInIkeaList = FALSE;   // start this out as false.  Set it to true once a word is found
    
    openAndValidateInputFile( InputFileName, &pInputFile);
    
    // Handle each word one at a time,
    while( fscanf(pInputFile, "%s", aWord) != EOF) {
        // Converting aWord to lower case and removing leading and trailing punctuation that would
        //    otherwise prevent a word match.
        convertWordToLowerCase( aWord);
        removeLeadingAndTrailingPunctuation( aWord);
        
        wordWasFoundInIkeaList = FALSE;
        
        // Check each of the possible conditions, storing the matching IKEA word when found into matchingWord
        if( binarySearch( aWord, ikeaWords, NumberOfIkeaWords) != -1) {
            wordWasFoundInIkeaList = TRUE;
            strcpy( matchingWord, aWord);    // Input file word was found as-is on IKEA words list
        }
        else {
            // For character changes, first check single character changes, then 2, then 3, as called for
            //       by the value of parameter numberOfCharactersToModify
            for( int i=1; i<=numberOfCharactersToModify; i++) {
               if( deletingCharactersGivesAMatch( aWord, matchingWord, ikeaWords, NumberOfIkeaWords, i)) {
                    wordWasFoundInIkeaList = TRUE;     // Word with one character deleted was found on IKEA words list
                    break;
                }
                else if( substitutingACharacterGivesAMatch( aWord, matchingWord, ikeaWords, i)) {
                    wordWasFoundInIkeaList = TRUE;     // Word with one character substituted was found on Ikea words list
                    break;
                }
                else if ( insertingACharacterGivesAMatch( aWord, matchingWord, ikeaWords, i)) {
                    wordWasFoundInIkeaList = TRUE;     // Word with additional characters matches an Ikea word
                    break;
                }
                else if( wordIsASubstring( aWord, matchingWord, ikeaWords)) {
                    wordWasFoundInIkeaList = TRUE;     // Word is a substring of some Ikea word
                    break;
                }

            }//end for( int i...
        }
        
        if( wordWasFoundInIkeaList) {
            printf("%s ", convertWordToUpperCase( matchingWord));
        }
        else {
            // Echo the word as lower case, since it was not found in the Ikea list
            printf("%s ", aWord);
        }
        fflush(stdout);
    }
}//end lookupModifiedWordsInIkeaWordList()


//--------------------------------------------------------------------------------------
int main()
{
    char ikeaWords[ NumberOfIkeaWords][ MaxWordSize];
    char dictionary[ NumberOfWordsInDictionary][ MaxWordSize];

    displayIdentifyingInformation();
    
    // Read dictionary words and IKEA words into their respective arrays
    readWordsFromFile( DictionaryFileName, dictionary);
    readWordsFromFile( IkeaWordsFileName, ikeaWords);
    
    convertAllIKEAWordsToLowerCase( ikeaWords);  // Convert IKEA words to all lower case
    
    // Stage 1: Step through each IKEA word, echoing it if it is found in the dictionary.
    printf("\n1. Ikea words found in the dictionary are: \n");
    displayIKEAWordsFoundInDictionary( ikeaWords, dictionary);

    // Stage 2: Handle each input file word one at a time and print it if it exactly matches some IKEA word
    printf("\n2. Input file words found in the Ikea list are: \n");
    lookupEachInputFileWordInIkeaWordList( ikeaWords);
    
    // Stage 3: Handle each input file word one at a time and and check for IKEA word matching after 1 character changes
    printf("\n");
    printf("\n3. Input file words found in the Ikea list after 1 delete, substitute, insert or substring search are: \n");
    lookupModifiedWordsInIkeaWordList( ikeaWords, 1);
    
    // Stage 4: Handle each input file word one at a time and and check for IKEA word matching after multiple character changes
    printf("\n");
    printf("\n4. Input file words found in the Ikea list after multiple delete, substitute, insert or substring searches are: \n");
    lookupModifiedWordsInIkeaWordList( ikeaWords, 3);
    
    printf("\n");
    printf("\nDone.\n");
    return 0;
}//end main()
