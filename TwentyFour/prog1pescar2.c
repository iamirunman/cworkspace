/* TwentyFour.c
 Generate all possible combinations of 4 digits and 3 operators (+,-,*,/)
 where the operators are combined to give the value 24.
 
	Author: Pablo Escarcega
 
	Sample Output:
 
         Author: Pablo Escarcega
         Program: #1, TwentyFour

         
         Welcome to the game of TwentyFour.  Using each of the four numbers shown
         below exactly once, combining them somehow with the basic mathematical
         operators (+,-,*,/) to yield the value twenty-four.
         
         The numbers to use are: 3, 8, 8, 8
         
         Enter the three operators to be used (+,-,*, or /): *+-
         3.0 * 8 is: 24.00
         24.0 + 8 is: 32.00
         32.0 - 8 is: 24.00
         
         Well done, genius!
         
         
         
         Would you like to play again (Y/N): n
         
         Thanks for playing.  Exiting program...
         
         Program ended with exit code: 0
 
    Sample Output of the DEBUG output, when SHOW_DEBUG is set to 1 at the top of the program:
 
         *** Start Debug Display ***
         1. 1 + 1 + 1 * 8
         2. 1 + 1 + 2 * 6
         3. 1 + 1 * 2 * 6
         4. 1 * 1 + 2 * 8
         5. 1 / 1 + 2 * 8
         6. 1 + 1 * 3 * 4
         7. 1 * 1 + 3 * 6
         8. 1 / 1 + 3 * 6
         9. 1 - 1 + 3 * 8
         10. 1 * 1 * 3 * 8
         11. 1 / 1 * 3 * 8
         .
         .
         .
         3171. 9 / 9 + 5 * 4
         3172. 9 + 9 + 6 * 1
         3173. 9 + 9 + 6 / 1
         3174. 9 + 9 - 6 * 2
         3175. 9 - 9 + 6 * 4
         3176. 9 / 9 * 6 * 4
         3177. 9 + 9 / 6 * 8
         3178. 9 + 9 + 7 - 1
         3179. 9 / 9 + 7 * 3
         3180. 9 + 9 + 8 - 2
         3181. 9 - 9 + 8 * 3
         3182. 9 / 9 * 8 * 3
         3183. 9 + 9 * 8 / 6
         3184. 9 + 9 + 9 - 3
         3185. 9 * 9 - 9 / 3
         Puzzle to choose is #883: 3*8+8-8
         *** End Debug Display ***
 
 */
//--------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Global constants
const int SHOW_DEBUG = 1;   // set a value so that DEBUG can be tested for true/false
const int TRUE = 1;         // this way TRUE can be used as a logical condition


//--------------------------------------------------------------------------------
// Display name and program information
void displayIdentifyingInformation()
{
    printf("\n");
    printf("Author: Pablo Escarcega    \n");
    printf("Program: #1, TwentyFour    \n");
    printf("\n");
}//end displayIdentifyingInformation()


//--------------------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    printf("Welcome to the game of TwentyFour.  Using each of the four numbers shown \n");
    printf("below exactly once, combining them somehow with the basic mathematical \n");
    printf("operators (+,-,*,/) to yield the value twenty-four. \n");
    printf("\n");
}//end displayInstructions()


//--------------------------------------------------------------------------------
// Check the final result of operations with 4 numbers to see if it == 24.
// If so display it.
void checkResult( char op1, char op2, char op3,
                  double num1, double num2, double num3, double num4,
                  double result,
                  int randomNumber, int &counter,
                  int &digitToUse1, int &digitToUse2, int &digitToUse3, int &digitToUse4,
                  char &operatorToUse1, char &operatorToUse2, char &operatorToUse3)
{
    // Check result
    if( fabs(result-24) < 0.001) {
        if( SHOW_DEBUG) {
            printf("%4d. %1.0f %c %1.0f %c %1.0f %c %1.0f\n", counter, num1, op1, num2, op2, num3, op3, num4);
            fflush(stdout);  // make sure output is shown
        }
        
        if (counter == randomNumber) {
            // store values to use for problem presented to user
            digitToUse1 = num1; digitToUse2 = num2; digitToUse3 = num3; digitToUse4 = num4;
            operatorToUse1 = op1; operatorToUse2 = op2; operatorToUse3 = op3;
        }
        
        counter++;   // increment solution counter
    }
}//end checkResult


