/*=============================================================================
|   Source code:  [perfect-number-tester]
|        Author:  [Hector Ramirez]
|    Student ID:  [Your Student ID]
|    Assignment:  Program #[2] [Perfect Numbers]
|
|            Course:  [COP 4338]
|           Section:  [U04]
|        Instructor:  William Feild
|          Due Date:  [10/01/2019], at the beginning of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|
|        Language:  [C]
|  Compile/Run:  [The fallowing instructions is to compile in the ocelot server at FIU.
|                   -std=c99: used to direct the compiler to use the newer c99 standard and libraries.
|                   -lm: used to tell the compiler to link the math library.
|                   -O3: this activates the highest level optimizations by the gcc compiler. This will activate
|                         several compiler directives. full list can be found at:
|                         https://gcc.gnu.org/onlinedocs/gcc-6.4.0/gcc/Optimize-Options.html#Optimize-Options.
|                         -O3 activates all directives from -O and -O2, these are listed on the top linked site.]
| 	gcc -std=c99 -lm -O3 *.c -o perfect-numbers
|   ./perfect-numbers
|  +-----------------------------------------------------------------------------
|
|  Description:  [//Todo]
|
|        Input:  [//Todo]
|
|       Output:  [//Todo]
|
|     Process:  [//Todo]
|
|   Required Features Not Included:
|                [//Todo]
|
|   Known Bugs:  [//Todo]
|  *===========================================================================*/
#include "perfect-numbers.h"
#include <ctype.h>


/**
 * As per the specifications, this are the boundaries to consider when reading input for the user. This will be the
 * min desired accuracy entered by the user and the maximum desired accuracy allowed.
 */
#define MIN_PRECISION 1
#define MAX_PRECISION 15

/**
 * Functions Prototypes, further information regarding each function provided in each functions function header.
 */
void promptUser(void);
int getAccuracyFromUser(void);
int validateInput(int unvalidatedInput);
double computeDesiredDelta(int decimalPlaceAccuracy);

int main(void)
{
    int desiredAccuracy = getAccuracyFromUser();
    double threshold = computeDesiredDelta(desiredAccuracy);
    mainLoop(desiredAccuracy,threshold);
    return NO_ERROR;

}

/**
 * FUNCTION NAME: promptUser
 * Prints prompts message to the screen.
 * PROMPT_MESSAGE : Used to properly prompt message with proper formatting with scanf.
 * @param: None
 * @return: None
 */
#define PROMPT_MESSAGE "Enter whole number between %d and %d for the accuracy of the square root of perfect number: "
void promptUser(void)
{
    printf(PROMPT_MESSAGE,MIN_PRECISION,MAX_PRECISION);
}

/**
 * FUNCTION NAME: getAccuracyFromUser
 * Code used in this validation was obtained from:
 * https://stackoverflow.com/questions/26583717/how-to-scanf-only-integer
 * Answer by: John Bode
 * Date: October 27, 2014.
 * Modified by Hector R to confirm to style guidelines.
 * isspace() function is explained on Chapter # 4 of (K/R) Page 71
 * Function will get the input from stdin and read it an integer variable, as per the specs the maximum number that we
 * can read is 15, a 2 digit number, we can set the scanf to only read the field of size 2 if it is over that it will
 * fail, if it encounters an error when converting it will fail as well.
 * SCANF_INPUT_STRING: String used to read the input from scanf for formatting.
 * SCANF_SUCCESS: Default case when user fallows instructions and enters only 1 whole number
 * SCANF_READ_TOO_MANY: when the fallow char is matched and user enter some input believed to be not valid.
 * @param : NONE (void)
 * @return a verified user input for desired decimal accuracy.
 */
#define SCANF_INPUT_STRING "%d%c"
#define SCANF_SUCCESS 1
#define SCANF_READ_TOO_MANY 2
#define NEW_LINE_CHAR '\n'
int getAccuracyFromUser(void)
{
    int input = EMPTY_INITIALIZER;
    int validated = EMPTY_INITIALIZER;
    int scanfStatus = EMPTY_INITIALIZER;
    char follow = EMPTY_INITIALIZER;

    do
    {
        promptUser();
        scanfStatus = scanf(SCANF_INPUT_STRING, &input, &follow );

        if ( scanfStatus == SCANF_READ_TOO_MANY)
        {
            //checks is fallow character is whitespace.
            if ( isspace( follow ) )
            {
                validated = validateInput(input);
            }
            else
            {
                while(getchar() != NEW_LINE_CHAR);
            }
        }
        else if ( scanfStatus == SCANF_SUCCESS)
        {
            validated = validateInput(input);
        }
        else
        {
            while(getchar() != NEW_LINE_CHAR);
        }
    }while (!validated);

    return input;

}

/**
 * Validates the passed parameter to verify that it is withing the specified range.
 * IS_VALID: return value of 1 if the number is found to be within range
 * NOT_VALID : return value of 0 if the number is outside the range.
 * @param unvalidatedNum : number to validated
 * @return : returns 1 if validated if number is withing range, 0 if outside range.
 */
#define IS_VALID 1
#define NOT_VALID 0
int validateInput(int unvalidatedNum)
{
    if(unvalidatedNum >= MIN_PRECISION && unvalidatedNum <= MAX_PRECISION)
    {
        return IS_VALID;
    }
    else
    {
        return NOT_VALID;
    }
}

/**
 * FUNCTION NAME: computeDesiredDelta
 * This function computes the allowed threshold when computing the squares.
 * Uses mathematical function
 * This is a previously known mathematical equation.
 * Threshold (Delta) = 1.0 / (10^decimalPlaceAccuracy)
 * for the power we will be using the math function pow().
 * return type is set to double as high level of precision is needed for higher decimal place accuracy.
 * @param decimalPlaceAccuracy: number of decimal places make the delta accurate to.
 * @return decimal value of the maximum threshold desired by the user.
 */
double computeDesiredDelta(int decimalPlaceAccuracy)
{
    double threshold = (1.0 / pow(10,decimalPlaceAccuracy));
    return threshold;
}