//--------------------------------------------------------------------------------
// Try all combinations between the result of the second pair with the fourth number,
// passing them on to another function to see if the result == 24.  Pass along
// the ops used so far so that at the inner-most level we can print out
// the ops used to give the resulting number.
void thirdPair( char op1, char op2,
               double num1, double num2, double num3, double num4,
               double resultSoFar,
               int randomNumber, int &counter,
               int &digitToUse1, int &digitToUse2, int &digitToUse3, int &digitToUse4,
               char &operatorToUse1, char &operatorToUse2, char &operatorToUse3)
{
    checkResult( op1, op2, '+', num1, num2, num3, num4, resultSoFar + num4, randomNumber, counter,
                 digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    checkResult( op1, op2, '-', num1, num2, num3, num4, resultSoFar - num4, randomNumber, counter,
                 digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    checkResult( op1, op2, '*', num1, num2, num3, num4, resultSoFar * num4, randomNumber, counter,
                 digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    checkResult( op1, op2, '/', num1, num2, num3, num4, resultSoFar / num4, randomNumber, counter,
                 digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
}//end thirdPair()


//--------------------------------------------------------------------------------
// Try all combinations between the result of the first pair with the third number,
// passing them on to another function to consider the last number.  Pass along
// the ops used so far so that at the inner-most level we can print out
// the ops used to give the resulting number.
void secondPair( char op1,
                double num1, double num2, double num3, double num4,
                double resultSoFar,
                int randomNumber, int &counter,
                int &digitToUse1, int &digitToUse2, int &digitToUse3, int &digitToUse4,
                char &operatorToUse1, char &operatorToUse2, char &operatorToUse3)
{
    thirdPair( op1, '+', num1, num2, num3, num4, resultSoFar + num3, randomNumber, counter,
               digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    thirdPair( op1, '-', num1, num2, num3, num4, resultSoFar - num3, randomNumber, counter,
               digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    thirdPair( op1, '*', num1, num2, num3, num4, resultSoFar * num3, randomNumber, counter,
               digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    thirdPair( op1, '/', num1, num2, num3, num4, resultSoFar / num3, randomNumber, counter,
               digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
}//end secondPair()


//--------------------------------------------------------------------------------
// Try all combinations of the first two numbers, passing them on to another
// function to consider subsequent pairs.
void firstPair( double num1, double num2, double num3, double num4,
               int randomNumber, int &counter,
               int &digitToUse1, int &digitToUse2, int &digitToUse3, int &digitToUse4,
               char &operatorToUse1, char &operatorToUse2, char &operatorToUse3)
{
    secondPair( '+', num1, num2, num3, num4, num1 + num2, randomNumber, counter,
                digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    secondPair( '-', num1, num2, num3, num4, num1 - num2, randomNumber, counter,
                digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    secondPair( '*', num1, num2, num3, num4, num1 * num2, randomNumber, counter,
                digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
    secondPair( '/', num1, num2, num3, num4, num1 / num2, randomNumber,  counter,
                digitToUse1, digitToUse2, digitToUse3, digitToUse4, operatorToUse1, operatorToUse2, operatorToUse3);
}//end firstPair()


//--------------------------------------------------------------------------------
// Display intermediate result and return it
double findResultAndDisplay(
                double num1,  // first operand, as a double
                char c,       // the operator as a char (one of +,-,*,/)
                int num2)     // second operand
{
    // find the result depending on the operator
    double result = 0.0;
    switch( c) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
    }
    printf("%3.1f %c %d is: %4.2f \n", num1*1.0, c, num2, result);
    
    return result;
}//end findResultAndDisplay()


//--------------------------------------------------------------------------------
// Verify the parameter is one of the characters +,-,*,/
int isValid( char c)
{
    if( c=='+' || c=='-' || c=='*' || c=='/') {
        return 1;   // 1 for true
    }
    else {
        return 0;   // 0 for false
    }
}//end isValid()


//--------------------------------------------------------------------------------
// Get the 3 operators and see if answer is correct
void solvePuzzle( int digitToUse1, int digitToUse2, int digitToUse3, int digitToUse4)
{
    char operator1, operator2, operator3;   // user operators (e.g. *+/ )
    char returnCharacter; // Stores the 4th key the user presses when prompted for input.
    //    Usually this should be the return character
    double result = 0.0;    // stores intermediate results
    
    // Present the puzzle to the user
    printf("The numbers to use are: %d, %d, %d, %d\n\n", digitToUse1, digitToUse2, digitToUse3, digitToUse4);
    fflush(stdout);
    
    // prompt for and validate user input
    do {
        // Prompt for user input
        printf("Enter the three operators to be used (+,-,*, or /): ");   fflush(stdout);
        
        // store user input of 3 operators (e.g. *-/) as well as the following character,
        // which should be the return character if input was correct
        scanf(" %c%c%c%c", &operator1, &operator2, &operator3, &returnCharacter);   // skip leading space
        
        // verify input length
        if( returnCharacter != '\n') {
            printf("*** Sorry, that input is the wrong length.  Please retry. ***\n");
            continue;  // loop back up and retry
        }
        
        // verify input characters are all valid.  Break out of loop if they are.
        if( isValid( operator1) && isValid( operator2) && isValid( operator3)) {
            break;   // break out of enclosing loop
        }
        else {
            printf("*** Sorry, invalid characters in input.  Please retry. ***\n");
            continue;   // loop back up and retry.
            // The above line is not strictly necessary, since we are end of loop anyway.
        }
        
    }while( TRUE);
    
    // Find each intermediate result, one at a time.  Convert first number from
    // int to double before passing it.
    result = findResultAndDisplay( 1.0 * digitToUse1, operator1, digitToUse2);    // first pair
    result = findResultAndDisplay( result, operator2, digitToUse3);              // second pair
    result = findResultAndDisplay( result, operator3, digitToUse4);              // third pair
    
    // Give appropriate message depending on whether or not result was correct.
    printf("\n");
    //if( result == 24.0) {            // using this version of comparison gives 3185 results
    if( fabs(result-24) < 0.001) {     // using this version of comparison gives 3185 results
        // correct answer
        printf("Well done, genius!");
    }
    else {
        // answer not correctd
        printf("Not right.  Better luck next  time.");
    }
    printf("\n\n");  fflush(stdout);
}//end solvePuzzle()


//--------------------------------------------------------------------------------
int main()
{
    char playAgainResponse = ' ';  // stores Y/N for response on whether to play again
    int randomNumber;
    srand( 1);   // seed the random number generator.  Put time( NULL) inside parenthesis for variable results
    int num1, num2, num3, num4;    // numbers used for counting in nested loops to get all possibilities
    int counter = 1;
    // The four digitsToUse variables will store the randomly selected set of 4 values to present to the user.
    int digitToUse1 = 0,
        digitToUse2 = 0,
        digitToUse3 = 0,
        digitToUse4 = 0;
    // The three operatorToUse variables store in turn all possible operator combinations
    char operatorToUse1 = ' ',
         operatorToUse2 = ' ',
         operatorToUse3 = ' ';
    
    // display name and program information
    displayIdentifyingInformation();
    
    displayInstructions();
    
    // loop to allow user to play multiple times
    do {
        counter = 1;   // reset this each time through the loop
        randomNumber = rand()%3185 + 1;  // add 1 because generated number is in range 0..3184
                                         // and our Counter is starting at 1, not 0
        
        // optionally display debugging information.  "Debug" is declared at top of program.
        if( SHOW_DEBUG) {
            printf("*** Start Debug Display *** \n");
        }
        // Generate all possible combinations of 4 numbers (3 sets)
        for(num1=1; num1<10; num1++) {
            for( num2=1; num2<10; num2++) {
                for( num3=1; num3<10; num3++) {
                    for( num4=1; num4<10; num4++) {
                        
                        // Check all combinations of numbers.  Convert int to
                        // double to avoid rounding errors.  Pass digitToUse and operatorToUse
                        // variables, which will store the set of values and operators whose index
                        // corresponds to the random number.
                        firstPair( (double)num1, (double)num2, (double)num3, (double)num4, randomNumber, counter,
                                   digitToUse1, digitToUse2, digitToUse3, digitToUse4,
                                   operatorToUse1, operatorToUse2, operatorToUse3);
                        
                    }//end for( int num4Ö
                }//end for( int num3...
            }//end for( int num2...
        }//end for(int num1
        
        // optionally display debugging information.  "Debug" is declared at top of program.
        if( SHOW_DEBUG) {
            printf("Puzzle to choose is #%d: %d%c%d%c%d%c%d\n",
                   randomNumber, digitToUse1, operatorToUse1, digitToUse2, operatorToUse2, digitToUse3, operatorToUse3, digitToUse4);
            printf("*** End Debug Display ***\n\n");
        }
        
        // Try to solve puzzle
        solvePuzzle( digitToUse1, digitToUse2, digitToUse3, digitToUse4);
        
        printf("\n");
        printf("\n");
        printf("Would you like to play again (Y/N): ");    fflush(stdout);
        scanf(" %c", &playAgainResponse);   // space inside quotes skips leading space on input
    } while( playAgainResponse == 'Y' || playAgainResponse == 'y');
    
    printf("\nThanks for playing.  Exiting program...\n\n");
    
    return 0;
}//end main()

